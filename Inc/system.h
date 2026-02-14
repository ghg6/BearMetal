/*
 * global.h
 *
 *  Created on: Feb 7, 2026
 *      Author: ghrug
 */

#ifndef SYSTEM_H_
#define SYSTEM_H_

#include <stdint.h>
#include "stm32f7xx.h"
#include "config.h"
#include "rcc.h"
#include "gpio.h"

void fpu_enable(void);
void clock_init(void);
void cache_enable(void);
void system_init(void);

#endif /* SYSTEM_H_ */
