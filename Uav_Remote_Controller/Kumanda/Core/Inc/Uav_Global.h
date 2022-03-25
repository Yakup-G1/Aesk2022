/*
 * Aesk_Uav_Global.h
 *
 *  Created on: Aug 19, 2021
 *      Author: PC_1830
 */

#ifndef INC_UAV_GLOBAL_H_
#define INC_UAV_GLOBAL_H_

#include "main.h"


#define Elapsed_time 0.001


//
//TIM_HandleTypeDef htim1;
//TIM_HandleTypeDef htim3;


uint32_t system_clock_counter_1ms;

typedef union
{
	struct
	{
		uint8_t Hz_1000 : 1 ;
		uint8_t Hz_200 : 1;
		uint8_t Hz_100 : 1;
		uint8_t Hz_50 : 1;
		uint8_t Hz_20 : 1;
		uint8_t Hz_10 : 1;
		uint8_t Hz_5 : 1;
		uint8_t Hz_1 : 1;
	}Task;

	uint8_t all_u8;

}time_task_union;

 time_task_union Time;


#endif /* INC_UAV_GLOBAL_H_ */
