```c
void fpu_enable(void)

{

// Enable CP10 and CP11 full access (Cortex-M7 FPU)

SCB->CPACR |= (0xFu << 20);

  

// Flush pipeline / ensure effect takes place immediately

__DSB();

__ISB();

}
```

FPU is enabled through the SCB. This enabled with the Coprocessor access control register.

![[Pasted image 20260212212211.png]]

Bits 20-23 correspond to the bits that activate the FPU

![[Pasted image 20260212212059.png]]
### __DSB()

Forces completion of all explicit memory accesses before continuing. This helps ensure the CPACR write is fully committed before you run any code that might depend on it.

### __ISB()

Flushes the CPU instruction pipeline and makes the core re-fetch instructions with the _new_ processor state (i.e., with FPU access now enabled). Without this, the CPU might keep executing prefetched instructions as if the FPU were still disabled.