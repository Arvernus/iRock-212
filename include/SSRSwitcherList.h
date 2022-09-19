/**
 * @file SSRSwitcherSignalTest.h
 * @author Joscha Wagner (joscha@nebensound.com)
 * @brief defines the Signals and limits used
 *
 * Copyright (c) Nebensound GmbH 2022
 *
 */

/**
 * @brief list of all SSRs
 *
 * @param Name name of the SSR
 */
// clang-format off
//                Name      SignalIdActor   SignalIdSwitch  inverted
#define SSRSwitcherIdList \
    SSRSwitcherId(SSR1,     SSR_Gate,       SSR_Switch,     false)
// clang-format on

// clang-format off
//                    SSRSwitcherId SignalIdSwitch  ActiveTime  HoldTime    Shunt       CompareType MaxOff  MinOff  MaxOn   MinOn
#define SSRSwitcherSwitchList \
    SSRSwitcherSwitch(SSR1,         SSR_Switch_Ovp, 10000,      2000,       AD_Shunt,   MinCompare, -1,     -1,     -0.01,  -0.01) \
    SSRSwitcherSwitch(SSR1,         SSR_Switch_Lvp, 10000,      2000,       AD_Shunt,   MaxCompare, 1,      1,      0.01,   0.01)
// clang-format on