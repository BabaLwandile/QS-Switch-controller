/*
 * QS_SWITCH_CRRC.h
 *
 *  Created on: May 3, 2024
 *      Author: 0163022
 */

#ifndef INC_QS_SWITCH_CRRC_H_
#define INC_QS_SWITCH_CRRC_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>

enum QS_Sate
    {
    QS_AC_MODE,
    QS_DC_MODE,
    QS_UNKOWN,
    QS_MANUAL_MODE,
    QS_FAULT

    };
typedef enum QS_State QS_State_t;

void runQSLoop(void);

#ifdef __cplusplus
}
#endif

#endif /* INC_QS_SWITCH_CRRC_H_ */
