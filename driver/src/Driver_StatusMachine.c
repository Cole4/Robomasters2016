
#define __DRIVER_STATUSMACHINE_GLOBALS

#include "Config.h"
#include "OSinclude.h"
#include "Driver_DBUS.h"
#include "Driver_vision.h"
#include "Driver_Control.h"
#include "Driver_mpu9250.h"
#include "Driver_FricMotor.h"
#include "Driver_CloudMotor.h"
#include "Driver_StatusMachine.h"
#include "Driver_SuperGyroscope.h"


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
    ControlMode = ControlMode_KM;
    FricStatus = FricStatus_Stop;
    KMSubschema = KMSubschema_Normal;
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
    portTickType CurrentTick = xTaskGetTickCount();
    
    //֡�ʹ��ͽ�����
    if(DBUSFrameRate < 3)
    {
        ControlMode = ControlMode_Protect;
        return;
    }
    
    //����ģʽ
    if(DBUS_ReceiveData.switch_left == 1)
    {
        ControlMode = ControlMode_RC;
    }
    else if(DBUS_ReceiveData.switch_left == 2)
    {
        ControlMode = ControlMode_KM;
    }
    else
    {
        ControlMode = ControlMode_Protect;
    } 
    
    //������ģʽ
    if(ControlMode == ControlMode_RC)
    {
/*******************************************  ��  Ħ����  ��  *******************************************/
        if((DBUS_ReceiveData.switch_right == 3) || (DBUS_ReceiveData.switch_right == 2))
        {
            FricStatus = FricStatus_Working;
        }
        else
        {
            FricStatus = FricStatus_Stop;
        }
/*******************************************  ��  Ħ����  ��  *******************************************/
        KMSubschema = KMSubschema_Normal;
    }
    //����ģʽ
    else if(ControlMode == ControlMode_KM)
    {
/*******************************************  ��  Ħ����  ��  *******************************************/
        if((DBUS_ReceiveData.switch_right == 3) || (DBUS_ReceiveData.switch_right == 2))
        {
            if(DBUS_ReceiveData.keyBoard.key_code & KEY_Z)
            {
                //����ģʽ
                FricStatus = FricStatus_Crazy;
            }
            else
            {
                //��������
                FricStatus = FricStatus_Working;
            }
        }
        else
        {
            FricStatus = FricStatus_Stop;
        }
/*******************************************  ��  Ħ����  ��  *******************************************/
/*******************************************  ��   ģʽ   ��  *******************************************/
        //����ʲôʱ����CTRL���ع��ֶ�Normalģʽ
        if(DBUS_CheckPush(KEY_SHIFT))
        {
            KMSubschema = KMSubschema_Normal;
        }
        
        //ֻ������Normalģʽ�½���ģʽ�л�
        if(KMSubschema == KMSubschema_Normal)
        {
            //����վģʽ
            if(DBUS_CheckPush(KEY_CTRL))
            {
                KMSubschema = KMSubschema_Supply;
            }
            //���Զ�ģʽ
//            else if(DBUS_ReceiveData.mouse.press_right)
//            {
//                KMSubschema = KMSubschema_Halfauto;
//            }
            //ҡ��ģʽ
            else if(DBUS_CheckPush(KEY_F))
            {
                KMSubschema = KMSubschema_Swing;
            }
            //���ģʽ
            else if(DBUS_CheckPush(KEY_X))
            {
                KMSubschema = KMSubschema_Bigsample;
            }
            //ȫ�Զ�ģʽ
            else if(DBUS_CheckPush(KEY_C))
            {
                KMSubschema = KMSubschema_Fullauto;
            }
            //ȦȦģʽ
            else if(DBUS_CheckPush(KEY_G))
            {
                KMSubschema = KMSubschema_Circle;
            }
        }
        //���ڰ��Զ��ع�
//        else if((KMSubschema == KMSubschema_Halfauto) && (!DBUS_ReceiveData.mouse.press_right))
//        {
//            KMSubschema = KMSubschema_Normal;
//        }
/*******************************************  ��   ģʽ   ��  *******************************************/
    }
    else
    {
        FricStatus = FricStatus_Stop;
        KMSubschema = KMSubschema_Normal;
    }
}















