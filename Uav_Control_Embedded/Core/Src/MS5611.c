/*
 * Barometre.c
 *
 *  Created on: Oct 5, 2021
 *      Author: karam
 */
#include <MS5611.h>

void Ms5611Init()
{
	Buffer[0]=MS5611_CMD_RESET;
	HAL_I2C_Master_Transmit(&I2cHatti, MS5611_ADDRESS, Buffer, 1, 100);
	HAL_Delay(1);

	for (int i=1;i<7;i++)
	{
		Buffer[0]=MS5611_PROM_READ_0+i*2;
		HAL_I2C_Master_Transmit(&I2cHatti, MS5611_ADDRESS, Buffer, 1, 100);
		HAL_I2C_Master_Receive(&I2cHatti, MS5611_ADDRESS, Buffer, 2, 100);
        C[i] = Buffer[0]<<8 | Buffer[1];
        HAL_Delay(5);
	}
}
void CalculateTemperature()
{

	Buffer[0]=MS5611_CMD_CONVERT_D2_4096;
	HAL_I2C_Master_Transmit(&I2cHatti, MS5611_ADDRESS, Buffer, 1, 100);
	HAL_Delay(9);
	Buffer[0]=MS5611_CMD_ADC_READ;
	HAL_I2C_Master_Transmit(&I2cHatti, MS5611_ADDRESS, Buffer, 1, 100);
	HAL_I2C_Master_Receive(&I2cHatti, MS5611_ADDRESS, Buffer, 3, 100);
	D2    = Buffer[0]<<16 | Buffer[1]<<8 |Buffer[2];//okunan Temperature degerini d2 e at

}
void CompansatedPressure()
{
	Buffer[0]=MS5611_CMD_CONVERT_D1_4096;
	HAL_I2C_Master_Transmit(&I2cHatti, MS5611_ADDRESS, Buffer, 1, 100);
	HAL_Delay(9);
	Buffer[0]=MS5611_CMD_ADC_READ;
	HAL_I2C_Master_Transmit(&I2cHatti, MS5611_ADDRESS, Buffer, 1, 100);
	HAL_I2C_Master_Receive(&I2cHatti, MS5611_ADDRESS, Buffer, 3, 100);
	D1    =  Buffer[0]<<16 | Buffer[1]<<8 |Buffer[2];
	dT    = D2-(C[5]*256);
	TEMP  = (2000+((dT*C[6])/8388608));
	TEMP_f32 = (float)TEMP/100.0;
	OFF   = C[2]*65536 + (C[4]*dT)/128;
	SENS  = C[1]*32768 + (C[3]*dT)/256;
	if(TEMP_f32>20)
		{
			T2   = pow(dT,2)/2147483648;
			OFF2 = (5*pow((TEMP-2000),2))/2;
			SENS2= (5*pow((TEMP-2000),2))/4;
			TEMP=TEMP-T2;
			OFF=OFF-OFF2;
			SENS=SENS-SENS2;
		}
		else
		{
			T2    = 0 ;
			SENS2 = 0 ;
			OFF2  = 0 ;
			TEMP=TEMP-T2;
			OFF=OFF-OFF2;
			SENS=SENS-SENS2;
		}

	P    = ((D1*SENS)/2097152-OFF)/32768;
	PRESSURE_f32 = (float)(P/100.0)-1000.0;
}
void FilteredPressure()
{
	CalculateTemperature();
	CompansatedPressure();
}
void Ms5611Altitude()
{
	FilteredPressure();
	First_Barometer_Pressure=First_Barometer_Pressure+Barometer_Pressure;
	if(i==100)
	{
	  Zero_point_Barometer_Pressure=First_Barometer_Pressure/i+0.12;//0.12 değeri rastgele verilmiştir başlangıcta zero point anlamadığım bir sebepten istenilenin yaklaşık 0.12 altında kalıyor
	}
	if(i!=101)
	{
	  i++;
	}
	k++;
	if(k==20)
	{
		actual_Pressure_fast=Barometer_Pressure_Filtered/20;
		Barometer_Pressure_Filtered = 0;
		k=0;
	}
	Barometer_Pressure = PRESSURE_f32;
	Barometer_Pressure_Filtered +=  Barometer_Pressure;
	actual_Pressure_slow = actual_Pressure_slow * (float)0.93 + actual_Pressure_fast * (float)0.07;
	actual_Pressure_diff = actual_Pressure_slow - actual_Pressure_fast;
	if (actual_Pressure_diff > 8)actual_Pressure_diff = 8;                                                    //If the difference is larger then 8 limit the difference to 8.
	if (actual_Pressure_diff < -8)actual_Pressure_diff = -8;                                                  //If the difference is smaller then -8 limit the difference to -8.
	//If the difference is larger then 1 or smaller then -1 the slow average is adjuste based on the error between the fast and slow average.
	if (actual_Pressure_diff > 1 || actual_Pressure_diff < -1)actual_Pressure_slow -= actual_Pressure_diff / 6.0;
	actual_Pressure = actual_Pressure_slow;
	Barometer_Altitude=44300*(1.0-pow(actual_Pressure/(Zero_point_Barometer_Pressure),0.1902949));
}
