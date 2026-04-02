/*
 * dma_drv.c
 *
 *  Created on: Mar 28, 2026
 *      Author: ghrug
 */

#include "dma_drv.h"

static const uint8_t dma_flag_bitpos[4] = { 0, 6, 16, 22 };

void dma_low_level_init()
{

}

int8_t _dma_isr_configure(DMA_StreamObj *stream_obj)
{

	if (stream_obj->stream->CR & 0x1) return(-1);

	DMA_Stream_TypeDef *stream = stream_obj->stream;

	if (stream_obj->interrupt_cfg.transfer_complete == 1) stream->CR |= (0b1 << 4);
	if (stream_obj->interrupt_cfg.half_transfer == 1) stream->CR |= (0b1 << 3);
	if (stream_obj->interrupt_cfg.transfer_error == 1) stream->CR |= (0b1 << 2);
	if (stream_obj->interrupt_cfg.direct_mode_error == 1) stream->CR |= (0b1 << 1);
	if (stream_obj->interrupt_cfg.fifo_error == 1) stream->FCR |= (0b1 << 7);

	return(1);
}

int8_t dma_stream_init(DMA_StreamObj *stream_obj)
{
	//DMA_Stream_cfg *cfg = stream_obj;
	DMA_Stream_TypeDef *stream = stream_obj->stream;
	uint32_t offset;

	// Ensure stream is disabled before configuring
	if (stream->CR & 0x1) return(DMA_ENABLED_ERROR);
	if ((stream_obj->dst_addr == 0x0 || stream_obj->src_addr == 0x0)) return(DMA_ADDRESS_ERROR);
	if (stream_obj->size == 0) return(DMA_SIZE_ERROR);
	if (stream_obj->fifo_threshold > 3) return(DMA_FIFO_CONFIG_ERROR);

	rcc_enable_dma(stream_obj->dma);

	// Configure addresses
	if (stream_obj->direction == M2P) {
		stream->PAR = stream_obj->dst_addr;
		stream->M0AR = stream_obj->src_addr;
	}
	else {
		stream->PAR = stream_obj->src_addr;
		stream->M0AR = stream_obj->dst_addr;
	}


	// Configure number of data items to transfer
	stream->NDTR = stream_obj->size;

	// Build Control Register (CR)
	uint32_t cr = 0;

	// Direction (bits 6-7): P2M=0b00, M2P=0b01, M2M=0b10
	cr |= (stream_obj->direction << 6);

	// Peripheral and Memory data width (bits 11-12, 13-14)
	// BIT_8=0b00, BIT_16=0b01, BIT_32=0b10
	cr |= ((stream_obj->data_width & 0x3) << 11);  // PSIZE
	cr |= ((stream_obj->data_width & 0x3) << 13);  // MSIZE

	// Priority Level (bits 16-17): 0=Low, 1=Medium, 2=High, 3=Very High
	cr |= ((stream_obj->priority & 0x3) << 16);

	// Transfer Mode
	if (stream_obj->transfer_mode == CIRCULAR) {
		cr |= (1 << 8);
	}
	if (stream_obj->transfer_mode == DOUBLEBUF) {
		cr |= (1 << 18);
		cr |= (1 << 8);
		stream->M1AR = stream_obj->dst_addr_dbuf;
	}

	// Memory increment (bit 10) - always enable for buffers
	if (stream_obj->direction == M2P) {
		cr |= (1 << 10);
	}
	else {
		cr |= (1 << 9);
	}

	// Init stored values for performance
	if (stream_obj->dma == DMA1) {
	    offset = ((uint32_t)stream_obj->stream - DMA1_STREAM0_BASE) / 0x14;
	} else {
	    offset = ((uint32_t)stream_obj->stream - DMA2_STREAM0_BASE) / 0x14;
	}

	if (offset < 4) {
	    stream_obj->isr_reg  = &stream_obj->dma->LISR;
	    stream_obj->ifcr_reg = &stream_obj->dma->LIFCR;
	    stream_obj->flag_offset = dma_flag_bitpos[offset % 4];  // 5 flag bits per stream in LO register
	} else {
	    stream_obj->isr_reg  = &stream_obj->dma->HISR;
	    stream_obj->ifcr_reg = &stream_obj->dma->HIFCR;
	    stream_obj->flag_offset = dma_flag_bitpos[(offset-4) % 4];
	}

	if (stream_obj->fifo == 1) {
		stream->FCR |= (1 << 2) | (stream_obj->fifo_threshold << 0);
	}

	// Write CR (EN bit 0 not set yet)
	stream->CR = cr;

	// Configure interrupts
	_dma_isr_configure(stream_obj);

	// Enable the stream (bit 0)
	stream->CR |= 1;

	return(1);
}

#ifdef DMA1_STREAM0_EN
DMA_StreamObj dma1_stream0 = {
	.dma = DMA1,
	.stream = DMA1_Stream0,
	.interrupt_cfg = {
		.half_transfer = DMA1_STREAM0_HTIF_EN,
		.transfer_complete = DMA1_STREAM0_TCIF_EN,
		.transfer_error = DMA1_STREAM0_TEIF_EN,
		.direct_mode_error = DMA1_STREAM0_DMEIF_EN,
		.fifo_error = DMA1_STREAM0_FEIF_EN,
	},
	.src_addr = DMA1_STREAM0_SRC_ADDR,
	.dst_addr = DMA1_STREAM0_DST_ADDR,
	.size = DMA1_STREAM0_BUFFER_SIZE,
	.direction = DMA1_STREAM0_DIRECTION,
	.data_width = DMA1_STREAM0_DATA_WIDTH,
	.transfer_mode = DMA1_STREAM0_TRANSFER_MODE,
	.priority = DMA1_STREAM0_PRIORITY
};
#endif

#ifdef DMA1_STREAM1_EN
DMA_StreamObj dma1_stream1 = {
	.dma = DMA1,
	.stream = DMA1_Stream1,
	.interrupt_cfg = {
		.half_transfer = DMA1_STREAM1_HTIF_EN,
		.transfer_complete = DMA1_STREAM1_TCIF_EN,
		.transfer_error = DMA1_STREAM1_TEIF_EN,
		.direct_mode_error = DMA1_STREAM1_DMEIF_EN,
		.fifo_error = DMA1_STREAM1_FEIF_EN,
	},
	.src_addr = DMA1_STREAM1_SRC_ADDR,
	.dst_addr = DMA1_STREAM1_DST_ADDR,
	.size = DMA1_STREAM1_BUFFER_SIZE,
	.direction = DMA1_STREAM1_DIRECTION,
	.data_width = DMA1_STREAM1_DATA_WIDTH,
	.transfer_mode = DMA1_STREAM1_TRANSFER_MODE,
	.priority = DMA1_STREAM1_PRIORITY
};
#endif

#ifdef DMA1_STREAM2_EN
DMA_StreamObj dma1_stream2 = {
	.dma = DMA1,
	.stream = DMA1_Stream2,
	.interrupt_cfg = {
		.half_transfer = DMA1_STREAM2_HTIF_EN,
		.transfer_complete = DMA1_STREAM2_TCIF_EN,
		.transfer_error = DMA1_STREAM2_TEIF_EN,
		.direct_mode_error = DMA1_STREAM2_DMEIF_EN,
		.fifo_error = DMA1_STREAM2_FEIF_EN,
	},
	.src_addr = DMA1_STREAM2_SRC_ADDR,
	.dst_addr = DMA1_STREAM2_DST_ADDR,
	.size = DMA1_STREAM2_BUFFER_SIZE,
	.direction = DMA1_STREAM2_DIRECTION,
	.data_width = DMA1_STREAM2_DATA_WIDTH,
	.transfer_mode = DMA1_STREAM2_CIRCULAR,
	.priority = DMA1_STREAM2_PRIORITY
};
#endif

#ifdef DMA1_STREAM3_EN
DMA_StreamObj dma1_stream3 = {
	.dma = DMA1,
	.stream = DMA1_Stream3,
	.interrupt_cfg = {
		.half_transfer = DMA1_STREAM3_HTIF_EN,
		.transfer_complete = DMA1_STREAM3_TCIF_EN,
		.transfer_error = DMA1_STREAM3_TEIF_EN,
		.direct_mode_error = DMA1_STREAM3_DMEIF_EN,
		.fifo_error = DMA1_STREAM3_FEIF_EN,
	},
	.src_addr = DMA1_STREAM3_SRC_ADDR,
	.dst_addr = DMA1_STREAM3_DST_ADDR,
	.size = DMA1_STREAM3_BUFFER_SIZE,
	.direction = DMA1_STREAM3_DIRECTION,
	.data_width = DMA1_STREAM3_DATA_WIDTH,
	.transfer_mode = DMA1_STREAM3_CIRCULAR,
	.priority = DMA1_STREAM3_PRIORITY
};
#endif

#ifdef DMA1_STREAM4_EN
DMA_StreamObj dma1_stream4 = {
	.dma = DMA1,
	.stream = DMA1_Stream4,
	.interrupt_cfg = {
		.half_transfer = DMA1_STREAM4_HTIF_EN,
		.transfer_complete = DMA1_STREAM4_TCIF_EN,
		.transfer_error = DMA1_STREAM4_TEIF_EN,
		.direct_mode_error = DMA1_STREAM4_DMEIF_EN,
		.fifo_error = DMA1_STREAM4_FEIF_EN,
	},
	.src_addr = DMA1_STREAM4_SRC_ADDR,
	.dst_addr = DMA1_STREAM4_DST_ADDR,
	.size = DMA1_STREAM4_BUFFER_SIZE,
	.direction = DMA1_STREAM4_DIRECTION,
	.data_width = DMA1_STREAM4_DATA_WIDTH,
	.transfer_mode = DMA1_STREAM4_CIRCULAR,
	.priority = DMA1_STREAM4_PRIORITY
};
#endif

#ifdef DMA1_STREAM5_EN
DMA_StreamObj dma1_stream5 = {
	.dma = DMA1,
	.stream = DMA1_Stream5,
	.interrupt_cfg = {
		.half_transfer = DMA1_STREAM5_HTIF_EN,
		.transfer_complete = DMA1_STREAM5_TCIF_EN,
		.transfer_error = DMA1_STREAM5_TEIF_EN,
		.direct_mode_error = DMA1_STREAM5_DMEIF_EN,
		.fifo_error = DMA1_STREAM5_FEIF_EN,
	},
	.src_addr = DMA1_STREAM5_SRC_ADDR,
	.dst_addr = DMA1_STREAM5_DST_ADDR,
	.size = DMA1_STREAM5_BUFFER_SIZE,
	.direction = DMA1_STREAM5_DIRECTION,
	.data_width = DMA1_STREAM5_DATA_WIDTH,
	.transfer_mode = DMA1_STREAM5_CIRCULAR,
	.priority = DMA1_STREAM5_PRIORITY
};
#endif

#ifdef DMA1_STREAM6_EN
DMA_StreamObj dma1_stream6 = {
	.dma = DMA1,
	.stream = DMA1_Stream6,
	.interrupt_cfg = {
		.half_transfer = DMA1_STREAM6_HTIF_EN,
		.transfer_complete = DMA1_STREAM6_TCIF_EN,
		.transfer_error = DMA1_STREAM6_TEIF_EN,
		.direct_mode_error = DMA1_STREAM6_DMEIF_EN,
		.fifo_error = DMA1_STREAM6_FEIF_EN,
	},
	.src_addr = DMA1_STREAM6_SRC_ADDR,
	.dst_addr = DMA1_STREAM6_DST_ADDR,
	.size = DMA1_STREAM6_BUFFER_SIZE,
	.direction = DMA1_STREAM6_DIRECTION,
	.data_width = DMA1_STREAM6_DATA_WIDTH,
	.transfer_mode = DMA1_STREAM6_CIRCULAR,
	.priority = DMA1_STREAM6_PRIORITY
};
#endif

#ifdef DMA1_STREAM7_EN
DMA_StreamObj dma1_stream7 = {
	.dma = DMA1,
	.stream = DMA1_Stream7,
	.interrupt_cfg = {
		.half_transfer = DMA1_STREAM7_HTIF_EN,
		.transfer_complete = DMA1_STREAM7_TCIF_EN,
		.transfer_error = DMA1_STREAM7_TEIF_EN,
		.direct_mode_error = DMA1_STREAM7_DMEIF_EN,
		.fifo_error = DMA1_STREAM7_FEIF_EN,
	},
	.src_addr = DMA1_STREAM7_SRC_ADDR,
	.dst_addr = DMA1_STREAM7_DST_ADDR,
	.size = DMA1_STREAM7_BUFFER_SIZE,
	.direction = DMA1_STREAM7_DIRECTION,
	.data_width = DMA1_STREAM7_DATA_WIDTH,
	.transfer_mode = DMA1_STREAM7_CIRCULAR,
	.priority = DMA1_STREAM7_PRIORITY
};
#endif

#ifdef DMA2_STREAM0_EN
DMA_StreamObj dma2_stream0 = {
	.dma = DMA2,
	.stream = DMA2_Stream0,
	.interrupt_cfg = {
		.half_transfer = DMA2_STREAM0_HTIF_EN,
		.transfer_complete = DMA2_STREAM0_TCIF_EN,
		.transfer_error = DMA2_STREAM0_TEIF_EN,
		.direct_mode_error = DMA2_STREAM0_DMEIF_EN,
		.fifo_error = DMA2_STREAM0_FEIF_EN,
	},
	.src_addr = DMA2_STREAM0_SRC_ADDR,
	.dst_addr = DMA2_STREAM0_DST_ADDR,
	.size = DMA2_STREAM0_BUFFER_SIZE,
	.direction = DMA2_STREAM0_DIRECTION,
	.data_width = DMA2_STREAM0_DATA_WIDTH,
	.transfer_mode = DMA2_STREAM0_CIRCULAR,
	.priority = DMA2_STREAM0_PRIORITY
};
#endif

#ifdef DMA2_STREAM1_EN
DMA_StreamObj dma2_stream1 = {
	.dma = DMA2,
	.stream = DMA2_Stream1,
	.interrupt_cfg = {
		.half_transfer = DMA2_STREAM1_HTIF_EN,
		.transfer_complete = DMA2_STREAM1_TCIF_EN,
		.transfer_error = DMA2_STREAM1_TEIF_EN,
		.direct_mode_error = DMA2_STREAM1_DMEIF_EN,
		.fifo_error = DMA2_STREAM1_FEIF_EN,
	},
	.src_addr = DMA2_STREAM1_SRC_ADDR,
	.dst_addr = DMA2_STREAM1_DST_ADDR,
	.size = DMA2_STREAM1_BUFFER_SIZE,
	.direction = DMA2_STREAM1_DIRECTION,
	.data_width = DMA2_STREAM1_DATA_WIDTH,
	.transfer_mode = DMA2_STREAM1_CIRCULAR,
	.priority = DMA2_STREAM1_PRIORITY
};
#endif

#ifdef DMA2_STREAM2_EN
DMA_StreamObj dma2_stream2 = {
	.dma = DMA2,
	.stream = DMA2_Stream2,
	.interrupt_cfg = {
		.half_transfer = DMA2_STREAM2_HTIF_EN,
		.transfer_complete = DMA2_STREAM2_TCIF_EN,
		.transfer_error = DMA2_STREAM2_TEIF_EN,
		.direct_mode_error = DMA2_STREAM2_DMEIF_EN,
		.fifo_error = DMA2_STREAM2_FEIF_EN,
	},
	.src_addr = DMA2_STREAM2_SRC_ADDR,
	.dst_addr = DMA2_STREAM2_DST_ADDR,
	.size = DMA2_STREAM2_BUFFER_SIZE,
	.direction = DMA2_STREAM2_DIRECTION,
	.data_width = DMA2_STREAM2_DATA_WIDTH,
	.transfer_mode = DMA2_STREAM2_CIRCULAR,
	.priority = DMA2_STREAM2_PRIORITY
};
#endif

#ifdef DMA2_STREAM3_EN
DMA_StreamObj dma2_stream3 = {
	.dma = DMA2,
	.stream = DMA2_Stream3,
	.interrupt_cfg = {
		.half_transfer = DMA2_STREAM3_HTIF_EN,
		.transfer_complete = DMA2_STREAM3_TCIF_EN,
		.transfer_error = DMA2_STREAM3_TEIF_EN,
		.direct_mode_error = DMA2_STREAM3_DMEIF_EN,
		.fifo_error = DMA2_STREAM3_FEIF_EN,
	},
	.src_addr = DMA2_STREAM3_SRC_ADDR,
	.dst_addr = DMA2_STREAM3_DST_ADDR,
	.size = DMA2_STREAM3_BUFFER_SIZE,
	.direction = DMA2_STREAM3_DIRECTION,
	.data_width = DMA2_STREAM3_DATA_WIDTH,
	.transfer_mode = DMA2_STREAM3_CIRCULAR,
	.priority = DMA2_STREAM3_PRIORITY
};
#endif

#ifdef DMA2_STREAM4_EN
DMA_StreamObj dma2_stream4 = {
	.dma = DMA2,
	.stream = DMA2_Stream4,
	.interrupt_cfg = {
		.half_transfer = DMA2_STREAM4_HTIF_EN,
		.transfer_complete = DMA2_STREAM4_TCIF_EN,
		.transfer_error = DMA2_STREAM4_TEIF_EN,
		.direct_mode_error = DMA2_STREAM4_DMEIF_EN,
		.fifo_error = DMA2_STREAM4_FEIF_EN,
	},
	.src_addr = DMA2_STREAM4_SRC_ADDR,
	.dst_addr = DMA2_STREAM4_DST_ADDR,
	.size = DMA2_STREAM4_BUFFER_SIZE,
	.direction = DMA2_STREAM4_DIRECTION,
	.data_width = DMA2_STREAM4_DATA_WIDTH,
	.transfer_mode = DMA2_STREAM4_CIRCULAR,
	.priority = DMA2_STREAM4_PRIORITY
};
#endif

#ifdef DMA2_STREAM5_EN
DMA_StreamObj dma2_stream5 = {
	.dma = DMA2,
	.stream = DMA2_Stream5,
	.interrupt_cfg = {
		.half_transfer = DMA2_STREAM5_HTIF_EN,
		.transfer_complete = DMA2_STREAM5_TCIF_EN,
		.transfer_error = DMA2_STREAM5_TEIF_EN,
		.direct_mode_error = DMA2_STREAM5_DMEIF_EN,
		.fifo_error = DMA2_STREAM5_FEIF_EN,
	},
	.src_addr = DMA2_STREAM5_SRC_ADDR,
	.dst_addr = DMA2_STREAM5_DST_ADDR,
	.size = DMA2_STREAM5_BUFFER_SIZE,
	.direction = DMA2_STREAM5_DIRECTION,
	.data_width = DMA2_STREAM5_DATA_WIDTH,
	.transfer_mode = DMA2_STREAM5_CIRCULAR,
	.priority = DMA2_STREAM5_PRIORITY
};
#endif

#ifdef DMA2_STREAM6_EN
DMA_StreamObj dma2_stream6 = {
	.dma = DMA2,
	.stream = DMA2_Stream6,
	.interrupt_cfg = {
		.half_transfer = DMA2_STREAM6_HTIF_EN,
		.transfer_complete = DMA2_STREAM6_TCIF_EN,
		.transfer_error = DMA2_STREAM6_TEIF_EN,
		.direct_mode_error = DMA2_STREAM6_DMEIF_EN,
		.fifo_error = DMA2_STREAM6_FEIF_EN,
	},
	.src_addr = DMA2_STREAM6_SRC_ADDR,
	.dst_addr = DMA2_STREAM6_DST_ADDR,
	.size = DMA2_STREAM6_BUFFER_SIZE,
	.direction = DMA2_STREAM6_DIRECTION,
	.data_width = DMA2_STREAM6_DATA_WIDTH,
	.transfer_mode = DMA2_STREAM6_CIRCULAR,
	.priority = DMA2_STREAM6_PRIORITY
};
#endif

#ifdef DMA2_STREAM7_EN
DMA_StreamObj dma2_stream7 = {
	.dma = DMA2,
	.stream = DMA2_Stream7,
	.interrupt_cfg = {
		.half_transfer = DMA2_STREAM7_HTIF_EN,
		.transfer_complete = DMA2_STREAM7_TCIF_EN,
		.transfer_error = DMA2_STREAM7_TEIF_EN,
		.direct_mode_error = DMA2_STREAM7_DMEIF_EN,
		.fifo_error = DMA2_STREAM7_FEIF_EN,
	},
	.src_addr = DMA2_STREAM7_SRC_ADDR,
	.dst_addr = DMA2_STREAM7_DST_ADDR,
	.size = DMA2_STREAM7_BUFFER_SIZE,
	.direction = DMA2_STREAM7_DIRECTION,
	.data_width = DMA2_STREAM7_DATA_WIDTH,
	.transfer_mode = DMA2_STREAM7_CIRCULAR,
	.priority = DMA2_STREAM7_PRIORITY
};
#endif
