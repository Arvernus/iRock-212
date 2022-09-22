#include <SSRSwitcher.h>
#include <TaskManagerIO.h>
#include <ExecWithParameter.h>
#include <MappingIO.h>
#include <Compare.h>
#include <BatShutOff.h>
#include <CLI.h>

#ifndef SSRSWITCHER_SIGNAL_LIST
#define SSRSWITCHER_SIGNAL_LIST "SSRSwitcherSignalTest.h"
#endif // SSRSWITCHER_SIGNAL_LIST
#include SSRSWITCHER_SIGNAL_LIST

#define SSRSwitcherId(Name, SignalIdActor, SignalIdSwitch) Name,
typedef enum
{
    SSRSwitcherIdList
        NoSSRSwitcher
} SSRSwitcherId;
#undef SSRSwitcherId
struct SSRSwitcherIdData
{
    Signals::SignalId SignalIdActor;
    Signals::SignalId SignalIdSwitch;
    String Name;
};
#define SSRSwitcherId(Name, SignalIdActor, SignalIdSwitch) \
    {SignalIdActor, SignalIdSwitch, #Name},
static SSRSwitcherIdData SSRSwitcherIds[] = {SSRSwitcherIdList};
#undef SSRSwitcherId

struct SSRSwitcherSwitchData
{
    SSRSwitcherId SSR;
    Signals::SignalId Input;
    unsigned int ActiveTime;
    unsigned int HoldTime;
    Signals::SignalId shunt;
    const Compare::Limit<float> shuntOffLimit;
    const Compare::Limit<float> shuntOnLimit;
};
#define SSRSwitcherSwitch(SSRSwitcherId, SignalIdSwitch, ActiveTime, HoldTime, Shunt, CompareType, MinMaxOff, ReleaseOff, MinMaxOn, ReleaseOn) \
    {SSRSwitcherId, SignalIdSwitch, ActiveTime, HoldTime, Shunt, {(Compare::LimitMode)Compare::CompareType, MinMaxOff, ReleaseOff, MinMaxOff, ReleaseOff}, {(Compare::LimitMode)Compare::CompareType, MinMaxOn, ReleaseOn, MinMaxOn, ReleaseOn}},
SSRSwitcherSwitchData SSRSwitcherSwitchs[] = {SSRSwitcherSwitchList};
#undef SSRSwitcherSwitch

class SSRSwitcherHandler : public Executable
{
private:
    bool lastStatus = false;

public:
    SSRSwitcherHandler(/* args */);
    ~SSRSwitcherHandler();
    void exec();
    void evaluate(SSRSwitcherId Id);
    bool input[sizeof(SSRSwitcherSwitchs) / sizeof(SSRSwitcherSwitchData)];
};
static SSRSwitcherHandler *SSRSwitcherTask = new SSRSwitcherHandler();

class SSRSwitcherTimeHandler : public Executable
{
private:
    SSRSwitcherId SSR;
    SSRSwitcher::OutputStatus outputStatus;
    unsigned int taskId;
    SSRSwitcherSwitchData *Trigger;

public:
    SSRSwitcherTimeHandler(SSRSwitcherId Id);
    ~SSRSwitcherTimeHandler();
    void init();
    void exec();
    void setStatus(SSRSwitcher::OutputStatus newStatus, unsigned int time = 2);
    void setTrigger(SSRSwitcherSwitchData *input);
    SSRSwitcher::OutputStatus getStatus();
};
static SSRSwitcherTimeHandler *SSRSwitcherTimeTask[NoSSRSwitcher];

SSRSwitcherHandler::SSRSwitcherHandler(/* args */)
{
}

SSRSwitcherHandler::~SSRSwitcherHandler()
{
}

void SSRSwitcherHandler::exec()
{

    for (SSRSwitcherId i = (SSRSwitcherId)0; i < NoSSRSwitcher; i = (SSRSwitcherId)((unsigned int)i + 1))
    {
        evaluate(i);
    }
}
void SSRSwitcherHandler::evaluate(SSRSwitcherId Id)
{

    bool testing = false; // true is logic working
    for (size_t j = 0; j < sizeof(SSRSwitcherSwitchs) / sizeof(SSRSwitcherSwitchData); j++)
    {
        bool input = !Signals::GetDigitalValue(SSRSwitcherSwitchs[j].Input) && SSRSwitcherSwitchs[j].SSR == Id;
        if (input)
        {
            SSRSwitcherTimeTask[Id]->setTrigger(&SSRSwitcherSwitchs[j]);
        }
        testing = testing || input;
    }
    if (testing != lastStatus)
    {
        if (testing)
        {
            SSRSwitcherTimeTask[Id]->setStatus(SSRSwitcher::shutoff);
        }
        else if (SSRSwitcherIds[Id].SignalIdSwitch)
        {
            SSRSwitcherTimeTask[Id]->setStatus(SSRSwitcher::open);
        }
        else
        {
            SSRSwitcherTimeTask[Id]->setStatus(SSRSwitcher::closed);
        }
    }
    lastStatus = testing;
}

SSRSwitcherTimeHandler::SSRSwitcherTimeHandler(SSRSwitcherId Id)
{
    SSR = Id;
    SSRSwitcherTimeTask[Id] = this;
    SSRSwitcherTimeHandler::init();
}

SSRSwitcherTimeHandler::~SSRSwitcherTimeHandler()
{
    taskManager.cancelTask(taskId);
}

void SSRSwitcherTimeHandler::init()
{
    outputStatus = SSRSwitcher::closed;
    taskId = taskManager.execute(SSRSwitcherTimeTask[SSR]);
    Trigger = &SSRSwitcherSwitchs[0];
}

void SSRSwitcherTimeHandler::exec()
{
    Compare::compare_result compare_result;
    bool thisTrigger;
    switch (outputStatus)
    {
    case SSRSwitcher::shutoff:
        Signals::SetDigitalValue(SSRSwitcherIds[SSR].SignalIdActor, false);
        setStatus(SSRSwitcher::waiting, Trigger->HoldTime);
        break;
    case SSRSwitcher::waiting:
        compare_result = Compare::calc<float>(Signals::GetAnalogValue(Trigger->shunt), Trigger->shuntOffLimit);
        if (compare_result.trigger)
        {
            Signals::SetDigitalValue(SSRSwitcherIds[SSR].SignalIdActor, true);
            setStatus(SSRSwitcher::testing, Trigger->ActiveTime);
        }
        if (compare_result.release)
        {
            setStatus(SSRSwitcher::waiting, Trigger->HoldTime);
        }
        break;
    case SSRSwitcher::testing:
        compare_result = Compare::calc<float>(Signals::GetAnalogValue(Trigger->shunt), Trigger->shuntOnLimit);
        if (compare_result.trigger)
        {
            setStatus(SSRSwitcher::testing, Trigger->HoldTime);
        }
        if (compare_result.release)
        {
            Signals::SetDigitalValue(SSRSwitcherIds[SSR].SignalIdActor, true);
            setStatus(SSRSwitcher::waiting, Trigger->HoldTime);
        }
        break;
    case SSRSwitcher::open:
        Signals::SetDigitalValue(SSRSwitcherIds[SSR].SignalIdActor, true);
        break;
    case SSRSwitcher::closed:
        Signals::SetDigitalValue(SSRSwitcherIds[SSR].SignalIdActor, false);
        break;
    default:
        Signals::SetDigitalValue(SSRSwitcherIds[SSR].SignalIdActor, false);
        break;
    }
}
void SSRSwitcherTimeHandler::setStatus(SSRSwitcher::OutputStatus newStatus, unsigned int time)
{
    taskManager.cancelTask(taskId);
    if (outputStatus != newStatus)
        switch (newStatus)
        {
        case SSRSwitcher::shutoff:
            Cli::printInfo("SSRSwitcher: Change to Status shutoff");
            break;
        case SSRSwitcher::waiting:
            Cli::printInfo("SSRSwitcher: Change to Status waiting");
            break;
        case SSRSwitcher::testing:
            Cli::printInfo("SSRSwitcher: Change to Status testing");
            break;
        case SSRSwitcher::open:
            Cli::printInfo("SSRSwitcher: Change to Status open");
            break;
        case SSRSwitcher::closed:
            Cli::printInfo("SSRSwitcher: Change to Status closed");
            break;
        default:
            Cli::printInfo("SSRSwitcher: Error no Status");
            break;
        }
    outputStatus = newStatus;
    taskId = taskManager.scheduleOnce(time, SSRSwitcherTimeTask[SSR]);
}
void SSRSwitcherTimeHandler::setTrigger(SSRSwitcherSwitchData *input)
{
    Trigger = input;
}

SSRSwitcher::OutputStatus SSRSwitcherTimeHandler::getStatus()
{
    return outputStatus;
}

void SSRSwitcher::setup(unsigned int interval)
{
    for (SSRSwitcherId Id = (SSRSwitcherId)0; Id < NoSSRSwitcher; Id = (SSRSwitcherId)((unsigned int)Id + 1))
    {
        new SSRSwitcherTimeHandler(Id);
    }
    taskManager.scheduleFixedRate(interval, SSRSwitcherTask);
}