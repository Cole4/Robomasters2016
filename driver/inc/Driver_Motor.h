
#ifndef __DRIVER_MOTOR_H
#define __DRIVER_MOTOR_H


#include "stm32f4xx.h"


//���CAN ID
#define YAWCANID		0x205
#define PITCHCANID		0x206

#define COULDCONTROLID	0x1FF

//�������е�λ��
#define ENCODERCenter   0x7FFF


//�Ƕ��޷�
#define PitchUPLimit            5800
#define PitchDOWNLimit          4500
#define PitchCenter             4844
#define YawLEFTLimit            6730
#define YawRIGHTLimit           2630
#define YawCenter               4650

//ǹĦ�����ٶ�
#define GUNWORKSPEED            260         //ʹǹ�ӵ������ٵ����ǹĦ�����ٶ�
#define POKEWORKSPEED           -100        //ʹǹ�ӵ�����Ƶ����ٶ�(���ſ��Ʒ���


#ifdef  __MOTOR_GLOBALS
#define __MOTOR_EXT
#else   
#define __MOTOR_EXT extern
#endif


//��̨���ʵ�ʽǶ�
__MOTOR_EXT int16_t PitchMotorAngle, YawMotorAngle;
//�������ʵ���ٶ�
__MOTOR_EXT int16_t PokeSpeed;
//��̨�������֡��������
__MOTOR_EXT uint16_t PitchMotorFrameCounter, YawMotorFrameCounter;
//��̨�������֡��
__MOTOR_EXT uint16_t PitchMotorFrameRate, YawMotorFrameRate;


void Motor_InitConfig(void);
void CloudMotorCurrent(int16_t Pitch, int16_t Yaw);
void PokeMotorCurrent(int16_t Current);
void GunFric_Control(uint8_t Control);
void Poke_Control(uint8_t status);
void SteeringAngle(uint16_t angle);



#endif
