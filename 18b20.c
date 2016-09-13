/************************************************
 **************DS18B20�����ӳ���*****************
************************************************/
#include"delay.h"
#include"18b20.h"


sbit DQ=P1^0;//DS18B20 �˿�

bit Initialize_DS18B20(void)//DS18B20��ʼ����״̬���
{
 bit dat=0;
 DQ = 1;    	//DQ��λ
 DelayUs2x(5);   //������ʱ
 DQ = 0;         //��������
 DelayUs2x(200); //��ʱ480us~960us
 DelayUs2x(100);
 DQ = 1;        //��������
 DelayUs2x(50); //15~60us �� ����60-240us�Ĵ�������
 dat=DQ;        //���x=0���ʼ���ɹ�, x=1���ʼ��ʧ��
 DelayUs2x(25); //������ʱ�ٷ���
 return dat;
}


unsigned char ReadOneChar(void)//��ȡһ���ֽ�
{
unsigned char i=0;
unsigned char dat=0;
for (i=8;i>0;i--)
 {
  DQ = 0; // �������ߣ��������ź�
  dat>>=1;
  DQ = 1; // �������ߣ�׼����һλ
  if(DQ)
   dat|=0x80;
  DelayUs2x(25);
 }
 return(dat);
}

void WriteOneChar(unsigned char dat)//д��һ���ֽ�
{
 unsigned char i=0;
 for (i=8; i>0; i--)
 {
  DQ = 0;// �������ߣ�׼��дһλ
  DQ = dat&0x01;//дһλ
  DelayUs2x(30);//��ʱ60us����
  DQ = 1;// ��������
  dat>>=1;
 }
DelayUs2x(25);
}

/*------------------------------------------------
                    ��ȡ�¶�
------------------------------------------------*/
float ReadTemperature(void)
{
float Temperature;
unsigned char LSB=0;
unsigned int MSB=0;
Initialize_DS18B20();//��λ
WriteOneChar(0xCC); // ����������кŵĲ���
WriteOneChar(0x44); // �����¶�ת��
DelayUs2x(10);
Initialize_DS18B20();//��λ
WriteOneChar(0xCC); //����������кŵĲ��� 
WriteOneChar(0xBE); //��ȡ�¶ȼĴ���
LSB=ReadOneChar();   //�ȶ��¶ȵ��ֽ�
MSB=ReadOneChar();   //����¶ȸ��ֽ�
MSB<<=8;
MSB=(unsigned int)(MSB+LSB);
Temperature=(float)(MSB*0.0625);
return Temperature;
}
