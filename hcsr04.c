/**********************************
******HC-SR04测距子程序************
**********************************/
 #include <reg52.h>
 #include <stdio.h>
 #include <math.h>
 #include "delay.h"
 #include "hcsr04.h"

 
 sbit TRIG=P1^6;//定义HC-SR04控制信号端口
 sbit ECHO=P1^7;//定义HC-SR04回响信号端口



 //初始化HC-SR04
 void Initialize_HCSR04()
 {
 TMOD|=0x01;//设置定时器工作模式
 TH0=0;//装载定时器初值
 TL0=0;
 TRIG=0;
 ECHO=0;
 }

 //测距(连续快速测量7次，然后去掉一个最大值和一个最小值，最后再求平均)
 float MeasureDistance(float CurrentSpeed)
 {
 float S=0;
 float T=0;
 unsigned char i,j;
 float Data[7],tmp;
 for(i=0;i<7;i++)
 {
 Initialize_HCSR04();
 DelayUs2x(10);//延时15us
 TRIG=1;
 while(!ECHO); //等待高电平
 TR0=1;        //开始计时
 while(ECHO);  //等待低电平
 TR0=0;        //停止计时
 T=(TH0*256+TL0);//取出定时器值高8位和低8位合并
 Data[i]=CurrentSpeed*T/2000;//单位：mm
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

