/*
 * ReadingSensor.h
 *
 *  Created on: 3 Eyl 2021
 *      Author: PC_1830
 */

#ifndef INC_READINGSENSOR_H_
#define INC_READINGSENSOR_H_

#include <Hmc5883L.h>
#include "TJ_MPU6050.h"
#include "Uav_Global.h"
#define DEG_TO_RAD 0.01745329251994329576923690768489
#define RAD_TO_DEG 57.2957795
#define Elapsed_time_Ahrs 0.005
#define GyroScalingFactor 0.030525030525*1.7 //   normal değeri bu değil zamandan okurken oluşan kayıpları telafi etmek için böyle birşey yaptım
#define AccelScalingFactor 0.0001220703125  //    1/8192 den geliyor datasheetden
#define Sample 2000
#define Gravity 9.8066

typedef struct
{
	float ImuRollVelocity; // X eksenindeki konum
	float ImuPitchVelocity;// Y eksenindeki konum
	float ImuYawVelocity;   // Z eksenindeki konum
}Imu_Vel_HandleTypedef;

typedef struct
{
	float Gyro_Roll_Set;
	float Gyro_Pitch_Set;
	float Gyro_Yaw_Set;
	float Gyro_Roll_Offset_Cal;
	float Gyro_Pitch_Offset_Cal;
	float Gyro_Yaw_Offset_Cal;
	float Gyro_Roll_Ahrs;
	float Gyro_Pitch_Ahrs;
	float Gyro_Yaw_Ahrs;
	float Gyro_Roll_Ahrs1;
	float Gyro_Pitch_Ahrs1;
	float Gyro_Yaw_Ahrs1;
	float Gyro_Roll_Degree;
	float Gyro_Pitch_Degree;
	float Gyro_Yaw_Degree;
	float Accel_Roll_Set;
	float Accel_Pitch_Set;
	float Accel_Yaw_Set;
	float Accel_Roll_Offset_Cal;
	float Accel_Pitch_Offset_Cal;
	float Accel_Yaw_Offset_Cal;
	float Accel_Roll_Degree;
	float Accel_Pitch_Degree;
	float ComplementaryRoll ;
	float ComplementaryPitch;
	float ComplementaryYaw  ;
//	float Gyro_Roll_LPF;
//	float Gyro_Pitch_LPF;
//	float Gyro_Yaw_LPF;
}Imu_HandleTypeDef;


typedef struct
{
	float RollMergeAccelemeter;
	float PitchMergeAccelemeter;
	float YawGyroMerge;
	float PitchGyroMerge;
	float RollGyroMerge;
}ImuMerge_HandleTypeDef;

float ComplementaryFAngleRoll,ComplementaryFAnglePitch,ComplementaryFAngleYaw;
float Roll_Gyro_Merge,Pitch_Gyro_Merge,Yaw_Gyro_Merge;

float gravityAccel;

RawData_Def myAccelRaw, myGyroRaw;
Imu_HandleTypeDef Mpu;
Imu_Vel_HandleTypedef MpuVelocity;

float Remove_Gravity_effect;

int m;

void ReadingSensorFilter();
void MPU6050();
void ICM20689();
void HMC5883L();
void Offset_Calculate();
void MPU6050AHRS();
float AccelToVelocity(float *VelocityData,float AccelData,float Dt);


#endif /* INC_READINGSENSOR_H_ */
