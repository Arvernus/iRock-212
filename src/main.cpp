#include "main.h"
#include <Arduino.h>
#include <TaskManager.h>
#include <MappingIO.h>
#include <CLI.h>
#include <BatShutoff.h>
#include <Balancer.h>
#include <SSRSwitcher.h>

#if defined(ARDUINO_IROCK_212_V1_0)
HardwareSerial Serial2(USART2);
#endif

#if defined(ARDUINO_IROCK_212_V1_1)
HardwareSerial Serial2(USART2);
#endif

void blink()
{
  unsigned int time = 1000;
  if (Signals::GetDigitalValue(Status_FinalSO))
    time = 100;
  Signals::SetDigitalValue(LED3, !Signals::GetDigitalValue(LED3));
  taskManager.scheduleOnce(time, blink);
}

void setup()
{
  Cli::setup(115200, true, true, true, true);
  Signals::Init();
  // ModBus::setup();
  blink();
  String greet;
  greet = "### Welcome to iRock ###\nYou are running, iRock OS ";
#define stringer(s) #s
#define str(s) stringer(s)
  greet = greet + str(SW_VERSION);
  greet = greet + " on your iRock 212 ";
  greet = greet + str(HW_VERSION);
#undef str
#undef stringer
  greet = greet + " in Mapping-Mode ";
  greet = greet + Mapping::ActualMap();
  Cli::start(greet);
  taskManager.yieldForMicros(5 * 1000 * 1000);
  SSRSwitcher::setup(100);
  BatShutOff::setup(1000);
  Balancer::setup(10000, 3, 2000);
}

void loop()
{
  taskManager.runLoop();
}