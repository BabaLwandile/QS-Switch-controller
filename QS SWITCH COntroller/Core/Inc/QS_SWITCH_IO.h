/*
 * QS_SWITCH_IO.h
 *
 *  Created on: May 2, 2024
 *      Author: 0163022
 */

#ifndef INC_QS_SWITCH_IO_H_
#define INC_QS_SWITCH_IO_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdint.h>
#include "main.h"
#include "stdbool.h"

typedef union						// module send to Lop
    {
	uint8_t data;
	struct
	    {
		uint8_t B0 :1;
		uint8_t B1 :1;
		uint8_t B2 :1;
		uint8_t B3 :1;
		uint8_t B4 :1;
		uint8_t B5 :1;
		uint8_t B6 :1;
		uint8_t B7 :1;
	    } bit;

    } Flag8_t;

/// Enumeration to indicate the state of the the general purpose input or
/// output.

enum IOState
    {
    OFF = GPIO_PIN_RESET, ///< "OFF" state.
    ON = GPIO_PIN_SET, ///< "ON" state.
    UNKNOWN
    };

/// Enumeration listing the available digit inputs to the QS Switch.

enum Inputs
    {
    MANUAL,
    DCS,    ///<DC command from the TCU
    ACS,    ///<AC command from the TCU
    DCFB,    ///<DC feedback from the QS micro-switches
    ACFB,    ///<AC feedback from the QS micro-switches
    ES ///<Enable signal from the TCU, to enable the
       ///<transition of the QS Switch
    };

/// Enumeration listing the available digital outputs of the QS Switch.

enum Outputs
    {
    Foward,
    Reverse,
    LED_EN,
    LED_DC,
    LED_AC,
    LED_Fault
    };
enum ButtonState
    {
    BTN_HOLD,
    BTN_PRESSED = 0,     ///<One click
    BTN_NOT_PRESSED
    };

typedef enum IOState IOState_t;
typedef enum Inputs Input_t;
typedef enum Outputs Output_t;
typedef enum ButtonState ButtonState_t;

typedef struct
    {
	uint32_t buttonTimer;
	bool buttonTimerEnable;
	ButtonState_t buttonStatus;     ///<Change from MenuButtonStatus_e
	Flag8_t buttonFlag;
	uint8_t buttonHeldPressedCounter;
    } MenuButton_t;

extern MenuButton_t ManualButton;

void MX_ADC_Init(void);
void MX_GPIO_Init(void);

uint16_t readAnalogueInput(void);

#ifdef __cplusplus
}
#endif

#endif /* INC_QS_SWITCH_IO_H_ */

