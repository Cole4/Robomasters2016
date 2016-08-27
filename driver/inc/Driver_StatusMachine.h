
#ifndef __DRIVER_STATUSMACHINE_H
#define __DRIVER_STATUSMACHINE_H


#include "stm32f4xx.h"


#define VisiolModeChangeDataSendNum     10


#ifdef  __DRIVER_STATUSMACHINE_GLOBALS
#define __DRIVER_STATUSMACHINE_EXT
#else
#define __DRIVER_STATUSMACHINE_EXT extern
#endif

//Ħ����״̬
typedef enum
{
    FricStatus_Stop,
    FricStatus_Working,
    FricStatus_Crazy,
}FricStatus_Enum;


//����ģʽ
typedef enum
{
    ControlMode_Protect,            //����ģʽ��ȫ��ֹͣ 
    ControlMode_RC,                 //ң�������ƣ�����ʽ��
    ControlMode_KM,                 //�������
}ControlMode_Enum;


//����ģʽ��ģʽ
typedef enum
{
    KMSubschema_Normal,         //����ģʽ��ȫ�ֶ�ģʽ��
    KMSubschema_Supply,         //����վģʽ
    KMSubschema_Swing,          //����ҡ��ģʽ
    KMSubschema_Halfauto,       //���Զ����ģʽ
    KMSubschema_Bigsample,      //���ģʽ
    KMSubschema_Fullauto,       //ȫ�Զ�ģʽ
    KMSubschema_Circle,         //����תȦ
}KMSubschema_Enum;



//״̬��
__DRIVER_STATUSMACHINE_EXT ControlMode_Enum         ControlMode;
__DRIVER_STATUSMACHINE_EXT FricStatus_Enum          FricStatus;
__DRIVER_STATUSMACHINE_EXT KMSubschema_Enum         KMSubschema;


void StatusMachine_InitConfig(void);
void StatusMachine_Update(void);


#endif
