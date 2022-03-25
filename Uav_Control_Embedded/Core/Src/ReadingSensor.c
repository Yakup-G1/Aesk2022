/*
 * ReadingSensor.c
 *
 *  Created on: 3 Eyl 2021
 *      Author: PC_1830
 */
#include "ReadingSensor.h"
#include "Filter.h"

void Offset_Calculate()
{
	for(int i = 0 ; i < Sample ; i++)
	{
		MPU6050_Get_Accel_RawData(&myAccelRaw);
		MPU6050_Get_Gyro_RawData(&myGyroRaw);

		Mpu.Gyro_Roll_Offset_Cal   += myGyroRaw.x  * GyroScalingFactor;
		Mpu.Gyro_Pitch_Offset_Cal  += myGyroRaw.y  * GyroScalingFactor;
		Mpu.Gyro_Yaw_Offset_Cal    += myGyroRaw.z  * GyroScalingFactor;
		Mpu.Accel_Roll_Offset_Cal  += myAccelRaw.x * AccelScalingFactor;
		Mpu.Accel_Pitch_Offset_Cal += myAccelRaw.y * AccelScalingFactor;
		Mpu.Accel_Yaw_Offset_Cal   += myAccelRaw.z * AccelScalingFactor;

		HAL_Delay(3);
		if(system_clock_counter_1ms%50==0)
		{

			if(m==1)
			{
				HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, 0);
				HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_1);
			}
			if(m==2)
			{
				HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_1);
				HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_2);
			}
			if(m==3)
			{
				HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_2);
				HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_3);
			}
			if(m==4)
			{
				HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_3);
				HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, 1);
				m=0;
			}

			m+=1;
		}

		// başka bir şekilde bekletmeliyiz ı2c sorunu bundan kaynaklanıyor olabilir
	    // ledler eklenecek buraya kalibrasyon oluyor ledleri
	}
	HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_3);

	Mpu.Gyro_Roll_Offset_Cal   /= Sample;
	Mpu.Gyro_Pitch_Offset_Cal  /= Sample;
	Mpu.Gyro_Yaw_Offset_Cal    /= Sample;
	Mpu.Accel_Roll_Offset_Cal  /= Sample;
	Mpu.Accel_Pitch_Offset_Cal /= Sample;
	Mpu.Accel_Yaw_Offset_Cal   /= Sample;
}
void MPU6050()// ivmeölçer ve gyro yaw değerleri eksi ile çarpılabilir
{
	MPU6050_Get_Accel_RawData(&myAccelRaw);
	MPU6050_Get_Gyro_RawData(&myGyroRaw);

	Mpu.Accel_Roll_Set   = (myAccelRaw.x * AccelScalingFactor) - Mpu.Accel_Roll_Offset_Cal   ;
	Mpu.Accel_Pitch_Set  = (myAccelRaw.y * AccelScalingFactor) - Mpu.Accel_Pitch_Offset_Cal   ;
	Mpu.Accel_Yaw_Set    = (myAccelRaw.z * AccelScalingFactor)								  ;//offset verilmesine gerek yok offsett verilecekse yanına 1 ekle
	Mpu.Gyro_Roll_Set    = (myGyroRaw.x  * GyroScalingFactor)  - Mpu.Gyro_Roll_Offset_Cal     ;
	Mpu.Gyro_Pitch_Set   = (myGyroRaw.y  * GyroScalingFactor)  - Mpu.Gyro_Pitch_Offset_Cal    ;
	Mpu.Gyro_Yaw_Set     = (myGyroRaw.z  * GyroScalingFactor)  - Mpu.Gyro_Yaw_Offset_Cal      ;

//	Mpu.Gyro_Roll_LPF    = (Mpu.Gyro_Roll_LPF * 0.8) + (Mpu.Gyro_Roll_Set  * 0.2); // low pass filtre gyroskop gürültülerini önlemek için
//	Mpu.Gyro_Pitch_LPF   = (Mpu.Gyro_Pitch_LPF* 0.8) + (Mpu.Gyro_Pitch_Set * 0.2);
//	Mpu.Gyro_Yaw_LPF     = (Mpu.Gyro_Yaw_LPF  * 0.8) + (Mpu.Gyro_Yaw_Set   * 0.2);
//
//	Mpu.Accel_Roll_Degree  = atan((Mpu.Accel_Pitch_Set)/sqrt(pow((Mpu.Accel_Roll_Set),2) + pow((Mpu.Accel_Yaw_Set),2)))*RAD_TO_DEG;// complementary için gerekli
//	Mpu.Accel_Pitch_Degree = atan(-1*(Mpu.Accel_Roll_Set )/sqrt(pow((Mpu.Accel_Pitch_Set),2) + pow((Mpu.Accel_Yaw_Set),2)))*RAD_TO_DEG;


	// Notch butterworth second order low pass filter ile filtrelendi
	Butterworth(&AccelRollFiltered  , Mpu.Accel_Roll_Set);
	Butterworth(&AccelPitchFiltered , Mpu.Accel_Pitch_Set);
	Butterworth(&AccelYawFiltered   , Mpu.Accel_Yaw_Set);
	Butterworth(&GyroRollFiltered   , Mpu.Gyro_Roll_Set);
	Butterworth(&GyroPitchFiltered  , Mpu.Gyro_Pitch_Set);
	Butterworth(&GyroYawFiltered    , Mpu.Gyro_Yaw_Set);

	gravityAccel = AccelYawFiltered.NotchFilterOut*9.81;

//	Mpu.Gyro_Roll_Ahrs   = Mpu.Gyro_Roll_Set  * Elapsed_time;//complementary ve Ahrs filtre girişlerine bunları uygulamalıyız
//	Mpu.Gyro_Pitch_Ahrs  = Mpu.Gyro_Pitch_Set * Elapsed_time;
//	Mpu.Gyro_Yaw_Ahrs    = Mpu.Gyro_Yaw_Set   * Elapsed_time;
//
//	Mpu.Gyro_Roll_Ahrs   = GyroRollFiltered.NotchFilterOut  * Elapsed_time;//complementary ve Ahrs filtre girişlerine bunları uygulamalıyız
//	Mpu.Gyro_Pitch_Ahrs  = GyroPitchFiltered.NotchFilterOut * Elapsed_time;
//	Mpu.Gyro_Yaw_Ahrs    = GyroYawFiltered.NotchFilterOut   * Elapsed_time;
//
//
//	Mpu.Gyro_Roll_Degree  += Mpu.Gyro_Roll_Set  * Elapsed_time;//yanlışlıkla complementaryde kullanma
//	Mpu.Gyro_Pitch_Degree += Mpu.Gyro_Pitch_Set * Elapsed_time;
//	Mpu.Gyro_Yaw_Degree   += Mpu.Gyro_Yaw_Set   * Elapsed_time;//imudan elde edilen yaw açısı joob broking roll ve pitch deki hatayı eklemeye bak
//
//	Mpu.ComplementaryRoll = (float)(0.992*(Mpu.ComplementaryRoll + Mpu.Gyro_Roll_Ahrs)  + 0.008*Mpu.Accel_Roll_Degree); // complementary filtre şuanda madwick ahrs filtrede sorun çıkar geçilebilir
//	Mpu.ComplementaryPitch= (float)(0.992*(Mpu.ComplementaryPitch+ Mpu.Gyro_Pitch_Ahrs)  + 0.008*Mpu.Accel_Pitch_Degree);
//
//	Mpu.ComplementaryRoll = (float)(0.992*(Mpu.ComplementaryRoll + Mpu.Gyro_Roll_Ahrs)  + 0.008*AccelRollFiltered.NotchFilterOut); // complementary filtre şuanda madwick ahrs filtrede sorun çıkar geçilebilir
//	Mpu.ComplementaryPitch= (float)(0.992*(Mpu.ComplementaryPitch+ Mpu.Gyro_Pitch_Ahrs)  + 0.008*AccelPitchFiltered.NotchFilterOut);
//	Mpu.ComplementaryYaw  = Mpu.Gyro_Yaw_Degree; //özel olarak ilgilen hmc ile birleştir

}

void MPU6050AHRS()
{
	Mpu.Gyro_Roll_Ahrs1  = GyroRollFiltered.NotchFilterOut   * Elapsed_time_Ahrs;//complementary ve Ahrs filtre girişlerine bunları uygulamalıyız
	Mpu.Gyro_Pitch_Ahrs1 = GyroPitchFiltered.NotchFilterOut  * Elapsed_time_Ahrs;
	Mpu.Gyro_Yaw_Ahrs1   = GyroYawFiltered.NotchFilterOut    * Elapsed_time_Ahrs;

	Remove_Gravity_effect = AccelYawFiltered.NotchFilterOut - Mpu.Accel_Yaw_Set;

	AccelToVelocity(&MpuVelocity.ImuRollVelocity, -AccelRollFiltered.NotchFilterOut*Gravity, Elapsed_time_Ahrs);
	AccelToVelocity(&MpuVelocity.ImuPitchVelocity,-AccelPitchFiltered.NotchFilterOut*Gravity, Elapsed_time_Ahrs);
	AccelToVelocity(&MpuVelocity.ImuYawVelocity, Remove_Gravity_effect*Gravity, Elapsed_time_Ahrs);
}
void HMC5883L()// manyotometre değerinin okunanarak manyotometre açısı için işlemlerin yapılması
{
	ManyometerReadValue();
	cx= (int)(Mag_Raw_X*cos(ComplementaryFAnglePitch*DEG_TO_RAD)+Mag_Raw_Y*sin(ComplementaryFAngleRoll*DEG_TO_RAD)*sin(ComplementaryFAnglePitch*DEG_TO_RAD)-Mag_Raw_Z*cos(ComplementaryFAngleRoll*DEG_TO_RAD)*sin(ComplementaryFAnglePitch*DEG_TO_RAD));
	cy= (int)(Mag_Raw_Y*cos(ComplementaryFAngleRoll*DEG_TO_RAD)+Mag_Raw_Z*sin(ComplementaryFAngleRoll*DEG_TO_RAD));

	magno_bearing = 180/M_PI * atan2((float)(cy),(float)(cx));

	if(magno_bearing<0)
	{
		magno_bearing = magno_bearing + 360;
	}
	if(magno_bearing > 360)
	{
		magno_bearing = magno_bearing - 360;
	}
}
float AccelToVelocity(float *VelocityData,float AccelData,float Dt)
{
	return *VelocityData += AccelData * Dt;
}

