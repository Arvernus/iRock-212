#include "main.h"
#include <Arduino.h>
#include <TaskManager.h>
#include <MappingIO.h>
#include <CLI.h>
#include <BatShutoff.h>
#include <Balancer.h>

void blink()
{
  unsigned int time = 1000;
  if (Signals::GetDigitalValue(Status_FinalSO))
    time = 100;
  Signals::SetDigitalValue(LED3, !Signals::GetDigitalValue(LED3));
  taskManager.scheduleOnce(time, blink);
}

void driveSSR()
{
  /* if (Signals::GetDigitalValue(Status_FinalSO) || Signals::GetDigitalValue(Status_OCP))
  {
    Signals::SetDigitalValue(SSR_Gate, false);
  }
  else if (!Signals::GetDigitalValue(Status_LVP) && !Signals::GetDigitalValue(Status_LVP))
  {
    Signals::SetDigitalValue(SSR_Gate, true);
  }
  // else if ()
  //{
  // }

  else if (Signals::GetAnalogValue(AD_Shunt) > 100)
  {
    if (Signals::GetDigitalValue(Status_LVP))
      Signals::SetDigitalValue(SSR_Gate, true);
    if (Signals::GetDigitalValue(Status_OVP))
      Signals::SetDigitalValue(SSR_Gate, false);
  }
  else if (Signals::GetAnalogValue(AD_Shunt) < 100)
  {
    if (Signals::GetDigitalValue(Status_LVP))
      Signals::SetDigitalValue(SSR_Gate, false);
    if (Signals::GetDigitalValue(Status_OVP))
      Signals::SetDigitalValue(SSR_Gate, true);
  } */
  taskManager.scheduleOnce(2000, driveSSR);
}

void debug()
{
  // String message = String(Signals::GetAnalogValue(AD_Shunt), 3);
  String message = String(Pins::ReadAnalog(PinV_GND), 3);
  //  String message = String(analogRead(PA2));
  Cli::printInfo(message);
  taskManager.scheduleOnce(1000, debug);
}

void setup()
{
  Cli::setup(115200, true, true, true, true);
  Signals::Init();
  // ModBus::setup();
  blink();
  String greet;
  greet = "### Welcome to iRock ###\nYou are running, iRock OS ";
#define str(s) #s
  greet = greet + F(str(SW_VERSION));
#undef str
  greet = greet + F(" on your iRock ");
#define str(s) #s
  greet = greet + F(str(HW_VERSION));
#undef str
  greet = greet + F(" in Mapping-Mode ");
  greet = greet + Mapping::ActualMap();
  Cli::start(greet);
  taskManager.yieldForMicros(5 * 1000 * 1000);
  BatShutOff::setup(1000);
  Balancer::setup(10000, 3, 2000);
  // debug();
  driveSSR();
}

void loop()
{
  taskManager.runLoop();
}