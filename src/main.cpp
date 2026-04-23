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

// ============================================================================
// Flash-Zeit Konfiguration
// ----------------------------------------------------------------------------
// Die folgenden Defines dienen dazu, das Board einmalig zu initialisieren oder
// Stammdaten zu setzen. Nach dem Flashen mit aktivem Define sollte die Zeile
// wieder auskommentiert und neu geflasht werden, damit bei einem Neustart
// nicht jedes Mal das Dateisystem zurueckgesetzt bzw. die Werte ueberschrieben
// werden.
//
// Dateisystem komplett neu anlegen (loescht Seriennummer, Kapazitaet, ...):
//#define RESET_FILESYSTEM
//
// Seriennummer einmalig setzen (max. 8 Zeichen):
//#define SET_SERIAL_NUMBER 2617121
//
// Kapazitaet der Batterie in Ah einmalig setzen (float):
// (Max. Lade-/Entladestrom werden daraus automatisch als Cap/2 abgeleitet.)
//#define SET_CAPACITY 400.0f
// ============================================================================
// function to blink LED3

void blink()
{
  unsigned int time = 1000;
  if (Signals::GetDigitalValue(Status_FinalSO))
    time = 100;
  Signals::SetDigitalValue(LED3, !Signals::GetDigitalValue(LED3));
  taskManager.scheduleOnce(time, blink);
}

// function to calculate the total battery voltage
void calculateBatteryVoltage()
{
  float voltage = 0;
  voltage = voltage + Signals::GetAnalogValue(Signals::SignalId::AD_C1);
  voltage = voltage + Signals::GetAnalogValue(Signals::SignalId::AD_C2);
  voltage = voltage + Signals::GetAnalogValue(Signals::SignalId::AD_C3);
  voltage = voltage + Signals::GetAnalogValue(Signals::SignalId::AD_C4);
  Signals::SetAnalogValue(AD_C_All, voltage);
}
void calculateSoc()
{
  float voltage = Signals::GetAnalogValue(Signals::SignalId::AD_C_All) / float(NUMBER_OF_CELLS);

  float Soc;

  if (voltage < 2.8)
  {
    Soc = 0.0;
  }
  else if (voltage > 3.3)
  {
    Soc = 100.0;
  }
  else
  {
    Soc = ((voltage - 2.8) / 0.5) * 100;
  }
  Signals::SetAnalogValue(Signals::SignalId::Soc, Soc);
}
void setup()
{
  Store::setup();
  Cli::setup(115200, true, true, true, true);
#ifdef RESET_FILESYSTEM
  Store::reset(true);
#endif // RESET_FILESYSTEM
#ifdef SET_SERIAL_NUMBER
  // NOLINTBEGIN (cppcoreguidelines-macro-usage)
#define stringer_sn(s) #s
#define str_sn(s) stringer_sn(s)
  char newSerialNumber[8] = str_sn(SET_SERIAL_NUMBER);
#undef str_sn
#undef stringer_sn
  // NOLINTEND
  newSerialNumber[sizeof(newSerialNumber) - 1] = '\0';
  Store::forbidden_write("SN", newSerialNumber, true);
#endif // SET_SERIAL_NUMBER
#ifdef SET_CAPACITY
  float newCapacity = SET_CAPACITY;
  Store::forbidden_write("Cap", newCapacity, true);
#endif // SET_CAPACITY
  Signals::Init();
  blink();
  // NOLINTBEGIN (cppcoreguidelines-init-variables,cppcoreguidelines-macro-usage)
  String greet = "### Welcome to iRock ###\nYou are running, iRock OS ";
#define stringer(s) #s
#define str(s) stringer(s)
  greet = greet + str(SW_VERSION);
  char hwName[16] = "iRock 212";
  char hwVersion[16] = str(HW_VERSION);
#undef str
#undef stringer
  // NOLINTEND
  hwName[sizeof(hwName) - 1] = '\0';
  hwVersion[sizeof(hwVersion) - 1] = '\0';
  // Nur schreiben, wenn die Datei noch nicht existiert. Ein erneutes
  // forbidden_write(..., true) wuerde die Datei aufgrund eines Library-Bugs
  // (trash setzen, aber nicht neu schreiben) unbrauchbar machen.
  if (Store::fileExists("HW_V") != Store::Ok)
  {
    Store::forbidden_write("HW_V", hwVersion, false);
  }
  if (Store::fileExists("HW_N") != Store::Ok)
  {
    Store::forbidden_write("HW_N", hwName, false);
  }
  Store::read("HW_N", hwName);
  Store::read("HW_V", hwVersion);
  hwName[sizeof(hwName) - 1] = '\0';
  hwVersion[sizeof(hwVersion) - 1] = '\0';
  greet = greet + " on your ";
  greet = greet + hwName;
  greet = greet + " (V";
  greet = greet + hwVersion;
  greet = greet + ") in Mapping-Mode ";
  greet = greet + Mapping::ActualMap();
  char serialNumber[8] = {0};
  Store::ErrorCode error = Store::read("SN", serialNumber);
  serialNumber[sizeof(serialNumber) - 1] = '\0';
  switch (error)
  {
  case Store::Ok:
    greet = greet + "\nSerialnumber: " + serialNumber;
    break;
  case Store::FileSystemVersionNotSupported:
    Cli::printError("Storage Error: File System Version not supported");
    break;
  case Store::NoResetObjectFound:
    Cli::printError("Storage Error: File System is not initialized or corrupted");
    break;
  default:
    Cli::printError("Storage Error: Unknown Error (" + String(error) + ")");
    break;
  }
  float capacity = 0.0f;
  Store::read("Cap", capacity);
  greet = greet + "\nCapacity: " + capacity;
  greet = greet + "\nType 'help' for a list of commands";
  // ModbusToWorld::setup() wird bereits in Signals::Init() aufgerufen.
  // Ein zweiter Aufruf wuerde ueber ModbusRTUServer.begin() -> end() die
  // bereits konfigurierten Holding-Register-Mappings wieder loeschen und
  // fuehrte dadurch zu "illegal data address"-Antworten.
  taskManager.yieldForMicros(5000000);
  SSRSwitcher::setup(500);
  BatShutoff::setup(1000);
  Balancer::setup(10000, 4, 2000, Balancer::Single);
  taskManager.scheduleFixedRate(1000, calculateBatteryVoltage);
  taskManager.scheduleFixedRate(1000, calculateSoc);
  Cli::start(greet);
}

void loop()
{
  taskManager.runLoop();
}
