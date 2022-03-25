/*
 * AhrsFilter2.h
 *
 *  Created on: 28 Şub 2022
 *      Author: karam
 */

#ifndef INC_AHRSFILTER2_H_
#define INC_AHRSFILTER2_H_

volatile float beta;				    												// Algoritma Kazanc Degeri
volatile float zeta;																		// Bias Comp Kazanc Degeri
volatile float SEq_1, SEq_2, SEq_3,SEq_4;

// Fonksiyon tanimlamalar
void MadgwickAHRSupdate(float gx, float gy, float gz, float ax, float ay, float az, float mx, float my, float mz);
void MadgwickAHRSupdateIMU(float gx, float gy, float gz, float ax, float ay, float az);
void MadgwickOriginalIMU(float gx, float gy, float gz, float ax, float ay, float az);
void Quat_to_Deg(float SEq_1,float SEq_2,float SEq_3,float SEq_4);

#endif /* INC_AHRSFILTER2_H_ */
