/*
 * AESK_GL.h
 *
 *  Created on: Dec 12, 2020
 *      Author: basri
 */

#ifndef INC_AESK_GL_H_
#define INC_AESK_GL_H_

#include "main.h"

 typedef enum
 {
	 FIFO_0 = 0,
	 FIFO_1,
	 TOTAL_FIFO,
 }FIFO_NUMBER;


  uint16_t aeskCRCCalculator(uint8_t * frame, size_t framesize);


#endif /* INC_AESK_GL_H_ */
