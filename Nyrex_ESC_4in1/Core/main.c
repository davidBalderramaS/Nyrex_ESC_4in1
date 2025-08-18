/*
 * Electronic Speed Controller (ESC) - BLDC Motor Driver Firmware
 * Utilizes a closed-loop feedback system.
 * Using the STM32G431RB microcontroller (Nucleo board), back emf detection, and ir2110 mosfet driver
 *
 * Enjoy :^)
 *
 * Author: David Balderrama S.
 * Start Date: 6/27/2025
 * End date: 8/14/2025
 *
 */

#include "stm32g4xx.h"
#include "stm32g431xx.h"
#include <stdio.h>
#include <math.h>

#include "Back_EMF/COMPx.h"
#include "Sensor_Handling/ADC.h"
#include "Communication/USART_printf.h"
#include "ESC_Control/PWM_To_Drivers.h"
#include "ESC_Control/OpenLoop_Config.h"
#include "ESC_Control/COMP_Loop_Config.h"
#include "Utils/Delay_Timer.h"
#include "Utils/Utils.h"


int main(void){
	LED_PA10_Init();
	USART2_PA2_Init();        // PA2 == COMP2_INM
	ADC_Poten_PA7_Init();     // TIMER3
	Delay_TIM17_Init();       // Delay_mS()

	COMP1_Init();             // PA1+ | PA4-  -> P1
	COMP3_Init_v2();          // PC1+ | PC0-  -> P2
	COMP4_Init_v2();          // PB0+ | PB2-  -> P3

	PWM_PB6_TIM4_CH1_Init();  // M1H
	PWM_PB3_TIM2_CH2_Init();  // M1L
	PWM_PA15_TIM2_CH1_Init(); // M2H
	PWM_PB7_TIM4_CH2_Init();  // M2L
	PWM_PC2_TIM1_CH3_Init();  // M3H
	PWM_PC3_TIM1_CH4_Init();  // M3L

	// Ensure global interrupts are enabled
	if (__get_PRIMASK() & 1){
		__enable_irq();
	}

	while (1){
		if (toggle_State == 0){
			// No feedback. Manually triggers commutational steps through manual delay
			Open_Loop();
		}
		else if (toggle_State == 1){
			// Uses feedback from back EMF to trigger commutational steps
	        Closed_Loop();
		}
	}
}




