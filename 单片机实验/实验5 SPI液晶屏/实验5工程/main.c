//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//中景园电子
//  文 件 名   : main.c
//  版 本 号   : v2.0
//  作    者   : HuangKai
//  生成日期   : 2018-10-31
//  最近修改   : 
//  功能描述   : LCD SPI接口演示例程
//              说明: 
//              ----------------------------------------------------------------
//              GND     电源地
//              VCC     3.3v电源
//              SCLK      P1.5（SCL）
//              MOSI      P1.6（SDA）
//              RES     P2.0
//              DC      P1.4
//              CS      不接  
//		BLK     不接 控制背光
//		MISO    P1.7
//              ----------------------------------------------------------------
// 修改历史   :
// 日    期   : 
// 作    者   : HuangKai
// 修改内容   : 创建文件
//版权所有，盗版必究。
//Copyright(C) 中景园电子2018-10-31
//All rights reserved
//******************************************************************************/
#include "delay.h"
#include "lcd.h"
#include <ioCC2530.h>

#define uint unsigned int
#define uchar unsigned char

void Initial_IO(void)
{
	P0DIR |= 0xff;     //P0定义为输出
        P1DIR |= 0xff;     //P1定义为输出
        P2DIR |= 0x01;     //P2.0定义为输出
        P0 &=~0xE0;
}

//******************************************************
int main(void)
 {	
	 u8 i,m;
	 float t=0;
        
         Initial_IO();  

	 Lcd_Init();			//初始化OLED  
	 LCD_Clear(WHITE);
	 BACK_COLOR=WHITE;

	 while(1)
	 {
		LCD_ShowChinese32x32(10,0,0,32,GBLUE);   //中
		LCD_ShowChinese32x32(45,0,1,32,GBLUE);   //景
		LCD_ShowChinese32x32(80,0,2,32,GBLUE);   //园
		LCD_ShowChinese32x32(115,0,3,32,GBLUE);  //电
		LCD_ShowChinese32x32(150,0,4,32,GBLUE);  //子
		LCD_ShowChinese32x32(10,75,0,16,RED);   //中
		LCD_ShowChinese32x32(45,75,1,16,RED);   //景
		LCD_ShowChinese32x32(80,75,2,16,RED);   //园
		LCD_ShowChinese32x32(115,75,3,16,RED);  //电
		LCD_ShowChinese32x32(150,75,4,16,RED);  //子
		LCD_ShowString(10,35,"2.8 TFT SPI 240*320",RED);
		LCD_ShowString(10,55,"LCD_W:",RED);	LCD_ShowNum(70,55,LCD_W,3,RED);
		LCD_ShowString(110,55,"LCD_H:",RED);LCD_ShowNum(160,55,LCD_H,3,RED);
		  
                for(i=0;i<2;i++)
		{
			for(m=0;m<6;m++)
			{
		           LCD_ShowPicture(0+m*40,120+i*40,39+m*40,159+i*40);
			}
		}
		
                while(1)
		{
                          LCD_ShowNum1(80,200,t,5,RED);
		          t+=0.01;
                }
          }//  while loop
}
