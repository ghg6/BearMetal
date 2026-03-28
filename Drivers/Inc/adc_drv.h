/*
 * adc_drv.h
 *
 *  Created on: Mar 15, 2026
 *      Author: ghrug
 */

#ifndef ADC_DRV_H_
#define ADC_DRV_H_

#include "global.h"

// Error Codes

typedef enum {
	ADC_OK,
	ADC_INIT_ERR,
	CHANNEL_ERR,
	RANK_ERR,
} ADC_CHANNEL_ERR;

// ADC Config Parameters

typedef enum {
	ADC_PS_TWO,
	ADC_PS_FOUR,
	ADC_PS_SIX,
	ADC_PS_EIGHT
}ADC_prescaler;

typedef enum {
	TWELVE_BIT,
	TEN_BIT,
	EIGHT_BIT,
	SIX_BIT,
} ADC_resolution;

typedef enum {
	LEFT,
	RIGHT
} ADC_Alignment;

typedef enum {
	CYCLE_3,
	CYCLE_15,
	CYCLE_28,
	CYCLE_56,
	CYCLE_84,
	CYCLE_112,
	CYCLE_144,
	CYCLE_480,
} ADC_Sampling;

typedef struct {
	uint8_t prescaler;
} ADC_Common_cfg;

typedef struct {

	uint8_t resolution;
	uint8_t alignment;


} ADC_cfg;

typedef struct {
	uint8_t F_init;
	uint8_t N_channels;
	ADC_TypeDef *adc;
} ADC_State;

typedef struct {
	ADC_cfg adc;
	uint8_t sampling;
	uint8_t channel;
} ADC_Channel_cfg;

// Function prototypes

void adc_common_init(ADC_Common_cfg *cfg);

void adc_enable(ADC_State *state, ADC_cfg *cfg);
int8_t adc_disable(ADC_State *state);

uint8_t adc_channel_enable(ADC_State *state, ADC_Channel_cfg *cfg, uint8_t rank);




#endif /* ADC_DRV_H_ */
