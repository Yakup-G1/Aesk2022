/*
 * FLASH.c
 *
 *  Created on: 4 Ağu 2021
 *      Author: Yusuf Yıldız
 *      **************************************************************************************************
 *      Sector map can be found in the reference manual under the embedded flash memory interface bookmark
 *      **************************************************************************************************
 */
#include "FLASH.h"

uint8_t HEX_FLASH_Buffer[40096] = {0};

uint8_t Flash_Clear_Sector(uint32_t StartSectorAddress)
{
	FLASH_EraseInitTypeDef EraseInitStruct;
	uint32_t SECTORError = 0;;
	HAL_FLASH_Unlock(); //Unlock the Flash to enable the flash control register access


	EraseInitStruct.TypeErase = FLASH_TYPEERASE_SECTORS;
	EraseInitStruct.Sector = GetSector(StartSectorAddress); // start address
	EraseInitStruct.NbSectors = 1;

	if (HAL_FLASHEx_Erase(&EraseInitStruct, &SECTORError) != HAL_OK)
	{
		SECTORError = SECTORError + 1;
		HAL_FLASH_Lock();
		return HAL_ERROR;
	}
	HAL_FLASH_Lock();
	return HAL_OK;
}

uint32_t GetSector(uint32_t Address)
{
  uint32_t sector = 0;

  if((Address < 0x08003FFF) && (Address >= 0x08000000))
  {
    sector = FLASH_SECTOR_0;
  }
  else if((Address < 0x08007FFF) && (Address >= 0x08004000))
  {
    sector = FLASH_SECTOR_1;
  }
  else if((Address < 0x0800BFFF) && (Address >= 0x08008000))
  {
    sector = FLASH_SECTOR_2;
  }
  else if((Address < 0x0800FFFF) && (Address >= 0x0800C000))
  {
    sector = FLASH_SECTOR_3;
  }
  else if((Address < 0x0801FFFF) && (Address >= 0x08010000))
  {
    sector = FLASH_SECTOR_4;
  }
  else if((Address < 0x0803FFFF) && (Address >= 0x08020000))
  {
    sector = FLASH_SECTOR_5;
  }
  else if((Address < 0x0805FFFF) && (Address >= 0x08040000))
  {
    sector = FLASH_SECTOR_6;
  }
  else if((Address < 0x0807FFFF) && (Address >= 0x08060000))
  {
    sector = FLASH_SECTOR_7;
  }
  else if((Address < 0x0809FFFF) && (Address >= 0x08080000))
  {
    sector = FLASH_SECTOR_8;
  }
  else if((Address < 0x080BFFFF) && (Address >= 0x080A0000))
  {
    sector = FLASH_SECTOR_9;
  }
  else if((Address < 0x080DFFFF) && (Address >= 0x080C0000))
  {
    sector = FLASH_SECTOR_10;
  }
  else if((Address < 0x080FFFFF) && (Address >= 0x080E0000))
  {
    sector = FLASH_SECTOR_11;
  }
 /* else if((Address < 0x08103FFF) && (Address >= 0x08100000))
  {
    sector = FLASH_SECTOR_12;
  }
  else if((Address < 0x08107FFF) && (Address >= 0x08104000))
  {
    sector = FLASH_SECTOR_13;
  }
  else if((Address < 0x0810BFFF) && (Address >= 0x08108000))
  {
    sector = FLASH_SECTOR_14;
  }
  else if((Address < 0x0810FFFF) && (Address >= 0x0810C000))
  {
    sector = FLASH_SECTOR_15;
  }
  else if((Address < 0x0811FFFF) && (Address >= 0x08110000))
  {
    sector = FLASH_SECTOR_16;
  }
  else if((Address < 0x0813FFFF) && (Address >= 0x08120000))
  {
    sector = FLASH_SECTOR_17;
  }
  else if((Address < 0x0815FFFF) && (Address >= 0x08140000))
  {
    sector = FLASH_SECTOR_18;
  }
  else if((Address < 0x0817FFFF) && (Address >= 0x08160000))
  {
    sector = FLASH_SECTOR_19;
  }
  else if((Address < 0x0819FFFF) && (Address >= 0x08180000))
  {
    sector = FLASH_SECTOR_20;
  }
  else if((Address < 0x081BFFFF) && (Address >= 0x081A0000))
  {
    sector = FLASH_SECTOR_21;
  }
  else if((Address < 0x081DFFFF) && (Address >= 0x081C0000))
  {
    sector = FLASH_SECTOR_22;
  }
  else if (Address < 0x081FFFFF) && (Address >= 0x081E0000)
  {
    sector = FLASH_SECTOR_23;
  }*/
  return sector;
}

uint8_t Flash_Write_Data_int8(uint32_t StartSectorAddress, int8_t *Data, uint16_t numberofwords)
{

	static FLASH_EraseInitTypeDef EraseInitStruct;
	uint32_t SECTORError;
	int sofar=0;

	 /* Unlock the Flash to enable the flash control register access *************/
	  HAL_FLASH_Unlock();

	  /* Erase the user Flash area */

	  /* Get the number of sector to erase from 1st sector */

	  uint32_t StartSector = GetSector(StartSectorAddress);
	  uint32_t EndSectorAddress = StartSectorAddress + numberofwords*4;
	  uint32_t EndSector = GetSector(EndSectorAddress);

	  /* Fill EraseInit structure*/
	  EraseInitStruct.TypeErase     = FLASH_TYPEERASE_SECTORS;
	  EraseInitStruct.VoltageRange  = FLASH_VOLTAGE_RANGE_3;
	  EraseInitStruct.Sector        = StartSector;
	  EraseInitStruct.NbSectors     = (EndSector - StartSector) + 1;

	  /* Note: If an erase operation in Flash memory also concerns data in the data or instruction cache,
	     you have to make sure that these data are rewritten before they are accessed during code
	     execution. If this cannot be done safely, it is recommended to flush the caches by setting the
	     DCRST and ICRST bits in the FLASH_CR register. */
	  if (HAL_FLASHEx_Erase(&EraseInitStruct, &SECTORError) != HAL_OK)
	  {
		  return HAL_FLASH_GetError ();
	  }

	  /* Program the user Flash area word by word
	    (area defined by FLASH_USER_START_ADDR and FLASH_USER_END_ADDR) ***********/

	   while (sofar<numberofwords)
	   {
	     if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_BYTE, StartSectorAddress, Data[sofar]) == HAL_OK)
	     {
	    	 StartSectorAddress += 1;  // use StartPageAddress += 2 for half word and 8 for double word
	    	 sofar++;
	     }
	     else
	     {
	       /* Error occurred while writing data in Flash memory*/
	    	 return HAL_FLASH_GetError ();
	     }
	   }

	  /* Lock the Flash to disable the flash control register access (recommended
	     to protect the FLASH memory against possible unwanted operation) *********/
	  HAL_FLASH_Lock();
	  return HAL_OK;
}

uint8_t Flash_Write_Data_u8(uint32_t StartSectorAddress, uint8_t *Data, uint16_t numberofwords)
{

	static FLASH_EraseInitTypeDef EraseInitStruct;
	uint32_t SECTORError;
	int sofar=0;

	 /* Unlock the Flash to enable the flash control register access *************/
	  HAL_FLASH_Unlock();

	  /* Erase the user Flash area */

	  /* Get the number of sector to erase from 1st sector */

	  uint32_t StartSector = GetSector(StartSectorAddress);
	  uint32_t EndSectorAddress = StartSectorAddress + numberofwords*4;
	  uint32_t EndSector = GetSector(EndSectorAddress);

	  /* Fill EraseInit structure*/
	  EraseInitStruct.TypeErase     = FLASH_TYPEERASE_SECTORS;
	  EraseInitStruct.VoltageRange  = FLASH_VOLTAGE_RANGE_3;
	  EraseInitStruct.Sector        = StartSector;
	  EraseInitStruct.NbSectors     = (EndSector - StartSector) + 1;

	  /* Note: If an erase operation in Flash memory also concerns data in the data or instruction cache,
	     you have to make sure that these data are rewritten before they are accessed during code
	     execution. If this cannot be done safely, it is recommended to flush the caches by setting the
	     DCRST and ICRST bits in the FLASH_CR register. */
	  if (HAL_FLASHEx_Erase(&EraseInitStruct, &SECTORError) != HAL_OK)
	  {
		  return HAL_FLASH_GetError ();
	  }

	  /* Program the user Flash area word by word
	    (area defined by FLASH_USER_START_ADDR and FLASH_USER_END_ADDR) ***********/

	   while (sofar<numberofwords)
	   {
	     if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_BYTE, StartSectorAddress, Data[sofar]) == HAL_OK)
	     {
	    	 StartSectorAddress += 1;  // use StartPageAddress += 2 for half word and 8 for double word
	    	 sofar++;
	     }
	     else
	     {
	       /* Error occurred while writing data in Flash memory*/
	    	 return HAL_FLASH_GetError ();
	     }
	   }

	  /* Lock the Flash to disable the flash control register access (recommended
	     to protect the FLASH memory against possible unwanted operation) *********/
	  HAL_FLASH_Lock();

	  return HAL_OK;
}

uint8_t Flash_Write_Data_int16(uint32_t StartSectorAddress, int16_t *Data, uint16_t numberofwords)
{

	static FLASH_EraseInitTypeDef EraseInitStruct;
	uint32_t SECTORError;
	int sofar=0;

	 /* Unlock the Flash to enable the flash control register access *************/
	  HAL_FLASH_Unlock();

	  /* Erase the user Flash area */

	  /* Get the number of sector to erase from 1st sector */

	  uint32_t StartSector = GetSector(StartSectorAddress);
	  uint32_t EndSectorAddress = StartSectorAddress + numberofwords*4;
	  uint32_t EndSector = GetSector(EndSectorAddress);

	  /* Fill EraseInit structure*/
	  EraseInitStruct.TypeErase     = FLASH_TYPEERASE_SECTORS;
	  EraseInitStruct.VoltageRange  = FLASH_VOLTAGE_RANGE_3;
	  EraseInitStruct.Sector        = StartSector;
	  EraseInitStruct.NbSectors     = (EndSector - StartSector) + 1;

	  /* Note: If an erase operation in Flash memory also concerns data in the data or instruction cache,
	     you have to make sure that these data are rewritten before they are accessed during code
	     execution. If this cannot be done safely, it is recommended to flush the caches by setting the
	     DCRST and ICRST bits in the FLASH_CR register. */
	  if (HAL_FLASHEx_Erase(&EraseInitStruct, &SECTORError) != HAL_OK)
	  {
		  return HAL_FLASH_GetError ();
	  }

	  /* Program the user Flash area word by word
	    (area defined by FLASH_USER_START_ADDR and FLASH_USER_END_ADDR) ***********/

	   while (sofar<numberofwords)
	   {
			if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, StartSectorAddress, Data[sofar]) == HAL_OK)
			{
			 StartSectorAddress += 2;  // use StartPageAddress += 2 for half word and 8 for double word
			 sofar++;
			}
			else
			{
			/* Error occurred while writing data in Flash memory*/
			 return HAL_FLASH_GetError ();
			}
	   }

	  /* Lock the Flash to disable the flash control register access (recommended
	     to protect the FLASH memory against possible unwanted operation) *********/
	  HAL_FLASH_Lock();
	  return HAL_OK;
}

uint8_t Flash_Write_Data_u16(uint32_t StartSectorAddress, uint16_t *Data, uint16_t numberofwords)
{

	static FLASH_EraseInitTypeDef EraseInitStruct;
	uint32_t SECTORError;
	int sofar=0;

	 /* Unlock the Flash to enable the flash control register access *************/
	  HAL_FLASH_Unlock();

	  /* Erase the user Flash area */

	  /* Get the number of sector to erase from 1st sector */

	  uint32_t StartSector = GetSector(StartSectorAddress);
	  uint32_t EndSectorAddress = StartSectorAddress + numberofwords*4;
	  uint32_t EndSector = GetSector(EndSectorAddress);

	  /* Fill EraseInit structure*/
	  EraseInitStruct.TypeErase     = FLASH_TYPEERASE_SECTORS;
	  EraseInitStruct.VoltageRange  = FLASH_VOLTAGE_RANGE_3;
	  EraseInitStruct.Sector        = StartSector;
	  EraseInitStruct.NbSectors     = (EndSector - StartSector) + 1;

	  if (HAL_FLASHEx_Erase(&EraseInitStruct, &SECTORError) != HAL_OK)
	  {
		  return HAL_FLASH_GetError ();
	  }

	  /* Program the user Flash area word by word
	    (area defined by FLASH_USER_START_ADDR and FLASH_USER_END_ADDR) ***********/

	   while (sofar<numberofwords)
	   {
	     if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, StartSectorAddress, Data[sofar]) == HAL_OK)
	     {
	    	 StartSectorAddress += 2;  // use StartPageAddress += 2 for half word and 8 for double word
	    	 sofar++;
	     }
	     else
	     {
	       /* Error occurred while writing data in Flash memory*/
	    	 return HAL_FLASH_GetError ();
	     }
	   }

	  /* Lock the Flash to disable the flash control register access (recommended
	     to protect the FLASH memory against possible unwanted operation) *********/
	  HAL_FLASH_Lock();

	  return HAL_OK;
}

uint32_t Flash_Write_Data_int32(uint32_t StartSectorAddress, int32_t *Data, uint16_t numberofwords)
{

	static FLASH_EraseInitTypeDef EraseInitStruct;
	uint32_t SECTORError;
	int sofar=0;


	 /* Unlock the Flash to enable the flash control register access *************/
	  HAL_FLASH_Unlock();

	  /* Erase the user Flash area */

	  /* Get the number of sector to erase from 1st sector */

	  uint32_t StartSector = GetSector(StartSectorAddress);
	  uint32_t EndSectorAddress = StartSectorAddress + numberofwords*4;
	  uint32_t EndSector = GetSector(EndSectorAddress);

	  /* Fill EraseInit structure*/
	  EraseInitStruct.TypeErase     = FLASH_TYPEERASE_SECTORS;
	  EraseInitStruct.VoltageRange  = FLASH_VOLTAGE_RANGE_3;
	  EraseInitStruct.Sector        = StartSector;
	  EraseInitStruct.NbSectors     = (EndSector - StartSector) + 1;

	  /* Note: If an erase operation in Flash memory also concerns data in the data or instruction cache,
	     you have to make sure that these data are rewritten before they are accessed during code
	     execution. If this cannot be done safely, it is recommended to flush the caches by setting the
	     DCRST and ICRST bits in the FLASH_CR register. */
	  if (HAL_FLASHEx_Erase(&EraseInitStruct, &SECTORError) != HAL_OK)
	  {
		  return HAL_FLASH_GetError ();
	  }

	  /* Program the user Flash area word by word
	    (area defined by FLASH_USER_START_ADDR and FLASH_USER_END_ADDR) ***********/

	   while (sofar<numberofwords)
	   {
	     if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, StartSectorAddress, Data[sofar]) == HAL_OK)
	     {
	    	 StartSectorAddress += 4;  // use StartPageAddress += 2 for half word and 8 for double word
	    	 sofar++;
	     }
	     else
	     {
	       /* Error occurred while writing data in Flash memory*/
	    	 return HAL_FLASH_GetError ();
	     }
	   }
	  /* Lock the Flash to disable the flash control register access (recommended
	     to protect the FLASH memory against possible unwanted operation) *********/
	  HAL_FLASH_Lock();

	  return HAL_OK;
}

uint32_t Flash_Write_Data_u32(uint32_t StartSectorAddress, uint32_t *Data, uint16_t numberofwords)
{

	static FLASH_EraseInitTypeDef EraseInitStruct;
	uint32_t SECTORError;
	int sofar=0;


	 /* Unlock the Flash to enable the flash control register access *************/
	  HAL_FLASH_Unlock();

	  /* Erase the user Flash area */

	  /* Get the number of sector to erase from 1st sector */

	  uint32_t StartSector = GetSector(StartSectorAddress);
	  uint32_t EndSectorAddress = StartSectorAddress + numberofwords*4;
	  uint32_t EndSector = GetSector(EndSectorAddress);

	  /* Fill EraseInit structure*/
	  EraseInitStruct.TypeErase     = FLASH_TYPEERASE_SECTORS;
	  EraseInitStruct.VoltageRange  = FLASH_VOLTAGE_RANGE_3;
	  EraseInitStruct.Sector        = StartSector;
	  EraseInitStruct.NbSectors     = (EndSector - StartSector) + 1;

	  /* Note: If an erase operation in Flash memory also concerns data in the data or instruction cache,
	     you have to make sure that these data are rewritten before they are accessed during code
	     execution. If this cannot be done safely, it is recommended to flush the caches by setting the
	     DCRST and ICRST bits in the FLASH_CR register. */
	  if (HAL_FLASHEx_Erase(&EraseInitStruct, &SECTORError) != HAL_OK)
	  {
		  return HAL_FLASH_GetError ();
	  }

	  /* Program the user Flash area word by word
	    (area defined by FLASH_USER_START_ADDR and FLASH_USER_END_ADDR) ***********/

	   while (sofar<numberofwords)
	   {
	     if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, StartSectorAddress, Data[sofar]) == HAL_OK)
	     {
	    	 StartSectorAddress += 4;  // use StartPageAddress += 2 for half word and 8 for double word
	    	 sofar++;
	     }
	     else
	     {
	       /* Error occurred while writing data in Flash memory*/
	    	 return HAL_FLASH_GetError ();
	     }
	   }
	  /* Lock the Flash to disable the flash control register access (recommended
	     to protect the FLASH memory against possible unwanted operation) *********/
	  HAL_FLASH_Lock();

	  return HAL_OK;
}

void Flash_Read_Data_int8 (uint32_t StartSectorAddress, int8_t *RxBuf, uint16_t numberofwords)
{
	while (numberofwords--)
	{
		*RxBuf = *(__IO uint32_t *)StartSectorAddress;
		StartSectorAddress += 1;
		RxBuf++;
	}
}

void Flash_Read_Data_u8 (uint32_t StartSectorAddress, uint8_t *RxBuf, uint16_t numberofwords)
{
	while (numberofwords--)
	{
		*RxBuf = *(__IO uint32_t *)StartSectorAddress;
		StartSectorAddress += 1;
		RxBuf++;
	}
}

void Flash_Read_Data_int16 (uint32_t StartSectorAddress, int16_t *RxBuf, uint16_t numberofwords)
{
	while (numberofwords--)
		{
			*RxBuf = *(__IO uint32_t *)StartSectorAddress;
			StartSectorAddress += 2;
			RxBuf++;
		}
}

void Flash_Read_Data_u16 (uint32_t StartSectorAddress, uint16_t *RxBuf, uint16_t numberofwords)
{
	while (numberofwords--)
	{
		*RxBuf = *(__IO uint32_t *)StartSectorAddress;
		StartSectorAddress += 2;
		RxBuf++;
	}
}

void Flash_Read_Data_int32 (uint32_t StartSectorAddress, int32_t *RxBuf, uint16_t numberofwords)
{
	while (numberofwords--)
	{
		*RxBuf = *(__IO uint32_t *)StartSectorAddress;
		StartSectorAddress += 4;
		RxBuf++;
	}
}

void Flash_Read_Data_u32 (uint32_t StartSectorAddress, uint32_t *RxBuf, uint16_t numberofwords)
{
	while (numberofwords--)
	{
		*RxBuf = *(__IO uint32_t *)StartSectorAddress;
		StartSectorAddress += 4;
		RxBuf++;
	}
}


#ifdef UART_FLAG_CTS
void Hex_File_Init(UART_HandleTypeDef * huart)
{
	HEX_UART = huart;
	Hex_File_Struct.record_len = 0;
	Hex_File_Struct.record_address = 0;
	Hex_File_Struct.record_type = 0;
	Hex_File_Struct.checksum = 0;
	Hex_File_Struct.calculated_checksum = 0;
	Hex_File_Struct.checksum_error = 0;
	Hex_File_Struct.row_count = 0;
}
void HEX_File_Control(uint8_t * buf, uint32_t len)
{
	uint8_t step = CATCH_COLON;
	uint8_t address_count = 0;
	uint8_t record_count = 0;
	uint8_t i = 0;
	uint8_t tempbuf[255];
	memcpy(tempbuf,buf,len);
	Hex_File_Struct.row_count++;
	for (i = 0; i < len; i++)
	{
		switch (step)
		{
			case CATCH_COLON:
			{
				if(buf[i] == ':')
				{
					step = CATCH_RECORD_LENGTH;
				}
				break;
			}
			case CATCH_RECORD_LENGTH:
			{
				Hex_File_Struct.record_len = Hexadecimal_To_Decimal(buf[i])*16;
				i++;
				Hex_File_Struct.record_len += Hexadecimal_To_Decimal(buf[i]);

				step = CATCH_ADDRESS;
				break;
			}
			case CATCH_ADDRESS:
			{

				Hex_File_Struct.record_address = (Hex_File_Struct.record_address << 4) | Hexadecimal_To_Decimal(buf[i]);
				address_count++;
				if(address_count == 4)
				{
					address_count = 0;
					step = CACTH_RECORD_TYPE;
				}
				break;
			}
			case CACTH_RECORD_TYPE:
			{
				Hex_File_Struct.record_type = Hexadecimal_To_Decimal(buf[i])*16;
				i++;
				Hex_File_Struct.record_type += Hexadecimal_To_Decimal(buf[i]);
				if(Hex_File_Struct.record_len != 0)
				{
					step = CATCH_DATA;
				}
				else
				{
					step = CATCH_CHECKSUM;
				}
				break;
			}
			case CATCH_DATA:
			{
				Hex_File_Struct.record[record_count] = Hexadecimal_To_Decimal(buf[i])*16;
				i++;
				Hex_File_Struct.record[record_count++] += Hexadecimal_To_Decimal(buf[i]);

				if(record_count == Hex_File_Struct.record_len)
				{
					record_count = 0;
					step = CATCH_CHECKSUM;
				}

				break;
			}
			case CATCH_CHECKSUM:
			{
				Hex_File_Struct.checksum = Hexadecimal_To_Decimal(buf[i])*16;
				i++;
				Hex_File_Struct.checksum += Hexadecimal_To_Decimal(buf[i]);
				Checksum_Control();
				step = CATCH_COLON;
				break;
			}
			default:
				break;
		}
	}
}
void Checksum_Control()
{
	uint8_t i;
	Hex_File_Struct.calculated_checksum = 0;
	for (i = 0; i < Hex_File_Struct.record_len; i++)
	{
		Hex_File_Struct.calculated_checksum += Hex_File_Struct.record[i];
	}
	Hex_File_Struct.calculated_checksum += (Hex_File_Struct.record_address>>8) + (Hex_File_Struct.record_address & 0xFF);
	Hex_File_Struct.calculated_checksum += Hex_File_Struct.record_len + Hex_File_Struct.record_type;
	Hex_File_Struct.calculated_checksum = (~Hex_File_Struct.calculated_checksum) + 1;

	if((uint8_t)Hex_File_Struct.calculated_checksum == Hex_File_Struct.checksum)
	{
		static uint16_t buf_count = 0;

		//buffera yaz
		if(Hex_File_Struct.record_type == Data_Record)
		{
			for (i = 0; i < Hex_File_Struct.record_len; i++)
			{
				HEX_FLASH_Buffer[buf_count++] = Hex_File_Struct.record[i];
			}
		}
		else if(Hex_File_Struct.record_type == End_of_File_Record)
		{
			if(Hex_File_Struct.checksum_error == 0)
			{
				HAL_UART_Transmit(HEX_UART, (uint8_t *)"DONE", sizeof("DONE"), HAL_MAX_DELAY);
				Flash_HEX_File(HEX_FLASH_Buffer,buf_count);
			}
			else
			{
				Hex_File_Struct.checksum_error = 0;
			}

		}
		else if(Hex_File_Struct.record_type == Extended_Linear_Address_Record)
		{

		}
		else if(Hex_File_Struct.record_type == Start_Linear_Address_Record)
		{

		}
		Hex_File_Struct.record_type = 0;
		Hex_File_Struct.record_len = 0;
		Hex_File_Struct.checksum = 0;
		Hex_File_Struct.record_address = 0;
		HAL_UART_Transmit(HEX_UART, (uint8_t *)"OK", sizeof("OK"), HAL_MAX_DELAY);
	}
	else
	{
		Hex_File_Struct.checksum_error++;
		HAL_UART_Transmit(HEX_UART, (uint8_t *)"ERROR", sizeof("ERROR"), HAL_MAX_DELAY);
	}

}
#endif
HAL_StatusTypeDef Flash_HEX_File(uint8_t *buf, uint32_t len)
{
	HAL_StatusTypeDef status;
	Flash_Write_Data_u8(temp_hex_buffer_address, buf, len);
	jump_step[0] = 1;
	jump_step[1] = len;
	Flash_Write_Data_u32(0x08040000,jump_step,sizeof(jump_step));
	NVIC_SystemReset();
	return status;
}
void JumpToApplication() // bootloaderdan applicationa geçiş
{
	Flash_Read_Data_u32(0x08040000,jump_step,sizeof(jump_step));

	//eğer hex dosyası yükleme komutu gelmişse komutu yükleyip geçiş yap
	if(jump_step[0] == 1)
	{
		uint8_t buf[40096] = {0};
		jump_step[0] = 0;
		Flash_Write_Data_u32(0x08040000,jump_step,sizeof(jump_step));

		printf("HEX File loading...\r\n");
		//hex dosyasını yükle
		Flash_Read_Data_u8(temp_hex_buffer_address, buf, jump_step[1]);
		Flash_Write_Data_u8(application_start_address, buf, jump_step[1]);
		printf("HEX File loading done!\r\n");
		printf("Loading application...\r\n");
		//ardından applicationa geçiş yap
		typedef void (*pFunction)(void);
		uint32_t JumpAddress;
		JumpAddress = *(__IO uint32_t*) (application_start_address + 4);
		pFunction Jump_To_Application = (pFunction) JumpAddress;
		HAL_DeInit();
		SysTick->CTRL = 0;
		SysTick->LOAD = 0;
		SysTick->VAL  = 0;

		 /* Initialize user application's Stack Pointer */
		SCB->VTOR = application_start_address;
		 __set_MSP(*(__IO uint32_t*) application_start_address);
		 Jump_To_Application();
	}
	else
	{
		if(((*(uint32_t*)application_start_address) & 0xFFFFFFFF) == 0xFFFFFFFF)
		{
			printf("There is no application found\r\n");
		}
		else
		{
			printf("Application found. Loading application...\r\n");
			//eğer adreste application varsa geçiş yap
			typedef void (*pFunction)(void);
			uint32_t JumpAddress;
			JumpAddress = *(__IO uint32_t*) (application_start_address + 4);
			pFunction Jump_To_Application = (pFunction) JumpAddress;
			HAL_DeInit();
			SysTick->CTRL = 0;
			SysTick->LOAD = 0;
			SysTick->VAL  = 0;

			 /* Initialize user application's Stack Pointer */
			SCB->VTOR = application_start_address;
			 __set_MSP(*(__IO uint32_t*) application_start_address);
			 Jump_To_Application();
		}

	}
}
void JumpToBootLoader()
{
	Flash_Read_Data_u32(0x08040000,jump_step,sizeof(jump_step));
	if(jump_step[0] == 1)
	{
		typedef void (*pFunction)(void);
		uint32_t JumpAddress;
		JumpAddress = *(__IO uint32_t*) (boot_loader_address + 4);
		pFunction Jump_To_Application = (pFunction) JumpAddress;

		SysTick->CTRL = 0;
		SysTick->LOAD = 0;
		SysTick->VAL  = 0;

		 /* Initialize user application's Stack Pointer */
		SCB->VTOR = boot_loader_address;
		 __set_MSP(*(__IO uint32_t*) boot_loader_address);
		 Jump_To_Application();
	}
}

uint8_t Hexadecimal_To_Decimal(uint8_t hexa)
{
	uint8_t dec;
	if(hexa-48 <= 9 && hexa-48 >= 0)//48 0'in ascii si
	{
		dec = hexa-48;
	}
	else
	{
		dec = hexa-55; //65 A'nin asciisi 65-55 = 10
	}
	return dec;
}




