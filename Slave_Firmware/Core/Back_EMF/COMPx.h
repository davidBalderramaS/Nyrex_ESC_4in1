/*
 * This file is for the initialization of internal comparators
 * for the back EMF detection circuitry
 *
 * Goal: When COMPx_INP > COMPx_INM,
 *       then switch to the next commutational step in motor sequence.
 *       Pretty simple, eh?
 *
 */

#ifndef BACK_EMF_COMPX_H_
#define BACK_EMF_COMPX_H_

#include "stm32g431xx.h"

extern volatile uint16_t phase1_2_counter;

void COMP1_Init(void);     // PA1+ | PA4-
void COMP3_Init_v2(void); // PC1+ | PC0-
void COMP4_Init_v2(void); // PB0+ | PB2-

// These function will be used for the next/final project (4-in-1 ESC)
//void COMP2_Init(void);    // PA3+ | PA2- <-USART2
//void COMP3_Init(void);    // PA0+ | PF1-
//void COMP2_Init_v2(void); // PA7+ | PA5-

void Enable_COMP1_Interrupt(void);
void Enable_COMP3_Interrupt(void);
void Enable_COMP4_Interrupt(void);
void COMP1_2_3_IRQHandler(void);
void COMP4_IRQHandler(void);

void Disable_All_COMP_Interrupts(void);

#endif /* BACK_EMF_COMPX_H_ */


