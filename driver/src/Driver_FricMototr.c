
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
        TIM8->CCR1 = 1000 + FRICMOTORWORKINGSPEED;
        TIM8->CCR2 = 1000 + FRICMOTORWORKINGSPEED;
    }
    else
    {
        TIM8->CCR1 = 1000;
        TIM8->CCR2 = 1000;
    }
}








