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
#define HSI_FREQUENCY (16*1000000) // 16Mhz
#define CPU_FREQUENCY (216*1000000) // 216Mhz

// Define custom configurations
//#define TICK_FREQUENCY 1000 // 1ms

// Interrupt Priorities
#define PRIORITY_TIMER2  8
#define PRIORITY_TIMER3  8
#define PRIORITY_TIMER4  8
#define PRIORITY_TIMER5  8
#define PRIORITY_TIMER6  8
#define PRIORITY_TIMER7  8



#endif /* CONFIG_H_ */
