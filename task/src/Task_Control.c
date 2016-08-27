
#include "Task_Control.h"

#include "Config.h"

#include "Driver_DBUS.h"
#include "Driver_Motor.h"
#include "Driver_vision.h"
#include "Driver_Chassis.h"
#include "Driver_mpu9250.h"
#include "Driver_Control.h"
#include "Driver_StatusMachine.h"
#include "Driver_SuperGyroscope.h"

/**
  * @brief  ��������
  * @param  ubused
  * @retval void
  */
float RC_EncoderYawTargetSum = YawCenter;           //ң�����ǶȻ���
float RC_EncoderPitchTargetSum = PitchCenter;       //ң�����ǶȻ���
  
void Task_Control(void *Parameters)
{
    int16_t PokeCurrent = 0;
    int16_t YawMotorCurrent = 0, PitchMotorCurrent = 0;
    AngleU_Struct TargetEncoderAngle;
    
    int16_t Counter = 0;
    portTickType LastTick = 0;
    
    for(;;)
    {
        LastTick = xTaskGetTickCount();
        
/************************  ��  ��̬����  �� ************************/
        MPU9250_Update();
/************************  ��  ��̬����  �� ************************/
/**************************************************************************************************/
/*********************  ��  ״̬��״̬����  �� *********************/
        StatusMachine_Update();
/*********************  ��  ״̬��״̬����  �� *********************/
/**************************************************************************************************/
/*********************  ��  ����״̬������  �� *********************/
        if(ControlStatus == ControlStatus_KM)
        {
            //��̨���� 
            if(CloudStatus == CloudStatus_Auto)     //�Զ�ģʽ
            {
            //Ԥ��
//            ForcastOnce(350, 400, &ForcastAngle, 1);
            
            
//                //ֱ�����
//                ForcastAngle = RecToPolar(EnemyDataBuffer[EnemyDataBufferPoint].X, 
//                                            EnemyDataBuffer[EnemyDataBufferPoint].Y, 
//                                            EnemyDataBuffer[EnemyDataBufferPoint].Z,
//                                            1);
//                
//            YawAngleTarget = ForcastAngle.H;
//            PitchAngleTarget = ForcastAngle.V;
            
            
//            YawAngleTarget = 0;
//            PitchAngleTarget = PitchCenter;
            
            //��������������������Ƿ���
//            if(
            }
            else    //����ģʽ
            {
//                //Pitch�ۼ�
//                ABSTargetPitch += DBUS_ReceiveData.mouse.y / 6.0F;
//                //Pitch�޷�
//                ABSTargetPitch = ABSTargetPitch > PitchDOWNLimit ? PitchDOWNLimit : ABSTargetPitch;
//                ABSTargetPitch = ABSTargetPitch < PitchUPLimit ? PitchUPLimit : ABSTargetPitch;
//                
//                //YawĿ��ʵ��ֵ�ۼ�
//                ABSTargetYaw -= DBUS_ReceiveData.mouse.x / 40.0F + DBUS_ReceiveData.ch3 / 1500.0F;
//                //Yaw�������Ŀ��ֵ����
//                YawEncoderBuffer = (ABSTargetYaw - SuperGyoAngle) * 22.75556F + YawCenter;
//                //Yaw�޷�
//                YawEncoderBuffer = YawEncoderBuffer > YawLEFTLimit ? YawLEFTLimit : YawEncoderBuffer;
//                YawEncoderBuffer = YawEncoderBuffer < YawRIGHTLimit ? YawRIGHTLimit : YawEncoderBuffer;
//                
//                EncoderTargetPitch = PitchSum;
//                EncoderTargetYaw = YawEncoderBuffer;
            }
        }
        //ң��������
//        if(DBUS_ReceiveData.switch_left == 1)
//        {
            if(DBUS_ReceiveData.switch_left == 1)
            {
                RC_EncoderPitchTargetSum += DBUS_ReceiveData.ch4 / 20.0F;
                RC_EncoderPitchTargetSum = RC_EncoderPitchTargetSum > PitchUPLimit ? PitchUPLimit : RC_EncoderPitchTargetSum;
                RC_EncoderPitchTargetSum = RC_EncoderPitchTargetSum < PitchDOWNLimit ? PitchDOWNLimit : RC_EncoderPitchTargetSum;
                
                RC_EncoderYawTargetSum -= DBUS_ReceiveData.ch3 / 20.0F;
                RC_EncoderYawTargetSum = RC_EncoderYawTargetSum > YawLEFTLimit ? YawLEFTLimit : RC_EncoderYawTargetSum;
                RC_EncoderYawTargetSum = RC_EncoderYawTargetSum < YawRIGHTLimit ? YawRIGHTLimit : RC_EncoderYawTargetSum;
                
                EncoderTargetPitch = RC_EncoderPitchTargetSum;
                EncoderTargetYaw = RC_EncoderYawTargetSum;
            }
            else if(DBUS_ReceiveData.switch_left == 2)
            {
                TargetEncoderAngle = RecToPolar(EnemyDataBuffer[EnemyDataBufferPoint].X, EnemyDataBuffer[EnemyDataBufferPoint].Y, EnemyDataBuffer[EnemyDataBufferPoint].Z, 1);
                Control_SetTargetPitch(TargetEncoderAngle.V, Encoder);
                Control_SetTargetYaw(TargetEncoderAngle.H, Encoder);
                
            }
//        }
        
            
        //ǹ����
        if(GunStatus == GunStatus_Motor)
        {
            GunFric_Control(1);
            Poke_Control(0);
        }
        else if(GunStatus == GunStatus_Shot)
        {
            GunFric_Control(1);
            Poke_Control(1);
        }
        else
        {
            GunFric_Control(0);
            Poke_Control(0);
        }

/*********************  ��  ����״̬������  �� *********************/
/**************************************************************************************************/
/**********************  ��  �������PID  �� ***********************/
        if(Counter >= 5)
        {
            Counter = 0;
        }
        else
        {
            Counter++;
        }
        
        if(Counter == 0)
        {
            //�������ٶȼ���
            PokeSpeed = ENCODERCenter - TIM3->CNT;
            TIM3->CNT = ENCODERCenter;
            
            //�������PID
            PokeCurrent = Control_PokePID();
        }
/*********************  ��  �������PID  ��  ***********************/
/**************************************************************************************************/
/*********************  ��  ��̨PID      ��  **********************/
        YawMotorCurrent = Control_YawPID();
        PitchMotorCurrent = Control_PitchPID();
/*********************  ��  ��̨PID      ��  **********************/
/**************************************************************************************************/
/*********************  ��   �������    ��  **********************/
        if(ControlStatus == ControlStatus_Protect)
        {
            //��̨�����������
            CloudMotorCurrent(0, 0);
            //��������ٶȿ���
            PokeMotorCurrent(0);
        }
        else
        {
            //��̨�����������
            CloudMotorCurrent(PitchMotorCurrent, YawMotorCurrent);
            //��������ٶȿ���
            PokeMotorCurrent(PokeCurrent);
        }
/*********************  ��   �������    ��  **********************/
/**************************************************************************************************/
        
		vTaskDelayUntil(&LastTick, 5 / portTICK_RATE_MS);
    }
}



