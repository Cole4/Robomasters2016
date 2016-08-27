
#ifndef __DRIVER_SUPERGYROSCOPE_H
#define __DRIVER_SUPERGYROSCOPE_H


#include "stm32f4xx.h"
#include "OSinclude.h"


#define SUPERGYROSCOPECANIC     0x11


#ifdef  __DRIVER_SUPERGYROSCOPE_GLOBALS
#define __DRIVER_SUPERGYROSCOPE_EXT
#else
#define __DRIVER_SUPERGYROSCOPE_EXT extern
#endif


typedef union u8Tofloat
{
    float floatdata;
    uint8_t uint8_tdata[4];
}u8Todouble;


//���������ǽǶ�
__DRIVER_SUPERGYROSCOPE_EXT float SuperGyoAngle;
//�����������ϴνǶ�
__DRIVER_SUPERGYROSCOPE_EXT float LastSuperGyoAngle;
//���������ǽ��ٶ�
__DRIVER_SUPERGYROSCOPE_EXT float SuperGyoOmega;
//���������ǽ��ٶ�תΪ��������λ
__DRIVER_SUPERGYROSCOPE_EXT float SuperGyoMotorEncoderOmega;
//��������������֡����
__DRIVER_SUPERGYROSCOPE_EXT float SuperGyoFrameCounter;
//��������������֡֡��
__DRIVER_SUPERGYROSCOPE_EXT float SuperGyoFrameRate;


void SuperGyo_InitConfig(void);


#endif
