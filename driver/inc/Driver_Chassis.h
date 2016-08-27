
#ifndef __DRIVER_CHASSIS_H
#define __DRIVER_CHASSIS_H


#include "stm32f4xx.h"


#define LFCHASSISCONTROLCANID           0x75
#define Max_WheelSpeed                  900
#define ChassisLimitCurrent             3000            //���̵������Ƽ���


//���̵��CANID
#define LFCHASSISCANID                  0x41
#define RFCHASSISCANID                  0x42
#define LBCHASSISCANID                  0x43
#define RBCHASSISCANID                  0x44
//���̵���ٶȿ���
#define CHASSISSPEEDSETCANID            0x46
//���̵����������
#define CHASSISCURRENTSETCANID          0x40


#ifdef  __DRIVER_CHASSIS_GLOBALS
#define __DRIVER_CHASSIS_EXT
#else
#define __DRIVER_CHASSIS_EXT extern
#endif


//���̵�������ṹ��
typedef struct
{
    //���Ŀ���ٶ�
    struct
    {
        int16_t LF;
        int16_t LB;
        int16_t RF;
        int16_t RB;
    }TargetSpeed;
    //���ʵ���ٶ�
    struct
    {
        int16_t LF;
        int16_t LB;
        int16_t RF;
        int16_t RB;
    }RealSpeed;
    //���Ƶ���
    struct
    {
        uint16_t LF;
        uint16_t LB;
        uint16_t RF;
        uint16_t RB;
    }LimitCurrent;
    //ʵ�ʵ���
    struct
    {
        uint16_t LF;
        uint16_t LB;
        uint16_t RF;
        uint16_t RB;
    }RealCurrent;
}MotorParam_Struct;


__DRIVER_CHASSIS_EXT float ChassisMaxSumCurrent;        //��������ܵ�������
__DRIVER_CHASSIS_EXT MotorParam_Struct MotorStatus;        //���״̬


void Chassis_SendAngle(void);
static void MecanumCalculate(float Vx, float Vy, float Omega, int16_t *Speed);


#endif
