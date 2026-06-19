/*
 * config.h
 *
 *  Created on: Feb 13, 2026
 *      Author: ghrug
 */

#ifndef CONFIG_H_
#define CONFIG_H_

// System Definitions
//#define USING_RTOS

// Define core board requirements
#define LSI_FREQUENCY (32*1000) // 32Khz
#define HSI_FREQUENCY (16*1000000) // 16Mhz
#define CPU_FREQUENCY (216*1000000) // 216Mhz
#define APB1_FREQUENCY (54*1000000)
#define APB2_FREQUENCY (108*1000000)

// Define custom configurations
//#define TICK_FREQUENCY 1000 // 1ms

// Interrupt Priorities
#define PRIORITY_TIMER2  8
#define PRIORITY_TIMER3  8
#define PRIORITY_TIMER4  8
#define PRIORITY_TIMER5  8
#define PRIORITY_TIMER6  8
#define PRIORITY_TIMER7  8

/************************************************
 * Watchdog Configure
 * IWDG timer is based on Counter/(LSI/PRESCALER)
 ***********************************************/
#define IWDG_PRESCALER IWDG_PRESCALER_32 // Available values defined in watchdog.h
#define IWDG_COUNTER 2000

// Define WWDG



#endif /* CONFIG_H_ */
