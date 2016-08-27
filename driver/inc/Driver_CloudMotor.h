
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

    #define PitchEncoderUPLimit             5600            //��̨��е���ޱ�����ֵ
    #define PitchEncoderDOWNLimit           4500            //��̨��е���ޱ�����ֵ
    #define PitchEncoderCenter              4844            //��̨Pitchˮƽ������ֵ
    #define YawEncoderLEFTLimit             5600            //��̨��е���ޱ�����ֵ
    #define YawEncoderRIGHTLimit            3800            //��̨��е�Ҽ��ޱ�����ֵ
    #define YawEncoderCenter                4650            //��̨Yaw�б�����ֵ

    #define PitchABSUPLimit                 60.0F           //�������ԽǶ��ϼ���
    #define PitchABSDOWNLimit               -40.0F          //�������ԽǶ��¼���
    
    #define PitchEncoderPassZeroBoundary    0               //Pitch����������ֽ�ֵ�����ֵ�жϹ���
    #define YawEncoderPassZeroBoundary      0               //Pitch����������ֽ�ֵ�����ֵ�жϹ���

#elif INFANTRY == 2     //����˹��

    #define PitchEncoderUPLimit             3500
    #define PitchEncoderDOWNLimit           2500
    #define PitchEncoderCenter              2888
    #define YawEncoderLEFTLimit             5000
    #define YawEncoderRIGHTLimit            3250
    #define YawEncoderCenter                4122
    
    #define PitchABSUPLimit                 60.0F 
    #define PitchABSDOWNLimit               -40.0F
    
    #define PitchEncoderPassZeroBoundary    0
    #define YawEncoderPassZeroBoundary      0

#elif INFANTRY == 3     //��ʿ��

    #define PitchEncoderUPLimit             4400
    #define PitchEncoderDOWNLimit           3500
    #define PitchEncoderCenter              3897
    #define YawEncoderLEFTLimit             4600
    #define YawEncoderRIGHTLimit            2220
    #define YawEncoderCenter                3380
    
    #define PitchABSUPLimit                 60.0F 
    #define PitchABSDOWNLimit               -40.0F
    
    #define PitchEncoderPassZeroBoundary    0
    #define YawEncoderPassZeroBoundary      0

#elif INFANTRY == 4     //����

    #define PitchEncoderUPLimit             5400
    #define PitchEncoderDOWNLimit           4430
    #define PitchEncoderCenter              4862
    #define YawEncoderLEFTLimit             4630
    #define YawEncoderRIGHTLimit            2230
    #define YawEncoderCenter                3440
                
    #define PitchABSUPLimit                 60.0F 
    #define PitchABSDOWNLimit               -40.0F
    
    #define PitchEncoderPassZeroBoundary    0
    #define YawEncoderPassZeroBoundary      0

#elif INFANTRY == 5     //����

    #define PitchEncoderUPLimit             5400
    #define PitchEncoderDOWNLimit           4600
    #define PitchEncoderCenter              4862
    #define YawEncoderLEFTLimit             10400
    #define YawEncoderRIGHTLimit            8400
    #define YawEncoderCenter                9270
                
    #define PitchABSUPLimit                 60.0F 
    #define PitchABSDOWNLimit               -40.0F
    
    #define PitchEncoderPassZeroBoundary    4000
    #define YawEncoderPassZeroBoundary      0

#endif




#ifdef  __CLOUDMOTOR_GLOBALS
#define __CLOUDMOTOR_EXT
#else   
#define __CLOUDMOTOR_EXT extern
#endif


//�Ƕ�����ö��
typedef enum
{
    AngleMode_OPP,          //��ԽǶ�
    AngleMode_ABS           //���ԽǶ�
}AngleMode_Enum;


//��̨��������ṹ��
typedef struct
{
    uint16_t RealEncoderAngle;                  //����Ƕȱ�����ֵ  
    float RealABSAngle;                         //ʵ�ʽǶȣ�����ֵ��
    float TargetABSAngle;                       //Ŀ��Ƕȣ�����ֵ��
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
void Cloud_YawAngleSet(float Target, AngleMode_Enum mode);
void Cloud_PitchAngleSet(float Target);


#endif
