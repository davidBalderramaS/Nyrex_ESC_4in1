/*
 * SPI_Config.h
 *
 *  Created on: Aug 19, 2025
 *      Author: David
 */

#ifndef COMMUNICATION_SPI_CONFIG_H_
#define COMMUNICATION_SPI_CONFIG_H_

extern uint8_t Read_Master_Value;

void SPI2_Slave_Init(void);
void SPI2_Master_Init(void);
void SPI2_Slave_TX_RX(void);


uint8_t SPI2_TX_RX(uint8_t data);
void SPI2_TX_Buffer(uint8_t *data, uint8_t size);
void SPI2_RX_Buffer(uint8_t *data, uint16_t size);

#endif /* COMMUNICATION_SPI_CONFIG_H_ */
