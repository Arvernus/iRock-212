/**
 * @file BatShutOffTriggersTest.h
 * @author Joscha Wagner (joscha@nebensound.com)
 * @brief defines the Signals and limits used
 *
 * Copyright (c) Nebensound GmbH 2021
 *
 */

/**
 * @brief list of all sorts off shutoff possible
 *
 * @param Name name of the shutoff type
 */
// clang-format off
//                 Name     Warning
#define BatShutOffTypeList \
    BatShutOffType(Final,   FINAL) \
    BatShutOffType(Charge,  CHANGE) \
    BatShutOffType(Load,    LOAD) \
    BatShutOffType(Load_Sw, LOAD_SW)
// clang-format on

/**
 * @brief list of all signals and there max and mins that will trigger shut off
 *
 * @param SignalID signal id of the Signal
 * @param ShutOffType defines the type of shut off
 * @param Mode  0 = no comparison
 *              1 = min
 *              2 = max
 *              3 = min and max
 * @param Max if the value of the signal is bigger than Max shut off will trigger
 * @param Release if the value of the signal is smaller than Release shut off will return to default
 */
// clang-format off
//                   ID         Type    Mode        Min     Min_Release Max     Max_Release
#define BatShutOffTriggerList \
    BatShutOffTrigger(MP_C5,     Charge, MaxCompare, 0,      0,          3.9,    3.65) \
    BatShutOffTrigger(MP_C6,     Charge, MaxCompare, 0,      0,          3.9,    3.65) \
    BatShutOffTrigger(MP_C7,     Charge, MaxCompare, 0,      0,          3.9,    3.65) \
    BatShutOffTrigger(MP_C8,     Charge, MaxCompare, 0,      0,          3.9,    3.65)
// clang-format on

/**
 * @brief list of all signals that will change on trigger
 * @param SignalID signal id of the Signal
 * @param ShutOffType defines the type of shut off
 * @param inverted is signal inverted
 */
// clang-format off
//                  ID              Type        inverted
#define BatShutOffActorList \
    BatShutOffActor(C_discon,       Charge,     false) \
    BatShutOffActor(L_discon,       Final,      false) \
    BatShutOffActor(C_discon,       Final,      false) \
    BatShutOffActor(Alarm,          Final,      false) \
    BatShutOffActor(BU_C5,          Final,      true) \
    BatShutOffActor(BU_C6,          Final,      true) \
    BatShutOffActor(BU_C7,          Final,      true) \
    BatShutOffActor(BU_C8,          Final,      true) \
    BatShutOffActor(L_discon,       Load,       true)
// clang-format on