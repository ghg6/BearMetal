/*
 * timer.c
 *
 *  Created on: Feb 13, 2026
 *      Author: ghrug
 */

 #include "timer.h"

  // System tick counter - incremented by SysTick_Handler every 1 ms
  static volatile uint32_t systick_ms = 0;

  /*
   * Initialize SysTick timer
   *
   * @param cpu_hz:  CPU frequency in Hz (e.g., 216000000 for 216 MHz)
   * @param tick_hz: Desired tick frequency in Hz (e.g., 1000 for 1 ms ticks)
   */
  void timer_init(uint32_t cpu_hz, uint32_t tick_hz)
  {
      // Calculate reload value for SysTick timer
      // LOAD = (cpu_hz / tick_hz) - 1
      SysTick->LOAD = (cpu_hz / tick_hz) - 1U;

      // Clear current value register and COUNTFLAG
      SysTick->VAL = 0U;

      // Configure SysTick control register:
      // - Use processor clock (not external reference clock)
      // - Enable SysTick exception (interrupt)
      // - Enable counter
      SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk  // Processor clock
                    | SysTick_CTRL_TICKINT_Msk    // Enable SysTick interrupt
                    | SysTick_CTRL_ENABLE_Msk;    // Start counting
  }

  /*
   * Get elapsed time in milliseconds since system start
   *
   * @return: Milliseconds elapsed (rolls over after ~49 days)
   */
  uint32_t timer_get_ms(void)
  {
      return systick_ms;
  }

  /*
   * Non-blocking elapsed timer
   *
   * Call repeatedly in a loop. Returns 1 when interval_ms has elapsed since
   * last call, 0 otherwise. Auto-resets on timeout.
   *
   * @param last_tick:   Pointer to storage variable (initialize to 0)
   * @param interval_ms: Interval in milliseconds
   * @return: 1 if interval elapsed, 0 otherwise
   *
   * Example usage:
   *   static uint32_t led_timer = 0;
   *   if (timer_elapsed(&led_timer, 1000)) {
   *       bsp_led_toggle();
   *   }
   */
  uint8_t timer_elapsed(uint32_t *last_tick, uint32_t interval_ms)
  {
      uint32_t now = timer_get_ms();
      uint32_t elapsed = now - *last_tick;

      if (elapsed >= interval_ms) {
          *last_tick = now;
          return 1;
      }
      return 0;
  }

  /*
   * SysTick interrupt service routine
   * Called every 1 ms by hardware timer
   */
  void SysTick_Handler(void)
  {
      systick_ms++;  // Increment millisecond counter
  }



