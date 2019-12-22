#include"i2c.h"


/**************************************************************************************************
 * 函数名称：QWait
 * 功能描述：延时函数（主频为32MHz时大约1us的延时）
 * 参    数：无
 * 返 回 值：无
 **************************************************************************************************/
void QWait()     
{
    asm("NOP");asm("NOP");asm("NOP");asm("NOP");
    asm("NOP");asm("NOP");asm("NOP");asm("NOP");
    asm("NOP");asm("NOP");asm("NOP");asm("NOP");
    asm("NOP");asm("NOP");asm("NOP");asm("NOP");  
    asm("NOP");asm("NOP");asm("NOP");asm("NOP");  
    asm("NOP");asm("NOP");asm("NOP");asm("NOP"); 
    asm("NOP");asm("NOP");asm("NOP");asm("NOP");
    asm("NOP");asm("NOP");asm("NOP");asm("NOP");    
}

/*******************************************************************************
* 函数名         : Delay10us()
* 函数功能	 : 延时10us
* 输入           : 无
* 输出         	 : 无
*******************************************************************************/
void Delay10us()
{  
  QWait();
  QWait();
  QWait();
  QWait();
  QWait();
  QWait();
  QWait();
  QWait();
  QWait();
  QWait();  
}

/*******************************************************************************
* 函数名         : I2cStart()
* 函数功能       : 起始信号：在SCL时钟信号在高电平期间SDA信号产生一个下降沿
* 输入           : 无
* 输出         	 : 无
* 备注           : 起始之后SDA和SCL都为0
*******************************************************************************/
void I2cStart()
{
        IO_DIR_PORT_PIN(1, 1, IO_OUT); 
	SDA=1;
	Delay10us();
	SCL=1;
	Delay10us();//建立时间是SDA保持时间>4.7us
	SDA=0;
	Delay10us();//保持时间是>4us
	SCL=0;			
	Delay10us();		
}

/*******************************************************************************
* 函数名         : I2cStop()
* 函数功能	 : 终止信号：在SCL时钟信号高电平期间SDA信号产生一个上升沿
* 输入           : 无
* 输出         	 : 无
* 备注           : 结束之后保持SDA和SCL都为1；表示总线空闲
*******************************************************************************/
void I2cStop()
{
        IO_DIR_PORT_PIN(1, 1, IO_OUT); 
	SDA=0;
	Delay10us();
	SCL=1;
	Delay10us();//保持时间是>4us
	SDA=1;
	Delay10us();		
}

/*******************************************************************************
* 函数名         : I2cSendByte(unsigned char dat)
* 函数功能	 : 通过I2C发送一个字节。在SCL时钟信号高电平期间，保持发送信号SDA保持稳定
* 输入           : num
* 输出         	 : 0或1。发送成功返回1，发送失败返回0
* 备注           : 发送完一个字节SCL=0,SDA=1
*******************************************************************************/
unsigned char I2cSendByte(unsigned char dat)
{
	unsigned char a=0,b=0;//最大255。		
        IO_DIR_PORT_PIN(1, 1, IO_OUT); 
	for(a=0;a<8;a++)//要发送8位，从最高位开始
	{
		SDA=dat>>7;	 //起始信号之后SCL=0，所以可以直接改变SDA信号
		dat=dat<<1;
		Delay10us();
		SCL=1;
		Delay10us();//建立时间>4.7us
		SCL=0;
		Delay10us();//时间大于4us	
	}
	SDA=1;

	Delay10us();
        IO_DIR_PORT_PIN(1, 1, IO_IN); 
	SCL=1;
	while(SDA)//如果超过2000us没有应答发送失败，或者为非应答，表示接收结束
	{
		b++;
		if(b>200)	//如果超过2000us没有应答发送失败，或者为非应答，表示接收结束
		{
			SCL=0;
			Delay10us();
			return 0;
		}
	}
	SCL=0;
	Delay10us();
 	return 1;		
}

/*******************************************************************************
* 函数名         : I2cReadByte()
* 函数功能	 : 使用I2c读取一个字节
* 输入           : ack： True为给应答， False为不给应答
* 输出         	 : dat
* 备注           : 接收完一个字节SCL=0,SDA=1.
*******************************************************************************/
unsigned char I2cReadByte(unsigned char ack)
{
	unsigned char a=0,dat=0;
        IO_DIR_PORT_PIN(1, 1, IO_OUT); 
	SDA=1;		 // 首先确保主机释放 SDA
	Delay10us();
        IO_DIR_PORT_PIN(1, 1, IO_IN); 
	for(a=0;a<8;a++)//接收8个字节
	{
		SCL=1;
		Delay10us();
		dat<<=1;
		dat|=SDA;
		Delay10us();
		SCL=0;
		Delay10us();
	}
        
        IO_DIR_PORT_PIN(1, 1, IO_OUT);     //将数据线恢复为输出状态
        SDA = !ack;  //  !ack; 拉高 SDA ，发送非应答信号; 或拉低SDA, 发送应答信号
        SCL = 1;  // 拉高 SCL
        Delay10us();
        SCL = 0; // 再拉低 SCL 完成非应答位，并保持住总线
	return dat;		
}


