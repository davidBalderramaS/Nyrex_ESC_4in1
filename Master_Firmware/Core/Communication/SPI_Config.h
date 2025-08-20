/*
 * SPI_Config.h
 *
 *  Created on: Aug 19, 2025
 *      Author: David
 */

#ifndef COMMUNICATION_SPI_CONFIG_H_
#define COMMUNICATION_SPI_CONFIG_H_

#define SPI2_PB12_MASTER_CS  (1 << 12)    // Chip select (CS) for slave1

extern uint8_t Read_Slave_Value;

void SPI2_Master_Init(void);
uint8_t SPI2_TX_RX(uint8_t data);

#endif /* COMMUNICATION_SPI_CONFIG_H_ */
