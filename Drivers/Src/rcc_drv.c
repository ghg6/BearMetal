/*
 * rcc_drv.c
 *
 *  Created on: Mar 5, 2026
 *      Author: ghrug
 */

#include "rcc_drv.h"

static RCC_GPIO_RefCnt rcc_gpio_ref_cnt;
static RCC_USART_RefCnt rcc_usart_ref_cnt;
static RCC_TIM_RefCnt rcc_tim_ref_cnt;
static RCC_ADC_RefCnt rcc_adc_ref_cnt;
static RCC_DMA_RefCnt rcc_dma_ref_cnt;

uint8_t ref_decrement_check_zero(uint8_t *cnt) {

	// Helper function to reduce checking if decrement is zero

	if (*cnt > 0) {
		(*cnt)--;
	}
	if (*cnt == 0) {
		return(1);
	}
	return(0);
}

void rcc_enable_gpio(GPIO_TypeDef *gpio)
{
    // Enable AHB1 clock for the given GPIO port
    if (gpio == GPIOA){
    	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    	rcc_gpio_ref_cnt.gpioa++;
    }
    else if (gpio == GPIOB) {
    	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
    	rcc_gpio_ref_cnt.gpiob++;
    }
    else if (gpio == GPIOC) {
    	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
    	rcc_gpio_ref_cnt.gpioc++;
    }
    else if (gpio == GPIOD) {
    	RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;
    	rcc_gpio_ref_cnt.gpiod++;
    }
    else if (gpio == GPIOE) {
    	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOEEN;
    	rcc_gpio_ref_cnt.gpioe++;
    }
    else if (gpio == GPIOF) {
    	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOFEN;
    	rcc_gpio_ref_cnt.gpiof++;
    }
    else if (gpio == GPIOG) {
    	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOGEN;
    	rcc_gpio_ref_cnt.gpiog++;
    }
    else if (gpio == GPIOH) {
    	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOHEN;
    	rcc_gpio_ref_cnt.gpioh++;
    }
    else if (gpio == GPIOI) {
    	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOIEN;
    	rcc_gpio_ref_cnt.gpioi++;
    }
    else if (gpio == GPIOJ) {
    	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOJEN;
    	rcc_gpio_ref_cnt.gpioj++;
    }
    else if (gpio == GPIOK) {
    	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOKEN;
    	rcc_gpio_ref_cnt.gpiok++;
    }
    else return;

    // Read-back to ensure the write completes before peripheral access
    (void)RCC->AHB1ENR;
}

void rcc_disable_gpio(GPIO_TypeDef *gpio)
{
	if (gpio == GPIOA) {
		if (ref_decrement_check_zero(&rcc_gpio_ref_cnt.gpioa)) {
			RCC->AHB1ENR &= ~RCC_AHB1ENR_GPIOAEN;
		}
	}
	else if (gpio == GPIOB) {
		if (ref_decrement_check_zero(&rcc_gpio_ref_cnt.gpiob)) {
			RCC->AHB1ENR &= ~RCC_AHB1ENR_GPIOBEN;
		}
	}
	else if (gpio == GPIOC) {
		if (ref_decrement_check_zero(&rcc_gpio_ref_cnt.gpioc)) {
			RCC->AHB1ENR &= ~RCC_AHB1ENR_GPIOCEN;
		}
	}
	else if (gpio == GPIOD) {
		if (ref_decrement_check_zero(&rcc_gpio_ref_cnt.gpiod)) {
			RCC->AHB1ENR &= ~RCC_AHB1ENR_GPIODEN;
		}
	}
	else if (gpio == GPIOE) {
		if (ref_decrement_check_zero(&rcc_gpio_ref_cnt.gpioe)) {
			RCC->AHB1ENR &= ~RCC_AHB1ENR_GPIOEEN;
		}
	}
	else if (gpio == GPIOF) {
		if (ref_decrement_check_zero(&rcc_gpio_ref_cnt.gpiof)) {
			RCC->AHB1ENR &= ~RCC_AHB1ENR_GPIOFEN;
		}
	}
	else if (gpio == GPIOG) {
		if (ref_decrement_check_zero(&rcc_gpio_ref_cnt.gpiog)) {
			RCC->AHB1ENR &= ~RCC_AHB1ENR_GPIOGEN;
		}
	}
	else if (gpio == GPIOH) {
		if (ref_decrement_check_zero(&rcc_gpio_ref_cnt.gpioh)) {
			RCC->AHB1ENR &= ~RCC_AHB1ENR_GPIOHEN;
		}
	}
	else if (gpio == GPIOI) {
		if (ref_decrement_check_zero(&rcc_gpio_ref_cnt.gpioi)) {
			RCC->AHB1ENR &= ~RCC_AHB1ENR_GPIOIEN;
		}
	}
	else if (gpio == GPIOJ) {
		if (ref_decrement_check_zero(&rcc_gpio_ref_cnt.gpioj)) {
			RCC->AHB1ENR &= ~RCC_AHB1ENR_GPIOJEN;
		}
	}
	else if (gpio == GPIOK) {
		if (ref_decrement_check_zero(&rcc_gpio_ref_cnt.gpiok)) {
			RCC->AHB1ENR &= ~RCC_AHB1ENR_GPIOKEN;
		}
	}
}

void rcc_enable_usart(USART_TypeDef *USART)
{
	if (USART == USART2)
	{
		// Enable USART2 clock and GPIO
		RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
		rcc_usart_ref_cnt.usart2++;
		rcc_enable_gpio(GPIOD);
	}
}

void rcc_disable_usart(USART_TypeDef *USART) {
	if (USART == USART2)
	{
		if (ref_decrement_check_zero(&rcc_usart_ref_cnt.usart2)) {
			RCC->APB1ENR &= ~RCC_APB1ENR_USART2EN;
			rcc_disable_gpio(GPIOD);
		}
	}
}

void rcc_enable_timer(TIM_TypeDef *timer) {

	if (timer == TIM1) {
	  RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
	  rcc_tim_ref_cnt.tim1++;
	  (void)RCC->APB2ENR;
	} else if (timer == TIM2) {
	  RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
	  rcc_tim_ref_cnt.tim2++;
	  (void)RCC->APB1ENR;
	} else if (timer == TIM3) {
	  RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
	  rcc_tim_ref_cnt.tim3++;
	  (void)RCC->APB1ENR;
	} else if (timer == TIM4) {
	  RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;
	  rcc_tim_ref_cnt.tim4++;
	  (void)RCC->APB1ENR;
	} else if (timer == TIM5) {
	  RCC->APB1ENR |= RCC_APB1ENR_TIM5EN;
	  rcc_tim_ref_cnt.tim5++;
	  (void)RCC->APB1ENR;
	} else if (timer == TIM6) {
	  RCC->APB1ENR |= RCC_APB1ENR_TIM6EN;
	  rcc_tim_ref_cnt.tim6++;
	  (void)RCC->APB1ENR;
	} else if (timer == TIM7) {
	  RCC->APB1ENR |= RCC_APB1ENR_TIM7EN;
	  rcc_tim_ref_cnt.tim7++;
	  (void)RCC->APB1ENR;
	} else if (timer == TIM8) {
	  RCC->APB2ENR |= RCC_APB2ENR_TIM8EN;
	  rcc_tim_ref_cnt.tim8++;
	  (void)RCC->APB2ENR;
	}

}

void rcc_disable_timer(TIM_TypeDef *timer) {

	if (timer == TIM1) {
		if (ref_decrement_check_zero(&rcc_tim_ref_cnt.tim1)) {
			RCC->APB2ENR &= ~RCC_APB2ENR_TIM1EN;
		}
	} else if (timer == TIM2) {
		if (ref_decrement_check_zero(&rcc_tim_ref_cnt.tim2)) {
			RCC->APB1ENR &= ~RCC_APB1ENR_TIM2EN;
		}
	} else if (timer == TIM3) {
		if (ref_decrement_check_zero(&rcc_tim_ref_cnt.tim3)) {
			RCC->APB1ENR &= ~RCC_APB1ENR_TIM3EN;
		}
	} else if (timer == TIM4) {
		if (ref_decrement_check_zero(&rcc_tim_ref_cnt.tim4)) {
			RCC->APB1ENR &= ~RCC_APB1ENR_TIM4EN;
		}
	} else if (timer == TIM5) {
		if (ref_decrement_check_zero(&rcc_tim_ref_cnt.tim5)) {
			RCC->APB1ENR &= ~RCC_APB1ENR_TIM5EN;
		}
	} else if (timer == TIM6) {
		if (ref_decrement_check_zero(&rcc_tim_ref_cnt.tim6)) {
			RCC->APB1ENR &= ~RCC_APB1ENR_TIM6EN;
		}
	} else if (timer == TIM7) {
		if (ref_decrement_check_zero(&rcc_tim_ref_cnt.tim7)) {
			RCC->APB1ENR &= ~RCC_APB1ENR_TIM7EN;
		}
	} else if (timer == TIM8) {
		if (ref_decrement_check_zero(&rcc_tim_ref_cnt.tim8)) {
			RCC->APB2ENR &= ~RCC_APB2ENR_TIM8EN;
		}
	}
}

void rcc_enable_adc(ADC_TypeDef *adc)
{
	if (adc == ADC1) {
		RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
		rcc_adc_ref_cnt.adc1++;
	} else if (adc == ADC2) {
		RCC->APB2ENR |= RCC_APB2ENR_ADC2EN;
		rcc_adc_ref_cnt.adc2++;
	} else if (adc == ADC3) {
		RCC->APB2ENR |= RCC_APB2ENR_ADC3EN;
		rcc_adc_ref_cnt.adc3++;
	} else return;

	// Read-back to ensure the write completes before peripheral access
	(void)RCC->APB2ENR;
}

void rcc_disable_adc(ADC_TypeDef *adc)
{
	if (adc == ADC1) {
		if (ref_decrement_check_zero(&rcc_adc_ref_cnt.adc1)) {
			RCC->APB2ENR &= ~RCC_APB2ENR_ADC1EN;
		}
	} else if (adc == ADC2) {
		if (ref_decrement_check_zero(&rcc_adc_ref_cnt.adc2)) {
			RCC->APB2ENR &= ~RCC_APB2ENR_ADC2EN;
		}
	} else if (adc == ADC3) {
		if (ref_decrement_check_zero(&rcc_adc_ref_cnt.adc3)) {
			RCC->APB2ENR &= ~RCC_APB2ENR_ADC3EN;
		}
	}
}

void rcc_enable_dma(DMA_TypeDef *dma)
{
	if (dma == DMA1) {
		RCC->AHB1ENR |= RCC_AHB1ENR_DMA1EN;
		rcc_dma_ref_cnt.dma1++;
		(void)RCC->AHB1ENR;  // Read-back
	} else if (dma == DMA2) {
		RCC->AHB1ENR |= RCC_AHB1ENR_DMA2EN;
		rcc_dma_ref_cnt.dma2++;
		(void)RCC->AHB1ENR;
	}
}

void rcc_disable_dma(DMA_TypeDef *dma)
{
	if (dma == DMA1) {
		if (ref_decrement_check_zero(&rcc_dma_ref_cnt.dma1)) {
				RCC->AHB1ENR &= ~RCC_AHB1ENR_DMA1EN;
		}
	} else if (dma == DMA2) {
		if (ref_decrement_check_zero(&rcc_dma_ref_cnt.dma2)) {
				RCC->AHB1ENR &= ~RCC_AHB1ENR_DMA2EN;
		}
	}
}

int8_t rcc_spi_is_enabled(SPI_TypeDef *spi) {

	return(0);
}

void rcc_enable_spi(SPI_TypeDef *spi) {

}


