/*
 * timer_drv.c
 *
 *  Created on: Mar 11, 2026
 *      Author: ghrug
 */

#include "timer_drv.h"

TimerCFG timer6 = {
	.prescaler =  10799,  // 108 MHz / 108 = 10 kHz
	.period =  10000,     // 10 kHz / 10000 = 1 Hz
};

tim_callback_t tim2_callback = NULL;
tim_callback_t tim3_callback = NULL;
tim_callback_t tim4_callback = NULL;
tim_callback_t tim5_callback = NULL;
tim_callback_t tim6_callback = NULL;
tim_callback_t tim7_callback = NULL;

int8_t timer_interrupt_handle(TIM_TypeDef *timer)
{
	// Check if interrupt is active
	// If active clear flag
	if (timer->SR & TIM_SR_UIF) {
		timer->SR &= ~TIM_SR_UIF;  // Clear interrupt flag
		return(1);
	}
	return(0);
}

int8_t enable_pwm(TIM_TypeDef *timer, TimerCFG *timer_cfg)
{

	if (timer == TIM6 || timer == TIM7) return(-1);

	timer->CCR1 = timer_cfg->duty;

	// 5. Configure PWM mode (CCMR1 - Channel 1)
	timer->CCMR1 = (timer_cfg->preload_enable << 3);
	timer->CCMR1 |= (timer_cfg->OC_mode << 4);  // PWM Mode 1 (bits 6:4)

	//Enable output on Channel 1
	timer->CCER |= TIM_CCER_CC1E;

	return(0);

}

void timer_init(TIM_TypeDef *timer, TimerCFG *timer_cfg, tim_callback_t callback)
{

	rcc_enable_timer(timer);

	// Set prescaler
	timer->PSC = timer_cfg->prescaler;

	// Set period
	timer->ARR = timer_cfg->period;

	// Enable timer
	timer->CR1 |= (1 << 0);

	// Do not activate interrupts unless a callback is passed
	if (callback != NULL) {
		timer->DIER |= TIM_DIER_UIE;  // Enable update interrupt

		if (timer == TIM2) {
			tim2_callback = callback;
			NVIC_EnableIRQ(TIM2_IRQn);
			NVIC_SetPriority(TIM2_IRQn, PRIORITY_TIMER2);
		} else if (timer == TIM3) {
			tim3_callback = callback;
			NVIC_EnableIRQ(TIM3_IRQn);
			NVIC_SetPriority(TIM3_IRQn, PRIORITY_TIMER3);
		} else if (timer == TIM4) {
			tim4_callback = callback;
			NVIC_EnableIRQ(TIM4_IRQn);
			NVIC_SetPriority(TIM4_IRQn, PRIORITY_TIMER4);
		} else if (timer == TIM5) {
			tim5_callback = callback;
			NVIC_EnableIRQ(TIM5_IRQn);
			NVIC_SetPriority(TIM5_IRQn, PRIORITY_TIMER5);
		} else if (timer == TIM6) {
			tim6_callback = callback;
			NVIC_EnableIRQ(TIM6_DAC_IRQn);
			NVIC_SetPriority(TIM6_DAC_IRQn, PRIORITY_TIMER6);
		} else if (timer == TIM7) {
			tim7_callback = callback;
			NVIC_EnableIRQ(TIM7_IRQn);
			NVIC_SetPriority(TIM7_IRQn, PRIORITY_TIMER7);
		}
	}


}

