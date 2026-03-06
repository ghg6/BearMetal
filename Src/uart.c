/*
 * uart.c
 *
 *  Created on: Feb 13, 2026
 *      Author: ghrug
 */
/*
#include "uart.h"

void uart_init(UsartObject *usart_obj)
{

	USART_TypeDef *usart = usart_obj->usart;

	// Enable USART
	usart->CR1 = 0b1;

	// Enable RX/TX
	usart->CR1 |= (usart_obj->mode << UART_MODE_POS);

	// Set Baud Rate
	usart->BRR = 0x1D;

	// Set Clock
	rcc_enable_usart(usart);

	// Set GPIO
	gpio_config(usart_obj->gpio_bus, usart_obj->tx_pin, usart_obj->gpio_config);
	gpio_config(usart_obj->gpio_bus, usart_obj->rx_pin, usart_obj->gpio_config);
}

gpio_pin_cfg_t usart2_gpio_config = {
    .mode = GPIO_MODE_AF,
	.otype = GPIO_OTYPE_PUSHPULL,
	.speed = GPIO_SPEED_HIGH,
	.pupd = GPIO_PUPD_NONE,
    .af = 7
};

UsartObject usart2 = {
	.usart = USART2,
	.gpio_bus = GPIOD,
	.gpio_config = &usart2_gpio_config,
	.tx_pin = 5,
	.rx_pin = 6,
	.baud_rate = 115200,
	.mode = RXTX
};
*/
