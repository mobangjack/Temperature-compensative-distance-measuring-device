#include<reg52.h> 
#include<stdio.h>
#include<math.h>
#include "18b20.h"
#include "1602.h"
#include "delay.h"
#include "hcsr04.h"

 sbit KEY=P1^3;
 sbit LED=P1^4;
 float CurrentTemperature;//��ǰ�¶�
 float CurrentSpeed;//��ǰ����
 float CurrentDistance;//����
 char TempDisplayBuf[16];//�¶���ʾ�ַ�������
 char DistanceDisplayBuf[16];//������ʾ�ַ�������

void main (void)
{
LED=0;//����״ָ̬ʾ��������           
LCD_Init();           //��ʼ��Һ��
DelayMs(20);          //��ʱ�������ȶ�
LCD_Clear();          //����
LCD_Write_String(0,0," Sonar System ");
LCD_Write_String(0,1," By: Bangjie Mo ");
DelayS(3);
LCD_Clear();          //����
LCD_Write_String(0,0,"press the key to");
LCD_Write_String(0,1,"measure distance");
while(1)
{
if(KEY==0)//��ⰴ��״̬
{
while(KEY==0);//�ȴ������ͷ�
LED=1;//����״ָ̬ʾ�����ڲ���
CurrentTemperature=ReadTemperature();//��ȡ��ǰ�¶�
DelayMs(1);
CurrentSpeed=331.4*sqrt(1+CurrentTemperature/273);//���㵱ǰ����
DelayMs(1);
CurrentDistance=MeasureDistance(CurrentSpeed);//��������
if(CurrentDistance>4000||CurrentDistance<20)//DS18B20����Ч������ΧΪ20mm~4000mm
{
LCD_Clear();          //����
LCD_Write_String(0,0,"    Warning !   ");//����������Χ����
LCD_Write_String(0,1," Out of range ! ");//����������Χ����
LED=1;//��������
}
else
{
sprintf(TempDisplayBuf,"T = %6.3f",CurrentTemperature);//������ֵ��ӡ���ַ���������
sprintf(DistanceDisplayBuf,"D = %8.3f mm",CurrentDistance);//������ֵ��ӡ���ַ���������
DelayMs(1);
LCD_Clear();
LCD_Write_String(0,1,DistanceDisplayBuf);//��ʾ��������
LCD_Write_String(0,0,TempDisplayBuf);//��ʾ��ǰ�¶�
LCD_Write_Char(13,0,0xDF);
LCD_Write_Char(14,0,'C');
LED=0;//����״ָ̬ʾ����������
DelayMs(1);
}
}
}
}
