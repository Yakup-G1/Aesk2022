/*
 * DSHOT.h
 *
 *  Created on: Jul 19, 2021
 *      Author: alper
 */

#ifndef SRC_DSHOT_H_
#define SRC_DSHOT_H_

#include "stm32f4xx_hal.h"
#include <stdbool.h>	// bool

#define MOTOR_BIT_0            	7
#define MOTOR_BIT_1            	14
#define MOTOR_BITLENGTH        	20

#define MOTOR_1_TIM             (&htim1)


void dshot_init(void);
void dshot_write(uint32_t* motor_dmabuffer, uint16_t value);
void dshot_write_all(uint16_t esc1, uint16_t esc2, uint16_t esc3, uint16_t esc4);

#endif /* SRC_DSHOT_H_ */
