/*
 * rcc_drv.c
 *
 *  Created on: Mar 5, 2026
 *      Author: ghrug
 */

#include "rcc_drv.h"

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

void rcc_enable_usart(USART_TypeDef *USART)
{
	if (USART == USART2)
	{
		// Enable USART2 clock
		RCC->APB1ENR |= RCC_APB1ENR_USART2EN;

		// Enable GPIOD clock
		RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;


	}

}

void rcc_enable_usart2()
{
	// Enable USART2 clock
	RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
}


