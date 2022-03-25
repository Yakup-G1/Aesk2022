/*
 * Kumanda.h
 *
 *  Created on: Feb 12, 2021
 *      Author: karam
 */
#include "main.h"

#ifndef INC_KUMANDA_H_
#define INC_KUMANDA_H_

#define Max_Axis_Value 25
#define Max_Yaw_Value 180
#define Max_Throttle 1990
#define Min_Throttle 1010
#define Altitude_Max_Value 5
#define Altitude_Min_Value 0
#define VelocityCoefficient 0.005
#define LevelAdjustCoefficient 27
#define LevelDivededValue 3
#define MaxDeadband 1520
#define MindDeadband 1480
#define ThrottleMaxDeadband 1600
#define ThrottleMinDeadband 1400
#define RcScale 0.27

typedef struct
{
	uint16_t Ch1;
	uint16_t Ch2;
	uint16_t Ch3;
	uint16_t Ch4;
	uint16_t Ch5;
	uint16_t Ch6;
	uint16_t Ch7;
	uint16_t Ch8;
	uint16_t Ch9;
	uint16_t Ch10;
	uint16_t Ch11;
	uint16_t Ch12;
	uint16_t Ch13;
	uint16_t Ch14;
	uint16_t Ch15;
	uint16_t Ch16;
}Rx;



uint8_t Rx_buffer[32];
uint8_t Rx_temp;
Rx Rc;

typedef struct
{
	uint16_t ReceiveTrue;
	uint16_t ConnectTrue;

}RemoteControl;
RemoteControl RcTrue;

typedef struct
{
	int16_t Raw;
	float Velocity;
	float Setpoint;
	float FeedForward;
	float TargetPosition;
	float TargetPositionVelocity;

}RemoteControlAxis;

float ThrottleLevelAdjustCoefficient;
int PositionLevelCoefficient;
float HeightError;
float LD;
float AltitudeCalculator;

RemoteControlAxis RemoteRoll,RemotePitch,RemoteYaw,RemoteThrottle;
void Kumanda_True();
void FailSafe();
void RemotoControlMapping();
void RemoteControlRate();
void DeadBand();
void AltitudeControl();
void PositionControl();

#endif /* INC_KUMANDA_H_ */
