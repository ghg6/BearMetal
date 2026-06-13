/*
 * isr.c
 *
 *  Created on: Mar 15, 2026
 *      Author: ghrug
 */

#include "isr.h"

#define DEBOUNCE_USART_MS 20

volatile uint32_t counter_1s = 0;
volatile uint32_t millis = 0;

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
    bsp_led_toggle(&led_1);
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

void USART2_IRQHandler(void)
{
	// This ISR handles the TX/RX of the USART peripheral
	// The debounce is needed in case noisy pin values
	// constantly trigger the ISR
	static uint32_t last_call = 0;
	if (millis - last_call > DEBOUNCE_USART_MS) {
		uart_handle_isr(&uart2_bsp.usart);
		last_call = millis;
	}
}
