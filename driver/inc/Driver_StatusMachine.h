
#ifndef __DRIVER_STATUSMACHINE_H
#define __DRIVER_STATUSMACHINE_H


#include "stm32f4xx.h"


#define VisiolModeChangeDataSendNum     10


#ifdef  __DRIVER_STATUSMACHINE_GLOBALS
#define __DRIVER_STATUSMACHINE_EXT
#else
#define __DRIVER_STATUSMACHINE_EXT extern
#endif

//ǹ״̬
typedef enum
{
    GunStatus_Stop,                 //ǹֹͣ
    GunStatus_Motor,                //������Ħ����
    GunStatus_Shot,                 //����
}GunStatus_Enum;

//�Զ�ģʽ����
typedef enum
{
    AutoMode_ON,                    //�Զ�ģʽ��
    AutoMode_OFF,                   //�Զ�ģʽ��
}AutoMode_Enum;


//����ģʽ
typedef enum
{
    ControlMode_Protect,          //����ģʽ��ȫ��ֹͣ
    ControlMode_RC,               //ң�������ƣ�����ʽ��
    ControlMode_KM,               //�������
    ControlMode_AUTO,             //��������
}ControlMode_Enum;


//״̬��
__DRIVER_STATUSMACHINE_EXT  AutoMode_Enum           AutoMode;
__DRIVER_STATUSMACHINE_EXT  GunStatus_Enum          GunStatus;
__DRIVER_STATUSMACHINE_EXT  ControlMode_Enum        ControlMode;


void StatusMachine_InitConfig(void);
void StatusMachine_Update(void);


#endif
