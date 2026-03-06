/*
 * gpio.c
 *
 *  Created on: Feb 7, 2026
 *      Author: ghrug
 */

/*
#include "../Inc/gpio.h"

static inline void set_2bit_field(volatile uint32_t *reg, uint32_t pin, uint32_t val)
{
    uint32_t shift = pin * 2u;
    *reg = (*reg & ~(3u << shift)) | ((val & 3u) << shift);
}

static inline void set_1bit_field(volatile uint32_t *reg, uint32_t pin, uint32_t val)
{
    *reg = (*reg & ~(1u << pin)) | ((val & 1u) << pin);
}

static inline void set_4bit_af(GPIO_TypeDef *gpio, uint32_t pin, uint32_t af)
{
    uint32_t idx   = (pin >> 3);          // 0 for 0..7, 1 for 8..15
    uint32_t shift = (pin & 7u) * 4u;     // position within AFRL/AFRH
    gpio->AFR[idx] = (gpio->AFR[idx] & ~(0xFu << shift)) | ((af & 0xFu) << shift);
}

void gpio_config(GPIO_TypeDef *gpio, uint32_t pin, const gpio_pin_cfg_t *cfg)
{
    // Mode
    set_2bit_field(&gpio->MODER, pin, (uint32_t)cfg->mode);

    // Pull-up/down
    set_2bit_field(&gpio->PUPDR, pin, (uint32_t)cfg->pupd);

    // Output type & speed only relevant for output/AF
    if (cfg->mode == GPIO_MODE_OUTPUT || cfg->mode == GPIO_MODE_AF) {
        set_1bit_field(&gpio->OTYPER,   pin, (uint32_t)cfg->otype);
        set_2bit_field(&gpio->OSPEEDR,  pin, (uint32_t)cfg->speed);
    }

    // Alternate function only relevant for AF mode
    if (cfg->mode == GPIO_MODE_AF) {
        set_4bit_af(gpio, pin, cfg->af);
    }
}

void gpio_write(GPIO_TypeDef *gpio, uint32_t pin, uint8_t value)
{
    if (value) gpio->BSRR = (1u << pin);
    else       gpio->BSRR = (1u << (pin + 16u));
}

void gpio_toggle(GPIO_TypeDef *gpio, uint32_t pin)
{
    uint32_t mask = (1u << pin);
    if (gpio->ODR & mask) gpio->BSRR = (mask << 16u);
    else                 gpio->BSRR = mask;
}

uint8_t gpio_read(GPIO_TypeDef *gpio, uint32_t pin)
{
    return (uint8_t)((gpio->IDR >> pin) & 1u);
}
*/




