/*
 * uart_drv.h
 *
 *  Created on: Mar 5, 2026
 *      Author: ghrug
 */

#ifndef UART_DRV_H_
#define UART_DRV_H_

#include "stdint.h"
#include "stm32f7xx.h"
#include "gpio_drv.h"
#include "rcc_drv.h"
#include "config.h"

#define UART_MODE_POS 2
#define UART_RXNEIE_POS 4

typedef enum {
	OFF,
	RX,
	TX,
	RXTX
} uart_mode_t;



typedef struct {
    USART_TypeDef *usart;
    uint32_t baud_rate;
    uint8_t mode;
    uint8_t irq_priority;

    uint8_t *rx_buf;
    uint16_t rx_buf_size;
    volatile uint16_t rx_head;   // written by ISR
    volatile uint16_t rx_tail;   // read by application

    uint8_t *tx_buf;
    uint16_t tx_buf_size;
    volatile uint16_t tx_head;   // written by application
    volatile uint16_t tx_tail;   // read by ISR
} UsartConfig;


// Function Prototypes

void uart_init(UsartConfig *usart_config);

int16_t uart_read(UsartConfig *cfg);

void uart_handle_isr(UsartConfig *cfg);

void uart_send(UsartConfig *cfg, uint8_t byte);


#endif /* UART_DRV_H_ */
