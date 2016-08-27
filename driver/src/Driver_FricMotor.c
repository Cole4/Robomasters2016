
#define __DRIVER_FRICMOTOR_GLOBALS

#include "Config.h"
#include "Handler.h"
#include "Task_CANSend.h"
#include "Driver_FricMotor.h"


/**
  * @brief  Ħ���ֳ�ʼ��
  * @param  void
  * @retval void
  */
void FricMotor_InitConfig(void)
{
    //�ٶȳ�ʼ��Ϊ0
    TIM8->CCR1 = 1000;
    TIM8->CCR2 = 1000;
    
//СӢ��ǹ��һ��������Ħ����
#if INFANTRY == 6
    ArtilleryFricRealSpeed[0] = 0;
    ArtilleryFricRealSpeed[1] = 0;
    ArtilleryFricTargetSpeed = 0;
#endif
}


/**
  * @brief  ǹĦ������ͣ
  * @param  0 ֹͣ        1 ����        2 ��Ұģʽ
  * @retval void
  */
void GunFric_Control(uint8_t Control)
{
    if(Control == 1)
    {
        TIM8->CCR1 = 1000 + FRICMOTORWORKINGSPEED;
        TIM8->CCR2 = 1000 + FRICMOTORWORKINGSPEED;
    }
    else if(Control == 2)
    {
        TIM8->CCR1 = 1000 + 1000;
        TIM8->CCR2 = 1000 + 1000;
    }
    else
    {
        TIM8->CCR1 = 1000;
        TIM8->CCR2 = 1000;
    }
}


//СӢ��ǹ��һ��������Ħ����
#if INFANTRY == 6
/**
  * @brief  ��Ħ�����ٶȵ���
  * @param  Ŀ���ٶ�
  * @retval void
  */
void FricArtillerySpeed_Adjust(uint8_t Target)
{
    int16_t Current[2];
    
    if(Target)
    {
        if(ARTILLERYACCBELOWSPEED > ArtilleryFricRealSpeed[0])
        {
            Current[0] = ARTILLERYFRICMAXCURREN;
        }
        else
        {
            Current[0] = ARTILLERYFRICMINCURRENOFTMAXSPEED;
        }
        
        if(ARTILLERYACCBELOWSPEED > ArtilleryFricRealSpeed[1])
        {
            Current[1] = ARTILLERYFRICMAXCURREN;
        }
        else
        {
            Current[1] = ARTILLERYFRICMINCURRENOFTMAXSPEED;
        }
    }
    else
    {
        Current[0] = 0;
        Current[1] = 0;
    }
    
    FricArtilleryMotorCurrent(Current[0], Current[1]);
}



/**
  * @brief  ��Ħ���ֵ����������
  * @param  ����
  * @retval void
  */
void FricArtilleryMotorCurrent(int16_t LeftArtilleryCurrent, int16_t RightArtilleryCurrent)
{
    CanSend_Type   SendData;
    
//    LeftArtilleryCurrent = LeftArtilleryCurrent > 30000 ? 30000 : LeftArtilleryCurrent;
//    RightArtilleryCurrent = RightArtilleryCurrent < -30000 ? -30000 : RightArtilleryCurrent;

#if CANPORT == 1
    SendData.CANx = 1;
#else
    SendData.CANx = 2;
#endif
    
    SendData.SendCanTxMsg.DLC   =   8;
    SendData.SendCanTxMsg.IDE   =   CAN_ID_STD;
    SendData.SendCanTxMsg.RTR   =   CAN_RTR_Data;
    SendData.SendCanTxMsg.StdId =   ARTILLERYFRICCONTROLCANID;
    
    SendData.SendCanTxMsg.Data[0] = (-LeftArtilleryCurrent) >> 8;
    SendData.SendCanTxMsg.Data[1] = (-LeftArtilleryCurrent);
    SendData.SendCanTxMsg.Data[2] = RightArtilleryCurrent >> 8;
    SendData.SendCanTxMsg.Data[3] = RightArtilleryCurrent;
    
    xQueueSend(Queue_CANSend, &SendData, 10);
}
#endif











