/*
 * Nextion.c
 *
 *  Created on: Feb 17, 2022
 *      Author: mert
 */

#include "main.h"
#include "Nextion.h"
#include "stdio.h"
#include "string.h"

uint8_t Cmd_End[3] = {0xFF,0xFF,0xFF};  // command end sequence


void NEXTION_SendNumber (UART_HandleTypeDef *huart, char *ID, int num)
{
	char buf[50] = { 0 };
	int len = sprintf (buf, "%s.val=%d", ID, num);
	HAL_UART_Transmit(huart, (uint8_t *)buf, len, 1000);
	HAL_UART_Transmit(huart, Cmd_End, 3, 100);
}


void NEXTION_SendString (UART_HandleTypeDef *huart, char *ID, char *string)
{
	char buf[50] = { 0 };
	int len = sprintf (buf, "%s.txt=\"%s\"", ID, string);
	HAL_UART_Transmit(huart, (uint8_t *)buf, len, 1000);
	HAL_UART_Transmit(huart, Cmd_End, 3, 100);
}
