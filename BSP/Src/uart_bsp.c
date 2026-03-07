/*
 * uart_bsp.c
 *
 *  Created on: Mar 5, 2026
 *      Author: ghrug
 */

#include "uart_bsp.h"



#define UART2_RX_BUF_SIZE 256
#define UART2_TX_BUF_SIZE 256

void uart_bsp_init(uart_bsp_cfg_t *cfg) {
	rcc_enable_usart(cfg->usart.usart);
    gpio_config(cfg->pins.port, cfg->pins.tx_pin, &cfg->pins.pin_cfg);
    gpio_config(cfg->pins.port, cfg->pins.rx_pin, &cfg->pins.pin_cfg);
    uart_init(&cfg->usart);
}

// Define USART2
#ifdef ENABLE_UART2

static uint8_t uart2_rx_buf[UART2_RX_BUF_SIZE];
static uint8_t uart2_tx_buf[UART2_TX_BUF_SIZE];

const gpio_pin_cfg_t uart2_gpio_cfg = {
	.mode = GPIO_MODE_AF,
	.otype = GPIO_OTYPE_PUSHPULL,
	.speed = GPIO_SPEED_HIGH,
	.pupd = GPIO_PUPD_NONE,
	.af = 7
};

const UsartConfig uart2_cfg = {
	.usart = USART2,
	.baud_rate = 115200,
	.mode = RXTX,
	.rx_buf = uart2_rx_buf,
	.rx_buf_size = UART2_RX_BUF_SIZE,
	.tx_buf = uart2_tx_buf,
	.tx_buf_size = UART2_TX_BUF_SIZE
};

uart_bsp_cfg_t uart2_bsp = {
	.usart = uart2_cfg,
	.pins =  {
		.port = GPIOD,
		.tx_pin = 5,
		.rx_pin = 6,
		.pin_cfg = uart2_gpio_cfg
	}

};

#endif


//UsartObject usart2 = {
//
//};



