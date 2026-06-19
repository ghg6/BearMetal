/*
 * watchdog.h
 *
 *  Created on: Feb 15, 2026
 *      Author: ghrug
 */

#ifndef WATCHDOG_H_
#define WATCHDOG_H_

#include <stdint.h>
#include "stm32f7xx.h"
#include "config.h"

typedef enum {
	IWDG_PRESCALER_4,
	IWDG_PRESCALER_8,
	IWDG_PRESCALER_16,
	IWDG_PRESCALER_32,
	IWDG_PRESCALER_64,
	IWDG_PRESCALER_128,
	IWDG_PRESCALER_256,
} IWDG_PRESCALER_VALUE;

void iwdg_init(IWDG_PRESCALER_VALUE prescaler, uint16_t counter);

void kick_watchdog(void);


#endif /* WATCHDOG_H_ */
