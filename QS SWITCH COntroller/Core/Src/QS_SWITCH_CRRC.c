/*
 * QS_SWITCH_CRRC.c
 *
 *  Created on: May 3, 2024
 *      Author: Linda Ngwenya
 */
#include "QS_SWITCH_CRRC.h"
#include "QS_SWITCH_IO.h"
#include "main.h"
#include <stdio.h>
#include <stdint.h>

//uint16_t StallingCurrent = readAnalogueInput();

const uint16_t MaxStallingCurrent = 2UL;
//////const uint16_t TimeOut= delay function

void runQSLoop(void)
    {

    IOState_t ACState = HAL_GPIO_ReadPin(GPIO_ACS_GPIO_Port, GPIO_ACS_Pin);
    IOState_t DCState = HAL_GPIO_ReadPin(GPIO_DCS_GPIO_Port, GPIO_DCS_Pin);

    ///<Checking if the QS is on AC mode and that DC feedback is not active
    if (ACState == ON && DCState == OFF)
	{
	HAL_GPIO_WritePin(GPIOB, LED_AC, GPIO_PIN_SET);

	}
    ///<Checking if the QS is on DC mode and that AC feedback is not active
    if (DCState == ON && ACState == OFF)
	{
	HAL_GPIO_WritePin(GPIOB, LED_DC, GPIO_PIN_SET);
	}
    ///<This is in between state which can be cause by some factors like power
    ///<cut while the QS Switch was on transition mode (moving from AC To DC and vice verse
    ///<This loop will take this the QS Switch to safe mode (default mode) which is
    ///< AC Mode
    else
	{
	HAL_GPIO_WritePin(GPIOB, Foward, GPIO_PIN_SET);
	while (ACState != ON && (readAnalogueInput() <= MaxStallingCurrent)) ///<while the AC feedback is not received stay on the loop
									     ///<also if time out and stalling current is not reached stay on the loop
	    {

	    }
	HAL_GPIO_WritePin(GPIOB, LED_AC, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOB, Foward, GPIO_PIN_RESET);
	}
    Transition();
    }

void Transition(void)
    {
    ///<Before we start the transition we need to check if the ES is high
    ///<if not high the system will disallow the transition to start
    if (getInput(DCS) == ON)
	{
	if (ES == ON && getInput(ACS) == OFF) ///< The transition is "To DC Mode" state
					      ///<The should be only one signal received at the time
	    {              ///< this loop is checking for the DC signal from TCU
	    HAL_GPIO_WritePin(GPIOB, Reverse, GPIO_PIN_SET);
	    ///< The motor will start to spin/rotate, then will wait for DC feedback, stalling current or Time out
	    /////////DELAY FUNCTION FOR TIME OUT////////////
	    if (readAnalogueInput() >= MaxStallingCurrent)//< Remenber to add the time out fucntion

		{
		HAL_GPIO_WritePin(GPIOB, Reverse, GPIO_PIN_RESET); ///< Stop the motor
		HAL_GPIO_WritePin(GPIOB, LED_Fault, GPIO_PIN_SET); ///< display the Fault LED
								   ///<This indicate that the system has fault
		}
	    if (DCFB == ON)
		{
		HAL_GPIO_WritePin(GPIOB, Reverse, GPIO_PIN_RESET); ///< Stop the motor if the feedback is received
		HAL_GPIO_WritePin(GPIOB, LED_DC, GPIO_PIN_SET); ///< Indicate the DC Mode LED

		}
	    else if (ACFB == ON) ///<Mismatch feedback the system will go to fault mode
		{
		HAL_GPIO_WritePin(GPIOB, LED_Fault, GPIO_PIN_SET);
		///< delay(2 min) cool down time
		}
	    }
	else
	    { ///< else the Enable Signal (ES) is low, therefore the system will not allow any transition
	    HAL_GPIO_WritePin(GPIOB, LED_Fault, GPIO_PIN_SET);
	    ///< Try to blink the white LED

	    }
	}

    if (getInput(ACS) == ON)
	{
	if (ES == ON && getInput(DCS) == OFF) ///< The transition is "To AC Mode" state
					      ///<The should be only one signal received at the time
	    {              ///< this loop is checking for the AC signal from TCU
	    HAL_GPIO_WritePin(GPIOB, Foward, GPIO_PIN_SET);
	    ///< The motor will start to spin/rotate, then will wait for AC feedback, stalling current or Time out
	    /////////DELAY FUNCTION FOR TIME OUT////////////
	    if (readAnalogueInput() >= MaxStallingCurrent)//< Remenber to add the time out fucntion

		{
		HAL_GPIO_WritePin(GPIOB, Foward, GPIO_PIN_RESET); ///< Stop the motor
		HAL_GPIO_WritePin(GPIOB, LED_Fault, GPIO_PIN_SET); ///< display the Fault LED
								   ///<This indicate that the system has fault
		}
	    if (ACFB == ON)
		{
		HAL_GPIO_WritePin(GPIOB, Foward, GPIO_PIN_RESET); ///< Stop the motor if the feedback is received
		HAL_GPIO_WritePin(GPIOB, LED_AC, GPIO_PIN_SET); ///< Indicate the DC Mode LED

		}
	    else if (DCFB == ON) ///<Mismatch feedback the system will go to fault mode
		{
		HAL_GPIO_WritePin(GPIOB, LED_Fault, GPIO_PIN_SET);
		///< delay(2 min) cool down time
		}
	    }
	else
	    { ///< else the Enable Signal (ES) is low, therefore the system will not allow any transition
	    HAL_GPIO_WritePin(GPIOB, LED_Fault, GPIO_PIN_SET);
	    ///< Try to blink the white LED

	    }
	}
    if (getInput(MANUAL) == ON)
	{
	///<Manual mode is activated by pressing and holding the button for 3 seconds
	///<declare Manual_time as button
	///if (getInput(MANUAL) == ON && Manual_time > 3000UL)
	 //   {

	  //  }
	}

    }

