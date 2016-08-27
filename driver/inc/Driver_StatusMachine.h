
#ifndef __DRIVER_STATUSMACHINE_H
#define __DRIVER_STATUSMACHINE_H


#include "stm32f4xx.h"


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
}GunStatus_TypeDef;

//��̨״̬
typedef enum
{
    CloudStatus_Normal,             //����ģʽ
    CloudStatus_Auto,               //�Զ�ģʽ
}CloudStatus_TypeDef;


//����ģʽ
typedef enum
{
    ControlStatus_Protect,          //����ģʽ��ȫ��ֹͣ
    ControlStatus_RC,               //ң�������ƣ�����ʽ��
    ControlStatus_KM,               //�������
}ControlStatus_TypeDef;


//״̬��
__DRIVER_STATUSMACHINE_EXT  CloudStatus_TypeDef         CloudStatus;
__DRIVER_STATUSMACHINE_EXT  GunStatus_TypeDef           GunStatus;
__DRIVER_STATUSMACHINE_EXT  ControlStatus_TypeDef       ControlStatus;


void StatusMachine_InitConfig(void);
void StatusMachine_Update(void);


#endif
