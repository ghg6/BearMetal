/*
 * global.h
 *
 *  Created on: Feb 7, 2026
 *      Author: ghrug
 */

#ifndef SYSTEM_H_
#define SYSTEM_H_

#include "global.h"
#include <stdint.h>
#include "stm32f7xx.h"
#include "config.h"
#include "clock.h"
#include "watchdog.h"

#include "timer_drv.h"

void fpu_enable(void);

void cache_enable(void);

void system_init(void);

#endif /* SYSTEM_H_ */
