/*
 * Kumanda.h
 *
 *  Created on: Feb 23, 2022
 *      Author: Mert KARAGÖZ
 */

#ifndef INC_KUMANDA_H_
#define INC_KUMANDA_H_

#define USART_BUFFER_SIZE 	256
#define BUFF_SIZE 			256

#define EKRAN_MIN			0
#define EKRAN_MAX			100
#define KUMANDA_MIN			1000
#define KUMANDA_MAX			2000

#define THROTTLE_MIN		60
#define THROTTLE_MAX		3720
#define YAW_MIN				200
#define YAW_MAX				3890
#define ROLL_MIN			160
#define ROLL_MAX			3820
#define PITCH_MIN			50
#define PITCH_MAX			3610

#define SOL_POT_MIN			0			// pot eklenince bu degerler degisecek
#define SOL_POT_MAX			4095		// pot eklenince bu degerler degisecek
#define SAG_POT_MIN			0			// pot eklenince bu degerler degisecek
#define SAG_POT_MAX			4095		// pot eklenince bu degerler degisecek


typedef struct
{
	uint8_t usart_receive_buffer[USART_BUFFER_SIZE];
	uint16_t tail;
}USART_Buffer;


typedef enum{
	ANASAYFA_EKRANI,
	TRIM_EKRANI,
	PARLAKLIK_EKRANI
}Hangi_Ekran;

Hangi_Ekran Ekran;


//  data[0] -> extra pot 1
//  data[1] -> extra pot 2
//  data[2] -> throttle
//  data[3] -> yaw
//  data[4] -> roll
//  data[5] -> pitch
//  data[6] -> battery voltage

typedef struct
{
	uint32_t adcBuffer[7];
	uint32_t data[7];
	uint16_t scaled_data[7];
	uint8_t swtch[4];
	uint8_t Rx_Buff[USART_BUFFER_SIZE];
	uint8_t Rx_indeks;
	int16_t Ofsetler[4];
	//[0] -> throttle ofset
	//[1] -> yaw ofset
	//[2] -> roll ofset
	//[3] -> pitch ofset

}Kumanda_t;

Kumanda_t Kumanda_Data;



void SendToNextion_AllData(UART_HandleTypeDef *huart);
void Map_AllData();
void Ekran_Control(const uint8_t *TEMP_BUF_EKRAN, uint16_t READ_BYTE);
void Uart_DMA_Receive_Start	(UART_HandleTypeDef *huart, USART_Buffer *usart_buffer);
int16_t read_DMA_Buffer	   	(UART_HandleTypeDef *huart, USART_Buffer *usart_buffer, uint8_t *temp_buf);
uint16_t map(uint16_t x, uint16_t in_min, uint16_t in_max, uint16_t out_min, uint16_t out_max);
uint16_t Stopper(uint16_t x);
uint16_t uzun_egri(uint16_t x);
int16_t kisa_egri(int16_t x);

#endif /* INC_KUMANDA_H_ */
