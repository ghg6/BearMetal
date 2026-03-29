### Common Pitfalls

- **Buffer alignment** — Some DMA controllers require buffers aligned to their transfer width. A 32-bit DMA transfer to a non-word-aligned address will fault or corrupt data silently.
- **Modifying a live buffer** — Writing into a buffer while DMA is reading from it causes race conditions. Always use double buffering or only touch the half the DMA isn't currently using.
- **Forgetting to enable the DMA clock** — On STM32 and similar, DMA is a peripheral with its own clock gate. A very common cause of "DMA does nothing."
- **Stack-allocated buffers** — Placing DMA buffers on the stack is dangerous; the buffer disappears when the function returns, but the DMA keeps writing to that address. Always make DMA buffers `static` or global.
- **Cache issues on M7** — As described above, always handle cache coherency explicitly.