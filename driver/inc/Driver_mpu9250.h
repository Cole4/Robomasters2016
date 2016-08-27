
#ifndef __DRIVER_MPU9250_H
#define __DRIVER_MPU9250_H


#include "stm32f4xx.h"


#ifdef  __MPU9250_GLOBALS
#define __MPU9250_EXT
#else
#define __MPU9250_EXT   extern
#endif


//��������̬�������ݽṹ
typedef struct
{
    //ʵ������
    struct
    {
        //���ٶ�ʵ������
        float OX;
        float OY;
        float OZ;
        //���ٶ�ʵ������
        float GX;
        float GY;
        float GZ;
        //�¶�ʵ������
        float T;
    }Real;
    
    //ת��Ϊ�������� ��/s �Ľ��ٶ�����
    struct
    {
        int16_t X;
        int16_t Y;
        int16_t Z;
    }MotorEncoderOmega;
    
    //����ʵ�ʶԵ�ŷ����
    struct
    {
        float Pitch;
        float Roll;
        float Yaw;
    }Euler;
}MPU9250_TypeDef;


typedef struct
{
    float X;
    float Y;
    float Z;
}Offset_TypeDef;


//��̬����
__MPU9250_EXT MPU9250_TypeDef Position;
//ƫ����������
__MPU9250_EXT Offset_TypeDef Omega_Offset;


void MPU9250_InitConfig(void);
uint8_t MPU9250_Update(void);


#endif
