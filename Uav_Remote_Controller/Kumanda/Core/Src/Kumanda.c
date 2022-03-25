/*
 * Kumanda.c
 *
 *  Created on: Feb 23, 2022
 *      Author: Mert KARAGÖZ
 */

#include "main.h"
#include "Kumanda.h"
#include "Nextion.h"
#include "math.h"

uint8_t i;

void SendToNextion_AllData(UART_HandleTypeDef *huart){

	if(Ekran == ANASAYFA_EKRANI){

		  NEXTION_SendNumber(huart, "pot1_bar", 		(uint16_t)(map(Kumanda_Data.scaled_data[0], KUMANDA_MIN, KUMANDA_MAX, EKRAN_MIN, EKRAN_MAX)));
		  NEXTION_SendNumber(huart, "pot2_bar", 		(uint16_t)(map(Kumanda_Data.scaled_data[1], KUMANDA_MIN, KUMANDA_MAX, EKRAN_MIN, EKRAN_MAX)));
		  NEXTION_SendNumber(huart, "throttle_bar", 	(uint16_t)(map(Kumanda_Data.scaled_data[2], KUMANDA_MIN, KUMANDA_MAX, EKRAN_MIN, EKRAN_MAX)));
		  NEXTION_SendNumber(huart, "yaw_bar", 			(uint16_t)(map(Kumanda_Data.scaled_data[3], KUMANDA_MIN, KUMANDA_MAX, EKRAN_MIN, EKRAN_MAX)));
		  NEXTION_SendNumber(huart, "roll_bar", 		(uint16_t)(map(Kumanda_Data.scaled_data[4], KUMANDA_MIN, KUMANDA_MAX, EKRAN_MIN, EKRAN_MAX)));
		  NEXTION_SendNumber(huart, "pitch_bar", 		(uint16_t)(map(Kumanda_Data.scaled_data[5], KUMANDA_MIN, KUMANDA_MAX, EKRAN_MIN, EKRAN_MAX)));
		  NEXTION_SendNumber(huart, "battery_bar",		(uint16_t)(100*(float)(Kumanda_Data.data[6]/4095.0)));

		  NEXTION_SendNumber(huart, "sw_1", Kumanda_Data.swtch[0]);
		  NEXTION_SendNumber(huart, "sw_2", Kumanda_Data.swtch[1]);
		  NEXTION_SendNumber(huart, "sw_3", Kumanda_Data.swtch[2]);
		  NEXTION_SendNumber(huart, "sw_4", Kumanda_Data.swtch[3]);

	}
	else if(Ekran == TRIM_EKRANI){

		  NEXTION_SendNumber(huart, "throttle_bar", 	(uint16_t)(map(Kumanda_Data.scaled_data[2], KUMANDA_MIN, KUMANDA_MAX, EKRAN_MIN, EKRAN_MAX)));
		  NEXTION_SendNumber(huart, "yaw_bar", 			(uint16_t)(map(Kumanda_Data.scaled_data[3], KUMANDA_MIN, KUMANDA_MAX, EKRAN_MIN, EKRAN_MAX)));
		  NEXTION_SendNumber(huart, "roll_bar", 		(uint16_t)(map(Kumanda_Data.scaled_data[4], KUMANDA_MIN, KUMANDA_MAX, EKRAN_MIN, EKRAN_MAX)));
		  NEXTION_SendNumber(huart, "pitch_bar", 		(uint16_t)(map(Kumanda_Data.scaled_data[5], KUMANDA_MIN, KUMANDA_MAX, EKRAN_MIN, EKRAN_MAX)));
		  NEXTION_SendNumber(huart, "battery_bar",		(uint16_t)(100*(float)(Kumanda_Data.data[6]/4095.0)));

		  NEXTION_SendNumber(huart, "thr_trim", Kumanda_Data.Ofsetler[0]);
		  NEXTION_SendNumber(huart, "yaw_trim", Kumanda_Data.Ofsetler[1]);
		  NEXTION_SendNumber(huart, "roll_trim", Kumanda_Data.Ofsetler[2]);
		  NEXTION_SendNumber(huart, "pitch_trim", Kumanda_Data.Ofsetler[3]);

	}
	else if(Ekran == PARLAKLIK_EKRANI){

		//hicbir sey gonderme

	}

}

void Map_AllData(){

//	  Kumanda_Data.data[3] = uzun_egri(Kumanda_Data.data[3]); 	//yaw
//	  Kumanda_Data.data[4] = kisa_egri(Kumanda_Data.data[4]);	//roll
//	  Kumanda_Data.data[5] = kisa_egri(Kumanda_Data.data[5]);	//pitch

	  Kumanda_Data.scaled_data[0] = map(Kumanda_Data.data[0], SOL_POT_MIN, SOL_POT_MAX, KUMANDA_MAX, KUMANDA_MIN);
	  Kumanda_Data.scaled_data[1] = map(Kumanda_Data.data[1], SAG_POT_MIN, SAG_POT_MAX, KUMANDA_MAX, KUMANDA_MIN);
	  Kumanda_Data.scaled_data[2] = map(Kumanda_Data.data[2], THROTTLE_MIN, THROTTLE_MAX, KUMANDA_MIN, KUMANDA_MAX);
	  Kumanda_Data.scaled_data[3] = map(Kumanda_Data.data[3], YAW_MIN, YAW_MAX, KUMANDA_MAX, KUMANDA_MIN);
	  Kumanda_Data.scaled_data[4] = map(Kumanda_Data.data[4], ROLL_MIN, ROLL_MAX, KUMANDA_MIN, KUMANDA_MAX);
	  Kumanda_Data.scaled_data[5] = map(Kumanda_Data.data[5], PITCH_MIN, PITCH_MAX, KUMANDA_MAX, KUMANDA_MIN);
	  Kumanda_Data.scaled_data[6] = (uint16_t)(1000*(float)(Kumanda_Data.data[6]/4095.0))+1000;

	  Kumanda_Data.scaled_data[2] += Kumanda_Data.Ofsetler[0];
	  Kumanda_Data.scaled_data[3] += Kumanda_Data.Ofsetler[1];
	  Kumanda_Data.scaled_data[4] += Kumanda_Data.Ofsetler[2];
	  Kumanda_Data.scaled_data[5] += Kumanda_Data.Ofsetler[3];

	  Kumanda_Data.scaled_data[2] = Stopper(Kumanda_Data.scaled_data[2]);
	  Kumanda_Data.scaled_data[3] = Stopper(Kumanda_Data.scaled_data[3]);
	  Kumanda_Data.scaled_data[4] = Stopper(Kumanda_Data.scaled_data[4]);
	  Kumanda_Data.scaled_data[5] = Stopper(Kumanda_Data.scaled_data[5]);

}

void Ekran_Control(const uint8_t *TEMP_BUF_EKRAN, uint16_t READ_BYTE){

	for(i = 0; i < READ_BYTE; i++)
	{

		if(TEMP_BUF_EKRAN[i] == 0x65)
		{

			if( (TEMP_BUF_EKRAN[i+1] == 0x01 && TEMP_BUF_EKRAN[i+2] == 0x06) || (TEMP_BUF_EKRAN[i+1] == 0x02 && TEMP_BUF_EKRAN[i+2] == 0x01))
			{
				if(TEMP_BUF_EKRAN[i+3] == 0x00)
					Ekran = ANASAYFA_EKRANI;

			}

			if( (TEMP_BUF_EKRAN[i+1] == 0x00 && TEMP_BUF_EKRAN[i+2] == 0x02) || (TEMP_BUF_EKRAN[i+1] == 0x02 && TEMP_BUF_EKRAN[i+2] == 0x02))
			{
				if(TEMP_BUF_EKRAN[i+3] == 0x00)
					Ekran = TRIM_EKRANI;

			}

			if( (TEMP_BUF_EKRAN[i+1] == 0x00 && TEMP_BUF_EKRAN[i+2] == 0x17) || (TEMP_BUF_EKRAN[i+1] == 0x01 && TEMP_BUF_EKRAN[i+2] == 0x13))
			{
				if(TEMP_BUF_EKRAN[i+3] == 0x00)
					Ekran = PARLAKLIK_EKRANI;

			}

			if( (Ekran == TRIM_EKRANI) && (TEMP_BUF_EKRAN[i+1] == 0x01) ){
				switch ( TEMP_BUF_EKRAN[i+2] )
				{
					case 0x07  : //THROTTLE +
					{
						Kumanda_Data.Ofsetler[0] += 1;
						break;
					}
					case 0x08 :	//THROTTLE -
					{
						Kumanda_Data.Ofsetler[0] -= 1;
						break;
					}
					case 0x09  : //YAW +
					{
						Kumanda_Data.Ofsetler[1] += 1;
						break;
					}
					case 0x0A :	//YAW -
					{
						Kumanda_Data.Ofsetler[1] -= 1;
						break;
					}
					case 0x0D  : //ROLL +
					{
						Kumanda_Data.Ofsetler[2] += 1;
						break;
					}
					case 0x0E :	//ROLL -
					{
						Kumanda_Data.Ofsetler[2] -= 1;
						break;
					}
					case 0x0B  : //PITCH +
					{
						Kumanda_Data.Ofsetler[3] += 1;
						break;
					}
					case 0x0C :	//PITCH -
					{
						Kumanda_Data.Ofsetler[3] -= 1;
						break;
					}
				}
			}
		}
	}
}


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
	read_byte = huart->RxXferSize - huart->hdmarx->Instance->CNDTR - usart_buffer->tail;

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

uint16_t map(uint16_t x, uint16_t in_min, uint16_t in_max, uint16_t out_min, uint16_t out_max)
{

  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}


uint16_t Stopper(uint16_t x)
{
  if(x > 2000)
	  x = 2000;

  if(x < 1000)
	  x = 1000;

  return x;
}

uint16_t uzun_egri(uint16_t x){
	if((x >= 1154) && (x <= 2942))
		x = ( ((x/4)-512)/10 * ((x/2)-1024)/50 * (x-2048)/200 ) + 2048;
	else
		x = x;

	return x;
}

int16_t kisa_egri(int16_t x){
	if((x >= 1720) && (x <= 2381))
		x = -exp((-(float)x/100.0)+23.0) + exp(((float)x/100.0)-18.0) + 2048.0;
	else
		x = x;

	return x;
}
