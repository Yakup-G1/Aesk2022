/*
 * gy271.h
 *
 *  Created on: Jun 9, 2021
 *      Author: egemen
 */

#ifndef INC_HMC5883L_H_
#define INC_HMC5883L_H_


#include "main.h"

#define ManyometerSlaveAdressRead 0x3D
#define ManyometerSlaveAdressWrite 0x3C

#define HMC5883L_CFG_REG_A  0x00
#define HMC5883L_CFG_REG_B  0x01
#define HMC5883L_MODE_REGISTER  0x02
#define HMC5883L_OUTX_L_REG  0x03
#define HMC5883L_OUTX_H_REG  0x04
#define HMC5883L_OUTY_L_REG  0x05
#define HMC5883L_OUTY_H_REG  0x06
#define HMC5883L_OUTZ_L_REG  0x07
#define HMC5883L_OUTZ_H_REG  0x08
#define HMC5883L_STATUS_REG  0x09
#define HMC5883L_IDENTIFICATION_A  0x10
#define HMC5883L_IDENTIFICATION_B  0x11
#define HMC5883L_IDENTIFICATION_C  0x12


I2C_HandleTypeDef hi2c1;//veri hangi i2c adresinde ise onu yaz
uint8_t Mydatas[6];

int16_t Mag_Raw_X,Mag_Raw_Y,Mag_Raw_Z;
float scaled_mag_x,scaled_mag_y,scaled_mag_z;
float biased_mag_x,biased_mag_y,biased_mag_z;
float calibrated_mag_x,calibrated_mag_y,calibrated_mag_z;
float calibration_matrice[3][3];
float bias_value_mag_x,bias_value_mag_y,bias_value_mag_z;
float magno_angle,magno_bearing;
float magno_declination;

float cx,cy;

void ManyometerInit();
void ManyometerRead(uint8_t rRegister,uint8_t NumberOfBytes);
void ManyometerWrite(uint8_t wRegister,uint8_t Value);
void ManyometerReadValue();
void Magno_Offset_Calc(void);

#endif /* INC_HMC5883L_H_ */
