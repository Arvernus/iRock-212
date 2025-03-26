/**
 * @file HardwareVersion.h
 * @author Joscha Wagner (joscha@nebensound.com)
 * @brief Defines the Hardwareversion of the board.
 *
 * Copyright (c) Nebensound GmbH 2025
 *
 */
#ifndef HW_VERSION
#if defined(HW_VERSION_2_4)
#define HW_VERSION 2.4
#elif defined(HW_VERSION_1_11)
#define HW_VERSION 1.11
#elif defined(HW_VERSION_1_1)
#define HW_VERSION 1.1
#elif defined(HW_VERSION_1_0)
#define HW_VERSION 1.0
#else
#define HW_VERSION 0.0
#endif // HW_VERSION_TAG
#endif // HW_VERSION
