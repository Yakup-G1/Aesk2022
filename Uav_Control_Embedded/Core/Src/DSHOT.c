/*
 * DSHOT.c
 *
 *  Created on: Jul 19, 2021
 *
 */

#include "DSHOT.h"
#include "MotorPowerCalculate.h"


extern TIM_HandleTypeDef htim1;

uint32_t motor1_dmabuffer[18];
uint32_t motor2_dmabuffer[18];
uint32_t motor3_dmabuffer[18];
uint32_t motor4_dmabuffer[18];

void dshot_init()
{
  	HAL_TIM_PWM_Start((&htim1), TIM_CHANNEL_1);
    HAL_TIM_PWM_Start((&htim1), TIM_CHANNEL_2);
  	HAL_TIM_PWM_Start((&htim1), TIM_CHANNEL_3);
  	HAL_TIM_PWM_Start((&htim1), TIM_CHANNEL_4);

//  	Motor.Sag_Arka=48;
//	Motor.Sag_On  =48;
//	Motor.Sol_Arka=48;
//	Motor.Sol_On  =48;
//	dshot_write_all(Motor.Sag_Arka,Motor.Sag_On,Motor.Sol_Arka,Motor.Sol_On);

		//__HAL_TIM_DISABLE_DMA((&htim1), TIM_DMA_CC1);
}

void dshot_write(uint32_t* motor_dmabuffer, uint16_t value)
{

	uint16_t packet;
	bool dshot_telemetry = false;

	packet = (value << 1) | (dshot_telemetry ? 1 : 0);

	unsigned csum = 0;
	unsigned csum_data = packet;

	for(int i = 0; i < 3; i++)
	{
    csum ^=  csum_data; //
    csum_data >>= 4;
	}

	csum &= 0xf;
	packet = (packet << 4) | csum;

	for(int i = 0; i < 16; i++)
	{
	motor_dmabuffer[i] = (packet & 0x8000) ? MOTOR_BIT_1 : MOTOR_BIT_0;
	packet <<= 1;
	}

	motor_dmabuffer[16] = 0;
	motor_dmabuffer[17] = 0;

}

HAL_StatusTypeDef statusDSHOT;

void dshot_write_all(uint16_t esc1, uint16_t esc2, uint16_t esc3, uint16_t esc4)
{
	dshot_write(motor1_dmabuffer, esc1);
	statusDSHOT = HAL_DMA_Start_IT(MOTOR_1_TIM->hdma[TIM_DMA_ID_CC1], (uint32_t)motor1_dmabuffer, (uint32_t)&MOTOR_1_TIM->Instance->CCR1, 18);

	dshot_write(motor2_dmabuffer, esc2);
	HAL_DMA_Start_IT(MOTOR_1_TIM->hdma[TIM_DMA_ID_CC2], (uint32_t)motor2_dmabuffer, (uint32_t)&MOTOR_1_TIM->Instance->CCR2, 18);

	dshot_write(motor3_dmabuffer, esc3);
	HAL_DMA_Start_IT(MOTOR_1_TIM->hdma[TIM_DMA_ID_CC3], (uint32_t)motor3_dmabuffer, (uint32_t)&MOTOR_1_TIM->Instance->CCR3, 18);

	dshot_write(motor4_dmabuffer, esc4);
	HAL_DMA_Start_IT(MOTOR_1_TIM->hdma[TIM_DMA_ID_CC4], (uint32_t)motor4_dmabuffer, (uint32_t)&MOTOR_1_TIM->Instance->CCR4, 18);

	__HAL_TIM_ENABLE_DMA((&htim1), TIM_DMA_CC1);
	__HAL_TIM_ENABLE_DMA((&htim1), TIM_DMA_CC2);
	__HAL_TIM_ENABLE_DMA((&htim1), TIM_DMA_CC3);
	__HAL_TIM_ENABLE_DMA((&htim1), TIM_DMA_CC4);

}

