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
// #define SET_SERIAL_NUMBER 2512119

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
void calculateSoc()
{
  float voltage = Signals::GetAnalogValue(Signals::SignalId::Bat_Voltage) / float(NUMBER_OF_CELLS);

  float Soc;

  if (voltage < 3.25)
  {
    Soc = 0.0;
  }
  else if (voltage > 3.4)
  {
    Soc = 100.0;
  }
  else
  {
    Soc = ((voltage - 3.25) / 0.15) * 100;
  }
  Signals::SetAnalogValue(Signals::SignalId::Bat_SoC, Soc);
}
void calculateBatteryVoltage()
{
  float voltage = 0;
  voltage = voltage + Signals::GetAnalogValue(Signals::SignalId::AD_C1);
  voltage = voltage + Signals::GetAnalogValue(Signals::SignalId::AD_C2);
  voltage = voltage + Signals::GetAnalogValue(Signals::SignalId::AD_C3);
  voltage = voltage + Signals::GetAnalogValue(Signals::SignalId::AD_C4);
  Signals::SetAnalogValue(Signals::SignalId::Bat_Voltage, voltage);
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
    char newHardwareVersion[16] = str(HW_VERSION);
    Store::forbidden_write("HW_V", newHardwareVersion, true);
#ifdef SET_SERIAL_NUMBER
    char initSerialNumber[8] = str(SET_SERIAL_NUMBER);
    Store::forbidden_write("SN", initSerialNumber);
#endif // SET_SERIAL_NUMBER
    char newHardwareName[16] = "iRock 212";
    Store::forbidden_write("HW_N", newHardwareName, true);
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
  Store::read("HW_V", HardwareVersion);
  Store::read("HW_N", HardwareName);
  char SerialNumber[8];
  Store::read(SerialNumber, "SN");
  float capacity;
  Store::read("Cap", capacity);
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
  greet = greet + "\nCapacity: ";
  greet = greet + capacity;
  Cli::start(greet);
  taskManager.yieldForMicros(5 * 1000 * 1000);
  SSRSwitcher::setup(500);
  BatShutoff::setup(1000);
  Balancer::setup(10000, 4, 2000, Balancer::Single);
  taskManager.scheduleFixedRate(1000, calculateBatteryVoltage);
  taskManager.scheduleFixedRate(1000, calculateSoc);
}

void loop()
{
  taskManager.runLoop();
}
