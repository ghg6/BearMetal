/*
 * isr.c
 *
 *  Created on: Mar 15, 2026
 *      Author: ghrug
 */

#include "isr.h"

/*******************************
 * Timer ISR
 *
 */

void TIM6_DAC_IRQHandler(void)
{
    if (timer_interrupt_handle(TIM6)) {
    	if (tim6_callback) tim6_callback();
    }
}

void tim6_led_callback(void)
{

    counter_1s++;
}

void TIM7_IRQHandler(void)
{
    if (timer_interrupt_handle(TIM7)) {
    	if (tim7_callback) tim7_callback();
    }
}

void tim7_tick_callback(void)
{
    millis++;
}

/*******************************
 * USART ISR
 *
 */

void USART3_IRQHandler(void)
{
	uart_handle_isr(&uart3_bsp.usart);
}
