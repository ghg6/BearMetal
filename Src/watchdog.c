/*
 * watchdog.c
 *
 *  Created on: Feb 15, 2026
 *      Author: ghrug
 */

#include "watchdog.h"

void iwdg_init(void)
{
    // Timeout ~2 seconds
    // Prevents system hang if code crashes
	IWDG->KR = 0x5555; // Enable Access
	IWDG->PR = 0b011; // Scale 32
	IWDG->RLR = 2000; // ~2 seconds
	IWDG->KR = 0xcccc; // Activate watchdog
}

void kick_watchdog(void)
{
	IWDG->KR = 0xaaaa;
}

void watchdog_init(void)
{
	iwdg_init();
}


