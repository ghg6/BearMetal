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

void watchdog_init(void);

void kick_watchdog(void);


#endif /* WATCHDOG_H_ */
