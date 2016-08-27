/**
  ******************************************************************************
  * @file    Project/STM32F4xx_StdPeriph_Templates/stm32f4xx_it.c 
  * @author  MCD Application Team
  * @version V1.4.0
  * @date    04-August-2014
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2014 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_it.h"
#include "main.h"

/** @addtogroup Template_Project
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M4 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}


/******************************************************************************/
/*                 STM32F4xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f4xx.s).                                               */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */ 


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

#include "Driver_DBUS.h"
#include "Driver_Motor.h"
#include "Driver_vision.h"
#include "Driver_SuperGyroscope.h"



uint8_t temp;

CanRxMsg CanRxData1;
CanRxMsg CanRxData2;


//CAN1���ݽ����жϣ��������������ǣ�
void CAN1_RX0_IRQHandler(void)
{
    //����CAN1����
    CAN_Receive(CAN1, 0, &CanRxData1);
    
    switch(CanRxData1.StdId)
    {
    }
    
	CAN_ITConfig(CAN1, CAN_IT_FMP0, ENABLE);
}


//CAN2���ݾͽ����жϣ�������̨������ݣ�3510Ħ�������ݣ�
void CAN2_RX0_IRQHandler(void)
{
    static uint8_t SuperGyoStartFlag = 0;
    u8Todouble dataTrans;
    
    CAN_Receive(CAN2, 0, &CanRxData2);
    
    switch(CanRxData2.StdId)
    {
        case    YAWCANID  :
        {
            YawMotorFrameCounter++;
            YawMotorAngle = ((int16_t)CanRxData2.Data[0] << 8) | CanRxData2.Data[1];
            break;
        }
        case    PITCHCANID  :
        {
            PitchMotorFrameCounter++;
            PitchMotorAngle = ((int16_t)CanRxData2.Data[0] << 8) | CanRxData2.Data[1];
            break;
        }
        case    SUPERGYROSCOPECANIC :
        {
            if(SuperGyoStartFlag)
            {
                SuperGyoFrameCounter++;
                
                LastSuperGyoAngle = SuperGyoAngle;
                
                dataTrans.uint8_tdata[0] = CanRxData2.Data[0];
                dataTrans.uint8_tdata[1] = CanRxData2.Data[1];
                dataTrans.uint8_tdata[2] = CanRxData2.Data[2];
                dataTrans.uint8_tdata[3] = CanRxData2.Data[3];
                
                SuperGyoAngle = dataTrans.floatdata;
                
                SuperGyoOmega = 200 * (SuperGyoAngle - LastSuperGyoAngle);
                
                SuperGyoMotorEncoderOmega = 1.388889F * SuperGyoOmega;
            }
            //��һ���յ�����
            else
            {
                dataTrans.uint8_tdata[0] = CanRxData1.Data[0];
                dataTrans.uint8_tdata[1] = CanRxData1.Data[1];
                dataTrans.uint8_tdata[2] = CanRxData1.Data[2];
                dataTrans.uint8_tdata[3] = CanRxData1.Data[3];
                LastSuperGyoAngle = dataTrans.floatdata;
                SuperGyoAngle = LastSuperGyoAngle;
                
                SuperGyoOmega = 0;
                SuperGyoStartFlag = 1;
            }
            break;
        }
    }
    
	CAN_ITConfig(CAN2, CAN_IT_FMP0, ENABLE);
}


//DBUS�����ж�
void UART5_IRQHandler(void)
{
    temp = UART5->DR;
    temp = UART5->SR;
    
    DMA_Cmd(DMA1_Stream0, DISABLE);
    
    //��������ȷ
    if(DMA1_Stream0->NDTR == DBUSBackLength)
    {
        DBUSFrameCounter++;         //֡������
        DBUS_DataDecoding();        //����
    }
    
    //����DMA
    DMA_ClearFlag(DMA1_Stream0, DMA_FLAG_TCIF0 | DMA_FLAG_HTIF0);
    while(DMA_GetCmdStatus(DMA1_Stream0) != DISABLE);
    DMA_SetCurrDataCounter(DMA1_Stream0, DBUSLength + DBUSBackLength);
    DMA_Cmd(DMA1_Stream0, ENABLE);
}


//PC�Ӿ����� �����ж�
void USART1_IRQHandler(void)
{
    uint8_t i, Sum = 0;
    FormatTrans Buffer;
    
    temp = USART1->SR;          //��USART1->DR��ȡ������ORDλ
    
    PCDataBufferPoint = (PCDataBufferPoint + 1) % PCDATALENGTH;
    PCDataBuffer[PCDataBufferPoint] = USART1->DR;
    
    //��֡ͷ
    if ((PCDataBuffer[(PCDataBufferPoint + 1) % PCDATALENGTH] == 0x44) &&
        (PCDataBuffer[(PCDataBufferPoint + 2) % PCDATALENGTH] == 0xBB) &&
        (PCDataBuffer[PCDataBufferPoint] == 0xFF))
    {
        for (i = 4; i <= 23; i++)       //��У��� 
        {
            Sum += PCDataBuffer[(PCDataBufferPoint + i) % PCDATALENGTH];
        }

        if (PCDataBuffer[(PCDataBufferPoint + 24) % PCDATALENGTH] == (Sum & 0xFF))       //У��ͨ��
        {
            if(PCDataBuffer[(PCDataBufferPoint + 3) % PCDATALENGTH] != 0)
            {
                PCFrameCounter++;
                
                EnemyDataBufferPoint = (EnemyDataBufferPoint + 1) % ENEMYDATABUFFERLENGHT;
                
                //����
                Buffer.u8[3] = PCDataBuffer[(PCDataBufferPoint + 4) % PCDATALENGTH];
                Buffer.u8[2] = PCDataBuffer[(PCDataBufferPoint + 5) % PCDATALENGTH];
                Buffer.u8[1] = PCDataBuffer[(PCDataBufferPoint + 6) % PCDATALENGTH];
                Buffer.u8[0] = PCDataBuffer[(PCDataBufferPoint + 7) % PCDATALENGTH];
                EnemyDataBuffer[EnemyDataBufferPoint].X = Buffer.F;

                Buffer.u8[3] = PCDataBuffer[(PCDataBufferPoint + 8) % PCDATALENGTH];
                Buffer.u8[2] = PCDataBuffer[(PCDataBufferPoint + 9) % PCDATALENGTH];
                Buffer.u8[1] = PCDataBuffer[(PCDataBufferPoint + 10) % PCDATALENGTH];
                Buffer.u8[0] = PCDataBuffer[(PCDataBufferPoint + 11) % PCDATALENGTH];
                EnemyDataBuffer[EnemyDataBufferPoint].Y = Buffer.F;

                Buffer.u8[3] = PCDataBuffer[(PCDataBufferPoint + 12) % PCDATALENGTH];
                Buffer.u8[2] = PCDataBuffer[(PCDataBufferPoint + 13) % PCDATALENGTH];
                Buffer.u8[1] = PCDataBuffer[(PCDataBufferPoint + 14) % PCDATALENGTH];
                Buffer.u8[0] = PCDataBuffer[(PCDataBufferPoint + 15) % PCDATALENGTH];
                EnemyDataBuffer[EnemyDataBufferPoint].Z = Buffer.F;

                Buffer.u8[3] = PCDataBuffer[(PCDataBufferPoint + 16) % PCDATALENGTH];
                Buffer.u8[2] = PCDataBuffer[(PCDataBufferPoint + 17) % PCDATALENGTH];
                Buffer.u8[1] = PCDataBuffer[(PCDataBufferPoint + 18) % PCDATALENGTH];
                Buffer.u8[0] = PCDataBuffer[(PCDataBufferPoint + 19) % PCDATALENGTH];
                EnemyDataBuffer[EnemyDataBufferPoint].TimeStamp = Buffer.F;

                Buffer.u8[3] = PCDataBuffer[(PCDataBufferPoint + 20) % PCDATALENGTH];
                Buffer.u8[2] = PCDataBuffer[(PCDataBufferPoint + 21) % PCDATALENGTH];
                Buffer.u8[1] = PCDataBuffer[(PCDataBufferPoint + 22) % PCDATALENGTH];
                Buffer.u8[0] = PCDataBuffer[(PCDataBufferPoint + 23) % PCDATALENGTH];
                EnemyDataBuffer[EnemyDataBufferPoint].Time = Buffer.I;

                EnemyDataBuffer[EnemyDataBufferPoint].ID = PCDataBuffer[(PCDataBufferPoint + 3) % PCDATALENGTH];
            }
        }
    }
    
}













