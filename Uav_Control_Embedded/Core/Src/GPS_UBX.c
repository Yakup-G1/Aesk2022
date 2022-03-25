/*
 * GPS_UBX.c
 *
 *  Created on: Feb 8, 2022
 *      Author: Mert KARAGÖZ
 *
 * 	Aciklama:
 *
 * 	Bu kutuphane yazilirken AESK_UART_STM32, AESK_Ring_Buffer ve GPS kutuphanelerinden yararlanilmistir.
 *
 * 	1) Bu kutuphane U-Blox firmasina ait NEO-M8N GPS modeli icin yazilmistir. Diger GPS'ler ile test edilmemistir.
 *
 * 	2) kutuphaneyi kullanabilmek icin proje dosyanizda ve AESK_UART_STM32 kutuphanelerinin
 * 	bulunmamasi gerekmektedir. Eger bu kutuphaneyi kullanmaniz gerekiyorsa GPS_UBX.c dosyasindaki
 * 	Uart_DMA_Receive_Start ve read_DMA_Buffer fonksiyonlarini ve GPS_UBX.h dosyasindaki USART_Buffer struct'ini
 * 	yorum satirina aliniz. Ardindan GPS_UBX.h dosyasinin 14. satirindaki kutuphane include etme yorumunu kaldiriniz.
 *
 *	3) UART DMA yapisi kullanilmistir.
 *
 *	4) MX dosyasinda yapilacak ayarlar ->
 *		UART acilacak.
 *		parameter settings'ten -> 9600 baudrate, 8 bits word length, parity none, stop bit 1 olarak ayaranacak.
 *		NVIC settings'ten -> global interrupt aktif edilecek.
 *		DMA settings'ten -> UARTX_RX eklenip, direction: perip. to memory olarak ayarlanacak.
 *			DMA Request Settings'ten -> mode: circular, increment address: memory, data width: byte olarak ayarlanacak.
 *
 *	5) main dosyasina eklenecek seyler ->
 *		#include "GPS_UBX.h" eklenecek.
 *		USER CODE BEGIN PV arasina ->
 *			uint8_t temp_buf_gps[1024] = { 0 }; //GPS verileri icin buffer
 *			uint16_t read_byte_gps = 0; 		//GPS'ten okunan byte sayisi
 *			USART_Buffer UBX_UART_Bufferi;
 *			UBX_Handle UBX_Data;
 *			eklenecek.
 *		USER CODE BEGIN 2 arasina ->
 *			NMEA2UBX_Config(&huartX, &UBX_UART_Bufferi);
 *			eklenecek.
 *		While icine ->
 *			read_byte_gps = read_DMA_Buffer(&huartX, &UBX_UART_Bufferi, temp_buf_gps);
 *			if(read_byte_gps > 0)
 *			GPS_Data_Control(&UBX_Data, temp_buf_gps, read_byte_gps);
 *			eklenecek.
 *
 *		!!!NOT &huartX yazan yerlerde X yerine aktif edilen uart yazılacaktir. örnek: &huart4, &huart5.
 *
 *
 */
#include "GPS_UBX.h"


uint8_t i,
		I,
		N,
		Check_A = 0,
		Check_B = 0,
		gelen_Check_A = 0,
		gelen_Check_B = 0;

uint8_t Buffer[96],
		pvt_load[92];

uint8_t DTM_off[] = 		{0XB5, 0X62, 0X06, 0X01, 0X03, 0X00, 0XF0, 0X0A, 0X00, 0X04, 0X23};
uint8_t GBS_off[] = 		{0XB5, 0X62, 0X06, 0X01, 0X03, 0X00, 0XF0, 0X09, 0X00, 0X03, 0X21};
uint8_t GGA_off[] = 		{0XB5, 0X62, 0X06, 0X01, 0X03, 0X00, 0XF0, 0X00, 0X00, 0XFA, 0X0F};
uint8_t GLL_off[] = 		{0XB5, 0X62, 0X06, 0X01, 0X03, 0X00, 0XF0, 0X01, 0X00, 0XFB, 0X11};
uint8_t GNS_off[] = 		{0XB5, 0X62, 0X06, 0X01, 0X03, 0X00, 0XF0, 0X0D, 0X00, 0X07, 0X29};
uint8_t GRS_off[] = 		{0XB5, 0X62, 0X06, 0X01, 0X03, 0X00, 0XF0, 0X06, 0X00, 0X00, 0X1B};
uint8_t GSA_off[] = 		{0XB5, 0X62, 0X06, 0X01, 0X03, 0X00, 0XF0, 0X02, 0X00, 0XFC, 0X13};
uint8_t GST_off[] = 		{0XB5, 0X62, 0X06, 0X01, 0X03, 0X00, 0XF0, 0X07, 0X00, 0X01, 0X1D};
uint8_t GSV_off[] =			{0XB5, 0X62, 0X06, 0X01, 0X03, 0X00, 0XF0, 0X03, 0X00, 0XFD, 0X15};
uint8_t RMC_off[] =			{0XB5, 0X62, 0X06, 0X01, 0X03, 0X00, 0XF0, 0X04, 0X00, 0XFE, 0X17};
uint8_t THS_off[] =			{0XB5, 0X62, 0X06, 0X01, 0X03, 0X00, 0XF0, 0X0E, 0X00, 0X08, 0X2B};
uint8_t VLW_off[] =			{0XB5, 0X62, 0X06, 0X01, 0X03, 0X00, 0XF0, 0X0F, 0X00, 0X09, 0X2D};
uint8_t VTG_off[] = 		{0XB5, 0X62, 0X06, 0X01, 0X03, 0X00, 0XF0, 0X05, 0X00, 0XFF, 0X19};
uint8_t ZDA_off[] =			{0XB5, 0X62, 0X06, 0X01, 0X03, 0X00, 0XF0, 0X08, 0X00, 0X02, 0X1F};
uint8_t POSITION_off[] = 	{0XB5, 0X62, 0X06, 0X01, 0X03, 0X00, 0XF1, 0X00, 0X00, 0XFB, 0X12};
uint8_t Config_16_off[] = 	{0XB5, 0X62, 0X06, 0X01, 0X03, 0X00, 0XF1, 0X01, 0X00, 0XFC, 0X14};
uint8_t SVSTATUS_off[] = 	{0XB5, 0X62, 0X06, 0X01, 0X03, 0X00, 0XF1, 0X03, 0X00, 0XFE, 0X18};
uint8_t TIME_off[] = 		{0XB5, 0X62, 0X06, 0X01, 0X03, 0X00, 0XF1, 0X04, 0X00, 0XFF, 0X1A};
uint8_t Config_19_off[] =	{0XB5, 0X62, 0X06, 0X01, 0X03, 0X00, 0XF1, 0X05, 0X00, 0X00, 0X1C};
uint8_t Config_20_off[] = 	{0XB5, 0X62, 0X06, 0X01, 0X03, 0X00, 0XF1, 0X06, 0X00, 0X01, 0X1E};

uint8_t POSLLH_on[] = 		{0XB5, 0X62, 0X06, 0X01, 0X03, 0X00, 0X01, 0X02, 0X01, 0X0E, 0X47};
uint8_t VELNED_on[] = 		{0XB5, 0X62, 0X06, 0X01, 0X03, 0X00, 0X01, 0X12, 0X01, 0X1E, 0X67};
uint8_t PVT_on[] =  		{0XB5, 0X62, 0X06, 0X01, 0X03, 0X00, 0X01, 0X07, 0X01, 0X13, 0X51};
uint8_t RATE_10Hz[] =  		{0XB5, 0X62, 0X06, 0X08, 0X06, 0X00, 0X64, 0X00, 0X01, 0X00, 0X01, 0X00, 0X7A, 0X12};



void Uart_DMA_Receive_Start(UART_HandleTypeDef *huart, USART_Buffer *usart_buffer)
{
	for(uint16_t i = 0; i < sizeof(USART_Buffer); i++)
	{
		((uint8_t*)usart_buffer)[i] = 0;
	}
	 while(HAL_UART_Receive_DMA(huart, usart_buffer->usart_receive_buffer, USART_BUFFER_SIZE) != HAL_OK);
	__HAL_UART_CLEAR_PEFLAG(huart);
}

int16_t read_DMA_Buffer(UART_HandleTypeDef *huart, USART_Buffer *usart_buffer, uint8_t *temp_buf)
{
	int16_t read_byte = 0;
	read_byte = huart->RxXferSize - huart->hdmarx->Instance->NDTR - usart_buffer->tail;

	if(read_byte == 0)
		return read_byte;

	else
	{
		if(read_byte < 0)
			read_byte = read_byte + huart->RxXferSize;

		for(uint16_t i = 0; i < read_byte; i++)
		{
			temp_buf[i] = usart_buffer->usart_receive_buffer[usart_buffer->tail];
			usart_buffer->tail++;

			if(usart_buffer->tail >= huart->RxXferSize)
				usart_buffer->tail = 0;
		}
		return read_byte;
	}
}


void NMEA2UBX_Config(UART_HandleTypeDef *huart, USART_Buffer *USART_Buf)
{
	HAL_UART_Transmit(huart, DTM_off, 11, 500);
	HAL_Delay(50);
	HAL_UART_Transmit(huart, GBS_off, 11, 500);
	HAL_Delay(50);
	HAL_UART_Transmit(huart, GGA_off, 11, 500);
	HAL_Delay(50);
	HAL_UART_Transmit(huart, GLL_off, 11, 500);
	HAL_Delay(50);
	HAL_UART_Transmit(huart, GNS_off, 11, 500);
	HAL_Delay(50);
	HAL_UART_Transmit(huart, GRS_off, 11, 500);
	HAL_Delay(50);
	HAL_UART_Transmit(huart, GSA_off, 11, 500);
	HAL_Delay(50);
	HAL_UART_Transmit(huart, GST_off, 11, 500);
	HAL_Delay(50);
	HAL_UART_Transmit(huart, GSV_off, 11, 500);
	HAL_Delay(50);
	HAL_UART_Transmit(huart, RMC_off, 11, 500);
	HAL_Delay(50);
	HAL_UART_Transmit(huart, THS_off, 11, 500);
	HAL_Delay(50);
	HAL_UART_Transmit(huart, VLW_off, 11, 500);
	HAL_Delay(50);
	HAL_UART_Transmit(huart, VTG_off, 11, 500);
	HAL_Delay(50);
	HAL_UART_Transmit(huart, ZDA_off, 11, 500);
	HAL_Delay(50);
	HAL_UART_Transmit(huart, POSITION_off, 11, 500);
	HAL_Delay(50);
	HAL_UART_Transmit(huart, Config_16_off, 11, 500);
	HAL_Delay(50);
	HAL_UART_Transmit(huart, SVSTATUS_off, 11, 500);
	HAL_Delay(50);
	HAL_UART_Transmit(huart, TIME_off, 11, 500);
	HAL_Delay(50);
	HAL_UART_Transmit(huart, Config_19_off, 11, 500);
	HAL_Delay(50);
	HAL_UART_Transmit(huart, Config_20_off, 11, 500);
	HAL_Delay(50);

	HAL_UART_Transmit(huart, PVT_on, 11, 500);
	HAL_Delay(50);

	HAL_UART_Transmit(huart, RATE_10Hz, 14, 500);
	HAL_Delay(50);

	Uart_DMA_Receive_Start(huart, USART_Buf);
}


void GPS_Data_Control(UBX_Handle *gpsDatas, const uint8_t *datas, uint8_t read_byte)
{

	static uint8_t indeks = 0;
	for(i = 0; i < read_byte ; i++)
	{
		switch(gpsDatas->state)
		{
			case YAKALA_u :
			{
				if(datas[i] == 181) //0xB5
				{
					gpsDatas->state =YAKALA_b;
					gpsDatas->gpsDatasArray[indeks++] = datas[i];
				}
				break;
			}

			case YAKALA_b :
			{
				if(datas[i] == 98) //0x62
				{
					gpsDatas->state =YAKALA_CLASS;
					gpsDatas->gpsDatasArray[indeks++] = datas[i];
				}
				else
				{
					gpsDatas->state =YAKALA_u;
					indeks = 0;
				}
				break;
			}

			case YAKALA_CLASS :
			{
				if(datas[i] == 1) //0x01 -> NAV
				{
					gpsDatas->state =YAKALA_ID;
					gpsDatas->gpsDatasArray[indeks++] = datas[i];
				}
				else
				{
					gpsDatas->state =YAKALA_u;
					indeks = 0;
				}
				break;
			}

			case YAKALA_ID :
			{
				if(datas[i] == 7) //0x07 -> PVT
				{
					gpsDatas->gpsDatasArray[indeks++] = datas[i];
					gpsDatas->state =YAKALA_LENGTH_L;
				}
				else
				{
					gpsDatas->state =YAKALA_u;
					indeks = 0;
				}
				break;
			}

			case YAKALA_LENGTH_L :
			{
				if(datas[i] == 92) // 0x5C
				{
					gpsDatas->gpsDatasArray[indeks++] = datas[i];
					gpsDatas->state =YAKALA_LENGTH_H;
				}
				else
				{
					gpsDatas->state =YAKALA_u;
					indeks = 0;
				}
				break;
			}

			case YAKALA_LENGTH_H :
			{
				if(datas[i] == 0) // 0x00
				{
					gpsDatas->gpsDatasArray[indeks++] = datas[i];
					if(gpsDatas->gpsDatasArray[2] == 1 && gpsDatas->gpsDatasArray[3] == 7)
					{
						gpsDatas->state =TOPLA_NAV_PVT_92;
					}

				}
				else
				{
					gpsDatas->state =YAKALA_u;
					indeks = 0;
				}
				break;
			}

			case TOPLA_NAV_PVT_92:		// NAV_PVT paketinin yapisi [ 0xB5, 0x62, 0x01, 0x07, 0x92, 0x00, Payload[92], CK_A, CK_B ] seklindendir.
			{
				if( indeks < (6 + 92 + 2) ) 							// ubx_NAV_PVT frame yapisi toplam 100 byte'dir. 6 byte bilgilendirme + 92 byte payload + 2 byte checksum
				{
					gpsDatas->gpsDatasArray[indeks++] = datas[i];
				}
				else
				{
					indeks = 0;
					GPS_Parser(gpsDatas, NAV_PVT_92);
					gpsDatas->state = YAKALA_u;
				}
				break;
			}

			case TOPLA_NAV_POSLLH_28:
			{
				if( indeks < (6 + 28 + 2) )								// ubx_NAV_POSLLH frame yapisi toplam 34 byte'dir. 6 byte bilgilendirme + 28 byte payload + 2 byte checksum.
				{
					gpsDatas->gpsDatasArray[indeks++] = datas[i];
				}
				else
				{
					indeks = 0;
					GPS_Parser(gpsDatas, NAV_POSLLH_28);
					gpsDatas->state = YAKALA_u;
				}
				break;
			}

		}

	}

}


void checksum_calc(UBX_Handle *gpsDatas)
{
	memcpy(Buffer, (uint8_t *)gpsDatas->gpsDatasArray+2, 96);
	N = 96; 														//checksum  hesaplanacak alanın byte sayısı;
	Check_A = 0, Check_B = 0;
	for(I=0; I<N; I++)
	{
		Check_A = Check_A + Buffer[I];
		Check_B = Check_B + Check_A;
	}
}


void UBX_gelen_checksum(UBX_Handle *gpsDatas)
{
	gelen_Check_A = gpsDatas->gpsDatasArray[98];
	gelen_Check_B = gpsDatas->gpsDatasArray[99];
}


void GPS_Parser(UBX_Handle *gpsDatas, UBX_Types gpsType)
{
	switch(gpsType)
	{
		case NAV_PVT_92:
		{
			checksum_calc(gpsDatas);
			UBX_gelen_checksum(gpsDatas);

			if ( (Check_A == gelen_Check_A) && (Check_B == gelen_Check_B) )		//checksum kontrolu
			{
				memcpy(pvt_load, (uint8_t *)gpsDatas->gpsDatasArray+6, 92); 	//alt tarafta okunabilirlik ve datasheete benzesin diye sadece payload'i ubx_PVT'ye kopyalıyorum.
				if ( /*pvt_load[11] == VALID_CONTROL*/ 1 )  							//validity kontrolu
				{

					gpsDatas->ubx_PVT.iTOW 			=			 pvt_load[3]<<24 | pvt_load[2]<<16 | pvt_load[1]<<8 | pvt_load[0];
					gpsDatas->ubx_PVT.year 			=			 pvt_load[5]<<8  | pvt_load[4];
					gpsDatas->ubx_PVT.month 		=			 pvt_load[6];
					gpsDatas->ubx_PVT.day 			=			 pvt_load[7];
					gpsDatas->ubx_PVT.hour			=			 pvt_load[8];
					gpsDatas->ubx_PVT.min 			=			 pvt_load[9];
					gpsDatas->ubx_PVT.sec 			=			 pvt_load[10];
					gpsDatas->ubx_PVT.valid 		=			 pvt_load[11];
					gpsDatas->ubx_PVT.tAcc			=			 pvt_load[15]<<24 | pvt_load[14]<<16 | pvt_load[13]<<8 | pvt_load[12];
					gpsDatas->ubx_PVT.nano 			= 	 		 pvt_load[19]<<24 | pvt_load[18]<<16 | pvt_load[17]<<8 | pvt_load[16];
					gpsDatas->ubx_PVT.fixType		= 			 pvt_load[20];
					gpsDatas->ubx_PVT.flags			= 			 pvt_load[21];
					gpsDatas->ubx_PVT.flags2		= 			 pvt_load[22];
					gpsDatas->ubx_PVT.numSV			=			 pvt_load[23];
					gpsDatas->ubx_PVT.longitude	 	=(int32_t)(	 pvt_load[27]<<24 | pvt_load[26]<<16 | pvt_load[25]<<8 | pvt_load[24]) / 10000000.0f;
					gpsDatas->ubx_PVT.latitude		=(int32_t)(	 pvt_load[31]<<24 | pvt_load[30]<<16 | pvt_load[29]<<8 | pvt_load[28]) / 10000000.0f;
					gpsDatas->ubx_PVT.height		 =			 pvt_load[35]<<24 | pvt_load[34]<<16 | pvt_load[33]<<8 | pvt_load[32];
					gpsDatas->ubx_PVT.hMSL			 =			 pvt_load[39]<<24 | pvt_load[38]<<16 | pvt_load[37]<<8 | pvt_load[36];
					gpsDatas->ubx_PVT.hAcc			 =			 pvt_load[43]<<24 | pvt_load[42]<<16 | pvt_load[41]<<8 | pvt_load[40];
					gpsDatas->ubx_PVT.vAcc	  		 =			 pvt_load[47]<<24 | pvt_load[46]<<16 | pvt_load[45]<<8 | pvt_load[44];
					gpsDatas->ubx_PVT.velN	  		 =			 pvt_load[51]<<24 | pvt_load[50]<<16 | pvt_load[49]<<8 | pvt_load[48];
					gpsDatas->ubx_PVT.velE	 		 =			 pvt_load[55]<<24 | pvt_load[54]<<16 | pvt_load[53]<<8 | pvt_load[52];
					gpsDatas->ubx_PVT.velD	  		 =			 pvt_load[59]<<24 | pvt_load[58]<<16 | pvt_load[57]<<8 | pvt_load[56];
					gpsDatas->ubx_PVT.gSpeed		 =			 pvt_load[63]<<24 | pvt_load[62]<<16 | pvt_load[61]<<8 | pvt_load[60];
					gpsDatas->ubx_PVT.headingMotion  =(int32_t)( pvt_load[67]<<24 | pvt_load[66]<<16 | pvt_load[65]<<8 | pvt_load[64]) / 100000.0f;
					gpsDatas->ubx_PVT.sAcc			 =			 pvt_load[71]<<24 | pvt_load[70]<<16 | pvt_load[69]<<8 | pvt_load[68];
					gpsDatas->ubx_PVT.headingAccuracy=(uint32_t)(pvt_load[75]<<24 | pvt_load[74]<<16 | pvt_load[73]<<8 | pvt_load[72]) / 100000.0f;
					gpsDatas->ubx_PVT.positionDOP	 =(uint16_t)(pvt_load[77]<<8  | pvt_load[76]) / 100.0f;
					gpsDatas->ubx_PVT.flags3		 =			 pvt_load[79]<<8  | pvt_load[78];
					gpsDatas->ubx_PVT.reserved1		 =			 pvt_load[83]<<24 | pvt_load[82]<<16 | pvt_load[81]<<8 | pvt_load[80];
					gpsDatas->ubx_PVT.headingVeh	 =(uint32_t)(pvt_load[87]<<24 | pvt_load[86]<<16 | pvt_load[85]<<8 | pvt_load[84]) / 100000.0f;
					gpsDatas->ubx_PVT.magDec		 =			 pvt_load[89]<<8  | pvt_load[88];
					gpsDatas->ubx_PVT.magAcc		 =			 pvt_load[91]<<8  | pvt_load[90];

					gpsDatas->gps_errorhandler.trueData_u32++;

					if( gpsDatas->ubx_PVT.numSV >= 9)
					{
						gpsDatas->satelite_num_flag = 1;
					}
					else
					{
						gpsDatas->satelite_num_flag = 0;
					}


				}
				else
				{
					gpsDatas->gps_errorhandler.validDataError_u32++;
				}
			}
			else
			{
			gpsDatas->gps_errorhandler.checksumError_u32++;
			}
			break;
		}
		case NAV_POSLLH_28:
		{
			// POSLLH paketi eklenmek istenirse buraya eklenebilir.
		}
		case NAV_HPPOSLLH_36:
		{
			// HPPOSLLH paketi eklenmek istenirse buraya eklenebilir.
		}
		case NAV_VELNED_36:
		{
			// VELNED paketi eklenmek istenirse buraya eklenebilir.
		}
	}
	gpsDatas->gpsEfficiency_u8 = ((float)gpsDatas->gps_errorhandler.trueData_u32 /(gpsDatas->gps_errorhandler.checksumError_u32 + gpsDatas->gps_errorhandler.validDataError_u32 + gpsDatas->gps_errorhandler.trueData_u32) * 100);
}


