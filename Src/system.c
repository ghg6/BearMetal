/*
 * global.c
 *
 *  Created on: Feb 7, 2026
 *      Author: ghrug
 */
#include <system.h>

// CMSIS global variable: core clock frequency
// This is initialized to HSI default, then updated by clock_init()
uint32_t SystemCoreClock = 16000000;

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

void clock_init(void)
{
    // Configure Flash latency BEFORE increasing system clock frequency
    // 216 MHz at 3.3V requires 7 wait states (from datasheet)
    FLASH->ACR |= FLASH_ACR_LATENCY_7WS;  // Set 7 wait states
    FLASH->ACR |= FLASH_ACR_PRFTEN;       // Enable prefetch buffer
    FLASH->ACR |= FLASH_ACR_ARTEN;        // Enable ART accelerator

    // Enable High-Speed External oscillator (HSE)
    RCC->CR |= RCC_CR_HSEON;

    // Wait for HSE to be ready (with timeout)
    uint32_t timeout = 0x4000;
    while (!(RCC->CR & RCC_CR_HSERDY) && --timeout)
        ;

    // Configure PLL for 216 MHz operation
    // Input: 8 MHz HSE
    // PLLM = 8:   8 MHz / 8 = 1 MHz (VCO input)
    // PLLN = 432: 1 MHz * 432 = 432 MHz (VCO output)
    // PLLP = 2:   432 MHz / 2 = 216 MHz (system clock)
    // PLLQ = 9:   432 MHz / 9 = 48 MHz (USB/SDMMC)
    RCC->PLLCFGR = RCC_PLLCFGR_PLLSRC_HSE  // HSE as PLL input source
                 | (8 << RCC_PLLCFGR_PLLM_Pos)    // PLLM = 8
                 | (432 << RCC_PLLCFGR_PLLN_Pos)  // PLLN = 432
                 | (0 << RCC_PLLCFGR_PLLP_Pos)    // PLLP = 0 (means divide by 2)
                 | (9 << RCC_PLLCFGR_PLLQ_Pos);   // PLLQ = 9

    // Enable PLL
    RCC->CR |= RCC_CR_PLLON;

    // Wait for PLL lock (with timeout)
    timeout = 0x4000;
    while (!(RCC->CR & RCC_CR_PLLRDY) && --timeout)
        ;

    // Configure AHB and APB prescalers while PLL is locking
    // AHB:  216 MHz (HPRE = 0, prescaler = 1)
    // APB1: 54 MHz (PPRE1 = 5, prescaler = 4, max 54 MHz)
    // APB2: 108 MHz (PPRE2 = 4, prescaler = 2, max 108 MHz)
    RCC->CFGR |= (0b0000 << RCC_CFGR_HPRE_Pos)   // AHB prescaler = 1
              | (0b101 << RCC_CFGR_PPRE1_Pos)  // APB1 prescaler = 4
              | (0b100 << RCC_CFGR_PPRE2_Pos); // APB2 prescaler = 2

    // Switch system clock source to PLL
    RCC->CFGR |= RCC_CFGR_SW_PLL;

    // Wait for clock switch to complete
    timeout = 0x4000;
    while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL && --timeout)
        ;

    // Update CMSIS SystemCoreClock variable
    SystemCoreClock = 216000000;

    // Disable HSI as it's no longer needed (optional power saving)
    RCC->CR &= ~RCC_CR_HSION;

    // Ensure memory operations complete
    __DSB();
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
    // Define memory regions (code, data, peripherals)
    // Set execute/read/write permissions
    // Catch memory corruption early
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

    // Only enable systick if not using RTOS
	#ifndef USING_RTOS
    //systick_init(CPU_FREQUENCY, TICK_FREQUENCY);
    timer_init(CPU_FREQUENCY, TICK_FREQUENCY);
	#endif
}



