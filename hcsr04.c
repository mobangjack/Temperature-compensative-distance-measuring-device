/**********************************
******HC-SR04����ӳ���************
**********************************/
 #include <reg52.h>
 #include <stdio.h>
 #include <math.h>
 #include "delay.h"
 #include "hcsr04.h"

 
 sbit TRIG=P1^6;//����HC-SR04�����źŶ˿�
 sbit ECHO=P1^7;//����HC-SR04�����źŶ˿�



 //��ʼ��HC-SR04
 void Initialize_HCSR04()
 {
 TMOD|=0x01;//���ö�ʱ������ģʽ
 TH0=0;//װ�ض�ʱ����ֵ
 TL0=0;
 TRIG=0;
 ECHO=0;
 }

 //���(�������ٲ���7�Σ�Ȼ��ȥ��һ�����ֵ��һ����Сֵ���������ƽ��)
 float MeasureDistance(float CurrentSpeed)
 {
 float S=0;
 float T=0;
 unsigned char i,j;
 float Data[7],tmp;
 for(i=0;i<7;i++)
 {
 Initialize_HCSR04();
 DelayUs2x(10);//��ʱ15us
 TRIG=1;
 while(!ECHO); //�ȴ��ߵ�ƽ
 TR0=1;        //��ʼ��ʱ
 while(ECHO);  //�ȴ��͵�ƽ
 TR0=0;        //ֹͣ��ʱ
 T=(TH0*256+TL0);//ȡ����ʱ��ֵ��8λ�͵�8λ�ϲ�
 Data[i]=CurrentSpeed*T/2000;//��λ��mm
 }
 for(i=0;i<7;i++)
 {
 for(j=0;j<7-i;j++)
 {
 if(Data[j]>Data[j+1])
 	{
	tmp=Data[j];
	Data[j]=Data[j+1];
	Data[j+1]=tmp;
	}
 }
 }
 for(i=1;i<6;i++)
 {
 S+=Data[i];
 }
 return S/5;
 }

