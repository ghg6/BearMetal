/*
 * timer.h
 *
 *  Created on: Feb 13, 2026
 *      Author: ghrug
 */

#ifndef TIMER_H_
#define TIMER_H_

  #include <stdint.h>
  #include "stm32f7xx.h"

  /* Initialize SysTick timer for system timing */
  void timer_init(uint32_t cpu_hz, uint32_t tick_hz);

  /* Get elapsed milliseconds since system start */
  uint32_t timer_get_ms(void);

  /* Non-blocking timer: returns 1 if interval_ms has elapsed, 0 otherwise */
  /* Call repeatedly in a loop to perform periodic actions */
  uint8_t timer_elapsed(uint32_t *last_tick, uint32_t interval_ms);

#endif /* TIMER_H_ */
