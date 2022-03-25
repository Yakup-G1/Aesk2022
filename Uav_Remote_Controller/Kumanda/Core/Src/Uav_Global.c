/*
 * Aesk_Uav_Global.c
 *
 *  Created on: Aug 19, 2021
 *      Author: PC_1830
 */

#include <Uav_Global.h>
//#include "ReadingSensor.h"

void HAL_SYSTICK_Callback(void)
{
	system_clock_counter_1ms++;

	if( system_clock_counter_1ms % 1000 == 0)
	{
		Time.Task.Hz_1 = 1;
	}
	if( system_clock_counter_1ms % 200 == 0)
	{
		Time.Task.Hz_5 = 1;
	}
	if( system_clock_counter_1ms % 100 == 0)
	{
		Time.Task.Hz_10 = 1;
	}
	if( system_clock_counter_1ms % 50 == 0)
	{
		Time.Task.Hz_20 = 1;
	}
	if( system_clock_counter_1ms % 20 == 0)
	{
		Time.Task.Hz_50 = 1;
	}
	if( system_clock_counter_1ms % 10 == 0)
	{
		Time.Task.Hz_100 = 1;
	}
	if( system_clock_counter_1ms % 5 == 0)
	{
		Time.Task.Hz_200 = 1;
	}
	if( system_clock_counter_1ms % 1 == 0)
	{
		Time.Task.Hz_1000 = 1;
	}
}



