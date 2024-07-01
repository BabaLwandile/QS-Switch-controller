/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2024 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include <stdio.h>
#include "QS_SWITCH_IO.h"

MenuButton_t ManualButton;

void SystemClock_Config(void);

int main(void)
    {
    ManualButton.buttonFlag.data = RESET;   ///<Flag Reset
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();
    MX_ADC_Init();
    ManualButton.buttonStatus = BTN_NOT_PRESSED;
    while (1)
	{

	runQSLoop();
	return 0;
	}
    }

