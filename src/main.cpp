#include "main.h"
#include <Arduino.h>
#include <TaskManager.h>
#include <MappingIO.h>
#include <CLI.h>
#include <BatShutoff.h>
#include <Balancer.h>

bool mainStatus = true;
bool swLoadStatus = true;

void blink()
{
  Signals::SetDigitalValue(LED3, !Signals::GetDigitalValue(LED3));
  taskManager.scheduleOnce(500, blink);
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
}

void loop()
{
  taskManager.runLoop();
}