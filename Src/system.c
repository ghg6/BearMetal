/*
 * global.c
 *
 *  Created on: Feb 7, 2026
 *      Author: ghrug
 */
#include <system.h>

void fpu_enable(void)
{
    // Enable CP10 and CP11 full access (Cortex-M7 FPU)
    SCB->CPACR |= (0xFu << 20);

    // Flush pipeline / ensure effect takes place immediately
    __ISB();
    __DSB();
}

void cache_enable(void)
{
    SCB_EnableICache();   // invalidates + enables I-cache
    SCB_EnableDCache();   // invalidates + enables D-cache
}

void systick_init(uint32_t cpu_hz, uint32_t tick_hz)
{
    SysTick->LOAD = (cpu_hz / tick_hz) - 1U;   // RVR
    SysTick->VAL  = 0U;       	                 // CVR (clear current + COUNTFLAG)
    SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk // processor clock
                  | SysTick_CTRL_TICKINT_Msk   // enable SysTick exception
                  | SysTick_CTRL_ENABLE_Msk;   // start
}



void nvic_init(void)
{
    // Set interrupt priorities
    // Enable/disable specific interrupts
	#ifdef INC_FREERTOS_H
	NVIC_SetPriority(SysTick_IRQn, configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY);
	#endif
}

void watchdog_init(void)
{
    // Timeout ~2 seconds
    // Prevents system hang if code crashes
}

void mpu_init(void)
 {
     // Disable MPU during configuration
     MPU->CTRL = 0;

     // Region 0: Flash (0x08000000, 2MB)
     MPU->RBAR = 0x08000000 | 0 | MPU_RBAR_VALID_Msk;
     MPU->RASR = (1 << 0)           // ENABLE
               | (20 << 1)          // SIZE: 2^(20+1) = 2MB
               | (0b101 << 24)          // AP: Privileged RO, User none
               | (0b1 << 20)          // C: Cacheable
               | (0b0 << 28);         // XN: Executable

     // Region 1: RAM (0x20000000, 512KB)
     MPU->RBAR = 0x20000000 | 1 | MPU_RBAR_VALID_Msk;
     MPU->RASR = (1 << 0)           // ENABLE
               | (18 << 1)          // SIZE: 2^(18+1) = 512KB
               | (0b011 << 24)          // AP: Privileged RW, User none
               | (0b1 << 20)          // C: Cacheable
               | (0b1 << 28);         // XN: No execute (data only)

     // Region 2: Peripherals (0x40000000, 512MB)
     MPU->RBAR = 0x40000000 | 2 | MPU_RBAR_VALID_Msk;
     MPU->RASR = (1 << 0)           // ENABLE
               | (28 << 1)          // SIZE: 2^(28+1) = 512MB
               | (0b011 << 24)          // AP: Privileged RW, User none
               | (0b0 << 20)          // C: Not cacheable
               | (0b1 << 21)          // B: Bufferable
               | (0b1 << 28);         // XN: No execute

     // Enable MPU with privileged default background
     MPU->CTRL = (1 << 0) | (1 << 2);  // ENABLE and PRIVDEFENA
 }

void gpio_init(void)
{
    // LED pins, button pins, etc.
}

void power_init(void)
{
    // Sleep modes for low-power operation
    // Configure voltage regulator
}

void HardFault_Handler(void)
{
    // Log error, reset, or halt gracefully
}

void MemManage_Handler(void)
{
    // Handle MPU violations
}

void system_init(void)
{
    // Order matters: enable FPU before any float code can run
    fpu_enable();

    // Configure clocks to 216 MHz before other operations
    clock_init();

    // Enable caches for improved performance at high frequency
    cache_enable();

    mpu_init();

    // Only enable systick if not using RTOS
	#ifndef USING_RTOS
    //systick_init(CPU_FREQUENCY, TICK_FREQUENCY);
    timer_init(CPU_FREQUENCY, TICK_FREQUENCY);
	#endif
}



