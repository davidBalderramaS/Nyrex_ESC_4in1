/*
 * This files control the open-loop system that drives the motor
 *
 * This simply calls the particular step in the pattern and sets a constant delay (PHASE_DELAY_US).
 * This is only used at the beginning at the start-up to make the motor spin
 *
 */

#ifndef ESC_CONTROL_OPENLOOP_CONFIG_H_
#define ESC_CONTROL_OPENLOOP_CONFIG_H_

#include "stm32g431xx.h"
#include "../Sensor_Handling/ADC.h"

#define PHASE_DELAY_MS   3        // 1000 uS = 1 mS
#define PHASE_DELAY_US   3000
#define OPEN_LOOP_DELAY  650      // How many cycles before breaking Open_Loop();

extern volatile uint16_t toggle_State; // toggles switch from Open_Loop() -> COMP_Loop()

void Open_Loop(void);

#endif /* ESC_CONTROL_OPENLOOP_CONFIG_H_ */
