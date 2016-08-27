#define __DRIVER_ESP8266_GLOBALS


#include "OSinclude.h"
#include "Driver_ESP8266.h"
#include "StringDecoding.h"


/**
  * @brief  ESP8266��ʼ��
  * @param  void
  * @retval 1 ��ʼ���ɹ�         0 ��ʼ��ʧ��
  */
void ESP8266_InitConfig(void)
{
    
}


/**
  * @brief  ��ESP8266����һ������(��ESP8266ControlTXBuffer[ESP8266ControlTXBufferLenght])
  * @param  ������
  * @retval void
  */
void ESP8266_SendPack(uint16_t Num)
{
    DMA_Cmd(DMA1_Stream3, DISABLE);                                     //�ر� DMA ����
    while (DMA_GetCmdStatus(DMA1_Stream3) != DISABLE){}                 //ȷ�� DMA ���Ա�����
    DMA_ClearFlag(DMA1_Stream3, DMA_FLAG_TCIF3 | DMA_FLAG_HTIF3);       //��ձ�־λ
    DMA1_Stream3->M0AR = (uint32_t)ESP8266TXBuffer;              //��������
    DMA_SetCurrDataCounter(DMA1_Stream3, Num);                          //���ݴ�����
    DMA_Cmd(DMA1_Stream3, ENABLE);                                      //���� DMA ����
}


/**
  * @brief  ESP8266����

 */



