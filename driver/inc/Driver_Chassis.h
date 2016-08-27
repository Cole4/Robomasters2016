
#ifndef __DRIVER_CHASSIS_H
#define __DRIVER_CHASSIS_H


#include "stm32f4xx.h"


#define LFCHASSISCONTROLCANID           0x75
#define MaxWheelSpeed                  900
#define ChassisLimitCurrent             2750            //���̵������Ƽ���
#define MOUSEINTLIMIT           0.9F        //�����ת�ٶ����ޣ��������תʱ�����ٶȸ��������С��ֵ


//���̵��CANID
#define LFCHASSISCANID                  0x41
#define RFCHASSISCANID                  0x42
#define LBCHASSISCANID                  0x43
#define RBCHASSISCANID                  0x44
//���̵���ٶȿ���
#define CHASSISSPEEDSETCANID            0x46
//���̵����������
#define CHASSISCURRENTSETCANID          0x40


#if INFANTRY == 1 || INFANTRY == 2 || INFANTRY == 3 || INFANTRY == 4 || INFANTRY == 5
#define CHASSISMAXPOWER                 80.0F       //���������
#elif INFANTRY == 6
#define CHASSISMAXPOWER                 160.0F      //���������
#endif


#ifdef  __DRIVER_CHASSIS_GLOBALS
#define __DRIVER_CHASSIS_EXT
#else
#define __DRIVER_CHASSIS_EXT extern
#endif


//�ٶ�ö��
typedef enum
{
    ChassisSpeedLevel_Hight,
    ChassisSpeedLevel_Low
}ChassisSpeedLevel_Enum;


//���������
typedef struct
{
    int16_t TargetSpeed;             //���Ŀ���ٶ�
    int16_t RealSpeed;               //���ʵ���ٶ�
    uint16_t LimitCurrent;           //���Ƶ���
    uint16_t RealCurrent;            //ʵ�ʵ���
    uint16_t NeedCurrent;            //�������
}OneMotorParam_Struct;


//���̵�������ṹ��
typedef struct
{
    OneMotorParam_Struct LF;
    OneMotorParam_Struct RF;
    OneMotorParam_Struct LB;
    OneMotorParam_Struct RB;
    ChassisSpeedLevel_Enum SpeedLevel;
    float VX;
    float VY;
    float Omega;
}ChassisParam_Struct;


//��������ܵ�������
__DRIVER_CHASSIS_EXT float ChassisMaxSumCurrent;   
//���״̬
__DRIVER_CHASSIS_EXT ChassisParam_Struct ChassisParam;    
//���̵��֡������
__DRIVER_CHASSIS_EXT uint16_t ChassisFrameCounter[4];   
//���̵��֡������
__DRIVER_CHASSIS_EXT uint16_t ChassisFrameRate[4];  



void Chassis_InitConfig(void);
void Chassis_Adjust(void);
void Chassis_SendMotorParam(uint8_t mode);
static void MecanumCalculate(float Vx, float Vy, float Omega, int16_t *Speed);
void Chassis_OmegaSet(float Target);
void Chassis_SpeedSet(float XSpeed, float YSpeed);
void Chassis_Control(uint8_t mode, uint8_t PIDChoie);
void Chassis_MotorDebug(void);


#endif
