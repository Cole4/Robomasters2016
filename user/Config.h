#ifndef __CONFIG_H
#define __CONFIG_H

/***************************************   �� �����ֲ���  �� **********************************************/
#define VISIONDEBUG             0           //�Ӿ�debugģʽ
#define INFANTRY                2           //1��Ħ       2����˹��       3��ʿ��        4 �������ֽ�ë��     5 ����  6 Ӣ��
//#define INFANTRYTYPE          1           //������  1 A�������ϵ�Ĭ�Ͽ��Ƴ�(C)   2 AB�����ϵ�Ĭ�Ϸǿ��Ƴ�(F)      3 ������

#if INFANTRY == 1               //��Ħ������

#define MAXWORKINGSPEED         850         //����ǰ�������ٶȣ����900��
#define MAXSHIFTSPEED           1200        //����ƽ���ٶ�
#define SNEAKSPEED              100         //Ǳ���ٶ�
#define QESPINPARAM             0.9F        //QE����ϵ����Խ������Խ�죬����ᷢ��������Ӧ�����ϣ�
#define FRICMOTORWORKINGSPEED   350         //Ħ���ֹ����ٶ�(230)
#define POKESTEPSPEED           -250        //������������ٶȣ����ſ��Ʒ��򣬲�Ҫ����
#define POKESTEPMINTIMECRACK    220         //������Сʱ������ms��
#define MOUSESPINPARAM          16.0F       //�������ϵ����ԽС����Խ�죬��С�ᷢ��������Ӧ�����ϣ�
#define MOUSEPITCHPARAM         20.0F       //���pitch����ϵ����ԽС�ٶ�Խ�죩
#define POKESTRUCKDEALLINES     300         //�������������ת��������
#define LOWSPEEDOVERRIDE        0.65F       //���̵���Ϊȫ�ٵĶ��ٱ���0-1��
#define DEPOTABSPITCH           -120        //������վ��̨pitch������ֵ��0Ϊˮƽ��-200 ~ 200�� 
#define CHASSISMAXPOWERRATE     0.82F       //�������Ƽ��޹��ʣ�80W������(�����ֵΪ0.9����ʵ�����ƹ���Ϊ0.9*80=72W��
#define AUTOSHOTTICKCRACK       400         //ȫ�Զ����ʱ����

#elif INFANTRY == 2               //����˹�Ӳ�����

#define MAXWORKINGSPEED         850         //����ǰ�������ٶȣ����900��
#define MAXSHIFTSPEED           1200        //����ƽ���ٶ�
#define SNEAKSPEED              100         //Ǳ���ٶ�
#define QESPINPARAM             0.9F        //QE����ϵ����Խ������Խ�죬����ᷢ��������Ӧ�����ϣ�
#define FRICMOTORWORKINGSPEED   260         //Ħ���ֹ����ٶ�(230)
#define POKESTEPSPEED           -250        //������������ٶȣ����ſ��Ʒ��򣬲�Ҫ����
#define POKESTEPMINTIMECRACK    200         //������Сʱ������ms��
#define MOUSESPINPARAM          16.0F       //�������ϵ����ԽС����Խ�죬��С�ᷢ��������Ӧ�����ϣ�
#define MOUSEPITCHPARAM         20.0F       //���pitch����ϵ����ԽС�ٶ�Խ�죩
#define POKESTRUCKDEALLINES     300         //�������������ת��������
#define LOWSPEEDOVERRIDE        0.65F       //���̵���Ϊȫ�ٵĶ��ٱ���0-1��
#define DEPOTABSPITCH           -120        //������վ��̨pitch������ֵ��0Ϊˮƽ��-200 ~ 200��  
#define CHASSISMAXPOWERRATE     0.82F       //�������Ƽ��޹��ʣ�80W        ������(�����ֵΪ0.9����ʵ�����ƹ���Ϊ0.9*80=72W��
#define AUTOSHOTTICKCRACK       400         //ȫ�Զ����ʱ����

#elif INFANTRY == 3               //��ʿ��������������ѵ��ڣ�

#define MAXWORKINGSPEED         850         //����ǰ�������ٶȣ����900��
#define MAXSHIFTSPEED           1200        //����ƽ���ٶ�
#define SNEAKSPEED              100         //Ǳ���ٶ�
#define QESPINPARAM             0.9F        //QE����ϵ����Խ������Խ�죬����ᷢ��������Ӧ�����ϣ�
#define FRICMOTORWORKINGSPEED   285         //Ħ���ֹ����ٶ�(230)
#define POKESTEPSPEED           -250        //������������ٶȣ����ſ��Ʒ��򣬲�Ҫ����
#define POKESTEPMINTIMECRACK    215         //������Сʱ������ms��
#define MOUSESPINPARAM          20.0F       //�������ϵ����ԽС����Խ�죬��С�ᷢ��������Ӧ�����ϣ�
#define MOUSEPITCHPARAM         15.0F       //���pitch����ϵ����ԽС�ٶ�Խ�죩
#define POKESTRUCKDEALLINES     300         //�������������ת��������
#define LOWSPEEDOVERRIDE        0.65F       //���̵���Ϊȫ�ٵĶ��ٱ���0-1��
#define DEPOTABSPITCH           -120        //������վ��̨pitch������ֵ��0Ϊˮƽ��-200 ~ 200�� 
#define CHASSISMAXPOWERRATE     0.82F       //�������Ƽ��޹��ʣ�80W������ (�����ֵΪ0.9����ʵ�����ƹ���Ϊ0.9*80=72W��
#define AUTOSHOTTICKCRACK       400         //ȫ�Զ����ʱ����

#elif INFANTRY == 4               //�����������ѵ��ڣ�

#define MAXWORKINGSPEED         850         //����ǰ�������ٶȣ����900��
#define MAXSHIFTSPEED           1200        //����ƽ���ٶ�
#define SNEAKSPEED              100         //Ǳ���ٶ�
#define QESPINPARAM             0.9F        //QE����ϵ����Խ������Խ�죬����ᷢ��������Ӧ�����ϣ�
#define FRICMOTORWORKINGSPEED   318         //Ħ���ֹ����ٶ�(230)
#define POKESTEPSPEED           -250        //������������ٶȣ����ſ��Ʒ��򣬲�Ҫ����
#define POKESTEPMINTIMECRACK    215         //������Сʱ������ms��
#define MOUSESPINPARAM          10.0F       //�������ϵ����ԽС����Խ�죬��С�ᷢ��������Ӧ�����ϣ�
#define MOUSEPITCHPARAM         10.0F       //���pitch����ϵ����ԽС�ٶ�Խ�죩
#define POKESTRUCKDEALLINES     300         //�������������ת��������
#define LOWSPEEDOVERRIDE        0.65F       //���̵���Ϊȫ�ٵĶ��ٱ���0-1��
#define DEPOTABSPITCH           -120        //������վ��̨pitch������ֵ��0Ϊˮƽ��-200 ~ 200�� 
#define CHASSISMAXPOWERRATE     0.82F       //�������Ƽ��޹��ʣ�80W������ (�����ֵΪ0.9����ʵ�����ƹ���Ϊ0.9*80=72W��
#define AUTOSHOTTICKCRACK       400         //ȫ�Զ����ʱ����

#elif INFANTRY == 5               //����

#define MAXWORKINGSPEED         850         //����ǰ�������ٶȣ����900��
#define MAXSHIFTSPEED           1200        //����ƽ���ٶ�
#define SNEAKSPEED              100         //Ǳ���ٶ�
#define QESPINPARAM             0.9F        //QE����ϵ����Խ������Խ�죬����ᷢ��������Ӧ�����ϣ�
#define FRICMOTORWORKINGSPEED   305         //Ħ���ֹ����ٶ�(230)
#define POKESTEPSPEED           -250        //������������ٶȣ����ſ��Ʒ��򣬲�Ҫ����
#define POKESTEPMINTIMECRACK    215         //������Сʱ������ms��
#define MOUSESPINPARAM          20.0F       //�������ϵ����ԽС����Խ�죬��С�ᷢ��������Ӧ�����ϣ�
#define MOUSEPITCHPARAM         10.0F       //���pitch����ϵ����ԽС�ٶ�Խ�죩
#define POKESTRUCKDEALLINES     300         //�������������ת��������
#define LOWSPEEDOVERRIDE        0.65F       //���̵���Ϊȫ�ٵĶ��ٱ���0-1��
#define DEPOTABSPITCH           -120        //������վ��̨pitch������ֵ��0Ϊˮƽ��-200 ~ 200�� 
#define CHASSISMAXPOWERRATE     0.82F       //�������Ƽ��޹��ʣ�80W������ (�����ֵΪ0.9����ʵ�����ƹ���Ϊ0.9*80=72W��
#define AUTOSHOTTICKCRACK       400         //ȫ�Զ����ʱ����

#elif INFANTRY == 6               //Ӣ��

#define MAXWORKINGSPEED         850         //����ǰ�������ٶȣ����900��
#define MAXSHIFTSPEED           1200        //����ƽ���ٶ�
#define SNEAKSPEED              100         //Ǳ���ٶ�
#define QESPINPARAM             0.9F        //QE����ϵ����Խ������Խ�죬����ᷢ��������Ӧ�����ϣ�
#define FRICMOTORWORKINGSPEED   305         //Ħ���ֹ����ٶ�(230)
#define POKESTEPSPEED           -250        //������������ٶȣ����ſ��Ʒ��򣬲�Ҫ����
#define POKESTEPMINTIMECRACK    215         //������Сʱ������ms��
#define MOUSESPINPARAM          20.0F       //�������ϵ����ԽС����Խ�죬��С�ᷢ��������Ӧ�����ϣ�
#define MOUSEPITCHPARAM         10.0F       //���pitch����ϵ����ԽС�ٶ�Խ�죩
#define POKESTRUCKDEALLINES     300         //�������������ת��������
#define LOWSPEEDOVERRIDE        0.1F       //���̵���Ϊȫ�ٵĶ��ٱ���0-1��
#define DEPOTABSPITCH           -120        //������վ��̨pitch������ֵ��0Ϊˮƽ��-200 ~ 200�� 
#define CHASSISMAXPOWERRATE     0.82F       //�������Ƽ��޹��ʣ�160W������ (�����ֵΪ0.9����ʵ�����ƹ���Ϊ0.9*160=144W��
#define AUTOSHOTTICKCRACK       400         //ȫ�Զ����ʱ����

#endif
/***************************************   �� �����ֲ���  �� **********************************************/



#define CANPORT             1           //ѡ��can�˿�
//#define MOTORTYPE         1           //������ͣ����ܣ�

#define DEBUGEMODE			1           //debugeģʽ
#define BELLBARKPeriod      100         //����������ʱ�䳤�ȣ�ms��
#define MONITORPERIOD       100         //���������ڣ�ms��

#define BEBUG_MODE          1           //debugģʽ

#define ArtilleryShotCrack  2300        //�ڷ�����ʱ��
#define SrtilleryPushTick   500         //�������Ƴ�ʱ��

#define GUNSpeed            23.5F       //ǹ�ӵ��ٶ�(m/s)
#define ARTILLERYSpeed      14.0F       //���ٶ�(m/s)

#define AFG                 9.87F       //acceleration of gravity�������ٶ�

#define ProgonsisCompensate 370         //Ԥ��ʱ�䲹��

#endif
