#include "main.h"
#include <Arduino.h>
#include <iRockIO.h>

bool mainStatus = true;
bool swLoadStatus = true;

void blink()
{
  Signals::SetDigitalValue(LED3, !Signals::GetDigitalValue(LED3));
  taskManager.scheduleOnce(500, blink);
}

void linkButtons()
{
  if (mainStatus != Signals::GetDigitalValue(Main_Button))
  {
    mainStatus = Signals::GetDigitalValue(Main_Button);
    Signals::SetDigitalValue(Main_Relay, mainStatus);
    Signals::SetDigitalValue(Main_On, mainStatus);
  }
  if (swLoadStatus != Signals::GetDigitalValue(L_sw_Button))
  {
    swLoadStatus = Signals::GetDigitalValue(L_sw_Button);
    Signals::SetDigitalValue(L_sw_discon, !swLoadStatus);
    Signals::SetDigitalValue(L_sw_On, swLoadStatus);
  }
}
void setup()
{
  Cli::setup(115200, true, true, true, true);
  Signals::Init();
  ModBus::setup();
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
  taskManager.scheduleFixedRate(100, linkButtons);
  taskManager.yieldForMicros(5 * 1000 * 1000);
  FinalShutOff::setup(1000);
  LoadShutOff::setup(1000);
  ChargeShutOff::setup(1000);
  Charging::setup(10000, 3, 2000);
}

void loop()
{
  taskManager.runLoop();
}