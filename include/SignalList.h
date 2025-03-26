/**
 * @file SignalList.h
 * @author Joscha Wagner (joscha@nebensound.com)
 * @brief Definition of all Signals for iRock V2
 *
 * Copyright (c) Nebensound GmbH 2021
 */

/*
* A signal is defined by the following parameters:
*
*	* SignalId	      Id of the Signal an enum (e.g. VREF_INT) which is the index
*                   into the SignalDefintion_Table
*	* Type			      Type of the Signal. One of the following values:
*					            * AnalogInput
*					            * AnalogOutput
*                     * DifferentialInput
*						          * DigitalInput
*						          * DigitalOutput
*						          * Switch
*                     * Button
*                     * MappingVariant
*	* Unit			      Name of the Unit measured (e.g. "A" for Ampere)
* * Gain            Factor to multiply the Analog Value with
*	* Offset          Offset to add to the Analog Value
*	* InitValue       Value at boot time (for digital Pins only 0 and 1 is allowed)
+ * Smooth          The level of smoothing of Analog Input Signals. Higher values
*                   reduce the smoothing, lower values increase it.
*                   A typical value is 5 or 10. 100 means no smoothing.
* * Interval        Defining the interval in milliseconds the Input Pin of a Signal
*                   are polled for new values. An interval of 0 means no polling
*                   and negative interval is interpreted as milliseconds polling
*                   but using interrupts if possible.
*	* Calibration	    Defines if the Signal needs calibration (true/false) can only
*					          be set for analog Signals
* * Generic         Defines if a Signal is a Generic Signal and allows Pins to be
*                   added to it at run-time. Only Output Signals allow dynamic
*                   addition of Pins at run-time. For other Signals the attribute
*                   is ignored and should be set to false.
* * ModbusRegister  Modbus Register address for the Signal
*	* Description 	  Description of the Signal
*
* Please define here the list of all Signals
*/
// clang-format off
#if defined(HW_VERSION_2_4) || defined(HW_VERSION_1_11)
//       SignalName             SignalType            Unit  Gain    Offset    Init  Smooth  Interval  Cal     Generic ModbusRegister          Description
#define SignalList \
  Signal(MapVar,                MappingVariant,       "",   1.0,    0.0,      0,    10,     0,        false,  false,  NoRegister,             "Variant of the Mapping Table to use") \
  Signal(CPU_TEMP,              CpuTemp,              "C",  1.0,    0.0,      0,    10,     1000,     true,   false,  Temperature_Sensor_1,   "Temperature within the CPU") \
  Signal(VREF_INT,              AnalogIntInput,       "V",  1.0,    0.0,      0,    10,     1000,     false,  false,  NoRegister,             "Electric potential of the constant voltage source within the processor") \
  Signal(AD_Shunt,              AnalogDiffInput,      "A",  1.0,    0.0,      0,    10,     10,       true,   false,  NoRegister,             "Sum of the current running in or out of the battery") \
  Signal(AD_Shunt_FB,           AnalogDiffInput,      "A",  1.0,    0.0,      0,    10,     10,       true,   false,  Feedback_Shunt_Current, "Shunt in the Feedback line") \
  Signal(Shunt,                 DigitalInput,         "",   1.0,    0.0,      0,    10,     10,       false,  false,  NoRegister,             "Status of charging") \
  Signal(AD_VGnd,               AnalogInput,          "V",  1.0,    0.0,      0,    10,     10,       true,   false,  NoRegister,             "Electric potential of virtual ground") \
  Signal(BU_C1,                 DigitalOutput,        "",   1.0,    0.0,      0,    10,     200,      false,  false,  Cell_1_Balance_Status,  "Output for balancing unit 1 - True means unit is working") \
  Signal(BU_C2,                 DigitalOutput,        "",   1.0,    0.0,      0,    10,     200,      false,  false,  Cell_2_Balance_Status,  "Output for balancing unit 2 - True means unit is working") \
  Signal(BU_C3,                 DigitalOutput,        "",   1.0,    0.0,      0,    10,     200,      false,  false,  Cell_3_Balance_Status,  "Output for balancing unit 3 - True means unit is working") \
  Signal(BU_C4,                 DigitalOutput,        "",   1.0,    0.0,      0,    10,     200,      false,  false,  Cell_4_Balance_Status,  "Output for balancing unit 4 - True means unit is working") \
  Signal(AD_C1,                 AnalogInput,          "V",  1.0,    0.0,      0,    3,      10,       true,   false,  Cell_1_Voltage,         "Electric potential of the battery cell 1") \
  Signal(AD_C2,                 AnalogInput,          "V",  1.0,    0.0,      0,    3,      10,       true,   false,  Cell_2_Voltage,         "Electric potential of the battery cell 2") \
  Signal(AD_C3,                 AnalogInput,          "V",  1.0,    0.0,      0,    3,      10,       true,   false,  Cell_3_Voltage,         "Electric potential of the battery cell 3") \
  Signal(AD_C4,                 AnalogInput,          "V",  1.0,    0.0,      0,    3,      10,       true,   false,  Cell_4_Voltage,         "Electric potential of the battery cell 4") \
  Signal(LED1,                  DigitalOutput,        "",   1.0,    0.0,      1,    10,     0,        false,  false,  NoRegister,             "Status LED 1 on PCB") \
  Signal(LED2,                  DigitalOutput,        "",   1.0,    0.0,      1,    10,     0,        false,  false,  NoRegister,             "Status LED 2 on PCB") \
  Signal(LED3,                  DigitalOutput,        "",   1.0,    0.0,      1,    10,     0,        false,  false,  NoRegister,             "Status LED 3 on PCB") \
  Signal(Status_OVP,            DigitalOutput,        "",   1.0,    0.0,      0,    10,     0,        false,  false,  NoRegister,             "Status of the Over Voltage Protection") \
  Signal(Status_LVP,            DigitalOutput,        "",   1.0,    0.0,      0,    10,     0,        false,  false,  NoRegister,             "Status of the Low Voltage Protection") \
  Signal(Status_FinalSO,        VirtualDigitalOutput, "",   1.0,    0.0,      0,    10,     0,        false,  false,  NoRegister,             "Status of the Final Shut Off") \
  Signal(Status_OCP,            VirtualDigitalOutput, "",   1.0,    0.0,      0,    10,     0,        false,  false,  NoRegister,             "Status of the Over Current Protection") \
  Signal(Alarm,                 VirtualDigitalOutput, "",   1.0,    0.0,      0,    10,     0,        false,  false,  NoRegister,             "Alarm Signal") \
  Signal(SSR_Gate,              DigitalOutput,        "",   1.0,    0.0,      0,    10,     0,        false,  false,  NoRegister,             "Drives SSR") \
  Signal(SSR_Switch,            VirtualDigitalOutput, "",   1.0,    0.0,      1,    10,     0,        false,  false,  NoRegister,             "Drives SSR engine") \
  Signal(SSR_Switch_Ovp,        VirtualDigitalOutput, "",   1.0,    0.0,      1,    10,     0,        false,  false,  NoRegister,             "Drives SSR engine") \
  Signal(SSR_Switch_Lvp,        VirtualDigitalOutput, "",   1.0,    0.0,      1,    10,     0,        false,  false,  NoRegister,             "Drives SSR engine") \
  Signal(SSR_Sense,             DigitalInput,         "",   1.0,    0.0,      0,    10,     200,      false,  false,  NoRegister,             "Senses SSR") \
  Signal(PSU_Gate,              DigitalOutput,        "",   1.0,    0.0,      1,    10,     200,      false,  false,  NoRegister,             "Driver PSU") \
  Signal(Powersafe,             DigitalOutput,        "",   1.0,    0.0,      0,    10,     200,      false,  false,  NoRegister,             "Turn on Powersafe") \
  Signal(VEBus_Current,         VEDirectInput,        "A",  0.001,  0.0,      0,    1000,   1000,     false,  false,  NoRegister,             "Current read from the VE smart Shunt") \
  Signal(Bat_Voltage,           AnalogInput,          "V",  1.0,    0.0,      0,    1000,   1000,     false,  false,  Battery_Voltage,        "Sum Voltage of the Battery") \
  Signal(Bat_Current,           AnalogInput,          "A",  1.0,    0.0,      0,    1000,   1000,     false,  false,  Battery_Current,        "Sum Current of the Battery") \
  Signal(Bat_SoC,               AnalogInput,          "%",  1.0,    0.0,      0,    1000,   1000,     false,  false,  Battery_SOC,            "State of Charge of the Battery") \
  Signal(Remaining_Cap,         AnalogInput,          "Ah", 1.0,    0.0,      0,    1000,   1000,     false,  false,  Remaining_Capacity,     "Remaining Capacity of the Battery") \
  Signal(Max_Ch_Cur,            AnalogInput,          "A",  1.0,    0.0,      0,    1000,   1000,     false,  false,  Max_Charge_Current,     "Maximum Charge Current of the Battery") \
  Signal(Max_Disch_Cur,         AnalogInput,          "A",  1.0,    0.0,      0,    1000,   1000,     false,  false,  Max_Discharge_Current,  "Maximum Discharge Current of the Battery") \
  Signal(Max_Bat_Vol,           AnalogInput,          "V",  1.0,    0.0,      0,    1000,   1000,     false,  false,  Max_Cell_Voltage,    "Maximum Voltage of the Battery") \
  Signal(Min_Bat_Vol,           AnalogInput,          "V",  1.0,    0.0,      0,    1000,   1000,     false,  false,  Min_Cell_Voltage,    "Minimum Voltage of the Battery")
#else
//       SignalName             SignalType            Unit  Gain    Offset    Init  Smooth  Interval  Cal     Generic Description
#define SignalList \
  Signal(MapVar,                MappingVariant,       "",   1.0,    0.0,      0,    10,     0,        false,  false,  "Variant of the Mapping Table to use") \
  Signal(CPU_TEMP,              CpuTemp,              "C",  1.0,    0.0,      0,    10,     1000,     true,   false,  "Temperature within the CPU") \
  Signal(VREF_INT,              AnalogIntInput,       "V",  1.0,    0.0,      0,    10,     1000,     false,  false,  "Electric potential of the constant voltage source within the processor") \
  Signal(AD_Shunt,              AnalogDiffInput,      "A",  1.0,    0.0,      0,    10,     10,       true,   false,  "Sum of the current running in or out of the battery") \
  Signal(AD_Shunt_FB,           AnalogDiffInput,      "A",  1.0,    0.0,      0,    10,     10,       true,   false,  "Shunt in the Feedback line") \
  Signal(Shunt,                 DigitalInput,         "",   1.0,    0.0,      0,    10,     10,       false,  false,  "Status of charging") \
  Signal(AD_VGnd,               AnalogInput,          "V",  1.0,    0.0,      0,    10,     10,       true,   false,  "Electric potential of virtual ground") \
  Signal(BU_C1,                 DigitalOutput,        "",   1.0,    0.0,      0,    10,     200,      false,  false,  "Output for balancing unit 1 - True means unit is working") \
  Signal(BU_C2,                 DigitalOutput,        "",   1.0,    0.0,      0,    10,     200,      false,  false,  "Output for balancing unit 2 - True means unit is working") \
  Signal(BU_C3,                 DigitalOutput,        "",   1.0,    0.0,      0,    10,     200,      false,  false,  "Output for balancing unit 3 - True means unit is working") \
  Signal(BU_C4,                 DigitalOutput,        "",   1.0,    0.0,      0,    10,     200,      false,  false,  "Output for balancing unit 4 - True means unit is working") \
  Signal(AD_C1,                 AnalogInput,          "V",  1.0,    0.0,      0,    3,      10,       true,   false,  "Electric potential of the battery cell 1") \
  Signal(AD_C2,                 AnalogInput,          "V",  1.0,    0.0,      0,    3,      10,       true,   false,  "Electric potential of the battery cell 2") \
  Signal(AD_C3,                 AnalogInput,          "V",  1.0,    0.0,      0,    3,      10,       true,   false,  "Electric potential of the battery cell 3") \
  Signal(AD_C4,                 AnalogInput,          "V",  1.0,    0.0,      0,    3,      10,       true,   false,  "Electric potential of the battery cell 4") \
  Signal(LED1,                  DigitalOutput,        "",   1.0,    0.0,      1,    10,     0,        false,  false,  "Status LED 1 on PCB") \
  Signal(LED2,                  DigitalOutput,        "",   1.0,    0.0,      1,    10,     0,        false,  false,  "Status LED 2 on PCB") \
  Signal(LED3,                  DigitalOutput,        "",   1.0,    0.0,      1,    10,     0,        false,  false,  "Status LED 3 on PCB") \
  Signal(Status_OVP,            DigitalOutput,        "",   1.0,    0.0,      0,    10,     0,        false,  false,  "Status of the Over Voltage Protection") \
  Signal(Status_LVP,            DigitalOutput,        "",   1.0,    0.0,      0,    10,     0,        false,  false,  "Status of the Low Voltage Protection") \
  Signal(Status_FinalSO,        VirtualDigitalOutput, "",   1.0,    0.0,      0,    10,     0,        false,  false,  "Status of the Final Shut Off") \
  Signal(Status_OCP,            VirtualDigitalOutput, "",   1.0,    0.0,      0,    10,     0,        false,  false,  "Status of the Over Current Protection") \
  Signal(Alarm,                 VirtualDigitalOutput, "",   1.0,    0.0,      0,    10,     0,        false,  false,  "Alarm Signal") \
  Signal(SSR_Gate,              DigitalOutput,        "",   1.0,    0.0,      0,    10,     0,        false,  false,  "Drives SSR") \
  Signal(SSR_Switch,            VirtualDigitalOutput, "",   1.0,    0.0,      1,    10,     0,        false,  false,  "Drives SSR engine") \
  Signal(SSR_Switch_Ovp,        VirtualDigitalOutput, "",   1.0,    0.0,      1,    10,     0,        false,  false,  "Drives SSR engine") \
  Signal(SSR_Switch_Lvp,        VirtualDigitalOutput, "",   1.0,    0.0,      1,    10,     0,        false,  false,  "Drives SSR engine") \
  Signal(SSR_Sense,             DigitalInput,         "",   1.0,    0.0,      0,    10,     200,      false,  false,  "Senses SSR") \
  Signal(PSU_Gate,              DigitalOutput,        "",   1.0,    0.0,      1,    10,     200,      false,  false,  "Driver PSU") \
  Signal(Powersafe,             DigitalOutput,        "",   1.0,    0.0,      0,    10,     200,      false,  false,  "Turn on Powersafe") \
  Signal(Bat_Current,           VEDirectInput,        "A",  1.0,    0.0,      0,    1000,   1000,     false,  false,  "Sum Current of the Battery")
#endif // HW_VERSION_2_4 || HW_VERSION_1_11
// clang-format on