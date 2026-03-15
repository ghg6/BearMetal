/*
 * timer_drv.h
 *
 *  Created on: Mar 11, 2026
 *      Author: ghrug
 */

#ifndef TIMER_DRV_H_
#define TIMER_DRV_H_

#include "global.h"

typedef enum {
	FROZEN = 0,
	SET_ACTIVE_ON_MATCH,
	SET_INACTIVE_ON_MATCH,
	TOGGLE,
	FORCE_INACTIVE,
	FORCE_ACTIVE,
	PWM_MODE1,
	PWM_MODE2,
	// Add advanced mode
} ComparatorMode;

typedef struct {
	uint16_t prescaler;
	uint32_t period;

	// PWMW
	uint8_t OC_mode;
	uint8_t preload_enable;
	uint8_t duty;

} TimerCFG;

typedef void (*tim_callback_t)(void);

extern tim_callback_t tim2_callback;
extern tim_callback_t tim3_callback;
extern tim_callback_t tim4_callback;
extern tim_callback_t tim5_callback;
extern tim_callback_t tim6_callback;
extern tim_callback_t tim7_callback;

extern TimerCFG timer6;

int8_t timer_interrupt_handle(TIM_TypeDef *timer);
void timer_init(TIM_TypeDef *timer, TimerCFG *timer_cfg, tim_callback_t callback);



#endif /* TIMER_DRV_H_ */
