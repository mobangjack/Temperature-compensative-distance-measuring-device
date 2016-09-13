#include<reg52.h> 
#include<stdio.h>
#include<math.h>
#include "18b20.h"
#include "1602.h"
#include "delay.h"
#include "hcsr04.h"

 sbit KEY=P1^3;
 sbit LED=P1^4;
 float CurrentTemperature;//当前温度
 float CurrentSpeed;//当前声速
 float CurrentDistance;//距离
 char TempDisplayBuf[16];//温度显示字符串缓冲
 char DistanceDisplayBuf[16];//距离显示字符串缓冲

void main (void)
{
LED=0;//测量状态指示：待测量           
LCD_Init();           //初始化液晶
DelayMs(20);          //延时有助于稳定
LCD_Clear();          //清屏
LCD_Write_String(0,0," Sonar System ");
LCD_Write_String(0,1," By: Bangjie Mo ");
DelayS(3);
LCD_Clear();          //清屏
LCD_Write_String(0,0,"press the key to");
LCD_Write_String(0,1,"measure distance");
while(1)
{
if(KEY==0)//检测按键状态
{
while(KEY==0);//等待按键释放
LED=1;//测量状态指示：正在测量
CurrentTemperature=ReadTemperature();//获取当前温度
DelayMs(1);
CurrentSpeed=331.4*sqrt(1+CurrentTemperature/273);//计算当前声速
DelayMs(1);
CurrentDistance=MeasureDistance(CurrentSpeed);//测量距离
if(CurrentDistance>4000||CurrentDistance<20)//DS18B20的有效测量范围为20mm~4000mm
{
LCD_Clear();          //清屏
LCD_Write_String(0,0,"    Warning !   ");//超出测量范围警告
LCD_Write_String(0,1," Out of range ! ");//超出测量范围警告
LED=1;//灯亮警告
}
else
{
sprintf(TempDisplayBuf,"T = %6.3f",CurrentTemperature);//将测量值打印到字符串缓冲区
sprintf(DistanceDisplayBuf,"D = %8.3f mm",CurrentDistance);//将测量值打印到字符串缓冲区
DelayMs(1);
LCD_Clear();
LCD_Write_String(0,1,DistanceDisplayBuf);//显示测量距离
LCD_Write_String(0,0,TempDisplayBuf);//显示当前温度
LCD_Write_Char(13,0,0xDF);
LCD_Write_Char(14,0,'C');
LED=0;//测量状态指示：测量结束
DelayMs(1);
}
}
}
}
