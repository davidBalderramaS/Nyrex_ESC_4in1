/*
 *  ADC.c
 *
 *  This source file is for the configuration
 *  of the ADC for PA7
 *
 *  It uses GPIO, timer, and interrupt peripherals
 *
 *  This is for the potentiometer input pin that reads user input
 *  and modifies output PWM signal (duty cycle) into mosfet drivers
 *
 */

#ifndef SENSOR_HANDLING_ADC_H_
#define SENSOR_HANDLING_ADC_H_

#include "stm32g431xx.h"
#include <stdio.h>

extern volatile uint16_t ADC_Value_PA7;

void ADC_Poten_PA7_Init(void);
void ADC1_2_IRQHandler(void);
uint16_t ADC_Truncate(int ADC_Val_Poten);
uint16_t Duty_Cycle_Percent(uint16_t dutyCycleRange);

#endif /* SENSOR_HANDLING_ADC_H_ */
