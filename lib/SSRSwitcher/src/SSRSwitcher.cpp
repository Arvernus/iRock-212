#include <SSRSwitcher.h>
#include <TaskManagerIO.h>
#include <ExecWithParameter.h>
#include <MappingIO.h>
#include <Compare.h>
#include <BatShutOff.h>

#ifndef SSRSWITCHER_SIGNAL_LIST
#define SSRSWITCHER_SIGNAL_LIST "SSRSwitcherSignalTest.h"
#endif // SSRSWITCHER_SIGNAL_LIST
#include SSRSWITCHER_SIGNAL_LIST

#define SSRSwitcherId(Name, SignalIdActor, SignalIdSwitch, inverted) Name,
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
    bool inverted;
};
#define SSRSwitcherId(Name, SignalIdActor, SignalIdSwitch, inverted) \
    {SignalIdActor, SignalIdSwitch, inverted},
SSRSwitcherIdData SSRSwitcherIds[] = {SSRSwitcherIdList};
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
#define SSRSwitcherSwitch(SSRSwitcherId, SignalIdSwitch, ActiveTime, HoldTime, Shunt, CompareType, MaxOff, MinOff, MaxOn, MinOn) \
    {SSRSwitcherId, SignalIdSwitch, ActiveTime, HoldTime, Shunt, {(Compare::LimitMode)Compare::CompareType, MaxOff, MaxOff, MinOff, MinOff}, {(Compare::LimitMode)Compare::CompareType, MaxOn, MaxOn, MinOn, MinOn}},
SSRSwitcherSwitchData SSRSwitcherSwitchs[] = {SSRSwitcherSwitchList};
#undef SSRSwitcherSwitch

class SSRSwitcherHandler : public Executable
{
private:
public:
    SSRSwitcherHandler(/* args */);
    ~SSRSwitcherHandler();
    void exec();
    bool input[sizeof(SSRSwitcherSwitchs) / sizeof(SSRSwitcherSwitchData)];
};
static SSRSwitcherHandler *SSRSwitcherTask = new SSRSwitcherHandler();

class SSRSwitcherTimeHandler : public Executable
{
private:
    SSRSwitcherId SSR;
    SSRSwitcher::OutputStatus outputStatus;
    unsigned int taskId;

public:
    SSRSwitcherTimeHandler(SSRSwitcherId Id);
    ~SSRSwitcherTimeHandler();
    void init();
    void exec();
    void setStatus(SSRSwitcher::OutputStatus newStatus);
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
        if (Signals::GetDigitalValue(SSRSwitcherIds[i].SignalIdSwitch))
        {
            bool testing = false;
            for (size_t j = 0; j < sizeof(SSRSwitcherSwitchs) / sizeof(SSRSwitcherSwitchData); j++)
            {
                testing = testing || !Signals::GetDigitalValue(SSRSwitcherSwitchs[j].Input);
            }
            if (!testing == (SSRSwitcherTimeTask[i]->getStatus() == SSRSwitcher::open))
            {
                if (testing)
                {
                    SSRSwitcherTimeTask[i]->setStatus(SSRSwitcher::newStatus);
                    // SSRSwitcherHandler::running(i);
                }
                else
                {
                    SSRSwitcherTimeTask[i]->setStatus(SSRSwitcher::open);
                    // Signals::SetDigitalValue(SSRSwitcherIds[i].SignalIdActor, !SSRSwitcherIds[i].inverted);
                }
            }
        }
        else
        {
            Signals::SetDigitalValue(SSRSwitcherIds[i].SignalIdActor, SSRSwitcherIds[i].inverted);
        }
    }
}

SSRSwitcherTimeHandler::SSRSwitcherTimeHandler(SSRSwitcherId Id)
{
    SSR = Id;
    SSRSwitcherTimeTask[Id] = this;
    outputStatus = SSRSwitcher::open;
    taskId = taskManager.execute(SSRSwitcherTimeTask[SSR]);
}

SSRSwitcherTimeHandler::~SSRSwitcherTimeHandler()
{
}
void SSRSwitcherTimeHandler::exec()
{
    for (size_t i = 0; i < sizeof(SSRSwitcherSwitchs) / sizeof(SSRSwitcherSwitchData); i++)
    {
        if (SSR == SSRSwitcherSwitchs[i].SSR)
        {
            Compare::compare_result compare_result;
            bool thisTrigger;
            switch (outputStatus)
            {
            case SSRSwitcher::newStatus:
                outputStatus = SSRSwitcher::waiting;
                taskId = taskManager.scheduleOnce(SSRSwitcherSwitchs[i].HoldTime, SSRSwitcherTimeTask[SSR]);
                break;
            case SSRSwitcher::waiting:
                compare_result = Compare::calc<float>(Signals::GetAnalogValue(SSRSwitcherSwitchs[i].shunt), SSRSwitcherSwitchs[i].shuntOffLimit);
                switch (SSRSwitcherSwitchs[i].shuntOffLimit.mode)
                {
                case Compare::MaxCompare:
                    if (compare_result.max.trigger)
                        thisTrigger = true;
                    break;
                case Compare::MinCompare:
                    if (compare_result.min.trigger)
                        thisTrigger = true;
                    break;
                case Compare::AllCompare:
                    if (compare_result.min.trigger || compare_result.max.trigger)
                        thisTrigger = true;
                    break;

                default:
                    thisTrigger = false;
                    break;
                }
                if (thisTrigger)
                {
                    outputStatus = SSRSwitcher::testing;
                    Signals::SetDigitalValue(SSRSwitcherIds[SSR].SignalIdActor, !SSRSwitcherIds[SSR].inverted);
                    taskId = taskManager.scheduleOnce(SSRSwitcherSwitchs[i].ActiveTime, SSRSwitcherTimeTask[SSR]);
                }
                else
                {
                    taskId = taskManager.scheduleOnce(SSRSwitcherSwitchs[i].HoldTime, SSRSwitcherTimeTask[SSR]);
                }
                break;
            case SSRSwitcher::testing:
                compare_result = Compare::calc<float>(Signals::GetAnalogValue(SSRSwitcherSwitchs[i].shunt), SSRSwitcherSwitchs[i].shuntOnLimit);
                switch (SSRSwitcherSwitchs[SSR].shuntOffLimit.mode)
                {
                case Compare::MaxCompare:
                    if (compare_result.max.trigger)
                        thisTrigger = true;
                    break;
                case Compare::MinCompare:
                    if (compare_result.min.trigger)
                        thisTrigger = true;
                    break;
                case Compare::AllCompare:
                    if (compare_result.min.trigger || compare_result.max.trigger)
                        thisTrigger = true;
                    break;

                default:
                    thisTrigger = false;
                    break;
                }
                if (thisTrigger)
                {
                    taskId = taskManager.scheduleOnce(SSRSwitcherSwitchs[i].HoldTime, SSRSwitcherTimeTask[SSR]);
                }
                else
                {
                    outputStatus = SSRSwitcher::waiting;
                    Signals::SetDigitalValue(SSRSwitcherIds[SSR].SignalIdActor, SSRSwitcherIds[SSR].inverted);
                    taskId = taskManager.scheduleOnce(SSRSwitcherSwitchs[i].HoldTime, SSRSwitcherTimeTask[SSR]);
                }
                break;
            case SSRSwitcher::open:
                if (Signals::GetDigitalValue(SSRSwitcherIds[SSR].SignalIdSwitch))
                {
                    Signals::SetDigitalValue(SSRSwitcherIds[SSR].SignalIdActor, !SSRSwitcherIds[SSR].inverted);
                }
                else
                {
                    Signals::SetDigitalValue(SSRSwitcherIds[SSR].SignalIdActor, SSRSwitcherIds[SSR].inverted);
                }

                break;
            default:
                break;
            }
        }
    }
}
void SSRSwitcherTimeHandler::setStatus(SSRSwitcher::OutputStatus newStatus)
{
    taskManager.cancelTask(taskId);
    outputStatus = newStatus;
    taskId = taskManager.execute(SSRSwitcherTimeTask[SSR]);
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