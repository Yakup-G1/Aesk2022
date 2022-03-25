 /* MotorPowerCalculate.c
 *
 *  Created on: 14 Mar 2021
 *      Author: Yakup Gündüz
 *
 *      Fonksiyonlar ve kullanım amaçları
 *
 *      1-)SetMotorPWM(); bu fonksiyon girilen değerleri motorların oldugu pwm çıkışları yazmak için kullanılmaktadır
 *      2-)Init_ESC();  bu fonksiyon işlemci çalışmaya başladıgında ESC kalibrasyonu istemektedir bu kalibrasyon için
 *      ESC ye çalışma aralığı gönderilmelidir başlangıçta 1000 yollayarak bütün ESC ler kalibre edilir bunu algılaması için
 *      ESC ye gönderilen verinin 2000 ms beklemelidir
 *      Not: En başta main içinde bir kere cağırılması yeterlidir başka bir yerde kullanmayınız
 *      3-)vibrationTest() bu fonksiyon ivmeölçer üzerinden titreşimi ölçmek için kullanılır vibration_total_result[]
 *      değerine kadar çok değişiyorsa o kadar titreşim üretmektedir.
 *      4-)MotorPowerCalculate() Bu fonksiyon kumandadan alınan veriler ile sensörden alınan verilerin arasındaki farkı
 *      pıd kontrol uygulayamaktadır pid kontrol cıkısına ek olarak voltage kayıplarınıda motor değerlerine eklemektedir.
 */
#include <AhrsFilter.h>
#include <Uav_Global.h>
#include "MotorPowerCalculate.h"
#include "math.h"
#include "GPS_UBX.h"

extern LIDAR_Handle LIDAR_Data;
extern uint8_t PositionFlag;
void SetMotorPWM(uint16_t SolArka,uint16_t SagArka,uint16_t SagOn,uint16_t SolOn)
{
	htim1.Instance->CCR1 = SagArka;
	htim1.Instance->CCR2 = SagOn;
	htim1.Instance->CCR3 = SolOn;
	htim1.Instance->CCR4 = SolArka;
}
void Init_ESC()
{
	__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_1,Dutymin);
	__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_2,Dutymin);
	__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_3,Dutymin);
	__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_4,Dutymin);
	HAL_Delay(2000);
}
//void vibrationTest()
//{
//	vibration_array[0] = 100*sqrt((Accel_Set_X * Accel_Set_X) + (Accel_Set_Y * Accel_Set_Y) + (Accel_Set_Z * Accel_Set_Z));
//
//	      for (array_counter = 16; array_counter > 0; array_counter--) {                   //Do this loop 16 times to create an array of accelrometer vectors.
//	        vibration_array[array_counter] = vibration_array[array_counter - 1];           //Shift every variable one position up in the array.
//	        avarage_vibration_level += vibration_array[array_counter];                     //Add the array value to the acc_av_vector variable.
//	      }
//	      avarage_vibration_level /= 17;                                                   //Divide the acc_av_vector by 17 to get the avarage total accelerometer vector.
//
//	      if (vibration_counter < 20) {                                                    //If the vibration_counter is less than 20 do this.
//	        vibration_counter ++;                                                          //Increment the vibration_counter variable.
//	        vibration_total_result += abs(vibration_array[0] - avarage_vibration_level);   //Add the absolute difference between the avarage vector and current vector to the vibration_total_result variable.
//	      }
//	      else {
//	        vibration_counter = 0;                                                         //If the vibration_counter is equal or larger than 20 do this.
//	        vibration_sonuc=vibration_total_result / 50;                                   //Print the total accelerometer vector divided by 50 on the serial monitor.
//	        vibration_total_result = 0;                                                    //Reset the vibration_total_result variable.
//	      }
//}
void MotorPowerCalculateWithRate()
{

	Rollerror  = RemoteRoll.Setpoint  - Ahrs_ROLL;
	Pitcherror = RemotePitch.Setpoint - Ahrs_PITCH;
	Yawerror   = RemoteYaw.Setpoint   - Ahrs_YAW;   // hesaplanacak sonra daha düzgün bir sekilde

//	RollControlSignal  	 = PID(RemoteRoll.Setpoint, Ahrs_ROLL,Roll.Kp, Roll.Ki, Roll.Kd, Roll.limMax, Roll.Elapsed_Time, &Roll.integrator, &Roll.prevError);
//	PitchControlSignal	 = PID(RemotePitch.Setpoint, Ahrs_PITCH,Pitch.Kp, Pitch.Ki, Pitch.Kd, Pitch.limMax, Pitch.Elapsed_Time, &Pitch.integrator, &Pitch.prevError);
//	YawControlSignal  	 = PID(RemoteYaw.Setpoint, Ahrs_YAW, Yaw.Kp, Yaw.Ki, Yaw.Kd, Yaw.limMax, Yaw.Elapsed_Time, &Yaw.integrator, &Yaw.prevError);

	if(Rc.Ch6>1100 && Rc.Ch6<=1400)
	{
		RollControlSignal  	 = PID2(&Roll,RemoteRoll.Setpoint, GyroRollFiltered.NotchFilterOut);
		PitchControlSignal 	 = PID2(&Pitch,RemotePitch.Setpoint, GyroPitchFiltered.NotchFilterOut);
		YawControlSignal  	 = PID2(&Yaw,RemoteYaw.Setpoint, GyroYawFiltered.NotchFilterOut);
		PositionFlag=0;			// gps modunun konumunu sıfırlar bu sayede mod değiştirip gps geçtiginde ilk kalkıs konumunu almak için 0 landı
		Motor.Sag_On           = round(RemoteThrottle.Raw  + RollControlSignal + PitchControlSignal - YawControlSignal );//round(Throttle_Kumanda + Roll_ControlSignal + Pitch_ControlSignal - Yaw_ControlSignal);
		Motor.Sag_Arka         = round(RemoteThrottle.Raw  + RollControlSignal - PitchControlSignal + YawControlSignal );
		Motor.Sol_On           = round(RemoteThrottle.Raw  - RollControlSignal + PitchControlSignal + YawControlSignal );
		Motor.Sol_Arka         = round(RemoteThrottle.Raw  - RollControlSignal - PitchControlSignal - YawControlSignal );
	}

	if(Rc.Ch6>1400 && Rc.Ch6<=1700)//altitude mode
	{
		RollControlSignal  	 = PID2(&Roll,RemoteRoll.Setpoint , GyroRollFiltered.NotchFilterOut);
		PitchControlSignal 	 = PID2(&Pitch,RemotePitch.Setpoint, GyroPitchFiltered.NotchFilterOut);
		YawControlSignal  	 = PID2(&Yaw,RemoteYaw.Setpoint, GyroYawFiltered.NotchFilterOut);

		Voltage_Loss_Prevention = 0;
		Motor.Sag_On           = round(1360 + AltitudeControlSignal  + RollControlSignal + PitchControlSignal - YawControlSignal + Voltage_Loss_Prevention);//round(Throttle_Kumanda + Roll_ControlSignal + Pitch_ControlSignal - Yaw_ControlSignal);
		Motor.Sag_Arka         = round(1360 + AltitudeControlSignal  + RollControlSignal - PitchControlSignal + YawControlSignal + Voltage_Loss_Prevention);
		Motor.Sol_On           = round(1360 + AltitudeControlSignal  - RollControlSignal + PitchControlSignal + YawControlSignal + Voltage_Loss_Prevention);
		Motor.Sol_Arka         = round(1360 + AltitudeControlSignal  - RollControlSignal - PitchControlSignal - YawControlSignal + Voltage_Loss_Prevention);
	}

	if(Rc.Ch6>1700 )			   // Position mode
	{

		RollPositionControlNorth = ((float)RollPositionControl * cos(Ahrs_YAW * 0.017453)) + ((float)PitchPositionControl * cos((Ahrs_YAW - 90) * 0.017453));// ahrs Yawda manyotometre olacak
		PitchPositionControlNorth=((float)PitchPositionControl * cos(Ahrs_YAW * 0.017453)) + ((float)RollPositionControl * cos((Ahrs_YAW + 90) * 0.017453));

		RollControlSignal  	 = PID2(&Roll,RollPositionControlNorth, GyroRollFiltered.NotchFilterOut);
		PitchControlSignal 	 = PID2(&Pitch,PitchPositionControlNorth, GyroPitchFiltered.NotchFilterOut);
		YawControlSignal  	 = PID2(&Yaw,RemoteYaw.Setpoint, GyroYawFiltered.NotchFilterOut);

//		Voltage_Loss_Prevention = (BatteryMaxVoltage - Battery.Voltage)*battery_compensation;
		Voltage_Loss_Prevention=0;
		Motor.Sag_On           = round(1360 + AltitudeControlSignal  + RollControlSignal + PitchControlSignal - YawControlSignal + Voltage_Loss_Prevention);//round(Throttle_Kumanda + Roll_ControlSignal + Pitch_ControlSignal - Yaw_ControlSignal);
		Motor.Sag_Arka         = round(1360 + AltitudeControlSignal  + RollControlSignal - PitchControlSignal + YawControlSignal + Voltage_Loss_Prevention);
		Motor.Sol_On           = round(1360 + AltitudeControlSignal  - RollControlSignal + PitchControlSignal + YawControlSignal + Voltage_Loss_Prevention);
		Motor.Sol_Arka         = round(1360 + AltitudeControlSignal  - RollControlSignal - PitchControlSignal - YawControlSignal + Voltage_Loss_Prevention);
	}

	Motor.Sag_On           = constrain(Motor.Sag_On,   MotorMinThrottle, MotorMaxThrottle) ;
	Motor.Sag_Arka         = constrain(Motor.Sag_Arka, MotorMinThrottle, MotorMaxThrottle) ;
	Motor.Sol_On           = constrain(Motor.Sol_On,   MotorMinThrottle, MotorMaxThrottle) ;
	Motor.Sol_Arka         = constrain(Motor.Sol_Arka, MotorMinThrottle, MotorMaxThrottle) ;
}
void MotorPowerCalculateWithAltitude()
{
	Rollerror  = RemoteRoll.Setpoint  - Ahrs_ROLL;
	Pitcherror = RemotePitch.Setpoint - Ahrs_PITCH;
	Yawerror   = RemoteYaw.Setpoint   - Ahrs_YAW;   // hesaplanacak sonra daha düzgün bir sekilde
	Altitudeerror = RemoteThrottle.Setpoint - LIDAR_Data.LIDAR_Pack.Distance;
	AltitudeControlSignal= PID2(&Altitude, RemoteThrottle.Setpoint, LIDAR_Data.LIDAR_Pack.Distance);
}
void MotorPowerCalculateWithPosition(UBX_Handle *gpsDatas)
{
	RollPositionControl  = PID2(&PIDRollPositionControl, RemoteRoll.TargetPositionVelocity, gpsDatas->ubx_PVT.velE);
	PitchPositionControl = PID2(&PIDPitchPositionControl, RemotePitch.TargetPositionVelocity, gpsDatas->ubx_PVT.velN);
}
