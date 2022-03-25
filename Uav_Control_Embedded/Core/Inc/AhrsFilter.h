/*
 * ReadingSensor.h
 *
 *  Created on: 14 Mar 2021
 *      Author: karam
 */

#ifndef INC_AHRSFILTER_H_
#define INC_AHRSFILTER_H_

#include "main.h"

#define DEG_TO_RAD 0.01745329251994329576923690768489
#define Dutymax 2000
#define Dutymin 1000
#define RAD_TO_DEG 57.2957795
#define M_PI 3.14159265358979323846
#define gyroMeasError 3.14159265358979f * (5.0f / 180.0f)
#define beta1 sqrt(3.0f / 4.0f) * gyroMeasError

float ComplementaryFAngleRoll,ComplementaryFAnglePitch,ComplementaryFAngleYaw;

float ahrs_y,ahrs_r,ahrs_p;
float last_ahrs_y,last_ahrs_r,last_ahrs_p,Ahrs_YAW,Ahrs_PITCH,Ahrs_ROLL;

float a_x, a_y, a_z;


void MadgwickAhrsFilter(float w_x,float w_y,float w_z,float a_x,float a_y,float a_z);



#endif /* INC_AHRSFILTER_H_ */
