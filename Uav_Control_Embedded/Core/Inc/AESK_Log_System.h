/*
 * AESK_Log_System.h
 *
 *  Created on: 26 Şub 2021
 *      Author: Yusuf
 *      Contact: ykemalpalaci@gmail.com
 */

/*
 *
 * Bu kütüphane, log işlemleri için 2 seçenek sunar.
 * Bu seçenekler aşağıda prototipleri verilen LogAsString ve LogAsBuffer
 * fonksiyonlarıdır. Açıklamaları üstlerinde yapılmıştır.
 *
 */

#ifndef INC_AESK_LOG_SYSTEM_H_
#define INC_AESK_LOG_SYSTEM_H_

#include "stdint.h"
#include "string.h"
#include "ff.h"
#include "fatfs.h"
#include "stdarg.h"
#include "GPS_UBX.h"


void vars_to_str(char *buffer, const char *format, ...);



/*
 * RTC değişkenleri, sadece bu blokta ve read only olarak kullanılacağı
 * için tanımlamalar burada yapılmıştır.
 */
//RTC_TimeTypeDef sTime;
//RTC_DateTypeDef sDate;
//RTC_HandleTypeDef hrtc;

/*
 * SD kart okunduğunda sonraki duruma geçilir.
 */
typedef enum
{
	NO_SD_Card_Detect = 0,
	SD_Card_Detect = 1,
}SD_Card_States;

typedef struct
{
	uint8_t transmitBuf[500]; 	//SD karta kaydedilecek verileri taşır.
	char path[200];				//SD kart verilerinin kaydedileceği yol. Yol verilmezse dosya ismi.
	uint8_t state;				//SD kart durumu enum'u için
	char total_log[400];		//İşlenmiş log verilerini taşıyan byte
	//uint32_t logger_u32;
	//uint32_t bytes_u32;
	uint32_t errorcounter_u32;	//FATFS fonksiyonlarının hataya düşme sayısını tutar.
	FRESULT result;				//Debug aşamasında kullanılabilecek FRESULT değişkeni
	FRESULT result_open;		//Dosya açma fonksiyonunun sonucunu taşıyan FRESULT değişkeni
	FRESULT result_write;		//Yazma fonksiyonunun sonucunu taşıyan FRESULT değişkeni
	FRESULT result_sync;		//Sync fonksiyonunun sonucunu taşıyan FRESULT değişkeni
	FRESULT result_close;		//Dosya kapatma fonksiyonunun sonucunu taşıyan FRESULT değişkeni
	unsigned int writtenbyte;	//Yazılan byte sayısı
	FATFS myFATAFS;				//f_mount fonksiyonunda kullanılan FATFS değişkeni
	FIL myFile;					//FATFS fonksiyonlarında kullanılan FIL değişkeni, C'deki FILE değişkeninin alternatifi.
}Sd_Card_Data;

/*
 * LogStart fonksiyonu, SD kartı yazılımsal olarak takar ve kaydı başlatır.
 * .txt uzantılı dosyanın ilk satırına verilerin başlığını ekler.
 * Başlık metni .c dosyasının başında tanımlanmıştır.
 */
void LogStart(Sd_Card_Data* sdcard_data);

/*
 * LogDataInit fonksiyonu, kaydı alınacak verilerin bulunduğu struct'taki
 * değerleri 0 ile ilklendirir. Eğer veriler ilklendirilmeden kayıt
 * alınmaya çalışılsaydı CreateLogBuffer fonksiyonuna gelen lyradata ve
 * gpsdata yapılarındaki değişkenler, "NULL" değerinde olacağı için bu fonksiyon
 * LogAsBuffer fonksiyonuna NULL değerlerine sahip bir transmit buffer
 * gönderecek ve bu nedenle LogAsBuffer fonksiyonu hiçbir değer kaydetmeyecekti.
 */
void LogDataInit();
void LogAsString( Sd_Card_Data *sd_card_data, UBX_Handle *gpsDatas);

/*
 * LogAsBuffer fonksiyonu, verileri CAN veya RS485 hattından geldiği gibi bir byte
 * dizisi olarak kaydeder. Bu fonksiyon ile oluşturulan kaydı açabilmek için
 * AESK Telemetry 2021 uygulaması gerekmektedir. Bu fonksiyonu x periyotlu bir
 * taskta çağırıyorsanız en az 2x periyotlu başka bir taskta LogSync fonksiyonunu
 * çağırın.
 *
 * Üzgünüm. Fonksiyon çalışmadı. Bakmaya vaktimiz olmadı. Umarım bir gün çalışır.
 */
//void LogAsBuffer(LyraData lyradata, GPS_Handle gps_data, Sd_Card_Data* sd_card_data);

//Yorum yazacağız vakit olursa.
//void LogAsString(LyraData lyradata, GPS_Handle gps_data, Sd_Card_Data *sd_card_data);


#endif /* INC_AESK_LOG_SYSTEM_H_ */
