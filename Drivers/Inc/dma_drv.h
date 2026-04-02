/*
 * dma_drv.h
 *
 *  Created on: Mar 28, 2026
 *      Author: ghrug
 */

#ifndef DMA_DRV_H_
#define DMA_DRV_H_

#include "global.h"
//#include "dma_config.h"

//#define DMA1_BASE 			0x40026000

#define DMA1_STREAM0_BASE 	0x40026010
#define DMA2_STREAM0_BASE	0x40026410

#define DMA1_STREAM1_BASE 	0x40026028
#define DMA1_STREAM3_BASE 	0x40026040
#define DMA1_STREAM4_BASE 	0x40026058
#define DMA1_STREAM5_BASE 	0x40026070
#define DMA1_STREAM6_BASE 	0x40026088
#define DMA1_STREAM7_BASE 	0x400260a0
#define DMA1_STREAM8_BASE 	0x400260b8

typedef enum {
	DMA_ENABLED_ERROR,
	DMA_ADDRESS_ERROR,
	DMA_SIZE_ERROR,
	DMA_FIFO_CONFIG_ERROR
} DMA_Error;

typedef enum {
	ONESHOT,
	CIRCULAR,
	DOUBLEBUF,
} TransferMode;

typedef enum {
	BIT_8,
	BIT_16,
	BIT_32,
} DataWidth; // This could potentially be a global type

typedef enum {
	P2M,
	M2P,
	M2M,
} DMA_Direction;

typedef enum {
	FEIF,
	DMEIF,
	TEIF,
	HTIF,
	TCIF,
} DMA_Interrupt;

typedef enum {
	FIFO_14_FULL,
	FIFO_12_FULL,
	FIFO_34_FULL,
	FIFO_FULL
} DMA_FIFO_Threshold;

typedef struct {
	uint8_t half_transfer : 1;
	uint8_t transfer_complete : 1;
	uint8_t transfer_error : 1;
	uint8_t direct_mode_error : 1;
	uint8_t reserve : 1;
	uint8_t fifo_error : 1;
} DMA_Interrupt_Cfg;

typedef struct {

	// CMSIS Header objects
	DMA_TypeDef *dma;
	DMA_Stream_TypeDef* stream;

	// Defined Configurations
	DMA_Interrupt_Cfg interrupt_cfg;
	uint32_t src_addr;
	uint32_t dst_addr;
	uint32_t dst_addr_dbuf;
	uint32_t size;           // Number of items
	uint8_t direction;       // P2M, M2P, M2M
	uint8_t data_width;      // 8, 16, 32 bit
	uint8_t transfer_mode;   // ONESHOT, CIRCULAR, DOUBLEBUF
	uint8_t priority;
	uint8_t fifo;
	uint8_t fifo_threshold;

	// Init values for performance
	volatile uint32_t *isr_reg;    // points to LISR or HISR
	volatile uint32_t *ifcr_reg;   // points to LIFCR or HIFCR
	uint32_t flag_offset;          // pre-shifted bit position per stream

} DMA_StreamObj;

//typedef struct {
//	DMA_Stream_cfg *cfg;
//}DMA_StreamObj;

/*
 * Function Prototypes
 */

void dma_low_level_init(void);

int8_t dma_stream_init(DMA_StreamObj *stream_obj);


static inline int8_t dma_read_flag(DMA_StreamObj *stream_obj, DMA_Interrupt interrupt_pos)
{
	return (*stream_obj->isr_reg >> (stream_obj->flag_offset + interrupt_pos)) & 0x1;
}

static inline int8_t dma_clear_flag(DMA_StreamObj *stream_obj, DMA_Interrupt interrupt_pos)
{
	*stream_obj->ifcr_reg = (1 << (stream_obj->flag_offset + interrupt_pos));
	return(1);
}

#ifdef DMA1_STREAM0_EN
DMA_StreamObj dma1_stream0;
#endif /* DMA1_STREAM0_EN */


#endif /* DMA_DRV_H_ */
