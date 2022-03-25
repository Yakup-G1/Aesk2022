/*
 * Nextion.h
 *
 *  Created on: Feb 17, 2022
 *      Author: mert
 */

#ifndef INC_NEXTION_H_
#define INC_NEXTION_H_




void NEXTION_SendNumber (UART_HandleTypeDef *huart, char *ID, int num);
void NEXTION_SendString (UART_HandleTypeDef *huart, char *ID, char *string);

#endif /* INC_NEXTION_H_ */
