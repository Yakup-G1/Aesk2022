/*
 * Filter.h
 *
 *  Created on: 9 Kas 2021
 *      Author: karam
 */

#ifndef INC_FILTER_H_
#define INC_FILTER_H_

typedef struct
{
	float NotchFilterIn[5];
	float NotchFilterOut;

}Notch;

Notch GyroRollFiltered;
Notch GyroPitchFiltered;
Notch GyroYawFiltered;
Notch AccelRollFiltered;
Notch AccelPitchFiltered;
Notch AccelYawFiltered;
Notch MagRollFiltered;
Notch MagPitchFiltered;
Notch MagYawFiltered;

// coefficient hesaplayıcı değişkenleri
double B_Coefficient[3],A_Coefficient[3];
//float CutOffFrekansı;//kesme frekansı
//float OrneklemeFrekansı;// Not filtre 1000 hz ise örnekleme frekansı bunun 5 te 1 olmalı döngü 5 kerede değerde bir çıkşı veriyor

void CoefficientCalculator(float CutOffFrekans,float OrneklemeFrekans);
float Butterworth(Notch *FilterName ,float FilterData);

//void Notch_Filterinit(float centerfreq_hz, float sampleTime, float notchfilter_hz);
//float NotchFilterUpdate(Notch *FilterName ,float FilterData);

#endif /* INC_FILTER_H_ */
