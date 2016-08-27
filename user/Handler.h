
#ifndef __HANDLER_H
#define __HANDLER_H


#include "stm32f4xx.h"
#include "OSinclude.h"


#ifdef  __HANDLER_GLOBALS
#define __HANDLER_EXT
#else
#define __HANDLER_EXT   extern
#endif


/************************   ���о��    ************************/
__HANDLER_EXT   xQueueHandle    Queue_CANSend;                  //CAN���Ͷ��о��
/************************   ������    ************************/
__HANDLER_EXT   TaskHandle_t    TaskHandle_BellOnce;            //���η�����������
__HANDLER_EXT   TaskHandle_t    TaskHandle_BellCycle;           //ѭ�����������






#endif
