#include "SCI.h"

/**********************************************************************
*  说明:  串口接收与发送相关函数
*        
*  作者:  Azmat
*  日期:  2017.12.15
***********************************************************************/

#define BAUD      9600 

//*sci0模块初始化
void InitSCI0(void) 
{
  SCI0BD = BUS_CLOCK/16/BAUD;   //设置SCI0波特率为9600
  SCI0CR1 = 0x00;               //设置SCI0为正常模式，八位数据位，无奇偶校验
  SCI0CR2 = 0x2c;               //允许发送数据，允许接收中断功能
}
//*发送一个字节数据
static void sendSCI0(unsigned char data) 
{
  while(!SCI0SR1_TDRE);         //等待发送数据寄存器（缓冲器）为空
  SCI0DRL = data;
} 
//*接收一个字节数据
byte receiveSCI0(void) 
{
  while(!SCI0SR1_RDRF);          //等待接收数据寄存器满
  return(SCI0DRL);
}

/**********************************************************************
*  说明:  串口字符串发送函数
*        
*  作者:  Azmat
*  日期:  2017.12.15
***********************************************************************/
void printk(char *str) 
{
  DisableInterrupts;
  while(*str != '\0')
      sendSCI0(*str++);
  EnableInterrupts;
}

/**********************************************************************
*  说明:  串口接收中断和命令解析相关函数
*        
*  作者:  Azmat
*  日期:  2017.12.15
***********************************************************************/


typedef struct{
	byte head[3];
	byte num;
	byte cmd[8];
}uart_t;
uart_t uart;

static char uart_cmdacc,uart_msgcnt;
static byte *pcmd = uart.head;


#pragma CODE_SEG __NEAR_SEG NON_BANKED

void interrupt 20 receive_data(void)    //串口接收
{
  DisableInterrupts;
   
  	*pcmd++ = receiveSCI0();
		if(uart_cmdacc == 0)
			uart_msgcnt++;
		if(uart_msgcnt == 1 && uart.head[0] != 0xff){
			pcmd = uart.head;
			uart_msgcnt = 0;
		}
		if(uart_msgcnt == 2 && uart.head[1] != 0x5a){
			pcmd = uart.head;
			uart_msgcnt = 0;
		}
		if(uart_msgcnt == 3 && uart.head[2] != 0xa5){
			pcmd = uart.head;
			uart_msgcnt = 0;
		}
		
		if(uart_msgcnt == 4 && uart.num > 0){
		  if(uart.num > 8){
  		  //命令长度大于8的不做反应
  		  pcmd = uart.head;
  			uart_msgcnt = 0;
		  }else {
		    uart_cmdacc = 1;
		  	uart.num --; 
		  }
		}else if(uart_cmdacc == 1){
		  sciCmd_Decode();//解析sci命令
			pcmd = uart.head;
			uart_msgcnt = 0;
			uart_cmdacc = 0;
		}

  EnableInterrupts;
}


 #pragma CODE_SEG DEFAULT
 





