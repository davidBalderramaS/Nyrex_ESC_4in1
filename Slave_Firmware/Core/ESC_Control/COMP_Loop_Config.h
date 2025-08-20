/*
 * This files control the closed-loop feedback system that drives the motor
 *
 * This sets the particular COMP to trigger and activate depending on the cycle step
 *
 * To simplify, it does the following:
 *
 *			PhaseX    > Virtual_Neutral
 * 		if (COMPx_INP > COMPx_INM){
 * 			go to next step
 * 		}
 *
 * 	It does so by using interrupts NOT by reading COMP_CRS_VALUE register
 *
 */

#ifndef ESC_CONTROL_COMP_LOOP_CONFIG_H_
#define ESC_CONTROL_COMP_LOOP_CONFIG_H_

#include "stm32g431xx.h"

extern volatile uint16_t COMP_Phase_State;

void Closed_Loop(void);

#endif /* ESC_CONTROL_COMP_LOOP_CONFIG_H_ */
