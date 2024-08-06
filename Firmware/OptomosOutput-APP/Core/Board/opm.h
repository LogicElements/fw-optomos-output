/*
 * opm.h
 *
 *  Created on: 22. 2. 2024
 *      Author: hp
 */

#ifndef BOARD_OPM_H_
#define BOARD_OPM_H_

/* Includes ------------------------------------------------------------------*/

#include "common.h"

/* Definitions----------------------------------------------------------------*/

#define OPM_CHANNELS      16

/* Typedefs-------------------------------------------------------------------*/

/* Functions -----------------------------------------------------------------*/

Status_t OPM_Init(void);
Status_t OPM_Handler(void);
Status_t OPM_State(void);
Status_t OPM_Set(void);
Status_t OPM_Clear(void);
Status_t OPM_Def_State(void);
#endif /* BOARD_OPM_H_ */
