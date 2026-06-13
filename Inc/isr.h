/*
 * isr.h
 *
 *  Created on: Mar 15, 2026
 *      Author: ghrug
 */

#ifndef ISR_H_
#define ISR_H_

#include "global.h"


void tim6_led_callback(void);
void tim7_tick_callback(void);

extern volatile uint32_t counter_1s;
extern volatile uint32_t millis;

#endif /* ISR_H_ */
