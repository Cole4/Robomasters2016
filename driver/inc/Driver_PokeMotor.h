
#ifndef __DRIVER_POKEMOTOR_H
#define __DRIVER_POKEMOTOR_H

#include "Config.h"
#include "stm32f4xx.h"
#include "OSinclude.h"


#define POKEENCODERLINESPERCIRCLE       5050        //�������������ÿ������
#define POKELINESPERSTEP                920         //�������������������

//��������������е�λ��
#define POKEENCODERCenter               0x7FFF


#ifdef  __DRIVER_POKEMOTOR_GLOBALS
#define __DRIVER_POKEMOTOR_EXT
#else
#define __DRIVER_POKEMOTOR_EXT extern
#endif


//�������״̬ö��
typedef enum
{
    PokeChassisParam_Working,                        //����
    PokeChassisParam_Stuck                           //���������ڷ�ת������
}PokeChassisParam_Enum;  
    
    
//�����������    
typedef struct  
{   
    int16_t RealSpeed;              //��������ٶ�
    long RealLocation;              //�������ʵ��λ��
    long TargetLocation;            //�������Ŀ��λ��
    PokeChassisParam_Enum Status;    //״̬
    portTickType LastShotTick;      //�ϴη���ʱ��
}PokeMotorParam_Struct;


//�����������
__DRIVER_POKEMOTOR_EXT PokeMotorParam_Struct PokeMotorParam;


void PokeMotor_InitConfig(void);
void PokeMotorCurrent(int16_t Current);
void PokeMotor_Step(void);
void PokeMotor_Adjust(void);




#endif
