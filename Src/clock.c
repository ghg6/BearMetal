/*
 * clock.c
 *
 *  Created on: Feb 14, 2026
 *      Author: ghrug
 */

#include "clock.h"

// CMSIS global variable: core clock frequency
// This is initialized to HSI default, then updated by clock_init()
uint32_t SystemCoreClock = HSI_FREQUENCY;

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
    SystemCoreClock = CPU_FREQUENCY;

    // Disable HSI as it's no longer needed (optional power saving)
    RCC->CR &= ~RCC_CR_HSION;

    // Ensure memory operations complete
    __DSB();
}


