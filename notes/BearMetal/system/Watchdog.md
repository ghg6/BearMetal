### IWDG->KR (Key Register) 
These are the key values that allows us to set/start the watchdog
0x5555 enables access to the register
0xCCCC starts the watchdog
0xAAAA must be written to the watchdog at regular intervals to keep counting down, otherwise a reset will be triggered

### IWDG->PR (Prescaler Register)
This value sets the prescaler for the LSI oscillator
000: divider /4 001: divider /8 010: divider /16 011: divider /32 100: divider /64 101: divider /128 110: divider /256 111: divider /256

### IWDG->RLR (Reload Register)
This determines the value to be loaded to the counter each time the KR is set to 0xAAAA, and then counts down from this value. Time our is a function of this and PR