
#define __DRIVER_CONTROL_GLOBALS

#include "Config.h"
#include "Driver_DBUS.h"
#include "Driver_Chassis.h"
#include "Driver_Control.h"
#include "Driver_mpu9250.h"
#include "Driver_PokeMotor.h"
#include "Driver_CloudMotor.h"
#include "Driver_SuperGyroscope.h"


/**
  * @brief  ��̨������Ƴ�ʼ��
  * @param  void
  * @retval void
  */
void CloudPID_InitConfig(void)
{
#if INFANTRY == 1       //��Ħ
    
#elif INFANTRY == 2     //����˹��
    
    YawOPID.P = 0;
    YawOPID.I = 0;
    YawOPID.D = 0;
    YawOPID.CurrentError = 0;
    YawOPID.LastError = 0;
    YawOPID.LastTick = 0;
    YawOPID.IMax = 0;
    YawOPID.PIDMax = 0;
    
    YawIPID.P = 100;
    YawIPID.I = 20;
    YawIPID.D = 0;
    YawIPID.CurrentError = 0;
    YawIPID.LastError = 0;
    YawIPID.LastTick = 0;
    YawIPID.IMax = 1000;
    YawIPID.PIDMax = 5000;
    
#elif INFANTRY == 3     //��ʿ��
    
#elif INFANTRY == 4     //������û���֣�����ô�аɣ�
    
#elif INFANTRY == 5     //����
    
#elif INFANTRY == 6     //Ӣ��
    
#endif
}


/**
  * @note   modified
  * @brief  Yaw��PID
  * @param  void
  * @retval 
  */
int16_t Control_YawPID(void)
{
	portTickType CurrentTick = xTaskGetTickCount(); 
/***************************************	�⻷	******************************************/
	YawOPID.CurrentError = CloudParam.Yaw.TargetABSAngle - CloudParam.Yaw.RealABSAngle;
	
	YawOPID.Pout = YawOPID.P * YawOPID.CurrentError;
	
	YawOPID.Iout += YawOPID.I * YawOPID.CurrentError;
	YawOPID.Iout = YawOPID.Iout > YawOPID.IMax ? YawOPID.IMax : YawOPID.Iout;
	YawOPID.Iout = YawOPID.Iout < -YawOPID.IMax ? -YawOPID.IMax : YawOPID.Iout;
	
	YawOPID.Dout = -YawOPID.D * (SuperGyoParam.Omega - Position.Real.OZ);
	
	YawOPID.PIDout = (YawOPID.Pout + YawOPID.Iout + YawOPID.Dout);
	
	YawOPID.PIDout = YawOPID.PIDout > YawOPID.PIDMax ? YawOPID.PIDMax : YawOPID.PIDout;
	YawOPID.PIDout = YawOPID.PIDout < -YawOPID.PIDMax ? -YawOPID.PIDMax : YawOPID.PIDout;
	
	YawOPID.LastError = YawOPID.CurrentError;
	
/***************************************	�ڻ�	******************************************/
	YawIPID.CurrentError = YawOPID.PIDout - (Position.Real.OZ - SuperGyoParam.Omega);	
	YawIPID.CurrentError = -DBUS_ReceiveData.ch4 - (Position.Real.OZ - SuperGyoParam.Omega);
	
	YawIPID.Pout = YawIPID.P * YawIPID.CurrentError;
	
	YawIPID.Iout += YawIPID.I * YawIPID.CurrentError;
	YawIPID.Iout = YawIPID.Iout > YawIPID.IMax ? YawIPID.IMax : YawIPID.Iout;
	YawIPID.Iout = YawIPID.Iout < -YawIPID.IMax ? -YawIPID.IMax : YawIPID.Iout;
	
	if(YawIPID.LastTick != CurrentTick)
	{
		YawIPID.Dout = YawIPID.D * (YawIPID.CurrentError - YawIPID.LastError) * 5 / (CurrentTick - YawIPID.LastTick);
	}
	else
	{
		YawIPID.Dout = YawIPID.D * (YawIPID.CurrentError - YawIPID.LastError);
	}
	
	YawIPID.PIDout = (YawIPID.Pout + YawIPID.Iout + YawIPID.Dout);
	
	YawIPID.PIDout = YawIPID.PIDout > YawIPID.PIDMax ? YawIPID.PIDMax : YawIPID.PIDout;
	YawIPID.PIDout = YawIPID.PIDout < -YawIPID.PIDMax ? -YawIPID.PIDMax : YawIPID.PIDout;
	
	YawIPID.LastError = YawIPID.CurrentError;
	YawIPID.LastTick = CurrentTick;
	
	return (short)YawIPID.PIDout;
}


/**
  * @note   modified
  * @brief  Pitch��PID
  * @param  void
  * @retval void
  */
int16_t Control_PitchPID(void)
{
	portTickType CurrentTick = xTaskGetTickCount(); 
/***************************************	�⻷	******************************************/

	PitchOPID.CurrentError = CloudParam.Pitch.TargetABSAngle - CloudParam.Pitch.RealABSAngle;
	
	PitchOPID.Pout = PitchOPID.P * PitchOPID.CurrentError;
	
	PitchOPID.Iout += PitchOPID.I * PitchOPID.CurrentError;
	PitchOPID.Iout = PitchOPID.Iout > PitchOPID.IMax ? PitchOPID.IMax : PitchOPID.Iout;
	PitchOPID.Iout = PitchOPID.Iout < -PitchOPID.IMax ? -PitchOPID.IMax : PitchOPID.Iout;
	
	PitchOPID.Dout = -PitchOPID.D * Position.Real.OX;
	
	PitchOPID.PIDout = PitchOPID.Pout + PitchOPID.Iout + PitchOPID.Dout;
	
	PitchOPID.PIDout = PitchOPID.PIDout > PitchOPID.PIDMax ? PitchOPID.PIDMax : PitchOPID.PIDout;
	PitchOPID.PIDout = PitchOPID.PIDout < -PitchOPID.PIDMax ? -PitchOPID.PIDMax : PitchOPID.PIDout;
	
	PitchOPID.LastError = PitchOPID.CurrentError;
	
/***************************************	�ڻ�	******************************************/
	PitchIPID.CurrentError = PitchOPID.PIDout - Position.Real.OX;	
//	PitchIPID.CurrentError =  - Position.MotorEncoderOmega.X;
	
	PitchIPID.Pout = PitchIPID.P * PitchIPID.CurrentError;
	
	PitchIPID.Iout += PitchIPID.I * PitchIPID.CurrentError;
	PitchIPID.Iout = PitchIPID.Iout > PitchIPID.IMax ? PitchIPID.IMax : PitchIPID.Iout;
	PitchIPID.Iout = PitchIPID.Iout < -PitchIPID.IMax ? -PitchIPID.IMax : PitchIPID.Iout;
	
	if(YawIPID.LastTick != CurrentTick)
	{
        PitchIPID.Dout = PitchIPID.D * (PitchIPID.CurrentError - PitchIPID.LastError) * 5 / (CurrentTick - PitchIPID.LastTick);
    }
    else
    {
        PitchIPID.Dout = PitchIPID.D * (PitchIPID.CurrentError - PitchIPID.LastError) / (CurrentTick - PitchIPID.LastTick);
    }
	
	PitchIPID.PIDout = (PitchIPID.Pout + PitchIPID.Iout + PitchIPID.Dout);
	
	PitchIPID.PIDout = PitchIPID.PIDout > PitchIPID.PIDMax ? PitchIPID.PIDMax : PitchIPID.PIDout;
	PitchIPID.PIDout = PitchIPID.PIDout < -PitchIPID.PIDMax ? -PitchIPID.PIDMax : PitchIPID.PIDout;
	
	PitchIPID.LastError = PitchIPID.CurrentError;
	PitchIPID.LastTick = CurrentTick;
	
	return (short)PitchIPID.PIDout;
}


/**
  * @brief  �������PID
  * @param  void
  * @retval 
  */
int16_t Control_PokeIPID(void)
{
    /*****************************  �⻷  *****************************/
    PokeOPID.CurrentError = PokeMotorParam.TargetLocation - PokeMotorParam.RealLocation;
    
    PokeOPID.Pout = PokeOPID.P * PokeOPID.CurrentError;
    PokeOPID.Dout = PokeOPID.D * (PokeOPID.CurrentError - PokeOPID.LastError);
    
    PokeOPID.PIDout = PokeOPID.Pout + PokeOPID.Dout;
    PokeOPID.PIDout = PokeOPID.PIDout > PokeOPID.PIDMax ? PokeOPID.PIDMax : PokeOPID.PIDout;
    PokeOPID.PIDout = PokeOPID.PIDout < -PokeOPID.PIDMax ? -PokeOPID.PIDMax : PokeOPID.PIDout;
    
    PokeOPID.LastError = PokeOPID.CurrentError;
    
    /*****************************  �ڻ�  *****************************/
    PokeIPID.CurrentError = PokeOPID.PIDout - PokeMotorParam.RealSpeed;
//    PokeIPID.CurrentError = DBUS_ReceiveData.ch1 - PokeMotorParam.RealSpeed;
    
    PokeIPID.Pout = PokeIPID.P * PokeIPID.CurrentError;
    
    PokeIPID.Iout += PokeIPID.CurrentError * PokeIPID.I;
    PokeIPID.Iout = PokeIPID.Iout > PokeIPID.IMax ? PokeIPID.IMax : PokeIPID.Iout;
    PokeIPID.Iout = PokeIPID.Iout < -PokeIPID.IMax ? -PokeIPID.IMax : PokeIPID.Iout;
    
    PokeIPID.Dout = PokeIPID.D * (PokeIPID.CurrentError - PokeIPID.LastError);
    
    PokeIPID.PIDout = -(PokeIPID.Pout + PokeIPID.Iout + PokeIPID.Dout);
    
    PokeIPID.PIDout = PokeIPID.PIDout > PokeIPID.PIDMax ? PokeIPID.PIDMax : PokeIPID.PIDout;
    PokeIPID.PIDout = PokeIPID.PIDout < -PokeIPID.PIDMax ? -PokeIPID.PIDMax : PokeIPID.PIDout;
    
    PokeIPID.LastError = PokeIPID.CurrentError;
    
    return PokeIPID.PIDout;
}


/** 
  * @note   modified
  * @brief  ���̽Ƕ�PID
  * @param  0 ����PID         1 �Զ�����PID
  * @retval void
  */
void Control_ChassisPID(void)
{
    /************************************       �⻷PID       ************************************/
    ChassisOPID.CurrentError = ChassisParam.TargetABSAngle - SuperGyoParam.Angle;
    
    ChassisOPID.Pout = ChassisOPID.P * ChassisOPID.CurrentError;
    
    ChassisOPID.Iout = ChassisOPID.I * ChassisOPID.CurrentError;
    ChassisOPID.Iout = ChassisOPID.Iout > ChassisOPID.IMax ? ChassisOPID.IMax : ChassisOPID.Iout;
    ChassisOPID.Iout = ChassisOPID.Iout < -ChassisOPID.IMax ? -ChassisOPID.IMax : ChassisOPID.Iout;
    
    ChassisOPID.Dout = ChassisOPID.D * (ChassisOPID.CurrentError - ChassisOPID.LastError);
    
    ChassisOPID.PIDout = ChassisOPID.Pout + ChassisOPID.Iout + ChassisOPID.Dout;
    ChassisOPID.PIDout = ChassisOPID.PIDout > ChassisOPID.PIDMax ? ChassisOPID.PIDMax : ChassisOPID.PIDout;
    ChassisOPID.PIDout = ChassisOPID.PIDout < -ChassisOPID.PIDMax ? -ChassisOPID.PIDMax : ChassisOPID.PIDout;
    
    /************************************       �ڻ�PID       ************************************/
    ChassisIPID.CurrentError = ChassisOPID.PIDout - SuperGyoParam.Omega ;
    
    ChassisIPID.Pout = ChassisIPID.P * ChassisIPID.CurrentError;
    
    ChassisIPID.Iout = ChassisIPID.I * ChassisIPID.CurrentError;
    ChassisIPID.Iout = ChassisIPID.Iout > ChassisIPID.IMax ? ChassisIPID.IMax : ChassisIPID.Iout;
    ChassisIPID.Iout = ChassisIPID.Iout < -ChassisIPID.IMax ? -ChassisIPID.IMax : ChassisIPID.Iout;
    
    ChassisIPID.Dout = ChassisIPID.D * (ChassisIPID.CurrentError - ChassisIPID.LastError);
    
    ChassisIPID.PIDout = -(ChassisIPID.Pout + ChassisIPID.Iout + ChassisIPID.Dout);
    ChassisIPID.PIDout = ChassisIPID.PIDout > ChassisIPID.PIDMax ? ChassisIPID.PIDMax : ChassisIPID.PIDout;
    ChassisIPID.PIDout = ChassisIPID.PIDout < -ChassisIPID.PIDMax ? -ChassisIPID.PIDMax : ChassisIPID.PIDout;
    
    ChassisParam.TargetOmega = ChassisIPID.PIDout;
}


///**
//  * @brief  Ԥ���Զ�׷��ר���ٶ�PID
//  * @param  Ŀ����ٶȣ��������ߵ�λ��
//  * @retval �������ֵ
//  */
//int16_t VControl_YawPID(float TargetOmega)
//{
//	portTickType CurrentTick = xTaskGetTickCount(); 
//    
//    ForcastYawSpeedPID.CurrentError = TargetOmega * 22.7556F - (Position.MotorEncoderOmega.Z - SuperGyoMotorEncoderOmega);
//	
//	ForcastYawSpeedPID.Pout = ForcastYawSpeedPID.P * ForcastYawSpeedPID.CurrentError;
//	
//	ForcastYawSpeedPID.Iout += ForcastYawSpeedPID.I * ForcastYawSpeedPID.CurrentError;
//	ForcastYawSpeedPID.Iout = ForcastYawSpeedPID.Iout > ForcastYawSpeedPID.IMax ? ForcastYawSpeedPID.IMax : ForcastYawSpeedPID.Iout;
//	ForcastYawSpeedPID.Iout = ForcastYawSpeedPID.Iout < -ForcastYawSpeedPID.IMax ? -ForcastYawSpeedPID.IMax : ForcastYawSpeedPID.Iout;
//	
//	if(ForcastYawSpeedPID.LastTick != CurrentTick)
//	{
//		ForcastYawSpeedPID.Dout = ForcastYawSpeedPID.D * (ForcastYawSpeedPID.CurrentError - ForcastYawSpeedPID.LastError) * 5 / (CurrentTick - ForcastYawSpeedPID.LastTick);
//	}
//	else
//	{
//		ForcastYawSpeedPID.Dout = ForcastYawSpeedPID.D * (ForcastYawSpeedPID.CurrentError - ForcastYawSpeedPID.LastError);
//	}
//	
//	ForcastYawSpeedPID.PIDout = (ForcastYawSpeedPID.Pout + ForcastYawSpeedPID.Iout + ForcastYawSpeedPID.Dout);
//	
//	ForcastYawSpeedPID.PIDout = ForcastYawSpeedPID.PIDout > ForcastYawSpeedPID.PIDMax ? ForcastYawSpeedPID.PIDMax : ForcastYawSpeedPID.PIDout;
//	ForcastYawSpeedPID.PIDout = ForcastYawSpeedPID.PIDout < -ForcastYawSpeedPID.PIDMax ? -ForcastYawSpeedPID.PIDMax : ForcastYawSpeedPID.PIDout;
//	
//	ForcastYawSpeedPID.LastError = ForcastYawSpeedPID.CurrentError;
//	ForcastYawSpeedPID.LastTick = CurrentTick;
//	
//	return (short)ForcastYawSpeedPID.PIDout;
//}







