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

#include "COMP_Loop_Config.h"

#include "stm32g431xx.h"

#include "../ESC_Control/PWM_To_Drivers.h"
#include "../Sensor_Handling/ADC.h"
#include "../Utils/Delay_Timer.h"
#include "../Communication/USART_printf.h"
#include "../Back_EMF/COMPx.h"
#include "../Utils/Utils.h"

#define  COMP_FLOATING          0       // Sets PWM duty cycle to 0
#define  COMP_PHASE_DELAY_uS    1400    // open_loop delay == 3000 uS -> @1200 uS (burns)

volatile uint16_t COMP_Phase_State = 1;  // Since Open_Loop ends off at step 6, start at 6

// Feedback system using back emf signal
void Closed_Loop(void){

	// Set LED_PA10 ON to indicate Closed_Loop() mode
	GPIOA->ODR |= LED_PA10;

	switch(COMP_Phase_State){
		case 1:
			// Cycle 1 -> PhaseA -> High side ON
			//            PhaseB -> low side ON
			//            PhaseC -> FLOATING
			Set_DutyCycle_PB6_TIM4_CH1(ADC_Truncate(ADC_Value_PA7)); // M1H
			Set_DutyCycle_PB7_TIM4_CH2(ADC_Truncate(ADC_Value_PA7)); // M2L

			Set_DutyCycle_PB3_TIM2_CH2(COMP_FLOATING);  // M1L
			Set_DutyCycle_PA15_TIM2_CH1(COMP_FLOATING); // M2H
			Set_DutyCycle_PC2_TIM1_CH3(COMP_FLOATING);  // M3H
			Set_DutyCycle_PC3_TIM1_CH4(COMP_FLOATING);  // M3L

			// Allow back-EMF to settle
			Delay_uS(COMP_PHASE_DELAY_uS);

			// P3 == Floating
			// call interrupt to wait for COMP4_INP > COMP4_INM
			Enable_COMP4_Interrupt();
			break;

		case 2:
			// Cycle 2 -> PhaseA -> High side ON
			//            PhaseB -> FLOATING
			//            PhaseC -> low side ON
			Set_DutyCycle_PB6_TIM4_CH1(ADC_Truncate(ADC_Value_PA7));  // M1H
			Set_DutyCycle_PC3_TIM1_CH4(ADC_Truncate(ADC_Value_PA7));  // M3L

			Set_DutyCycle_PB3_TIM2_CH2(COMP_FLOATING);  // M1L
			Set_DutyCycle_PA15_TIM2_CH1(COMP_FLOATING); // M2H
			Set_DutyCycle_PB7_TIM4_CH2(COMP_FLOATING);  // M2L
			Set_DutyCycle_PC2_TIM1_CH3(COMP_FLOATING);  // M3H

			// Allow back-EMF to settle
			Delay_uS(COMP_PHASE_DELAY_uS);

			// P2 == Floating
			// call interrupt to wait for COMP3_INP > COMP3_INM
			Enable_COMP3_Interrupt();
			break;

		case 3:
			// Cycle 3 -> PhaseA -> FLOATING
			//            PhaseB -> High side ON
			//            PhaseC -> low side ON
			Set_DutyCycle_PA15_TIM2_CH1(ADC_Truncate(ADC_Value_PA7)); // M2H
			Set_DutyCycle_PC3_TIM1_CH4(ADC_Truncate(ADC_Value_PA7));  // M3L

			Set_DutyCycle_PB6_TIM4_CH1(COMP_FLOATING);  // M1H
			Set_DutyCycle_PB3_TIM2_CH2(COMP_FLOATING);  // M1L
			Set_DutyCycle_PB7_TIM4_CH2(COMP_FLOATING);  // M2L
			Set_DutyCycle_PC2_TIM1_CH3(COMP_FLOATING);  // M3H

			// Allow back-EMF to settle
			Delay_uS(COMP_PHASE_DELAY_uS);

			// P1 == Floating
			// call interrupt to wait for COMP1_INP > COMP1_INM
			Enable_COMP1_Interrupt();
			break;

		case 4:
			// Cycle 4 -> PhaseA -> Low side ON
			//            PhaseB -> High side ON
			//            PhaseC -> FLOATING
			Set_DutyCycle_PA15_TIM2_CH1(ADC_Truncate(ADC_Value_PA7)); // M2H
			Set_DutyCycle_PB3_TIM2_CH2(ADC_Truncate(ADC_Value_PA7));  // M1L

			Set_DutyCycle_PB6_TIM4_CH1(COMP_FLOATING);  // M1H
			Set_DutyCycle_PB7_TIM4_CH2(COMP_FLOATING);  // M2L
			Set_DutyCycle_PC2_TIM1_CH3(COMP_FLOATING);  // M3H
			Set_DutyCycle_PC3_TIM1_CH4(COMP_FLOATING);  // M3L

			// Allow back-EMF to settle
			Delay_uS(COMP_PHASE_DELAY_uS);

			// P3 == Floating
			// call interrupt to wait for COMP4_INP > COMP4_INM
			Enable_COMP4_Interrupt();
			break;

		case 5:
			// Cycle 5 -> PhaseA -> Low side ON
			//            PhaseB -> FLOATING
			//            PhaseC -> High side ON
			Set_DutyCycle_PC2_TIM1_CH3(ADC_Truncate(ADC_Value_PA7));  // M3H
			Set_DutyCycle_PB3_TIM2_CH2(ADC_Truncate(ADC_Value_PA7));  // M1L

			Set_DutyCycle_PB6_TIM4_CH1(COMP_FLOATING);  // M1H
			Set_DutyCycle_PA15_TIM2_CH1(COMP_FLOATING); // M2H
			Set_DutyCycle_PB7_TIM4_CH2(COMP_FLOATING);  // M2L
			Set_DutyCycle_PC3_TIM1_CH4(COMP_FLOATING);  // M3L

			// Allow back-EMF to settle
			Delay_uS(COMP_PHASE_DELAY_uS);

			// P2 == Floating
			// call interrupt to wait for COMP3_INP > COMP3_INM
			//phase1_2_counter = 3;
			Enable_COMP3_Interrupt();
			break;

		case 6:
			// Cycle 6 -> PhaseA -> FLOATING
			//            PhaseB -> LOW side ON
			//            PhaseC -> High side ON
			Set_DutyCycle_PC2_TIM1_CH3(ADC_Truncate(ADC_Value_PA7));  // M3H
			Set_DutyCycle_PB7_TIM4_CH2(ADC_Truncate(ADC_Value_PA7));  // M2L

			Set_DutyCycle_PB6_TIM4_CH1(COMP_FLOATING);  // M1H
			Set_DutyCycle_PB3_TIM2_CH2(COMP_FLOATING);  // M1L
			Set_DutyCycle_PA15_TIM2_CH1(COMP_FLOATING); // M2H
			Set_DutyCycle_PC3_TIM1_CH4(COMP_FLOATING);  // M3L

			// Allow back-EMF to settle
			Delay_uS(COMP_PHASE_DELAY_uS);

			// P1 == Floating
			// call interrupt to wait for COMP1_INP > COMP1_INM
			//phase1_2_counter = 4;
			Enable_COMP1_Interrupt();
			break;

		default:
			break;
	}
}


