/*
 * uart_bsp.h
 *
 *  Created on: Mar 5, 2026
 *      Author: ghrug
 */

#ifndef UART_BSP_H_
#define UART_BSP_H_

#include "stm32f7xx.h"
#include "uart_drv.h"
#include "gpio_drv.h"
#include "rcc_drv.h"

#define ENABLE_UART2

typedef struct {
	GPIO_TypeDef *port;
	uint8_t tx_pin;
	uint8_t rx_pin;
	gpio_pin_cfg_t pin_cfg;
} uart_pins_cfg_t;

typedef struct {
	UsartConfig usart;
    uart_pins_cfg_t pins;
} uart_bsp_cfg_t;

extern uart_bsp_cfg_t uart2_bsp;

void uart_bsp_init(uart_bsp_cfg_t *cfg);



#endif /* UART_BSP_H_ */
