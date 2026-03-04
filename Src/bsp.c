/*
 * bsp.c
 * Board Support Package
 *  Created on: Feb 7, 2026
 *      Author: ghrug
 */

#include "bsp.h"
#include "stm32f7xx.h"
#include "rcc.h"
#include "gpio.h"

#define LED_GPIO GPIOB
#define LED_PIN  0u

void bsp_init(void)
{
    rcc_enable_gpio(LED_GPIO);
    __NOP();

    static const gpio_pin_cfg_t led_cfg = {
        .mode  = GPIO_MODE_OUTPUT,
        .otype = GPIO_OTYPE_PUSHPULL,
        .speed = GPIO_SPEED_LOW,
        .pupd  = GPIO_PUPD_NONE,
        .af    = 0
    };

    gpio_config(LED_GPIO, LED_PIN, &led_cfg);
}

void bsp_led_toggle(void)
{
    gpio_toggle(LED_GPIO, LED_PIN);
}




