### Cache Coherency (Cortex-M7 and Up)

On MCUs with data caches (STM32H7, i.MX RT), DMA bypasses the cache and writes directly to RAM. This creates a **coherency hazard**:

- DMA writes fresh data to RAM
- CPU reads _stale data_ from its cache instead
- Your buffer looks unchanged even though DMA updated it

The fix is to either:

- Place DMA buffers in **non-cacheable memory regions** (MPU configuration)
- Manually **invalidate the cache** for the buffer region before reading it

This is one of the most common and confusing bugs when moving from Cortex-M4 to M7.