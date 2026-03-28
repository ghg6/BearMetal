/*
 * global.h
 *
 *  Created on: Mar 15, 2026
 *      Author: ghrug
 */

#ifndef GLOBAL_H_
#define GLOBAL_H_

#include <stddef.h>
#include <stdint.h>

// CMSIS
#include "stm32f7xx.h"
#include <cmsis_gcc.h>

// Drivers
#include "gpio_drv.h"
#include "rcc_drv.h"
#include "timer_drv.h"
#include "uart_drv.h"
#include "adc_drv.h"

// BSP
#include "led_bsp.h"
#include "uart_bsp.h"

// App
#include "isr.h"
#include "config.h"


#endif /* GLOBAL_H_ */
