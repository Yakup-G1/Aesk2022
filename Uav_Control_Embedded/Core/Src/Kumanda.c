
/*
 *
 * Fonksiyonlar ve kullanım amaçları
 *
 * 1-)temel map'leme fonksiyonu int ve float değerler için 2 tane yapılmıstır
 * 2-)Kumanda_True() Fonksiyonu Kumandanın haberleşmesinin 2 farklı şekilde koptugunu anlayabiliriz
 *    a-)kumandanın failsafe modu var ve bu moda göre kumanda kapanmadan önce son bir değer yolluyor
 *    ve bu yolladıgı değeri istediğimiz şekilde değiştirebiliyoruz kumandada VRA kanalı şeçilmiştir
 *    bu kanalda pot değeri 1111 değeri okunduğunda kumanda kapanmış demektir.
 *    not; eğer bu değer elle bir şekilde 1111 değerinde bırakılırsa drone çalışmaz failsafe modunda kalır
 *    b-)diğer yöntem donanımsal bir sorundur eğer rx kablosunda bir sorun varsa receive interrupta belirli bir süre
 *    girmesse oluşturulan bir flag ile kontrol edilir eğer 200ms lik bir task oluşturursak 200 ms de bir bu task sıfırlanır
 *    receive interupta 159 ms bir girmektedir bu bilgiden yararlanarak bayrak kontrol edilir ve sürekli 1 yapılır 200 ms lik taskda
 *    yaptıgımız bir receive interrupta sıfırlanmaktadır eğer sıfırlanmıyorsa kablosu çıkmış demektir
 *    Not: bu sorun geçici bir çözüm yöntemidir daha iyi bir yöntem bulunabilir
 *  3-)FailSafe() fonksiyonu motorlara giden güç direk minimuma çekmektedir
 *    Not: bu mode daha sonra otomatik olarak kendi kendine inmesi sağlanabilir yada geri dönüş ve benzeri modlar eklenebilir
 *  4-)RemotoControlMapping() bu fonksiyon amacı kumandadan okunan değerleri belirli değerler arasına sabitlemektedir
 *     bunun sebebi kontrolü bu değerler üzerinde yapmaktır.
 */
#include "Kumanda.h"
#include "Uav_Global.h"
#include "ReadingSensor.h"
#include "AhrsFilter.h"
#include "GPS_UBX.h"
//void FailSafe()
//{
//	while(1)
//	{
//		Motor.Sol_Arka = 1000;
//		Motor.Sag_Arka = 1000;
//		Motor.Sag_On   = 1000;
//		Motor.Sol_On   = 1000;
//	    SetMotorPWM(Motor.Sol_Arka, Motor.Sag_Arka,Motor.Sag_On, Motor.Sol_On);
//	}
//}
uint8_t PositionFlag=0;
void RemotoControlMapping()
{
	RemoteRoll.Raw  	= Rc.Ch1; //MapInt(Rc.Ch1, Min_Throttle, Max_Throttle, -Max_Axis_Value, Max_Axis_Value);
	RemotePitch.Raw  	= Rc.Ch2; //MapInt(Rc.Ch2, Min_Throttle, Max_Throttle, -Max_Axis_Value, Max_Axis_Value);
	RemoteYaw.Raw       = Rc.Ch4;
	RemoteThrottle.Raw  = Rc.Ch3; //MapInt(Rc.Ch2, Min_Throttle, Max_Throttle, -Max_Axis_Value, Max_Axis_Value);

	RemoteRoll.Velocity  	 = RemoteRoll.Velocity     + (RemoteRoll.Raw  	 -1500) * VelocityCoefficient * Elapsed_time;
	RemotePitch.Velocity  	 = RemotePitch.Velocity    + (RemotePitch.Raw  	 -1500) * VelocityCoefficient * Elapsed_time;
	RemoteYaw.Velocity       = RemoteYaw.Velocity      + (RemoteYaw.Raw      -1500) * VelocityCoefficient * Elapsed_time;
	RemoteThrottle.Velocity  = RemoteThrottle.Velocity + (RemoteThrottle.Raw -1500) * VelocityCoefficient * Elapsed_time;

	if(RemoteThrottle.Velocity <= 0)
	{
		RemoteThrottle.Velocity=0;
	}
	if (RemoteRoll.Raw  > MaxDeadband)
	{
		RemoteRoll.Setpoint    = -(RemoteRoll.Raw  - MaxDeadband);
		RemoteRoll.FeedForward = -(RemoteRoll.Raw  - MaxDeadband);
	}
	else if (RemoteRoll.Raw < MindDeadband)
	{
		RemoteRoll.Setpoint = -(RemoteRoll.Raw - MindDeadband);
		RemoteRoll.FeedForward = -(RemoteRoll.Raw - MindDeadband);
	}

	RemoteRoll.Setpoint -= Ahrs_ROLL * LevelAdjustCoefficient;// kumanda hassasiyeti level adjust coefficient ayarlıyor
	RemoteRoll.Setpoint /= LevelDivededValue;

	if (RemotePitch.Raw  > MaxDeadband)
	{
		RemotePitch.Setpoint = RemotePitch.Raw  - MaxDeadband;
		RemotePitch.FeedForward = RemotePitch.Raw  - MaxDeadband;
	}
	else if (RemotePitch.Raw < MindDeadband)
	{
		RemotePitch.Setpoint = RemotePitch.Raw - MindDeadband;
		RemotePitch.FeedForward = RemotePitch.Raw - MindDeadband;
	}

	RemotePitch.Setpoint -= Ahrs_PITCH * LevelAdjustCoefficient;// kumanda hassasiyeti level adjust coefficient ayarlıyor
	RemotePitch.Setpoint /= LevelDivededValue;

	if (RemoteYaw.Raw  > MaxDeadband)
	{
		RemoteYaw.Setpoint = RemoteYaw.Raw - MaxDeadband;
		RemoteYaw.FeedForward = RemoteYaw.Raw - MaxDeadband;
	}
	else if (RemoteYaw.Raw < MindDeadband)
	{
		RemoteYaw.Setpoint = RemoteYaw.Raw - MindDeadband;
		RemoteYaw.FeedForward = RemoteYaw.Raw - MindDeadband;
	}
	if(Rc.Ch6>1700 )			   // Position mode geçiş
	{
		RemoteYaw.Setpoint -= magno_bearing * LevelAdjustCoefficient;// kumanda hassasiyeti level adjust coefficient ayarlıyor
		RemoteYaw.Setpoint /= 2;
	}
	else
	{
		RemoteYaw.Setpoint -= Ahrs_YAW * LevelAdjustCoefficient;// kumanda hassasiyeti level adjust coefficient ayarlıyor
		RemoteYaw.Setpoint /= 2;
	}
	RemoteThrottle.Setpoint=MapFloat(RemoteThrottle.Raw, 1000, 2000, 0, 250);
}
void PositionControl(UBX_Handle *gpsDatas)
{
	if(Rc.Ch6 >1700)
	{
		if(PositionFlag==0) // bu flag ile gps moduna gectiğinde ilk konumu setpoint değerine atıyor bu sayede ilk positiona göre hata buluyoruz
		{
			RemoteRoll.TargetPosition  = gpsDatas->ubx_PVT.latitude ;
			RemotePitch.TargetPosition = gpsDatas->ubx_PVT.longitude ;
		}
		PositionFlag = 1;
	}

	RemoteRoll.TargetPositionVelocity = constrain((RemoteRoll.TargetPosition - gpsDatas->ubx_PVT.latitude), 300, 300);
	RemoteRoll.TargetPositionVelocity*= PositionLevelCoefficient; // PositionLevelCoefficient P katsayısı
	RemotePitch.TargetPositionVelocity = constrain((RemotePitch.TargetPosition - gpsDatas->ubx_PVT.latitude), 300, 300);
	RemotePitch.TargetPositionVelocity*= PositionLevelCoefficient; // PositionLevelCoefficient P katsayısı

}
//void AltitudeControl()
//{
//	HeightError = RemoteThrottle.Velocity - Barometer_Altitude;
//	LD = gravityAccel/ 2*pow(ThrottleLevelAdjustCoefficient,2);
//	if(HeightError <= 2*LD)
//	{
//
//	}
//} // devam edicek https://diydrones.com/profiles/blogs/arducopter-2-9-pid-loops-for-stabilize-acro-and-alt-hold


//void Kumanda_True()
//{
//
//	        RcTrue.ReceiveTrue = Rc.Ch5;// kumanda failsafe modu ile kumandanın 5 inci pinine kapanmadan 1111 değeri yolluyor bunu kullandım
//			if((RcTrue.ReceiveTrue != 1111) && (RcTrue.ConnectTrue==1) )
//		   {
//
//		    }
//				else
//				{
//						FailSafe();
//						resetPid();
//				}
//			RcTrue.ConnectTrue=0;
//			Flag_400ms=0;
//
//}
//void DeadBand()
//{
//
//	if(Remote.Throttle<>
//	//kumandanın orta noktasını ölü band olusturucam
//}
//void RemoteControlRate()
//{
//
//}




