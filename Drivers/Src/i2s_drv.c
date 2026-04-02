/*
 * i2s_drv.c
 *
 *  Created on: Apr 1, 2026
 *      Author: ghrug
 */

#include "i2s_drv.h"

int8_t i2s_init(SPI_TypeDef *spi, I2S_cfg *cfg) {

	// Check if peripheral is active
	if (rcc_spi_is_enabled(spi)) {
	        if (spi->I2SCFGR & (1 << 10)) return -1; // Already running
	} else {
		rcc_enable_spi(spi);
	}

	// Reset registers
	spi->I2SCFGR = 0;
	spi->I2SPR   = 0;

	// I2S Configuration Register
	spi->I2SCFGR = (1 << 11)
			| (cfg->mode << 8)
			| (cfg->i2s_standard << 4)
			| (cfg->clock_polarity << 3)
			| (cfg->data_length << 1)
			| (cfg->channel_length << 0);

	// I2S Prescaler Register
	spi->I2SPR = (cfg->mck_output_enable << 9) | (cfg->prescaler_odd << 8) | (cfg->prescaler_div << 0);

	// DMA configuration
	if (cfg->dma_en) {
	    spi->CR2 &= ~(3 << 0); // Clear RXDMAEN and TXDMAEN
	    if (cfg->mode == MASTER_TRANSMIT || cfg->mode == SLAVE_TRANSMIT) {
	        spi->CR2 |= (1 << 1); // TXDMAEN
	    } else {
	        spi->CR2 |= (1 << 0); // RXDMAEN
	    }
	}
	spi->I2SCFGR |= (1 << 10); // Enable Peripheral

	return(0);
}


