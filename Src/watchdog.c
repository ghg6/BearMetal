/*
 * watchdog.c
 *
 *  Created on: Feb 15, 2026
 *      Author: ghrug
 */

#include "watchdog.h"

void iwdg_init(IWDG_PRESCALER_VALUE prescaler, uint16_t counter)
{
    // Freeze the IWDG counter whenever the debugger halts the core.
    // Without this, the watchdog keeps counting while you sit on a
    // breakpoint and resets the chip after ~2 s, which looks like a
    // random crash. The DBGMCU freeze bit has no effect unless a
    // debugger is attached, so it is safe to leave set in release.
    DBGMCU->APB1FZ |= DBGMCU_APB1_FZ_DBG_IWDG_STOP;

    // Prevents system hang if code crashes
	IWDG->KR = 0x5555; // Enable Access

	IWDG->PR = prescaler; // Defined in config.h

	if (counter >= 4095) counter = 4095; // 12 bit max value
	IWDG->RLR = counter;

	//while (IWDG->SR & (IWDG_SR_PVU | IWDG_SR_RVU));  // wait for latch
	IWDG->KR = 0xcccc; // Activate watchdog
}

void kick_watchdog(void)
{
	IWDG->KR = 0xaaaa;
}


