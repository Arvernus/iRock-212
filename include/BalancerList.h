/**
 * @file BalancerSignalsTest.h
 * @author Joscha Wagner (joscha@nebensound.com)
 * @brief defines the Signals and limits used
 *
 * Copyright (c) Nebensound GmbH 2021
 *
 */

/**
 * @brief list of all signals and their max and mins that will trigger final shut off
 *
 * @param SignalID signal id of the Signal
 * @param SignalID_BU BU attached to current
 * @param min minimal offset to other cells to trigger
 * @param max maximal offset to other cells to trigger final shut off
 */
// clang-format off
//                 ID       BU      Mode        Min     Min_Release Max     Max_Release
#define BalancerSignalList \
    BalancerSignal(MP_C5,   BU_C5,  AllCompare, 0.003,  0.003,      1,      1) \
    BalancerSignal(MP_C6,   BU_C6,  AllCompare, 0.003,  0.003,      1,      1) \
    BalancerSignal(MP_C7,   BU_C7,  AllCompare, 0.003,  0.003,      1,      1) \
    BalancerSignal(MP_C8,   BU_C8,  AllCompare, 0.003,  0.003,      1,      1)
// clang-format on