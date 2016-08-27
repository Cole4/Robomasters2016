
#define __MOTOR_GLOBALS

#include "Task_CANSend.h"
#include "Driver_Motor.h"
#include "Driver_Control.h"

#include "Handler.h"


/*******************
Yaw��
	���ޣ�4000
	�Ҽ��ޣ�2100
	�����ߣ�3100
    ��������˳ʱ��ת������ת��
    ����������ʱ��ת������ת��
    ���ٶȣ�Z�ᣬ������
Pitch��
	�ϼ��ޣ�7190
	�¼��ޣ�7890
	ˮƽλ��7600
    ��������̧ͷ
    ����������ͷ
    ���ٶȣ�X�ᣬ̧ͷ������ͷ��
*******************/



/**
  * @brief  �����ʼ��
  * @param  void
  * @retval void
  */
void Motor_InitConfig(void)
{
    PitchMotorAngle = PitchCenter;
    YawMotorAngle   = YawCenter;
    
    TIM8->CCR1 = 1000;
    TIM8->CCR2 = 1000;
    
    //�����������Ӧ���ֲ���
    GPIO_ResetBits(GPIOA, GPIO_Pin_5);
    //�������������λ�ó�ʼ��
    TIM3->CNT = ENCODERCenter;
    //��������ٶȳ�ʼ��
    PokeSpeed = 0;
    //����Ƕȳ�ʼ��
    SteeringAngle(0);
}
    
    
    
/**
  * @brief  ��̨�����������
  * @param  pitch�������yaw�����
  * @retval void
  */
void CloudMotorCurrent(int16_t Pitch, int16_t Yaw)
{
    static CanSend_Type   SendData;
    
    SendData.CANx = 2;
    
    SendData.SendCanTxMsg.DLC   =   8;
    SendData.SendCanTxMsg.IDE   =   CAN_ID_STD;
    SendData.SendCanTxMsg.RTR   =   CAN_RTR_Data;
    SendData.SendCanTxMsg.StdId =   COULDCONTROLID;
    
    SendData.SendCanTxMsg.Data[0] = Yaw >> 8;
    SendData.SendCanTxMsg.Data[1] = Yaw;
    SendData.SendCanTxMsg.Data[2] = Pitch >> 8;
    SendData.SendCanTxMsg.Data[3] = Pitch;
    SendData.SendCanTxMsg.Data[4] = 0;
    SendData.SendCanTxMsg.Data[5] = 0;
    SendData.SendCanTxMsg.Data[6] = 0;
    SendData.SendCanTxMsg.Data[7] = 0;
    
    xQueueSend(Queue_CANSend, &SendData, 10);
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
    
    if(Current >= 0)
    {
        GPIO_ResetBits(GPIOA, GPIO_Pin_5);
        TIM5->CCR2 = S;
    }
    else
    {
        GPIO_SetBits(GPIOA, GPIO_Pin_5);
        TIM5->CCR2 = -S;
    }
}


/**
  * @brief  ǹĦ������ͣ
  * @param  0 ֹͣ        1 ����
  * @retval void
  */
void GunFric_Control(uint8_t Control)
{
    if(Control)
    {
        TIM8->CCR1 = 1000 + GUNWORKSPEED;
        TIM8->CCR2 = 1000 + GUNWORKSPEED;
    }
    else
    {
        TIM8->CCR1 = 1000;
        TIM8->CCR2 = 1000;
    }
}


/**
  * @brief  ���������ͣ
  * @param  0 ֹͣ        1 ��
  * @retval void
  */
void Poke_Control(uint8_t status)
{
    if(status)
    {
        //Ħ����������ת�ſɷ���
        if(TIM8->CCR1 > 50)
        {
            PokeSpeedTarget = POKEWORKSPEED;
        }
    }
    else
    {
        PokeSpeedTarget = 0;
    }
}



/**
  * @brief  ����Ƕȿ���
  * @param  �Ƕ�
  * @retval void
  */
void SteeringAngle(uint16_t angle)
{
    
}


