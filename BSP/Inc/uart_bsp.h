/*
 * uart_bsp.h
 *
 *  Created on: Mar 5, 2026
 *      Author: ghrug
 */

#ifndef UART_BSP_H_
#define UART_BSP_H_

#include "uart_drv.h"
#include "gpio_drv.h"


typedef struct {
	USART_TypeDef *usart;
	GPIO_TypeDef *gpio_bus;

	gpio_pin_cfg_t *gpio_config;

	uint8_t rx_pin;
	uint8_t tx_pin;


} UsartObject;



#endif /* UART_BSP_H_ */
