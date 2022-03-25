/*
 * PID.h
 *
 *  Created on: 14 Mar 2021
 *      Author: karam
 */

#ifndef INC_PID_H_
#define INC_PID_H_

typedef struct {

	float Kp;
	float Ki;
	float Kd;

	float tau;// low pass filter

	float limMin;
	float limMax;

	float limMinInt;
	float limMaxInt;

	float Elapsed_Time;

	float integrator;
	float prevError;
	float differentiator;
	float prevMeasurement;

	float out;

} PIDController;

PIDController Roll;
PIDController Pitch;
PIDController Yaw;
PIDController Altitude;

PIDController PIDRollPositionControl;
PIDController PIDPitchPositionControl;

void PID_init(PIDController *Pid);

void resetPid();
float PID(float Set_Value, float Actual_Value, float Kp, float Ki, float Kd, float Limit, double dt,float *integral,float *pre_error);
float PID2(PIDController *pid, float setpoint, float measurement);
#endif /* INC_PID_H_ */
