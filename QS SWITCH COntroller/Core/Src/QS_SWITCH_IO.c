/*
 * QS_SWITCH_IO.c
 *
 *  Created on: May 2, 2024
 *      Author: 0163022
 */
#include <stdio.h>
#include <stdint.h>
#include "main.h"
#include "QS_SWITCH_IO.h"
#include "stm32f051x8.h"

ADC_HandleTypeDef hadc;
uint16_t ADC_CurrentSensor = 0;

uint16_t readAnalogueInput()
    {

    HAL_ADC_Start(&hadc);
    HAL_ADC_PollForConversion(&hadc, 20);
    ADC_CurrentSensor = HAL_ADC_GetValue(&hadc);
    HAL_Delay(500);

    return (ADC_CurrentSensor);

    }

void setOutput(const Output_t aOutput, const IOState_t aState)
    {
    switch (aOutput)
	{
    case LED_EN:
	HAL_GPIO_WritePin(GPIOB, LED_EN, aState);

	break;
    case LED_Fault:
	HAL_GPIO_WritePin(GPIOB, LED_Fault, aState);
	break;
    case LED_AC:
	HAL_GPIO_WritePin(GPIOB, LED_AC, aState);
	break;
    case LED_DC:
	HAL_GPIO_WritePin(GPIOB, LED_DC, aState);
	break;
    case Foward:
	HAL_GPIO_WritePin(GPIOB, Foward, aState);
	break;
    case Reverse:
	HAL_GPIO_WritePin(GPIOB, Reverse, aState);
	break;
    default:
	;
	}
    }

IOState_t getInput(const Input_t aInput)
    {
    IOState_t ret_val;
    switch (aInput)
	{
    case ES:     ///Change the variables
	ret_val = HAL_GPIO_ReadPin(GPIO_Enable_Signal_GPIO_Port,
	GPIO_Enable_Signal_Pin);
	break;
    case DCS:
	ret_val = HAL_GPIO_ReadPin(GPIO_DCS_GPIO_Port, GPIO_DCS_Pin);
	break;
    case ACS:
	ret_val = HAL_GPIO_ReadPin(GPIO_ACS_GPIO_Port, GPIO_ACS_Pin);
	break;
    case DCFB:
	ret_val = HAL_GPIO_ReadPin(GPIO_DCFB_GPIO_Port, GPIO_DCFB_Pin);
	break;
    case ACFB:
	ret_val = HAL_GPIO_ReadPin(GPIO_ACFB_GPIO_Port, GPIO_ACFB_Pin);
	break;
    case MANUAL:
	ret_val = HAL_GPIO_ReadPin(GPIO_Manual_GPIO_Port, GPIO_Manual_Pin);
	break;
	}
    return (ret_val);
    }

void MX_ADC_Init(void)
    {

    ADC_ChannelConfTypeDef sConfig =
	{
	0
	};

    /** Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion)
     */
    hadc.Instance = ADC1;
    hadc.Init.ClockPrescaler = ADC_CLOCK_ASYNC_DIV1;
    hadc.Init.Resolution = ADC_RESOLUTION_12B;
    hadc.Init.DataAlign = ADC_DATAALIGN_RIGHT;
    hadc.Init.ScanConvMode = ADC_SCAN_DIRECTION_FORWARD;
    hadc.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
    hadc.Init.LowPowerAutoWait = DISABLE;
    hadc.Init.LowPowerAutoPowerOff = DISABLE;
    hadc.Init.ContinuousConvMode = DISABLE;
    hadc.Init.DiscontinuousConvMode = DISABLE;
    hadc.Init.ExternalTrigConv = ADC_SOFTWARE_START;
    hadc.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
    hadc.Init.DMAContinuousRequests = DISABLE;
    hadc.Init.Overrun = ADC_OVR_DATA_PRESERVED;
    if (HAL_ADC_Init(&hadc) != HAL_OK)
	{
	Error_Handler();
	}

    /** Configure for the selected ADC regular channel to be converted.
     */
    sConfig.Channel = ADC_CHANNEL_0;
    sConfig.Rank = ADC_RANK_CHANNEL_NUMBER;
    sConfig.SamplingTime = ADC_SAMPLETIME_1CYCLE_5;
    if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK)
	{
	Error_Handler();
	}

    }
