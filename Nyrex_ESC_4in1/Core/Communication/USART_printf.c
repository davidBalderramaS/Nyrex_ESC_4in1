/*
 * This files is for the Configuration USART for serial communication (Sending)
 *
 * Sets PA9 to AF7 for USART1_TX
 *
 */

#include "USART_printf.h"

#include "stm32g431xx.h"
#include <stdio.h>

#define BAUD_RATE  9600
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)


// Configure PA2 for USART2
void USART2_PA2_Init(void){
    // Enable GPIOA Clk and USART2 Clk
    RCC->AHB2ENR |= (1 << 0);
    RCC->APB1ENR1 |= (1 << 17);
    //RCC->APB1SMENR1 |= (1 << 17);

    // Configure PA2 as AF7 (USART2_TX)
    GPIOA->MODER &= ~(0b11 << 4);
    GPIOA->MODER |=  (0b10 << 4);    // Set PA2 to Alt Funct Mode
    GPIOA->AFR[0] &= ~(0b1111 << 8);
    GPIOA->AFR[0] |=  (0b0111 << 8);  // Sets AFM to AF7

    // Configure USART2
    USART2->BRR = SystemCoreClock / BAUD_RATE;  // Set Baud rate (9600), assuming 16MHz Clk
    //USART2->BRR = 16000000 / BAUD_RATE;
    USART2->CR1 = USART_CR1_TE | USART_CR1_UE;  // Enable transmitter and USART
}

// Function for sending data (characters)
void USART2_Write(char ch) {
    while (!(USART2->ISR & USART_ISR_TXE));  // Wait until transmit data register empty
    USART2->TDR = (ch & 0xFF);              // Send the character
}

// Overrides printf function
int __io_putchar(int ch) {
    USART2_Write(ch);
    return ch;
}

// These functions will be used on the next/final project (4-in-1 ESC)

/*
// Configure PA9 for USART1
void USART1_PA9_Init(void) {
    // Enable GPIOA Clk and USART1 Clk
    RCC->AHB2ENR |= (1 << 0);
    RCC->APB2ENR |= (1 << 14);

    // Configure PA9 (AFRL2) as AF7 (USART1_TX)
    GPIOA->MODER &= ~(0b11 << 18);
    GPIOA->MODER |=  (0b10 << 18);    // Set PA9 to Alt Funct Mode
    GPIOA->AFR[1] &= ~(0b1111 << 4);
    GPIOA->AFR[1] |=  (0b0111 << 4);  // Sets AFM to AF7

    // Configure USART1
    USART1->BRR = SystemCoreClock / BAUD_RATE;  // Set Baud rate (9600), assuming 16MHz Clk
    //USART1->BRR = 16000000 / BAUD_RATE;
    USART1->CR1 = USART_CR1_TE | USART_CR1_UE;  // Enable transmitter and USART
}

// Configure PA14 for USART2
void USART2_PA14_Init(void){
    // Enable GPIOA Clk and USART2 Clk
    RCC->AHB2ENR |= (1 << 0);
    RCC->APB1SMENR1 |= (1 << 17);

    // Configure PA14 as AF7 (USART2_TX)
    GPIOA->MODER &= ~(0b11 << 28);
    GPIOA->MODER |=  (0b10 << 28);    // Set PA14 to Alt Funct Mode
    GPIOA->AFR[1] &= ~(0b1111 << 24);
    GPIOA->AFR[1] |=  (0b0111 << 24);  // Sets AFM to AF7

    // Configure USART2
    USART2->BRR = SystemCoreClock / BAUD_RATE;  // Set Baud rate (9600), assuming 16MHz Clk
    //USART2->BRR = 16000000 / BAUD_RATE;
    USART2->CR1 = USART_CR1_TE | USART_CR1_UE;  // Enable transmitter and USART
}
*/

/*

// Function for sending data (characters)
void USART1_Write(char ch) {
    while (!(USART1->ISR & USART_ISR_TXE));  // Wait until transmit data register empty
    USART1->TDR = (ch & 0xFF);              // Send the character
    //USART1->TDR = ch;

    //while (!(USART1->ISR & USART_ISR_TC));
}

// Overrides printf function
int __io_putchar(int ch) {
    USART1_Write(ch);
    return ch;
}

*/


