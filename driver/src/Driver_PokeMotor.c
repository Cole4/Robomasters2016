
#define __DRIVER_POKEMOTOR_GLOBALS

#include "OSinclude.h"
#include "Driver_Control.h"
#include "Driver_PokeMotor.h"


/**
  * @brief  ���������ʼ��
  * @param  void
  * @retval void
  */
void PokeMotor_InitConfig(void)
{
    PokeMotorParam.RealLocation = 0;
    PokeMotorParam.RealSpeed = 0;
    PokeMotorParam.Status = PokeMotorParam_Working;
    PokeMotorParam.TargetLocation = 0;
    PokeMotorParam.LastShotTick = 0;
    
    //�������������λ�ó�ʼ��
    TIM3->CNT = POKEENCODERCenter;
    
    //������������ʼ��Ϊ˳ʱ��
    GPIO_SetBits(GPIOA, GPIO_Pin_5);
}




/**
  * @brief  ���������������
  * @param  ������С����399��
  * @retval void
  */
void PokeMotorCurrent(int16_t Current)
{
    int16_t S;
    
    S = Current > 399 ? 399 : Current;
    S = Current < -399 ? -399 : Current;
    
    //˳ʱ��
    if(Current >= 0)
    {
        GPIO_SetBits(GPIOA, GPIO_Pin_5);
        TIM5->CCR2 = S;
    }
    else
    {
        GPIO_ResetBits(GPIOA, GPIO_Pin_5);
        TIM5->CCR2 = -S;
    }
//#endif
}


/**
  * @brief  �����������һ��
  * @param  void
  * @retval void
  * @note   ����������ڷ�ֹͣ״̬��working,struck����Ч,������Ƶ
  */
void PokeMotor_Step(void)
{
    portTickType CurrentTick = xTaskGetTickCount();
    
    if((PokeMotorParam.Status == PokeMotorParam_Working) && 
        (CurrentTick - PokeMotorParam.LastShotTick >= POKESTEPMINTIMECRACK) && 
        (PokeMotorParam.RealLocation - PokeMotorParam.TargetLocation >= -30) &&
        (PokeMotorParam.RealLocation - PokeMotorParam.TargetLocation <= 30))
    {
        PokeMotorParam.TargetLocation = PokeMotorParam.RealLocation - POKELINESPERSTEP;
        PokeMotorParam.LastShotTick = CurrentTick;
    }
}


/**
  * @brief  ����������ƺ���
  * @param  void
  * @retval void
  * @note   �˺���Ҫ����������
  */
void PokeMotor_Adjust(void)
{
    int16_t PokeCurrent;
    
    PokeMotorParam.RealSpeed = POKEENCODERCenter - TIM3->CNT;
    TIM3->CNT = POKEENCODERCenter;
    
    //���С��30��
    if((PokeOPID.CurrentError < 30) && (PokeOPID.CurrentError > -30))
    {
        PokeMotorParam.Status = PokeMotorParam_Working;
    }
    
    //���ݻ����ж��Ƿ񿨵��������ִﵽ80%����ʱ��Ϊ����,����תָ���Ƕ�
    if(((PokeIPID.Iout > PokeIPID.IMax * 0.85F) || (PokeIPID.Iout < -PokeIPID.IMax * 0.85F)) && (PokeMotorParam.Status == PokeMotorParam_Working))
    {
        PokeMotorParam.Status = PokeMotorParam_Stuck;
        
//        PokeMotorParam.TargetLocation -= PokeMotorParam.RealSpeed > 0 ? POKESTRUCKDEALLINES : -POKESTRUCKDEALLINES;
        PokeMotorParam.TargetLocation = PokeMotorParam.RealLocation + POKESTRUCKDEALLINES;
    }
    
    PokeMotorParam.RealLocation += PokeMotorParam.RealSpeed;
    
    PokeCurrent = Control_PokeIPID();
    
    PokeMotorCurrent(PokeCurrent);
}




