#ifndef __COMMONDATASTRUCTURE_H
#define __COMMONDATASTRUCTURE_H

/******************************************************
���ļ�Ϊ�������ݽṹ
******************************************************/

#include "stm32f4xx.h"


//��ʽת��������
typedef union
{
    uint8_t u8[4];
    float F;
    int I;
}FormatTrans;



#endif
