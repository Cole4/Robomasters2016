
#define __DRIVER_CHASSIS_GLOBALS

#include "Handler.h"
#include "OSinclude.h"
#include "Task_CANSend.h"
#include "Driver_Motor.h"
#include "Driver_Chassis.h"
#include "Driver_Control.h"
#include "Driver_SuperGyroscope.h"




volatile float Last_Spd[4];
//���ֽ������
const signed char MecanumCalculateMAT[4][3] = { 
	{1, 1, 1},
	{1,-1,-1},
	{1,-1, 1}, 
	{1, 1,-1}
};

/**
  * @brief  ���̳�ʼ��
  * @param  void 
  * @retval void
  */
void Chassis_InitConfig(void)
{
    for(int i=0;i<=3;i++)
    {
        Last_Spd[i]=0;
    }
    
    ChassisMaxSumCurrent = 2900.0F;
}


/**
  * @brief  �����ٶȿ���
  * @param  x�ٶȣ�ǰ��
  * @param  y�ٶȣ��ң�
  * @param  ���ٶȣ�˳ʱ��Ϊ����
  * @note   �˺���δ���͵���
  * @retval void
  */
void Chassis_Control(int16_t Vx, int16_t Vy, int16_t Omega)
{
    int16_t WheelSpeed[4];
    int16_t PowerSum;
    
    //���ֽ���
    MecanumCalculate(Vx, Vy, Omega, WheelSpeed);
    
    MotorStatus.TargetSpeed.LF = WheelSpeed[0];
    MotorStatus.TargetSpeed.RF = WheelSpeed[1];
    MotorStatus.TargetSpeed.LB = WheelSpeed[2];
    MotorStatus.TargetSpeed.RB = WheelSpeed[3];
    
    //���ʷ���
    PowerSum = MotorStatus.TargetSpeed.LF + MotorStatus.TargetSpeed.RF + MotorStatus.TargetSpeed.LB + MotorStatus.TargetSpeed.RF;
    
    MotorStatus.LimitCurrent.LF = ChassisMaxSumCurrent * MotorStatus.TargetSpeed.LF / PowerSum;
    MotorStatus.LimitCurrent.RF = ChassisMaxSumCurrent * MotorStatus.TargetSpeed.RF / PowerSum;
    MotorStatus.LimitCurrent.LB = ChassisMaxSumCurrent * MotorStatus.TargetSpeed.LB / PowerSum;
    MotorStatus.LimitCurrent.RB = ChassisMaxSumCurrent * MotorStatus.TargetSpeed.RB / PowerSum;
}


/**
  * @brief  �����ٶ������Ƶ���
  * @param  ģʽ  1 �������ݽṹ�е�Ŀ���ٶ������Ƶ���     0 �����ٶ������Ƶ���Ϊ0�����ڽ���ͣ����
  * @retval void
  */
void Chassis_SendMotorParam(uint8_t mode)
{
    static  CanSend_Type   SendData;
    
    SendData.CANx = 2;
    
    SendData.SendCanTxMsg.DLC   =   8;
    SendData.SendCanTxMsg.IDE   =   CAN_ID_STD;
    SendData.SendCanTxMsg.RTR   =   CAN_RTR_Data;
    
    if(mode)
    {
        SendData.SendCanTxMsg.StdId =   CHASSISSPEEDSETCANID;
        SendData.SendCanTxMsg.Data[0] = MotorStatus.TargetSpeed.LF >> 8;
        SendData.SendCanTxMsg.Data[1] = MotorStatus.TargetSpeed.LF;
        SendData.SendCanTxMsg.Data[2] = MotorStatus.TargetSpeed.RF >> 8;
        SendData.SendCanTxMsg.Data[3] = MotorStatus.TargetSpeed.RF;
        SendData.SendCanTxMsg.Data[4] = MotorStatus.TargetSpeed.LB >> 8;
        SendData.SendCanTxMsg.Data[5] = MotorStatus.TargetSpeed.LB;
        SendData.SendCanTxMsg.Data[6] = MotorStatus.TargetSpeed.RB >> 8;
        SendData.SendCanTxMsg.Data[7] = MotorStatus.TargetSpeed.RB;
        xQueueSend(Queue_CANSend, &SendData, 10);
        
        SendData.SendCanTxMsg.StdId =   CHASSISCURRENTSETCANID;
        SendData.SendCanTxMsg.Data[0] = MotorStatus.LimitCurrent.LF >> 8;
        SendData.SendCanTxMsg.Data[1] = MotorStatus.LimitCurrent.LF;
        SendData.SendCanTxMsg.Data[2] = MotorStatus.LimitCurrent.RF >> 8;
        SendData.SendCanTxMsg.Data[3] = MotorStatus.LimitCurrent.RF;
        SendData.SendCanTxMsg.Data[4] = MotorStatus.LimitCurrent.LB >> 8;
        SendData.SendCanTxMsg.Data[5] = MotorStatus.LimitCurrent.LB;
        SendData.SendCanTxMsg.Data[6] = MotorStatus.LimitCurrent.RB >> 8;
        SendData.SendCanTxMsg.Data[7] = MotorStatus.LimitCurrent.RB;
        xQueueSend(Queue_CANSend, &SendData, 10);
    }
    else
    {
        SendData.SendCanTxMsg.StdId =   CHASSISSPEEDSETCANID;
        SendData.SendCanTxMsg.Data[0] = 0;
        SendData.SendCanTxMsg.Data[1] = 0;
        SendData.SendCanTxMsg.Data[2] = 0;
        SendData.SendCanTxMsg.Data[3] = 0;
        SendData.SendCanTxMsg.Data[4] = 0;
        SendData.SendCanTxMsg.Data[5] = 0;
        SendData.SendCanTxMsg.Data[6] = 0;
        SendData.SendCanTxMsg.Data[7] = 0;
        xQueueSend(Queue_CANSend, &SendData, 10);
        
        SendData.SendCanTxMsg.StdId =   CHASSISCURRENTSETCANID;
        SendData.SendCanTxMsg.Data[0] = 0;
        SendData.SendCanTxMsg.Data[1] = 0;
        SendData.SendCanTxMsg.Data[2] = 0;
        SendData.SendCanTxMsg.Data[3] = 0;
        SendData.SendCanTxMsg.Data[4] = 0;
        SendData.SendCanTxMsg.Data[5] = 0;
        SendData.SendCanTxMsg.Data[6] = 0;
        SendData.SendCanTxMsg.Data[7] = 0;
        xQueueSend(Queue_CANSend, &SendData, 10);
    }
}


/**
  * @brief  ���ֽ���
  * @param  x�ٶȣ�ǰ��
  * @param  y�ٶȣ��ң�
  * @param  ���ٶȣ�˳ʱ��Ϊ����
  * @retval void
  */
static void MecanumCalculate(float Vx, float Vy, float Omega, int16_t *Speed)
{
	unsigned char ii = 0, jj = 0;
	float temp_mat[3] = {0,0,0};
	float max_spd = 0,temp_speed = 0;
	float temp_ration = 0;	
	float my_spd[4] = {0,0,0,0};
    
	temp_mat[0] = Vx;
	temp_mat[1] = Vy;
	temp_mat[2] = Omega;
    
	for(ii = 0;ii<4;ii++)
	{
		for(jj = 0;jj<3;jj++)
		{
			my_spd[ii] += temp_mat[jj]*MecanumCalculateMAT[ii][jj];
		}
		my_spd[ii] = temp_speed;
		Last_Spd[ii] = my_spd[ii];
	}
	for(ii = 0;ii<4;ii++)  //�ҵ��ٶ����ֵ
	{
		temp_speed = my_spd[ii] > 0 ? my_spd[ii] : -my_spd[ii];
		max_spd = (max_spd>temp_speed) ? max_spd:temp_speed;
	}
	if( max_spd > Max_WheelSpeed )//��������С
	{
		temp_ration = Max_WheelSpeed/max_spd;
		for(ii = 0;ii<4;ii++)
		{
			my_spd[ii] = my_spd[ii]*temp_ration; 
			Last_Spd[ii] = my_spd[ii];
		}	
	}
	
    //����ʵ���ٶ�
	Speed[0] = (int16_t)my_spd[0]; 
	Speed[1] = (int16_t)my_spd[1]; 
	Speed[2] = (int16_t)my_spd[2]; 
	Speed[3] = (int16_t)my_spd[3]; 
}
