/*
 * SPI_Config.c
 *
 *  Created on: Aug 19, 2025
 *      Author: David
 */

#include "stm32g431xx.h"
#include <stdio.h>
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

void SPI2_Master_Init(void){
	// Init Clk access to GPIOB and SPI2
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;
	RCC->APB1ENR1 |= RCC_APB1ENR1_SPI2EN;

	// Config pins to Alt Funct Mode
	GPIOB->MODER &= ~((0b11 << 24) | (0b11 << 26) | (0b11 << 28) | (0b11 << 30));
	GPIOB->MODER |= (0b01 << 24);  // PB12 == Gen Purpose Output
	GPIOB->MODER |= (0b10 << 26);  // PB13
	GPIOB->MODER |= (0b10 << 28);  // PB14
	GPIOB->MODER |= (0b10 << 30);  // PB15

	GPIOB->AFR[1] &= ~(0b1111 << 20 | 0b1111 << 24 | 0b1111 << 28);
	GPIOB->AFR[1] |= (0b0101 << 20); // PB13
	GPIOB->AFR[1] |= (0b0101 << 24); // PB14
	GPIOB->AFR[1] |= (0b0101 << 28); // PB15

	// Config SPI2_CR1 register
	SPI2->CR1 |= SPI_CR1_MSTR;     // Set to master
	SPI2->CR1 |= (0b011 << 3);     // Baud rate == F_PCLK/16
	SPI2->CR1 |= SPI_CR1_SSM;      // Software slave management enabled
	SPI2->CR1 |= SPI_CR1_SSI;      // Internal slave select
	SPI2->CR1 &= ~(SPI_CR1_CPOL | SPI_CR1_CPHA); // Mode 0

	// Config SPI2_CR2 register
	SPI2->CR2 = 0;
	SPI2->CR2 |= (0b0111 << 8);

	// Enable SPI2
	SPI2->CR1 |= SPI_CR1_SPE;
	//GPIOB->ODR |= SPI2_PB12_MASTER_CS; // Set NSS high (slave) inactive
}

// Original function (Before NRF24)
// Send and recieve data
void SPI2_Slave_TX_RX(void){
	if (SPI2->SR & SPI_SR_RXNE){
		// Read data
		Read_Master_Value = *((__IO uint8_t*)&SPI2->DR);
		//printf("Read from Master: %u \r\n", Read_Master_Value);

		// Send dummy data back (optional)
		*((__IO uint8_t*)&SPI2->DR) = 0xFF; // 0x00, 0x15
	}
}

// Sends and receives data
uint8_t SPI2_TX_RX(uint8_t data){
	uint32_t Timeout_Tx = 100000;
	uint32_t Timeout_Rx = 100000;

	// Wait for TX buffer empty
    while(!(SPI2->SR & SPI_SR_TXE)){
        if (--Timeout_Tx == 0) {
            printf("Master TXE Timeout \r\n");
            return 0;
        }
    }
    // Write data
    *((__IO uint8_t*)&SPI2->DR) = data;

    // Wait for RX buffer not empty
    while(!(SPI2->SR & SPI_SR_RXNE)){
        if (--Timeout_Rx == 0) {
            printf("Master RXNE Timeout\r\n");
            return 0;
        }
    }
    // Read received
    return *((__IO uint8_t*)&SPI2->DR);
}

// Send a pointer to a buffer plus a size -> NRF24
void SPI2_TX_Buffer(uint8_t *data, uint8_t size){
    for(uint8_t i = 0; i < size; i++){
        SPI2_TX_RX(data[i]);
    }
}

void SPI2_RX_Buffer(uint8_t *data, uint16_t size){
    for(uint16_t i = 0; i < size; i++){
        data[i] = SPI2_TX_RX(0xFF);
    }
}

