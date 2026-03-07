/*
 * gpio_drv.h
 *
 *  Created on: Mar 5, 2026
 *      Author: ghrug
 */

#ifndef GPIO_DRV_H_
#define GPIO_DRV_H_

#include <stdint.h>
#include "stm32f7xx.h"

typedef enum {
    GPIO_MODE_INPUT  = 0u,
    GPIO_MODE_OUTPUT = 1u,
    GPIO_MODE_AF     = 2u,
    GPIO_MODE_ANALOG = 3u
} gpio_mode_t;

typedef enum {
    GPIO_OTYPE_PUSHPULL  = 0u,
    GPIO_OTYPE_OPENDRAIN = 1u
} gpio_otype_t;

typedef enum {
    GPIO_SPEED_LOW      = 0u,
    GPIO_SPEED_MEDIUM   = 1u,
    GPIO_SPEED_HIGH     = 2u,
    GPIO_SPEED_VERYHIGH = 3u
} gpio_speed_t;

typedef enum {
    GPIO_PUPD_NONE = 0u,
    GPIO_PUPD_UP   = 1u,
    GPIO_PUPD_DOWN = 2u
} gpio_pupd_t;

typedef struct {
	gpio_mode_t  mode;
    gpio_otype_t otype;   // used for output/AF
    gpio_speed_t speed;   // used for output/AF
    gpio_pupd_t  pupd;
    uint8_t      af;      // 0..15, only used when mode==AF
} gpio_pin_cfg_t;

void gpio_config(GPIO_TypeDef *gpio, uint32_t pin, const gpio_pin_cfg_t *cfg);

void gpio_write(GPIO_TypeDef *gpio, uint32_t pin, uint8_t value);
void gpio_toggle(GPIO_TypeDef *gpio, uint32_t pin);
uint8_t gpio_read(GPIO_TypeDef *gpio, uint32_t pin);



#endif /* GPIO_DRV_H_ */
