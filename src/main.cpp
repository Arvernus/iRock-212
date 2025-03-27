#include <Arduino.h>
#include "main.h"
#include <TaskManager.h>
#include <PersistentStorage.h>
#include <MappingIO.h>
#include <CLI.h>
#include <BatShutoff.h>
#include <Balancer.h>
#include <SSRSwitcher.h>
#ifdef ENABLE_MODBUS
#include <ModbusToWorld.h>
#endif // ENABLE_MODBUS

// Set Serialnumber
// #define SET_SERIAL_NUMBER 1234567

// Reset Filesystem
// #define RESET_FILESYSTEM

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
  blink();
  {
#define stringer(s) #s
#define str(s) stringer(s)
#define DEVELOPERVERSION Develop
#ifdef RESET_FILESYSTEM
    Store::reset(true);
#endif // RESET_FILESYSTEM
#ifdef SET_SERIAL_NUMBER
    char initSerialNumber[8] = str(SET_SERIAL_NUMBER);
    Store::forbidden_write("SN", initSerialNumber);
#endif // SET_SERIAL_NUMBER
  }
  char SoftwareVersion[16] = str(SW_VERSION);
  char HardwareVersion[sizeof(str(HW_VERSION))];
  char HardwareName[sizeof(str(HW_NAME))];
#undef DEVELOPERVERSION
#undef str
#undef stringer
  String greet;
  Store::read("HW_V", HardwareVersion);
  Store::read("HW_N", HardwareName);
  char SerialNumber[8];
  Store::read("SN", SerialNumber);
  greet = "### Welcome to iRock ###\nYou are running, iRock OS ";
  greet = greet + SoftwareVersion;
  greet = greet + " on your ";
  greet = greet + HardwareName;
  greet = greet + " (V";
  greet = greet + HardwareVersion;
  greet = greet + ") in Mapping-Mode ";
  greet = greet + Mapping::ActualMap();
  greet = greet + "\nSerialnumber: ";
  greet = greet + SerialNumber;

  Cli::start(greet);
  taskManager.yieldForMicros(5 * 1000 * 1000);
  SSRSwitcher::setup(500);
  BatShutoff::setup(1000);
  Balancer::setup(10000, 4, 2000, Balancer::Single);
}

void loop()
{
  taskManager.runLoop();
}
