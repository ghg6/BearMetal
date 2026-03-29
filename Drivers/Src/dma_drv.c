/*
 * dma_drv.c
 *
 *  Created on: Mar 28, 2026
 *      Author: ghrug
 */

#include "dma_drv.h"

int8_t _dma_isr_configure(DMA_Stream_cfg *cfg)
{

	if (cfg->stream->CR & 0x1) return(-1);

	DMA_Stream_TypeDef *stream = cfg->stream;

	if (cfg->interrupt_cfg.half_transfer == 1) stream->CR |= (0b1 << 3);
	if (cfg->interrupt_cfg.transfer_complete == 1) stream->CR |= (0b1 << 4);
	if (cfg->interrupt_cfg.transfer_error == 1) stream->CR |= (0b1 << 2);
	if (cfg->interrupt_cfg.direct_mode_error == 1) stream->CR |= (0b1 << 1);
	if (cfg->interrupt_cfg.fifo_error == 1) stream->FCR |= (0b1 << 7);

	return(1);
}

int8_t dma_stream_init(DMA_StreamObj stream_obj)
{
	DMA_Stream_cfg *cfg = stream_obj.cfg;
	DMA_Stream_TypeDef *stream = cfg->stream;

	// Ensure stream is disabled before configuring
	if (stream->CR & 0x1) return(-1);

	// Configure addresses
	stream->PAR = cfg->src_addr;
	stream->M0AR = cfg->dst_addr;

	// Configure number of data items to transfer
	stream->NDTR = cfg->size;

	// Build Control Register (CR)
	uint32_t cr = 0;

	// Direction (bits 6-7): P2M=0b00, M2P=0b01, M2M=0b10
	cr |= (cfg->direction << 6);

	// Peripheral and Memory data width (bits 11-12, 13-14)
	// BIT_8=0b00, BIT_16=0b01, BIT_32=0b10
	cr |= ((cfg->data_width & 0x3) << 11);  // PSIZE
	cr |= ((cfg->data_width & 0x3) << 13);  // MSIZE

	// Priority Level (bits 16-17): 0=Low, 1=Medium, 2=High, 3=Very High
	cr |= ((cfg->priority & 0x3) << 16);

	// Circular mode (bit 8)
	if (cfg->circular) cr |= (1 << 8);

	// Memory increment (bit 10) - always enable for buffers
	cr |= (1 << 10);

	// Write CR (EN bit 0 not set yet)
	stream->CR = cr;

	// Configure interrupts
	_dma_isr_configure(cfg);

	// Enable the stream (bit 0)
	stream->CR |= 1;

	return(1);
}

int8_t dma_read(DMA_StreamObj *stream)
{

	return(1);
}

int8_t dma_clear_flag(DMA_StreamObj *stream_obj, DMA_Interrupt interrupt_pos)
{
	DMA_TypeDef *dma = stream_obj->cfg->dma;
	DMA_Stream_TypeDef *stream = stream_obj->cfg->stream;

	uint32_t offset;

	if (dma == DMA1) {
		offset = ((uint32_t)&stream->CR - DMA1_STREAM0_BASE)/(0x14);
		if (offset < 4) {
			  dma->LIFCR |= (0b1 << (offset * 5 + interrupt_pos));  // Streams 0-3
		} else {
			  dma->HIFCR |= (0b1 << ((offset - 4) * 5 + interrupt_pos));  // Streams 4-7
		}
	}
	if (dma == DMA2) {
		offset = ((uint32_t)&stream->CR - DMA2_STREAM0_BASE)/(0x14);
		if (offset < 4) {
			  dma->LIFCR |= (0b1 << (offset * 5 + interrupt_pos));  // Streams 0-3
		} else {
			  dma->HIFCR |= (0b1 << ((offset - 4) * 5 + interrupt_pos));  // Streams 4-7
		}
	}

	return(1);
}



