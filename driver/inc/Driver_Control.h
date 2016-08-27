
#ifndef __DRIVER_CONTROL_H
#define __DRIVER_CONTROL_H


#include "stm32f4xx.h"
#include "OSinclude.h"


#ifdef  __DRIVER_CONTROL_GLOBALS
#define __DRIVER_CONTROL_EXT
#else
#define __DRIVER_CONTROL_EXT extern
#endif


#define Motor3510Speed      4000        //������3510����ٶ�


typedef enum
{
    Encoder,
    ABS
}CoordinateMode_Enum;


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


void CloudPID_InitConfig(void);
int16_t Control_YawPID(void);
int16_t Control_PitchPID(void);
int16_t Control_PokeIPID(void);
void Control_ChassisPID(void);


#endif
