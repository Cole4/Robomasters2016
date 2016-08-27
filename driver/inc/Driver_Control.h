
#ifndef __DRIVER_CONTROL_H
#define __DRIVER_CONTROL_H


#include "stm32f4xx.h"
#include "OSinclude.h"
#include "Config.h"


#ifdef  __DRIVER_CONTROL_GLOBALS
#define __DRIVER_CONTROL_EXT
#else
#define __DRIVER_CONTROL_EXT extern
#endif


//PID���ݽṹ
typedef struct
{
	float P;
	float I;
	float D;
	
	float CurrentError;
	float LastError;
	float Pout;
	float Iout;
	float Dout;
	float PIDout;
	
	float IMax;
	float PIDMax;
	
	portTickType LastTick;
}PID_Type;



//��̨PID����
__DRIVER_CONTROL_EXT PID_Type PitchOPID, YawOPID, PitchIPID, YawIPID;
//��������ٶ�PID
__DRIVER_CONTROL_EXT PID_Type PokeIPID, PokeOPID;     
//���̽Ƕ�PID
__DRIVER_CONTROL_EXT PID_Type ChassisIPID, ChassisOPID; 
//�����Զ��Ƕ�PID
__DRIVER_CONTROL_EXT PID_Type ChassisAUTOIPID, ChassisAUTOOPID; 
//Ԥ���ٶ�PID
__DRIVER_CONTROL_EXT PID_Type ForcastYawSpeedPID;

//#if INFANTRYTYPE == 1 || INFANTRYTYPE == 2
////AB��ģʽ
//__DRIVER_CONTROL_EXT ABInfantryMode_Enum ABInfantryMode;
//#endif


void CloudPID_InitConfig(void);
int16_t Control_YawPID(void);
int16_t Control_PitchPID(void);
int16_t Control_PokeIPID(void);
void Control_ChassisPID(void);
int16_t Control_FeedForwardYawPID(float FeedSpeed);

#endif
