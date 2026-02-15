
# Flash
The first step is configuring the flash. Otherwise the CPU will try to fetch instructions faster than they can be supplied.
```C
FLASH->ACR |= FLASH_ACR_LATENCY_7WS; // Set 7 wait states 
FLASH->ACR |= FLASH_ACR_PRFTEN; // Enable prefetch buffer 
FLASH->ACR |= FLASH_ACR_ARTEN; // Enable ART accelerator
```
![[Pasted image 20260214113803.png]]
Flash Access Control Register
### Latency
Because the access time is slower than the CPU cycle, the CPU must wait several cycles otherwise it will read garbage

### Prefetch
Enabling this means the buffer will grab the next few set of instructions during code execution. This reduces the practical wait states during execution

### ART Accelerator
Adaptive Real-Time Memory Accelerator caches instructions. It does this based on what was recently used, predicting the codes pattern, and fetches intelligently based on execution history

0000 = zero wait states, 1111 = 15 wait states

# HSE

```c
RCC->CR |= RCC_CR_HSEON;
```
![[Pasted image 20260214122722.png]]
Control clock register

This activates the high speed external (HSE) oscillator the internal oscillator has an accuracy of +/-1-2%, the HSE has an accuracy of +/-10-50 ppm. This applies power to the oscillator amplifier that drives the crystal

```c
while (!(RCC->CR & RCC_CR_HSERDY) && --timeout)
```
This waits for stability. The crystal needs to ramp up to steady state, so without a delay the clock could be unstable and cause a system crash

# Clock Bus Architecture

```c
RCC->CFGR |= (0b0000 << RCC_CFGR_HPRE_Pos) // AHB prescaler = 1
	| (0b101 << RCC_CFGR_PPRE1_Pos) // APB1 prescaler = 4
	| (0b100 << RCC_CFGR_PPRE2_Pos); // APB2 prescaler = 2
```

This determines the scaling value of the various clock buses. Advanced High Performance Bus (AHB) runs at the clock speed for maximum performance. The Advance Peripheral Buses (AHB) run at lower speeds for peripherals that don't require high performance

In the mask, the first bit indicates division enabled. The next two bits represent the dividing number (00=2, 01=4....11=16)

# Clock Switch
```c
RCC->CFGR |= RCC_CFGR_SW_PLL

timeout = 0x4000;
while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL && --timeout)
```
This switches the clock from the default internal clock to the PLL. This does not happen instantaneously so a quick delay is needed. The PLL is the Phase-Locked Loop clock that takes the HSE (or HSI as an input)

# Define Clock Speed
```c
SystemCoreClock = 216000000;
```
The clock speed needs to be defined for the CMSIS library. This allows several timing functions to work correctly

# HSI Disable
```c
RCC->CR &= ~RCC_CR_HSION;
```
This disables the HSI as it is no longer needed while we use the HSE. This saves power, but it could be left on for various reasons such a clock security system (CSS), independent watchdog (IWDG although this usually uses LSI), or quick clock switching.

# Data Synchronization Barrier
This flushes all memory writes before continuing
