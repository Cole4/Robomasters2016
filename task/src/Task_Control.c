
#include "Task_Control.h"

#include "Config.h"

#include "mpu9250dmp.h"
#include "Driver_DBUS.h"
#include "Driver_Judge.h"
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

#include <math.h>


static void Control_KMSubschemaNormal(void);
static void Control_KMSubschemaSupply(void);
static void Control_KMSubschemaHalfauto(void);
static void Control_KMSubschemaSwing(void);
static void Control_KMSubschemaBigsample(void);
static void Control_KMSubschemaFullauto(void);
static void Control_KMSubschemaCircle(void);


//״̬�л���־λ
static uint8_t JumpToRCFlag = 1, JumpToKMFlag = 1, JumpToProtectFlag = 1;
    
    
/**
  * @brief  ������������5ms��
  * @param  ubused
  * @retval void
  */
void Task_Control(void *Parameters)
{
    portTickType CurrentControlTick = 0;                //��ǰϵͳʱ��
    uint32_t dmpresetCounter;                            //dmp����������
    
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
/*********************  ��  ��������������  �� *********************/
        DBUS_ButtonCheckJump(CurrentControlTick);
/*********************  ��  ״̬��״̬����  �� *********************/
/**************************************************************************************************/
/*********************  ��  Ħ����  �� *********************/
	
        //Ħ���ֿ���
        if(FricStatus_Working == FricStatus)
        {
            GunFric_Control(1);
#if INFANTRY == 6
            FricArtillerySpeed_Adjust(ARTILLERYFRICSPEED);
#endif
        }
        else if(FricStatus_Crazy == FricStatus)
        {
            GunFric_Control(2);
#if INFANTRY == 6
            FricArtillerySpeed_Adjust(ARTILLERYFRICSPEED);
#endif
        }
        else
        {
            GunFric_Control(0);
#if INFANTRY == 6
            FricArtillerySpeed_Adjust(0);
#endif
        }
/*********************  ��  ״̬��״̬����  �� *********************/
/**************************************************************************************************/
/*********************  ��  ����״̬������  �� *********************/
        
        //����ģʽ����
        if(ControlMode_RC == ControlMode)
        {
			//������ģʽת��ң��ģʽ
			if(JumpToRCFlag)
			{
                TIM3->CNT = POKEENCODERCenter;              //���������ʱ����λ����ֹ�ı�ģʽʱת��
				CloudParam.Yaw.TargetABSAngle = SuperGyoParam.Angle;
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
                TIM3->CNT = POKEENCODERCenter;              //���������ʱ����λ����ֹ�ı�ģʽʱת��
				CloudParam.Yaw.TargetABSAngle = SuperGyoParam.Angle;
				PokeMotorParam.TargetLocation = PokeMotorParam.RealLocation;
			}
			
			JumpToRCFlag = 1;
			JumpToKMFlag = 0;
			JumpToProtectFlag = 1; 

//Debugģʽ�£��˴�����debug����ͨģʽ�����ڼ������
#if DEBUGECONTROLRC == 1
            Control_KMSubschemaHalfauto();
#else		
            Control_KMMode();
#endif
        }
        else
        {
			//������ģʽת�뱣��ģʽ
			if(JumpToProtectFlag)
			{
				CloudParam.Yaw.TargetABSAngle = CloudParam.Yaw.RealABSAngle;
				PokeMotorParam.TargetLocation = PokeMotorParam.RealLocation;
			}
			
			JumpToRCFlag = 1;
			JumpToKMFlag = 1;
			JumpToProtectFlag = 0;
			
            Control_ProtectMode();
        }
        
/*********************  ��  ����״̬������  �� *********************/
/**************************************************************************************************/
/*********************  ��  �����������   �� ***********************/
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
    //��̨����
    Cloud_YawAngleSet(CloudParam.Yaw.TargetABSAngle - DBUS_ReceiveData.ch3 / 500.0F, AngleMode_ABS);
    Cloud_PitchAngleSet(CloudParam.Pitch.TargetABSAngle + DBUS_ReceiveData.ch4 / 120.0F);
    Cloud_Adjust(1);
    
    //���̿���
    Chassis_TargetDirectionSet(CloudParam.Yaw.TargetABSAngle);
    Chassis_SpeedSet(DBUS_ReceiveData.ch2, DBUS_ReceiveData.ch1);
    Chassis_Adjust(1);
	
    //������ſ���
	Steering_Control(2);
    
#if INFANTRY == 6
    if(DBUS_ReceiveData.switch_right == 2)
    {
        Poke_CylinderAdjust(1);
    }
    else
    {
        Poke_CylinderAdjust(0);
    }
#else
    if(DBUS_ReceiveData.switch_right == 2)
    {
        PokeMotor_Step();
    }
    PokeMotor_Adjust(1);
#endif
    
}


/**
  * @breif  ������ƺ���
  * @param  void
  * @retval void
  */
static void Control_KMMode(void)
{  
    if(KMSubschema_Normal == KMSubschema)
    {
        Control_KMSubschemaNormal();
    }
    else if(KMSubschema_Supply == KMSubschema)
    {
        Control_KMSubschemaSupply();
    }
    else if(KMSubschema_Halfauto == KMSubschema)
    {
        Control_KMSubschemaHalfauto();
    }
    else if(KMSubschema_Swing == KMSubschema)
    {
        Control_KMSubschemaSwing();
    }
    else if(KMSubschema_Bigsample == KMSubschema)
    {
        Control_KMSubschemaBigsample();
    }
    else if(KMSubschema_Fullauto == KMSubschema)
    {
        Control_KMSubschemaFullauto();
    }
    else if(KMSubschema_Circle == KMSubschema)
    {
        Control_KMSubschemaCircle();
    }
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
    PokeMotor_Adjust(0);
#if INFANTRY == 6
    FricArtilleryMotorCurrent(0, 0);
#endif
}


/**
  * @brief  ����ģʽ��ģʽ����Normal
  * @param  void
  * @retval void
  */
static void Control_KMSubschemaNormal(void)
{
    int8_t Xspeed = 0, Yspeed = 0;
    float TargetYaw;
    
    //��̨����
    if(DBUS_CheckPush(KEY_Q))
    {
        TargetYaw = CloudParam.Yaw.TargetABSAngle + 1.0F;
    }
    else if(DBUS_CheckPush(KEY_E))
    {
        TargetYaw = CloudParam.Yaw.TargetABSAngle - 1.0F;
    }
    else
    {
        TargetYaw = CloudParam.Yaw.TargetABSAngle - DBUS_ReceiveData.mouse.x / 20.0F;
    }
    Cloud_YawAngleSet(TargetYaw, AngleMode_ABS);
    Cloud_PitchAngleSet(CloudParam.Pitch.TargetABSAngle - DBUS_ReceiveData.mouse.y / 20.0F);
    Cloud_Adjust(1);
    
    //���̿���
    if(DBUS_CheckPush(KEY_W))
    {
        Xspeed = 1;
    }
    else if(DBUS_CheckPush(KEY_S))
    {
        Xspeed = -1;
    }
    else
    {
        Xspeed = 0;
    }
    
    if(DBUS_CheckPush(KEY_D))
    {
        Yspeed = 1;
    }
    else if(DBUS_CheckPush(KEY_A))
    {
        Yspeed = -1;
    }
    else
    {
        Yspeed = 0;
    }
    
    Chassis_TargetDirectionSet(CloudParam.Yaw.TargetABSAngle);
    Chassis_SpeedSet(MAXWORKINGSPEED * Xspeed, MAXWORKINGSPEED * Yspeed);
    Chassis_Adjust(1);
	
    //������ſ���
	Steering_Control(0);
    
#if INFANTRY == 6
    if(DBUS_ReceiveData.mouse.press_left)
    {
        Poke_CylinderAdjust(1);
    }
    else
    {
        Poke_CylinderAdjust(0);
    }
#else
    if(DBUS_ReceiveData.mouse.press_lef)
    {
        PokeMotor_Step();
    }
    PokeMotor_Adjust(1);
#endif
}


/**
  * @brief  ����ģʽ��ģʽ����Supply
  * @param  void
  * @retval void
  */
static void Control_KMSubschemaSupply(void)
{
    int8_t Xspeed = 0, Yspeed = 0;
    float TargetYaw;
    
    //��̨����
    if(DBUS_CheckPush(KEY_Q))
    {
        TargetYaw = CloudParam.Yaw.TargetABSAngle + 0.2F;
    }
    else if(DBUS_CheckPush(KEY_E))
    {
        TargetYaw = CloudParam.Yaw.TargetABSAngle - 0.2F;
    }
    else
    {
        TargetYaw = CloudParam.Yaw.TargetABSAngle - DBUS_ReceiveData.mouse.x / 100.0F;
    }
    Cloud_YawAngleSet(TargetYaw, AngleMode_ABS);
    Cloud_PitchAngleSet(DEPOTABSPITCH);
    Cloud_Adjust(1);
    
    //���̿���
    if(DBUS_CheckPush(KEY_W))
    {
        Xspeed = 1;
    }
    else if(DBUS_CheckPush(KEY_S))
    {
        Xspeed = -1;
    }
    else
    {
        Xspeed = 0;
    }
    
    if(DBUS_CheckPush(KEY_D))
    {
        Yspeed = 1;
    }
    else if(DBUS_CheckPush(KEY_A))
    {
        Yspeed = -1;
    }
    else
    {
        Yspeed = 0;
    }
    
    Chassis_TargetDirectionSet(CloudParam.Yaw.TargetABSAngle);
    Chassis_SpeedSet(SNEAKSPEED * Xspeed, SNEAKSPEED * Yspeed);
    Chassis_Adjust(1);
	
    //������ſ���
	Steering_Control(1);
}


/**
  * @brief  ����ģʽ��ģʽ����Halfauto
  * @param  void
  * @retval void
  */
#define LastSpeedLength     6
#define ForcastCloud        0


    AngleF_Struct CurrentAngle;
    AngleF_Struct LastAngle[LastSpeedLength];
    double FeendS = 0;
    float FeedParam = 60;
static void Control_KMSubschemaHalfauto(void)
{
#if ForcastCloud == 1
    
    int8_t index;
    
#if INFANTRY == 6
    if(DBUS_ReceiveData.switch_right == 2)
    {
        Poke_CylinderAdjust(1);
    }
    else
    {
        Poke_CylinderAdjust(0);
    }
#else
    if(DBUS_ReceiveData.switch_right == 2)
    {
        PokeMotor_Step();
    }
    PokeMotor_Adjust(1);
#endif
    
    //���̿���
    Chassis_Adjust(0);
    
    //Ԥ�н��
    ForcastOnce(300, 150, &CurrentAngle, 0);
    
    //��̨�Ƕ��趨
    Cloud_YawAngleSet(SuperGyoParam.Angle + CurrentAngle.H, AngleMode_ABS);
    Cloud_PitchAngleSet(CurrentAngle.V);
    
    //�ٶȲ�������
    FeendS = (CurrentAngle.H - LastAngle[LastSpeedLength - 1].H);
    
    //��̨����
    Cloud_AutoAdjust(FeendS * FeedParam, 1);
    
    //��ʷֵ����
    for (index = LastSpeedLength - 1; index > 0; index--)
    {
        LastAngle[index] = LastAngle[index - 1];
    }
    LastAngle[0] = CurrentAngle;
    
#else
    
    int8_t index;
    
#if INFANTRY == 6
    if(DBUS_ReceiveData.switch_right == 2)
    {
        Poke_CylinderAdjust(1);
    }
    else
    {
        Poke_CylinderAdjust(0);
    }
#else
    if(DBUS_ReceiveData.switch_right == 2)
    {
        PokeMotor_Step();
    }
    PokeMotor_Adjust(1);
#endif
    
    //���̿���
    Chassis_Adjust(0);
    
    //�Ƕ�ת��
    CurrentAngle = RecToPolar(EnemyDataBuffer[EnemyDataBufferPoint].X, EnemyDataBuffer[EnemyDataBufferPoint].Y, EnemyDataBuffer[EnemyDataBufferPoint].Z, 0, PitchEncoderCenter, 1);
    
    //��̨�Ƕ��趨
    Cloud_YawAngleSet(SuperGyoParam.Angle + CurrentAngle.H, AngleMode_ABS);
    Cloud_PitchAngleSet(CurrentAngle.V);
    
    //�ٶȲ�������
    FeendS = (CurrentAngle.H - LastAngle[LastSpeedLength - 1].H);
    
    //��̨����
    Cloud_AutoAdjust(FeendS * FeedParam, 1);
    
    //��ʷֵ����
    for (index = LastSpeedLength - 1; index > 0; index--)
    {
        LastAngle[index] = LastAngle[index - 1];
    }
    LastAngle[0] = CurrentAngle;
#endif
}


/**
  * @brief  ����ģʽ��ģʽ����Swing
  * @param  void
  * @retval void
  */
static void Control_KMSubschemaSwing(void)
{
    static uint8_t SwingDir = 0;            //ҡ�ڷ���  1��   0��
    int8_t Xspeed = 0, Yspeed = 0;
    float TargetYaw;
    float SwingLimitLeft, SwingLimitRight;
    float TargetRealAngle;
    
    //��̨����
    if(DBUS_CheckPush(KEY_Q))
    {
        TargetYaw = CloudParam.Yaw.TargetABSAngle + 1.0F;
    }
    else if(DBUS_CheckPush(KEY_E))
    {
        TargetYaw = CloudParam.Yaw.TargetABSAngle - 1.0F;
    }
    else
    {
        TargetYaw = CloudParam.Yaw.TargetABSAngle - DBUS_ReceiveData.mouse.x / 20.0F;
    }
    Cloud_YawAngleSet(TargetYaw, AngleMode_ABS);
    Cloud_PitchAngleSet(CloudParam.Pitch.TargetABSAngle - DBUS_ReceiveData.mouse.y / 20.0F);
    Cloud_Adjust(1);
    
    //����Ŀ��Ƕ����ã�����ҡ��
    SwingLimitLeft = CloudParam.Yaw.TargetABSAngle + SWINGMODELIMIT;
    SwingLimitRight = CloudParam.Yaw.TargetABSAngle - SWINGMODELIMIT;
    if(SwingDir)
    {
        if(SwingLimitLeft > SuperGyoParam.Angle)
        {
            Chassis_TargetDirectionSet(ChassisParam.TargetABSAngle + SWINGMODEOMEGA / 200.0F);
        }
        else
        {
            Chassis_TargetDirectionSet(ChassisParam.TargetABSAngle - SWINGMODEOMEGA / 200.0F);
            SwingDir = 0;
        }
    }
    else
    {
        if(SwingLimitRight < SuperGyoParam.Angle)
        {
            Chassis_TargetDirectionSet(ChassisParam.TargetABSAngle - SWINGMODEOMEGA / 200.0F);
        }
        else
        {
            Chassis_TargetDirectionSet(ChassisParam.TargetABSAngle + SWINGMODEOMEGA / 200.0F);
            SwingDir = 1;
        }
    }
     
    //����XY�ٶ����ã���������̨����ǰ��
    if(DBUS_CheckPush(KEY_W))
    {
        Xspeed = 1;
    }
    else if(DBUS_CheckPush(KEY_S))
    {
        Xspeed = -1;
    }
    else
    {
        Xspeed = 0;
    }
    
    if(DBUS_CheckPush(KEY_D))
    {
        Yspeed = -1;
    }
    else if(DBUS_CheckPush(KEY_A))
    {
        Yspeed = 1;
    }
    else
    {
        Yspeed = 0;
    }
    
    TargetRealAngle = (CloudParam.Yaw.RealABSAngle - SuperGyoParam.Angle) * 0.0174533F;
    Chassis_SpeedSet(SNEAKSPEED * Xspeed * cos(TargetRealAngle) + SNEAKSPEED * Yspeed * sin(TargetRealAngle), 
                    -SNEAKSPEED * Xspeed * sin(TargetRealAngle) - SNEAKSPEED * Yspeed * cos(TargetRealAngle));
    
    Chassis_Adjust(1);
}

  
/**
  * @brief  ����ģʽ��ģʽ����Bigsample
  * @param  void
  * @retval void
  */
static void Control_KMSubschemaBigsample(void)
{
    
}


/**
  * @brief  ����ģʽ��ģʽ����Fullauto
  * @param  void
  * @retval void
  */
static void Control_KMSubschemaFullauto(void)
{
    
}


/**
  * @brief  ����ģʽ��ģʽ����Circle
  * @param  void
  * @retval void
  */
static void Control_KMSubschemaCircle(void)
{
    static int8_t CircleDir = 1;
    
    if(DBUS_CheckPush(KEY_Q | KEY_A))
    {
        CircleDir = 1;
    }
    else if(DBUS_CheckPush(KEY_E | KEY_D))
    {
        CircleDir = -1;
    }
    
    if(xTaskGetTickCount() - InfantryJudge.LastHartTick < CIRCLEMODEDELAY)
    {
        Cloud_YawAngleSet(CloudParam.Yaw.TargetABSAngle + CircleDir * CIRCLEMODEOMEGA / 200.0F, AngleMode_ABS);
    }
    
    Cloud_Adjust(1);
    
    //���̿���
    Chassis_TargetDirectionSet(CloudParam.Yaw.TargetABSAngle);
    Chassis_SpeedSet(0, 0);
    Chassis_Adjust(1);
}
























