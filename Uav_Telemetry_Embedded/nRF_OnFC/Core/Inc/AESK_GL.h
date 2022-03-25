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

 typedef union
 {
     struct
     {
         uint8_t task_1000_Hz : 1 ;
         uint8_t task_200_Hz : 1;
         uint8_t task_100_Hz : 1;
         uint8_t task_50_Hz : 1;
         uint8_t task_20_Hz : 1;
         uint8_t task_10_Hz : 1;
         uint8_t task_2_Hz : 1;
         uint8_t task_1_Hz : 1;
         uint8_t reserved : 2;
     }time_task_t;
     uint8_t all_u8;
 }time_task_union;

 time_task_union tt;

  typedef struct
  {

	  uint32_t system_clock_counter_1ms;
  }AESK_GL;

  AESK_GL aesk_gl;

  void AESK_GL_Init(AESK_GL* aesk_gl);
  uint16_t aeskCRCCalculator(uint8_t * frame, size_t framesize);


#endif /* INC_AESK_GL_H_ */
