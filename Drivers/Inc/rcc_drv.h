/*
 * rcc_drv.h
 *
 *  Created on: Mar 5, 2026
 *      Author: ghrug
 */

#ifndef RCC_DRV_H_
#define RCC_DRV_H_

#include "stm32f7xx.h"

typedef struct {

} rcc_cfg_t;

void rcc_enable_gpio(GPIO_TypeDef *gpio);

void rcc_enable_usart(USART_TypeDef *USART);

void rcc_enable_usart2();

#endif /* RCC_DRV_H_ */
