/*
 * Kalman2.c
 *
 *  Created on: 21 Tem 2021
 *      Author: karam
 */
#include <KalmanImu.h>
int Counter = 0;

float Kalman_filter(float AccelemeterAngle, float GyroRate, float ElapsedTime)
{
	if(Counter==0)
	{
		Q_angle = 0.001;
		Q_bias = 0.003;
		R_measure = 0.03;
		angle = 0.0;
		bias = 0.0;

		Kalman[0][0] = 0.0;
		Kalman[0][1] = 0.0;
		Kalman[1][0] = 0.0;
		Kalman[1][1] = 0.0;
		Counter++;
	}
	rate = GyroRate - bias;
	angle += ElapsedTime * rate;

	Kalman[0][0] += ElapsedTime * (ElapsedTime*Kalman[1][1] - Kalman[0][1] - Kalman[1][0] + Q_angle);
	Kalman[0][1] -= ElapsedTime * Kalman[1][1];
	Kalman[1][0] -= ElapsedTime * Kalman[1][1];
	Kalman[1][1] += Q_bias * ElapsedTime;

	float S = Kalman[0][0] + R_measure;

	float K[2];
	K[0] = Kalman[0][0] / S;
	K[1] = Kalman[1][0] / S;

	float y = AccelemeterAngle - angle;
	angle += K[0] * y;
	bias += K[1] * y;

	float P00_temp = Kalman[0][0];
	float P01_temp = Kalman[0][1];

	Kalman[0][0] -= K[0] * P00_temp;
	Kalman[0][1] -= K[0] * P01_temp;
	Kalman[1][0] -= K[1] * P00_temp;
	Kalman[1][1] -= K[1] * P01_temp;

	return angle;
}

