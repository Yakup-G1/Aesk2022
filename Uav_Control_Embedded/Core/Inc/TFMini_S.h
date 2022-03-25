/*
 * TFMini_S.h
 *
 *  Created on: Mar 3, 2022
 *      Author: Mert KARAGOZ
 */

#ifndef TFMINI_S_H_
#define TFMINI_S_H_

#include "main.h"
#include "stdint.h"
#include "string.h"

#define USART_BUFFER_SIZE 		1024
#define BUFFER_SIZE  			1024

#define HEADS					0x59


typedef struct
{
	uint8_t usart_receive_buffer[USART_BUFFER_SIZE];
	uint16_t tail;
}TF_USART_Buffer;

typedef enum
{
	YAKALA_HEADS = 0,
	PARSE_LIDAR
}LIDAR_States;

typedef struct {
	uint16_t 	Distance;
	uint16_t 	Strength;
	uint8_t 	Mode;
	uint8_t 	SpareByte;
	uint8_t 	Checksum;
	float 		AngleDistance;
}LIDAR_Pack_t;

typedef struct{
	LIDAR_States 			state;
	uint32_t 				checksumError_u32;
	LIDAR_Pack_t			LIDAR_Pack;
}LIDAR_Handle;


//void Uart_DMA_Receive_Start	(UART_HandleTypeDef *huart, USART_Buffer *usart_buffer);
//int16_t read_DMA_Buffer	   	(UART_HandleTypeDef *huart, USART_Buffer *usart_buffer, uint8_t *temp_buf);
void LIDAR_Config(UART_HandleTypeDef *huart, TF_USART_Buffer *USART_Buf);
void LIDAR_Data_Parser(LIDAR_Handle *lidarDatas, const uint8_t *datas, uint8_t read_byte);

#endif /* TFMINI_S_H_ */
