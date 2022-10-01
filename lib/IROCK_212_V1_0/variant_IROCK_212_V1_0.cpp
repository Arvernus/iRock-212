/*
 *******************************************************************************
 * Copyright (c) 2011-2021, STMicroelectronics
 * All rights reserved.
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 *******************************************************************************
 */
#ifdef ARDUINO_IROCK_212_V1_0
#include "pins_arduino.h"

// Pin number
const PinName digitalPin[] = {
    PA_0,  // D1/A0
    PA_1,  // D2/A1
    PA_2,  // D3/A2
    PA_3,  // D4/A3
    PA_4,  // D5/A4
    PA_5,  // D6/A5
    PA_6,  // D7/A6
    PA_7,  // D8/A7
    PA_8,  // D9
    PA_9,  // D10
    PA_10, // D11
    PA_11, // D12
    PA_12, // D13
    PA_13, // D14
    PA_14, // D15
    PA_15, // D16
    PB_0,  // D17/A8
    PB_1,  // D18/A9
    PB_2,  // D19
    PB_3,  // D20
    PB_4,  // D21
    PB_5,  // D22
    PB_6,  // D23
    PB_7,  // D24
    PB_8,  // D25
    PB_9,  // D26
    PB_10, // D27
    PB_11, // D28
    PB_12, // D29
    PB_13, // D30
    PB_14, // D31
    PB_15, // D32
    PC_0,  // D33/A10
    PC_1,  // D34/A11
    PC_2,  // D35/A12
    PC_3,  // D36/A13
    PC_4,  // D37/A14
    PC_5,  // D38/A15
    PC_6,  // D39
    PC_7,  // D40
    PC_8,  // D41
    PC_9,  // D42
    PC_10, // D43
    PC_11, // D44
    PC_12, // D45
    PC_13, // D46
    PC_14, // D47
    PC_15, // D48
    PD_2,  // D49
    PH_0,  // D50
    PH_1   // D51
};

// Analog (Ax) pin number array
const uint32_t analogInputPin[] = {
    0,  // A0,  PA0
    1,  // A1,  PA1
    2,  // A2,  PA2
    3,  // A3,  PA3
    4,  // A4,  PA4
    5,  // A5,  PA5
    6,  // A6,  PA6
    7,  // A7,  PA7
    16, // A8,  PB0
    17, // A9,  PB1
    32, // A10, PC0
    33, // A11, PC1
    34, // A12, PC2
    35, // A13, PC3
    36, // A14, PC4
    37  // A15, PC5
};

// ----------------------------------------------------------------------------

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

  /**
   * @brief  System Clock Configuration
   * @param  None
   * @retval None
   */
  WEAK void SystemClock_Config(void)
  {
    RCC_OscInitTypeDef RCC_OscInitStruct = {};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {};
    RCC_PeriphCLKInitTypeDef PeriphClkInit = {};

    /** Configure the main internal regulator output voltage
     */
    __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
    /** Initializes the RCC Oscillators according to the specified parameters
     * in the RCC_OscInitTypeDef structure.
     */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI | RCC_OSCILLATORTYPE_HSI48;
    RCC_OscInitStruct.HSIState = RCC_HSI_ON;
    RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
    RCC_OscInitStruct.HSI48State = RCC_HSI48_ON;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
    RCC_OscInitStruct.PLL.PLLMUL = RCC_PLLMUL_4;
    RCC_OscInitStruct.PLL.PLLDIV = RCC_PLLDIV_2;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
    {
      Error_Handler();
    }
    /** Initializes the CPU, AHB and APB buses clocks
     */
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
    {
      Error_Handler();
    }
    PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USB;
    PeriphClkInit.UsbClockSelection = RCC_USBCLKSOURCE_HSI48;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
    {
      Error_Handler();
    }
  }

#ifdef USBCON
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {};
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USB;
  PeriphClkInit.UsbClockSelection = RCC_USBCLKSOURCE_PLL;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
#endif /* USBCON */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* ARDUINO_IROCK_212_V1_0 */