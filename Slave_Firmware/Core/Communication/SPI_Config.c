/*
 * SPI_Config.c
 *
 *  Created on: Aug 19, 2025
 *      Author: David
 */

#include "stm32g431xx.h"
#include "SPI_Config.h"

uint8_t Read_Master_Value;

/*
*	          SPI (Master)                            (Slave)
*	PB12 -> GPIOx (General output)    ->        SPI2_NSS (Chip select)
*   PB13 -> SPI2_SCLK (Clock)         ->        SPI2_SCLK (Clock)
*	PB15 -> SPI2_MOSI (Tx)            ->        PB14 -> SPI2_MISO (Rx)
*	PB14 -> SPI2_MISO (Rx)            <-        PB15 -> SPI2_MOSI (Tx)
*/
void SPI2_Slave_Init(void){
	// Init Clk access to GPIOB and SPI2
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;
	RCC->APB1ENR1 |= RCC_APB1ENR1_SPI2EN;

	// Config pins to Alt Funct Mode
	GPIOB->MODER &= ~((0b11 << 24) | (0b11 << 26) | (0b11 << 28) | (0b11 << 30));
	GPIOB->MODER |= (0b10 << 24);   // PB12
	GPIOB->MODER |= (0b10 << 26);   // PB13
	GPIOB->MODER |= (0b10 << 28);   // PB14
	GPIOB->MODER |= (0b10 << 30);   // PB15

	GPIOB->AFR[1] &= ~((0b1111 << 16) | (0b1111 << 20) | (0b1111 << 24) | (0b1111 << 28));
	GPIOB->AFR[1] |= (0b0101 << 16);   // PB12
	GPIOB->AFR[1] |= (0b0101 << 20);   // PB13
	GPIOB->AFR[1] |= (0b0101 << 24);   // PB14
	GPIOB->AFR[1] |= (0b0101 << 28);   // PB15

	// Config SPI2_CR1 register
	SPI2->CR1 = 0;
	SPI2->CR1 &= ~SPI_CR1_MSTR;                  // Set to slave
	SPI2->CR1 &= ~(SPI_CR1_CPOL | SPI_CR1_CPHA); // Mode 0

	// Note: Hardware NSS is used (SSM and SSI not set)

	// Config SPI2_CR2 register
	SPI2->CR2 = 0;
	SPI2->CR2 |= (0b0111 << 8); // Set data size to 8-bits

	// Enable SPI2
	SPI2->CR1 |= SPI_CR1_SPE;
}

// Send and recieve data
void SPI2_Slave_TX_RX(void){
	if (SPI2->SR & SPI_SR_RXNE){
		// Read data
		Read_Master_Value = *((__IO uint8_t*)&SPI2->DR);
		printf("Read from Master: %u \r\n", Read_Master_Value);

		// Send dummy data back (optional)
		*((__IO uint8_t*)&SPI2->DR) = 0xFF; // 0x00, 0x15
	}
}

