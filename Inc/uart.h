/*
 * uart.h
 *
 *  Created on: Feb 13, 2026
 *      Author: ghrug
 */

#ifndef UART_H_
#define UART_H_

#include "stdint.h"
#include "stm32f7xx.h"
#include "rcc.h"
#include "gpio.h"

#define UART_MODE_POS 2

typedef enum {
	OFF,
	RX,
	TX,
	RXTX
} uart_mode_t;

typedef struct {
	USART_TypeDef *usart;
	GPIO_TypeDef *gpio_bus;

	gpio_pin_cfg_t *gpio_config;

	uint8_t rx_pin;
	uint8_t tx_pin;

	uint32_t baud_rate;
	uint8_t mode;
} UsartObject;



extern gpio_pin_cfg_t usart2_gpio_config;
extern UsartObject usart2;



#endif /* UART_H_ */
