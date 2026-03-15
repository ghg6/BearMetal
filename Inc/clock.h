/*
 * clock.h
 *
 *  Created on: Feb 14, 2026
 *      Author: ghrug
 */

#ifndef CLOCK_H_
#define CLOCK_H_

#include "global.h"

void clock_init(void);
void clock_set_frequency(uint32_t target_hz);
void clock_switch_to_hsi(void);
void clock_switch_to_pll(void);
uint32_t clock_get_frequency(void);


#endif /* CLOCK_H_ */
