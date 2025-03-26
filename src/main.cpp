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
    char HardwareVersion[16] = str(HW_VERSION);
    Store::forbidden_write("HW_V", HardwareVersion, true);
#ifdef SET_SERIAL_NUMBER
    char SerialNumber[8] = str(SET_SERIAL_NUMBER);
    Store::forbidden_write("SN", SerialNumber, true);
#endif // SET_SERIAL_NUMBER
    char HardwareName[16] = "iRock 212";
    Store::forbidden_write("HW_N", HardwareName, true);
  }
  char SoftwareVersion[16] = str(SW_VERSION);
#undef DEVELOPERVERSION
#undef str
#undef stringer
  String greet;
  char HardwareVersion[16];
  Store::read(HardwareVersion, "HW_V");
  char HardwareName[16];
  Store::read(HardwareName, "HW_N");
  char SerialNumber[8];
  Store::read(SerialNumber, "SN");
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
  ModbusToWorld::setup(1, 9600, 100);
  taskManager.yieldForMicros(5 * 1000 * 1000);
  SSRSwitcher::setup(500);
  BatShutoff::setup(1000);
  Balancer::setup(10000, 4, 2000, Balancer::Single);
}

void loop()
{
  taskManager.runLoop();
}
