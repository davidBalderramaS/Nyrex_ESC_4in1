/*
 *
 * This function uses TIM3 for an accurate delay function
 *
 */

#ifndef UTILS_DELAY_TIMER_H_
#define UTILS_DELAY_TIMER_H_

#include "stm32g431xx.h"

void Delay_TIM17_Init(void);
void Delay_uS(uint16_t time_uS);
void Delay_mS(uint16_t time_mS);

#endif /* UTILS_DELAY_TIMER_H_ */
