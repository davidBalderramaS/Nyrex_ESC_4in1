/*
 * Random/Misc functions for testing stuff
 */

#include "Utils.h"
#include "stm32g4xx.h"

#define LED_PA10         (1 << 10)
#define DELAY_BRUTE_CNT  250000

// Turn on LED on breadboard
void LED_PA10_Init(void){
	// init Clk to GPIOA
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;

	// Clear PA10
	GPIOA->MODER &= ~(0b11 << 20);

	// Set PA10 as output
	GPIOA->MODER |= (0b01 << 20);
}

// Brute force delay function
void Delay_Brute(void){
	for (volatile uint32_t count = 0; count < DELAY_BRUTE_CNT; count++);
}

