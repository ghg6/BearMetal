/*
 * led_bsp.c
 *
 *  Created on: Mar 15, 2026
 *      Author: ghrug
 */

#include "led_bsp.h"

static const gpio_pin_cfg_t led_cfg = {
    .mode  = GPIO_MODE_OUTPUT,
    .otype = GPIO_OTYPE_PUSHPULL,
    .speed = GPIO_SPEED_LOW,
    .pupd  = GPIO_PUPD_NONE,
    .af    = 0
};

LED_cfg led_1 = {
	.config = led_cfg,
	.bus = LED_GPIO,
	.pin = LED_PIN,
};

void led_bsp_init(LED_cfg *cfg)
{
    rcc_enable_gpio(cfg->bus);
    __NOP();

    gpio_config(cfg->bus, cfg->pin, &cfg->config);
}

void bsp_led_toggle(LED_cfg *cfg)
{
    gpio_toggle(cfg->bus, cfg->pin);
}


