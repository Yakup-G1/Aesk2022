/*
 Library:					NRF24L01/NRF24L01+
 Modified by:				Yusuf Yıldız
 Date Written:			10/11/2018
 Last modified:		-/-
 Description:			This is an STM32 device driver library for the NRF24L01 Nordic Radio transceiver, using STM HAL libraries

 References:				This library was written based on the Arduino NRF24 Open-Source library by J. Coliz and the NRF24 datasheet
 - https://github.com/maniacbug/RF24
 - https://www.sparkfun.com/datasheets/Components/SMD/nRF24L01Pluss_Preliminary_Product_Specification_v1_0.pdf
*/

//List of header files
#include <AESK_NRF24.h>

//*** Variables declaration ***//
#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))
#define _BOOL(x) (((x)>0) ? 1:0)

//*** Library variables ***//
static uint64_t pipe0_reading_address;
static bool ack_payload_available; /**< Whether there is an ack payload waiting */
static uint8_t ack_payload_length; /**< Dynamic size of pending ack payload. */
static uint8_t payload_size; /**< Fixed size of payloads */
static bool dynamic_payloads_enabled; /**< Whether dynamic payloads are enabled. */
static bool p_variant; /* False for RF24L01 and true for RF24L01P */
static bool wide_band; /* 2Mbs data rate in use? */

//*** NRF24L01 pins and handles ***//
//CE and CSN pins
static GPIO_TypeDef *nrf24_PORT;
static uint16_t nrf24_CSN_PIN;
static uint16_t nrf24_CE_PIN;
//SPI handle
static SPI_HandleTypeDef * nrf24_hspi;
void AESK_NRF24_Init(SPI_HandleTypeDef * hspi,GPIO_TypeDef * CSN_CE_Port, uint16_t CSN_Pin, uint16_t CE_Pin)
{
	AESK_NRF24_begin(CSN_CE_Port, CSN_Pin, CE_Pin, hspi);
	AESK_NRF24_startListening();
	AESK_NRF24_SetPayloadSize();
	AESK_NRF24_openReadingPipe(aesk_nrf24_data.RxpipeAddrs);
	AESK_NRF24_openWritingPipe(aesk_nrf24_data.TxpipeAddrs);
	AESK_NRF24_setChannel(aesk_nrf24_data.Channel);
	AESK_NRF24_setAutoAck(false);
	AESK_NRF24_setPayloadSize(32);

}
void AESK_NRF24_DATA_Init(uint8_t Channel, uint64_t RxpipeAddrs, void (*OnReceive)(uint8_t * pack, uint16_t len))
{
	aesk_nrf24_data.ReadByte = 0;
	aesk_nrf24_data.WrittenByte = 0;
	aesk_nrf24_data.Channel = Channel;
	aesk_nrf24_data.RxpipeAddrs = RxpipeAddrs;
	aesk_nrf24_data.TxpipeAddrs = 0x1122112211;
	aesk_nrf24_data.lastPackCount = 0;
	aesk_nrf24_data.onReceive = OnReceive;
}
//Microsecond delay function
void AESK_NRF24_DelayMicroSeconds(uint32_t uSec)
{
	uint32_t uSecVar = uSec;
	uSecVar = uSecVar * ((SystemCoreClock / 1000000) / 3);
	while (uSecVar--);
}

//1. Chip Select function
void AESK_NRF24_csn(int state)
{
	if (state) HAL_GPIO_WritePin(nrf24_PORT, nrf24_CSN_PIN, GPIO_PIN_SET);
	else HAL_GPIO_WritePin(nrf24_PORT, nrf24_CSN_PIN, GPIO_PIN_RESET);
}
//2. Chip Enable
void AESK_NRF24_ce(int state)
{
	if (state) HAL_GPIO_WritePin(nrf24_PORT, nrf24_CE_PIN, GPIO_PIN_SET);
	else HAL_GPIO_WritePin(nrf24_PORT, nrf24_CE_PIN, GPIO_PIN_RESET);
}
//3. Read single byte from a register
uint8_t AESK_NRF24_read_register(uint8_t reg)
{
	uint8_t spiBuf[3];
	uint8_t retData;
	//Put CSN low
	AESK_NRF24_csn(0);
	//Transmit register address
	spiBuf[0] = reg & 0x1F;
	HAL_SPI_Transmit(nrf24_hspi, spiBuf, 1, 100);
	//Receive data
	HAL_SPI_Receive(nrf24_hspi, &spiBuf[1], 1, 100);
	retData = spiBuf[1];
	//Bring CSN high
	AESK_NRF24_csn(1);
	return retData;
}
//4. Read multiple bytes register
void AESK_NRF24_read_registerN(uint8_t reg, uint8_t *buf, uint8_t len)
{
	uint8_t spiBuf[3];
	//Put CSN low
	AESK_NRF24_csn(0);
	//Transmit register address
	spiBuf[0] = reg & 0x1F;
	//spiStatus = NRF24_SPI_Write(spiBuf, 1);
	HAL_SPI_Transmit(nrf24_hspi, spiBuf, 1, 100);
	//Receive data
	HAL_SPI_Receive(nrf24_hspi, buf, len, 100);
	//Bring CSN high
	AESK_NRF24_csn(1);
}
//5. Write single byte register
void AESK_NRF24_write_register(uint8_t reg, uint8_t value)
{
	uint8_t spiBuf[3];
	//Put CSN low
	AESK_NRF24_csn(0);
	//Transmit register address and data
	spiBuf[0] = reg | 0x20;
	spiBuf[1] = value;
	HAL_SPI_Transmit(nrf24_hspi, spiBuf, 2, 100);
	//Bring CSN high
	AESK_NRF24_csn(1);
}
//6. Write multipl bytes register
void AESK_NRF24_write_registerN(uint8_t reg, const uint8_t *buf, uint8_t len)
{
	uint8_t spiBuf[3];
	//Put CSN low
	AESK_NRF24_csn(0);
	//Transmit register address and data
	spiBuf[0] = reg | 0x20;
	HAL_SPI_Transmit(nrf24_hspi, spiBuf, 1, 100);
	HAL_SPI_Transmit(nrf24_hspi, (uint8_t*) buf, len, 100);
	//Bring CSN high
	AESK_NRF24_csn(1);
}
//7. Write transmit payload
void AESK_NRF24_write_payload(const void *buf, uint8_t len)
{
	uint8_t wrPayloadCmd;
	//Bring CSN low
	AESK_NRF24_csn(0);
	//Send Write Tx payload command followed by pbuf data
	wrPayloadCmd = CMD_W_TX_PAYLOAD;
	HAL_SPI_Transmit(nrf24_hspi, &wrPayloadCmd, 1, 100);
	HAL_SPI_Transmit(nrf24_hspi, (uint8_t*) buf, len, 100);
	//Bring CSN high
	AESK_NRF24_csn(1);
}
//8. Read receive payload
void AESK_NRF24_read_payload(void *buf, uint8_t len)
{
	uint8_t cmdRxBuf;
	//Get data length using payload size
	uint8_t data_len = MIN(len, AESK_NRF24_getPayloadSize());
	//Read data from Rx payload buffer
	AESK_NRF24_csn(0);
	cmdRxBuf = CMD_R_RX_PAYLOAD;
	HAL_SPI_Transmit(nrf24_hspi, &cmdRxBuf, 1, 100);
	HAL_SPI_Receive(nrf24_hspi, buf, data_len, 100);
	AESK_NRF24_csn(1);
}

//9. Flush Tx buffer
void AESK_NRF24_flush_tx(void)
{
	AESK_NRF24_write_register(CMD_FLUSH_TX, 0xFF);
}
//10. Flush Rx buffer
void AESK_NRF24_flush_rx(void)
{
	AESK_NRF24_write_register(CMD_FLUSH_RX, 0xFF);
}
//11. Get status register value
uint8_t AESK_NRF24_get_status(void)
{
	uint8_t statReg;
	statReg = AESK_NRF24_read_register(REG_STATUS);
	return statReg;
}

//12. Begin function
void AESK_NRF24_begin(GPIO_TypeDef *nrf24PORT, uint16_t nrfCSN_Pin, uint16_t nrfCE_Pin, SPI_HandleTypeDef * nrfSPI)
{
	nrf24_hspi = nrfSPI;
	//Copy Pins and Port variables
	nrf24_PORT = nrf24PORT;
	nrf24_CSN_PIN = nrfCSN_Pin;
	nrf24_CE_PIN = nrfCE_Pin;

	//Put pins to idle state
	AESK_NRF24_csn(1);
	AESK_NRF24_ce(0);
	//5 ms initial delay
	HAL_Delay(5);

	//**** Soft Reset Registers default values ****//
	AESK_NRF24_write_register(0x00, 0x08);
	AESK_NRF24_write_register(0x01, 0x3f);
	AESK_NRF24_write_register(0x02, 0x03);
	AESK_NRF24_write_register(0x03, 0x03);
	AESK_NRF24_write_register(0x04, 0x03);
	AESK_NRF24_write_register(0x05, 0x02);
	AESK_NRF24_write_register(0x06, 0x0f);
	AESK_NRF24_write_register(0x07, 0x0e);
	AESK_NRF24_write_register(0x08, 0x00);
	AESK_NRF24_write_register(0x09, 0x00);
	uint8_t pipeAddrVar[6];
	pipeAddrVar[4] = 0xE7;
	pipeAddrVar[3] = 0xE7;
	pipeAddrVar[2] = 0xE7;
	pipeAddrVar[1] = 0xE7;
	pipeAddrVar[0] = 0xE7;
	AESK_NRF24_write_registerN(0x0A, pipeAddrVar, 5);
	pipeAddrVar[4] = 0xC2;
	pipeAddrVar[3] = 0xC2;
	pipeAddrVar[2] = 0xC2;
	pipeAddrVar[1] = 0xC2;
	pipeAddrVar[0] = 0xC2;
	AESK_NRF24_write_registerN(0x0B, pipeAddrVar, 5);
	AESK_NRF24_write_register(0x0C, 0xC3);
	AESK_NRF24_write_register(0x0D, 0xC4);
	AESK_NRF24_write_register(0x0E, 0xC5);
	AESK_NRF24_write_register(0x0F, 0xC6);
	pipeAddrVar[4] = 0xE7;
	pipeAddrVar[3] = 0xE7;
	pipeAddrVar[2] = 0xE7;
	pipeAddrVar[1] = 0xE7;
	pipeAddrVar[0] = 0xE7;
	AESK_NRF24_write_registerN(0x10, pipeAddrVar, 5);
	AESK_NRF24_write_register(0x11, 0);
	AESK_NRF24_write_register(0x12, 0);
	AESK_NRF24_write_register(0x13, 0);
	AESK_NRF24_write_register(0x14, 0);
	AESK_NRF24_write_register(0x15, 0);
	AESK_NRF24_write_register(0x16, 0);

	AESK_NRF24_ACTIVATE_cmd();
	AESK_NRF24_write_register(0x1c, 0);
	AESK_NRF24_write_register(0x1d, 0);
	//Initialise retries 15 and delay 1250 usec
	AESK_NRF24_setRetries(15, 15);
	//Initialise PA level to max (0dB)
	AESK_NRF24_setPALevel(RF24_PA_0dB);
	//Initialise data rate to 1Mbps
	AESK_NRF24_setDataRate(RF24_250KBPS);
	//Initalise CRC length to 16-bit (2 bytes)
	AESK_NRF24_setCRCLength(RF24_CRC_16);
	//Disable dynamic payload
	AESK_NRF24_disableDynamicPayloads();
	//Set payload size
	AESK_NRF24_setPayloadSize(32);

	//Reset status register
	AESK_NRF24_resetStatus();
	//Initialise channel to 76
	AESK_NRF24_setChannel(76);
	//Flush buffers
	AESK_NRF24_flush_tx();
	AESK_NRF24_flush_rx();

	AESK_NRF24_powerDown();

}
//13. Listen on open pipes for reading (Must call AESK_NRF24_openReadingPipe() first)
void AESK_NRF24_startListening(void)
{
	//Power up and set to RX mode
	AESK_NRF24_write_register(REG_CONFIG, AESK_NRF24_read_register(REG_CONFIG) | (1UL << 1) | (1UL << 0));
	//Restore pipe 0 address if exists
	if (pipe0_reading_address) AESK_NRF24_write_registerN(REG_RX_ADDR_P0, (uint8_t*) (&pipe0_reading_address), 5);

	//Flush buffers
	AESK_NRF24_flush_tx();
	AESK_NRF24_flush_rx();
	//Set CE HIGH to start listenning
	AESK_NRF24_ce(1);
	//Wait for 130 uSec for the radio to come on
	AESK_NRF24_DelayMicroSeconds(150);
}
//14. Stop listening (essential before any write operation)
void AESK_NRF24_stopListening(void)
{
	AESK_NRF24_ce(0);
	AESK_NRF24_flush_tx();
	AESK_NRF24_flush_rx();
}
//15. Write(Transmit data), returns true if successfully sent
bool AESK_NRF24_write(const void *buf, uint8_t len)
{
	bool retStatus;
	//Start writing
	AESK_NRF24_resetStatus();
	AESK_NRF24_startWrite(buf, len);

	//Data monitor
	uint8_t observe_tx;
	uint8_t status;
	uint32_t sent_at = HAL_GetTick();
	const uint32_t timeout = 10; //ms to wait for timeout
	do {
		AESK_NRF24_read_registerN(REG_OBSERVE_TX, &observe_tx, 1);
		//Get status register
		status = AESK_NRF24_get_status();
	} while (!(status & ( _BV(BIT_TX_DS) | _BV(BIT_MAX_RT))) && (HAL_GetTick() - sent_at < timeout));

	bool tx_ok, tx_fail;
	AESK_NRF24_whatHappened(&tx_ok, &tx_fail, &ack_payload_available);
	retStatus = tx_ok;
	if (ack_payload_available)
	{
		ack_payload_length = AESK_NRF24_getDynamicPayloadSize();
	}
	//Power down
	AESK_NRF24_available();
	AESK_NRF24_flush_tx();

	return retStatus;
}
//16. Check for available data to read
bool AESK_NRF24_available(void)
{
	return AESK_NRF24_availablePipe(NULL);
}
//17. Read received data
bool AESK_NRF24_read(void *buf, uint8_t len)
{
	AESK_NRF24_read_payload(buf, len);
	uint8_t rxStatus = AESK_NRF24_read_register(REG_FIFO_STATUS) & _BV(BIT_RX_EMPTY);
	AESK_NRF24_flush_rx();
	AESK_NRF24_getDynamicPayloadSize();
	AESK_NRF24_resetStatus();
	return rxStatus;
}
//18. Open Tx pipe for writing (Cannot perform this while Listenning, has to call AESK_NRF24_stopListening)
void AESK_NRF24_openReadingPipe(uint64_t address)
{
	AESK_NRF24_write_registerN(REG_RX_ADDR_P0, (uint8_t*) (&address), 5);
}
void AESK_NRF24_openWritingPipe(uint64_t address)
{
	AESK_NRF24_write_registerN(REG_TX_ADDR, (uint8_t*) (&address), 5);
}
void AESK_NRF24_SetPayloadSize()
{
	const uint8_t max_payload_size = 32;
	AESK_NRF24_write_register(REG_RX_PW_P0, MIN(payload_size, max_payload_size));
}
//19. Open reading pipe
//void AESK_NRF24_openReadingPipe(uint8_t number, uint64_t address)
//{
//	if (number == 0) pipe0_reading_address = address;
//
//	if (number <= 6)
//	{
//		if (number < 2)
//		{
//			//Address width is 5 bytes
//			AESK_NRF24_write_registerN(NRF24_ADDR_REGS[number], (uint8_t*) (&address), 5);
//		}
//		else
//		{
//			AESK_NRF24_write_registerN(NRF24_ADDR_REGS[number], (uint8_t*) (&address), 1);
//		}
//		//Write payload size
//		AESK_NRF24_write_register(RF24_RX_PW_PIPE[number], payload_size);
//		//Enable pipe
//		AESK_NRF24_write_register(REG_EN_RXADDR, AESK_NRF24_read_register(REG_EN_RXADDR) | _BV(number));
//	}
//
//}
//20 set transmit retries (rf24_Retries_e) and delay
void AESK_NRF24_setRetries(uint8_t delay, uint8_t count)
{
	AESK_NRF24_write_register(REG_SETUP_RETR, (delay & 0xf) << BIT_ARD | (count & 0xf) << BIT_ARC);
}

//21. Set RF channel frequency
void AESK_NRF24_setChannel(uint8_t channel)
{
	const uint8_t max_channel = 127;
	AESK_NRF24_write_register(REG_RF_CH, MIN(channel, max_channel));
}
//22. Set payload size
void AESK_NRF24_setPayloadSize(uint8_t size)
{
	const uint8_t max_payload_size = 32;
	payload_size = MIN(size, max_payload_size);
}
//23. Get payload size
uint8_t AESK_NRF24_getPayloadSize(void)
{
	return payload_size;
}
//24. Get dynamic payload size, of latest packet received
uint8_t AESK_NRF24_getDynamicPayloadSize(void)
{
	return AESK_NRF24_read_register(CMD_R_RX_PL_WID);
}
//25. Enable payload on Ackknowledge packet
void AESK_NRF24_enableAckPayload(void)
{
	//Need to enable dynamic payload and Ack payload together
	AESK_NRF24_write_register(REG_FEATURE,
	AESK_NRF24_read_register( REG_FEATURE) | _BV(BIT_EN_ACK_PAY) | _BV(BIT_EN_DPL));
	if (!AESK_NRF24_read_register(REG_FEATURE))
	{
		AESK_NRF24_ACTIVATE_cmd();
		AESK_NRF24_write_register(REG_FEATURE,
		AESK_NRF24_read_register( REG_FEATURE) | _BV(BIT_EN_ACK_PAY) | _BV(BIT_EN_DPL));
	}
	// Enable dynamic payload on pipes 0 & 1
	AESK_NRF24_write_register(REG_DYNPD,
	AESK_NRF24_read_register(REG_DYNPD) | _BV(BIT_DPL_P1) | _BV(BIT_DPL_P0));
}
//26. Enable dynamic payloads
void AESK_NRF24_enableDynamicPayloads(void)
{
	//Enable dynamic payload through FEATURE register
	AESK_NRF24_write_register(REG_FEATURE,
	AESK_NRF24_read_register(REG_FEATURE) | _BV(BIT_EN_DPL));
	if (!AESK_NRF24_read_register(REG_FEATURE))
	{
		AESK_NRF24_ACTIVATE_cmd();
		AESK_NRF24_write_register(REG_FEATURE,
		AESK_NRF24_read_register(REG_FEATURE) | _BV(BIT_EN_DPL));
	}
	//Enable Dynamic payload on all pipes
	AESK_NRF24_write_register(REG_DYNPD,
	AESK_NRF24_read_register(REG_DYNPD) | _BV(BIT_DPL_P5) | _BV(BIT_DPL_P4) | _BV(BIT_DPL_P3) | _BV(BIT_DPL_P2) | _BV(BIT_DPL_P1) | _BV(BIT_DPL_P0));
	dynamic_payloads_enabled = true;

}
void AESK_NRF24_disableDynamicPayloads(void)
{
	AESK_NRF24_write_register(REG_FEATURE, AESK_NRF24_read_register(REG_FEATURE) & ~(_BV(BIT_EN_DPL)));
	//Disable for all pipes 
	AESK_NRF24_write_register(REG_DYNPD, 0);
	dynamic_payloads_enabled = false;
}
//27. Check if module is NRF24L01+ or normal module
bool AESK_NRF24_isNRF_Plus(void)
{
	return p_variant;
}
//28. Set Auto Ack for all
void AESK_NRF24_setAutoAck(bool enable)
{
	if (enable) AESK_NRF24_write_register(REG_EN_AA, 0x3F);
	else 		AESK_NRF24_write_register(REG_EN_AA, 0x00);
}
//29. Set Auto Ack for certain pipe
void AESK_NRF24_setAutoAckPipe(uint8_t pipe, bool enable)
{
	if (pipe <= 6) {
		uint8_t en_aa = AESK_NRF24_read_register( REG_EN_AA);

		if (enable) en_aa |= _BV(pipe);
		else 		en_aa &= ~_BV(pipe);

		AESK_NRF24_write_register( REG_EN_AA, en_aa);
	}
}
//30. Set transmit power level
void AESK_NRF24_setPALevel(rf24_pa_dbm_e level)
{
	uint8_t setup = AESK_NRF24_read_register(REG_RF_SETUP);
	setup &= ~(_BV(RF_PWR_LOW) | _BV(RF_PWR_HIGH));

	// switch uses RAM (evil!)
	if (level == RF24_PA_0dB) 		 setup |= (_BV(RF_PWR_LOW) | _BV(RF_PWR_HIGH));
	else if (level == RF24_PA_m6dB)  setup |= _BV(RF_PWR_HIGH);
	else if (level == RF24_PA_m12dB) setup |= _BV(RF_PWR_LOW);
	else if (level == RF24_PA_ERROR) setup |= (_BV(RF_PWR_LOW) | _BV(RF_PWR_HIGH));


	AESK_NRF24_write_register( REG_RF_SETUP, setup);
}
//31. Get transmit power level
rf24_pa_dbm_e AESK_NRF24_getPALevel(void)
{
	rf24_pa_dbm_e result = RF24_PA_ERROR;
	uint8_t power = AESK_NRF24_read_register(REG_RF_SETUP) & (_BV(RF_PWR_LOW) | _BV(RF_PWR_HIGH));

	// switch uses RAM (evil!)
	if (power == (_BV(RF_PWR_LOW) | _BV(RF_PWR_HIGH))) result = RF24_PA_0dB;
	else if (power == _BV(RF_PWR_HIGH)) 			   result = RF24_PA_m6dB;
	else if (power == _BV(RF_PWR_LOW)) 				   result = RF24_PA_m12dB;
	else 											   result = RF24_PA_m18dB;

	return result;
}
//32. Set data rate (250 Kbps, 1Mbps, 2Mbps)
bool AESK_NRF24_setDataRate(rf24_datarate_e speed)
{
	bool result = false;
	uint8_t setup = AESK_NRF24_read_register(REG_RF_SETUP);

	// HIGH and LOW '00' is 1Mbs - our default
	wide_band = false;
	setup &= ~(_BV(RF_DR_LOW) | _BV(RF_DR_HIGH));
	if (speed == RF24_250KBPS)
	{
		// Must set the RF_DR_LOW to 1; RF_DR_HIGH (used to be RF_DR) is already 0
		// Making it '10'.
		wide_band = false;
		setup |= _BV(RF_DR_LOW);
	}
	else
	{
		// Set 2Mbs, RF_DR (RF_DR_HIGH) is set 1
		// Making it '01'
		if (speed == RF24_2MBPS)
		{
			wide_band = true;
			setup |= _BV(RF_DR_HIGH);
		}
		else
		{
			// 1Mbs
			wide_band = false;
		}
	}
	AESK_NRF24_write_register(REG_RF_SETUP, setup);

	// Verify our result
	if (AESK_NRF24_read_register(REG_RF_SETUP) == setup) result = true;
	else wide_band = false;
	return result;
}
//33. Get data rate
rf24_datarate_e AESK_NRF24_getDataRate(void)
{
	rf24_datarate_e result;
	uint8_t dr = AESK_NRF24_read_register(REG_RF_SETUP) & (_BV(RF_DR_LOW) | _BV(RF_DR_HIGH));
	// switch uses RAM (evil!)

	// Order matters in our case below
	if (dr == _BV(RF_DR_LOW)) 		result = RF24_250KBPS;
	else if (dr == _BV(RF_DR_HIGH)) result = RF24_2MBPS;
	else 							result = RF24_1MBPS;

	return result;
}
//34. Set crc length (disable, 8-bits or 16-bits)
void AESK_NRF24_setCRCLength(rf24_crclength_e length)
{
	uint8_t config = AESK_NRF24_read_register(REG_CONFIG) & ~( _BV(BIT_CRCO) | _BV(BIT_EN_CRC));

	// switch uses RAM
	if (length == RF24_CRC_DISABLED)
	{
		// Do nothing, we turned it off above.
	} else if (length == RF24_CRC_8)
	{
		config |= _BV(BIT_EN_CRC);
	} else
	{
		config |= _BV(BIT_EN_CRC);
		config |= _BV(BIT_CRCO);
	}
	AESK_NRF24_write_register( REG_CONFIG, config);
}
//35. Get CRC length
rf24_crclength_e AESK_NRF24_getCRCLength(void)
{
	rf24_crclength_e result = RF24_CRC_DISABLED;
	uint8_t config = AESK_NRF24_read_register(REG_CONFIG) & ( _BV(BIT_CRCO) | _BV(BIT_EN_CRC));

	if (config & _BV(BIT_EN_CRC))
	{
		if (config & _BV(BIT_CRCO)) result = RF24_CRC_16;
		else result = RF24_CRC_8;
	}

	return result;
}
//36. Disable CRC
void AESK_NRF24_disableCRC(void)
{
	uint8_t disable = AESK_NRF24_read_register(REG_CONFIG) & ~_BV(BIT_EN_CRC);
	AESK_NRF24_write_register( REG_CONFIG, disable);
}
//37. power up
void AESK_NRF24_powerUp(void)
{
	AESK_NRF24_write_register(REG_CONFIG, AESK_NRF24_read_register(REG_CONFIG) | _BV(BIT_PWR_UP));
}
//38. power down
void AESK_NRF24_powerDown(void)
{
	AESK_NRF24_write_register(REG_CONFIG, AESK_NRF24_read_register(REG_CONFIG) & ~_BV(BIT_PWR_UP));
}
//39. Check if data are available and on which pipe (Use this for multiple rx pipes)
bool AESK_NRF24_availablePipe(uint8_t *pipe_num)
{
	uint8_t status = AESK_NRF24_get_status();

	bool result = (status & _BV(BIT_RX_DR));

	if (result)
	{
		// If the caller wants the pipe number, include that
		if (pipe_num) *pipe_num = (status >> BIT_RX_P_NO) & 0x7;
		// Clear the status bit
		AESK_NRF24_write_register(REG_STATUS, _BV(BIT_RX_DR));

		// Handle ack payload receipt
		if (status & _BV(BIT_TX_DS))
		{
			AESK_NRF24_write_register(REG_STATUS, _BV(BIT_TX_DS));
		}
	}
	return result;
}
//40. Start write (for IRQ mode)
void AESK_NRF24_startWrite(const void *buf, uint8_t len)
{
	// Transmitter power-up
	AESK_NRF24_ce(0);
	AESK_NRF24_write_register(REG_CONFIG, (AESK_NRF24_read_register(REG_CONFIG) | _BV(BIT_PWR_UP)) & ~_BV(BIT_PRIM_RX));
	AESK_NRF24_ce(1);
	AESK_NRF24_DelayMicroSeconds(150);

	// Send the payload
	AESK_NRF24_write_payload(buf, len);

	// Enable Tx for 15usec
	AESK_NRF24_ce(1);
	AESK_NRF24_DelayMicroSeconds(15);
	AESK_NRF24_ce(0);
}
//41. Write acknowledge payload
void AESK_NRF24_writeAckPayload(uint8_t pipe, const void *buf, uint8_t len)
{
	const uint8_t *current = (uint8_t*) buf;
	const uint8_t max_payload_size = 32;
	uint8_t data_len = MIN(len, max_payload_size);
	AESK_NRF24_csn(0);
	AESK_NRF24_write_registerN(CMD_W_ACK_PAYLOAD | (pipe & 0x7), current, data_len);
	AESK_NRF24_csn(1);
}
//42. Check if an Ack payload is available
bool AESK_NRF24_isAckPayloadAvailable(void)
{
	bool result = ack_payload_available;
	ack_payload_available = false;
	return result;
}
//43. Check interrupt flags
void AESK_NRF24_whatHappened(bool *tx_ok, bool *tx_fail, bool *rx_ready)
{
	uint8_t status = AESK_NRF24_get_status();
	*tx_ok = 0;
	AESK_NRF24_write_register(REG_STATUS, _BV(BIT_RX_DR) | _BV(BIT_TX_DS) | _BV(BIT_MAX_RT));
	// Report to the user what happened
	*tx_ok = status & _BV(BIT_TX_DS);
	*tx_fail = status & _BV(BIT_MAX_RT);
	*rx_ready = status & _BV(BIT_RX_DR);
}
//44. Test if there is a carrier on the previous listenning period (useful to check for intereference)
bool AESK_NRF24_testCarrier(void)
{
	return AESK_NRF24_read_register(REG_CD) & 1;
}
//45. Test if a signal carrier exists (=> -64dB), only for NRF24L01+
bool AESK_NRF24_testRPD(void)
{
	return AESK_NRF24_read_register(REG_RPD) & 1;
}

//46. Reset Status
void AESK_NRF24_resetStatus(void)
{
	AESK_NRF24_write_register(REG_STATUS, _BV(BIT_RX_DR) | _BV(BIT_TX_DS) | _BV(BIT_MAX_RT));
}

//47. ACTIVATE cmd
void AESK_NRF24_ACTIVATE_cmd(void)
{
	uint8_t cmdRxBuf[2];
	//Read data from Rx payload buffer
	AESK_NRF24_csn(0);
	cmdRxBuf[0] = CMD_ACTIVATE;
	cmdRxBuf[1] = 0x73;
	HAL_SPI_Transmit(nrf24_hspi, cmdRxBuf, 2, 100);
	AESK_NRF24_csn(1);
}
//48. Get AckPayload Size
uint8_t NRF24_GetAckPayloadSize(void)
{
	return ack_payload_length;
}

void AESK_NRF24_Set_PipeAdress(uint64_t TxpipeAddrs)
{
	aesk_nrf24_data.TxpipeAddrs = TxpipeAddrs;
	AESK_NRF24_openWritingPipe(aesk_nrf24_data.TxpipeAddrs);
}

void AESK_NRF24_ReadPack()
{

	if(AESK_NRF24_available())
	{
		uint8_t tempBuf[32];
		int i;

		AESK_NRF24_read(tempBuf, payload_size);
		for (i = 0; i < payload_size-1; i++)
		{
			aesk_nrf24_data.RxBuffer[aesk_nrf24_data.ReadByte++] = tempBuf[i];
		}
		aesk_nrf24_data.packCount = tempBuf[i];
		if((aesk_nrf24_data.packCount - aesk_nrf24_data.lastPackCount == 1))
		{
			aesk_nrf24_data.lastPackCount = aesk_nrf24_data.packCount;
		}
		else
		{
			aesk_nrf24_data.ReadByte = 0;
			aesk_nrf24_data.lastPackCount = 0;
		}
		if(aesk_nrf24_data.ReadByte >= aesk_nrf24_data.RxBuffer[1])
		{
			aesk_nrf24_data.ReadByte = 0;
			aesk_nrf24_data.lastPackCount = 0;

			aesk_nrf24_data.onReceive(aesk_nrf24_data.RxBuffer, aesk_nrf24_data.RxBuffer[1]);
		}
	}
//	else
//	{
//		CDC_Transmit_FS(aesk_nrf24_data.ErrorBuffer, 2);
//	}
}
bool AESK_NRF24_WritePack(uint8_t * pack, uint16_t len, uint64_t TxpipeAddrs)
{
	AESK_NRF24_stopListening();

	AESK_NRF24_Set_PipeAdress(TxpipeAddrs);

	bool status;
	int i;
	aesk_nrf24_data.packCounter = 1;

	while(aesk_nrf24_data.WrittenByte < len)
	{
		uint8_t tempBuf[32] = {0};
		for (i = 0; i < payload_size-1; i++)
		{
			tempBuf[i] = pack[aesk_nrf24_data.WrittenByte++];
		}
		tempBuf[i] = aesk_nrf24_data.packCounter++;
		status = AESK_NRF24_write(tempBuf, payload_size);
	}

	if(status)
		HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);

	aesk_nrf24_data.WrittenByte = 0;

	AESK_NRF24_startListening();
	return status;
}
