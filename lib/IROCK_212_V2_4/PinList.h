/**
 * @file PinList.h
 * @author Joscha Wagner (joscha@nebensound.com)
 * @brief Definition of all Pins for iRock 212 V2_4 hardware
 *
 * Copyright (c) Nebensound GmbH 2021
 */

// I2C definitions
// #define SERIAL_VE_BUS 2

/*
 * A Pin is defined by the following parameters:
 *
 *	* PinId	        Id of the Pin an enum (e.g. PinPA1) which is the index
 *					into the Pin table
 *  * PinNo         The number of the Pin on the Processor a symbolic constant
 *                   of the used hardware board (e.g. PA1)
 *	* Type			Type of the Pin. One of the following values:
 *						* AnalogInputPin
 *                      * AnalogOutputPin
 *	                    * DigitalInputPin
 *	                    * DigitalInputPullUpPin
 *	                    * DigitalInputPullDownPin
 *	                    * DigitalOutputPin
 *                      * DigitalOutputOpenDrainPin
 *	                    * VrefIntExternPin
 *  * Gain          Factor (float) to multiply the Analog Value with
 *	* Offset        Offset (float) to add to the Analog Value
 *	* Inverted		Boolean defining if the Digital Value should be inverted
 *	* Generic  	    This boolean attribute defines if the Pin is a Generic
 *                   Pin and allows to be added to a Signal at run-time.
 *                   Only Output Pins allow dynamic addition at run-time.
 *                   For other Pins the attribute is ignored and should
 *                   be set to false.
 *	* Description 	Description of the Pin
 *
 *
 * Please define here the list of all Pins
 */
// clang-format off
//      PinName             Pin/Address PinType                     Gain    Offset  Invert  Generic Description
#define PinList \
    Pin(PinDip1,            PA15,       DigitalInputPullUpPin,      1.0,    0.0,    true,   false,  "Dip switch 1") \
    Pin(PinDip2,            PC10,       DigitalInputPullUpPin,      1.0,    0.0,    true,   false,  "Dip switch 2") \
    Pin(PinDip3,            PC11,       DigitalInputPullUpPin,      1.0,    0.0,    true,   false,  "Dip switch 3") \
    Pin(PinDip4,            PC12,       DigitalInputPullUpPin,      1.0,    0.0,    true,   false,  "Dip switch 4") \
    Pin(PinAD_C1,           PC5,        AnalogInputPin,             2.0,    0.0,    false,  false,  "Cell 1 voltage") \
    Pin(PinAD_C2,           PC4,        AnalogInputPin,             2.0,    0.0,    false,  false,  "Cell 2 voltage") \
    Pin(PinAD_C3,           PA7,        AnalogInputPin,             2.0,    0.0,    false,  false,  "Cell 3 voltage") \
    Pin(PinAD_C4,           PA6,        AnalogInputPin,             2.0,    0.0,    false,  false,  "Cell 4 voltage") \
    Pin(PinGPO_LVP,         PH1,        DigitalOutputPin,           1.0,    0.0,    true,   false,  "GPO LVP") \
    Pin(PinGPO_OVP,         PH0,        DigitalOutputPin,           1.0,    0.0,    true,   false,  "GPO UVP") \
    Pin(PinGPO_Alarm,       PC15,       DigitalOutputPin,           1.0,    0.0,    true,   false,  "GPO Alarm") \
    Pin(PinBU_C1,           PB15,       DigitalOutputPin,           1.0,    0.0,    false,  false,  "BU Cell 1") \
    Pin(PinBU_C2,           PB2,        DigitalOutputPin,           1.0,    0.0,    false,  false,  "BU Cell 2") \
    Pin(PinBU_C3,           PA4,        DigitalOutputPin,           1.0,    0.0,    false,  false,  "BU Cell 3") \
    Pin(PinBU_C4,           PA3,        DigitalOutputPin,           1.0,    0.0,    false,  false,  "BU Cell 4") \
    Pin(PinLED1,            PD2,        DigitalOutputPin,           1.0,    0.0,    false,  false,  "LED 1") \
    Pin(PinLED2,            PB3,        DigitalOutputPin,           1.0,    0.0,    false,  false,  "LED 2") \
    Pin(PinLED3,            PB4,        DigitalOutputPin,           1.0,    0.0,    false,  false,  "LED 3") \
    Pin(PinSSR_Shunt,       PB1,        AnalogInputPin,             1.0,    0.0,    false,  false,  "SSR-Shunt") \
    Pin(PinShunt,           PC0,        AnalogInputPin,             1.0,    0.0,    false,  false,  "Shunt") \
    Pin(PinFBShunt,         PA5,        AnalogInputPin,             1.0,    0.0,    false,  false,  "Feedback Shunt") \
    Pin(PinV_GND,           PC1,        AnalogInputPin,             1.0,    0.0,    false,  false,  "Virtual Ground") \
    Pin(PinGate,            PC6,        DigitalOutputPin,           1.0,    0.0,    false,  false,  "Gate Driver") \
    Pin(PinGatePSU,         PC7,        DigitalOutputPin,           1.0,    0.0,    false,  false,  "Gate PSU Driver") \
    Pin(PinVE_Current,      NoPin,      VEDirectPin,                1.0,    0.0,    false,  false,  "Current from VE Shunt")
// clang-format on
