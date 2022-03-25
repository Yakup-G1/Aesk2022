/*
 * AESK_GL.c
 *
 *  Created on: Dec 12, 2020
 *      Author: basri
 */

#include "AESK_GL.h"

void AESK_GL_Init(AESK_GL* aesk_gl)
{
	for(uint32_t i = 0; i < sizeof(AESK_GL); i++)
	{
		((uint8_t*)aesk_gl)[i] = 0;
	}
}

void HAL_SYSTICK_Callback(void)
{
	aesk_gl.system_clock_counter_1ms++;

		if(aesk_gl.system_clock_counter_1ms % 5 == 0)
		{
			tt.time_task_t.task_200_Hz = 1;
		}

		if(aesk_gl.system_clock_counter_1ms % 10 == 0)
		{
			tt.time_task_t.task_100_Hz = 1;
		}

		if(aesk_gl.system_clock_counter_1ms % 20 == 0)
		{
			tt.time_task_t.task_50_Hz = 1;
		}

		if(aesk_gl.system_clock_counter_1ms % 50 == 0)
		{
			tt.time_task_t.task_20_Hz = 1;
		}
		if(aesk_gl.system_clock_counter_1ms % 100 == 0)
		{
			tt.time_task_t.task_10_Hz = 1;
		}
		if(aesk_gl.system_clock_counter_1ms % 500 == 0)
		{
			tt.time_task_t.task_2_Hz = 1;
		}
		if(aesk_gl.system_clock_counter_1ms % 1000 == 0)
		{
			tt.time_task_t.task_1_Hz = 1;
		}

}

uint16_t aeskCRCCalculator(uint8_t *frame, size_t framesize)
{
	uint16_t crc16_data = 0;
	uint8_t data = 0;
	for (uint8_t mlen = 0; mlen < framesize; mlen++)
	{
		data = frame[mlen] ^ ((uint8_t) (crc16_data) & (uint8_t) (0xFF));
		data ^= data << 4;
		crc16_data = ((((uint16_t) data << 8) | ((crc16_data & 0xFF00) >> 8)) ^ (uint8_t) (data >> 4) ^ ((uint16_t) data << 3));
	}
	return (crc16_data);
}




