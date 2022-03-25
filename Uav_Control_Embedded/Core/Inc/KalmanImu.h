/*
 * Kalman2.h
 *
 *  Created on: 21 Tem 2021
 *      Author: karam
 */

#ifndef INC_KALMANIMU_H_
#define INC_KALMANIMU_H_

float Q_angle;
float Q_bias;
float R_measure;

float angle;
float bias;
float rate;

float Kalman[2][2]; // Error covariance matrix - This is a 2x2 matrix

float Kalman_filter(float AccelemeterAngle, float GyroRate, float ElapsedTime);
#endif /* INC_KALMANIMU_H_ */
