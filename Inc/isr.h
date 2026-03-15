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

// Add counters
extern volatile uint32_t counter_1s;

#endif /* ISR_H_ */
