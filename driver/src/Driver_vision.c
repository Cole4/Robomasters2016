
#define __DRIVER_VISION_GLOBALS

#include "Config.h"
#include "Driver_vision.h"
#include "Driver_CloudMotor.h"
#include <math.h>

/*
X�� ��
Y�� ��
Z�� ǰ
*/


/**
  * @brief  �Ӿ���ʼ��
  * @param  void
  * @retval void
  */
void Vision_InitConfig(void)
{
    PCDataBufferPoint = 0;
    EnemyDataBufferPoint = 0;
    
    EnemyDataBuffer[EnemyDataBufferPoint].ID = 1;
    EnemyDataBuffer[EnemyDataBufferPoint].Time = 0;
    EnemyDataBuffer[EnemyDataBufferPoint].X = 0;
    EnemyDataBuffer[EnemyDataBufferPoint].Y = 0;
    EnemyDataBuffer[EnemyDataBufferPoint].Z = 1;
}


/**
  * @brief  ��ֱ������ϵת��Ϊ����������Ƕ�
  * @param  X
  * @param  Y
  * @param  Z
  * @param  0 �������������ٶ�      1 �����������ٶ�
  * @retval �Ƕ�
  */
AngleI_Struct RecToPolar(float X, float Y, float Z, uint8_t mode)
{
    AngleI_Struct ReturnData;
    float Distance = sqrt(X * X + Z * Z);
    float distance, radian;
    
    ReturnData.H =  - atan(X / Z) * 1303.7973F;
    
    distance = sqrt(X * X + Z * Z);
    if(mode == 0)
    {
    //�������������ٶ�
        ReturnData.V = atan(Y / distance) * 1303.7973F;
    }
    else
    {
    //�����������ٶ�
        radian = (atan(((AFG * distance * distance) / (GUNSpeed * GUNSpeed) - Y) / sqrt(Y * Y + distance * distance)) - atan(Y / distance)) / 2;
        ReturnData.V = radian * 1303.7973F;
    }
    
    return ReturnData;
}


/**
  * @brief  ·����Ϻ��ĺ����������������һ�����
  * @param  Ԥ������ʱ�䳤��
  * @param  Ԥ��ʱ��
  * @param  Ԥ��λ��
  * @retval 0 �ɹ�        1 ʧ��
  */
uint8_t ForcastCore(uint16_t SampleTime, uint16_t ForcastTime, Point_Struct *ForcastPoint)
{
    int RelativeTime;       //���ʱ�䣬��ֹ����ʱ�䳬��Χ
    uint16_t index = 0, Currentindex;
    uint16_t SampleNum = 0;
    

    float A = 0;
    float B = 0;
    float C = 0;
    float D = 0;
    float E = 0;
    
    float Fx = 0;
    float Gx = 0;
    float Hx = 0;
    float Ix = 0;
    float Jx = 0;
    float Kx = 0;
    float Lx = 0;
    float Mx = 0;
    float Nx = 0;
    
    float Fz = 0;
    float Gz = 0;
    float Hz = 0;
    float Iz = 0;
    float Jz = 0;
    float Kz = 0;
    float Lz = 0;
    float Mz = 0;
    float Nz = 0;
    
    float Pax, Pbx, Pcx;
    float Paz, Pbz, Pcz;
    
    //Ѱ�����
    for(SampleNum = 0; SampleNum < ENEMYDATABUFFERLENGHT; SampleNum++)
    {
        if(EnemyDataBuffer[(EnemyDataBufferPoint + ENEMYDATABUFFERLENGHT - SampleNum - 1) % ENEMYDATABUFFERLENGHT].Time + SampleTime < EnemyDataBuffer[EnemyDataBufferPoint].Time)
        {
            break;
        }
    }
    
    //�������������
    if(SampleNum < 5)
    {
        return 1;
    }
    
    E =  -(1 + SampleNum);
    
    //�������
    for(index = 0; index <= SampleNum; index++)
    {
        Currentindex = (EnemyDataBufferPoint + ENEMYDATABUFFERLENGHT - index) % ENEMYDATABUFFERLENGHT;
        
        RelativeTime = EnemyDataBuffer[Currentindex].Time - EnemyDataBuffer[(EnemyDataBufferPoint + ENEMYDATABUFFERLENGHT - SampleNum) % ENEMYDATABUFFERLENGHT].Time;        

//        Relative2 = RelativeTime * RelativeTime;
//        Relative3 = Relative2 * RelativeTime;
//        Relative4 = Relative3 * RelativeTime;
        
        A = A - RelativeTime * RelativeTime * RelativeTime * RelativeTime;
        B = B - RelativeTime * RelativeTime * RelativeTime;
        C = C - RelativeTime * RelativeTime;
        D = D - RelativeTime;
        
        Fx = Fx + RelativeTime * RelativeTime * EnemyDataBuffer[Currentindex].X;
        Gx = Gx + RelativeTime * EnemyDataBuffer[Currentindex].X;
        Hx = Hx + EnemyDataBuffer[Currentindex].X;
        
        Fz = Fz + RelativeTime * RelativeTime * EnemyDataBuffer[Currentindex].Z;
        Gz = Gz + RelativeTime * EnemyDataBuffer[Currentindex].Z;
        Hz = Hz + EnemyDataBuffer[Currentindex].Z;
    }
    

    Ix = D * Fx - C * Gx;
    Jx = A * D - B * C;
    Kx = B * D - C * C;
    Lx = E * Fx - Hx * C;
    Mx = A * E - C * C;
    Nx = B * E - C * D;
    
    Iz = D * Fz - C * Gz;
    Jz = A * D - B * C;
    Kz = B * D - C * C;
    Lz = E * Fz - Hz * C;
    Mz = A * E - C * C;
    Nz = B * E - C * D;

    Pax = (Ix * Nx - Lx * Kx) / (Mx * Kx - Jx * Nx);
    Pbx = -(Ix + Pax * Jx)  / Kx;
    Pcx = - (Fx + Pax * A + Pbx * B) / C;
    
    Paz = (Iz * Nz - Lz * Kz) / (Mz * Kz - Jz * Nz);
    Pbz = -(Iz + Paz * Jz) / Kz;
    Pcz = - (Fz + Paz * A + Pbz * B) / C;
    
    ForcastTime += EnemyDataBuffer[EnemyDataBufferPoint].Time - EnemyDataBuffer[(EnemyDataBufferPoint + ENEMYDATABUFFERLENGHT - SampleNum) % ENEMYDATABUFFERLENGHT].Time;
    
    ForcastPoint->X = (ForcastTime * ForcastTime * Pax + Pbx * ForcastTime + Pcx);
    ForcastPoint->Y = EnemyDataBuffer[Currentindex].Y;
    ForcastPoint->Z = (Paz * ForcastTime * ForcastTime + Pbz * ForcastTime + Pcz);
    
    return 0;
}    


/**
  * @brief  ��ȡĿ�굱ǰ���ٶ�
  * @param  void
  * @retval ����̨ΪԲ�ģ�Ŀ��Ľ��ٶȣ���λΪ��/s
  */
CompensateSpeed_struct Get_EnemyCompensate(void)
{
    CompensateSpeed_struct ReturnData;
    
    ReturnData.X = (EnemyDataBuffer[EnemyDataBufferPoint].X - 
                            EnemyDataBuffer[(EnemyDataBufferPoint + ENEMYDATABUFFERLENGHT - 1) % ENEMYDATABUFFERLENGHT].X) /
                            (EnemyDataBuffer[EnemyDataBufferPoint].Time - EnemyDataBuffer[(EnemyDataBufferPoint + ENEMYDATABUFFERLENGHT - 1) % ENEMYDATABUFFERLENGHT].Time);
    
    ReturnData.Y = (EnemyDataBuffer[EnemyDataBufferPoint].Y - 
                            EnemyDataBuffer[(EnemyDataBufferPoint + ENEMYDATABUFFERLENGHT - 1) % ENEMYDATABUFFERLENGHT].Y) /
                            (EnemyDataBuffer[EnemyDataBufferPoint].Time - EnemyDataBuffer[(EnemyDataBufferPoint + ENEMYDATABUFFERLENGHT - 1) % ENEMYDATABUFFERLENGHT].Time);
        
    ReturnData.Z = (EnemyDataBuffer[EnemyDataBufferPoint].Z - 
                            EnemyDataBuffer[(EnemyDataBufferPoint + ENEMYDATABUFFERLENGHT - 1) % ENEMYDATABUFFERLENGHT].Z) /
                            (EnemyDataBuffer[EnemyDataBufferPoint].Time - EnemyDataBuffer[(EnemyDataBufferPoint + ENEMYDATABUFFERLENGHT - 1) % ENEMYDATABUFFERLENGHT].Time);
    
    return ReturnData;
}


/**
  * @brief  ����һ����ϣ����Ŀ��Ƕȣ������̨�����
  * @param  �������ʱ��(ms)
  * @param  ���ʱ�䳤��(ms)
  * @param  ʱ��ģʽ    0 �Զ���ʱ�䣨��ForcastTime���� 1 �Զ��趨Ԥ��ʱ�䣨���ݾ��뼰�ӵ��ٶ�ȷ����
  * @retval 0 ������ϳɹ�        1 ���������ݲ��������ʧ��ֱ��ʹ�õ�ǰλ����ΪĿ��λ��
  */
uint8_t ForcastOnce(uint16_t SampleTime, uint16_t ForcastTime, AngleI_Struct *ForcastAngle, uint8_t TimeMode)
{
    Point_Struct ForcastPoint;
    float distance;
    
    //�Զ��������ʱ�䳤��
    if(TimeMode)
    {
        distance = sqrt(EnemyDataBuffer[EnemyDataBufferPoint].X * EnemyDataBuffer[EnemyDataBufferPoint].X + EnemyDataBuffer[EnemyDataBufferPoint].Y * EnemyDataBuffer[EnemyDataBufferPoint].Y);
        ForcastTime = distance * 1000 / GUNSpeed + ProgonsisCompensate;
    }
    
    if(ForcastCore(SampleTime, ForcastTime, &ForcastPoint) == 0)        //������ϳɹ�
    {
        //Ŀ���ת��ΪĿ��Ƕ�
        *ForcastAngle = RecToPolar(ForcastPoint.X, 
                                    ForcastPoint.Y, 
                                    ForcastPoint.Z,
                                    1);
        
        return 0;
    }
    //�������ʧ��
    else
    {
        //���ʧ��ֱ��ʹ�õ�ǰλ����ΪĿ��λ��
        *ForcastAngle = RecToPolar(EnemyDataBuffer[EnemyDataBufferPoint].X, 
                                    EnemyDataBuffer[EnemyDataBufferPoint].Y, 
                                    EnemyDataBuffer[EnemyDataBufferPoint].Z,
                                    1);
        
        return 1;
    }
}






