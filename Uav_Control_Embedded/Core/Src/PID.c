/*
 * PID.c
 *
 *  Created on: 14 Mar 2021
 *      Author: karam
 */
#include <stdlib.h>
#include <string.h>
#include "PID.h"
#include "MotorPowerCalculate.h"
//Nottt pihll lab pid sine bak
float PID(float Set_Value, float Actual_Value, float Kp, float Ki, float Kd, float Limit, double Elapsed_Time,float *integral,float *pre_error)
{
	float error;
	float derivative;
	float output;

	error = Set_Value - Actual_Value;
	if(Kd !=0)
	{
		derivative = (error - *pre_error) / Elapsed_Time;//
	}
	else{
		derivative=0;
	}
	// Anti wind-up kontrolü
	output = Kp*error + Ki*(*integral) + Kd*derivative;
	if(abs((int)output) >= Limit && (((error >= 0) && (*integral >= 0)) || ((error < 0) && (*integral < 0))))
	{
			*integral = *integral;
	}
	else
	{
		*integral = *integral + (Elapsed_Time * error);
	}


	if(abs((int)output) >= Limit)
	{
		if(output < 0)
		{
			output = -Limit;
		}
		else
		{
			output = Limit;
		}
  }
	*pre_error = error;
	return output;
}
//float PIDAltitude(float Set_Value,float Actual_Value, float Kp, float Ki, float Kd, float Limit, double Elapsed_Time,float *integral,float *pre_error)
//{
//	float error;
//	float derivative;
//	float output;
//
//	error = Set_Value - Actual_Value;
//	if(Kd !=0)
//	{
//		derivative = (error - *pre_error) / Elapsed_Time;
//	}
//	else{
//		derivative=0;
//	}
//
//	// Anti-windup clamp method
//	output = Kp*error + Ki*(*integral) + Kd*derivative;
//	if(abs((int)output) >= Limit && (((error >= 0) && (*integral >= 0)) || ((error < 0) && (*integral < 0))))
//	{
//			*integral = *integral;
//	}
//	else
//	{
//		*integral = *integral + (Elapsed_Time * error);
//	}
//
//
//	if(abs((int)output) >= Limit)
//	{
//		if(output < 0)
//		{
//			output = -Limit;
//		}
//		else
//		{
//			output = Limit;
//		}
//  }
//	*pre_error = error;
//	return output;
//}

float PID2(PIDController *pid, float setpoint, float measurement)//  referance adresi buradadır https://www.youtube.com/watch?v=zOByx3Izf5U
{

    float error = setpoint - measurement;

    float proportional = pid->Kp * error;

    pid->integrator = pid->integrator + 0.5f * pid->Ki * pid->Elapsed_Time * (error + pid->prevError);

    if (pid->integrator > pid->limMaxInt) {

        pid->integrator = pid->limMaxInt;

    } else if (pid->integrator < pid->limMinInt) {

        pid->integrator = pid->limMinInt;

    }

    pid->differentiator = -(2.0f * pid->Kd * (measurement - pid->prevMeasurement)
                        + (2.0f * pid->tau - pid->Elapsed_Time) * pid->differentiator)
                        / (2.0f * pid->tau + pid->Elapsed_Time);

    pid->out = proportional + pid->integrator + pid->differentiator;

    if (pid->out > pid->limMax)
    {
        pid->out = pid->limMax;
    }
    else if (pid->out < pid->limMin)
    {
        pid->out = pid->limMin;
    }

    pid->prevError       = error;
    pid->prevMeasurement = measurement;


    return pid->out;

}
void PID_init(PIDController *Pid)// pid değerlerinin kumanda iletimi kesildiğinde sıfırlanma fonksiyonu
{

	Pid->integrator = 0.0f;
	Pid->prevError  = 0.0f;

	Pid->differentiator  = 0.0f;
	Pid->prevMeasurement = 0.0f;

	Pid->out = 0.0f;


}


void resetPid()// pid değerlerinin kumanda iletimi kesildiğinde sıfırlanma fonksiyonu
{
	Roll_Last_Error   =0;
	Pitch_Last_Error  =0;
	Yaw_Last_Error    =0;
	Altitude_Last_Error=0;

	Roll_Pid_i=0;
	Pitch_Pid_i=0;
	Yaw_Pid_i=0;
    Altitude_Pid_i=0;
}



