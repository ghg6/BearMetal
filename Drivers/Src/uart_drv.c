/*
 * uart_drv.c
 *
 *  Created on: Mar 5, 2026
 *      Author: ghrug
 */

#include "uart_drv.h"

/*
* Compute BRR for oversampling by 16 (OVER8 = 0).
* USARTDIV = f_ck / baud, and BRR == USARTDIV in this mode.
* The +baud/2 rounds to nearest to minimize baud error.
*/
static uint32_t calc_baud_rate(uint32_t f_ck, uint32_t baud_rate)
{
  return (f_ck + baud_rate / 2u) / baud_rate;
}

static uint32_t usart_pclk(USART_TypeDef *usart)
{
    // USART1 and USART6 are on APB2; the rest are on APB1.
    if (usart == USART1 || usart == USART6)
        return APB2_FREQUENCY;   // 108 MHz
    return APB1_FREQUENCY;       // 54 MHz
}

static void kick_tx(USART_TypeDef *usart, uint8_t data) {

	// Assign data to Transmit Data Register (TDR)
	// Transmit Data Register Empty (TXE) is cleared
	usart->TDR = data;
}

static void kick_rx(USART_TypeDef *usart, uint8_t *data)
{
	*data = (uint8_t)(usart->RDR & 0xFF);

}

static IRQn_Type usart_irqn(USART_TypeDef *usart)
{
    if (usart == USART1) return USART1_IRQn;
    if (usart == USART2) return USART2_IRQn;
    if (usart == USART3) return USART3_IRQn;
    // etc.
    return USART2_IRQn;  // fallback
}

void uart_init(UsartConfig *usart_config)
{

	USART_TypeDef *usart = usart_config->usart;

	// Set Clock
	rcc_enable_usart(usart);

	// Set Baud Rate
	usart->BRR = calc_baud_rate(usart_pclk(usart), usart_config->baud_rate);

	// Enable RX/TX
	usart->CR1 |= (usart_config->mode << UART_MODE_POS);

	// Enable RX interrupts
	if (usart_config->mode != TX) {
		usart->CR1 |= (1u << UART_RXNEIE_POS);
	}

	// Enable USART
	usart->CR1 |= USART_CR1_UE;

	// Set interrupt
	IRQn_Type irqn = usart_irqn(usart);
	NVIC_SetPriority(irqn, usart_config->irq_priority);
	NVIC_EnableIRQ(irqn);

}

// Returns -1 if buffer empty, otherwise the byte
int16_t uart_read(UsartConfig *cfg)
{
    if (cfg->rx_tail == cfg->rx_head) return -1;
    uint8_t byte = cfg->rx_buf[cfg->rx_tail];
    cfg->rx_tail = (cfg->rx_tail + 1) % cfg->rx_buf_size;
    return byte;
}

int8_t uart_send(UsartConfig *cfg, uint8_t byte)
{
    uint16_t next = (cfg->tx_head + 1) % cfg->tx_buf_size;
    if (next == cfg->tx_tail) return -1;    // TX buffer full, drop byte
    cfg->tx_buf[cfg->tx_head] = byte;
    cfg->tx_head = next;
    cfg->usart->CR1 |= USART_CR1_TXEIE;    // kick off ISR-driven TX
    return 0;
}

void uart_handle_isr(UsartConfig *cfg)
{
  uint32_t isr = cfg->usart->ISR;

  if (isr & USART_ISR_RXNE) {
	  uint8_t byte;
	  kick_rx(cfg->usart, &byte);
	  // write byte into rx_buf ring buffer
	  uint16_t next = (cfg->rx_head + 1) % cfg->rx_buf_size;
	  if (next != cfg->rx_tail) {     // drop on overflow
		  cfg->rx_buf[cfg->rx_head] = byte;
		  cfg->rx_head = next;
	  }
  }

  if (isr & USART_ISR_TXE) {
	  if (cfg->tx_tail != cfg->tx_head) {
		  kick_tx(cfg->usart, cfg->tx_buf[cfg->tx_tail]);
		  cfg->tx_tail = (cfg->tx_tail + 1) % cfg->tx_buf_size;
	  } else {
		  cfg->usart->CR1 &= ~USART_CR1_TXEIE;  // nothing left, disable interrupt
	  }
  }
}


