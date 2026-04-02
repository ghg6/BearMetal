/*
 * i2s_drv.h
 *
 *  Created on: Apr 1, 2026
 *      Author: ghrug
 */

#ifndef I2S_DRV_H_
#define I2S_DRV_H_

#include "global.h"

typedef enum {
	SLAVE_TRANSMIT,
	SLAVE_RECIEVE,
	MASTER_TRANSMIT,
	MASTER_RECIEVE,
} I2S_cfg_mode;

typedef enum {
	I2S_BIT_16,
	I2S_BIT_24,
	I2S_BIT_32,
} I2S_Data_Length;

typedef enum {
	I2S_STANDARD_PHILIPS,
	I2S_STANDARD_MSB,
	I2S_STANDARD_LSB,
	I2S_STANDARD_PCM,
} I2S_Standard;

typedef struct {

	uint8_t mode;
	uint8_t data_length;
	uint8_t channel_length;
	uint8_t i2s_standard;
	uint8_t clock_polarity;

	uint8_t mck_output_enable;
	uint8_t prescaler_div;
	uint8_t prescaler_odd;

	uint8_t dma_en;
} I2S_cfg;

#endif /* I2S_DRV_H_ */
