/**
 * @file MappingListTest.h
 * @author Joscha Wagner (joscha@nebensound.com)
 * @brief Definition of Mappings of Pins to Signals for unit tests
 *
 * Copyright (c) Nebensound GmbH 2021
 */

/*
 * A Mapping of a Pin to a Signal is defined:
 *
 *   * List          Number of the list ot add the entry to:
 *                       * 0: Base List
 *                       * 1-<MaxVariants> Variant x
 *   * Signal        The Signal the Pin will be assigned to
 *   * Pin           The Pin to assign to the Signal
 *
 * Please define here the list of all Mappings
 */
// clang-format off
#define MappingList \
    MapPin(0,   MapVar,         PinDip1) \
    MapPin(0,   MapVar,         PinDip2) \
    MapPin(0,   MapVar,         PinDip3) \
    MapPin(0,   AD_Shunt,       PinShunt) \
    MapPin(0,   AD_VGnd,        PinV_GND) \
    MapPin(0,   BU_C5,          PinBU_C5) \
    MapPin(0,   BU_C6,          PinBU_C6) \
    MapPin(0,   BU_C7,          PinBU_C7) \
    MapPin(0,   BU_C8,          PinBU_C8) \
    MapPin(0,   MP_C5,          PinAD_C5) \
    MapPin(0,   MP_C6,          PinAD_C6) \
    MapPin(0,   MP_C7,          PinAD_C7) \
    MapPin(0,   MP_C8,          PinAD_C8) \
    MapPin(0,   LED1,           PinLED1) \
    MapPin(0,   LED2,           PinLED2) \
    MapPin(0,   LED3,           PinLED3) \
    MapPin(0,   C_discon,       PinC_discon) \
    MapPin(0,   L_discon,       PinL_discon)
// clang-format on
