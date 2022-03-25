/*
 * Aesk_Uav_Global.c
 *
 *  Created on: Aug 19, 2021
 *      Author: PC_1830
 */
#include "Uav_Global.h"

void HAL_SYSTICK_Callback(void)
{
	system_clock_counter_1ms++;

	if( system_clock_counter_1ms % 1000 == 0)
	{
		Time.Task.Hz_1 = 1;
	}
	if( system_clock_counter_1ms % 200 == 0)
	{
		Time.Task.Hz_5 = 1;
	}
	if( system_clock_counter_1ms % 100 == 0)
	{
		Time.Task.Hz_10 = 1;
	}
	if( system_clock_counter_1ms % 50 == 0)
	{
		Time.Task.Hz_20 = 1;
	}
	if( system_clock_counter_1ms % 20 == 0)
	{
		Time.Task.Hz_50 = 1;
	}
	if( system_clock_counter_1ms % 5 == 0)
	{
		Time.Task.Hz_200 = 1;
	}
	if( system_clock_counter_1ms % 2 == 0)
	{
		Time.Task.Hz_500 = 1;
	}
	if( system_clock_counter_1ms % 1 == 0)
	{
		Time.Task.Hz_1000 = 1;
	}
}
int MapInt(int x, int in_min, int in_max, int out_min, int out_max)
{
	return (int)(x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
float MapFloat(float x, float in_min, float in_max, float out_min, float out_max)
{
	return (float)(x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
float constrain(float value, float Min, float Max)
{
	if(value < Min)
	{
		return Min;
	}
	if(value > Max)
	{
		return Max;
	}

	return value;
}
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart==&huart3)
	{
		RcTrue.ConnectTrue=1;
		static int index = 0;
		Rx_buffer[index++] = Rx_temp;
		if(index == 1 && Rx_buffer[0] != 0x20)
		{
			index = 0;
		}
		if(index == 2 && Rx_buffer[1] != 0x40)
		{
			index = 0;
		}
		if(index == 32)
		{
			index = 0;
			uint16_t checksum;
			uint16_t checksum_cal = 0xFFFF;
			checksum = Rx_buffer[31] << 8 | Rx_buffer[30];

			for(int i = 0 ; i<30 ; i++)
			{
				checksum_cal -= Rx_buffer[i];
			}

			if(checksum_cal == checksum)
			{
				Rc.Ch1 = Rx_buffer[3] << 8 | Rx_buffer[2];
				Rc.Ch2 = Rx_buffer[5] << 8 | Rx_buffer[4];
				Rc.Ch3 = Rx_buffer[7] << 8 | Rx_buffer[6];
				Rc.Ch4 = Rx_buffer[9] << 8 | Rx_buffer[8];
				Rc.Ch5 = Rx_buffer[11] << 8 | Rx_buffer[10];
				Rc.Ch6 = Rx_buffer[13] << 8 | Rx_buffer[12];
				Rc.Ch7 = Rx_buffer[15] << 8 | Rx_buffer[14];
				Rc.Ch8 = Rx_buffer[17] << 8 | Rx_buffer[16];
				Rc.Ch9 = Rx_buffer[19] << 8 | Rx_buffer[18];
				Rc.Ch10 = Rx_buffer[21] << 8 | Rx_buffer[20];
				Rc.Ch11 = Rx_buffer[23] << 8 | Rx_buffer[22];
				Rc.Ch12 = Rx_buffer[25] << 8 | Rx_buffer[24];
				Rc.Ch13 = Rx_buffer[27] << 8 | Rx_buffer[26];
				Rc.Ch14 = Rx_buffer[29] << 8 | Rx_buffer[28];
			}
		}
		HAL_UART_Receive_IT(&huart3, &Rx_temp, 1);
	}
	//if(huart==&huart5)
	//{
	//	{
	//		RaspberryRxBuffer[index++] = raspberryRx;
	//		if(raspberryRx == 'Y')
	//		{
	//			sscanf(RaspberryRxBuffer, "H-%d-%d-Y", &Degree, &Distance );
	//			cozulen_packet++;
	//			memset(RaspberryRxBuffer,0,index);
	//			index = 0;
	//		}
	//		HAL_UART_Receive_IT(&huart5, &raspberryRx, 1);
	//}
	//}
}
//void Read_ADC()
//{
//	HAL_ADC_Start(&hadc1);
//	if(HAL_ADC_PollForConversion(&hadc1, 100000)==HAL_OK)
//	{
//		Battery.Adc_value = HAL_ADC_GetValue(&hadc1);
//	}
//	HAL_ADC_Stop(&hadc1);
//}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	onReceiveFlag = 0;

	AESK_NRF24_ReadPack();

	onReceiveFlag = 1;
}
void onReceive(uint8_t * pack, uint16_t len)
{
	if(*pack == 'P' || *pack == 'G' || *pack == 'U')
	{
		AESK_NRF24_WritePack(pack, len, nodeGCS);
		HAL_GPIO_TogglePin(Led2_GPIO_Port, Led2_Pin);
	}

	parseBuffer(pack);

	HAL_GPIO_TogglePin(Led2_GPIO_Port, Led2_Pin);

	onReceiveFlag = 1;
}

void parseBuffer(uint8_t *buffer)
{
    uint16_t index = 2;

    if(aesk_nrf24_data.RxBuffer[0] == 'P')
    {
        AESK_UINT8toUINT24_LE(&aesk_Rx_Datas_Int.RollPitchKp,buffer,&index);
        AESK_UINT8toUINT24_LE(&aesk_Rx_Datas_Int.RollPitchKi,buffer,&index);
        AESK_UINT8toUINT24_LE(&aesk_Rx_Datas_Int.RollPitchKd,buffer,&index);

        AESK_UINT8toUINT24_LE(&aesk_Rx_Datas_Int.YawKp,buffer,&index);
        AESK_UINT8toUINT24_LE(&aesk_Rx_Datas_Int.YawKi,buffer,&index);
        AESK_UINT8toUINT24_LE(&aesk_Rx_Datas_Int.YawKd,buffer,&index);

        AESK_UINT8toUINT24_LE(&aesk_Rx_Datas_Int.AltitudeKp,buffer,&index);
        AESK_UINT8toUINT24_LE(&aesk_Rx_Datas_Int.AltitudeKi,buffer,&index);
        AESK_UINT8toUINT24_LE(&aesk_Rx_Datas_Int.AltitudeKd,buffer,&index);

        AESK_UINT8toUINT24_LE(&aesk_Rx_Datas_Int.GpsKp,buffer,&index);
        AESK_UINT8toUINT24_LE(&aesk_Rx_Datas_Int.GpsKi,buffer,&index);
        AESK_UINT8toUINT24_LE(&aesk_Rx_Datas_Int.GpsKd,buffer,&index);

        AESK_UINT8toUINT24_LE(&aesk_Rx_Datas_Int.Ext1Kp,buffer,&index);
        AESK_UINT8toUINT24_LE(&aesk_Rx_Datas_Int.Ext1Ki,buffer,&index);
        AESK_UINT8toUINT24_LE(&aesk_Rx_Datas_Int.Ext1Kd,buffer,&index);

        AESK_UINT8toUINT24_LE(&aesk_Rx_Datas_Int.Ext2Kp,buffer,&index);
        AESK_UINT8toUINT24_LE(&aesk_Rx_Datas_Int.Ext2Ki,buffer,&index);
        AESK_UINT8toUINT24_LE(&aesk_Rx_Datas_Int.Ext2Kd,buffer,&index);


        aesk_Rx_Datas_Float.floatRollPitchKp = (float)aesk_Rx_Datas_Int.RollPitchKp/100000;
        aesk_Rx_Datas_Float.floatRollPitchKi = (float)aesk_Rx_Datas_Int.RollPitchKi/100000;
        aesk_Rx_Datas_Float.floatRollPitchKd = (float)aesk_Rx_Datas_Int.RollPitchKd/100000;

        Roll.Kp = aesk_Rx_Datas_Float.floatRollPitchKp;
		Roll.Ki = aesk_Rx_Datas_Float.floatRollPitchKi;
		Roll.Kd = aesk_Rx_Datas_Float.floatRollPitchKd;

		Pitch.Kp = aesk_Rx_Datas_Float.floatRollPitchKp;
		Pitch.Ki = aesk_Rx_Datas_Float.floatRollPitchKi;
		Pitch.Kd = aesk_Rx_Datas_Float.floatRollPitchKd;

        aesk_Rx_Datas_Float.floatYawKp = (float)aesk_Rx_Datas_Int.YawKp/100000;
        aesk_Rx_Datas_Float.floatYawKi = (float)aesk_Rx_Datas_Int.YawKi/100000;
        aesk_Rx_Datas_Float.floatYawKd = (float)aesk_Rx_Datas_Int.YawKd/100000;

        Yaw.Kp = aesk_Rx_Datas_Float.floatYawKp;
		Yaw.Ki = aesk_Rx_Datas_Float.floatYawKi;
		AltitudeCalculator = aesk_Rx_Datas_Float.floatYawKd;
		Yaw.Kd = 0;
		aesk_Rx_Datas_Float.floatAltitudeKp = (float)aesk_Rx_Datas_Int.AltitudeKp/100000;
		aesk_Rx_Datas_Float.floatAltitudeKi = (float)aesk_Rx_Datas_Int.AltitudeKi/100000;
		aesk_Rx_Datas_Float.floatAltitudeKd = (float)aesk_Rx_Datas_Int.AltitudeKd/100000;

		Altitude.Kp=  aesk_Rx_Datas_Float.floatAltitudeKp ;
		Altitude.Ki=  aesk_Rx_Datas_Float.floatAltitudeKi ;
		Altitude.Kd=  aesk_Rx_Datas_Float.floatAltitudeKd ;
		Flash_Write_Data_u8(0x08060000,&buffer[2], 72);// 24 sadece roll ve yaw degerlerini tutmak için arttırmak istediğinde her deger için 4 bayt

		aesk_Rx_Datas_Float.floatGpsKp = (float)aesk_Rx_Datas_Int.GpsKp/100000;
        aesk_Rx_Datas_Float.floatGpsKi = (float)aesk_Rx_Datas_Int.GpsKi/100000;
        aesk_Rx_Datas_Float.floatGpsKd = (float)aesk_Rx_Datas_Int.GpsKd/100000;

        aesk_Rx_Datas_Float.floatExt1Kp = (float)aesk_Rx_Datas_Int.Ext1Kp/100000;
        aesk_Rx_Datas_Float.floatExt1Ki = (float)aesk_Rx_Datas_Int.Ext1Ki/100000;
        aesk_Rx_Datas_Float.floatExt1Kd = (float)aesk_Rx_Datas_Int.Ext1Kd/100000;

        aesk_Rx_Datas_Float.floatExt2Kp = (float)aesk_Rx_Datas_Int.Ext2Kp/100000;
        aesk_Rx_Datas_Float.floatExt2Ki = (float)aesk_Rx_Datas_Int.Ext2Ki/100000;
        aesk_Rx_Datas_Float.floatExt2Kd = (float)aesk_Rx_Datas_Int.Ext2Kd/100000;
    }
    else if(aesk_nrf24_data.RxBuffer[0] == 'T')
	{
		AESK_UINT8toUINT16_LE(&aesk_Rx_Datas_Int.adc1,buffer,&index);
		AESK_UINT8toUINT16_LE(&aesk_Rx_Datas_Int.adc2,buffer,&index);
		AESK_UINT8toUINT16_LE(&aesk_Rx_Datas_Int.adc3,buffer,&index);
		AESK_UINT8toUINT16_LE(&aesk_Rx_Datas_Int.adc4,buffer,&index);
		AESK_UINT8toUINT16_LE(&aesk_Rx_Datas_Int.adc5,buffer,&index);
		AESK_UINT8toUINT16_LE(&aesk_Rx_Datas_Int.adc6,buffer,&index);
		AESK_UINT8toUINT16_LE(&aesk_Rx_Datas_Int.adc7,buffer,&index);
		AESK_UINT8toUINT16_LE(&aesk_Rx_Datas_Int.adc8,buffer,&index);
		AESK_UINT8toUINT16_LE(&aesk_Rx_Datas_Int.adc9,buffer,&index);
		AESK_UINT8toUINT16_LE(&aesk_Rx_Datas_Int.adc10,buffer,&index);
	}
    else if(aesk_nrf24_data.RxBuffer[0] == 'U')
    {
		  NVIC_SystemReset();
    }

}
void Battery_Calculate()
{
	for (int i=0;i<10;i++)
	{
		Battery.Adc_value = adc_data[0];
		Battery.Adc_array[i]= Battery.Adc_value;
	}
	for(int i = 0; i < 10; i++)
	{
		if(Battery.Adc_index < Battery.Adc_array[i])
		{
			Battery.Adc_index = Battery.Adc_array[i];
		}
	}
	Battery.Adc_output = Battery.Adc_index;
//	Battery.Voltage2 = (((Battery.Adc_output-2900.0)/215)+13.3);// değerler bataryaya göre ayarlanmalı
	Battery.Voltage = MapFloat(Battery.Adc_output, 2900, 3660, 13.3, 16.8);
	Battery.Adc_index = 0;
}
void MainAllInit()
{
	HAL_TIM_Base_Start(&htim1);//timer başlatma fonksiyonu


	dshot_init();
	HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_3);//motorlara giden pwmleri başlatma

	HAL_UART_Receive_IT(&huart3, &Rx_temp, 1);
//	HAL_UART_Receive_IT(&huart5, &raspberryRx, 1);//raspberry interrupt fonksiyonu
  	MPU6050_Init(&hi2c2);// imunun  başlatma fonksiyonun
	myMpuConfig.Accel_Full_Scale=AFS_SEL_4g;//configürasyon için değerlerin ayarlanması
	myMpuConfig.ClockSource=Internal_8MHz;//configürasyon için değerlerin ayarlanması
	myMpuConfig.CONFIG_DLPF=DLPF_44A_42G_Hz;//configürasyon için değerlerin ayarlanması
	myMpuConfig.Gyro_Full_Scale=FS_SEL_500;//configürasyon için değerlerin ayarlanması
	myMpuConfig.Sleep_Mode_Bit=0;//configürasyon için değerlerin ayarlanması
	MPU6050_Config(&myMpuConfig);
	Rolltau = 0.009f;
	RollLimit = 400.0f;
	RollLimitint = 50.0f;
	AESK_NRF24_DATA_Init(48, 0x11223344AA, &onReceive);
	AESK_NRF24_Init(&hspi1, NRF_CSN_GPIO_Port, NRF_CSN_Pin, NRF_CE_Pin);

	ManyometerInit();

	PID_init(&Roll);
	PID_init(&Pitch);
	PID_init(&Yaw);
	PID_init(&Altitude);

	Init_ESC(); // Esc kalibrasyon fonksiyonu
	Offset_Calculate();// imunun kendi calibre etmesi için fonksiyon

//	Ms5611Init();
	BarometerInit();
	Registerinit();// registera kaydedilen pid degerlerini yükler

	Roll.tau= Rolltau;
	Roll.limMax = RollLimit;
	Roll.limMin = -RollLimit;
	Roll.limMaxInt = RollLimitint;
	Roll.limMinInt = -RollLimitint;
	Roll.Elapsed_Time = Elapsed_time;

	Pitch.tau= Rolltau;
	Pitch.limMax = RollLimit;
	Pitch.limMin = -RollLimit;
	Pitch.limMaxInt = RollLimitint;
	Pitch.limMinInt = -RollLimitint;
    Pitch.Elapsed_Time = Elapsed_time;

	Yaw.tau= Rolltau;
	Yaw.limMax = RollLimit;
	Yaw.limMin = -RollLimit;
	Yaw.limMaxInt = RollLimitint;
	Yaw.limMinInt = -RollLimitint;
	Yaw.Elapsed_Time = Elapsed_time;

	Altitude.tau= Rolltau;
	Altitude.limMax = RollLimit;
	Altitude.limMin = -RollLimit;
	Altitude.limMaxInt = RollLimitint;
	Altitude.limMinInt = -RollLimitint;
	Altitude.Elapsed_Time = Elapsed_time;
}
void RemoteControlOnOff()
{
	if((Rc.Ch6<=1100) || Rc.Ch3 <= 1050)
	{
		SetMotorPWM(1000, 1000, 1000, 1000);
		PID_init(&Roll);
		PID_init(&Pitch);
		PID_init(&Yaw);
		PID_init(&Altitude);
	}
	else
	{
		SetMotorPWM(Motor.Sol_Arka, Motor.Sag_Arka,Motor.Sag_On, Motor.Sol_On);
	}
}
void Registerinit()
{
	uint8_t pidBuf[72];
	Flash_Read_Data_u8(0x08060000, pidBuf, 72);
	uint16_t indexx = 0;
	AESK_UINT8toUINT24_LE(&aesk_Rx_Datas_Int.RollPitchKp,pidBuf,&indexx);
	AESK_UINT8toUINT24_LE(&aesk_Rx_Datas_Int.RollPitchKi,pidBuf,&indexx);
	AESK_UINT8toUINT24_LE(&aesk_Rx_Datas_Int.RollPitchKd,pidBuf,&indexx);

	AESK_UINT8toUINT24_LE(&aesk_Rx_Datas_Int.YawKp,pidBuf,&indexx);
	AESK_UINT8toUINT24_LE(&aesk_Rx_Datas_Int.YawKi,pidBuf,&indexx);
	AESK_UINT8toUINT24_LE(&aesk_Rx_Datas_Int.YawKd,pidBuf,&indexx);

	AESK_UINT8toUINT24_LE(&aesk_Rx_Datas_Int.AltitudeKp,pidBuf,&indexx);
	AESK_UINT8toUINT24_LE(&aesk_Rx_Datas_Int.AltitudeKi,pidBuf,&indexx);
	AESK_UINT8toUINT24_LE(&aesk_Rx_Datas_Int.AltitudeKd,pidBuf,&indexx);

	AESK_UINT8toUINT24_LE(&aesk_Rx_Datas_Int.GpsKp,pidBuf,&indexx);
	AESK_UINT8toUINT24_LE(&aesk_Rx_Datas_Int.GpsKi,pidBuf,&indexx);
	AESK_UINT8toUINT24_LE(&aesk_Rx_Datas_Int.GpsKd,pidBuf,&indexx);

	AESK_UINT8toUINT24_LE(&aesk_Rx_Datas_Int.Ext1Kp,pidBuf,&indexx);
	AESK_UINT8toUINT24_LE(&aesk_Rx_Datas_Int.Ext1Ki,pidBuf,&indexx);
	AESK_UINT8toUINT24_LE(&aesk_Rx_Datas_Int.Ext1Kd,pidBuf,&indexx);

	AESK_UINT8toUINT24_LE(&aesk_Rx_Datas_Int.Ext2Kp,pidBuf,&indexx);
	AESK_UINT8toUINT24_LE(&aesk_Rx_Datas_Int.Ext2Ki,pidBuf,&indexx);
	AESK_UINT8toUINT24_LE(&aesk_Rx_Datas_Int.Ext2Kd,pidBuf,&indexx);

	aesk_Rx_Datas_Float.floatRollPitchKp = (float)aesk_Rx_Datas_Int.RollPitchKp/100000;
	aesk_Rx_Datas_Float.floatRollPitchKi = (float)aesk_Rx_Datas_Int.RollPitchKi/100000;
	aesk_Rx_Datas_Float.floatRollPitchKd = (float)aesk_Rx_Datas_Int.RollPitchKd/100000;

	Roll.Kp = aesk_Rx_Datas_Float.floatRollPitchKp;
	Roll.Ki = aesk_Rx_Datas_Float.floatRollPitchKi;
	Roll.Kd = aesk_Rx_Datas_Float.floatRollPitchKd;

	Pitch.Kp = aesk_Rx_Datas_Float.floatRollPitchKp;
	Pitch.Ki = aesk_Rx_Datas_Float.floatRollPitchKi;
	Pitch.Kd = aesk_Rx_Datas_Float.floatRollPitchKd;

    aesk_Rx_Datas_Float.floatYawKp = (float)aesk_Rx_Datas_Int.YawKp/100000;
	aesk_Rx_Datas_Float.floatYawKi = (float)aesk_Rx_Datas_Int.YawKi/100000;
	aesk_Rx_Datas_Float.floatYawKd = (float)aesk_Rx_Datas_Int.YawKd/100000;

	Yaw.Kp = aesk_Rx_Datas_Float.floatYawKp;
	Yaw.Ki = aesk_Rx_Datas_Float.floatYawKi;
	Yaw.Kd = 0;
	AltitudeCalculator = aesk_Rx_Datas_Float.floatYawKd;

	aesk_Rx_Datas_Float.floatAltitudeKp = (float)aesk_Rx_Datas_Int.AltitudeKp/100000;
	aesk_Rx_Datas_Float.floatAltitudeKi = (float)aesk_Rx_Datas_Int.AltitudeKi/100000;
	aesk_Rx_Datas_Float.floatAltitudeKd = (float)aesk_Rx_Datas_Int.AltitudeKd/100000;

	Altitude.Kp = aesk_Rx_Datas_Float.floatAltitudeKp;
	Altitude.Ki = aesk_Rx_Datas_Float.floatAltitudeKi;
	Altitude.Kd = aesk_Rx_Datas_Float.floatAltitudeKd;

}


