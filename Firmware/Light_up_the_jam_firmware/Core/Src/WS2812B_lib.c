
#include "WS2812B_lib.h"

const uint16_t LED_ON = 0xffff;
const uint16_t LED_OFF = 0x0000;

uint16_t LED_COLOR_BUFFER [ LED_COLOR_BUFFER_SIZE ] = {0};

uint8_t UPDATE_BUFFER_FLAG = 0;

void effectOneColor(struct channelParams *channel_param)
{
	for(int i = 0; i < LED_NUMBER; i++)
	{
		setLEDcolor(LED_COLOR_BUFFER, channel_param->channel
									, i,
									channel_param->one_color_r,
									channel_param->one_color_g,
									channel_param->one_color_b);
	}
}

void effectOneColorDim(struct channelParams *channel_param)
{
	if(channel_param->one_color_dim_r_flag == 1)
	{
		if(channel_param->one_color_dim_r_dir == 0)
		{
			channel_param->one_color_dim_r += channel_param->one_color_dim_increment;
			if(channel_param->one_color_dim_r >= 255 - channel_param->one_color_dim_increment)
			{
				channel_param->one_color_dim_r_dir = 1;
			}
		}
		else
		{
			channel_param->one_color_dim_r -= channel_param->one_color_dim_increment;
			if(channel_param->one_color_dim_r <= channel_param->one_color_dim_increment)
			{
				channel_param->one_color_dim_r_dir = 0;
			}
		}
	}

	if(channel_param->one_color_dim_g_flag == 1)
	{
		if(channel_param->one_color_dim_g_dir == 0)
		{
			channel_param->one_color_dim_g += channel_param->one_color_dim_increment;
			if(channel_param->one_color_dim_g >= 255 - channel_param->one_color_dim_increment)
			{
				channel_param->one_color_dim_g_dir = 1;
			}
		}
		else
		{
			channel_param->one_color_dim_g -= channel_param->one_color_dim_increment;
			if(channel_param->one_color_dim_g <= channel_param->one_color_dim_increment)
			{
				channel_param->one_color_dim_g_dir = 0;
			}
		}
	}

	if(channel_param->one_color_dim_b_flag == 1)
	{
		if(channel_param->one_color_dim_b_dir == 0)
		{
			channel_param->one_color_dim_b += channel_param->one_color_dim_increment;
			if(channel_param->one_color_dim_b >= 255 - channel_param->one_color_dim_increment)
			{
				channel_param->one_color_dim_b_dir = 1;
			}
		}
		else
		{
			channel_param->one_color_dim_b -= channel_param->one_color_dim_increment;
			if(channel_param->one_color_dim_b <= channel_param->one_color_dim_increment)
			{
				channel_param->one_color_dim_b_dir = 0;
			}
		}
	}

	for(int i = 0; i < LED_NUMBER; i++)
	{
		setLEDcolor(LED_COLOR_BUFFER, channel_param->channel
									, i,
									channel_param->one_color_dim_r,
									channel_param->one_color_dim_g,
									channel_param->one_color_dim_b);
	}
}


void effectUpDown(struct channelParams *channel_param)
{
	for(int i = channel_param->up_down_current; i < channel_param->up_down_length + channel_param->up_down_current; i++)
	{
		setLEDcolor(LED_COLOR_BUFFER, channel_param->channel
									, i,
									channel_param->up_down_color_r,
									channel_param->up_down_color_g,
									channel_param->up_down_color_b);
	}

	if(channel_param->up_down_add_or_sub == 0)
	{
		channel_param->up_down_current++;
	}
	if(channel_param->up_down_add_or_sub == 1)
	{
		channel_param->up_down_current--;
	}

	if(channel_param->up_down_current >= LED_NUMBER - channel_param->up_down_length)
	{
		channel_param->up_down_add_or_sub = 1;
	}
	if(channel_param->up_down_current <= 0)
	{
		channel_param->up_down_add_or_sub = 0;
	}
}

void effectUpDownColorChange(struct channelParams *channel_param)
{
	for(int i = channel_param->up_down_current; i < channel_param->up_down_length + channel_param->up_down_current; i++)
	{
		setLEDcolor(LED_COLOR_BUFFER, channel_param->channel
									, i,
									128 + i * 3,
									128 - i * 3,
									i * 3);
	}

	if(channel_param->up_down_add_or_sub == 0)
	{
		channel_param->up_down_current++;
	}
	if(channel_param->up_down_add_or_sub == 1)
	{
		channel_param->up_down_current--;
	}

	if(channel_param->up_down_current >= LED_NUMBER - channel_param->up_down_length)
	{
		channel_param->up_down_add_or_sub = 1;
	}
	if(channel_param->up_down_current <= 0)
	{
		channel_param->up_down_add_or_sub = 0;
	}
}

void effectNothing(struct channelParams *channel_param)
{
	return;
}

void effectSetOneLedColor(struct channelParams *channel_param)
{
	static unsigned char i = 0;
	setLEDcolor(LED_COLOR_BUFFER, channel_param->channel
										, i,
										255,
										0x00,
										0);
	i = (i+1)%LED_NUMBER;
}

void setLEDcolor(uint16_t* buffer, uint8_t channel, uint32_t ledNumber, uint8_t g, uint8_t r, uint8_t b)
{
	//This function can be optimized
	uint16_t channelSelector = 1 << channel;

	for(uint8_t i = 0; i < 8; i ++)
	{
		if(r & (((uint8_t)(0x80)) >> i))
			buffer[ledNumber * 24 + i + 1] 		|= channelSelector;

		if(g & (((uint8_t)(0x80)) >> i))
			buffer[ledNumber * 24 + i + 8 + 1]  |= channelSelector;

		if(b & (((uint8_t)(0x80)) >> i))
			buffer[ledNumber * 24 + i + 16 + 1] |= channelSelector;
	}
}

void initDMA(void)
{

	RCC->AHB1ENR |= RCC_AHB1ENR_DMA2EN;

	DMA2->LIFCR = 0xffffffff;
	//DMA2->HIFCR = 0xffffffff;

	//DMA2 Stream 1 channel 0
	//DMA2->LIFCR |= (DMA_LIFCR_CTCIF1);

	DMA2_Stream1->CR |= DMA_SxCR_CHSEL_2 |
						DMA_SxCR_CHSEL_1 |
						DMA_SxCR_MSIZE_0 |
						DMA_SxCR_PSIZE_0 |
						   //DMA_SxCR_MINC |
						   //DMA_SxCR_CIRC |
						  DMA_SxCR_DIR_0;

	DMA2_Stream1->NDTR = LED_COLOR_BUFFER_SIZE;
	DMA2_Stream1->PAR = (uint32_t*)&(GPIOB->ODR);
	DMA2_Stream1->M0AR = (uint16_t*)&LED_ON;//(uint16_t*)LED_TOGGLE;
	DMA2_Stream1->FCR = 0;
	DMA2_Stream1->CR |= DMA_SxCR_EN;

	//DMA2 Stream2 channel
	//DMA2->LIFCR |= (DMA_LIFCR_CTCIF2);

	DMA2_Stream2->CR |= DMA_SxCR_CHSEL_2 |
						DMA_SxCR_CHSEL_1 |
						DMA_SxCR_MSIZE_0 |
						DMA_SxCR_PSIZE_0 |
						   DMA_SxCR_MINC |
						 //DMA_SxCR_CIRC |
						   DMA_SxCR_DIR_0;

	DMA2_Stream6-> CR |= (DMA_SxCR_TCIE);
	DMA2_Stream2->NDTR = LED_COLOR_BUFFER_SIZE;
	DMA2_Stream2->PAR = (uint32_t*)&(GPIOB->ODR);
	DMA2_Stream2->M0AR = (uint16_t*)LED_COLOR_BUFFER;

	NVIC_SetPriority(DMA2_Stream6_IRQn, 0);
	NVIC_EnableIRQ(DMA2_Stream6_IRQn);

	DMA2_Stream1->FCR = 0;
	DMA2_Stream2->CR |= DMA_SxCR_EN;

	//DMA2 Stream6 channel 6
	//DMA2->HIFCR |= (DMA_HIFCR_CTCIF6);

	DMA2_Stream6->CR |= DMA_SxCR_CHSEL_2 |
						DMA_SxCR_CHSEL_1 |
						DMA_SxCR_MSIZE_0 |
						DMA_SxCR_PSIZE_0 |
						   //DMA_SxCR_MINC |
						   //DMA_SxCR_CIRC |
						  DMA_SxCR_DIR_0;

	DMA2_Stream6->NDTR = LED_COLOR_BUFFER_SIZE;
	DMA2_Stream6->PAR = (uint32_t*)&(GPIOB->ODR);
	DMA2_Stream6->M0AR = (uint16_t*)&LED_OFF;
	DMA2_Stream1->FCR = 0;
	DMA2_Stream6->CR |= DMA_SxCR_EN;

}

void initTIM1(void)
{

	RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;

	//TIM1->CR1 |= TIM_CR1_DIR;
	TIM1->DIER |= TIM_DIER_CC1DE | TIM_DIER_CC2DE | TIM_DIER_CC3DE;//TIM_DIER_CC1IE;

	TIM1->PSC = 0;
	TIM1->ARR = 63;

	TIM1->CCR1 = 0;
	TIM1->CCR2 = 21;
	TIM1->CCR3 = 42;

	//TIM1->CR1 |= TIM_CR1_CEN;
}

void initTIM2(void)
{
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;

	TIM2->ARR = (1 << 22);//period of around 80 mS
	TIM2->DIER |= TIM_DIER_UIE;

	NVIC_SetPriority (TIM2_IRQn, 1);
	NVIC_EnableIRQ (TIM2_IRQn);

	TIM2->CR1 &= ~(TIM_CR1_CEN);//At the beginning TIM2 is not enabled
}

void DMA2_Stream6_IRQHandler(void)
{
	if(DMA2->HISR & DMA_HIFCR_CTCIF6)
	{
		//HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
		TIM1->CR1 &= ~(TIM_CR1_CEN);

		//Set update buffer flag
		//buffer update must be done in less than TIM2 overflow period
		UPDATE_BUFFER_FLAG = 1;

		TIM2->CR1  |= TIM_CR1_CEN;
		DMA2->HIFCR |= (DMA_HIFCR_CTCIF6);
	}
}


void TIM2_IRQHandler(void)
{
	if(TIM2->SR & TIM_SR_UIF)
	{
		//HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
		TIM2->SR &= ~(TIM_SR_UIF);
		TIM2->CR1 &= ~(TIM_CR1_CEN);

		DMA2->LIFCR = 0xffffffff;

		DMA2_Stream1->CR |= DMA_SxCR_EN;
		DMA2_Stream2->CR |= DMA_SxCR_EN;
		DMA2_Stream6->CR |= DMA_SxCR_EN;

		//UART clear buffer


		TIM1->CR1 |= TIM_CR1_CEN;
	}
}

void startLEDBufferTransmission(void)
{
	TIM1->CR1 |= (TIM_CR1_CEN);
}

void stopLEDBufferTransmission(void)
{
	TIM1->CR1 &= ~(TIM_CR1_CEN);
}

