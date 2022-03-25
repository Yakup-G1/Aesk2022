/*
 * AhrsFilter2.c
 *
 *  Created on: 28 Şub 2022
 *      Author: karam
 */


#include "AhrsFilter2.h"
#include <math.h>
#include "ReadingSensor.h"

// Filtre Katsayi Tanimlamalari

#define betaDef			0.02f									// 0-1 arasinda  0.15ti (0 tamamen gyro, 1'e yaklastikca ivmeye daha cok guvenir)
#define zeta 				0.01f					 			// Drift düzeltme katsayisi

//---------------------------------------------------------------------------------------------------
// Degisken Tanimlamalari
volatile float beta = betaDef;									// Filtre içi katsayi tanimlama
volatile float SEq_1=1.0f, SEq_2=0.0f, SEq_3=0.0f,SEq_4=0.0f;	// Quaternion tanimi
//volatile float q0=1.0f, q1=0.0f, q2=0.0f,q3=0.0f;				// Quaternion tanimi
volatile float SEqHatDot_1,SEqHatDot_2,SEqHatDot_3,SEqHatDot_4;	// Quaternion türev tanimi
volatile float b_x=1.0f,b_z=0.0f;								// Filtre Katsayisi
volatile float w_err_x=0.0f,w_err_y=0.0f,w_err_z=0.0f;			// Açisal hiz hata tahmini
volatile float w_bx=0.0f,w_by=0.0f,w_bz=0.0f;					// Açisal hiz bias
volatile float w_x,w_y,w_z;									    // Açisal hiz tahmini																																// Filtre çalisma periyodu
extern float dt_IMU;											// IMU ölçüm periyodu
float Madg_Roll,Madg_Pitch,Madg_Yaw;							// Roll Pitch Yaw Tahmin Edilen Açi
float invSqrt(float x);											// Hizli matris tersini alma fonksiyonu

float madg_quaternion[4]={0};
float madg_eulerd[3]={0};

//IMU+MARG AHRS Tahmin Filtresi
void MadgwickAHRSupdate(float gx, float gy, float gz, float ax, float ay, float az, float mx, float my, float mz) {

	 volatile float f_1,f_2,f_3,f_4,f_5,f_6;
	 volatile float J11_24,J12_23,J13_22,J14_21,J32,J33,J41,J42,J43,J44,J51,J52,J53,J54,J61,J62,J63,J64;
	 volatile float SEqHatDot_1,SEqHatDot_2,SEqHatDot_3,SEqHatDot_4;
//	 volatile float SEq_dot_omega_1,SEq_dot_omega_2,SEq_dot_omega_3,SEq_dot_omega_4;
	 volatile float	SEqDot_omega_1,SEqDot_omega_2,SEqDot_omega_3,SEqDot_omega_4;
	 volatile float norm_temp;
	 volatile float h_x,h_y,h_z;
	// Eger manyetometre yoksa
	if((mx == 0.0f) && (my == 0.0f) && (mz == 0.0f))
		{
		// Yalnizca IMU AHRS Tahmin Filresi Çalistir
		MadgwickAHRSupdateIMU(gx, gy, gz, ax, ay, az);
		return;
		}

	// Eger ivmeölçer verilerinde bir problem yoksa
	if(!((ax <=0.001f) && (ay <= 0.01f) && (az <= 0.1f))) {

		// Madgwick Algoritmasi
  	norm_temp = sqrt(ax * ax + ay * ay + az * az);
	ax =ax/norm_temp;
	ay =ay/norm_temp;
	az =az/norm_temp;

	norm_temp = sqrt(mx * mx + my * my + mz * mz);
	mx =mx/norm_temp;
	my =my/norm_temp;
	mz =mz/norm_temp;

	h_x = 2.0f*mx * (0.5f - SEq_3 * SEq_3 - SEq_4 * SEq_4) + 2.0f*my * (SEq_2*SEq_3 - SEq_1*SEq_4) + 2.0f*mz * (SEq_2*SEq_4 + SEq_1*SEq_3);
	h_y = 2.0f*mx * (SEq_2*SEq_3 + SEq_1*SEq_4) + 2.0f*my * (0.5f - SEq_2 * SEq_2 - SEq_4 * SEq_4) + 2.0f*mz * (SEq_3*SEq_4 - SEq_1*SEq_2);
	h_z = 2.0f*mx * (SEq_2*SEq_4 - SEq_1*SEq_3) + 2.0f*my * (SEq_3*SEq_4 + SEq_1*SEq_2) + 2.0f*mz * (0.5f - SEq_2 * SEq_2 - SEq_3 * SEq_3);

	b_x = sqrt((h_x * h_x) + (h_y * h_y));
	b_z = h_z;

	f_1=       2.0f*SEq_2*SEq_4 - 2.0f*SEq_1*SEq_3 - ax;
	f_2=       2.0f*SEq_1*SEq_2 + 2.0f*SEq_3*SEq_4 - ay;
	f_3=1.0f - 2.0f*SEq_2*SEq_2 - 2.0f*SEq_3*SEq_3 - az;
	f_4 = 2.0f*b_x * (0.5f - SEq_3 * SEq_3 - SEq_4 * SEq_4) + 2.0f*b_z * (SEq_2*SEq_4 - SEq_1*SEq_3) - mx;
	f_5 = 2.0f*b_x * (SEq_2 * SEq_3 - SEq_1 * SEq_4) + 2.0f*b_z * (SEq_1 * SEq_2 + SEq_3 * SEq_4) - my;
	f_6 = 2.0f*b_x * (SEq_1*SEq_3 + SEq_2*SEq_4) + 2.0f*b_z * (0.5f - SEq_2 * SEq_2 - SEq_3 * SEq_3) - mz;

	J11_24 = 2.0f*SEq_3;
	J12_23 = 2.0f*SEq_4;
	J13_22 = 2.0f*SEq_1;
	J14_21 = 2.0f*SEq_2;
	J32 = 2.0f * J14_21;
	J33 = 2.0f * J11_24;
	J41 = 2.0f * b_z*SEq_3;
	J42 = 2.0f * b_z*SEq_4;
	J43 = 2.0f * 2.0f*b_x*SEq_3 + 2.0f*b_z*SEq_1;
	J44 = 2.0f * 2.0f*b_x*SEq_4 - 2.0f*b_z*SEq_2;
	J51 = 2.0f*b_x*SEq_4 - 2.0f*b_z*SEq_2;
	J52 = 2.0f*b_x*SEq_3 + 2.0f*b_z*SEq_1;
	J53 = 2.0f*b_x*SEq_2 + 2.0f*b_z*SEq_4;
	J54 = 2.0f*b_x*SEq_1 - 2.0f*b_z*SEq_3;
	J61 = 2.0f*b_x*SEq_3;
	J62 = 2.0f*b_x*SEq_4 - 2.0f * 2.0f*b_z*SEq_2;
	J63 = 2.0f*b_x*SEq_1 - 2.0f * 2.0f*b_z*SEq_3;
	J64 = 2.0f*b_x*SEq_2;

	SEqHatDot_1 = J14_21 * f_2 - J11_24 * f_1 - J41    * f_4 - J51 * f_5 + J61 * f_6;
	SEqHatDot_2 = J12_23 * f_1 + J13_22 * f_2 - J32    * f_3 + J42 * f_4 + J52 * f_5 + J62 * f_6;
	SEqHatDot_3 = J12_23 * f_2 - J33    * f_3 - J13_22 * f_1 - J43 * f_4 + J53 * f_5 + J63 * f_6;
	SEqHatDot_4 = J14_21 * f_1 + J11_24 * f_2 - J44    * f_4 - J54 * f_5 + J64 * f_6;

	norm_temp=sqrt(SEqHatDot_1*SEqHatDot_1+SEqHatDot_2*SEqHatDot_2+SEqHatDot_3*SEqHatDot_3+SEqHatDot_4*SEqHatDot_4);

	SEqHatDot_1=SEqHatDot_1/norm_temp;
	SEqHatDot_2=SEqHatDot_2/norm_temp;
	SEqHatDot_3=SEqHatDot_3/norm_temp;
	SEqHatDot_4=SEqHatDot_4/norm_temp;

	w_err_x = 2.0f*SEq_1 * SEqHatDot_2 - 2.0f*SEq_2 * SEqHatDot_1 - 2.0f*SEq_3 * SEqHatDot_4 + 2.0f*SEq_4 * SEqHatDot_3;
	w_err_y = 2.0f*SEq_1 * SEqHatDot_3 + 2.0f*SEq_2 * SEqHatDot_4 - 2.0f*SEq_3 * SEqHatDot_1 - 2.0f*SEq_4 * SEqHatDot_2;
	w_err_z = 2.0f*SEq_1 * SEqHatDot_4 - 2.0f*SEq_2 * SEqHatDot_3 + 2.0f*SEq_3 * SEqHatDot_2 - 2.0f*SEq_4 * SEqHatDot_1;

	w_bx = w_bx+ w_err_x *zeta*Elapsed_time_Ahrs;
	w_by = w_by+ w_err_y *zeta*Elapsed_time_Ahrs;
	w_bz = w_bz+ w_err_z *zeta*Elapsed_time_Ahrs;
	w_x =gx*(M_PI/180.0f)- w_bx;
	w_y =gy*(M_PI/180.0f)- w_by;
	w_z =gz*(M_PI/180.0f)- w_bz;


	SEqDot_omega_1 = -SEq_2/2.0f * w_x -SEq_3/2.0f * w_y - SEq_4/2.0f * w_z;
	SEqDot_omega_2 = SEq_1/2.0f * w_x + SEq_3/2.0f * w_z - SEq_4/2.0f * w_y;
	SEqDot_omega_3 = SEq_1/2.0f * w_y - SEq_2/2.0f * w_z + SEq_4/2.0f * w_x;
	SEqDot_omega_4 = SEq_1/2.0f * w_z + SEq_2/2.0f * w_y - SEq_3/2.0f * w_x;

	SEq_1 =SEq_1+ (SEqDot_omega_1 - (beta * SEqHatDot_1))*Elapsed_time_Ahrs;
	SEq_2 =SEq_2+ (SEqDot_omega_2 - (beta * SEqHatDot_2))*Elapsed_time_Ahrs;
	SEq_3 =SEq_3+ (SEqDot_omega_3 - (beta * SEqHatDot_3))*Elapsed_time_Ahrs;
	SEq_4 =SEq_4+ (SEqDot_omega_4 - (beta * SEqHatDot_4))*Elapsed_time_Ahrs;

	norm_temp=sqrt(SEq_1*SEq_1+SEq_2*SEq_2+SEq_3*SEq_3+SEq_4*SEq_4);

	// Sonuç Oryantasyonu (Quaternion)
	SEq_1=SEq_1/norm_temp;
	SEq_2=SEq_2/norm_temp;
	SEq_3=SEq_3/norm_temp;
	SEq_4=SEq_4/norm_temp;

		// Quaternion Euler Açi Dönüsümü
	Quat_to_Deg(SEq_1,SEq_2,SEq_3,SEq_4);

	madg_quaternion[0] = SEq_1;
	madg_quaternion[1] = SEq_2;
	madg_quaternion[2] = SEq_3;
	madg_quaternion[3] = SEq_4;

	Madg_Roll=madg_eulerd[0]*180.0f/M_PI;
	Madg_Pitch=madg_eulerd[1]*180.0f/M_PI;
	Madg_Yaw=madg_eulerd[2]*180.0f/M_PI;

	Madg_Yaw+=5.32f;

	if(Madg_Yaw<0.0f)Madg_Yaw+=360.0f;
	if(Madg_Yaw>360.0f)Madg_Yaw-=360.0f;

	if(Madg_Yaw>360.0f)
	{
		Madg_Yaw=Madg_Yaw-360.0f;
	}

	}
}
//IMU+MARG AHRS Tahmin Filtresi
void MadgwickAHRSupdateIMU(float gx, float gy, float gz, float ax, float ay, float az) {

	 // Filtre lokal degiskenleri
	 volatile float f_1,f_2,f_3;
	 volatile float J11_24,J12_23,J13_22,J14_21,J32,J33;
//	 volatile float SEq_dot_omega_1,SEq_dot_omega_2,SEq_dot_omega_3,SEq_dot_omega_4;
	 volatile float norm_temp;
	 volatile float	SEqDot_omega_1,SEqDot_omega_2,SEqDot_omega_3,SEqDot_omega_4;

	// Eger ivmeölçer sensöründe bir problem yok ise
	if(!((ax == 0.0f) && (ay == 0.0f) && (az <= 0.001f))) {

		// Madgwick Algoritmasi
		norm_temp = sqrt(ax * ax + ay * ay + az * az);
		ax =ax/norm_temp;
		ay =ay/norm_temp;
		az =az/norm_temp;

		f_1=       2.0f*SEq_2*SEq_4 - 2.0f*SEq_1*SEq_3 - ax;
		f_2=       2.0f*SEq_1*SEq_2 + 2.0f*SEq_3*SEq_4 - ay;
		f_3=1.0f - 2.0f*SEq_2*SEq_2 - 2.0f*SEq_3*SEq_3 - az;

		J11_24=2.0f*SEq_3;
		J12_23=4.0f*SEq_4;
		J13_22=2.0f*SEq_1;
		J14_21=2.0f*SEq_2;
		J32=2.0f*J14_21;
		J33=2.0f*J11_24;

		SEqHatDot_1=J14_21*f_2 - J11_24*f_1;
		SEqHatDot_2=J12_23*f_1 + J13_22*f_2 - J32*f_3;
		SEqHatDot_3=J12_23*f_2 - J33*f_3 - J13_22*f_1;
		SEqHatDot_4=J14_21*f_1 + J11_24*f_2;

		norm_temp=sqrt(SEqHatDot_1*SEqHatDot_1+SEqHatDot_2*SEqHatDot_2+SEqHatDot_3*SEqHatDot_3+SEqHatDot_4*SEqHatDot_4);
		SEqHatDot_1=SEqHatDot_1/norm_temp;
		SEqHatDot_2=SEqHatDot_2/norm_temp;
		SEqHatDot_3=SEqHatDot_3/norm_temp;
		SEqHatDot_4=SEqHatDot_4/norm_temp;

		// Jiroskop Biasleri Hesaplaniyor
		w_err_x = 2.0f*SEq_1 * SEqHatDot_2 - 2.0f*SEq_2 * SEqHatDot_1 - 2.0f*SEq_3 * SEqHatDot_4 + 2.0f*SEq_4 * SEqHatDot_3;
		w_err_y = 2.0f*SEq_1 * SEqHatDot_3 + 2.0f*SEq_2 * SEqHatDot_4 - 2.0f*SEq_3 * SEqHatDot_1 - 2.0f*SEq_4 * SEqHatDot_2;
		w_err_z = 2.0f*SEq_1 * SEqHatDot_4 - 2.0f*SEq_2 * SEqHatDot_3 + 2.0f*SEq_3 * SEqHatDot_2 - 2.0f*SEq_4 * SEqHatDot_1;

		w_bx = w_bx+ w_err_x *zeta*Elapsed_time_Ahrs;
		w_by = w_by+ w_err_y *zeta*Elapsed_time_Ahrs;
		w_bz = w_bz+ w_err_z *zeta*Elapsed_time_Ahrs;
		w_x =gx*(M_PI/180.0f)- w_bx;
		w_y =gy*(M_PI/180.0f)- w_by;
		w_z =gz*(M_PI/180.0f)- w_bz;

		SEqDot_omega_1 = -SEq_2/2.0f * w_x - SEq_3/2.0f * w_y - SEq_4/2.0f * w_z;
		SEqDot_omega_2 = SEq_1/2.0f * w_x  + SEq_3/2.0f * w_z - SEq_4/2.0f * w_y;
		SEqDot_omega_3 = SEq_1/2.0f * w_y  - SEq_2/2.0f * w_z + SEq_4/2.0f * w_x;
		SEqDot_omega_4 = SEq_1/2.0f * w_z  + SEq_2/2.0f * w_y - SEq_3/2.0f * w_x;
	}
	SEq_1 =SEq_1+ (SEqDot_omega_1 - (beta * SEqHatDot_1))*Elapsed_time_Ahrs;
	SEq_2 =SEq_2+ (SEqDot_omega_2 - (beta * SEqHatDot_2))*Elapsed_time_Ahrs;
	SEq_3 =SEq_3+ (SEqDot_omega_3 - (beta * SEqHatDot_3))*Elapsed_time_Ahrs;
	SEq_4 =SEq_4+ (SEqDot_omega_4 - (beta * SEqHatDot_4))*Elapsed_time_Ahrs;

	norm_temp=sqrt(SEq_1*SEq_1+SEq_2*SEq_2+SEq_3*SEq_3+SEq_4*SEq_4);

    // Sonuç Oryantasyonu (Quaternion)
	SEq_1=SEq_1/norm_temp;
	SEq_2=SEq_2/norm_temp;
	SEq_3=SEq_3/norm_temp;
	SEq_4=SEq_4/norm_temp;

	// Quaternion Euler Açi Dönüsümü
	// Quat_to_Deg(SEq_1,SEq_2,SEq_3,SEq_4);

	madg_quaternion[0] = SEq_1;
	madg_quaternion[1] = SEq_2;
	madg_quaternion[2] = SEq_3;
	madg_quaternion[3] = SEq_4;

	Madg_Roll=madg_eulerd[0]*180.0f/M_PI;
	Madg_Pitch=madg_eulerd[1]*180.0f/M_PI;
	Madg_Yaw=madg_eulerd[2]*180.0f/M_PI;
}

// Quaternion Euler Açi Dönüsüm Fonksiyonu
void Quat_to_Deg(float SEq_1,float SEq_2,float SEq_3,float SEq_4)
{

Madg_Roll=(atan2(2*(SEq_1*SEq_2+SEq_3*SEq_4),(SEq_1*SEq_1-SEq_2*SEq_2-SEq_3*SEq_3+SEq_4*SEq_4))*(180.0f/M_PI));
Madg_Pitch=-asin(2*SEq_2*SEq_4-2*SEq_3*SEq_1)*(180.0f/M_PI);
Madg_Yaw=atan2(2*(SEq_1*SEq_4+SEq_2*SEq_3),(SEq_1*SEq_1+SEq_2*SEq_2-SEq_3*SEq_3-SEq_4*SEq_4))*(180.0f/M_PI);

//	// 0-360 derece arasi
//	if (Madg_Yaw <0) Madg_Yaw*=-1;
//	else if(Madg_Yaw>0) Madg_Yaw=360-Madg_Yaw;
//	Madg_Yaw+=5.32f;
//	if(Madg_Yaw<0.0f)Madg_Yaw+=360.0f;
//	if(Madg_Yaw>360.0f)Madg_Yaw-=360.0f;
}



