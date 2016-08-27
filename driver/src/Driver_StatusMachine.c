
#define __DRIVER_STATUSMACHINE_GLOBALS

#include "Config.h"
#include "OSinclude.h"
#include "Driver_DBUS.h"
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
    CloudStatus = CloudStatus_Normal;
    GunStatus = GunStatus_Stop;
    ControlStatus = ControlStatus_KM;
}


/**
  * @brief  ״̬��״̬����
  * @param  void
  * @retval void
  * @note   ǹ�ڵ��ͬ������
  */
void StatusMachine_Update(void)
{
    static uint8_t GunFricWorking = 0;
    
    
#if BEBUG_MODE
    //֡�ʹ���ͣ��
    if(DBUSFrameRate < 3)
    {
        ControlStatus = ControlStatus_Protect;
        
        return;
    }
#endif
    
//    //����ģʽѡ��
//    if(DBUS_ReceiveData.switch_left == 1)
//    {
//        //����ģʽ
//        ControlStatus = ControlStatus_KM;
//    }
//    //ң��������
//    else if(DBUS_ReceiveData.switch_left == 2)
//    {
//        //ң��ģʽ
//        ControlStatus = ControlStatus_RC;
//    }
//    else
//    {
//        //����ģʽ
//         ControlStatus = ControlStatus_Protect;
//    }
//        
//    //�������
//    if(ControlStatus == ControlStatus_KM)
//    {
//        //ǹĦ������ͣ
//        if(DBUS_ReceiveData.mouse.press_left)
//        {
//            GunStatus = GunStatus_Motor;
//        }
//        
//        
//        //ǹ�������ǹ���䣨����Ħ��������ʱ��Ч��
//        if(DBUS_ReceiveData.mouse.press_left)
//        {
//            GunStatus = GunStatus_Shot;
//        }
//        else
//        {
//            if(GunFricWorking)
//            {
//                GunStatus = GunStatus_Motor;
//            }
//            else
//            {
//                GunStatus = GunStatus_Stop;
//            }
//        }
//            
//        
//        //��̨ģʽ
//        if(DBUS_ReceiveData.mouse.press_right)
//        {
//            CloudStatus = CloudStatus_Auto;
//        }
//        else
//        {
//            CloudStatus = CloudStatus_Normal;
//        }
//    }
//    else        //ң����ģʽ
//    {
        if(DBUS_ReceiveData.switch_right == 2)
        {
            GunStatus = GunStatus_Shot;
        }
        else if(DBUS_ReceiveData.switch_right == 3)
        {
            GunStatus = GunStatus_Motor;
        }
        else
        {
            GunStatus = GunStatus_Stop;
        }
}















