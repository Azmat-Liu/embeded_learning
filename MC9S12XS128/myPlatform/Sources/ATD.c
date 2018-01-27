#include "ATD.h"


void InitATD(void) 
{
  ATD0CTL1=0x20;  //10位转换精度
  ATD0CTL2=0x40;  //对结果寄存器的访问将自动清除相应CCF标志位，（快速清理）
  ATD0CTL3=0x88;  //每次只转换1个通道,非FIFO模式,冻结模式下继续转换
  ATD0CTL4=0x01;  //采样时间为4个时钟周期，prs=1;ATDclock=BusClock/((prs+1)*2)
  ATD0DIEN=0x00;   // 禁止数字输入
}

word atdChannel(byte ch) 
{
 uchar count,i;
 int Max,Min,a[5],Sum,rtnValue;  
 switch(ch)
 { 
  case 1:
 
     for(count=0;count<5;count++) 
       {
        ATD0CTL5 = 0x01;    //转换AD01
        while(!ATD0STAT0_SCF);//判断一个转换序列完成
        a[count]=ATD0DR0;
       }
     Max=a[0];
     Min=a[0];
     Sum=a[0];
     for(i=1;i<5;i++) 
       {
        Sum += a[i];
        if(a[i]>Max) Max=a[i];
        if(a[i]<Min) Min=a[i];
       }
     rtnValue=(Sum-Max-Min)/3;      
     break; 

  case 2:
    
    for(count=0;count<5;count++) 
       {
        ATD0CTL5 = 0x02;    //转换AD02
        while(!ATD0STAT0_SCF);//判断一个转换序列完成
        a[count]=ATD0DR0;
       }
     Max=a[0];
     Min=a[0];
     Sum=a[0];
     for(i=1;i<5;i++) 
       {
        Sum += a[i];
        if(a[i]>Max) Max=a[i];
        if(a[i]<Min) Min=a[i];
       }
     rtnValue=(Sum-Max-Min)/3;      
     break;
     
  case 3:
    
    for(count=0;count<5;count++) 
       {
        ATD0CTL5 = 0x03;    //转换AD03
        while(!ATD0STAT0_SCF);//判断一个转换序列完成
        a[count]=ATD0DR0;
       }
     Max=a[0];
     Min=a[0];
     Sum=a[0];
     for(i=1;i<5;i++) 
       {
        Sum += a[i];
        if(a[i]>Max) Max=a[i];
        if(a[i]<Min) Min=a[i];
       }
     rtnValue=(Sum-Max-Min)/3;      
     break;
  
 }
 
 return rtnValue;

}







