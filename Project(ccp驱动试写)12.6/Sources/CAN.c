#include "CAN.h"


struct CAN_Messages msg_send,msg_get;    //CAN总线发送结构

/*********************************************/
/*                CAN0初始化                 */
/*********************************************/

byte InitMSCAN0(void)      //初始化MSCAN
{
  word timeCnt=0;
  if(CAN0CTL0_INITRQ==0)      // 查询是否进入初始化状态   
    CAN0CTL0_INITRQ =1;        // 请求进入初始化状态
  //等待进入初始化状态
  while ((CAN0CTL1_INITAK==0) && (timeCnt<500))
    timeCnt++;  
  if( timeCnt>=500 )
    return (CanEnterInitModeOverTime);
  else timeCnt=0; 
  //使能MSCAN模块,设置为一般运行模式、使用总线时钟源
  CAN0CTL1_CANE   = 1; //允许MSCAN模块
  CAN0CTL1_CLKSRC = 1; //使用总线时钟
  CAN0CTL1_LOOPB  = 0; //非循环自检模式
  CAN0CTL1_LISTEN = 0; //非监听模式
  CAN0CTL1_BORM   = 1; //用户可恢复Bus-Off
  CAN0CTL1_WUPM   = 0; //总线有显性边沿跳变时唤醒总线
  /*******************************************
  *   调用配置函数 :   
  *   需要在CANE=1的情况下
  *   才可配置，否则可能配置无效  
  *********************************************/
  CANSetParams(); //设置CAN 参数
  (void)CANSetFilter();  //设置滤波器
  
  //请求返回一般模式运行              
  CAN0CTL0 = 0x00;             
  //等待回到一般运行模式 
  while( (CAN0CTL1_INITAK) && (timeCnt <500) ) 
    timeCnt++;        
  if( timeCnt>=500 )
    return (CanEnterNormalModeOverTime);
  else timeCnt=0;
  //等待总线时钟同步
  while( (CAN0CTL0_SYNCH==0) && (timeCnt <500) )
    timeCnt++;    
  if( timeCnt>=500 )
    return (CanSyncOverTime);
  //中断使能
  CAN0RIER_RXFIE = 1;          //使能接收缓冲区满中断
  //CAN0RIER_CSCIE = 1;          //使能CAN总线状态改变中断
  //CAN0RIER_RSTATE = 1;         //01 当接收导致总线离线时产生CSCIE中断
  //CAN0RIER_TSTATE = 1;         //01 当发送导致总线离线时产生CSCIE中断
  return (CanInitOK);
}

/*********************************************/
/*              CAN0参数设置               */
/*********************************************/

static void CANSetParams(void) //设置CAN总线参数
{
  CAN0BTR0_SJW = 1;      //同步跳跃宽度设置为1
  CAN0BTR0_BRP = 7;            //设置波特率 
  #ifndef CAN_BOUND_RATE
    #error "Please define CAN_BOUND_RATE"
  #endif 
  #if(CAN_BOUND_RATE == 500) 
    CAN0BTR1 = 0x14;      //设置时段1和时段2的Tq个数 ,总线频率为500kb/s
  #else if(CAN_BOUND_RATE == 250)
    CAN0BTR1 = 0x1c;      //设置时段1和时段2的Tq个数 ,总线频率为250kb/s
  #endif 
  
}

/*********************************************/
/*              CAN0滤波器设置               */
/*********************************************/

static byte CANSetFilter(void)   //设置滤波器
{
    CAN0IDAC_IDAM = 0x01;   //bit4= 1和bit5= 0，Four 16-bit acceptance filters
  #if(CAN_Filters_Enable == 1)     //使用CAN总线滤波器
    //开启全部滤波器
    CAN0IDMR0 = 0x02; //掩码
    CAN0IDMR1 = 0x60;
    CAN0IDMR2 = 0x00;
    CAN0IDMR3 = 0x00;
    CAN0IDMR4 = 0x00;
    CAN0IDMR5 = 0x00;
    CAN0IDMR6 = 0x00;
    CAN0IDMR7 = 0x00;
    //对相应ID进行滤波
    //第一帧
    CAN0IDAR0 = (byte)(CAN0_RX_First_ID>>3);
    CAN0IDAR1 = (byte)(CAN0_RX_First_ID<<5);
    CAN0IDAR2 = 0x29;
    CAN0IDAR3 = 0x40;
    //第二帧
    CAN0IDAR4 = (byte)(CAN0_RX_Second_ID>>3);
    CAN0IDAR5 = (byte)(CAN0_RX_Second_ID<<5);
    CAN0IDAR6 = (byte)(CCP_CRO_ID>>3);
    CAN0IDAR7 = (byte)(CCP_CRO_ID<<5);
    
  #else if(CAN_Filters_Enable == 0)     //不使用CAN总线滤波器
    //关闭所有滤波器
    CAN0IDMR0 = 0xFF;
    CAN0IDMR1 = 0xFF;
    CAN0IDMR2 = 0xFF;
    CAN0IDMR3 = 0xFF;
    CAN0IDMR4 = 0xFF;
    CAN0IDMR5 = 0xFF;
    CAN0IDMR6 = 0xFF;
    CAN0IDMR7 = 0xFF;
  #endif
  #if( CAN_Filters_Enable != 1 && CAN_Filters_Enable != 0 )
    #error "Please define CAN_Filters_Enable corretly"
    return (FALSE);  
  #endif
  return (TRUE);
}
/*********************************************
*  CAN0进入睡眠模式(不可唤醒状态)                   
*********************************************/
static byte CANEnterSleepMode(void)
{
  word timeCnt=0;
  //请求进入睡眠模式
  CAN0CTL0_SLPRQ = 1;
  DisableInterrupts;
    /*  不允许被唤醒  */
    CAN0CTL0_WUPE  = 0;
    CAN0RIER_WUPIE = 0;  //禁止唤醒中断
    while( (CAN0CTL1_SLPAK == 0) && (timeCnt <1000) )
      timeCnt++; 
  EnableInterrupts;   
  if( timeCnt>=1000 )
    return (FALSE);
  else 
    return (TRUE);
}
/*********************************************
*  CAN0退出睡眠模式                   
*********************************************/
static byte CANExitSleepMode(void)
{
  word timeCnt=0;
  //请求进入睡眠模式
  CAN0CTL0_SLPRQ = 0;
  /*  不允许被唤醒  */
  CAN0CTL0_WUPE  = 0;
  CAN0RIER_WUPIE = 0;  //禁止唤醒中断
  while( (CAN0CTL1_SLPAK == 1) && (timeCnt <1000) )
    timeCnt++;    
  if( timeCnt>=1000 )
    return (FALSE);
  else 
    return (TRUE);  

}

/*********************************************/
/*                CAN0发送                   */
/*********************************************/

byte MSCAN0SendMsg(struct CAN_Messages msg)
{
  unsigned char send_buf, sp;
  if(msg.len > 8)        // 检查数据长度
    return(CanTxLenOverRun);
  if(CAN0CTL0_SYNCH==0)  // 检查总线时钟
    return(CanTxNotSync);
  if(!(CAN0TFLG&7))
    return (CanTxFull);  //缓冲区已满
  // 寻找空闲的缓冲器
  CAN0TBSEL_TX=CAN0TFLG;
  send_buf=CAN0TBSEL;
  if(msg.id <= 0x7FF)
  {  // 标准帧
    CAN0TXIDR0 = (unsigned char)(msg.id>>3);
    CAN0TXIDR1 = (unsigned char)(msg.id<<5);
  } 
  else if(msg.id > 0x7FF && msg.id <= 0x1FFFFFFF)
  { //  扩展帧          
    CAN0TXIDR0 = (msg.id>>21) & 0xFF;         
    CAN0TXIDR1 = (msg.id>>18) & 0x07; 
    CAN0TXIDR1 = CAN0TXIDR1 << 5;
    CAN0TXIDR1 = CAN0TXIDR1 | ((msg.id>>15) & 0x07);
    CAN0TXIDR1_SRR = 1;
    CAN0TXIDR1_IDE = 1;                            //扩展帧 
    CAN0TXIDR2 = ( msg.id>>7) & 0xFF; 
    CAN0TXIDR3 = ( msg.id<<1) & 0xFF; 
    CAN0TXIDR3_RTR = 0; 
  } 
  else
    return (CanTxErrIDLen);  //ID超长
  if(msg.RTR)
    CAN0TXIDR1 |= 0x10;       // RTR = 阴性
  for(sp = 0; sp < msg.len; sp++)
    *((&CAN0TXDSR0)+sp) = msg.data[sp];    // 写入数据
    
  CAN0TXDLR_DLC = msg.len;  // 写入数据长度
  // 写入优先级
  CAN0TXTBPR = msg.prty;
  // 清 TXx 标志 (缓冲器准备发送)
  CAN0TFLG = send_buf;
  //打开对应的发送缓冲区空中断
  CAN0TIER_TXEIE = send_buf;       
  
  return(CanTxOK);
}
/*********************************************/
/*                CAN0接收                  */
/********************************************/

byte MSCAN0GetMsg(struct CAN_Messages *msg)
{
  unsigned char sp2;
  dword idreg;
  // 检测接收标志
  if(!(CAN0RFLG_RXF))
    return(FALSE);
  // 检测 CAN协议报文模式 （一般/扩展） 标识符
  if(CAN0RXIDR1_IDE)    //扩展标识符
  {
    idreg= *((dword*)((dword)(&CAN0RXIDR0)));
    msg->id=((idreg>>1)& 0x3FFFF)|((idreg>>3)& 0x1FFC0000);    //扩展帧模式读取帧ID
    
    if(CAN0RXIDR3&0x01)
      msg->RTR = TRUE;
    else
      msg->RTR = FALSE;
  }
  else      //标准帧
  {
    msg->id = (unsigned int)(CAN0RXIDR0<<3) |  (unsigned char)(CAN0RXIDR1>>5);
              
    if(CAN0RXIDR1&0x10)
      msg->RTR = TRUE;
    else
      msg->RTR = FALSE;
  }
  // 读取数据长度 
  msg->len = CAN0RXDLR_DLC;
  // 读取数据
  for(sp2 = 0; sp2 < msg->len; sp2++)
    msg->data[sp2] = *((&CAN0RXDSR0)+sp2);
  // 清 RXF 标志位 (缓冲器准备接收)
  CAN0RFLG = 0x01;

  return(TRUE);
}

/*********************************************/
/*               CAN故障恢复                 */
/*********************************************/
static byte CANBusOffRecover(void)
{
  byte value = 0;
  if(CANEnterSleepMode())
  {
  DisableInterrupts;
    CAN0MISC_BOHOLD = 1;     //清除Bus-Off标志
    value = InitMSCAN0();    //重新初始化
  EnableInterrupts;
  }
  else
    value = CanNotInSleepMode;
  return (value);
}
//获取CAN接收器状态
word canBusWarningCount=0;    //警告转变为错误的时间控制与BusOff_Update的调用周期有关
static byte CANGetTransceiverState(void) 
{
  byte value = 0;
  if( CAN0RFLG_RSTAT == 0 && CAN0RFLG_TSTAT == 0)
    value = CanBusNormal;
  else if( CAN0RFLG_RSTAT == 1 || CAN0RFLG_TSTAT == 1) 
  {
    canBusWarningCount++;
    value = CanBusWarning;
    if(canBusWarningCount >= 500)    //若警告次数太多，则认为是错误
      value = CanBusError;
  }
  else if( CAN0RFLG_RSTAT == 2 || CAN0RFLG_TSTAT == 2)
    value = CanBusError;
  else if( CAN0RFLG_RSTAT == 3 || CAN0RFLG_TSTAT == 3)
    value = CanBusOff;
  return (value);
}
//获取发送缓冲区状态
static byte CANGetTxBufferState(void)
{
  byte value;
  value = CAN0TFLG_TXE;
  
  return (value);
}
/*********************************************************************
* 函数 :CANBud-Off刷新函数
* 功能 :保证发送缓冲区不会溢出
*       检测CAN总线状态,存在故障时延时一段时间后恢复
* 日期 :2017.9.20
*********************************************************************/
word canBusOffTimeCnt;   //BusOff恢复计时
void BusOff_Update(void)
{
  if( (CANGetTransceiverState() == CanBusError) || (CANGetTransceiverState() == CanBusOff))
  {
    //PITDelay(50);  //必须加延时
    canBusOffTimeCnt++;
    if( canBusOffTimeCnt >= 5000)
      (void) CANBusOffRecover(); 
  }
  else
    canBusOffTimeCnt = 0;
}
/*********************************************************************
* 函数 :CAN周期发送函数
* 功能 :周期发送命令报文
* 日期 :2017.9.21
*********************************************************************/
void CANMsg_Update(void)
{
   canMessageWrite();
   (void)MSCAN0SendMsg(msg_send);

}

/***********************************************************/
/*                   CAN通讯数据打包                       */
/***********************************************************/
void canMessageWrite(void)   //填写CAN报文内容
{
    msg_send.id = CAN0_TX_ID;
    msg_send.data[0] += 1;
    msg_send.data[1] += 2;
    msg_send.data[2] = 3;
    msg_send.data[3] += 4; 
    msg_send.data[4] = 5;    //Logic_Speed/256;
    msg_send.data[5] = 6;    //Logic_Speed%256;
    msg_send.data[6] = 10;
    msg_send.data[7] = 1;
    msg_send.len = CAN_DLC;
    msg_send.RTR = FALSE;
    msg_send.prty = 0;
      
}
/*
*接收协议解析
*/
byte TPS,Battery_Soc,Motor_Mode;
word Motor_Speed,Contorller_Torque;  
void protocol(dword id) 
{
  word temp1,temp2,temp3;
  switch(id)
  {
    case   CAN0_RX_First_ID:
        
       temp1 = 100*msg_get.data[6];
       TPS = (byte)(temp1/255);        //油门开度 % 
       break;
    case   CAN0_RX_Second_ID:
                                            
       temp2 = msg_get.data[4]*256 + msg_get.data[5];    
       Battery_Soc = (byte)(temp2/100);    //电池电量 %     
       break;
    case   CAN0_RX_Third_ID:
                                                
       temp3 = msg_get.data[2]*256 + msg_get.data[3];        
       Motor_Speed = temp3/2-11998;               //电机转速
       Contorller_Torque = msg_get.data[4]*256 + msg_get.data[5];   //实际输出扭矩
       break;
    case   CAN0_RX_Fourth_ID:
   
       Motor_Mode = msg_get.data[4]&0x7c;       //电机模式(取中间5位作为判断依据)     
       break;
                                             
     default:     
        break;               
  }
}

/***********************************************************/
/*                   CAN0总线中断服务函数                  */
/***********************************************************/
char canRX_error,canTX_error;

#pragma CODE_SEG __NEAR_SEG NON_BANKED
//接收中断
void interrupt 38 CAN_receive(void) 
{
    if( MSCAN0GetMsg(&msg_get)&&(!msg_get.RTR) )   //报文协议解析
    {  
      switch(msg_get.id)
      {
         case   CCP_CRO_ID:   //命令接收对象ID
           {
              ccpCommand(msg_get.data);   //将数组的首地址传给ccpCommand
           }
           break;

                                         
         default:     
              protocol(msg_get.id);
                 
       }  
     } 
 }
 
 //发送中断
void interrupt 39 CAN_transmit(void)
{
  CAN0TIER_TXEIE = 0x00; //禁止所有发送缓冲区空中断
  Sch.rdytaskTik[0] = 0;    //重置时间
  if( CANGetTxBufferState() != 0)
  {
    /*与ExtCCP耦合的函数，无法避免*/
    (void)ccpSendCallBack();
  }
}
#pragma CODE_SEG DEFAULT


















