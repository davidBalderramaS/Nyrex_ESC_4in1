/*
 * Control_Algoriths.c
 *
 *  Created on: Aug 20, 2025
 *      Author: David
 */

#include "Control_Algoriths.h"

#include "stm32g431xx.h"
#include <stdio.h>
#include <math.h>

/*
 * These values set the PWM duty cycle for mosfet drivers
 * ADC Value (3.3V)   -> 0 - 2048
 * ADC_truncate_Value -> 0 - 159
 * Throttle_Val       -> 80 - 159
 *
 *
 * I subtracted 0.05 so that the function round would round down, not up when x/2 == 0.5
 * wouln't skip a number/count a number twice
 *
 */

uint8_t Throttle_Algo(uint8_t ADC_Value_Truncate2){
	double Throttle_Val = ((((double)(ADC_Value_Truncate2 / 2) - 0.05)) + 79);

	return (uint8_t)round(Throttle_Val);
}
