/**
 * @file MappingList.h
 * @author Joscha Wagner (joscha@nebensound.com)
 * @brief Definition of Mapping of Pins to Signals (iRock v2_3)
 *
 * Copyright (c) Nebensound GmbH 2021
 */

/*
 * A Mapping of a Pin to a Signal is defined:
 *
 *   * List          Number of the list to add the entry to:
 *                       * 0: Base List
 *                       * 1-<MaxVariants> Variant x
 *   * Signal        The Signal the Pin will be assigned to
 *   * Pin           The Pin to assign to the Signal
 *
 * Please define here the list of all Mappings
 */

// clang-format off
#define MappingList \
    MapPin(0, MapVar, PinDip3) \
    MapPin(0, MapVar, PinDip2) \
    MapPin(0, MapVar, PinDip1) \
    MapPin(0, AD_Charge, PinAD_Charge) \
    MapPin(0, AD_Load, PinAD_Load) \
    MapPin(0, AD_Load_sw, PinAD_Load_sw) \
    MapPin(0, AD_Shunt, PinShunt) \
    MapPin(0, AD_Shunt, PinV_GND) \
    MapPin(0, BU_C1, PinBU_C1) \
    MapPin(0, BU_C2, PinBU_C2) \
    MapPin(0, BU_C3, PinBU_C3) \
    MapPin(0, BU_C4, PinBU_C4) \
    MapPin(0, MP_C1, PinMP_C1) \
    MapPin(0, MP_C2, PinMP_C2) \
    MapPin(0, MP_C3, PinMP_C3) \
    MapPin(0, MP_C4, PinMP_C4) \
    MapPin(0, MP_Batt_U, PinMP_Batt_U) \
    MapPin(0, MP_Charge_U, PinMP_Charge_U) \
    MapPin(0, MP_Load_U, PinMP_Load_U) \
    MapPin(0, MP_Load_sw_U, PinMP_Load_sw_U) \
    MapPin(0, LED1, PinLED1) \
    MapPin(0, LED2, PinLED2) \
    MapPin(0, LED3, PinLED3) \
    MapPin(0, C_discon, PinC_discon) \
    MapPin(0, L_discon, PinL_discon) \
    MapPin(0, L_sw_discon, PinL_sw_discon) \
    MapPin(0, Main_Relay, PinMain_Relay_On) \
    MapPin(0, Main_Relay, PinMain_Relay_Off) \
    MapPin(0, Temp, PinTemp) \
    MapPin(0, Temp_C, PinTemp_C) \
    MapPin(0, Temp_L, PinTemp_L) \
    MapPin(0, Temp_L_sw, PinTemp_L_sw) \
    MapPin(0, ModBus_enable, PinModBusPV) \
    \
    MapPin(1, Main_On, PinGPO_1) \
    MapPin(1, L_sw_On, PinGPO_2) \
    MapPin(1, Alarm, PinGPO_3) \
    MapPin(1, L_On, PinGPO_4) \
    MapPin(1, L_On, PinGPO_5) \
    MapPin(1, C_On, PinGPO_6) \
    MapPin(1, Main_Button, PinGPI_1) \
    MapPin(1, L_sw_Button, PinGPI_2) \
    \
    MapPin(2, Main_On, PinGPO_1) \
    MapPin(2, L_sw_On, PinGPO_2) \
    MapPin(2, Alarm, PinGPO_3) \
    MapPin(2, C_On, PinGPO_4) \
    MapPin(2, L_On, PinGPO_5) \
    MapPin(2, C_On, PinGPO_6) \
    MapPin(2, Main_Button, PinGPI_1) \
    MapPin(2, L_sw_Button, PinGPI_2) \
    \
    MapPin(3, Main_On, PinGPO_1) \
    MapPin(3, L_sw_On, PinGPO_2) \
    MapPin(3, L_On, PinGPO_3) \
    MapPin(3, C_On, PinGPO_4) \
    MapPin(3, L_On, PinGPO_5) \
    MapPin(3, C_On, PinGPO_6) \
    MapPin(3, Main_Button, PinGPI_1) \
    MapPin(3, L_sw_Button, PinGPI_2) \
    \
    MapPin(4, Main_On, PinGPO_1) \
    MapPin(4, Alarm, PinGPO_2) \
    MapPin(4, L_On, PinGPO_3) \
    MapPin(4, C_On, PinGPO_4) \
    MapPin(4, L_On, PinGPO_5) \
    MapPin(4, C_On, PinGPO_6) \
    MapPin(4, Main_Button, PinGPI_1) \
    \
    MapPin(5, L_sw_On, PinGPO_1) \
    MapPin(5, Alarm, PinGPO_2) \
    MapPin(5, L_On, PinGPO_3) \
    MapPin(5, C_On, PinGPO_4) \
    MapPin(5, L_On, PinGPO_5) \
    MapPin(5, C_On, PinGPO_6) \
    MapPin(5, L_sw_Button, PinGPI_1) \
    \
    MapPin(7, Main_On, PinGPO_1) \
    MapPin(7, Main_On, PinGPO_2) \
    MapPin(7, Main_On, PinGPO_3) \
    MapPin(7, Main_On, PinGPO_4) \
    MapPin(7, Main_On, PinGPO_5) \
    MapPin(7, Main_On, PinGPO_6) \
    MapPin(7, Main_Button, PinGPI_1) \
    MapPin(7, Main_Button, PinGPI_2) \
    MapPin(7, Main_Button, PinGPI_3) \
    MapPin(7, Main_Button, PinGPI_4)

// clang-format on