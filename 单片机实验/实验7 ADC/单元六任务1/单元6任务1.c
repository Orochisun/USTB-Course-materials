#include "ioCC2530.h"
#define uint unsigned int
#define uchar unsigned char

//定义控制灯的端口
#define LED1 P0_5	//定义LED1为P0_5口控制
#define LED2 P0_6	//定义LED2为P0_6口控制

void delay(uint);
void initUART(void);
void InitialAD(void);
void UartTX_Send_String(char *Data,int len);

char adcdata[]=" 0.0V\n ";


/****************************************************************
*函数功能 ：主函数						*
*入口参数 ：无							*
*返 回 值 ：无							*
*说    明 ：无							*
****************************************************************/
void main(void)
{	
  P0DIR |= 0x60;
  
  
  char temp[2];
  uint adc;
  float num;
  initUART();   //初始化串口
  InitialAD();       //初始化ADC

  while(1)
  {       
   if(ADCCON1>=0x80)    //ADCCON1.EOC,转换完毕判断
    {
     LED1 = 0;	  	//转换完毕指示
     LED2= 1;           //打开数据处理指示灯
	
     temp[1] = ADCL;
     temp[0] = ADCH;

      adc |= (uint)temp[1];
      adc |= ( (uint) temp[0] )<<8;
      adc>>=2; // ADCL[1:0]没用使用
      num = adc*3.3/8192;//定参考电压为3.3V。14位分辨率
      adcdata[1] = (char)(num)%10+48;
      adcdata[3] = (char)(num*10)%10+48;
      UartTX_Send_String(adcdata,6);	//串口送数    
      LED2= 0;                       //完成数据处理      
      delay(30000);

      InitialAD(); //启动下一次转换
    }
  }
}


/****************************************************************
*函数功能 ：延时						*
*入口参数 ：定性延时						*
*返 回 值 ：无							*
*说    明 ：							*
****************************************************************/
void delay(uint time)
{ uint i;
  uchar j;
  for(i = 0; i < time; i++)
  {  for(j = 0; j < 240; j++) 
      {   asm("NOP");    // asm是内嵌汇编，nop是空操作,执行一个指令周期
          asm("NOP");
          asm("NOP");
       }  
   }  
}


/****************************************************************
*函数功能 ：初始化串口1						*
*入口参数 ：无							*
*返 回 值 ：无							*
*说    明 ：57600-8-n-1						*
****************************************************************/
void initUART(void)
{
 CLKCONCMD &= 0x80;           //晶振32MHz
  
  PERCFG = 0x00;			//位置1 P0口
  P0SEL = 0x0C;				//P0用作串口
  
  U0CSR |= 0x80;			//UART方式
  U0GCR |= 10;				//baud_e = 10;
  U0BAUD |= 216;			//波特率设为57600
  UTX0IF = 1;
  
  U0CSR |= 0X40;			//允许接收
  IEN0 |= 0x84;				//开总中断，接收中断
}


/****************************************************************
*函数功能 ：初始化ADC						*
*入口参数 ：无					        	*
*返 回 值 ：无							*
*说    明 ：参考电压AVDD，转换对象是1/3AVDD			*
****************************************************************/
void InitialAD(void)
{

  P0SEL  |= (1 << (0));	  //设置P0.0为外设IO口
  P0DIR  &= ~ (1 << (0)); //设置P0.0为输入I/O

  LED1=1; //启动ADC转换， 指示灯
    
  ADCCON1 &= ~0x80;		//清EOC标志	
  APCFG  |=1;             //设置P0.0为模拟I/O  
  ADCCON3=0xb0;		//单次转换,参考电压为电源电压  //14位分辨率
  ADCCON1 = 0X30;	//停止A/D
  ADCCON1 |= 0X40;	//ADCCON1.ST=1，启动A/D
  
}
/****************************************************************
*函数功能 ：串口发送字符串函数					*
*入口参数 : data:数据						*
*	    len :数据长度				        *
*返 回 值 ：无						        *
*说    明 ：							*
****************************************************************/
void UartTX_Send_String(char *Data,int len)
{
  int j;
  for(j=0;j<len;j++)
  {
    U0DBUF = *Data++;
    while(UTX0IF == 0);
    UTX0IF = 0;
  }
}
