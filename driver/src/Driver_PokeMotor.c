
#define __DRIVER_POKEMOTOR_GLOBALS

#include "OSinclude.h"
#include "Driver_Control.h"
#include "Driver_PokeMotor.h"

//�������������5050/Ȧ

/**
  * @brief  ���������ʼ��
  * @param  void
  * @retval void
  */
void PokeMotor_InitConfig(void)
{
    PokeMotorParam.RealLocation = 0;
    PokeMotorParam.RealSpeed = 0;
    PokeMotorParam.Status = PokeMotorParam_Suit;
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
    
    if((PokeMotorParam.Status == PokeMotorParam_Suit) && 
        (CurrentTick - PokeMotorParam.LastShotTick >= POKESTEPMINTIMECRACK))
    {
        PokeMotorParam.TargetLocation = PokeMotorParam.RealLocation - POKELINESPERSTEP;
        PokeMotorParam.LastShotTick = CurrentTick;
    }
}


/**
  * @brief  ����������ƺ���
  * @param  1 PID����     0ʧ��
  * @retval void
  * @note   �˺���Ҫ����������
  */
void PokeMotor_Adjust(uint8_t mode)
{
    int16_t PokeCurrent;
    static portTickType LastStruckCheckTick = 0;
    static long LastCheckLocation = 0;
    static portTickType LastStallDealTick = 0;
    portTickType CurrentTick = xTaskGetTickCount();
    
    if(mode)
    {
        //��������ٶ�λ�ü���
        PokeMotorParam.RealSpeed = POKEENCODERCenter - TIM3->CNT;
        TIM3->CNT = POKEENCODERCenter;
        
        //���С��25����Ϊ�ﵽĿ��λ��,�����ڵ���״̬
        if((PokeMotorParam.RealLocation > PokeMotorParam.TargetLocation ? (PokeMotorParam.RealLocation - PokeMotorParam.TargetLocation) : (PokeMotorParam.TargetLocation > PokeMotorParam.RealLocation)) < 25)
        {
            PokeMotorParam.Status = PokeMotorParam_Suit;
        }
        else
        {
            PokeMotorParam.Status = PokeMotorParam_Adjusting;
        }
        
        //ÿ20ms��⿨��
        if(CurrentTick - LastStruckCheckTick >= 200)
        {
            //ֻ�е���״̬���п��ܿ��������п������
            if(PokeMotorParam_Adjusting == PokeMotorParam.Status)
            {
                //20ms���˶�С��50����Ϊ����
                if((PokeMotorParam.RealLocation > LastCheckLocation ? (PokeMotorParam.RealLocation - LastCheckLocation) : (LastCheckLocation - PokeMotorParam.RealLocation)) < 50)
                {
                    //������ת����ʱ����Ϊ100ms����ֹ��η�ת�ۼ�
                    if(CurrentTick - LastStallDealTick > 100)
                    {
                        PokeMotorParam.TargetLocation = PokeMotorParam.RealLocation + PokeMotorParam.TargetLocation > PokeMotorParam.RealLocation ? POKESTRUCKDEALLINES : -POKESTRUCKDEALLINES;
                    }
                    
                    LastStallDealTick = CurrentTick;
                }
            }
            
            LastCheckLocation = PokeMotorParam.RealLocation;
            LastStruckCheckTick = CurrentTick;
        }
        
        
        PokeMotorParam.RealLocation += PokeMotorParam.RealSpeed;
        
        PokeCurrent = Control_PokeIPID();
        
        PokeMotorCurrent(PokeCurrent);
    }
    else
    {
        PokeMotorCurrent(0);
    }
}




