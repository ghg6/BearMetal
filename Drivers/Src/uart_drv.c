/*
 * uart_drv.c
 *
 *  Created on: Mar 5, 2026
 *      Author: ghrug
 */

#include "uart_drv.h"

void calc_baud_rate(uint32_t baud_rate)
{

}

void kick_tx(USART_TypeDef *usart, uint8_t data) {

	// Assign data to Transmit Data Register (TDR)
	// Transmit Data Register Empty (TXE) is cleared
	usart->TDR = data;
}

void kick_rx(USART_TypeDef *usart, uint8_t *data)
{
	*data = (uint8_t)(usart->RDR & 0xFF);

}

void uart_init(UsartConfig *usart_config)
{

	USART_TypeDef *usart = usart_config->usart;

	// Enable USART
	usart->CR1 = 0b1;

	// Enable RX/TX
	usart->CR1 |= (usart_config->mode << UART_MODE_POS);

	// Enable RX interrupts
	usart->CR1 |= (1u << UART_RXNEIE_POS);

	// Set Baud Rate
	usart->BRR = 0x1D;

	// Set Clock
	//rcc_enable_usart(usart);

	// Set GPIO
	//gpio_config(usart_obj->gpio_bus, usart_obj->tx_pin, usart_obj->gpio_config);
	//gpio_config(usart_obj->gpio_bus, usart_obj->rx_pin, usart_obj->gpio_config);
}


