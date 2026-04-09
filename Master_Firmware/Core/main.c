/*
 * Electronic Speed Controller (ESC) - BLDC Motor Driver Firmware
 * Utilizes a closed-loop feedback system.
 * Using the STM32G431RB microcontroller (Nucleo board), back emf detection, and ir2110 mosfet driver
 *
 * Enjoy :^)
 *
 * Author: David Balderrama S.
 * Start Date: 8/17/2025
 * End date: ?
 *
 */

#include "stm32g4xx.h"
#include "stm32g431xx.h"
#include <stdio.h>
#include <math.h>
#include <string.h>

#include "Back_EMF/COMPx.h"
#include "Sensor_Handling/ADC.h"
#include "Communication/USART_printf.h"
#include "ESC_Control/PWM_To_Drivers.h"
#include "ESC_Control/OpenLoop_Config.h"
#include "ESC_Control/COMP_Loop_Config.h"
#include "Utils/Delay_Timer.h"
#include "Utils/Utils.h"
#include "Communication/SPI_Config.h"
#include "Control_System/Control_Algoriths.h"
#include "NRF24L01/NRF24.h"
#include "NRF24L01/NRF24_reg_addresses.h"

#define PLD_SIZE 32

/*
 *       Master
 */

// Stuff for NRF24 idk
uint8_t data_T[PLD_SIZE] = {"Start"};
uint8_t ack_T[PLD_SIZE];

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

	SPI2_Master_Init();

	// Ensure global interrupts are enabled
	if (__get_PRIMASK() & 1){
		__enable_irq();
	}

	// NRF24 Init
	csn_high();
	nrf24_init();
	nrf24_tx_pwr(_0dbm);
	nrf24_data_rate(_1mbps);
	nrf24_set_channel(78);
	nrf24_pipe_pld_size(0,PLD_SIZE);
	uint8_t addr[5] = { 0x10, 0x21, 0x32, 0x43, 0x54};
	nrf24_open_tx_pipe(addr);
	nrf24_open_rx_pipe(0,addr);

	nrf24_stop_listen();

	while (1){
		//uint8_t throttle_value = (uint8_t)Throttle_Algo(ADC_Truncate(ADC_Value_PA7));
		uint8_t throttle_value = (uint8_t)(ADC_Truncate(ADC_Value_PA7));
	    data_T[0] = throttle_value;

	    for (int i = 1; i < 32; i++)
	     {
	         data_T[i] = 0;
	     }

	   // printf("%u \r\n", throttle_value);

	    nrf24_transmit(data_T, sizeof(data_T));
	    Delay_mS(35);
	}
}


