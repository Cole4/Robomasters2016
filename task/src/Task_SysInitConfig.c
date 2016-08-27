
#include "Task_SysInitConfig.h"
#include "OSinclude.h"

#include "Handler.h"

#include "mpu9250dmp.h"

#include "BSP_CAN.h"
#include "BSP_TIM.h"
#include "BSP_DMA.h"
#include "BSP_SPI.h"
#include "BSP_GPIO.h"
#include "BSP_NVIC.h"
#include "BSP_UART.h"

#include "Driver_Bell.h"
#include "Driver_DBUS.h"
#include "Driver_Judge.h"
#include "Driver_Vision.h"
#include "Driver_Chassis.h"
#include "Driver_mpu9250.h"
#include "Driver_Control.h"
#include "Driver_Steering.h"
#include "Driver_PokeMotor.h"
#include "Driver_FricMotor.h"
#include "Driver_CloudMotor.h"
#include "Driver_StatusMachine.h"
#include "Driver_SuperGyroscope.h"

#include "Task_Bell.h"
#include "Task_Monitor.h"
#include "Task_CANSend.h"
#include "Task_Control.h"


#include "Driver_ESP8266.h"
/**
  * @brief  ϵͳ��ʼ������
  * @param  unused
  * @retval void
  */
  
  int kkk = 0, dddd = 3;;
  
  
void Task_SysInitConfig(void *Parameters)
{
    BSP_GPIO_InitConfig();
    BSP_CAN_InitConfig();
    BSP_TIM_InitConfig();
    BSP_UART_InitConfig();
    BSP_DMA_InitConfig();
    BSP_NVIC_InitConfig();
    
    Steering_InitConfig();
    Poke_InitConfig();
    Bell_InitConfig();
    DBUS_InitConfig();
    CloudMotor_InitConfig();
    ControlPID_InitConfig();
    StatusMachine_InitConfig();
    SuperGyo_InitConfig();
    Vision_InitConfig();
    MPU9250_InitConfig();
    FricMotor_InitConfig();
    Chassis_InitConfig();
    
    //��ʱ��֤������������ʼ��
    vTaskDelay(1000);
    MPU9250DMP_InitConfig(0);
    
    //�ȴ����������ǳ�ʼ�����
    vTaskDelay(1000); 
    
    //����CAN���Ͷ���
	Queue_CANSend = xQueueCreate(64, sizeof(CanSend_Type));		
    
    //////////////////////������
    //����������
    xTaskCreate(Task_Monitor,
                "Task_Monitor",
                512,
                NULL,
                4,
                NULL);
    
    //CAN��������
    xTaskCreate(Task_CANSend,
                "Task_CANSend",
                200,
                NULL,
                3,
                NULL);
    
    //��������
    xTaskCreate(Task_Control,
                "Task_Control",
                512,
                NULL,
                2,
                NULL);
                
    //��������������
	xTaskCreate(Task_BellBark,
				"Task_BellCycle",
				64,
				NULL,
				6,
				NULL);
                
    DMA_Cmd(DMA1_Stream0, DISABLE);
    while(DMA_GetCmdStatus(DMA1_Stream0) != DISABLE);
    DMA_SetCurrDataCounter(DMA1_Stream0, DBUSLength + DBUSBackLength);
    DMA_Cmd(DMA1_Stream0, ENABLE);
    
    DMA_Cmd(DMA1_Stream2, DISABLE);
    while(DMA_GetCmdStatus(DMA1_Stream2) != DISABLE);
    DMA_SetCurrDataCounter(DMA1_Stream2, JudgeBufferLength);
    DMA_Cmd(DMA1_Stream2, ENABLE);
    
    Bell_BarkWarning(1, 1);

    vTaskDelay(500);
    
    vTaskDelete(NULL);
}
