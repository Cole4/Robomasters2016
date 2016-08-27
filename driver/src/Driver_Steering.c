
#include "Driver_Steering.h"



/**
  * @brief  �����ʼ��
  * @param  void
  * @retval void
  */
void Steering_InitConfig(void)
{
    TIM8->CCR4 = 2200;      //�رղ���
}


/**
  * @brief  ����Ƕȿ���
  * @param  0 �رղ���          1 �򿪲���
  * @retval void 
  */
void Steering_Control(uint8_t status)
{
    if(status)
    {
        TIM8->CCR4 = 800;
    }
    else
    {
        TIM8->CCR4 = 2200;
    }
}








