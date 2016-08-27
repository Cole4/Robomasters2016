
#define __CLOUDMOTOR_GLOBALS

#include "Config.h"
#include "Task_CANSend.h"
#include "Driver_Control.h"
#include "Driver_CloudMotor.h"
#include "Driver_SuperGyroscope.h"

#include "Handler.h"


/*******************
���������ͷ�ļ��궨��
*******************/



/**
  * @brief  �����ʼ��
  * @param  void
  * @retval void
  */
void CloudMotor_InitConfig(void)
{
    CloudParam.Pitch.EncoderTargetAngle = PitchCenter;
    CloudParam.Pitch.ABSTargetAngle     = 0;
    CloudParam.Pitch.AngleMode          = AngleMode_Encoder;
    CloudParam.Pitch.FrameCounter       = 0;
    CloudParam.Pitch.FrameRate          = 0;
    CloudParam.Pitch.RealEncoderAngle   = PitchCenter;
    
    CloudParam.Yaw.EncoderTargetAngle   = YawCenter;
    CloudParam.Yaw.ABSTargetAngle       = 0;
    CloudParam.Yaw.AngleMode            = AngleMode_Encoder;
    CloudParam.Yaw.FrameCounter         = 0;
    CloudParam.Yaw.FrameRate            = 0;
    CloudParam.Yaw.RealEncoderAngle     = YawCenter;
    
    CloudParam.Lock = 1;
}
    
    
    
/**
  * @brief  ��̨�����������
  * @param  pitch�������yaw�����
  * @retval void
  */
void CloudMotorCurrent(int16_t Pitch, int16_t Yaw)
{
    static CanSend_Type   SendData;
    
    #if CANPORT == 1
    SendData.CANx = 1;
    #else
    SendData.CANx = 2;
    #endif
    
    
    SendData.SendCanTxMsg.DLC   =   8;
    SendData.SendCanTxMsg.IDE   =   CAN_ID_STD;
    SendData.SendCanTxMsg.RTR   =   CAN_RTR_Data;
    SendData.SendCanTxMsg.StdId =   COULDCONTROLID;
    
//    #if MOTORTYPE == 0
    SendData.SendCanTxMsg.Data[0] = Yaw >> 8;
    SendData.SendCanTxMsg.Data[1] = Yaw;
    SendData.SendCanTxMsg.Data[2] = Pitch >> 8;
    SendData.SendCanTxMsg.Data[3] = Pitch;
    SendData.SendCanTxMsg.Data[4] = 0;
    SendData.SendCanTxMsg.Data[5] = 0;
    SendData.SendCanTxMsg.Data[6] = 0;
    SendData.SendCanTxMsg.Data[7] = 0;
//    #else
//    SendData.SendCanTxMsg.Data[0] = (-Yaw) >> 8;
//    SendData.SendCanTxMsg.Data[1] = (-Yaw);
//    SendData.SendCanTxMsg.Data[2] = (-Pitch) >> 8;
//    SendData.SendCanTxMsg.Data[3] = (-Pitch);
//    SendData.SendCanTxMsg.Data[4] = 0;
//    SendData.SendCanTxMsg.Data[5] = 0;
//    SendData.SendCanTxMsg.Data[6] = 0;
//    SendData.SendCanTxMsg.Data[7] = 0;
//    #endif
    
    xQueueSend(Queue_CANSend, &SendData, 10);
}


/**
  * @brief  ������ں���
  * @Parma  0 ���ͣ��      1 PID����
  * @retval void
  * @note   �˺���Ӧ��������ִ��
  */
void Cloud_Adjust(uint8_t mode)
{
    int16_t PitchMotorCurrent, YawMotorCurrent;
    
    //δ����
    if(mode)
    {
        //Yaw���ԽǶ�Ŀ��ģʽ
        if(CloudParam.Yaw.AngleMode == AngleMode_ABS)
        {
            CloudParam.Yaw.EncoderTargetAngle = (CloudParam.Yaw.ABSTargetAngle - SuperGyoAngle) * 22.7556F + YawCenter;
            CloudParam.Yaw.EncoderTargetAngle = CloudParam.Yaw.EncoderTargetAngle > YawLEFTLimit ? YawLEFTLimit : CloudParam.Yaw.EncoderTargetAngle;
            CloudParam.Yaw.EncoderTargetAngle = CloudParam.Yaw.EncoderTargetAngle < YawRIGHTLimit ? YawRIGHTLimit : CloudParam.Yaw.EncoderTargetAngle;
        }
        
        PitchMotorCurrent = Control_PitchPID();
        YawMotorCurrent = Control_YawPID();
    }
    //����
    else
    {
        PitchMotorCurrent = 0;
        YawMotorCurrent = 0;
    }
    
    //��̨�����������
    CloudMotorCurrent(PitchMotorCurrent, YawMotorCurrent);
}


/**
  * @brief  ��̨Yaw�ȼ�ģʽ����
  * @param  Ŀ��Ƕ�
  * @param  ģʽ  0 ���ԽǶ�          1 ��ԽǶȣ��������Ƕ�,�����Ҹ���
  * @retval void
  */
void Cloud_YawAngleSet(float Target, uint8_t mode)
{
    int16_t Buffer;
    
    if(mode)
    {
        CloudParam.Yaw.AngleMode = AngleMode_Encoder;
        
        Buffer = (int16_t)Target + YawCenter;
        Buffer = Buffer > YawLEFTLimit ? YawLEFTLimit : Buffer;
        Buffer = Buffer < YawRIGHTLimit ? YawRIGHTLimit : Buffer;
        
        CloudParam.Yaw.EncoderTargetAngle = Buffer;
    }
    else
    {
        CloudParam.Yaw.AngleMode = AngleMode_ABS;
        CloudParam.Yaw.ABSTargetAngle = Target;
    }
}


/**
  * @brief  ��̨Pitch�Ƕȼ�ģʽ����
  * @param  Ŀ��Ƕ�(�������Ƕȣ�
  * @retval void
  */
void Cloud_PitchAngleSet(float Target)
{
    int16_t Buffer;
    
    CloudParam.Pitch.AngleMode = AngleMode_Encoder;
    
    Buffer = (int16_t)Target + PitchCenter;
    Buffer = Buffer > PitchUPLimit ? PitchUPLimit : Buffer;
    Buffer = Buffer < PitchDOWNLimit ? PitchDOWNLimit : Buffer;
    
    CloudParam.Pitch.EncoderTargetAngle = Buffer;
}






