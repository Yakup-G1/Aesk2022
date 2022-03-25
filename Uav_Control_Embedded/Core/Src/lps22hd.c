#include "main.h"
#include "math.h"
#include "lps22hd.h"
#include "Kumanda.h"

int counter=0;
uint8_t lps22hd_flag=1;
int Counter2,k;

void BarometerWrite(uint8_t wRegister,uint8_t Value)//barometre adreslerine değer yazma fonksiyonu
{
	uint8_t data[2];
	data[0]         = wRegister;
	data[1]         = Value;
	HAL_I2C_Master_Transmit(&hi2c1,SLAVE_ADDR_WRITE, data, 2, 10);

}
void BarometerReadXL(uint8_t rRegister,uint8_t NumberOfBytes)//barometre adresindeki değer okuman fonksiyonu
{
	HAL_I2C_Mem_Read(&hi2c1, SLAVE_ADDR_READ, rRegister, 1 , Barometer_DataXL, NumberOfBytes, 10);

}
void BarometerReadL(uint8_t rRegister,uint8_t NumberOfBytes)//barometre adresindeki değer okuman fonksiyonu
{
	HAL_I2C_Mem_Read(&hi2c1, SLAVE_ADDR_READ, rRegister, 1 , Barometer_DataL, NumberOfBytes, 10);

}
void BarometerReadH(uint8_t rRegister,uint8_t NumberOfBytes)//barometre adresindeki değer okuman fonksiyonu
{
	HAL_I2C_Mem_Read(&hi2c1, SLAVE_ADDR_READ, rRegister, 1 , Barometer_DataH, NumberOfBytes, 10);

}
void BarometerInit()//barometre başlatma fonksiyonu
{

	BarometerWrite(CTRL_REG1,0b01010000);
	BarometerWrite(CTRL_REG2,0x00);
}
void BarometerReadValues()//1ms flagin içinde yapma// barometre bütün değerlerin okunup birlerştirilmesi ve
{

	  BarometerReadXL(PRESS_OUT_XL, 1);
	  BarometerReadL(PRESS_OUT_L, 1);
	  BarometerReadH(PRESS_OUT_H, 1);
      k++;
      if(k==20)
      {
    	  actual_Pressure_fast=Barometer_Pressure_Filtered/20;
    	  Barometer_Pressure_Filtered = 0;
    	  k=0;
      }
	  Barometer_Pressure = Barometer_DataXL[0]  + (Barometer_DataL[0]<<8) + (Barometer_DataH[0]<<16);
      Barometer_Pressure=Barometer_Pressure/4096;
      Barometer_Pressure_Filtered +=  Barometer_Pressure;
      actual_Pressure_slow = actual_Pressure_slow * (float)0.93 + actual_Pressure_fast * (float)0.07;
      actual_Pressure_diff = actual_Pressure_slow - actual_Pressure_fast;
      if (actual_Pressure_diff > 8)actual_Pressure_diff = 8;                                                    //If the difference is larger then 8 limit the difference to 8.
          if (actual_Pressure_diff < -8)actual_Pressure_diff = -8;                                                  //If the difference is smaller then -8 limit the difference to -8.
          //If the difference is larger then 1 or smaller then -1 the slow average is adjuste based on the error between the fast and slow average.
          if (actual_Pressure_diff > 1 || actual_Pressure_diff < -1)actual_Pressure_slow -= actual_Pressure_diff / 6.0;
          actual_Pressure = actual_Pressure_slow;


  	  //AESK_Median_Filter(Barometer_Pressure,&Barometer_Pressure_Filtered, 10);

  	 /* Barometer_Altitude=44300*(1.0-pow(Barometer_Pressure/First_Barometer_Pressure,0.1903));
  	  y_barometer=Barometer_Altitude*0.01+last_barometer_value*0.09;
  	 AESK_Median_Filter(Barometer_Altitude,&Barometer_Pressure_Filtered, 30);
  	  last_barometer_value=y_barometer;*/

}
//void BarometerAltitude()//1msflag içinde yapma
//{
//counter++;
//if(counter==30)
//{//zero point eklenecek
//    First_Barometer_DataXL[0]= Barometer_DataXL[0];
//	First_Barometer_DataL[0]= Barometer_DataL[0];
//	First_Barometer_DataH[0]= Barometer_DataH[0];
//	First_Barometer_Pressure= First_Barometer_DataXL[0]  + (First_Barometer_DataL[0]<<8) + (First_Barometer_DataH[0]<<16);
//	First_Barometer_Pressure=First_Barometer_Pressure/4096;
//}
//}

void BarometerAltitude()//1msflag içinde yapma
{
	// barometre için yapılacaklar 1000  sayısını biraz düşürmeyi dene öncelikle
	//daha sonra hesaplanan Barometer_Altitude degerini toplayıp 20 ye böl bu senin hızlı degiştirme degerin
	//daha sonra bir tanede slow degeri belirle ve ıar filtre uygula
	//0.98 slow verin 0.02 de fast verin yap
	//ve slow verinden fast verini cıkartarak pressure diff i bul
	//actual diff büyüktür 10 ve küçüktür -10 ise bunları 10 ve -10 arasında sınırlandır
	//sonra pressure diff degerini slow verinden cıkar cıkardıgında bu senin actual pressure verin olacak
	if(Rc.Ch6<=1100)
	{
		Counter2=0;
		Zero_point_Barometer_Pressure=0;
		First_Barometer_Pressure=0;
	}

	if(Counter2==100)
	{
	   Zero_point_Barometer_Pressure=First_Barometer_Pressure/100;
	}
	if(Counter2!=101)
	{
		First_Barometer_Pressure=First_Barometer_Pressure+Barometer_Pressure;
		Counter2++;
	}


	Barometer_Altitude=44300*(1.0-pow(actual_Pressure/Zero_point_Barometer_Pressure,0.1902949));
//	if(Barometer_Altitude <= 0.05)
//	{
//		Barometer_Altitude = 0.0;
//	}
}

