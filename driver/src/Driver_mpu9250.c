
#define __MPU9250_GLOBALS

#include "Config.h"
#include "Driver_mpu9250.h"
#include "OSinclude.h"
#include "mpu9250dmp.h"


/**
  * @brief  mpu9250��ʼ��
  * @param  void
  * @retval void
  */
void MPU9250_InitConfig(void)
{
#if INFANTRY == 1       //��Ħ
    
#elif INFANTRY == 2     //����˹��
    
    Omega_Offset.X = -0.54F;
    Omega_Offset.Y = -0.4F;
    Omega_Offset.Z = 0.46F;
    
#elif INFANTRY == 3     //��ʿ��
    
#elif INFANTRY == 4     //������û���֣�����ô�аɣ�
    
#elif INFANTRY == 5     //����
    
#elif INFANTRY == 6     //Ӣ��
    
#endif
}


/**
  * @brief  mpu9250����ŷ���Ǽ����ٶ�
  * @param  void
  * @retval 0�ɹ�     1ʧ��
  */
uint8_t MPU9250_Update(void)
{
    uint8_t result;
    
    float Pitch, Roll, Yaw;
    float OX, OY, OZ;
    
    result = MPU9250DMP_GetEuler(&Pitch, &Roll, &Yaw);
    if(result)return 1;
    result = MPU9250_GetGyro(&OX, &OY, &OZ);
    if(result)return 1;
    
    Position.Euler.Pitch = Pitch;
    Position.Euler.Roll = Roll;
    Position.Euler.Yaw = Yaw;
    
    Position.Real.OX = -(OX - Omega_Offset.X);
    Position.Real.OY = -(OY - Omega_Offset.Y);
    Position.Real.OZ = -(OZ - Omega_Offset.Z);
    
    return 0;
}

