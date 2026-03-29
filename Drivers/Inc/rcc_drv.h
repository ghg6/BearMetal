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



/***************************************************************
 * Define Reference Count Structs
 * The reference count is required for power saving operations.
 * The gpio can't be shut off if multiple peripherals require it
 **************************************************************/

typedef struct {
	uint8_t gpioa;
	uint8_t gpiob;
	uint8_t gpioc;
	uint8_t gpiod;
	uint8_t gpioe;
	uint8_t gpiof;
	uint8_t gpiog;
	uint8_t gpioh;
	uint8_t gpioi;
	uint8_t gpioj;
	uint8_t gpiok;
} RCC_GPIO_RefCnt;

typedef struct {
	uint8_t usart1;
	uint8_t usart2;
	uint8_t usart3;
	uint8_t usart4;
	uint8_t usart5;
	uint8_t usart6;
	uint8_t usart7;
	uint8_t usart8;
} RCC_USART_RefCnt;

typedef struct {
	uint8_t tim1;
	uint8_t tim2;
	uint8_t tim3;
	uint8_t tim4;
	uint8_t tim5;
	uint8_t tim6;
	uint8_t tim7;
	uint8_t tim8;
} RCC_TIM_RefCnt;

typedef struct {
	uint8_t adc1;
	uint8_t adc2;
	uint8_t adc3;
} RCC_ADC_RefCnt;

typedef struct {
	uint8_t dma1;
	uint8_t dma2;
} RCC_DMA_RefCnt;

typedef struct {

} RCC_I2C_RefCnt;

typedef struct {

} RCC_SPI_RefCnt;

/*
 * Function Prototypes
 */

extern void rcc_enable_gpio(GPIO_TypeDef *gpio);
void rcc_disable_gpio(GPIO_TypeDef *gpio);

void rcc_enable_usart(USART_TypeDef *USART);

void rcc_enable_timer(TIM_TypeDef *timer);
void rcc_disable_timer(TIM_TypeDef *timer);

void rcc_enable_adc(ADC_TypeDef *adc);
void rcc_disable_adc(ADC_TypeDef *adc);

void rcc_enable_dma(DMA_TypeDef *dma);
void rcc_disable_dma(DMA_TypeDef *dma);


void rcc_enable_usart2();

#endif /* RCC_DRV_H_ */
