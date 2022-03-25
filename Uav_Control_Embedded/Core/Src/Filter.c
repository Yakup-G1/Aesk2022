/*
 * Filtertry.c
 *
 *  Created on: 9 Kas 2021
 *      Author: karam
 */
#include "Filter.h"
#include "ReadingSensor.h"

// Notch Filter Katsayıları (İİR tabanlı)
//filtre katsayıları otomatşk dolduran fonksiyonu yaz
const float A_LP[3]={1.0f,-1.6474599888437864f,0.70089678675383704};
const float B_LP[3]={0.013359199477512686f, 0.026718398955025372f,0.013359199477512686f};

//const float A_Coefficient[3]={1.0f,-1.9111970694086076f,0.91497583661868542f};
//const float A_Coefficient[3]={0.00094469180251951211f, 0.0018893836050390242f, 0.00094469180251951211f};

// bu fonksiyon A_Coefficient ve A_Coefficient filtre katsayıları bulmak için yapılmıştır
// aşağıda bu filtreye kesme frekansını ve kodu döngünüzün gerçekleştiği frekansın 5 te 1ini girerek kullanabilirsiniz
// alınan katsayılar ile kesmede belirlediğiniz frekansı aralıgını kullanmassınız
// istediğniz değerleri bir kere debugdan belirleyerek A_Coefficient Ve A_Coefficient ye sırasıyla yerleştiriniz
void CoefficientCalculator(float CutOffFrekansHZ,float OrneklemeFrekansHZ)
{
	float GenelFrekans = CutOffFrekansHZ / OrneklemeFrekansHZ;
	const double ita = 1.0f/tan(M_PI * GenelFrekans);
	const double q = sqrt(2.0f);
	B_Coefficient[0] = 1.0f / (1.0f + q*ita + ita*ita);
	B_Coefficient[1] = 2*B_Coefficient[0];
	B_Coefficient[2] = B_Coefficient[0];
	A_Coefficient[0] = 1;// bir olmalı
	A_Coefficient[1] = -2.0f * (ita * ita - 1.0) * B_Coefficient[0];
	A_Coefficient[2] = (1.0 - q*ita + ita * ita) * B_Coefficient[0];
}

float Butterworth(Notch *FilterName ,float FilterData)
{
	FilterName->NotchFilterOut = (B_LP[0])*FilterData+(B_LP[1])*FilterName->NotchFilterIn[0]+(B_LP[2])*FilterName->NotchFilterIn[1]-(A_LP[1])*FilterName->NotchFilterIn[2]-(A_LP[2])*FilterName->NotchFilterIn[3];
	FilterName->NotchFilterIn[1] = FilterName->NotchFilterIn[0];
	FilterName->NotchFilterIn[0] = FilterData;
	FilterName->NotchFilterIn[3] = FilterName->NotchFilterIn[2];
	FilterName->NotchFilterIn[2] = FilterName->NotchFilterOut;
	return FilterName->NotchFilterOut;
}

//float NotchFilterUpdate(Notch *FilterName ,float FilterData)
//{
//	FilterName->NotchFilterIn[2] = FilterName->NotchFilterIn[1];
//	FilterName->NotchFilterIn[1] = FilterName->NotchFilterIn[0];
//	FilterName->NotchFilterIn[4] = FilterName->NotchFilterIn[3];
//	FilterName->NotchFilterIn[3] = FilterName->NotchFilterOut;
//	FilterName->NotchFilterIn[0] = FilterData;
//	FilterName->NotchFilterOut = (alpha * FilterName->NotchFilterIn[0] + 2.0f*(alpha-8.0f)*FilterName->NotchFilterIn[1]+alpha*FilterName->NotchFilterIn[2]- 2.0f*(alpha -8.0f )*FilterName->NotchFilterIn[3]-(alpha-beta)*FilterName->NotchFilterIn[4])/(alpha+beta);
//
//	return FilterName->NotchFilterOut;
//}
//void Notch_Filterinit(float centerfreq_hz, float sampleTime, float notchfilter_hz)
//{
//	float wo_rps = 2.0f * M_PI *centerfreq_hz;
//	float ww_rps = 2.0f * M_PI *notchfilter_hz;
//
//	float wo_pw_rps = (2.0f / sampleTime) * tanf(0.5f * wo_rps * sampleTime);
//
//	alpha= 4.0f *wo_pw_rps * wo_pw_rps *sampleTime*sampleTime;
//	beta = 2.0f *ww_rps* sampleTime;
//}
