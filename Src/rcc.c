/*
 * rcc.c
 *
 *  Created on: Feb 7, 2026
 *      Author: ghrug
 */

#include "rcc.h"

void rcc_enable_gpio(GPIO_TypeDef *gpio)
{
    // Enable AHB1 clock for the given GPIO port
    if (gpio == GPIOA)      RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    else if (gpio == GPIOB) RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
    else if (gpio == GPIOC) RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
    else if (gpio == GPIOD) RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;
    else if (gpio == GPIOE) RCC->AHB1ENR |= RCC_AHB1ENR_GPIOEEN;
    else if (gpio == GPIOF) RCC->AHB1ENR |= RCC_AHB1ENR_GPIOFEN;
    else if (gpio == GPIOG) RCC->AHB1ENR |= RCC_AHB1ENR_GPIOGEN;
    else if (gpio == GPIOH) RCC->AHB1ENR |= RCC_AHB1ENR_GPIOHEN;
    else if (gpio == GPIOI) RCC->AHB1ENR |= RCC_AHB1ENR_GPIOIEN;
    else if (gpio == GPIOJ) RCC->AHB1ENR |= RCC_AHB1ENR_GPIOJEN;
    else if (gpio == GPIOK) RCC->AHB1ENR |= RCC_AHB1ENR_GPIOKEN;
    else return;

    // Read-back to ensure the write completes before peripheral access
    (void)RCC->AHB1ENR;
}


