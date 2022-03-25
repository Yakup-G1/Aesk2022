/*
 * GPS_UBX.h
 *
 *  Created on: Feb 8, 2022
 *      Author: mert
 */

#ifndef GPS_UBX_H_
#define GPS_UBX_H_

#include "main.h"
#include "stdint.h"
#include "string.h"
//#include "AESK_UART_STM32.h"    		// GPS_UBX.c dosyasindaki aciklamayi okuyunuz.


#define USART_BUFFER_SIZE 		1024
#define BUFFER_SIZE  			1024
#define VALID_CONTROL			63    	// 0b00111111   GPS'ten tüm veriler alinmaya baslandiginin göstergesi.
										// Ancak veriler hala hassas degil. Bunun kontrolu icin ise uydu sayisina bakicaz.

typedef struct
{
	uint8_t usart_receive_buffer[USART_BUFFER_SIZE];
	uint16_t tail;
}USART_Buffer;


typedef enum
{
	YAKALA_u = 0,
	YAKALA_b,
	YAKALA_CLASS,
	YAKALA_ID,
	YAKALA_LENGTH_L,
	YAKALA_LENGTH_H,
	TOPLA_NAV_PVT_92,
	TOPLA_NAV_POSLLH_28,
//	TOPLA_NAV_HPPOSLLH_36,
//	TOPLA_NAV_VELNED_36,
}UBX_States;


typedef enum
{
	NAV_PVT_92,			//payload length 92 byte. NAV_PVT paketinin yapisi [ 0xB5, 0x62, 0x01, 0x07, 0x92, 0x00, Payload[92], CK_A, CK_B ] seklindendir.
	NAV_POSLLH_28,		//payload length 28 byte
	NAV_HPPOSLLH_36,	//payload length 36 byte
	NAV_VELNED_36,		//payload length 36 byte
}UBX_Types;


typedef struct
{
	uint32_t 	checksumError_u32;
	uint32_t 	validDataError_u32;
	uint32_t	trueData_u32;
}UBX_ErrorHandle;


// Rx NAV-PVT (ubx8)
typedef struct
{
	uint32_t	iTOW;			// < GPS Time of Week [ms]
	uint16_t	year; 			// < Year (UTC)
	uint8_t		month; 			// < Month, range 1..12 (UTC)
	uint8_t		day; 			// < Day of month, range 1..31 (UTC)
	uint8_t		hour; 			// < Hour of day, range 0..23 (UTC)
	uint8_t		min; 			// < Minute of hour, range 0..59 (UTC)
	uint8_t		sec;			// < Seconds of minute, range 0..60 (UTC)
	uint8_t		valid; 			// < Validity flags (see UBX_RX_NAV_PVT_VALID_...)
	uint32_t	tAcc; 			// < Time accuracy estimate (UTC) [ns]
	int32_t		nano;			// < Fraction of second (UTC) [-1e9...1e9 ns]
	uint8_t		fixType;		// < GNSSfix type: 0 = No fix, 1 = Dead Reckoning only, 2 = 2D fix, 3 = 3d-fix, 4 = GNSS + dead reckoning, 5 = time only fix
	uint8_t		flags, flags2;	// < Fix Status Flags (see UBX_RX_NAV_PVT_FLAGS_...)
	uint8_t		numSV;			// < Number of SVs used in Nav Solution
//	int32_t		lon;			// < Longitude [1e-7 deg]
//	int32_t		lat;			// < Latitude [1e-7 deg]
	float 		longitude;		// < Longitude (Float)
	float 		latitude;		// < Latitude (Float)
	int32_t		height;			// < Height above ellipsoid [mm]
	int32_t		hMSL;			// < Height above mean sea level [mm]
	uint32_t	hAcc;  			// < Horizontal accuracy estimate [mm]
	uint32_t	vAcc;  			// < Vertical accuracy estimate [mm]
	int32_t		velN;			// < NED north velocity [mm/s]
	int32_t		velE;			// < NED east velocity [mm/s]
	int32_t		velD;			// < NED down velocity [mm/s]
	int32_t		gSpeed;			// < Ground Speed (2-D) [mm/s]
//	int32_t		headMot;		// < Heading of motion (2-D) [1e-5 deg]
	float 		headingMotion;	// < Heading of motion (2-D) (Float)
	uint32_t	sAcc;			// < Speed accuracy estimate [mm/s]
//	uint32_t	headAcc;		// < Heading accuracy estimate (motion and vehicle) [1e-5 deg]
	float 		headingAccuracy;// < Heading accuracy estimate (motion and vehicle) (Float)
//	uint16_t	pDOP;			// < Position DOP [0.01]
	float 		positionDOP; 	// < Position DOP (Float)
	uint16_t	flags3;			// < Additional flags
	uint32_t	reserved1;		// < Reserved
//	int32_t		headVeh;		// < (ubx8+ only) Heading of vehicle (2-D) [1e-5 deg]
	float 		headingVeh; 	// < (ubx8+ only) Heading of vehicle (2-D) (Float)
	int16_t		magDec;			// < [1e-2 deg]
	uint16_t	magAcc;			// < [1e-2 deg]
} UBX_payload_NAV_PVT_t;


// Rx NAV-POSLLH
typedef struct {
	uint32_t	iTOW;			// < GPS Time of Week [ms]
	int32_t		lon;			// < Longitude [1e-7 deg]
	int32_t		lat;			// < Latitude [1e-7 deg]
	int32_t		height;			// < Height above ellipsoid [mm]
	int32_t		hMSL;			// < Height above mean sea level [mm]
	uint32_t	hAcc;  			// < Horizontal accuracy estimate [mm]
	uint32_t	vAcc;  			// < Vertical accuracy estimate [mm]
} UBX_payload_NAV_POSLLH_t;


// Rx NAV-VELNED
typedef struct {
	uint32_t	iTOW;		// < GPS Time of Week [ms]
	int32_t		velN;		// < North velocity component [cm/s]
	int32_t		velE;		// < East velocity component [cm/s]
	int32_t		velD;		// < Down velocity component [cm/s]
	uint32_t	speed;		// < Speed (3-D) [cm/s]
	uint32_t	gSpeed;		// < Ground speed (2-D) [cm/s]
	int32_t		heading;	// < Heading of motion 2-D [1e-5 deg]
	float 		heading_f;	// < Heading of motion 2-D (Float)
	uint32_t	sAcc;		// < Speed accuracy estimate [cm/s]
	uint32_t	cAcc;		// < Course / Heading accuracy estimate [1e-5 deg]
	float 		cAcc_f; 	// < Course / Heading accuracy estimate (Float)
} UBX_payload_NAV_VELNED_t;


typedef struct{
	uint8_t 				gpsDatasArray[BUFFER_SIZE];
	uint8_t 				gpsEfficiency_u8;
	UBX_States 				state;
	UBX_ErrorHandle 		gps_errorhandler;
	uint8_t					satelite_num_flag;
	UBX_payload_NAV_PVT_t	ubx_PVT;
}UBX_Handle;


void Uart_DMA_Receive_Start	(UART_HandleTypeDef *huart, USART_Buffer *usart_buffer);
int16_t read_DMA_Buffer	   	(UART_HandleTypeDef *huart, USART_Buffer *usart_buffer, uint8_t *temp_buf);
void NMEA2UBX_Config		(UART_HandleTypeDef *huart, USART_Buffer *USART_Buf);
void GPS_Data_Control		(UBX_Handle *gpsDatas, const uint8_t *datas, uint8_t read_byte);
void checksum_calc			(UBX_Handle *gpsDatas);
void UBX_gelen_checksum		(UBX_Handle *gpsDatas);
void GPS_Parser				(UBX_Handle *gpsDatas, UBX_Types gpsType);


#endif /* GPS_UBX_H_ */
