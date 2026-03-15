/*
 * led_bsp.h
 *
 *  Created on: Mar 15, 2026
 *      Author: ghrug
 */

#ifndef LED_BSP_H_
#define LED_BSP_H_

#include "gpio_drv.h"
#include "rcc_drv.h"

#define LED_GPIO GPIOB
#define LED_PIN  0u

typedef struct {
	gpio_pin_cfg_t config;
	GPIO_TypeDef *bus;
	uint8_t pin;
}LED_cfg;

extern LED_cfg led_1;

void led_bsp_init(LED_cfg *cfg);
void bsp_led_toggle(LED_cfg *cfg);


#endif /* LED_BSP_H_ */
