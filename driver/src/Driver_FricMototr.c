
#define __DRIVER_FRICMOTOR_GLOBALS

#include "Config.h"
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
    
    FricStatus = FricStatus_Stop;
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








