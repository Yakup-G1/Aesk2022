/*
 * MotorPowerCalculate.h
 *
 *  Created on: Feb 15, 2021
 *      Author: karam
 */

#ifndef INC_MOTORPOWERCALCULATE_H_
#define INC_MOTORPOWERCALCULATE_H_
#include "main.h"
#include "Kumanda.h"
#include "PID.h"
//#include "ReadingSensor.h"
#include "MotorPowerCalculate.h"


TIM_HandleTypeDef htim1;/// denenecek unutma calısmayabilir

#define Dutymax 2000
#define Dutymin 1000
#define ControlSignalLimit 400
#define battery_compensation 40
#define BatteryMaxVoltage 12.57
#define MotorMinThrottle 1000
#define MotorMaxThrottle 1900

typedef struct
{
	float Error;
	float Control_Signal;
	float KP;
	float KI;
	float KD;
	float Input;
	float Setpoint;
}Control_HandleTypedef ;

float Roll_Last_Error;
float Pitch_Last_Error;
float Yaw_Last_Error;
float Altitude_Last_Error;
float Roll_Pid_i;
float Pitch_Pid_i;
float Yaw_Pid_i;
float Altitude_Pid_i;


float Rollerror;
float Pitcherror;
float Yawerror;
float Altitudeerror;


float RollControlSignal;
float PitchControlSignal;
float YawControlSignal;
float AltitudeControlSignal;

float RollPositionControl;
float RollPositionControlNorth; // yaw yönüne göre Roll açısı vermek için
float PitchPositionControl;
float PitchPositionControlNorth;// yaw yönüne göre Pitch açısı vermek için

void vibrationTest();
int32_t vibration_array[20], avarage_vibration_level, vibration_total_result;
uint8_t array_counter, throttle_init_ok, vibration_counter;
int vibration_sonuc;
int hangi_motor;
struct Motor_Powers
{
  uint16_t Sol_On;
  uint16_t Sag_On;
  uint16_t Sol_Arka;
  uint16_t Sag_Arka;
}Motor;

float Voltage_Loss_Prevention;
void Init_ESC();
void SetMotorPWM(uint16_t on,uint16_t arka,uint16_t sag,uint16_t sol);
void MotorPowerCalculateWithRate();
void MotorPowerCalculateWithAltitude();
void MotorPowerCalculateWithPosition();
float AESK_Ramp_Function(float increment, uint16_t target_angle,float *last_value);
void Transmit_NRF(void);
void ParseNRF(void);


#endif /* INC_MOTORPOWERCALCULATE_H_ */
