/*
 * PWM_To_Drivers.c
 *
 * This files is for the configuration of the 6 PWM waveforms that are used to toggle the Mosfets ON/OFF
 * (through the mosfet drivers)
 *
 */

#ifndef ESC_CONTROL_PWM_TO_DRIVERS_H_
#define ESC_CONTROL_PWM_TO_DRIVERS_H_

#include "stm32g431xx.h"

extern volatile uint16_t temp;

void Set_DutyCycle_PB6_TIM4_CH1(uint16_t ADC_Poten_Trunc_Value);  // M1H
void Set_DutyCycle_PB3_TIM2_CH2(uint16_t ADC_Poten_Trunc_Value);  // M1L
void Set_DutyCycle_PA15_TIM2_CH1(uint16_t ADC_Poten_Trunc_Value); // M2H
void Set_DutyCycle_PB7_TIM4_CH2(uint16_t ADC_Poten_Trunc_Value);  // M2L
void Set_DutyCycle_PC2_TIM1_CH3(uint16_t ADC_Poten_Trunc_Value);  // M3H
void Set_DutyCycle_PC3_TIM1_CH4(uint16_t ADC_Poten_Trunc_Value);  // M3L


void PWM_PB7_TIM4_CH2_Init(void);
void PWM_PB6_TIM4_CH1_Init(void);
void PWM_PB3_TIM2_CH2_Init(void);
void PWM_PA15_TIM2_CH1_Init(void);
void PWM_PC2_TIM1_CH3_Init(void);
void PWM_PC3_TIM1_CH4_Init(void);

// Will use these function in next/final project (4-in-1 ESC)
// void PWM_PA14_TIM8_CH2_Init(void);
// void PWM_PA13_TIM4_CH3_Init(void);

#endif /* ESC_CONTROL_PWM_TO_DRIVERS_H_ */
