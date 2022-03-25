/*
 * FLASH.h
 *
 *  Created on: 4 Ağu 2021
 *      Author: Yusuf Yıldız
 *      **************************************************************************************************
 *      Sector map can be found in the reference manual under the embedded flash memory interface bookmark
 *      **************************************************************************************************
 */

#ifndef INC_FLASH_H_
#define INC_FLASH_H_

#include "main.h"
#include "stm32f4xx_hal_flash.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define temp_hex_buffer_address 	0x08060000
#define application_start_address 	0x08020000
#define boot_loader_address 		0x08000000

#ifndef UART_FLAG_CTS
typedef void UART_HandleTypeDef;
#endif

UART_HandleTypeDef * HEX_UART;
uint32_t jump_step[2];

typedef enum{
	CATCH_COLON = 0,
	CATCH_RECORD_LENGTH = 1,
	CATCH_ADDRESS = 3,
	CACTH_RECORD_TYPE = 4,
	CATCH_DATA = 5,
	CATCH_CHECKSUM = 6,
	CATCH_ROW_COUNT = 7,
}HexFileStep;

typedef enum{
	Data_Record = 0x00,
	End_of_File_Record = 0x01,
	Extended_Segment_Address_Record = 0x02,
	Start_Segment_Address_Record = 0x03,
	Extended_Linear_Address_Record = 0x04,
	Start_Linear_Address_Record = 0x05,
	Row_Count = 0x06,
}RecordTypes;

typedef struct{
	uint8_t record_len;
	uint32_t record_address;
	uint8_t record_type;
	uint8_t checksum;
	uint16_t calculated_checksum;
	uint8_t checksum_error;
	uint8_t record[16];
	uint16_t row_count;
}HEX_File_TypeDef;

HEX_File_TypeDef Hex_File_Struct;
uint32_t GetSector(uint32_t Address);
uint8_t Flash_Clear_Sector(uint32_t StartSectorAddress);

uint8_t Flash_Write_Data_int8(uint32_t StartSectorAddress, int8_t *Data, uint16_t numberofwords);
uint8_t Flash_Write_Data_u8(uint32_t StartSectorAddress, uint8_t *Data, uint16_t numberofwords);
uint8_t Flash_Write_Data_int16(uint32_t StartSectorAddress, int16_t *Data, uint16_t numberofwords);
uint8_t Flash_Write_Data_u16(uint32_t StartSectorAddress, uint16_t *Data, uint16_t numberofwords);
uint32_t Flash_Write_Data_int32(uint32_t StartSectorAddress, int32_t *Data, uint16_t numberofwords);
uint32_t Flash_Write_Data_u32(uint32_t StartSectorAddress, uint32_t *Data, uint16_t numberofwords);

void Flash_Read_Data_int8 (uint32_t StartSectorAddress, int8_t *RxBuf, uint16_t numberofwords);
void Flash_Read_Data_u8 (uint32_t StartSectorAddress, uint8_t *RxBuf, uint16_t numberofwords);
void Flash_Read_Data_int16 (uint32_t StartSectorAddress, int16_t *RxBuf, uint16_t numberofwords);
void Flash_Read_Data_u16 (uint32_t StartSectorAddress, uint16_t *RxBuf, uint16_t numberofwords);
void Flash_Read_Data_int32 (uint32_t StartSectorAddress, int32_t *RxBuf, uint16_t numberofwords);
void Flash_Read_Data_u32 (uint32_t StartPageAddress, uint32_t *RxBuf, uint16_t numberofwords);

void Hex_File_Init();
void HEX_File_Control(uint8_t * buf, uint32_t len);
void Checksum_Control(void);
HAL_StatusTypeDef Flash_HEX_File(uint8_t *buf, uint32_t len);
uint8_t Hexadecimal_To_Decimal(uint8_t hexa);
void JumpToBootLoader();
void JumpToApplication();
#endif /* INC_FLASH_H_ */
