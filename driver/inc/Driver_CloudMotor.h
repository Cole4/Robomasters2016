
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
#define ABSPITCHUPLIMIT         60.0F          //pitch���ԽǶ����޷�
#define ABSPITCHDOWNLIMIT       -40.0F         //pitch���ԽǶ����޷�
#elif INFANTRY == 2     //����˹��
#define PitchUPLimit            3500
#define PitchDOWNLimit          2600
#define PitchCenter             2888
#define YawLEFTLimit            5500
#define YawRIGHTLimit           3000
#define YawCenter               4100
#define ABSPITCHUPLIMIT         60.0F          //pitch���ԽǶ����޷�
#define ABSPITCHDOWNLIMIT       -40.0F         //pitch���ԽǶ����޷�
#elif INFANTRY == 3     //��ʿ��
#define PitchUPLimit            4400
#define PitchDOWNLimit          3500
#define PitchCenter             3897
#define YawLEFTLimit            4600
#define YawRIGHTLimit           2220
#define YawCenter               3380
#define ABSPITCHUPLIMIT         60.0F          //pitch���ԽǶ����޷�
#define ABSPITCHDOWNLIMIT       -40.0F         //pitch���ԽǶ����޷�
#elif INFANTRY == 4     //����
#define PitchUPLimit            5400
#define PitchDOWNLimit          4430
#define PitchCenter             4862
#define YawLEFTLimit            4630
#define YawRIGHTLimit           2230
#define YawCenter               3440
#define ABSPITCHUPLIMIT         60.0F          //pitch���ԽǶ����޷�
#define ABSPITCHDOWNLIMIT       -40.0F         //pitch���ԽǶ����޷�
#elif INFANTRY == 5     //����
#define PitchUPLimit            5400
#define PitchDOWNLimit          4600
#define PitchCenter             4862
#define YawLEFTLimit            10400
#define YawRIGHTLimit           8400
#define YawCenter               9270
#define ABSPITCHUPLIMIT         60.0F          //pitch���ԽǶ����޷�
#define ABSPITCHDOWNLIMIT       -40.0F         //pitch���ԽǶ����޷�
#elif INFANTRY == 6     //Ӣ��
#define PitchUPLimit            7850
#define PitchDOWNLimit          7060
#define PitchCenter             7377
#define YawLEFTLimit            3980
#define YawRIGHTLimit           2560
#define YawCenter               3327
#define ABSPITCHUPLIMIT         60.0F          //pitch���ԽǶ����޷�
#define ABSPITCHDOWNLIMIT       -40.0F         //pitch���ԽǶ����޷�
#endif




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
