/*
 * Barometre.h
 *
 *  Created on: Oct 5, 2021
 *      Author: karam
 */

#ifndef INC_MS5611_H_
#define INC_MS5611_H_

#include "main.h"
#include "math.h"
#define MS5611_ADDRESS                (0x76<<1) //gnd ye baglı ise 77 olacak adress
#define I2cHatti hi2c2							//bağlı olan I2c hattı

#define MS5611_SLAVEADDRESS_WRITE     0xEE
#define MS5611_SLAVEADDRESS_READ      0xEF

#define MS5611_CMD_ADC_READ           0x00
#define MS5611_CMD_RESET              0x1E

#define MS5611_CMD_CONVERT_D1_256     0x40
#define MS5611_CMD_CONVERT_D1_512     0x42
#define MS5611_CMD_CONVERT_D1_1024    0x44
#define MS5611_CMD_CONVERT_D1_2048    0x46
#define MS5611_CMD_CONVERT_D1_4096    0x48
#define MS5611_CMD_CONVERT_D2_256     0x50
#define MS5611_CMD_CONVERT_D2_512     0x52
#define MS5611_CMD_CONVERT_D2_1024    0x54
#define MS5611_CMD_CONVERT_D2_2048    0x56
#define MS5611_CMD_CONVERT_D2_4096    0x58

#define MS5611_ADC   0x00    // read ADC 1


#define MS5611_PROM_READ_0            0xA0
#define MS5611_PROM_READ_1            0xA2
#define MS5611_PROM_READ_2            0xA4
#define MS5611_PROM_READ_3            0xA6
#define MS5611_PROM_READ_4            0xA8
#define MS5611_PROM_READ_5            0xAA
#define MS5611_PROM_READ_6            0xAC
#define MS5611_PROM_READ_7            0xAE

int k;
int i;
float Barometer_Pressure;
float First_Barometer_Pressure;
float Zero_point_Barometer_Pressure;
float Barometer_Pressure_Filtered;
float actual_Pressure_fast;
float actual_Pressure_slow;
float actual_Pressure_diff;
float actual_Pressure;
float  Barometer_Altitude;
float  Barometer_Altitude_Filtered;

uint16_t C[7];

uint8_t Buffer[3];
uint32_t D1,D2;// d1 okunan pressure degeri, d2 okunan temperature değeri

int counter;

int32_t dT,TEMP,P;
int64_t OFF,SENS,OFF2,SENS2;
float T2;
float TEMP_f32,PRESSURE_f32;
I2C_HandleTypeDef I2cHatti;

void Ms5611Write(uint8_t wRegister,uint8_t Value);
void Ms5611Read(uint8_t rRegister,uint8_t NumberOfBytes);
void Ms5611Init();
void CalculateTemperature();
void CompansatedPressure();
void FilteredPressure();
void Ms5611Altitude();

#endif /* INC_MS5611_H_ */
