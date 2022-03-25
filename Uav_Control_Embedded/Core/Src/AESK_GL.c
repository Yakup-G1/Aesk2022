/*
 * AESK_GL.c
 *
 *  Created on: Dec 12, 2020
 *      Author: basri
 */

#include "AESK_GL.h"


uint16_t aeskCRCCalculator(uint8_t *frame, size_t framesize)
{
	uint16_t crc16_data = 0;
	uint8_t data = 0;
	for (uint8_t mlen = 0; mlen < framesize; mlen++)
	{
		data = frame[mlen] ^ ((uint8_t) (crc16_data) & (uint8_t) (0xFF));
		data ^= data << 4;
		crc16_data = ((((uint16_t) data << 8) | ((crc16_data & 0xFF00) >> 8)) ^ (uint8_t) (data >> 4) ^ ((uint16_t) data << 3));
	}
	return (crc16_data);
}




