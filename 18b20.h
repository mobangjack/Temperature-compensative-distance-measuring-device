#ifndef __DS18B20_H__
#define __DS18B20_H__

#include<reg52.h>
#include<intrins.h>

#define uchar unsigned char
#define uint   unsigned int;

/*------------------------------------------------
                  ��������
------------------------------------------------*/

bit Initialize_DS18B20(void);//DS18B20��ʼ����״̬���
unsigned char ReadOneChar(void);//��ȡһ���ֽ�
void WriteOneChar(unsigned char dat);//д��һ���ֽ�
float ReadTemperature(void);//��ȡ�¶�

#endif
