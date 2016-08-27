
#ifndef __DRIVER_CLOUDMOTOR_H
#define __DRIVER_CLOUDMOTOR_H

#include "Config.h"
#include "stm32f4xx.h"


//���CAN ID
#define YAWMOTORCANID		0x205
#define PITCHMOTORCANID		0x206

#define COULDCONTROLID	    0x1FF


//�Ƕ��޷�
#if INFANTRY == 1       //��Ħ
#define PitchUPLimit            5600
#define PitchDOWNLimit          4500
#define PitchCenter             4844
#define YawLEFTLimit            5600
#define YawRIGHTLimit           3800
#define YawCenter               4650
#elif INFANTRY == 2     //����˹��
#define PitchUPLimit            5600
#define PitchDOWNLimit          4400
#define PitchCenter             4804
#define YawLEFTLimit            4900
#define YawRIGHTLimit           3400
#define YawCenter               4100
#elif INFANTRY == 3     //��ʿ��
#define PitchUPLimit            4400
#define PitchDOWNLimit          3500
#define PitchCenter             3897
#define YawLEFTLimit            4050
#define YawRIGHTLimit           2420
#define YawCenter               3380
#endif

#define ABSPITCHUPLIMIT         70.0F          //pitch���ԽǶ����޷�
#define ABSPITCHDOWNLIMIT       -50.0F          //pitch���ԽǶ����޷�



#ifdef  __CLOUDMOTOR_GLOBALS
#define __CLOUDMOTOR_EXT
#else   
#define __CLOUDMOTOR_EXT extern
#endif


//�Ƕ�����ö��
typedef enum
{
    AngleMode_Encoder,
    AngleMode_ABS
}AngleMode_Enum;


//��̨��������ṹ��
typedef struct
{
    uint16_t EncoderTargetAngle;                //Ŀ��Ƕȣ�������ֵ��
    float   ABSTargetAngle;                     //Ŀ��Ƕȣ�ʵ��ֵ��
    uint16_t RealEncoderAngle;                  //���ʵ�ʽǶȣ�������ֵ��    
    AngleMode_Enum AngleMode;                   //�Ƕ�ģʽ��ָ��Ŀ��Ƕ�ʹ�þ��ԽǶȻ�����ԽǶ�
    uint16_t FrameCounter;                      //֡�ʼ�����
    uint16_t FrameRate;                         //֡��
}ClourMotorParam_Struct;

//��̨�����ṹ��
typedef struct
{
    ClourMotorParam_Struct Pitch;               //Pitch�������
    ClourMotorParam_Struct Yaw;                 //Yaw�������
    uint8_t Lock;                               //0 ��������̨���ֹͣ       1 ��������
}CloudParam_Struct;


//��̨����
__CLOUDMOTOR_EXT CloudParam_Struct CloudParam;



void CloudMotor_InitConfig(void);
void CloudMotorCurrent(int16_t Pitch, int16_t Yaw);
void Cloud_Adjust(uint8_t mode);
void Cloud_YawAngleSet(float Target, uint8_t mode);
void Cloud_PitchAngleSet(float Target, uint8_t mode);


#endif
