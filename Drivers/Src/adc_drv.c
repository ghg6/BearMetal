/*
 * adc_drv.c
 *
 *  Created on: Mar 15, 2026
 *      Author: ghrug
 */

#include "adc_drv.h"

void adc_common_init(ADC_Common_cfg *cfg) {
	ADC123_COMMON->CCR &= ~(0x3 << 16);  // Clear ADCPRE[1:0]
	ADC123_COMMON->CCR |= (cfg->prescaler << 16);
}

void adc_enable(ADC_State *state, ADC_cfg *cfg)
{
	if (state->F_init == 1) return;

	rcc_enable_adc(state->adc);

	// Clear registers before init
	state->adc->SQR1 = 0;
	state->adc->SQR2 = 0;
	state->adc->SQR3 = 0;
	state->adc->SMPR1 = 0;  // Add this
	state->adc->SMPR2 = 0;  // Add this

	// ADC Resolution
	state->adc->CR1 &= ~(0xF << 24);
	state->adc->CR1 |= (cfg->resolution << 24);

	// ADC Alignment
	state->adc->CR2 &= ~(1 << 11);  // Clear ALIGN
	state->adc->CR2 |= (cfg->alignment << 11);

	// Enable ADC
	state->adc->CR2 |= (0b1 << 0);

	// Read back to verify write completes
	(void)state->adc->CR2;
	for(int i=0; i<10; i++) __NOP();

	state->F_init = 1;
}

int8_t adc_disable(ADC_State *state) {

	// Dont disable adc unless all channel are off
	if (state->N_channels != 0) return(0);

	rcc_disable_adc(state->adc);
	state->adc->CR2 &= ~(0b1 << 0);

	return(1);
}

uint8_t adc_channel_enable(ADC_State *state, ADC_Channel_cfg *cfg, uint8_t rank) {

	if (state->F_init == 0) return(ADC_INIT_ERR);
	if (rank < 1 || rank > 16) return(RANK_ERR);
	if (cfg->channel > 18) return(CHANNEL_ERR);

	if (cfg->channel >= 10) {
		state->adc->SMPR1 &= ~(0x7 << (((uint32_t)cfg->channel - 10) * 3)); // Clear bits first
	    state->adc->SMPR1 |= ((uint32_t)cfg->sampling << (((uint32_t)cfg->channel - 10) * 3));  // Channel 10→bit 0, 11→bit 3, etc
	} else {
		state->adc->SMPR2 &= ~(0x7 << ((uint32_t)cfg->channel * 3)); // Clear bits first
		state->adc->SMPR2 |= ((uint32_t)cfg->sampling << ((uint32_t)cfg->channel * 3));  // Channel 0→bit 0, 1→bit 3, etc
	}

    // Write channel to the correct SQR register and bit offset based on rank
    if (rank <= 6) {
    	state->adc->SQR3 |= ((uint32_t)cfg->channel << ((rank-1) * 5));
    } else if (rank <= 12) {
    	state->adc->SQR2 |= ((uint32_t)cfg->channel << ((rank - 7) * 5));
    } else {
    	state->adc->SQR1 |= ((uint32_t)cfg->channel << ((rank - 13) * 5));
    }


    // Update sequence length in SQR1 L field
    uint8_t current_len = (state->adc->SQR1 >> 20) & 0xF;
    state->adc->SQR1 &= ~(0xF << 20);
    state->adc->SQR1 |= ((current_len + 1) << 20);

    state->N_channels++;

    return(ADC_OK);

}

void adc_channel_disable() {

}


