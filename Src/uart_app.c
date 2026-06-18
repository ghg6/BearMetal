/*
 * uart_app.c
 *
 *  Created on: Jun 2026
 *      Author: ghrug
 */

#include "uart_app.h"
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

void uart_app_send_buf(uart_bsp_cfg_t *cfg, const uint8_t *buf, uint16_t len)
{
	for (uint16_t i = 0; i < len; i++) {
		while (uart_send(&cfg->usart, buf[i]) < 0) {
			/* spin-wait until TX ring buffer has space */
		}
	}
}

void uart_app_send_string(uart_bsp_cfg_t *cfg, const char *str)
{
	uart_app_send_buf(cfg, (const uint8_t *)str, (uint16_t)strlen(str));
}

void uart_app_printf(uart_bsp_cfg_t *cfg, const char *fmt, ...)
{
	char buf[UART_APP_PRINTF_BUF_SIZE];
	va_list args;
	va_start(args, fmt);
	int n = vsnprintf(buf, sizeof(buf), fmt, args);
	va_end(args);

	if (n > 0) {
		uint16_t len = (n < UART_APP_PRINTF_BUF_SIZE)
				? (uint16_t)n
				: (uint16_t)(UART_APP_PRINTF_BUF_SIZE - 1);
		uart_app_send_buf(cfg, (const uint8_t *)buf, len);
	}
}

uint16_t uart_app_available(uart_bsp_cfg_t *cfg)
{
	UsartConfig *u = &cfg->usart;
	return (u->rx_head - u->rx_tail + u->rx_buf_size) % u->rx_buf_size;
}

int16_t uart_app_read_line(uart_bsp_cfg_t *cfg, char *buf, uint16_t max_len)
{
	static uint16_t pos = 0;

	while (uart_app_available(cfg) > 0) {
		int16_t c = uart_read(&cfg->usart);
		if (c < 0) break;

		if (c == '\r') {
			continue;
		}

		if (c == '\n') {
			buf[pos] = '\0';
			uint16_t count = pos;
			pos = 0;
			return (int16_t)count;
		}

		if (pos < max_len - 1) {
			buf[pos++] = (char)c;
		}
	}

	return -1;
}

void uart_app_run(uart_bsp_cfg_t *cfg)
{
	static uint32_t last_counter = 0;

	if (counter_1s != last_counter) {
		bsp_led_toggle(&led_1);
		uart_app_printf(cfg, "counter: %lu\r\n", counter_1s);
		last_counter = counter_1s;
	}
}
