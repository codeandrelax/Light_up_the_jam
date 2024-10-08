



#include "main.h"

UART_HandleTypeDef huart1;

#include "WS2812B_lib.h"

uint8_t received_string[3] = {0};

static const char effect1[]= "E01";
static const char effect2[] = "E02";
static const char effect3[] = "E03";
static const char effect4[] = "E04";
static const char effect5[] = "E05";

static uint8_t effectSelectorFlag = 1;

void effect1Select(void);//Turn off
void effect2Select(void);
void effect3Select(void);
void effect4Select(void);
void effect5Select(void);

void (*effectSelector)(void) = effect3Select;

uint8_t strcmp_v(const int8_t* first, const int8_t* second);

uint8_t strcmp_v(const int8_t* first, const int8_t* second)
{
	uint8_t i = 0;
	while(first[i] == second[i] && i < 3)
	{
		i++;
	}
	return i == 3 ? 1 : 0;
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(strcmp_v(effect1, received_string))
	{
		HAL_UART_Transmit(&huart1, "Efekat 1\n", sizeof("Efekat 1\n"), 100);
		effectSelector = effect1Select;
		effectSelectorFlag = 1;
	}

	if(strcmp_v(effect2, received_string))
	{
		HAL_UART_Transmit(&huart1, "Efekat 2\n", sizeof("Efekat 2\n"), 100);
		effectSelector = effect2Select;
		effectSelectorFlag = 1;
	}

	if(strcmp_v(effect3, received_string))
	{
		HAL_UART_Transmit(&huart1, "Efekat 3\n", sizeof("Efekat 3\n"), 100);
		effectSelector = effect3Select;
		effectSelectorFlag = 1;
	}

	if(strcmp_v(effect4, received_string))
	{
		HAL_UART_Transmit(&huart1, "Efekat 4\n", sizeof("Efekat 4\n"), 100);
		effectSelector = effect4Select;
		effectSelectorFlag = 1;
	}

	if(strcmp_v(effect5, received_string))
	{
		HAL_UART_Transmit(&huart1, "Efekat 5\n", sizeof("Efekat 5\n"), 100);
		effectSelector = effect5Select;
		effectSelectorFlag = 1;
	}

	HAL_UART_Transmit(&huart1, "Interrupt\n", sizeof("Interrupt\n"), 100);
    HAL_UART_Receive_IT(&huart1, received_string, 3);
}

void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART1_UART_Init(void);

struct channelParams channel_params_array[10] = {0};


/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
	HAL_Init();
	SystemClock_Config();

	MX_GPIO_Init();
	MX_USART1_UART_Init();

	HAL_UART_Transmit(&huart1, "Begin\n", 6, 100);
	HAL_UART_Receive_IT (&huart1, received_string, 3);

	initDMA();
	initTIM1();
	initTIM2();

	startLEDBufferTransmission();

	static uint8_t color = 0;

	while (1)
	{
		effectSelector();
		if(UPDATE_BUFFER_FLAG == 1)
		{
			//Clear buffer

			for(int i = 0; i < LED_COLOR_BUFFER_SIZE; i++)
			{
			  LED_COLOR_BUFFER[i] = 0;
			}

			for(int i = 0; i < 10; i++)
			{
			  channel_params_array[i].effectExecutor(&channel_params_array[i]);
			}

			color ++;

			UPDATE_BUFFER_FLAG = 0;
		}
	}
}

void effect1Select(void)
{
	if(effectSelectorFlag == 1)
	{
		channel_params_array[0].channel = 0;
		channel_params_array[0].EEFECT = NO_EFFECT;
		channel_params_array[0].effectExecutor = &effectNothing;

		channel_params_array[1].channel = 1;
		channel_params_array[1].EEFECT = NO_EFFECT;
		channel_params_array[1].effectExecutor = &effectNothing;

		channel_params_array[2].channel = 2;
		channel_params_array[2].EEFECT = NO_EFFECT;
		channel_params_array[2].effectExecutor = &effectNothing;

		channel_params_array[3].channel = 3;
		channel_params_array[3].EEFECT = NO_EFFECT;
		channel_params_array[3].effectExecutor = &effectNothing;

		channel_params_array[4].channel = 4;
		channel_params_array[4].EEFECT = NO_EFFECT;
		channel_params_array[4].effectExecutor = &effectNothing;

		channel_params_array[5].channel = 5;
		channel_params_array[5].EEFECT = NO_EFFECT;
		channel_params_array[5].effectExecutor = &effectNothing;

		channel_params_array[6].channel = 6;
		channel_params_array[6].EEFECT = NO_EFFECT;
		channel_params_array[6].effectExecutor = &effectNothing;

		channel_params_array[7].channel = 7;
		channel_params_array[7].EEFECT = NO_EFFECT;
		channel_params_array[7].effectExecutor = &effectNothing;

		channel_params_array[8].channel = 8;
		channel_params_array[8].EEFECT = NO_EFFECT;
		channel_params_array[8].effectExecutor = &effectNothing;

		channel_params_array[9].channel = 9;
		channel_params_array[9].EEFECT = NO_EFFECT;
		channel_params_array[9].effectExecutor = &effectNothing;
	}
}

void effect2Select(void)
{
	if(effectSelectorFlag == 1)
	{
		channel_params_array[0].channel = 0;
		channel_params_array[0].EEFECT = UP_DOWN_EFFECT_COLOR_CHANGE;
		channel_params_array[0].effectExecutor = &effectUpDownColorChange;
		channel_params_array[0].up_down_color_r = 128;
		channel_params_array[0].up_down_color_g = 255;
		channel_params_array[0].up_down_color_b = 0;
		channel_params_array[0].up_down_length = 5;
		channel_params_array[0].up_down_current = 8;

		channel_params_array[1].channel = 1;
		channel_params_array[1].EEFECT = UP_DOWN_EFFECT_COLOR_CHANGE;
		channel_params_array[1].effectExecutor = &effectUpDownColorChange;
		channel_params_array[1].up_down_color_r = 128;
		channel_params_array[1].up_down_color_g = 255;
		channel_params_array[1].up_down_color_b = 0;
		channel_params_array[1].up_down_length = 5;
		channel_params_array[1].up_down_current = 12;

		channel_params_array[2].channel = 2;
		channel_params_array[2].EEFECT = UP_DOWN_EFFECT_COLOR_CHANGE;
		channel_params_array[2].effectExecutor = &effectUpDownColorChange;
		channel_params_array[2].up_down_color_r = 128;
		channel_params_array[2].up_down_color_g = 255;
		channel_params_array[2].up_down_color_b = 0;
		channel_params_array[2].up_down_length = 5;
		channel_params_array[2].up_down_current = 16;

		channel_params_array[3].channel = 3;
		channel_params_array[3].EEFECT = UP_DOWN_EFFECT_COLOR_CHANGE;
		channel_params_array[3].effectExecutor = &effectUpDownColorChange;
		channel_params_array[3].up_down_color_r = 128;
		channel_params_array[3].up_down_color_g = 255;
		channel_params_array[3].up_down_color_b = 0;
		channel_params_array[3].up_down_length = 5;
		channel_params_array[3].up_down_current = 20;

		channel_params_array[4].channel = 4;
		channel_params_array[4].EEFECT = UP_DOWN_EFFECT_COLOR_CHANGE;
		channel_params_array[4].effectExecutor = &effectUpDownColorChange;
		channel_params_array[4].up_down_color_r = 128;
		channel_params_array[4].up_down_color_g = 255;
		channel_params_array[4].up_down_color_b = 0;
		channel_params_array[4].up_down_length = 5;
		channel_params_array[4].up_down_current = 24;

		channel_params_array[5].channel = 5;
		channel_params_array[5].EEFECT = UP_DOWN_EFFECT_COLOR_CHANGE;
		channel_params_array[5].effectExecutor = &effectUpDownColorChange;
		channel_params_array[5].up_down_color_r = 128;
		channel_params_array[5].up_down_color_g = 255;
		channel_params_array[5].up_down_color_b = 0;
		channel_params_array[5].up_down_length = 5;
		channel_params_array[5].up_down_current = 24;

		channel_params_array[6].channel = 6;
		channel_params_array[6].EEFECT = UP_DOWN_EFFECT_COLOR_CHANGE;
		channel_params_array[6].effectExecutor = &effectUpDownColorChange;
		channel_params_array[6].up_down_color_r = 128;
		channel_params_array[6].up_down_color_g = 255;
		channel_params_array[6].up_down_color_b = 0;
		channel_params_array[6].up_down_length = 5;
		channel_params_array[6].up_down_current = 20;

		channel_params_array[7].channel = 7;
		channel_params_array[7].EEFECT = UP_DOWN_EFFECT_COLOR_CHANGE;
		channel_params_array[7].effectExecutor = &effectUpDownColorChange;
		channel_params_array[7].up_down_color_r = 128;
		channel_params_array[7].up_down_color_g = 255;
		channel_params_array[7].up_down_color_b = 0;
		channel_params_array[7].up_down_length = 5;
		channel_params_array[7].up_down_current = 16;

		channel_params_array[8].channel = 8;
		channel_params_array[8].EEFECT = UP_DOWN_EFFECT_COLOR_CHANGE;
		channel_params_array[8].effectExecutor = &effectUpDownColorChange;
		channel_params_array[8].up_down_color_r = 128;
		channel_params_array[8].up_down_color_g = 255;
		channel_params_array[8].up_down_color_b = 0;
		channel_params_array[8].up_down_length = 5;
		channel_params_array[2].up_down_current = 12;

		channel_params_array[9].channel = 9;
		channel_params_array[9].EEFECT = UP_DOWN_EFFECT_COLOR_CHANGE;
		channel_params_array[9].effectExecutor = &effectUpDownColorChange;
		channel_params_array[9].up_down_color_r = 128;
		channel_params_array[9].up_down_color_g = 255;
		channel_params_array[9].up_down_color_b = 0;
		channel_params_array[9].up_down_length = 5;
		channel_params_array[9].up_down_current = 8;

		effectSelectorFlag = 0;
	}
}

void effect3Select(void)
{
	if(effectSelectorFlag == 1)
	{
		channel_params_array[0].channel = 0;
		channel_params_array[0].EEFECT = ONE_COLOR_EFFECT_DIM;
		channel_params_array[0].effectExecutor = &effectOneColorDim;
		channel_params_array[0].one_color_dim_r = 0;
		channel_params_array[0].one_color_dim_g = 255;
		channel_params_array[0].one_color_dim_b = 128;
		channel_params_array[0].one_color_dim_r_flag = 1;
		channel_params_array[0].one_color_dim_g_flag = 1;
		channel_params_array[0].one_color_dim_b_flag = 1;
		channel_params_array[0].one_color_dim_increment = 1;
		channel_params_array[0].one_color_dim_r_dir = 0;
		channel_params_array[0].one_color_dim_g_dir = 0;
		channel_params_array[0].one_color_dim_b_dir = 0;

		channel_params_array[1].channel = 1;
		channel_params_array[1].EEFECT = ONE_COLOR_EFFECT_DIM;
		channel_params_array[1].effectExecutor = &effectOneColorDim;
		channel_params_array[1].one_color_dim_r = 255;
		channel_params_array[1].one_color_dim_g = 0;
		channel_params_array[1].one_color_dim_b = 128;
		channel_params_array[1].one_color_dim_r_flag = 1;
		channel_params_array[1].one_color_dim_g_flag = 1;
		channel_params_array[1].one_color_dim_b_flag = 1;
		channel_params_array[1].one_color_dim_increment = 1;
		channel_params_array[1].one_color_dim_r_dir = 0;
		channel_params_array[1].one_color_dim_g_dir = 0;
		channel_params_array[1].one_color_dim_b_dir = 0;

		channel_params_array[2].channel = 2;
		channel_params_array[2].EEFECT = ONE_COLOR_EFFECT_DIM;
		channel_params_array[2].effectExecutor = &effectOneColorDim;
		channel_params_array[2].one_color_dim_r = 128;
		channel_params_array[2].one_color_dim_g = 128;
		channel_params_array[2].one_color_dim_b = 128;
		channel_params_array[2].one_color_dim_r_flag = 1;
		channel_params_array[2].one_color_dim_g_flag = 1;
		channel_params_array[2].one_color_dim_b_flag = 1;
		channel_params_array[2].one_color_dim_increment = 1;
		channel_params_array[2].one_color_dim_r_dir = 0;
		channel_params_array[2].one_color_dim_g_dir = 0;
		channel_params_array[2].one_color_dim_b_dir = 0;

		channel_params_array[3].channel = 3;
		channel_params_array[3].EEFECT = ONE_COLOR_EFFECT_DIM;
		channel_params_array[3].effectExecutor = &effectOneColorDim;
		channel_params_array[3].one_color_dim_r = 0;
		channel_params_array[3].one_color_dim_g = 0;
		channel_params_array[3].one_color_dim_b = 128;
		channel_params_array[3].one_color_dim_r_flag = 1;
		channel_params_array[3].one_color_dim_g_flag = 1;
		channel_params_array[3].one_color_dim_b_flag = 1;
		channel_params_array[3].one_color_dim_increment = 1;
		channel_params_array[3].one_color_dim_r_dir = 0;
		channel_params_array[3].one_color_dim_g_dir = 0;
		channel_params_array[3].one_color_dim_b_dir = 0;

		channel_params_array[4].channel = 4;
		channel_params_array[4].EEFECT = ONE_COLOR_EFFECT_DIM;
		channel_params_array[4].effectExecutor = &effectOneColorDim;
		channel_params_array[4].one_color_dim_r = 0;
		channel_params_array[4].one_color_dim_g = 255;
		channel_params_array[4].one_color_dim_b = 0;
		channel_params_array[4].one_color_dim_r_flag = 1;
		channel_params_array[4].one_color_dim_g_flag = 1;
		channel_params_array[4].one_color_dim_b_flag = 1;
		channel_params_array[4].one_color_dim_increment = 1;
		channel_params_array[4].one_color_dim_r_dir = 0;
		channel_params_array[4].one_color_dim_g_dir = 0;
		channel_params_array[4].one_color_dim_b_dir = 0;

		channel_params_array[5].channel = 5;
		channel_params_array[5].EEFECT = ONE_COLOR_EFFECT_DIM;
		channel_params_array[5].effectExecutor = &effectOneColorDim;
		channel_params_array[5].one_color_dim_r = 0;
		channel_params_array[5].one_color_dim_g = 128;
		channel_params_array[5].one_color_dim_b = 128;
		channel_params_array[5].one_color_dim_r_flag = 1;
		channel_params_array[5].one_color_dim_g_flag = 1;
		channel_params_array[5].one_color_dim_b_flag = 1;
		channel_params_array[5].one_color_dim_increment = 1;
		channel_params_array[5].one_color_dim_r_dir = 0;
		channel_params_array[5].one_color_dim_g_dir = 0;
		channel_params_array[5].one_color_dim_b_dir = 0;

		channel_params_array[6].channel = 6;
		channel_params_array[6].EEFECT = ONE_COLOR_EFFECT_DIM;
		channel_params_array[6].effectExecutor = &effectOneColorDim;
		channel_params_array[6].one_color_dim_r = 255;
		channel_params_array[6].one_color_dim_g = 255;
		channel_params_array[6].one_color_dim_b = 0;
		channel_params_array[6].one_color_dim_r_flag = 1;
		channel_params_array[6].one_color_dim_g_flag = 1;
		channel_params_array[6].one_color_dim_b_flag = 1;
		channel_params_array[6].one_color_dim_increment = 1;
		channel_params_array[6].one_color_dim_r_dir = 0;
		channel_params_array[6].one_color_dim_g_dir = 0;
		channel_params_array[6].one_color_dim_b_dir = 0;

		channel_params_array[7].channel = 7;
		channel_params_array[7].EEFECT = ONE_COLOR_EFFECT_DIM;
		channel_params_array[7].effectExecutor = &effectOneColorDim;
		channel_params_array[7].one_color_dim_r = 0;
		channel_params_array[7].one_color_dim_g = 255;
		channel_params_array[7].one_color_dim_b = 0;
		channel_params_array[7].one_color_dim_r_flag = 1;
		channel_params_array[7].one_color_dim_g_flag = 1;
		channel_params_array[7].one_color_dim_b_flag = 1;
		channel_params_array[7].one_color_dim_increment = 1;
		channel_params_array[7].one_color_dim_r_dir = 0;
		channel_params_array[7].one_color_dim_g_dir = 0;
		channel_params_array[7].one_color_dim_b_dir = 0;

		channel_params_array[8].channel = 8;
		channel_params_array[8].EEFECT = ONE_COLOR_EFFECT_DIM;
		channel_params_array[8].effectExecutor = &effectOneColorDim;
		channel_params_array[8].one_color_dim_r = 0;
		channel_params_array[8].one_color_dim_g = 255;
		channel_params_array[8].one_color_dim_b = 255;
		channel_params_array[8].one_color_dim_r_flag = 1;
		channel_params_array[8].one_color_dim_g_flag = 1;
		channel_params_array[8].one_color_dim_b_flag = 1;
		channel_params_array[8].one_color_dim_increment = 1;
		channel_params_array[8].one_color_dim_r_dir = 0;
		channel_params_array[8].one_color_dim_g_dir = 0;
		channel_params_array[8].one_color_dim_b_dir = 0;

		channel_params_array[9].channel = 9;
		channel_params_array[9].EEFECT = ONE_COLOR_EFFECT_DIM;
		channel_params_array[9].effectExecutor = &effectOneColorDim;
		channel_params_array[9].one_color_dim_r = 255;
		channel_params_array[9].one_color_dim_g = 255;
		channel_params_array[9].one_color_dim_b = 255;
		channel_params_array[9].one_color_dim_r_flag = 1;
		channel_params_array[9].one_color_dim_g_flag = 1;
		channel_params_array[9].one_color_dim_b_flag = 1;
		channel_params_array[9].one_color_dim_increment = 1;
		channel_params_array[9].one_color_dim_r_dir = 0;
		channel_params_array[9].one_color_dim_g_dir = 0;
		channel_params_array[9].one_color_dim_b_dir = 0;

		effectSelectorFlag = 0;
	}
}

void effect4Select(void)
{
	if(effectSelectorFlag == 1)
	{
		channel_params_array[0].channel = 0;
		channel_params_array[0].EEFECT = ONE_COLOR_EFFECT_DIM;
		channel_params_array[0].effectExecutor = &effectOneColorDim;
		channel_params_array[0].one_color_dim_r = 255;
		channel_params_array[0].one_color_dim_g = 0;
		channel_params_array[0].one_color_dim_b = 0;
		channel_params_array[0].one_color_dim_r_flag = 1;
		channel_params_array[0].one_color_dim_g_flag = 0;
		channel_params_array[0].one_color_dim_b_flag = 0;
		channel_params_array[0].one_color_dim_increment = 1;
		channel_params_array[0].one_color_dim_r_dir = 0;
		channel_params_array[0].one_color_dim_g_dir = 0;
		channel_params_array[0].one_color_dim_b_dir = 0;

		channel_params_array[1].channel = 1;
		channel_params_array[1].EEFECT = ONE_COLOR_EFFECT_DIM;
		channel_params_array[1].effectExecutor = &effectOneColorDim;
		channel_params_array[1].one_color_dim_r = 225;
		channel_params_array[1].one_color_dim_g = 0;
		channel_params_array[1].one_color_dim_b = 0;
		channel_params_array[1].one_color_dim_r_flag = 1;
		channel_params_array[1].one_color_dim_g_flag = 0;
		channel_params_array[1].one_color_dim_b_flag = 0;
		channel_params_array[1].one_color_dim_increment = 1;
		channel_params_array[1].one_color_dim_r_dir = 0;
		channel_params_array[1].one_color_dim_g_dir = 0;
		channel_params_array[1].one_color_dim_b_dir = 0;

		channel_params_array[2].channel = 2;
		channel_params_array[2].EEFECT = ONE_COLOR_EFFECT_DIM;
		channel_params_array[2].effectExecutor = &effectOneColorDim;
		channel_params_array[2].one_color_dim_r = 200;
		channel_params_array[2].one_color_dim_g = 0;
		channel_params_array[2].one_color_dim_b = 0;
		channel_params_array[2].one_color_dim_r_flag = 1;
		channel_params_array[2].one_color_dim_g_flag = 0;
		channel_params_array[2].one_color_dim_b_flag = 0;
		channel_params_array[2].one_color_dim_increment = 1;
		channel_params_array[2].one_color_dim_r_dir = 0;
		channel_params_array[2].one_color_dim_g_dir = 0;
		channel_params_array[2].one_color_dim_b_dir = 0;

		channel_params_array[3].channel = 3;
		channel_params_array[3].EEFECT = ONE_COLOR_EFFECT_DIM;
		channel_params_array[3].effectExecutor = &effectOneColorDim;
		channel_params_array[3].one_color_dim_r = 175;
		channel_params_array[3].one_color_dim_g = 0;
		channel_params_array[3].one_color_dim_b = 0;
		channel_params_array[3].one_color_dim_r_flag = 1;
		channel_params_array[3].one_color_dim_g_flag = 0;
		channel_params_array[3].one_color_dim_b_flag = 0;
		channel_params_array[3].one_color_dim_increment = 1;
		channel_params_array[3].one_color_dim_r_dir = 0;
		channel_params_array[3].one_color_dim_g_dir = 0;
		channel_params_array[3].one_color_dim_b_dir = 0;

		channel_params_array[4].channel = 4;
		channel_params_array[4].EEFECT = ONE_COLOR_EFFECT_DIM;
		channel_params_array[4].effectExecutor = &effectOneColorDim;
		channel_params_array[4].one_color_dim_r = 150;
		channel_params_array[4].one_color_dim_g = 0;
		channel_params_array[4].one_color_dim_b = 0;
		channel_params_array[4].one_color_dim_r_flag = 1;
		channel_params_array[4].one_color_dim_g_flag = 0;
		channel_params_array[4].one_color_dim_b_flag = 0;
		channel_params_array[4].one_color_dim_increment = 1;
		channel_params_array[4].one_color_dim_r_dir = 0;
		channel_params_array[4].one_color_dim_g_dir = 0;
		channel_params_array[4].one_color_dim_b_dir = 0;

		channel_params_array[5].channel = 5;
		channel_params_array[5].EEFECT = ONE_COLOR_EFFECT_DIM;
		channel_params_array[5].effectExecutor = &effectOneColorDim;
		channel_params_array[5].one_color_dim_r = 125;
		channel_params_array[5].one_color_dim_g = 0;
		channel_params_array[5].one_color_dim_b = 0;
		channel_params_array[5].one_color_dim_r_flag = 1;
		channel_params_array[5].one_color_dim_g_flag = 0;
		channel_params_array[5].one_color_dim_b_flag = 0;
		channel_params_array[5].one_color_dim_increment = 1;
		channel_params_array[5].one_color_dim_r_dir = 0;
		channel_params_array[5].one_color_dim_g_dir = 0;
		channel_params_array[5].one_color_dim_b_dir = 0;

		channel_params_array[6].channel = 6;
		channel_params_array[6].EEFECT = ONE_COLOR_EFFECT_DIM;
		channel_params_array[6].effectExecutor = &effectOneColorDim;
		channel_params_array[6].one_color_dim_r = 100;
		channel_params_array[6].one_color_dim_g = 0;
		channel_params_array[6].one_color_dim_b = 0;
		channel_params_array[6].one_color_dim_r_flag = 1;
		channel_params_array[6].one_color_dim_g_flag = 0;
		channel_params_array[6].one_color_dim_b_flag = 0;
		channel_params_array[6].one_color_dim_increment = 1;
		channel_params_array[6].one_color_dim_r_dir = 0;
		channel_params_array[6].one_color_dim_g_dir = 0;
		channel_params_array[6].one_color_dim_b_dir = 0;

		channel_params_array[7].channel = 7;
		channel_params_array[7].EEFECT = ONE_COLOR_EFFECT_DIM;
		channel_params_array[7].effectExecutor = &effectOneColorDim;
		channel_params_array[7].one_color_dim_r = 75;
		channel_params_array[7].one_color_dim_g = 0;
		channel_params_array[7].one_color_dim_b = 0;
		channel_params_array[7].one_color_dim_r_flag = 1;
		channel_params_array[7].one_color_dim_g_flag = 0;
		channel_params_array[7].one_color_dim_b_flag = 0;
		channel_params_array[7].one_color_dim_increment = 1;
		channel_params_array[7].one_color_dim_r_dir = 0;
		channel_params_array[7].one_color_dim_g_dir = 0;
		channel_params_array[7].one_color_dim_b_dir = 0;

		channel_params_array[8].channel = 8;
		channel_params_array[8].EEFECT = ONE_COLOR_EFFECT_DIM;
		channel_params_array[8].effectExecutor = &effectOneColorDim;
		channel_params_array[8].one_color_dim_r = 50;
		channel_params_array[8].one_color_dim_g = 0;
		channel_params_array[8].one_color_dim_b = 0;
		channel_params_array[8].one_color_dim_r_flag = 1;
		channel_params_array[8].one_color_dim_g_flag = 0;
		channel_params_array[8].one_color_dim_b_flag = 0;
		channel_params_array[8].one_color_dim_increment = 1;
		channel_params_array[8].one_color_dim_r_dir = 0;
		channel_params_array[8].one_color_dim_g_dir = 0;
		channel_params_array[8].one_color_dim_b_dir = 0;

		channel_params_array[9].channel = 9;
		channel_params_array[9].EEFECT = ONE_COLOR_EFFECT_DIM;
		channel_params_array[9].effectExecutor = &effectOneColorDim;
		channel_params_array[9].one_color_dim_r = 25;
		channel_params_array[9].one_color_dim_g = 0;
		channel_params_array[9].one_color_dim_b = 0;
		channel_params_array[9].one_color_dim_r_flag = 1;
		channel_params_array[9].one_color_dim_g_flag = 0;
		channel_params_array[9].one_color_dim_b_flag = 0;
		channel_params_array[9].one_color_dim_increment = 1;
		channel_params_array[9].one_color_dim_r_dir = 0;
		channel_params_array[9].one_color_dim_g_dir = 0;
		channel_params_array[9].one_color_dim_b_dir = 0;

		effectSelectorFlag = 0;
	}
}

void effect5Select(void)
{
	if(effectSelectorFlag == 1)
	{

		channel_params_array[0].channel = 0;
		channel_params_array[0].EEFECT = ONE_COLOR_EFFECT_DIM;
		channel_params_array[0].effectExecutor = &effectOneColorDim;
		channel_params_array[0].one_color_dim_r = 0;
		channel_params_array[0].one_color_dim_g = 255;
		channel_params_array[0].one_color_dim_b = 128;
		channel_params_array[0].one_color_dim_r_flag = 1;
		channel_params_array[0].one_color_dim_g_flag = 1;
		channel_params_array[0].one_color_dim_b_flag = 1;
		channel_params_array[0].one_color_dim_increment = 10;
		channel_params_array[0].one_color_dim_r_dir = 0;
		channel_params_array[0].one_color_dim_g_dir = 1;
		channel_params_array[0].one_color_dim_b_dir = 0;

		channel_params_array[1].channel = 1;
		channel_params_array[1].EEFECT = ONE_COLOR_EFFECT_DIM;
		channel_params_array[1].effectExecutor = &effectOneColorDim;
		channel_params_array[1].one_color_dim_r = 255;
		channel_params_array[1].one_color_dim_g = 128;
		channel_params_array[1].one_color_dim_b = 128;
		channel_params_array[1].one_color_dim_r_flag = 1;
		channel_params_array[1].one_color_dim_g_flag = 1;
		channel_params_array[1].one_color_dim_b_flag = 1;
		channel_params_array[1].one_color_dim_increment = 4;
		channel_params_array[1].one_color_dim_r_dir = 1;
		channel_params_array[1].one_color_dim_g_dir = 0;
		channel_params_array[1].one_color_dim_b_dir = 0;

		channel_params_array[2].channel = 2;
		channel_params_array[2].EEFECT = ONE_COLOR_EFFECT_DIM;
		channel_params_array[2].effectExecutor = &effectOneColorDim;
		channel_params_array[2].one_color_dim_r = 128;
		channel_params_array[2].one_color_dim_g = 128;
		channel_params_array[2].one_color_dim_b = 0;
		channel_params_array[2].one_color_dim_r_flag = 1;
		channel_params_array[2].one_color_dim_g_flag = 1;
		channel_params_array[2].one_color_dim_b_flag = 1;
		channel_params_array[2].one_color_dim_increment = 1;
		channel_params_array[2].one_color_dim_r_dir = 0;
		channel_params_array[2].one_color_dim_g_dir = 1;
		channel_params_array[2].one_color_dim_b_dir = 0;

		channel_params_array[3].channel = 3;
		channel_params_array[3].EEFECT = ONE_COLOR_EFFECT_DIM;
		channel_params_array[3].effectExecutor = &effectOneColorDim;
		channel_params_array[3].one_color_dim_r = 128;
		channel_params_array[3].one_color_dim_g = 0;
		channel_params_array[3].one_color_dim_b = 128;
		channel_params_array[3].one_color_dim_r_flag = 1;
		channel_params_array[3].one_color_dim_g_flag = 1;
		channel_params_array[3].one_color_dim_b_flag = 1;
		channel_params_array[3].one_color_dim_increment = 2;
		channel_params_array[3].one_color_dim_r_dir = 0;
		channel_params_array[3].one_color_dim_g_dir = 0;
		channel_params_array[3].one_color_dim_b_dir = 0;

		channel_params_array[4].channel = 4;
		channel_params_array[4].EEFECT = ONE_COLOR_EFFECT_DIM;
		channel_params_array[4].effectExecutor = &effectOneColorDim;
		channel_params_array[4].one_color_dim_r = 128;
		channel_params_array[4].one_color_dim_g = 255;
		channel_params_array[4].one_color_dim_b = 0;
		channel_params_array[4].one_color_dim_r_flag = 1;
		channel_params_array[4].one_color_dim_g_flag = 1;
		channel_params_array[4].one_color_dim_b_flag = 1;
		channel_params_array[4].one_color_dim_increment = 3;
		channel_params_array[4].one_color_dim_r_dir = 1;
		channel_params_array[4].one_color_dim_g_dir = 0;
		channel_params_array[4].one_color_dim_b_dir = 0;

		channel_params_array[5].channel = 5;
		channel_params_array[5].EEFECT = ONE_COLOR_EFFECT_DIM;
		channel_params_array[5].effectExecutor = &effectOneColorDim;
		channel_params_array[5].one_color_dim_r = 0;
		channel_params_array[5].one_color_dim_g = 128;
		channel_params_array[5].one_color_dim_b = 128;
		channel_params_array[5].one_color_dim_r_flag = 1;
		channel_params_array[5].one_color_dim_g_flag = 1;
		channel_params_array[5].one_color_dim_b_flag = 1;
		channel_params_array[5].one_color_dim_increment = 1;
		channel_params_array[5].one_color_dim_r_dir = 0;
		channel_params_array[5].one_color_dim_g_dir = 0;
		channel_params_array[5].one_color_dim_b_dir = 0;

		channel_params_array[6].channel = 6;
		channel_params_array[6].EEFECT = ONE_COLOR_EFFECT_DIM;
		channel_params_array[6].effectExecutor = &effectOneColorDim;
		channel_params_array[6].one_color_dim_r = 255;
		channel_params_array[6].one_color_dim_g = 255;
		channel_params_array[6].one_color_dim_b = 0;
		channel_params_array[6].one_color_dim_r_flag = 1;
		channel_params_array[6].one_color_dim_g_flag = 1;
		channel_params_array[6].one_color_dim_b_flag = 1;
		channel_params_array[6].one_color_dim_increment = 3;
		channel_params_array[6].one_color_dim_r_dir = 0;
		channel_params_array[6].one_color_dim_g_dir = 0;
		channel_params_array[6].one_color_dim_b_dir = 0;

		channel_params_array[7].channel = 7;
		channel_params_array[7].EEFECT = ONE_COLOR_EFFECT_DIM;
		channel_params_array[7].effectExecutor = &effectOneColorDim;
		channel_params_array[7].one_color_dim_r = 0;
		channel_params_array[7].one_color_dim_g = 255;
		channel_params_array[7].one_color_dim_b = 0;
		channel_params_array[7].one_color_dim_r_flag = 1;
		channel_params_array[7].one_color_dim_g_flag = 1;
		channel_params_array[7].one_color_dim_b_flag = 1;
		channel_params_array[7].one_color_dim_increment = 3;
		channel_params_array[7].one_color_dim_r_dir = 0;
		channel_params_array[7].one_color_dim_g_dir = 0;
		channel_params_array[7].one_color_dim_b_dir = 0;

		channel_params_array[8].channel = 8;
		channel_params_array[8].EEFECT = ONE_COLOR_EFFECT_DIM;
		channel_params_array[8].effectExecutor = &effectOneColorDim;
		channel_params_array[8].one_color_dim_r = 0;
		channel_params_array[8].one_color_dim_g = 255;
		channel_params_array[8].one_color_dim_b = 255;
		channel_params_array[8].one_color_dim_r_flag = 1;
		channel_params_array[8].one_color_dim_g_flag = 1;
		channel_params_array[8].one_color_dim_b_flag = 1;
		channel_params_array[8].one_color_dim_increment = 2;
		channel_params_array[8].one_color_dim_r_dir = 0;
		channel_params_array[8].one_color_dim_g_dir = 0;
		channel_params_array[8].one_color_dim_b_dir = 0;

		channel_params_array[9].channel = 9;
		channel_params_array[9].EEFECT = ONE_COLOR_EFFECT_DIM;
		channel_params_array[9].effectExecutor = &effectOneColorDim;
		channel_params_array[9].one_color_dim_r = 0;
		channel_params_array[9].one_color_dim_g = 255;
		channel_params_array[9].one_color_dim_b = 255;
		channel_params_array[9].one_color_dim_r_flag = 1;
		channel_params_array[9].one_color_dim_g_flag = 1;
		channel_params_array[9].one_color_dim_b_flag = 1;
		channel_params_array[9].one_color_dim_increment = 1;
		channel_params_array[9].one_color_dim_r_dir = 0;
		channel_params_array[9].one_color_dim_g_dir = 0;
		channel_params_array[9].one_color_dim_b_dir = 0;

		effectSelectorFlag = 0;
	}
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 12;
  RCC_OscInitStruct.PLL.PLLN = 144;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV6;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 9600;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_4
                          |GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_8
                          |GPIO_PIN_9, GPIO_PIN_RESET);

  /*Configure GPIO pins : PB0 PB1 PB2 PB4
                           PB5 PB6 PB7 PB8
                           PB9 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_4
                          |GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_8
                          |GPIO_PIN_9;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : PB3 */
  GPIO_InitStruct.Pin = GPIO_PIN_3;
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
