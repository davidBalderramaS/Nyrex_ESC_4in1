/*
 * This files is for the Configuration USART for serial communication (Receiving)
 *
 * Sets PA10 to AF7 for USART1_TX
 *
 */

#ifndef COMMUNICATION_USART1_RX_H_
#define COMMUNICATION_USART1_RX_H_

#include "stm32g431xx.h"

void USART1_PA10_Init(void);
char USART1_ReadChar(void);
int __io_getchar(void);

#endif /* COMMUNICATION_USART1_RX_H_ */


