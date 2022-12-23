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
 * @param SignalIdActor Signal that should be switched
 * @param SignalIdSwitch Signal (virtual digital input) that sores the current value
 * @param inverted is the SignalIdSwitch inverted?
 */
// clang-format off
//                Name      SignalIdActor   SignalIdSwitch
#define SSRSwitcherIdList \
    SSRSwitcherId(SSR1,     SSR_Gate,       SSR_Switch)
// clang-format on

/**
 * @brief list of all signals (switches) that will switch any given SSR INFO: two states at one time are not yet defined
 *
 * @param SSRSwitcherId SSR the Switch belongs to
 * @param SignalIdSwitch input signal
 * @param ActiveTime time the SSR stays active when status is testing
 * @param HoldTime time the SSR stays active when status is waiting
 * @param Shunt condition that needs to be met to
 * @param CompareType only MinCompare and MaxCompare should be used
 * @param MinMaxOff depending on CompareType the minimum or maximum value the Shunt can have to stay in status waiting
 * @param ReleaseOff depending on CompareType the minimum or maximum value the Shunt can have to end status waiting
 * @param MinMaxOn depending on CompareType the minimum or maximum value the Shunt can have to stay in status testing
 * @param ReleaseOn depending on CompareType the minimum or maximum value the Shunt can have to end status testing
 *
 */
// clang-format off
//                    SSRSwitcherId SignalIdSwitch  ActiveTime  HoldTime    Shunt       CompareType MinMaxOff   ReleaseOff  MinMaxOn    ReleaseOn
#define SSRSwitcherSwitchList \
    SSRSwitcherSwitch(SSR1,         SSR_Switch_Ovp, 10000,      2000,       AD_Shunt,   MinCompare, -1,         -1,         -0.01,      -0.01) \
    SSRSwitcherSwitch(SSR1,         SSR_Switch_Lvp, 10000,      2000,       AD_Shunt,   MaxCompare, 1,          1,          0.01,       0.01)
// clang-format on