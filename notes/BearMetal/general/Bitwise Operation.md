### Set a Bit |=

```C
SCB->CPACR |= (0xFu << 20);
```

0xFu == 0b1111. Shifting left 20 bits means bits 20-23 will be set to 1

|= sets those bits without changing the other bits in the register