

#ifndef __CONFIG_H
#define __CONFIG_H


#define DEBUGECONTROLRC             0           //debugģʽң�ؿ���
#define USEESP8266                  0           //ʹ��ESP8266���ز���ϵͳ����

/***************************************   �� �����ֲ���  �� **********************************************/
#define INFANTRY                    2           //1��Ħ   2����˹��   3��ʿ��    4 ��ë��ԭ���б����ģ����ɵ���������ˣ����������ң�  5 ����       6 СӢ��

#if INFANTRY == 1               //��Ħ������

    #define FRICMOTORWORKINGSPEED   165         //Ħ���ֹ����ٶ�(170)
    #define POKESTRUCKDEALLINES     400         //�������������ת��������
    #define CHASSISMAXPOWERRATE     1.0F       //�������Ƽ��޹��ʣ�80W������(�����ֵΪ0.9����ʵ�����ƹ���Ϊ0.9*80=72W��
    #define POKESTEPSPEED           -250        //������������ٶȣ����ſ��Ʒ��򣬲�Ҫ����
    #define POKESTEPMINTIMECRACK    265         //������Сʱ������ms��
    #define MAXWORKINGSPEED         850         //�����˶��ٶȣ����900��
    #define DEPOTABSPITCH           -8.0F       //������վ��̨pitch���ԽǶ�ֵ��0Ϊˮƽ��-20 ~ 20��  
    #define SNEAKSPEED              150         //Ǳ���ٶ�
    #define SWINGMODELIMIT          30          //ҡ��ģʽ�����޷�(�����޸ģ����ø���40�������ģʽ����ʧЧ)
    #define SWINGMODEOMEGA          90          //ҡ��ģʽ���ٶ�
    #define CIRCLEMODEOMEGA         300         //ȦȦģʽ���ٶ�
    #define CIRCLEMODEDELAY         10000       //ȦȦģʽ�ܵ��˺���תʱ��  
    
#elif INFANTRY == 2               //����˹�Ӳ�����

    #define FRICMOTORWORKINGSPEED   160         //Ħ���ֹ����ٶ�(170)
    #define POKESTRUCKDEALLINES     400         //�������������ת��������
    #define CHASSISMAXPOWERRATE     0.82F       //�������Ƽ��޹��ʣ�80W������(�����ֵΪ0.9����ʵ�����ƹ���Ϊ0.9*80=72W��
    #define POKESTEPSPEED           -250        //������������ٶȣ����ſ��Ʒ��򣬲�Ҫ����
    #define POKESTEPMINTIMECRACK    265         //������Сʱ������ms��
    #define MAXWORKINGSPEED         850         //�����˶��ٶȣ����900��
    #define DEPOTABSPITCH           -8.0F       //������վ��̨pitch���ԽǶ�ֵ��0Ϊˮƽ��-20 ~ 20��  
    #define SNEAKSPEED              150         //Ǳ���ٶ�
    #define SWINGMODELIMIT          30          //ҡ��ģʽ�����޷�(�����޸ģ����ø���40�������ģʽ����ʧЧ)
    #define SWINGMODEOMEGA          90          //ҡ��ģʽ���ٶ�
    #define CIRCLEMODEOMEGA         300         //ȦȦģʽ���ٶ�
    #define CIRCLEMODEDELAY         10000       //ȦȦģʽ�ܵ��˺���תʱ��    

#elif INFANTRY == 3               //��ʿ�������

    #error this type of infantry has not been debuged

//    #define MAXWORKINGSPEED         850         //����ǰ�������ٶȣ����900��
//    #define MAXSHIFTSPEED           1200        //����ƽ���ٶ�
//    #define SNEAKSPEED              100         //Ǳ���ٶ�
//    #define QESPINPARAM             27                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               -  //QE����ϵ����Խ������Խ�죬����ᷢ��������Ӧ�����ϣ�
//    #define FRICMOTORWORKINGSPEED   285         //Ħ���ֹ����ٶ�(230)
//    #define POKESTEPSPEED           -250        //������������ٶȣ����ſ��Ʒ��򣬲�Ҫ����
//    #define POKESTEPMINTIMECRACK    265         //������Сʱ������ms��
//    #define MOUSESPINPARAM          20.0F       //�������ϵ����ԽС����Խ�죬��С�ᷢ��������Ӧ�����ϣ�
//    #define MOUSEPITCHPARAM         15.0F       //���pitch����ϵ����ԽС�ٶ�Խ�죩
//    #define POKESTRUCKDEALLINES     300         //�������������ת��������
//    #define LOWSPEEDOVERRIDE        0.65F       //���̵���Ϊȫ�ٵĶ��ٱ���0-1��
//    #define DEPOTABSPITCH           -350        //������վ��̨pitch������ֵ��0Ϊˮƽ��-200 ~ 200�� 
//    #define CHASSISMAXPOWERRATE     0.82F       //�������Ƽ��޹��ʣ�80W������ (�����ֵΪ0.9����ʵ�����ƹ���Ϊ0.9*80=72W��
//    #define AUTOSHOTTICKCRACK       400         //ȫ�Զ����ʱ����
//    #define LOSTTARGETTICKAUTO      2000        //��ָ֡��ʱ�俪ʼѲ��
//    #define FULLAUTOCHASSISANGLE    60          //ȫ�Զ�ģʽ������ת���߽Ƕȷ�Χ
//    #define FULLAUTOCHASSISSPEED    0.3F        //ȫ�Զ�ģʽ������ת�ٶ�

#elif INFANTRY == 4               //��ë

    #define FRICMOTORWORKINGSPEED   310         //Ħ���ֹ����ٶ�(230)
    #define POKESTRUCKDEALLINES     400          //�������������ת��������
    #define CHASSISMAXPOWERRATE     0.82F       //�������Ƽ��޹��ʣ�80W������(�����ֵΪ0.9����ʵ�����ƹ���Ϊ0.9*80=72W��
    #define POKESTEPSPEED           -250        //������������ٶȣ����ſ��Ʒ��򣬲�Ҫ����
    #define POKESTEPMINTIMECRACK    265         //������Сʱ������ms��
    #define MAXWORKINGSPEED         850         //�����˶��ٶȣ����900��
    #define DEPOTABSPITCH           -8.0F       //������վ��̨pitch���ԽǶ�ֵ��0Ϊˮƽ��-20 ~ 20��  
    #define SNEAKSPEED              150         //Ǳ���ٶ�
    #define SWINGMODELIMIT          30          //ҡ��ģʽ�����޷�(�����޸ģ����ø���40�������ģʽ����ʧЧ)
    #define SWINGMODEOMEGA          90          //ҡ��ģʽ���ٶ�
    #define CIRCLEMODEOMEGA         300         //ȦȦģʽ���ٶ�
    #define CIRCLEMODEDELAY         10000       //ȦȦģʽ�ܵ��˺���תʱ��  


#elif INFANTRY == 5               //����

    #define FRICMOTORWORKINGSPEED   260         //Ħ���ֹ����ٶ�(230)
    #define POKESTRUCKDEALLINES     400          //�������������ת��������
    #define CHASSISMAXPOWERRATE     0.82F       //�������Ƽ��޹��ʣ�80W������(�����ֵΪ0.9����ʵ�����ƹ���Ϊ0.9*80=72W��
    #define POKESTEPSPEED           -250        //������������ٶȣ����ſ��Ʒ��򣬲�Ҫ����
    #define POKESTEPMINTIMECRACK    265         //������Сʱ������ms��
    #define MAXWORKINGSPEED         850         //�����˶��ٶȣ����900��
    #define DEPOTABSPITCH           -8.0F       //������վ��̨pitch���ԽǶ�ֵ��0Ϊˮƽ��-20 ~ 20��  
    #define SNEAKSPEED              150         //Ǳ���ٶ�
    #define SWINGMODELIMIT          30          //ҡ��ģʽ�����޷�(�����޸ģ����ø���40�������ģʽ����ʧЧ)
    #define SWINGMODEOMEGA          90          //ҡ��ģʽ���ٶ�
    #define CIRCLEMODEOMEGA         300         //ȦȦģʽ���ٶ�
    #define CIRCLEMODEDELAY         10000       //ȦȦģʽ�ܵ��˺���תʱ��    

#elif INFANTRY == 6               //���ز�����

    #define FRICMOTORWORKINGSPEED   260         //Ħ���ֹ����ٶ�(230)
    #define POKESTRUCKDEALLINES     400         //�������������ת��������
    #define CHASSISMAXPOWERRATE     0.82F       //�������Ƽ��޹��ʣ�80W������(�����ֵΪ0.9����ʵ�����ƹ���Ϊ0.9*80=72W��
    #define POKESTEPSPEED           -250        //������������ٶȣ����ſ��Ʒ��򣬲�Ҫ����
    #define POKESTEPMINTIMECRACK    265         //������Сʱ������ms��
    #define MAXWORKINGSPEED         850         //�����˶��ٶȣ����900��
    #define DEPOTABSPITCH           -8.0F       //������վ��̨pitch���ԽǶ�ֵ��0Ϊˮƽ��-20 ~ 20��  
    #define SNEAKSPEED              150         //Ǳ���ٶ�
    #define SWINGMODELIMIT          30          //ҡ��ģʽ�����޷�(�����޸ģ����ø���40�������ģʽ����ʧЧ)
    #define SWINGMODEOMEGA          90          //ҡ��ģʽ���ٶ�
    #define CIRCLEMODEOMEGA         300         //ȦȦģʽ���ٶ�
    #define CIRCLEMODEDELAY         10000       //ȦȦģʽ�ܵ��˺���תʱ��   
    #define ARTILLERYFRICSPEED      5000        //��Ħ�����ٶ�    
    #define ARTILLERYSHOTCRACK      220         //�ڷ���ʱ����

#endif
/***************************************   �� �����ֲ���  �� **********************************************/

#if INFANTRY == 1       //��Ħ
    
    #define PITCHMOTORCURRENTPLUSDIR        1           //pitch����̨�����������Ϊ��ʱת������     1 ̧ͷ         0 ��ͷ
    #define YAWMOTORCURRENTPLUSDIR          1           //yaw����̨�����������Ϊ��ʱת������       1 ��ʱ��       0 ˳ʱ��
    #define PITCHMOTORENCODERPLUSEDIR       1           //pitch����̨�������������ʱת������       1 ̧ͷ         0 ��ͷ
    #define YAWMOTORENCODERPLUSEDIR         1           //yaw����̨�������������ʱת������         1 ��ʱ��       0 ˳ʱ��
    #define CANPORT                         1           //ѡ��can�˿�
    #define MOTORTYPE                       1           //�������                                 1 3510        0 35
    #define FRICTYPE                        0           //Ħ��������                               1 3510        0 ��ͨ��ˢ
    
#elif INFANTRY == 2     //����˹��
    
    #define PITCHMOTORCURRENTPLUSDIR        1           //pitch����̨�����������Ϊ��ʱת������     1 ̧ͷ         0 ��ͷ
    #define YAWMOTORCURRENTPLUSDIR          1           //yaw����̨�����������Ϊ��ʱת������       1 ��ʱ��       0 ˳ʱ��
    #define PITCHMOTORENCODERPLUSEDIR       1           //pitch����̨�������������ʱת������       1 ̧ͷ         0 ��ͷ
    #define YAWMOTORENCODERPLUSEDIR         1           //yaw����̨�������������ʱת������         1 ��ʱ��       0 ˳ʱ��
    #define CANPORT                         1           //ѡ��can�˿�
    #define MOTORTYPE                       0           //�������                                 1 3510        0 35
    #define FRICTYPE                        0           //Ħ��������                               1 3510        0 ��ͨ��ˢ

#elif INFANTRY == 3     //��ʿ��
    
    #define PITCHMOTORCURRENTPLUSDIR        1           //pitch����̨�����������Ϊ��ʱת������     1 ̧ͷ         0 ��ͷ
    #define YAWMOTORCURRENTPLUSDIR          1           //yaw����̨�����������Ϊ��ʱת������       1 ��ʱ��       0 ˳ʱ��
    #define PITCHMOTORENCODERPLUSEDIR       1           //pitch����̨�������������ʱת������       1 ̧ͷ         0 ��ͷ
    #define YAWMOTORENCODERPLUSEDIR         1           //yaw����̨�������������ʱת������         1 ��ʱ��       0 ˳ʱ��
    #define CANPORT                         1           //ѡ��can�˿�
    #define MOTORTYPE                       1           //�������                                 1 3510        0 35
    #define FRICTYPE                        0           //Ħ��������                               1 3510        0 ��ͨ��ˢ

#elif INFANTRY == 4     //��ë
    
    #define PITCHMOTORCURRENTPLUSDIR        0           //pitch����̨�����������Ϊ��ʱת������     1 ̧ͷ         0 ��ͷ
    #define YAWMOTORCURRENTPLUSDIR          0           //yaw����̨�����������Ϊ��ʱת������       1 ��ʱ��       0 ˳ʱ��
    #define PITCHMOTORENCODERPLUSEDIR       1           //pitch����̨�������������ʱת������       1 ̧ͷ         0 ��ͷ
    #define YAWMOTORENCODERPLUSEDIR         1           //yaw����̨�������������ʱת������         1 ��ʱ��       0 ˳ʱ��
    #define CANPORT                         1           //ѡ��can�˿�
    #define MOTORTYPE                       0          //�������                                 1 3510        0 35
    #define FRICTYPE                        0           //Ħ��������                               1 3510        0 ��ͨ��ˢ

#elif INFANTRY == 5     //����
    
    #define PITCHMOTORCURRENTPLUSDIR        0           //pitch����̨�����������Ϊ��ʱת������     1 ̧ͷ         0 ��ͷ
    #define YAWMOTORCURRENTPLUSDIR          1           //yaw����̨�����������Ϊ��ʱת������       1 ��ʱ��       0 ˳ʱ��
    #define PITCHMOTORENCODERPLUSEDIR       1           //pitch����̨�������������ʱת������       1 ̧ͷ         0 ��ͷ
    #define YAWMOTORENCODERPLUSEDIR         1           //yaw����̨�������������ʱת������         1 ��ʱ��       0 ˳ʱ��
    #define CANPORT                         1           //ѡ��can�˿�
    #define MOTORTYPE                       1           //�������                                 1 3510        0 35
    #define FRICTYPE                        0           //Ħ��������                               1 3510        0 ��ͨ��ˢ


#elif INFANTRY == 6     //СӢ��
    
    #define PITCHMOTORCURRENTPLUSDIR        2           //pitch����̨�����������Ϊ��ʱת������     1 ̧ͷ         0 ��ͷ
    #define YAWMOTORCURRENTPLUSDIR          1           //yaw����̨�����������Ϊ��ʱת������       1 ��ʱ��       0 ˳ʱ��
    #define PITCHMOTORENCODERPLUSEDIR       0           //pitch����̨�������������ʱת������       1 ̧ͷ         0 ��ͷ
    #define YAWMOTORENCODERPLUSEDIR         1           //yaw����̨�������������ʱת������         1 ��ʱ��       0 ˳ʱ��
    #define CANPORT                         1           //ѡ��can�˿�
    #define MOTORTYPE                       0           //�������                                 1 3510        0 35
    #define FRICTYPE                        1           //Ħ��������                               1 3510        0 ��ͨ��ˢ

#endif

#define BELLBARKPeriod      100         //����������ʱ�䳤�ȣ�ms��
#define MONITORPERIOD       100         //���������ڣ�ms��
#define GUNSpeed            23.5F       //ǹ�ӵ��ٶ�(m/s)
#define ACCofGravity        9.87F       //acceleration of gravity�������ٶ�

#endif


