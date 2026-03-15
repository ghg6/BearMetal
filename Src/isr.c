/*
 * isr.c
 *
 *  Created on: Mar 15, 2026
 *      Author: ghrug
 */

#include "isr.h"

volatile uint32_t counter_1s = 0;

void TIM6_DAC_IRQHandler(void)
{
    if (timer_interrupt_handle(TIM6)) {
    	if (tim6_callback) tim6_callback();
    }
}

// In isr.c
void tim6_led_callback(void)
{
    bsp_led_toggle(&led_1);
    counter_1s++;
}


