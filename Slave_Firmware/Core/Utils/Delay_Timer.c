/*
 *
 * This function uses TIM3 for an accurate delay function
 *
 */

#include "Delay_Timer.h"
#include "stm32g431xx.h"
#include <stdio.h>

void Delay_TIM17_Init(void){
	// Init Clk for TIM3
	RCC->APB2ENR |= RCC_APB2ENR_TIM17EN;

	 // Wait for clock stabilization (optional, for robustness)
	 while (!(RCC->APB2ENR & RCC_APB2ENR_TIM17EN)) {}

	// Set TIM3 prescaler
	     // freq = Sys_Clk / (PSC + 1)(ARR + 1)
	     // 1MHz = 16 Mhz / (16 + 1)(userInput + 1)
	     // 1MHz == 1 uS
	     // therefore, set PSC = 16 and ARR = userInput

	TIM17->PSC = (SystemCoreClock / 1000000) - 1;        // Clk pre-scaler -> 16MHz / 16 = 1MHz
	TIM17->ARR = 0xFFFF;        // Set maximum duty cycle == 1uS

    // Generate an update event to apply PSC and ARR
	TIM17->EGR |= TIM_EGR_UG;

    // Clear the counter
	TIM17->CNT = 0;

	// Enable the timer
	TIM17->CR1 |= TIM_CR1_CEN;
}

// 1,000,000 uS == 1 sec
void Delay_uS(uint16_t time_uS){
	// Reset the counter
	TIM17->CNT = 0;

	//while ((volatile uint16_t)TIM3->CNT < time_uS);
	while (TIM17->CNT < time_uS);
}

// 1,000 uS == 1 mS --> 1000 mS == 1 sec
void Delay_mS(uint16_t time_mS){

	for (uint16_t counter = 0; counter < time_mS; counter++){
		Delay_uS(1000);
	}
}




