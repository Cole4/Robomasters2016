
#include "Task_Control.h"

#include "Config.h"

#include "mpu9250dmp.h"
#include "Driver_DBUS.h"
#include "Driver_vision.h"
#include "Driver_Chassis.h"
#include "Driver_mpu9250.h"
#include "Driver_Control.h"
#include "Driver_Steering.h"
#include "Driver_PokeMotor.h"
#include "Driver_FricMotor.h"
#include "Driver_CloudMotor.h"
#include "Driver_StatusMachine.h"
#include "Driver_SuperGyroscope.h"


/**
  * @brief  ������������5ms��
  * @param  ubused
  * @retval void
  */
void Task_Control(void *Parameters)
{
    portTickType CurrentControlTick = 0;                //��ǰϵͳʱ��
    uint32_t dmpresetCounter;                            //dmp����������
	uint8_t JumpToRCFlag = 1, JumpToKMFlag = 1, JumpToProtectFlag = 1;
    
    for(;;)
    {
        CurrentControlTick = xTaskGetTickCount();
        
/************************  ��  ��̬����  �� ************************/
        MPU9250_Update();
        
        //DMPÿ5s�����������ɵ��
        if(dmpresetCounter >= 5000)
        {
            dmpresetCounter = 0;
            mpu_set_dmp_state(0);
            mpu_set_dmp_state(1);
        }
        else
        {
            dmpresetCounter++;
        }
        
        //Yaw��ʵ�ʾ��ԽǶ�
        CloudParam.Yaw.RealABSAngle = SuperGyoParam.Angle + ((int16_t)CloudParam.Yaw.RealEncoderAngle - YawEncoderCenter) * 0.043945F;
        //Pitch��ʵ�ʾ��ԽǶ�
        CloudParam.Pitch.RealABSAngle = Position.Euler.Pitch;
        
/************************  ��  ��̬����  �� ************************/
/**************************************************************************************************/
/*********************  ��  ״̬��״̬����  �� *********************/
        StatusMachine_Update();
/*********************  ��  ״̬��״̬����  �� *********************/
/**************************************************************************************************/
/*********************  ��  ����״̬������  �� *********************/
        
#if DEBUGECONTROLRC == 1
		
        PokeMotor_Adjust();
		
#else
		
        if(ControlMode_RC == ControlMode)
        {
			//������ģʽת��ң��ģʽ
			if(JumpToRCFlag)
			{
				CloudParam.Yaw.TargetABSAngle = CloudParam.Yaw.RealABSAngle;
				PokeMotorParam.TargetLocation = PokeMotorParam.RealLocation;
			}
			
			JumpToRCFlag = 0;
			JumpToKMFlag = 1;
			JumpToProtectFlag = 1;
			
            Control_RCMode();
        }
        else if(ControlMode_KM == ControlMode)
        {
			//������ģʽת�����ģʽ
			if(JumpToKMFlag)
			{
				CloudParam.Yaw.TargetABSAngle = CloudParam.Yaw.RealABSAngle;
				PokeMotorParam.TargetLocation = PokeMotorParam.RealLocation;
			}
			
			JumpToRCFlag = 1;
			JumpToKMFlag = 0;
			JumpToProtectFlag = 1; 
			
            Control_KMMode();
        }
        else
        {
			//������ģʽת�뱣��ģʽ
			if(JumpToProtectFlag)
			{
				CloudParam.Yaw.TargetABSAngle = CloudParam.Yaw.RealABSAngle;
			}
			
			JumpToRCFlag = 1;
			JumpToKMFlag = 1;
			JumpToProtectFlag = 0;
			
            Control_ProtectMode();
        }
#endif
        
/*********************  ��  ����״̬������  �� *********************/
/**************************************************************************************************/
/**********************  ��  �����������   �� ***********************/
/*********************  ��  �������PID  ��  ***********************/
/**************************************************************************************************/
/*********************  ��  ��̨PID      ��  **********************/
/*********************  ��  ��̨PID      ��  **********************/
/**************************************************************************************************/
/*********************  ��   �������    ��  **********************/
/*********************  ��   �������    ��  **********************/
/**************************************************************************************************/
        
		vTaskDelayUntil(&CurrentControlTick, 5 / portTICK_RATE_MS);
    }
}


/**
  * @breif  ң�ؿ��ƺ���
  * @param  void
  * @retval void
  */
static void Control_RCMode(void)
{
    Cloud_YawAngleSet(CloudParam.Yaw.TargetABSAngle - DBUS_ReceiveData.ch3 / 500.0F, AngleMode_ABS);
    Cloud_PitchAngleSet(CloudParam.Pitch.TargetABSAngle + DBUS_ReceiveData.ch4 / 120.0F);
    
    Cloud_Adjust(1);
    
    Chassis_TargetDirectionSet(CloudParam.Yaw.TargetABSAngle);
    Chassis_SpeedSet(DBUS_ReceiveData.ch2, DBUS_ReceiveData.ch1);
    Chassis_Adjust(1);
	
	if(FricStatus_Working == FricStatus)
	{
		GunFric_Control(1);
	}
	else
	{
		GunFric_Control(0);
	}
	
	Steering_Control(2);
}


/**
  * @breif  ������ƺ���
  * @param  void
  * @retval void
  */
static void Control_KMMode(void)
{
    
}


/**
  * @breif  ����ģʽ���ƺ���
  * @param  void
  * @retval void
  */
static void Control_ProtectMode(void)
{
    Cloud_Adjust(0);
    Chassis_Adjust(0);
	Steering_Control(2);
}











