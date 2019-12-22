/****************************************************************************
* 文 件 名: main.c
* 描    述: 定时器T1通过中断方式控制LED3周期性闪烁
****************************************************************************/
#include <ioCC2530.h>

typedef unsigned char uchar;
typedef unsigned int uint;

#define LED1 P0_5 // P0.5口控制LED1
#define LED2 P0_6 // P0.6口控制LED2
#define LED3 P0_7 // P0.7口控制LED

#define KEY1 P0_4 // P0.4口控制KEY1
#define KEY3 P1_3 // P1.3口控制KEY3

uchar t1_count = 0;  // Timer1溢出次数计数

uchar k1_count = 0;  // KEY1消抖计数
uchar k3_count = 0;  // KEY3消抖计数

uchar Key1Value = 0; // 上次是否KEY1被按下
uchar Key3Value = 1; // 上次是否KEY3被按下

/****************************************************************************
* 名    称: InitLed()
* 功    能: 设置LED灯相应的IO口
* 入口参数: 无
* 出口参数: 无
****************************************************************************/
void InitLed(void)
{
  P0DIR |= 0xe0; //P0.7定义为输出
  LED1 = 0;      //使LED1灯上电默认为熄灭
  LED2 = 0;      //使LED2灯上电默认为熄灭
  LED3 = 0;      //使LED3灯上电默认为熄灭
}

/****************************************************************************
* 名    称: KeyScan()
* 功    能: 读取按键状态
* 入口参数: 无
* 出口参数: 无
****************************************************************************/
void KeyScan(void)
{
  if (KEY1 == 0)
  {
    k1_count++;
    if (k1_count >= 7)
    {
      Key1Value = 1;
      Key3Value = 0;
      k1_count = 0;
    }
  }
  else if (KEY1 == 1)
  {
    k1_count = 0;
  }

  if (KEY3 == 0)
  {
    k3_count++;
    if (k3_count >= 7)
    {
      Key3Value = 1;
      Key1Value = 0;
      k3_count = 0;
    }
  }
  else if (KEY3 == 1)
  {
    k3_count = 0;
  }
}

/****************************************************************************
* 名    称: InitT1()
* 功    能: 定时器1初始化，系统不配置工作时钟时默认为16MHz
* 入口参数: 无
* 出口参数: 无
****************************************************************************/
void InitT1()
{
  T1CTL |= 0x0c; //128分频
  //每隔0.5s会产生一个中断请求
  T1CC0L = 0x12; //设置最大计数数值的低8位。
  T1CC0H = 0x7A; //设置最大计数数值的高8位。
  T1OVFIM = 1;   //使能定时器1溢出中断，可不写
  T1IE = 1;      //使能定时器1中断
  EA = 1;        //开全局中断
  T1CTL |= 0x03; //设置Up/down模式，计数开始
}

/****************************************************************************
* 名    称: InitT3()
* 功    能: 定时器3初始化，系统不配置工作时钟时默认为2分频16MHz
* 入口参数: 无
* 出口参数: 无
****************************************************************************/
void InitT3()
{
  T3CTL |= 0x0c;
  T3IE = 1;
  T3CTL |= 0xE0;
  T3CTL &= ~0x03;
  T3CTL |= 0x10;
  EA = 1;
}

/****************************************************************************
* 定时器T1中断处理函数
****************************************************************************/
#pragma vector = T1_VECTOR
__interrupt void T1_INT(void)
{
  T1STAT &= ~0x20; //清除定时器1溢出中断标志位
  t1_count++;        //定时器1溢出次数加1，溢出周期为0.5s
  if (t1_count == 3) //如果溢出次数达到3说明经过了1.5s
  {
    LED1 = Key1Value; //点亮LED1
    LED3 = Key3Value; //点亮LED3
  }
  else if (t1_count >= 4) //如果溢出次数达到4说明经过了2s
  {
    LED1 = LED3 = t1_count = 0; //清零定时器1溢出次数
  }
}

/****************************************************************************
* 定时器T3中断处理函数
****************************************************************************/
#pragma vector = T3_VECTOR
__interrupt void T3_ISR(void)
{
  KeyScan();
}

/****************************************************************************
* 程序入口函数
****************************************************************************/
void main(void)
{
  InitLed(); //调用LED初始化函数
  InitT1();  //调用Timer1初始化函数
  InitT3();  //调用Timer3初始化函数

  while (1);
}
