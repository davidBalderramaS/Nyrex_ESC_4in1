/*
 * This files is for the Configuration USART for serial communication (Receiving)
 *
 * Sets PA10 to AF7 for USART1_TX
 *
 */

#include "USART1_RX.h"
#include "stm32g431xx.h"

#define BAUD_RATE  9600

// Configure PA10 for USART1
void USART1_PA10_Init(void){
    // Enable GPIOA and USART1 Clk
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;
    RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
    //RCC->APB1SMENR1 |= (1 << 17);

    // Configure PA10 as AF7 (USART1_RX)
    GPIOA->MODER &= ~(0b11 << 20);
    GPIOA->MODER |=  (0b10 << 20);    // Set PA10 to Alt Funct Mode
    GPIOA->AFR[1] &= ~(0b1111 << 8);
    GPIOA->AFR[1] |=  (0b0111 << 8);  // Sets AFM to AF7

    // Configure USART1
    USART1->BRR = SystemCoreClock / BAUD_RATE;  // Set Baud rate (9600), assuming 16MHz Clk
    USART1->CR1 = USART_CR1_RE | USART_CR1_UE;  // Enable transmitter and USART
}

// Function for receiving data (characters)
char USART1_ReadChar(void) {
    while (!(USART1->ISR & USART_ISR_RXNE));  // Wait for data

    return (char)(USART1->RDR & 0xFF);        // Read char
}

// Overrides scanf()
int __io_getchar(void) {
    return USART1_ReadChar();
}


// To enable, call:
// scanf("%hu ", &userInput);

