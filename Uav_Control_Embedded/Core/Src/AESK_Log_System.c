/*
 * AESK_Log_System.c
 *
 *  Created on: 26 Şub 2021
 *      Author: Yusuf
 */

#include "AESK_Log_System.h"
#include "Uav_Global.h"

void vars_to_str(char *buffer, const char *format, ...)
{
	va_list args;
	va_start(args, format);
	vsprintf(buffer, format, args);
	va_end(args);
}
char *SDHeader =

//		"Time\t"		//gps Time

		"Year\t"		//Gps Year
		"Month\t"		//Gps Month
		"Day\t"			//Gps Day
		"Hour\t"		//Gps Hour
		"Min\t"			//Gps Min

		"VelNorth\t"    //  mm/s
		"VelEast\t"		//  mm/s
		"VelDown\t"		//  mm/s

		"Lattitude\t"
		"Longtitude\t"


		"BarometerAltitude\t"	//  m
		"Actual_Pressure\t"   //hPa

		"NotchFilterGyroRoll\t"		// m/s
		"NotchFilterGyroPitch\t"	// m/s
		"NotchFilterGyroYaw\t"		// m/s

		"NotchFilterAccelRoll\t"	// m/s^2
		"NotchFilterAccelPitch\t"	// m/s^2
		"NotchFilterAccelYaw\t"		// m/s^2

		"NotchFilterMagRoll\t"		//Gauss
		"NotchFilterMagPitch\t"		//Gauss
		"NotchFilterMagYaw\t"		//Gauss

		"Magno_Bearing\t"			//kuzeye olan Açı

		"Ahrs_Roll\t"				//Açı
		"Ahrs_Pitch\t"				//Açı
		"Ahrs_Yaw\t"				//Açı

		"RemoteRollRaw\t"			//birimsiz
		"RemotePitchRaw\t"			//birimsiz
		"RemoteYawRaw\t"			//birimsiz
		"RemoteThrottleRaw\t"		//birimsiz

		"RemoteRollSetpoint\t"		//birimsiz
		"RemotePitchSetpoint\t"		//birimsiz
		"RemoteYawSetpoint\t"		//birimsiz
		"RemoteThrottleSetpoint\t"	//birimsiz

		"RemoteRollVelocity\t"		//birimsiz
		"RemotePitchVelocity\t"		//birimsiz
		"RemoteYawVelocity\t"		//birimsiz
		"RemoteThrottleVelocity\t"	//birimsiz

		"MotorSag_On\t"				//birimsiz
		"MotorSag_Arka\t"			//birimsiz
		"MotorSol_On\t"				//birimsiz
		"MotorSol_Arka\t"			//birimsiz

		"RollControlSignal\t"		//birimsiz
		"PitchControlSignal\t"		//birimsiz
		"YawControlSignal\t"		//birimsiz
		"AltitudeControlSignal\t"	//birimsiz

		"BatteryVoltage\t"			//Voltage

		"RollKp\t"					//birimsiz
		"RollKi\t"					//birimsiz
		"RollKd\t"					//birimsiz

		"YawKp\t"					//birimsiz
		"YawKi\t"					//birimsiz
		"YawKd\t"					//birimsiz

		"AltitudeKp\t"				//birimsiz
		"AltitudeKi\t"				//birimsiz
		"AltitudeKd\t\n";				//birimsiz

void LogStart(Sd_Card_Data *sdcard_data)
{
	sdcard_data->result = f_mount(&sdcard_data->myFATAFS, (TCHAR const*) SDPath, 1);
	if (sdcard_data->result == FR_OK)
	{

		vars_to_str(sdcard_data->path, "%02d-%02d-%02d.txt", 8,8,98);// buraya utc zaman vb eklenecek kart acılırken burası yapılıyor

		sdcard_data->result_open = f_open(&sdcard_data->myFile, sdcard_data->path, FA_WRITE | FA_OPEN_APPEND);
		f_write(&sdcard_data->myFile, SDHeader, strlen(SDHeader), (void*) &sdcard_data->writtenbyte);
		sdcard_data->state = SD_Card_Detect;
		f_close(&sdcard_data->myFile);
	}
}
void LogDataInit()
{
	GyroRollFiltered.NotchFilterOut  = 1;
	GyroPitchFiltered.NotchFilterOut = 1;
	GyroYawFiltered.NotchFilterOut   = 1;

	AccelRollFiltered.NotchFilterOut = 1;
	AccelPitchFiltered.NotchFilterOut= 1;
	AccelYawFiltered.NotchFilterOut  = 1;

	MagRollFiltered.NotchFilterOut   = 1;
	MagPitchFiltered.NotchFilterOut  = 1;
	MagYawFiltered.NotchFilterOut    = 1;

	magno_bearing                    = 1;

	Ahrs_ROLL                        = 1;
	Ahrs_PITCH                       = 1;
	Ahrs_YAW                         = 1;

	RemoteRoll.Raw                   = 1;
	RemotePitch.Raw                  = 1;
	RemoteYaw.Raw                    = 1;
	RemoteThrottle.Raw				 = 1;

	RemoteRoll.Setpoint              = 1;
	RemotePitch.Setpoint             = 1;
	RemoteYaw.Setpoint               = 1;
	RemoteThrottle.Setpoint          = 1;

	RemoteRoll.Velocity              = 1;
	RemotePitch.Velocity             = 1;
	RemoteYaw.Velocity               = 1;
	RemoteThrottle.Velocity          = 1;

	Motor.Sag_On                     = 1;
	Motor.Sag_Arka                   = 1;
	Motor.Sol_On                     = 1;
	Motor.Sol_Arka                   = 1;

	RollControlSignal                = 1;
	PitchControlSignal               = 1;
	YawControlSignal                 = 1;
	AltitudeControlSignal            = 1;

	Battery.Voltage                  = 1;

	Roll.Kp                          = 1;
	Roll.Ki                          = 1;
	Roll.Kd                          = 1;

	Yaw.Kp                           = 1;
	Yaw.Ki                           = 1;
	Yaw.Kd                           = 1;

	Altitude.Kp                      = 1;
	Altitude.Ki                      = 1;
	Altitude.Kd                      = 1;
}
void LogAsString( Sd_Card_Data *sd_card_data,UBX_Handle *gpsDatas)
{

	vars_to_str((char*) sd_card_data->transmitBuf,




			"%d\t"		//year
			"%02d\t"	//Month
			"%02d\t"	//Day
			"%02d\t"	//hour
			"%02d\t"	//Min

			"%d\t"		//velocity North
			"%d\t"		//velocity East
			"%d\t"		//velocity Down

			"%.6f\t"	//Lattitude
			"%.6f\t"	//Longtitude

			"%.2f\t"	//Barometer Altitude
			"%.2f\t"	//actual Pressure

			"%.2f\t"	//gyro
			"%.2f\t"
			"%.2f\t"

			"%.2f\t"	//accel
			"%.2f\t"
			"%.2f\t"

			"%.2f\t"	//Mag
			"%.2f\t"
			"%.2f\t"

			"%.2f\t"   //magno bear

			"%.2f\t"	//ahrs
			"%.2f\t"
			"%.2f\t"

			"%d\t"		//remote.raw
			"%d\t"
			"%d\t"
			"%d\t"

			"%.2f\t"	//remote.setpoint
			"%.2f\t"
			"%.2f\t"
			"%.2f\t"

			"%.2f\t"	//remote.velocity
			"%.2f\t"
			"%.2f\t"
			"%.2f\t"

			"%d\t"  	//Motor
			"%d\t"
			"%d\t"
			"%d\t"

			"%.2f\t"		//Control Signal
			"%.2f\t"
			"%.2f\t"
			"%.2f\t"

			"%.2f\t"	//battery voltage

			"%.2f\t"	//roll
			"%.2f\t"
			"%.2f\t"

			"%.2f\t"	//yaw
			"%.2f\t"
			"%.2f\t"

			"%.2f\t"	//altitude
			"%.2f\t"
			"%.2f\n",

			gpsDatas->ubx_PVT.year,
			gpsDatas->ubx_PVT.month,
			gpsDatas->ubx_PVT.day,
			gpsDatas->ubx_PVT.hour,
			gpsDatas->ubx_PVT.min,

			gpsDatas->ubx_PVT.velN,
			gpsDatas->ubx_PVT.velE,
			gpsDatas->ubx_PVT.velD,

			gpsDatas->ubx_PVT.longitude,
			gpsDatas->ubx_PVT.latitude,

			Barometer_Altitude,
			actual_Pressure,

			GyroRollFiltered.NotchFilterOut,
			GyroPitchFiltered.NotchFilterOut,
			GyroYawFiltered.NotchFilterOut,

			AccelRollFiltered.NotchFilterOut,
			AccelPitchFiltered.NotchFilterOut,
			AccelYawFiltered.NotchFilterOut,

			MagRollFiltered.NotchFilterOut,
			MagPitchFiltered.NotchFilterOut,
			MagYawFiltered.NotchFilterOut,

			magno_bearing,

			Ahrs_ROLL,
			Ahrs_PITCH,
			Ahrs_YAW,

			RemoteRoll.Raw,
			RemotePitch.Raw,
			RemoteYaw.Raw,
			RemoteThrottle.Raw,

			RemoteRoll.Setpoint,
			RemotePitch.Setpoint,
			RemoteYaw.Setpoint,
			RemoteThrottle.Setpoint,

			RemoteRoll.Velocity,
			RemotePitch.Velocity,
			RemoteYaw.Velocity,
			RemoteThrottle.Velocity,

			Motor.Sag_On,
			Motor.Sag_Arka,
			Motor.Sol_On,
			Motor.Sol_Arka,

			RollControlSignal,
			PitchControlSignal,
			YawControlSignal,
			AltitudeControlSignal,

			Battery.Voltage,

			Roll.Kp,
			Roll.Ki,
			Roll.Kd,

			Yaw.Kp,
			Yaw.Ki,
			Yaw.Kd,

			Altitude.Kp,
			Altitude.Ki,
			Altitude.Kd
			);


	vars_to_str((char*) sd_card_data->total_log, "%d:%d:%d\t", 8, 8, 11);
	strcat(sd_card_data->total_log, (const char*) sd_card_data->transmitBuf);
	sd_card_data->result_open = f_open(&sd_card_data->myFile, sd_card_data->path,
			FA_WRITE | FA_OPEN_APPEND | FA_OPEN_ALWAYS);
	if(sd_card_data->result_open != FR_OK)
	{
		sd_card_data->errorcounter_u32++;
		sd_card_data->result_close = f_close(&sd_card_data->myFile);
		if(sd_card_data->result_close == FR_OK)
		{
			sd_card_data->result_open = f_open(&sd_card_data->myFile, sd_card_data->path,
					FA_WRITE | FA_OPEN_APPEND | FA_OPEN_ALWAYS);
		}
	}
	sd_card_data->result_write = f_write(&sd_card_data->myFile, sd_card_data->total_log, strlen(sd_card_data->total_log), (void*) &sd_card_data->writtenbyte);
	if ((sd_card_data->writtenbyte != 0) && (sd_card_data->result_write == FR_OK))
	{
		sd_card_data->result_close = f_close(&sd_card_data->myFile);
		if(sd_card_data->result_close != FR_OK)
		{
			sd_card_data->result_close = f_close(&sd_card_data->myFile);
		}
	}

	else
	{
		sd_card_data->result = f_mount(&sd_card_data->myFATAFS, (TCHAR const*) SDPath, 1);
		if(sd_card_data->result == FR_DISK_ERR)
		{
			f_close(&sd_card_data->myFile);
		}
	}
}


