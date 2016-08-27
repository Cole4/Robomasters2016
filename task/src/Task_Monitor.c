
#include "Handler.h"

#include "Task_Monitor.h"

#include "Driver_Bell.h"
#include "Driver_DBUS.h"
#include "Driver_Motor.h"
#include "Driver_vision.h"
#include "Driver_mpu9250.h"
#include "Driver_SuperGyroscope.h"

#include "Config.h"

int16_t speed = 0;

/**
  * @brief  ����������
  * @param  unused
  * @retval voif
  */
void Task_Monitor(void *Parameters)
{
    //ϵͳ״̬��ÿһλ��Ӧһ������0������1����
/****************************************************************
    15  |   14  |   13  |   12  |   11  |   10  |   9   |   8   |
        |       |       |       |       |       |       |       |
-----------------------------------------------------------------
    7   |   6   |   5   |   4   |   3   |   2   |   1   |   0   |
        |       |����Gyr|��Ħ��  |��Ħ�� |  Yaw  | Pitch |  DBUS |
****************************************************************/
    uint16_t SysErrorStatus = 0;
    
    for(;;)
    {
/**************************  ��   ����֡��ͳ��   ��  **************************/
        //DBUS֡��ͳ��
        DBUSFrameRate = DBUSFrameCounter;	
        DBUSFrameCounter = 0;
        
        //��̨���֡��ͳ��
        PitchMotorFrameRate = PitchMotorFrameCounter;
        PitchMotorFrameCounter = 0;
        YawMotorFrameRate = YawMotorFrameCounter;
        YawMotorFrameCounter = 0;
        
        //��������������֡ͳ��
        SuperGyoFrameRate = SuperGyoFrameCounter;
        SuperGyoFrameCounter = 0;
        
        //�Ӿ�֡��ͳ��
        PCFrameRate = PCFrameCounter;
        PCFrameCounter = 0;
        
        //DBUS֡�ʹ���
        if(DBUSFrameRate < 6)
        {
            SysErrorStatus |= 0x0001;
        }
        else
        {
            SysErrorStatus &= 0xFFFE;
        }
        //Pitch��̨֡�ʹ���
        if(PitchMotorFrameRate < 30)
        {
            SysErrorStatus |= 0x0002;
        }
        else
        {
            SysErrorStatus &= 0xFFFD;
        }
        //Yaw��̨֡�ʹ���
        if(YawMotorFrameRate < 30)
        {
            SysErrorStatus |= 0x0004;
        }
        else
        {
            SysErrorStatus &= 0xFFFB;
        }
        //����������֡�ʹ���
        if(SuperGyoFrameRate < 30)
        {
            SysErrorStatus |= 0x0020;
        }
        else
        {
            SysErrorStatus &= 0xFFDF;
        }
/**************************  ��   ����֡��ͳ��   ��  **************************/
/**************************************************************************************************/
/**************************  ��   �����־��λ   ��  **************************/
        //DBUS
        if(SysErrorStatus & 0x0001)
        {
            Bell_BarkWarning(2, MAXAWarning);
        }
        //yaw��̨���
        else if(SysErrorStatus & 0x0004)
        {
            Bell_BarkWarning(3, MAXAWarning);
        }
        //pitch��̨���
        else if(SysErrorStatus & 0x0002)
        {
            Bell_BarkWarning(4, MAXAWarning);
        }
        //����������
        else if(SysErrorStatus & 0x0020)
        {
            Bell_BarkWarning(7, MAXAWarning);
        }
        else
        {
            Bell_BarkWarning(0, MAXAWarning);
        }
            

        
        vTaskDelay(200);
    }
}
