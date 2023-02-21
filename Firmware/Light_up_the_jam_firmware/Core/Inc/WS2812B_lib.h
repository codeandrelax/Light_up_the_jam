/*
 * WS2812B_lib.h
 *
 *  Created on: Jan 17, 2023
 *      Author: Damjan
 */

#ifndef INC_WS2812B_LIB_H_
#define INC_WS2812B_LIB_H_

#include "stm32f4xx_hal.h"

#define ONE_COLOR_EFFECT 0
#define UP_DOWN_EFFECT 1
#define UP_DOWN_EFFECT_COLOR_CHANGE 2
#define NO_EFFECT 3
#define ONE_COLOR_EFFECT_DIM 3

#define LED_NUMBER ( 31 )
#define LED_COLOR_BUFFER_SIZE ( LED_NUMBER * 3 * 8 )

#define CHANNEL_NUMBER 10

extern uint8_t UPDATE_BUFFER_FLAG;
extern uint16_t LED_COLOR_BUFFER [ LED_COLOR_BUFFER_SIZE ];

void initTIM1(void);
void initTIM2(void);
void initDMA(void);

void startLEDBufferTransmission(void);
void stopLEDBufferTransmission(void);

typedef struct _channelParams channelParams;

struct channelParams
{
	uint8_t EEFECT;
	uint8_t channel;

	void (*effectExecutor)(struct channelParams*);

	//ONE_COLOR
	uint8_t one_color_r;
	uint8_t one_color_g;
	uint8_t one_color_b;

	//ONE_COLOR_DIM
	uint8_t one_color_dim_r;
	uint8_t one_color_dim_g;
	uint8_t one_color_dim_b;

	uint8_t one_color_dim_r_flag;
	uint8_t one_color_dim_g_flag;
	uint8_t one_color_dim_b_flag;

	uint8_t one_color_dim_increment;

	uint8_t one_color_dim_r_dir;
	uint8_t one_color_dim_g_dir;
	uint8_t one_color_dim_b_dir;

	//UP DOWN EFFECT
	uint8_t up_down_length;
	uint8_t up_down_current;
	uint8_t up_down_add_or_sub;

	uint8_t up_down_color_r;
	uint8_t up_down_color_g;
	uint8_t up_down_color_b;

};

void setLEDcolor(uint16_t* buffer, uint8_t channel, uint32_t ledNumber, uint8_t g, uint8_t r, uint8_t b);

void effectNothing(struct channelParams *channel_param);
void effectOneColor(struct channelParams *channel_param);
void effectUpDown(struct channelParams *channel_param);
void effectUpDownColorChange(struct channelParams *channel_param);
void effectSetOneLedColor(struct channelParams *channel_param);
void effectOneColorDim(struct channelParams *channel_param);
#endif /* INC_WS2812B_LIB_H_ */
