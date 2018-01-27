#include "includes.h"
#ifndef _CAN_H_
#define _CAN_H_

  /*CAN 基本配置*/
  #define CAN_BOUND_RATE      500    //CAN总线波特率500kbps
  #define CAN_Filters_Enable  0      //选择是否使用CAN总线滤波器,1为使用,0为不使用
  #define CAN_DLC             8      //发送数据长度
  //#define CanCmdTxPeriod      10     //CAN命令发送周期(与计数周期有关)
  /*CAN 初始化状态*/
  #define CanInitOK                   0x00
  #define CanEnterInitModeOverTime    0x01
  #define CanEnterNormalModeOverTime  0x02
  #define CanSyncOverTime             0x04
  #define CanNotInSleepMode           0x08
  /*CAN 发送状态*/
  #define CanTxOK          0x01
  #define CanTxFull        0x02
  #define CanTxLenOverRun  0x04
  #define CanTxNotSync     0x08
  #define CanTxErrIDLen    0x10
  /*CAN 总线状态*/
  #define CanBusNormal    0x01
  #define CanBusWarning   0x02
  #define CanBusError     0x03
  #define CanBusOff       0x04
  //CAN总线ID
  #define CAN0_RX_First_ID     0x403   //CAN0接收第一帧ID   
  #define CAN0_RX_Second_ID    0x469   //CAN0接收第二帧ID 
  #define CAN0_TX_ID     0x10F     //CAN0发送ID
  //用以与上位机通信
  //#define CCP_DTO_ID        0x10E           /* CAN identifier ECU -> Master */
  //#define CCP_CRO_ID        0x10D           /* CAN identifier Master -> ECU */
  //CAN报文结构 
  struct CAN_Messages       
  {
    unsigned long id;
    Bool RTR;
    unsigned char data[8];
    unsigned char len;
    unsigned char prty;
  };
  extern struct CAN_Messages msg_send, msg_get;

  static byte CANSetFilter(void);
  static void CANSetParams(void);
  static byte CANEnterSleepMode(void);
  static byte CANExitSleepMode(void);
  static byte CANGetTransceiverState(void);
  static byte CANGetTxBufferState(void);
  static byte CANBusOffRecover(void);
  byte InitMSCAN0(void);
  void BusOff_Update(void);
  void CANMsg_Update(void);
  byte MSCAN0SendMsg(struct CAN_Messages msg);
  byte MSCAN0GetMsg(struct CAN_Messages *msg);
  void canMessageWrite(void);
  


#endif
