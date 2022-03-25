/*
 * ReadingSensor.c
 *
 *  Created on: 14 Mar 2021
 *      Author: karam
 */
#include "AhrsFilter.h"
#include <KalmanImu.h>
#include <math.h>
#include "Uav_Global.h"

uint8_t calib_mag = 0;
float q0 = 1.0f, q1 = 0.0f, q2 = 0.0f, q3 = 0.0f;
float DCM00 = 1.0;
float DCM01 = 0.0;
float DCM02 = 0.0;
float DCM10 = 0.0;
float DCM11 = 1.0;
float DCM12 = 0.0;
float DCM20 = 0.0;
float DCM21 = 0.0;
float DCM22 = 1.0;
void MadgwickAhrsFilter(float gx,float gy,float gz,float a_x,float a_y,float a_z)
{

	float norm;
	float qDot_omega_1, qDot_omega_2, qDot_omega_3, qDot_omega_4;
	float f_1, f_2, f_3;
	float J_11or24, J_12or23, J_13or22, J_14or21, J_32, J_33;
	float qHatDot_1, qHatDot_2, qHatDot_3, qHatDot_4;

	float halfq0 = 0.5f * q0;
	float halfq1 = 0.5f * q1;
	float halfq2 = 0.5f * q2;
	float halfq3 = 0.5f * q3;
	float twoq0 = 2.0f * q0;
	float twoq1 = 2.0f * q1;
	float twoq2 = 2.0f * q2;

	norm = sqrt(a_x * a_x + a_y * a_y + a_z * a_z);
	a_x /= norm;
	a_y /= norm;
	a_z /= norm;

	f_1 = twoq1 * q3 - twoq0 * q2 - a_x;
	f_2 = twoq0 * q1 + twoq2 * q3 - a_y;
	f_3 = 1.0f - twoq1 * q1 - twoq2 * q2 - a_z;
	J_11or24 = twoq2;
	J_12or23 = 2.0f * q3;
	J_13or22 = twoq0;
	J_14or21 = twoq1;
	J_32 = 2.0f * J_14or21;
	J_33 = 2.0f * J_11or24;

	qHatDot_1 = J_14or21 * f_2 - J_11or24 * f_1;
	qHatDot_2 = J_12or23 * f_1 + J_13or22 * f_2 - J_32 * f_3;
	qHatDot_3 = J_12or23 * f_2 - J_33 * f_3 - J_13or22 * f_1;
	qHatDot_4 = J_14or21 * f_1 + J_11or24 * f_2;

	norm = sqrt(qHatDot_1 * qHatDot_1 + qHatDot_2 * qHatDot_2 + qHatDot_3 * qHatDot_3 + qHatDot_4 * qHatDot_4);
	qHatDot_1 /= norm;
	qHatDot_2 /= norm;
	qHatDot_3 /= norm;
	qHatDot_4 /= norm;

	qDot_omega_1 = -halfq1 * gx - halfq2 * gy - halfq3 * gz;
	qDot_omega_2 = halfq0 * gx + halfq2 * gz - halfq3 * gy;
	qDot_omega_3 = halfq0 * gy - halfq1 * gz + halfq3 * gx;
	qDot_omega_4 = halfq0 * gz + halfq1 * gy - halfq2 * gx;

	q0 += (qDot_omega_1 - (beta1 * qHatDot_1)) * Elapsed_time_Ahrs;
	q1 += (qDot_omega_2 - (beta1 * qHatDot_2)) * Elapsed_time_Ahrs;
	q2 += (qDot_omega_3 - (beta1 * qHatDot_3)) * Elapsed_time_Ahrs;
	q3 += (qDot_omega_4 - (beta1 * qHatDot_4)) * Elapsed_time_Ahrs;

	norm = sqrt(q0 * q0 + q1 * q1 + q2 * q2 + q3 * q3);
	q0 /= norm;
	q1 /= norm;
	q2 /= norm;
	q3 /= norm;
	float q0q1 = q0*q1;
	float q0q2 = q0*q2;
	float q0q3 = q0*q3;
	float q1q1 = q1*q1;
	float q1q2 = q1*q2;
	float q1q3 = q1*q3;
	float q2q2 = q2*q2;
	float q2q3 = q2*q3;
	float q3q3 = q3*q3;

	DCM00 = 2*(0.5 - q2q2 - q3q3);
	DCM01 = 2*(q1q2 - q0q3);
	DCM02 = 2*(q1q3 + q0q2);
	DCM10 = 2*(q1q2 + q0q3);
	DCM11 = 2*(0.5 - q1q1 - q3q3);
	DCM12 = 2*(q2q3 - q0q1);
	DCM20 = 2*(q1q3 - q0q2);
	DCM21 = 2*(q2q3 + q0q1);
	DCM22 = 2*(0.5 - q1q1 - q2q2);

	ahrs_y=atan2(DCM10, DCM00)*RAD_TO_DEG;
	ahrs_p=-asin(DCM20)*RAD_TO_DEG;
	ahrs_r=atan2(DCM21, DCM22)*RAD_TO_DEG;

	Ahrs_YAW     = 0.5*ahrs_y  + 0.5*last_ahrs_y;
	Ahrs_PITCH   = 0.5*ahrs_p  + 0.5*last_ahrs_p;
	Ahrs_ROLL    = 0.5*ahrs_r  + 0.5*last_ahrs_r;

	last_ahrs_y  =  Ahrs_YAW;
	last_ahrs_p  =  Ahrs_PITCH;
	last_ahrs_r  =  Ahrs_ROLL;
}
