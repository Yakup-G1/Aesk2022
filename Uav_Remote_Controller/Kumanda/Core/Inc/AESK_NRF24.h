/*
Library:				NRF24L01/NRF24L01+
Modified by:			Yusuf Yıldız
Date Written:			11/03/2021
Last modified:		-/-
Description:			This is an STM32 device driver library for the NRF24L01 Nordic Radio transceiver, using STM HAL libraries

References:				This library was written based on the Arduino NRF24 Open-Source library by J. Coliz and the NRF24 datasheet
										- https://github.com/maniacbug/RF24
										- https://www.sparkfun.com/datasheets/Components/SMD/nRF24L01Pluss_Preliminary_Product_Specification_v1_0.pdf
*/
#ifndef AESK_NRF24_H_
#define AESK_NRF24_H_

#include "main.h"
#include "nRF24L01.h"
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "AESK_Data_Pack_lib.h"
//#include "AESK_GL.h"


typedef struct{
	uint8_t RxBuffer[255];
	uint8_t TxBuffer[255];
	uint16_t ReadByte;
	uint16_t WrittenByte;
	uint64_t RxpipeAddrs;
	uint64_t TxpipeAddrs;
	uint8_t Channel;
	uint8_t lastPackCount;
	uint8_t packCount;
	uint8_t packCounter;
	void (*onReceive)(uint8_t * pack, uint16_t len);

}AESK_NRF24_DATA;
AESK_NRF24_DATA aesk_nrf24_data;

//**** TypeDefs ****//
//1. Power Amplifier function, NRF24_setPALevel() 
typedef enum { 
	RF24_PA_m18dB = 0,
	RF24_PA_m12dB,
	RF24_PA_m6dB,
	RF24_PA_0dB,
	RF24_PA_ERROR 
}rf24_pa_dbm_e ;
//2. NRF24_setDataRate() input
typedef enum { 
	RF24_1MBPS = 0,
	RF24_2MBPS,
	RF24_250KBPS
}rf24_datarate_e;
//3. NRF24_setCRCLength() input
typedef enum { 
	RF24_CRC_DISABLED = 0,
	RF24_CRC_8,
	RF24_CRC_16
}rf24_crclength_e;
//4. Pipe address registers
static const uint8_t NRF24_ADDR_REGS[7] = {
		REG_RX_ADDR_P0,
		REG_RX_ADDR_P1,
		REG_RX_ADDR_P2,
		REG_RX_ADDR_P3,
		REG_RX_ADDR_P4,
		REG_RX_ADDR_P5,
		REG_TX_ADDR
};
//5. RX_PW_Px registers addresses
static const uint8_t RF24_RX_PW_PIPE[6] = {
		REG_RX_PW_P0, 
		REG_RX_PW_P1,
		REG_RX_PW_P2,
		REG_RX_PW_P3,
		REG_RX_PW_P4,
		REG_RX_PW_P5
};
//**** Functions prototypes ****//

void AESK_NRF24_Init(SPI_HandleTypeDef * hspi,GPIO_TypeDef * CSN_CE_Port, uint16_t CSN_Pin, uint16_t CE_Pin);

void AESK_NRF24_DATA_Init(uint8_t Channel, uint64_t RxpipeAddrs ,void (*OnReceive)(uint8_t * pack, uint16_t len));

//Microsecond delay function
void AESK_NRF24_DelayMicroSeconds(uint32_t uSec);

//1. Chip Select function
void AESK_NRF24_csn(int mode);
//2. Chip Enable
void AESK_NRF24_ce(int level);
//3. Read single byte from a register
uint8_t AESK_NRF24_read_register(uint8_t reg);
//4. Read multiple bytes register
void AESK_NRF24_read_registerN(uint8_t reg, uint8_t *buf, uint8_t len);
//5. Write single byte register
void AESK_NRF24_write_register(uint8_t reg, uint8_t value);
//6. Write multipl bytes register
void AESK_NRF24_write_registerN(uint8_t reg, const uint8_t* buf, uint8_t len);
//7. Write transmit payload
void AESK_NRF24_write_payload(const void* buf, uint8_t len);
//8. Read receive payload
void AESK_NRF24_read_payload(void* buf, uint8_t len);
//9. Flush Tx buffer
void AESK_NRF24_flush_tx(void);
//10. Flush Rx buffer
void AESK_NRF24_flush_rx(void);
//11. Get status register value
uint8_t AESK_NRF24_get_status(void);

//12. Begin function
void AESK_NRF24_begin(GPIO_TypeDef *nrf24PORT, uint16_t nrfCSN_Pin, uint16_t nrfCE_Pin, SPI_HandleTypeDef * nrfSPI);
//13. Listen on open pipes for reading (Must call NRF24_openReadingPipe() first)
void AESK_NRF24_startListening(void);
//14. Stop listening (essential before any write operation)
void AESK_NRF24_stopListening(void);

//15. Write(Transmit data), returns true if successfully sent
bool AESK_NRF24_write( const void* buf, uint8_t len );
//16. Check for available data to read
bool AESK_NRF24_available(void);
//17. Read received data
bool AESK_NRF24_read( void* buf, uint8_t len );
//18. Open Tx pipe for writing (Cannot perform this while Listening, has to call NRF24_stopListening)
void AESK_NRF24_openReadingPipe(uint64_t address);
void AESK_NRF24_openWritingPipe(uint64_t address);
void AESK_NRF24_SetPayloadSize();
//19. Open reading pipe
//void AESK_NRF24_openReadingPipe(uint8_t number, uint64_t address);
//20 set transmit retries (rf24_Retries_e) and delay
void AESK_NRF24_setRetries(uint8_t delay, uint8_t count);
//21. Set RF channel frequency
void AESK_NRF24_setChannel(uint8_t channel);
//22. Set payload size
void AESK_NRF24_setPayloadSize(uint8_t size);
//23. Get payload size
uint8_t AESK_NRF24_getPayloadSize(void);
//24. Get dynamic payload size, of latest packet received
uint8_t AESK_NRF24_getDynamicPayloadSize(void);
//25. Enable payload on Ackknowledge packet
void AESK_NRF24_enableAckPayload(void);
//26. Enable dynamic payloads
void AESK_NRF24_enableDynamicPayloads(void);
void AESK_NRF24_disableDynamicPayloads(void);
//27. Check if module is NRF24L01+ or normal module
bool AESK_NRF24_isNRF_Plus(void) ;
//28. Set Auto Ack for all
void AESK_NRF24_setAutoAck(bool enable);
//29. Set Auto Ack for certain pipe
void AESK_NRF24_setAutoAckPipe( uint8_t pipe, bool enable ) ;
//30. Set transmit power level
void AESK_NRF24_setPALevel( rf24_pa_dbm_e level ) ;
//31. Get transmit power level
rf24_pa_dbm_e AESK_NRF24_getPALevel( void ) ;
//32. Set data rate (250 Kbps, 1Mbps, 2Mbps)
bool AESK_NRF24_setDataRate(rf24_datarate_e speed);
//33. Get data rate
rf24_datarate_e AESK_NRF24_getDataRate( void );
//34. Set crc length (disable, 8-bits or 16-bits)
void AESK_NRF24_setCRCLength(rf24_crclength_e length);
//35. Get CRC length
rf24_crclength_e AESK_NRF24_getCRCLength(void);
//36. Disable CRC
void AESK_NRF24_disableCRC( void ) ;
//37. power up
void AESK_NRF24_powerUp(void) ;
//38. power down
void AESK_NRF24_powerDown(void);
//39. Check if data are available and on which pipe (Use this for multiple rx pipes)
bool AESK_NRF24_availablePipe(uint8_t* pipe_num);
//40. Start write (for IRQ mode)
void AESK_NRF24_startWrite( const void* buf, uint8_t len );
//41. Write acknowledge payload
void AESK_NRF24_writeAckPayload(uint8_t pipe, const void* buf, uint8_t len);
//42. Check if an Ack payload is available
bool AESK_NRF24_isAckPayloadAvailable(void);
//43. Check interrupt flags
void AESK_NRF24_whatHappened(bool *tx_ok,bool *tx_fail,bool *rx_ready);
//44. Test if there is a carrier on the previous listenning period (useful to check for intereference)
bool AESK_NRF24_testCarrier(void);
//45. Test if a signal carrier exists (=> -64dB), only for NRF24L01+
bool AESK_NRF24_testRPD(void) ;
//46. Reset Status
void AESK_NRF24_resetStatus(void);
//47. ACTIVATE cmd
void AESK_NRF24_ACTIVATE_cmd(void);
//48. Get AckPayload Size
uint8_t AESK_NRF24_GetAckPayloadSize(void);

void AESK_NRF24_Set_PipeAdress(uint64_t TxpipeAddrs);
bool AESK_NRF24_WritePack(uint8_t * pack, uint16_t len, uint64_t TxpipeAddrs);
void AESK_NRF24_ReadPack();
uint16_t aeskCRCCalculator(uint8_t * frame, size_t framesize);

#endif
