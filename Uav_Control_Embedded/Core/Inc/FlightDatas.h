/*
 * FlightDatas.h
 *
 *  Created on: 7 Şub 2022
 *      Author: ysfkhy
 */

#ifndef INC_FLIGHTDATAS_H_
#define INC_FLIGHTDATAS_H_

typedef struct{
	float floatRollPitchKp;
	float floatRollPitchKi;
	float floatRollPitchKd;

	float floatYawKp;
	float floatYawKi;
	float floatYawKd;

	float floatAltitudeKp;
	float floatAltitudeKi;
	float floatAltitudeKd;

	float floatGpsKp;
	float floatGpsKi;
	float floatGpsKd;

	float floatExt1Kp;
	float floatExt1Ki;
	float floatExt1Kd;

	float floatExt2Kp;
	float floatExt2Ki;
	float floatExt2Kd;
}Aesk_Rx_Datas_Float;
Aesk_Rx_Datas_Float aesk_Rx_Datas_Float;

typedef struct{
uint32_t RollPitchKp;
uint32_t RollPitchKi;
uint32_t RollPitchKd;

uint32_t YawKp;
uint32_t YawKi;
uint32_t YawKd;

uint32_t AltitudeKp;
uint32_t AltitudeKi;
uint32_t AltitudeKd;

uint32_t GpsKp;
uint32_t GpsKi;
uint32_t GpsKd;

uint32_t Ext1Kp;
uint32_t Ext1Ki;
uint32_t Ext1Kd;

uint32_t Ext2Kp;
uint32_t Ext2Ki;
uint32_t Ext2Kd;

uint16_t adc1;
uint16_t adc2;
uint16_t adc3;
uint16_t adc4;
uint16_t adc5;
uint16_t adc6;
uint16_t adc7;
uint16_t adc8;
uint16_t adc9;
uint16_t adc10;
}Aesk_Rx_Datas_Int;
Aesk_Rx_Datas_Int aesk_Rx_Datas_Int;



#endif /* INC_FLIGHTDATAS_H_ */
