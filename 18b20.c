/************************************************
 **************DS18B20测温子程序*****************
************************************************/
#include"delay.h"
#include"18b20.h"


sbit DQ=P1^0;//DS18B20 端口

bit Initialize_DS18B20(void)//DS18B20初始化及状态检测
{
 bit dat=0;
 DQ = 1;    	//DQ复位
 DelayUs2x(5);   //稍做延时
 DQ = 0;         //拉低总线
 DelayUs2x(200); //延时480us~960us
 DelayUs2x(100);
 DQ = 1;        //拉高总线
 DelayUs2x(50); //15~60us 后 接收60-240us的存在脉冲
 dat=DQ;        //如果x=0则初始化成功, x=1则初始化失败
 DelayUs2x(25); //稍作延时再返回
 return dat;
}


unsigned char ReadOneChar(void)//读取一个字节
{
unsigned char i=0;
unsigned char dat=0;
for (i=8;i>0;i--)
 {
  DQ = 0; // 拉低总线，产生读信号
  dat>>=1;
  DQ = 1; // 拉高总线，准备读一位
  if(DQ)
   dat|=0x80;
  DelayUs2x(25);
 }
 return(dat);
}

void WriteOneChar(unsigned char dat)//写入一个字节
{
 unsigned char i=0;
 for (i=8; i>0; i--)
 {
  DQ = 0;// 拉低总线，准备写一位
  DQ = dat&0x01;//写一位
  DelayUs2x(30);//延时60us以上
  DQ = 1;// 拉高总线
  dat>>=1;
 }
DelayUs2x(25);
}

/*------------------------------------------------
                    读取温度
------------------------------------------------*/
float ReadTemperature(void)
{
float Temperature;
unsigned char LSB=0;
unsigned int MSB=0;
Initialize_DS18B20();//复位
WriteOneChar(0xCC); // 跳过读序号列号的操作
WriteOneChar(0x44); // 启动温度转换
DelayUs2x(10);
Initialize_DS18B20();//复位
WriteOneChar(0xCC); //跳过读序号列号的操作 
WriteOneChar(0xBE); //读取温度寄存器
LSB=ReadOneChar();   //先读温度低字节
MSB=ReadOneChar();   //后读温度高字节
MSB<<=8;
MSB=(unsigned int)(MSB+LSB);
Temperature=(float)(MSB*0.0625);
return Temperature;
}
