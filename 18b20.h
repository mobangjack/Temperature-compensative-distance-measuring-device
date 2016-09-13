#ifndef __DS18B20_H__
#define __DS18B20_H__

#include<reg52.h>
#include<intrins.h>

#define uchar unsigned char
#define uint   unsigned int;

/*------------------------------------------------
                  函数声明
------------------------------------------------*/

bit Initialize_DS18B20(void);//DS18B20初始化及状态检测
unsigned char ReadOneChar(void);//读取一个字节
void WriteOneChar(unsigned char dat);//写入一个字节
float ReadTemperature(void);//读取温度

#endif
