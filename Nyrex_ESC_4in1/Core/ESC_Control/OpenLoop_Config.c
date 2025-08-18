/*
 * This files control the open-loop system that drives the motor
 *
 * This simply calls the particular step in the pattern and sets a constant delay (PHASE_DELAY_US).
 * This is only used at the beginning at the start-up to make the motor spin
 *
 */

#include "OpenLoop_Config.h"

#include "stm32g431xx.h"

#include "../ESC_Control/PWM_To_Drivers.h"
#include "../Sensor_Handling/ADC.h"
#include "../Utils/Delay_Timer.h"
#include "../Communication/USART_printf.h"


#define FLOATING          0         // Sets PWM duty cycle to 0

volatile uint16_t Phase_State = 1;  // Commutational step pattern
volatile uint16_t toggle_State = 0; // toggles Open_Loop() -> COMP_Loop()
uint32_t counter = 0;


void Open_Loop(void){

	switch(Phase_State){
		case 1:
			// Cycle 1 -> PhaseA -> High side ON
			//            PhaseB -> low side ON
			//            PhaseC -> FLOATING
			Set_DutyCycle_PB6_TIM4_CH1(ADC_Truncate(ADC_Value_PA7)); // M1H
			Set_DutyCycle_PB7_TIM4_CH2(ADC_Truncate(ADC_Value_PA7)); // M2L

			Set_DutyCycle_PB3_TIM2_CH2(FLOATING);  // M1L
			Set_DutyCycle_PA15_TIM2_CH1(FLOATING); // M2H
			Set_DutyCycle_PC2_TIM1_CH3(FLOATING);  // M3H
			Set_DutyCycle_PC3_TIM1_CH4(FLOATING);  // M3L


			Delay_uS(PHASE_DELAY_US);
			Phase_State++;
			break;

		case 2:
			// Cycle 2 -> PhaseA -> High side ON
			//            PhaseB -> FLOATING
			//            PhaseC -> low side ON
			Set_DutyCycle_PB6_TIM4_CH1(ADC_Truncate(ADC_Value_PA7));  // M1H
			Set_DutyCycle_PC3_TIM1_CH4(ADC_Truncate(ADC_Value_PA7));  // M3L

			Set_DutyCycle_PB3_TIM2_CH2(FLOATING);  // M1L
			Set_DutyCycle_PA15_TIM2_CH1(FLOATING); // M2H
			Set_DutyCycle_PB7_TIM4_CH2(FLOATING);  // M2L
			Set_DutyCycle_PC2_TIM1_CH3(FLOATING);  // M3H


			Delay_uS(PHASE_DELAY_US);
			Phase_State++;
			break;

		case 3:
			// Cycle 3 -> PhaseA -> FLOATING
			//            PhaseB -> High side ON
			//            PhaseC -> low side ON
			Set_DutyCycle_PA15_TIM2_CH1(ADC_Truncate(ADC_Value_PA7)); // M2H
			Set_DutyCycle_PC3_TIM1_CH4(ADC_Truncate(ADC_Value_PA7));  // M3L

			Set_DutyCycle_PB6_TIM4_CH1(FLOATING);  // M1H
			Set_DutyCycle_PB3_TIM2_CH2(FLOATING);  // M1L
			Set_DutyCycle_PB7_TIM4_CH2(FLOATING);  // M2L
			Set_DutyCycle_PC2_TIM1_CH3(FLOATING);  // M3H


			Delay_uS(PHASE_DELAY_US);
			Phase_State++;
			break;

		case 4:
			// Cycle 4 -> PhaseA -> Low side ON
			//            PhaseB -> High side ON
			//            PhaseC -> FLOATING
			Set_DutyCycle_PA15_TIM2_CH1(ADC_Truncate(ADC_Value_PA7)); // M2H
			Set_DutyCycle_PB3_TIM2_CH2(ADC_Truncate(ADC_Value_PA7));  // M1L

			Set_DutyCycle_PB6_TIM4_CH1(FLOATING);  // M1H
			Set_DutyCycle_PB7_TIM4_CH2(FLOATING);  // M2L
			Set_DutyCycle_PC2_TIM1_CH3(FLOATING);  // M3H
			Set_DutyCycle_PC3_TIM1_CH4(FLOATING);  // M3L


			Delay_uS(PHASE_DELAY_US);
			Phase_State++;
			break;

		case 5:
			// Cycle 5 -> PhaseA -> Low side ON
			//            PhaseB -> FLOATING
			//            PhaseC -> High side ON
			Set_DutyCycle_PC2_TIM1_CH3(ADC_Truncate(ADC_Value_PA7));  // M3H
			Set_DutyCycle_PB3_TIM2_CH2(ADC_Truncate(ADC_Value_PA7));  // M1L

			Set_DutyCycle_PB6_TIM4_CH1(FLOATING);  // M1H
			Set_DutyCycle_PA15_TIM2_CH1(FLOATING); // M2H
			Set_DutyCycle_PB7_TIM4_CH2(FLOATING);  // M2L
			Set_DutyCycle_PC3_TIM1_CH4(FLOATING);  // M3L


			Delay_uS(PHASE_DELAY_US);
			Phase_State++;
			break;

		case 6:
			// Cycle 6 -> PhaseA -> FLOATING
			//            PhaseB -> LOW side ON
			//            PhaseC -> High side ON
			Set_DutyCycle_PC2_TIM1_CH3(ADC_Truncate(ADC_Value_PA7));  // M3H
			Set_DutyCycle_PB7_TIM4_CH2(ADC_Truncate(ADC_Value_PA7));  // M2L

			Set_DutyCycle_PB6_TIM4_CH1(FLOATING);  // M1H
			Set_DutyCycle_PB3_TIM2_CH2(FLOATING);  // M1L
			Set_DutyCycle_PA15_TIM2_CH1(FLOATING); // M2H
			Set_DutyCycle_PC3_TIM1_CH4(FLOATING);  // M3L


			Delay_uS(PHASE_DELAY_US);
			Phase_State = 1;

			// Switches to COMP_Loop() after "OPEN_LOOP_DELAY" number of cycles
			counter++;
			if(counter == OPEN_LOOP_DELAY){
				toggle_State = 1;
			}
			break;

		default:
			break;
	}
}
