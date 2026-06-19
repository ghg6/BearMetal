/*
 * uart_app.h
 *
 *  Created on: Jun 2026
 *      Author: ghrug
 */

#ifndef UART_APP_H_
#define UART_APP_H_

#include <stdint.h>
#include "uart_bsp.h"
#include "system.h"

#define UART_APP_PRINTF_BUF_SIZE 128

void     uart_app_send_string(uart_bsp_cfg_t *cfg, const char *str);
void     uart_app_send_buf(uart_bsp_cfg_t *cfg, const uint8_t *buf, uint16_t len);
void     uart_app_printf(uart_bsp_cfg_t *cfg, const char *fmt, ...);
uint16_t uart_app_available(uart_bsp_cfg_t *cfg);
int16_t  uart_app_read_line(uart_bsp_cfg_t *cfg, char *buf, uint16_t max_len);
void     uart_app_service(void);

#endif /* UART_APP_H_ */
