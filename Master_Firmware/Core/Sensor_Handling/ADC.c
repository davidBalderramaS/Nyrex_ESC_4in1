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

#include "ADC.h"

#include "stm32g4xx.h"
#include <stdio.h>
#include <math.h>

#define PWM_DutyCycle_Max   159
#define ADC_Bits            4096

volatile uint16_t ADC_Value_PA7 = 0;

// Initializes GPIOA, Timer, and Interrupt peripherals for PA7
void ADC_Poten_PA7_Init(void){
	// Step 1: Init GPIOA
	// Enable GPIOA Clk access
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;
	// Set PA7 to analog mode
	GPIOA->MODER |= (0b11 << 14);


	// Step 2: Init Timer (TIM3_CH2 -> AF2)
    // Enable TIM3 clock
    RCC->APB1ENR1 |= RCC_APB1ENR1_TIM3EN;

    // Set prescaler and auto-reload for 10ms period (For 16 MHz Clk)
    TIM3->PSC = 16000 - 1;   // 16 MHz / 16000 = 1 kHz
    TIM3->ARR = 1000 - 1;    // 1 kHz / 1000 = 1 Hz (1s)

    // Set TIM3 to generate TRGO on update event
    TIM3->CR2 |= (0b010 << 4);

    // Enable timer
    TIM3->CR1 |= TIM_CR1_CEN;


    // Step 3: Init Interrupt (ADC2_IN4) -> IN4 = CH4
	// enable ADC2 Clk and ADC Clk source
	RCC->AHB2ENR |= RCC_AHB2ENR_ADC12EN;
	RCC->CCIPR |= (0b10 << 28);

	// ADC startup sequence
	// Enable ADC voltage regulator (RM0440: 21.4.6)
	ADC2->CR &= ~(ADC_CR_ADEN|ADC_CR_DEEPPWD);     // Disable ADC and DEEPPWD
	ADC2->CR |= ADC_CR_ADVREGEN;                   // Enable voltage regulator
	for (volatile uint32_t i = 0; i < 1000; i++);  // Wait ~20 µs for regulator

	// Calibrate ADC
	ADC2->CR |= ADC_CR_ADCAL;         // Start calibration
	while (ADC2->CR & ADC_CR_ADCAL);  // Wait for calibration to complete

	// Enable ADC
	ADC2->CR |= ADC_CR_ADEN;
	while (!(ADC2->ISR & ADC_ISR_ADRDY));  // Wait for ADC to be ready

    // Trigger from TIM3 TRGO
    ADC2->CFGR |= (0b00100 << 5);  // TIM3_TRGO = 4 (RM0440: Table 67. Interconnect 19)
    ADC2->CFGR |= (0b01 << 10);    // Trigger on rising edge

    // Convert CH4 first -> SQ1
	ADC2->SQR1 |= (4 << 6);

    // Set sample time for SMP4 (CH4) -> 47.5 ADC Clk cycles
	ADC2->SMPR1 &= ~(0b111 << 12);
	ADC2->SMPR1 |= (0b100 << 12);

    // Enable end of conv interrupt EOCIE
    ADC2->IER |= ADC_IER_EOCIE;

    // Enable ADC interrupt in NVIC
    NVIC_SetPriority(ADC1_2_IRQn, 2);  // Optional: Set priority
    NVIC_EnableIRQ(ADC1_2_IRQn);

    // Start ADC conversion (triggered by TIM3_TRGO)
    ADC2->CR |= ADC_CR_ADSTART;
}

// ADC Interrupt thingy
void ADC1_2_IRQHandler(void) {
    if (ADC2->ISR & ADC_ISR_EOC) {
    	// 12-bit result (0–4095)
    	ADC_Value_PA7 = ADC2->DR;
    }
}

/*
 *  This function adjusts/truncates values of the ADC input (potentiometer value)
 *  in order to fit the PWM duty cycle range
 *  ADC = 0-4095
 *  PWM duty cycle = CCRx = 0-159 <-- For a 100k Hz PWM signal
 */
uint16_t ADC_Truncate(int ADC_Val_Poten){
	// truncatedVal = (userInput/4095) * 159
	double ADC_Val_Truncated = (((double)ADC_Val_Poten/(ADC_Bits - 1)) * PWM_DutyCycle_Max);

	// round up to nearest whole number
	return (uint16_t)round(ADC_Val_Truncated);
}

/*
 *  This function calculates the duty cycle percentage
 *  Input is truncated ADC value
 */
uint16_t Duty_Cycle_Percent(uint16_t dutyCycleRange){
	double dutyCyclePercentage = (((double)dutyCycleRange / PWM_DutyCycle_Max) * 100);

	return (uint16_t)round(dutyCyclePercentage);
}





