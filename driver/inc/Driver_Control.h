
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



//��̨PitchĿ��Ƕ�(��������Ϊ��λ��
__DRIVER_CONTROL_EXT  uint16_t    EncoderTargetPitch, EncoderTargetYaw;
//��̨Pitch��yawĿ��Ƕȣ�ʵ��ֵ��
__DRIVER_CONTROL_EXT float ABSTargetPitch, ABSTargetYaw;  
//�������Ŀ���ٶ�
__DRIVER_CONTROL_EXT  int16_t    PokeSpeedTarget;
//��̨PID����
__DRIVER_CONTROL_EXT PID_Type PitchOPID, YawOPID, PitchIPID, YawIPID;
//��������ٶ�PID
__DRIVER_CONTROL_EXT PID_Type PokePID;
//ǹ���Ŀ���ٶȵ���
__DRIVER_CONTROL_EXT uint16_t GnuSpeedTarget;       


void CloudPID_InitConfig(void);
int16_t Control_YawPID(void);
int16_t Control_PitchPID(void);
int16_t Control_PokePID(void);
void Control_SetTargetPitch(float TargetPitch, CoordinateMode_Enum mode);
void Control_SetTargetYaw(float TargetYaw, CoordinateMode_Enum mode);
void Control_SetTargetPitch(float TargetPitch, CoordinateMode_Enum mode);
void Control_SetTargetYaw(float TargetYaw, CoordinateMode_Enum mode);


#endif
