/*
 * This files is for the Configuration USART for serial communication (Sending)
 *
 * Sets PA9 to AF7 for USART1_TX
 *
 */

#ifndef COMMUNICATION_USART_PRINTF_H_
#define COMMUNICATION_USART_PRINTF_H_

#include "stm32g431xx.h"

#define BAUD_RATE  9600
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)

void USART2_PA2_Init(void);
void USART2_Write(char ch);
int __io_putchar(int ch);

// These function will be used on the next/final project (4-in-1 ESC)
//void USART1_PA9_Init(void);
//void USART2_PA14_Init(void);
//void USART1_Write(char ch);
//int __io_putchar(int ch);

#endif /* COMMUNICATION_USART_PRINTF_H_ */
