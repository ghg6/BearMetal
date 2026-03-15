
### CEN

### UDIS
ARPE is only for the ARR (period) register. If you need to update multiple registers at once, like CCR duty cycle, this allows you to disable updates. Setting to 0 re-enables updates at the next update event
### URS (Update Request Source)


### OPM (One Pulse Mode)
This is used when you want a timed one off event

### DIR (Direction)
Up count or down count. This determines which edge of the pulse you anchor your edge to (leading or trailing)

### CMS (Center Aligned Mode Selection)

### ARPE (Auto-Reload Preload Enable)
This contrrols whether the ARR (Auto-Reload Register) is buffered. If set to 1 it won't update until the end of the period. This is important as changing PWM mid period can cause glitches

### CKD (Clock Division)

### UIFREMAP (UIF Remapping)
