/*
 * dma_drv.h
 *
 *  Created on: Mar 28, 2026
 *      Author: ghrug
 */

#ifndef DMA_DRV_H_
#define DMA_DRV_H_

#include "global.h"

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

typedef struct {
	uint8_t half_transfer : 1;
	uint8_t transfer_complete : 1;
	uint8_t transfer_error : 1;
	uint8_t direct_mode_error : 1;
	uint8_t fifo_error : 1;
} DMA_Interrupt_Cfg;

typedef struct {
	DMA_TypeDef *dma;
} DMA_cfg;

typedef struct {
	DMA_TypeDef *dma;
	DMA_Stream_TypeDef* stream;
	DMA_Interrupt_Cfg interrupt_cfg;
	uint32_t src_addr;
	uint32_t dst_addr;
	uint32_t size;           // Number of items
	uint8_t direction;       // P2M, M2P, M2M
	uint8_t data_width;      // 8, 16, 32 bit
	uint8_t circular;        // 1 for continuous
	uint8_t priority;
} DMA_Stream_cfg;

typedef struct {
	DMA_Stream_cfg *cfg;
}DMA_StreamObj;

/*
 * Function Prototypes
 */

int8_t dma_stream_init(DMA_StreamObj);
int8_t dma_read(DMA_StreamObj *stream);
int8_t dma_clear_flag(DMA_StreamObj *stream, DMA_Interrupt interrupt);



#endif /* DMA_DRV_H_ */
