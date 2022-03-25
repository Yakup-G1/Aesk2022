/*
 * TFMini_S.c
 *
 *  Created on: Mar 3, 2022
 *      Author: Mert KARAG�Z
 *
 * 	Aciklama:
 *
 * 	Bu kutuphane yazilirken AESK_UART_STM32, AESK_Ring_Buffer kutuphanelerinden yararlanilmistir.
 *
 * 	1) Bu kutuphane Benewake firmasina ait TFmini-s lidar modeli icin yazilmistir.
 *
 *	2) UART DMA yapisi kullanilmistir.
 *
 *	4) MX dosyasinda yapilacak ayarlar ->
 *		UART acilacak.
 *		parameter settings'ten -> 115200 baudrate, 8 bits word length, parity none, stop bit 1 olarak ayaranacak.
 *		NVIC settings'ten -> global interrupt aktif edilecek.
 *		DMA settings'ten -> UARTX_RX eklenip, direction: perip. to memory olarak ayarlanacak.
 *		DMA Request Settings'ten -> mode: circular, increment address: memory, data width: byte olarak ayarlanacak.
 *
 *	5) main dosyasina eklenecek seyler ->
 *		#include "TFMini_S.h" eklenecek.
 *		USER CODE BEGIN PV arasina ->
 *      	uint8_t temp_buf_lidar[1024] = { 0 }; //Lidar verileri icin buffer
 *      	uint16_t read_byte_lidar = 0; 		//Lidar'ten okunan byte sayisi
 *      	USART_Buffer LIDAR_UART_Bufferi;
 *      	LIDAR_Handle LIDAR_Data;
 *			eklenecek.
 *		USER CODE BEGIN 2 arasina ->
 *			 LIDAR_Config(&huartX, &LIDAR_UART_Bufferi);
 *			eklenecek.
 *		While icine ->
 *		read_byte_lidar = read_DMA_Buffer(&huartX, &LIDAR_UART_Bufferi, temp_buf_lidar);
 *			if(read_byte_lidar > 0)
 *				LIDAR_Data_Parser(&LIDAR_Data, temp_buf_lidar, read_byte_lidar);
 *			eklenecek.
 *
 *		!!!NOT &huartX yazan yerlerde X yerine aktif edilen uart yaz�lacaktir. �rnek: &huart4, &huart5.
 *
 *
 */



#include "TFMini_S.h"
#include "GPS_UBX.h"
#include "ReadingSensor.h"


uint8_t i,
		check = 0,
		gelen_check = 0,
		Buffer[9];

uint32_t say = 0;


//void Uart_DMA_Receive_Start(UART_HandleTypeDef *huart, USART_Buffer *usart_buffer)
//{
//	for(uint16_t i = 0; i < sizeof(USART_Buffer); i++)
//	{
//		((uint8_t*)usart_buffer)[i] = 0;
//	}
//	 while(HAL_UART_Receive_DMA(huart, usart_buffer->usart_receive_buffer, USART_BUFFER_SIZE) != HAL_OK);
//	__HAL_UART_CLEAR_PEFLAG(huart);
//}
//
//int16_t read_DMA_Buffer(UART_HandleTypeDef *huart, USART_Buffer *usart_buffer, uint8_t *temp_buf)
//{
//	int16_t read_byte = 0;
//	read_byte = huart->RxXferSize - huart->hdmarx->Instance->NDTR - usart_buffer->tail;
//
//	if(read_byte == 0)
//		return read_byte;
//
//	else
//	{
//		if(read_byte < 0)
//			read_byte = read_byte + huart->RxXferSize;
//
//		for(uint16_t i = 0; i < read_byte; i++)
//		{
//			temp_buf[i] = usart_buffer->usart_receive_buffer[usart_buffer->tail];
//			usart_buffer->tail++;
//
//			if(usart_buffer->tail >= huart->RxXferSize)
//				usart_buffer->tail = 0;
//		}
//		return read_byte;
//	}
//}


		
void LIDAR_Config(UART_HandleTypeDef *huart, TF_USART_Buffer *USART_Buf)
{
	Uart_DMA_Receive_Start(huart, USART_Buf);
}

void LIDAR_Data_Parser(LIDAR_Handle *lidarDatas, const uint8_t *datas, uint8_t read_byte)
{

	static uint8_t ci = 0;  // checksum control indeks
	uint8_t check_toplam = 0;
	for(i = 0; i < read_byte ; i++)
	{
		switch(lidarDatas->state)
		{
			case YAKALA_HEADS :
			{
				if( (datas[i] == HEADS) && (datas[i+1] == HEADS) )
				{
					for(ci = 0; ci < 8; ci++)
					{
						check_toplam = check_toplam + datas[i+ci];
					}

					if(check_toplam == datas[i+8])
					{
						lidarDatas->state = PARSE_LIDAR;
						say++;
					}
					else{
						lidarDatas->checksumError_u32++;
					}
					check_toplam = 0;
//					lidarDatas->state = PARSE_LIDAR;

				}else{
					lidarDatas->state = YAKALA_HEADS;
				}

				break;
			}
			case PARSE_LIDAR :
			{

				lidarDatas->LIDAR_Pack.Distance 	= datas[i+2] << 8 | datas[i+1];
				lidarDatas->LIDAR_Pack.Strength 	= datas[i+4] << 8 | datas[i+3];
				lidarDatas->LIDAR_Pack.Mode 		= datas[i+5];
				lidarDatas->LIDAR_Pack.SpareByte 	= datas[i+6];
				lidarDatas->LIDAR_Pack.Checksum 	= datas[i+7];

				lidarDatas->LIDAR_Pack.AngleDistance = ((float)lidarDatas->LIDAR_Pack.Distance/100.0f) - (Barometer_Altitude*AltitudeCalculator*sqrt(pow(Ahrs_ROLL,2)+pow(Ahrs_PITCH,2)));

				lidarDatas->state = YAKALA_HEADS;

				break;
			}

		}

	}

}
