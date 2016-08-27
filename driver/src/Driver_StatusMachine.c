
#define __DRIVER_STATUSMACHINE_GLOBALS

#include "Config.h"
#include "OSinclude.h"
#include "Driver_DBUS.h"
#include "Driver_vision.h"
#include "Driver_Control.h"
#include "Driver_StatusMachine.h"


/*
wasdǰ�����ҿ���
qe��������
���������䣨δ����Ħ����������Ħ���֣����Ҽ��Զ����
ctrl + shift�ر�Ħ����
*/

/**
  * @brief  ״̬����ʼ��
  * @param  void
  * @retval void
  */
void StatusMachine_InitConfig(void)
{
    AutoMode = AutoMode_OFF;
    GunStatus = GunStatus_Stop;
    ControlMode = ControlMode_KM;
    SneakMode = 0;
}


/**
  * @brief  ״̬��״̬����
  * @param  void
  * @retval void
  * @note   ң�������뿪��1ң�������ƣ���1������3��Ħ���֣�2����
            ���뿪��3������ģʽ�����ȫ���ر�
            ���뿪��2�����̿��ƣ��Ҳ��뿪��3��Ħ���֣�����Ҽ��Զ����
            QE����
  */
    uint8_t FristToKM = 1;
void StatusMachine_Update(void)
{
    static uint8_t RateCounter = 0;
    static uint8_t BigSampleCounter = 0;
    static uint8_t AttackCounter = 0;
    static portTickType LastPCShutdownSignalTick = 0;
    portTickType CurrentTick = xTaskGetTickCount();
    
    
    //֡�ʹ���ͣ��
    if(DBUSFrameRate < 3)
    {
        ControlMode = ControlMode_Protect;
        
        SneakMode = 0;
        
        return;
    }
    
    //ң��������
    if(DBUS_ReceiveData.switch_left == 1)
    {
        FristToKM = 1;
        
        ControlMode = ControlMode_RC;
        
        //Ħ����
        if(DBUS_ReceiveData.switch_right == 3)
        {
            GunStatus = GunStatus_Motor;
        }
        else if(DBUS_ReceiveData.switch_right == 2)
        {
            GunStatus = GunStatus_Shot;
        }
        else
        {
            GunStatus = GunStatus_Stop;
        }
        
        //�Զ�����ر�
        AutoMode = AutoMode_OFF;
        
        SneakMode = 0;
    }
    //�������
    else if(DBUS_ReceiveData.switch_left == 2)
    {
        if(FristToKM == 1)
        {
            ControlMode = ControlMode_KM;
            FristToKM = 0;
        }
        
        //Ǳ�п���
        if(DBUS_ReceiveData.keyBoard.key_code & KEY_CTRL)
        {
            SneakMode = 1;
        }
        else if(DBUS_ReceiveData.keyBoard.key_code & KEY_SHIFT)
        {
            SneakMode = 0;
        }
        
        if(DBUS_ReceiveData.keyBoard.key_code & KEY_C)
        {
            ControlMode = ControlMode_KM;
        }
        else if(DBUS_ReceiveData.keyBoard.key_code & KEY_F)
        {
            ControlMode = ControlMode_AUTO;
        }
        
        //���ͷ���Ƶ�ʼ�С���ڸ���
        if(RateCounter == 4)
        {
            //�з�Ŀ���ɫ
            if((DBUS_ReceiveData.ch1 > 600) && 
                (DBUS_ReceiveData.ch2 > 600) &&
                (DBUS_ReceiveData.ch3 < -600) &&
                (DBUS_ReceiveData.ch4 > 600))
            {
                SendEnemyColor('R');
            }
            //�з�Ŀ����ɫ
            else if((DBUS_ReceiveData.ch1 < -600) && 
                (DBUS_ReceiveData.ch2 > 600) &&
                (DBUS_ReceiveData.ch3 > 600) &&
                (DBUS_ReceiveData.ch4 > 600))
            {
                SendEnemyColor('B');
            }
            //���ģʽ
            else if(DBUS_ReceiveData.keyBoard.key_code & KEY_X)
            {
                AttackCounter = 0;
                
                if(BigSampleCounter < VisiolModeChangeDataSendNum)
                {
                    VisionType = VisionType_BigSample;
                    SendPCOrder(PCOrder_BigSample);
                    BigSampleCounter++;
                }
            }
            //�Զ����ģʽ�������������ز����ǣ�
            else
            {
                BigSampleCounter = 0;
                
                if(AttackCounter < VisiolModeChangeDataSendNum)
                {
                    VisionType = VisionType_Attack;
                    SendPCOrder(PCOrder_Attack);
                    AttackCounter++;
                }
            }
            RateCounter = 0;
        }
        else
        {
            RateCounter++;
        }
        
//#if INFANTRYTYPE == 1 
//        if(DBUS_ReceiveData.keyBoard.key_code & KEY_C)
//        {
//            ABInfantryMode = ABInfantry_Master;
//        }
//        else if(DBUS_ReceiveData.keyBoard.key_code & KEY_F)
//        {
//            ABInfantryMode = ABInfantry_Slave;
//        }
//#elif INFANTRYTYPE == 2
//        if(DBUS_ReceiveData.keyBoard.key_code & KEY_F)
//        {
//            ABInfantryMode = ABInfantry_Master;
//        }
//        else if(DBUS_ReceiveData.keyBoard.key_code & KEY_C)
//        {
//            ABInfantryMode = ABInfantry_Slave;
//        }
//#endif
    }
    //����ģʽ
    else
    {
        FristToKM = 1;
        SneakMode = 0;
        
        ControlMode = ControlMode_Protect;
        
        //�ػ�
        if((DBUS_ReceiveData.ch1 > 600) && 
            (DBUS_ReceiveData.ch2 < -600) &&
            (DBUS_ReceiveData.ch3 < -600) &&
            (DBUS_ReceiveData.ch4 > 600))
        {
            if(LastPCShutdownSignalTick + 5000 < CurrentTick)
            {
                SendPCOrder(PCOrder_Shutdown);
            }
        }
        else
        {
            LastPCShutdownSignalTick = CurrentTick;
        }
    }
}















