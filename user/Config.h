#ifndef __CONFIG_H
#define __CONFIG_H

/***************************************   �� �����ֲ���  �� **********************************************/
#define VISIONDEBUG             1           //�Ӿ�debugģʽ
#define INFANTRY                2           //1��Ħ       2����˹��       3��ʿ��

#if INFANTRY == 1               //��Ħ������

#define MAXWORKINGSPEED         850         //����ǰ�������ٶȣ����900��
#define MAXSHIFTSPEED           1200        //����ǰ�������ٶ�
#define SNEAKSPEED              100         //Ǳ���ٶ�
#define QESPINPARAM             0.9F        //QE����ϵ����Խ������Խ�죬����ᷢ��������Ӧ�����ϣ�
#define FRICMOTORWORKINGSPEED   230         //Ħ���ֹ����ٶ�(230)
#define POKESTEPSPEED           -200        //������������ٶȣ����ſ��Ʒ��򣬲�Ҫ����
#define POKESTEPMINTIMECRACK    215         //������Сʱ������ms��
#define MOUSESPINPARAM          16.0F       //�������ϵ����ԽС����Խ�죬��С�ᷢ��������Ӧ�����ϣ�
#define MOUSEINTLIMIT           0.9F        //�����ת�ٶ����ޣ��������תʱ�����ٶȸ��������С��ֵ
#define POKESTRUCKDEALLINES     200         //�������������ת��������

#elif INFANTRY == 2               //����˹�Ӳ�����

#define MAXWORKINGSPEED         850         //����ǰ�������ٶȣ����900��
#define MAXSHIFTSPEED           1200        //����ǰ�������ٶ�
#define SNEAKSPEED              100         //Ǳ���ٶ�
#define QESPINPARAM             0.9F        //QE����ϵ����Խ������Խ�죬����ᷢ��������Ӧ�����ϣ�
#define FRICMOTORWORKINGSPEED   230         //Ħ���ֹ����ٶ�(230)
#define POKESTEPSPEED           -200        //������������ٶȣ����ſ��Ʒ��򣬲�Ҫ����
#define POKESTEPMINTIMECRACK    215         //������Сʱ������ms��
#define MOUSESPINPARAM          16.0F       //�������ϵ����ԽС����Խ�죬��С�ᷢ��������Ӧ�����ϣ�
#define MOUSEINTLIMIT           0.9F        //�����ת�ٶ����ޣ��������תʱ�����ٶȸ��������С��ֵ
#define POKESTRUCKDEALLINES     200         //�������������ת��������

#elif INFANTRY == 3               //��ʿ�������

#define MAXWORKINGSPEED         850         //����ǰ�������ٶȣ����900��
#define MAXSHIFTSPEED           1200        //����ǰ�������ٶ�
#define SNEAKSPEED              100         //Ǳ���ٶ�
#define QESPINPARAM             0.9F        //QE����ϵ����Խ������Խ�죬����ᷢ��������Ӧ�����ϣ�
#define FRICMOTORWORKINGSPEED   230         //Ħ���ֹ����ٶ�(230)
#define POKESTEPSPEED           -200        //������������ٶȣ����ſ��Ʒ��򣬲�Ҫ����
#define POKESTEPMINTIMECRACK    215         //������Сʱ������ms��
#define MOUSESPINPARAM          24.0F       //�������ϵ����ԽС����Խ�죬��С�ᷢ��������Ӧ�����ϣ�
#define MOUSEINTLIMIT           0.9F        //�����ת�ٶ����ޣ��������תʱ�����ٶȸ��������С��ֵ
#define POKESTRUCKDEALLINES     200         //�������������ת��������

#endif
/***************************************   �� �����ֲ���  �� **********************************************/



#define CANPORT             1           //ѡ��can�˿�
//#define MOTORTYPE           1           //������ͣ����ܣ�

#define DEBUGEMODE			1           //debugeģʽ
#define BELLBARKPeriod      100         //����������ʱ�䳤�ȣ�ms��
#define MONITORPERIOD       100         //���������ڣ�ms��

#define BEBUG_MODE          1           //debugģʽ

#define ArtilleryShotCrack  2300        //�ڷ�����ʱ��
#define SrtilleryPushTick   500         //�������Ƴ�ʱ��

#define GUNSpeed            23.0F       //ǹ�ӵ��ٶ�(m/s)
#define ARTILLERYSpeed      14.0F       //���ٶ�(m/s)

#define AFG                 9.87F       //acceleration of gravity�������ٶ�

#define ProgonsisCompensate 370         //Ԥ��ʱ�䲹��

#endif
