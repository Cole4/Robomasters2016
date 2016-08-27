#ifndef __DRIVER_JUDGE_H
#define __DRIVER_JUDGE_H


#include "stm32f4xx.h"


#define JudgeFrameHeader        0xA5        //֡ͷ 


#ifdef  __DRIVER_GLOBALS
#define __DRIVER_EXT
#else
#define __DRIVER_EXT extern
#endif


//С��״̬ö��
typedef enum
{
    BUFF_TYPE_NONE, //��Ч
    BUFF_TYPE_ARMOR = 0x01, //������
    BUFF_TYPE_SUPPLY = 0x04, //��Ѫ��
    BUFF_TYPE_BULLFTS= 0x08, //�ӵ���
}LBuffType_Enum;


//λ��״̬�ṹ��
typedef __packed struct
{
    uint8_t flag; //0 ��Ч�� 1 ��Ч
    uint32_t x;
    uint32_t y;
    uint32_t z;
    uint32_t compass;
}GpsData_Struct;


//����������Ϣ�ṹ��
typedef __packed struct
{
    uint32_t remainTime;
    uint16_t remainLifeValue;
    float realChassisOutV;
    float realChassisOutA;
    uint8_t runeStatus[4];
    uint8_t bigRune0Status;
    uint8_t bigRune1status;
    uint8_t conveyorBelts0:2;
    uint8_t conveyorBelts1:2;
    uint8_t parkingApron0:1;
    uint8_t parkingApron1:1;
    uint8_t parkingApron2:1;
    uint8_t parkingApron3:1;
    GpsData_Struct gpsData;
}GameInfo_Struct;


//ʵʱѪ���仯��Ϣ�ṹ��
typedef __packed struct
{
    uint8_t weakId:4;
    uint8_t way:4;
    uint16_t value;
}RealBloodChangedData_Struct;


//ʵʱ�����Ϣ�ṹ��
typedef __packed struct
{
    float realBulletShootSpeed;
    float realBulletShootFreq;
    float realGolfShootSpeed;
    float realGolfShootFreq;
}RealShootData_Struct;


//ʵʱ��ѹ
__DRIVER_EXT float JudgeRealVoltage;
//ʵʱ����
__DRIVER_EXT float JudgeRealCurrent;
//֡�ʼ�����
__DRIVER_EXT float JudgeFrameCounter;
//֡��
__DRIVER_EXT float JudgeFrameRate;



#endif
