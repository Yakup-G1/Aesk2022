/*
 * Aesk_Uav_Global.h
 *
 *  Created on: Aug 19, 2021
 *      Author: PC_1830
 */

#ifndef INC_UAV_GLOBAL_H_
#define INC_UAV_GLOBAL_H_

#include "main.h"
#include "Kumanda.h"
#include "MotorPowerCalculate.h"
#include "Filter.h"
#include "AhrsFilter.h"
#include "AESK_Ring_Buffer.h"
#include "ReadingSensor.h"
#include "nRF24L01.h"
#include "AESK_Data_Pack_lib.h"
#include "AESK_GL.h"
#include "AESK_NRF24.h"
#include "FLASH.h"
#include "FlightDatas.h"
//#include "MS5611.h"
#include "lps22hd.h"
#include "DSHOT.h"
#include "TFMini_S.h"

#define Elapsed_time 0.002

I2C_HandleTypeDef hi2c1;
I2C_HandleTypeDef hi2c2;
I2C_HandleTypeDef hi2c3;
UART_HandleTypeDef huart4;
UART_HandleTypeDef huart5;
UART_HandleTypeDef huart3;
//ADC_HandleTypeDef hadc1;
TIM_HandleTypeDef htim1;
TIM_HandleTypeDef htim3;
SPI_HandleTypeDef hspi1;


MPU_ConfigTypeDef myMpuConfig;
uint32_t system_clock_counter_1ms;
uint16_t adc_data[3];
uint16_t adc_buffer[3];
bool onReceiveFlag ;
uint16_t indexTx;

uint64_t thisNode;
uint64_t nodeGCS;

typedef union
{
	struct
	{
		uint8_t Hz_1000 : 1 ;
		uint8_t Hz_500 : 1;
		uint8_t Hz_200 : 1;
		uint8_t Hz_50 : 1;
		uint8_t Hz_20 : 1;
		uint8_t Hz_10 : 1;
		uint8_t Hz_5 : 1;
		uint8_t Hz_1 : 1;
	}Task;

	uint8_t all_u8;

}time_task_union;

 time_task_union Time;

typedef struct
{
	uint16_t Adc_value;
	uint16_t Adc_index;
	uint16_t Adc_output;
	uint16_t Adc_array[10];
	float Voltage;
}Battery_handleTypeDef;

Battery_handleTypeDef Battery;
int Counter;

float MapFloat(float x, float in_min, float in_max, float out_min, float out_max);
int MapInt(int x, int in_min, int in_max, int out_min, int out_max);
float constrain(float value, float Min, float Max);
void Read_ADC();
void Battery_Calculate();
void MainAllInit();
void Autonomous_With_GPS();
void RemoteControlOnOff();
void Registerinit();//işlemci registere kaydedilen degeri başlatma
void parseBuffer(uint8_t *buffer);

float Rolltau  ;
float RollLimit ;
float RollLimitint ;


#endif /* INC_UAV_GLOBAL_H_ */
