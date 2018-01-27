#include "D_Flash.h"



/******************************************************************/
/*       D_Flash Memory 一共8K                                    */
/*       单片机预留一个1K空间用以访问D_Flash                      */
/*       地址为:0x0800 - 0xBFF                                    */
/*       通过EPAGE寄存器来确定是哪一部分D_Flash放入窗口中         */
/******************************************************************/



/*************************************************************/
/*                      初始化DFLASH                         */
/*            DFLASH的相对地址范围为0x0000-0x1fff            */
/*************************************************************/
byte InitDFlash(void)
{
  word timeCnt=0;
  while( (FSTAT_CCIF==0) && (timeCnt<5000))//等待正在处理的FLASH操作完成
    timeCnt++;  
  if( timeCnt>=5000)
    return (FlashInitOverTime);    //等待超时
  else timeCnt=0;             
  FCLKDIV=0x0F;                    //外部晶振为16M.FLASH时钟不超过1M，具体参照手册
  FCNFG=0x00;                      //禁止中断
  while( (FCLKDIV_FDIVLD==0) && (timeCnt<500));        //等待时钟设置成功
    timeCnt++;  
  if( timeCnt>=500)
    return (FlashSyncOverTime);   //Flash同步超时
  else
    return (FlashInitOk);
}

/************************************************************/
/*    根据扇区号和块号和位置，计算出需要操作的地址          */
/*    参数：secNum:扇区号（0~31）                           */
/*    StartPos:块号（0~31）一个扇区中的块，8字节一分        */
/*    返回地址的偏移地址，没有全局地址前缀0x10              */
/************************************************************/
word CallOffsetAddress(byte SecNum,byte PieceNum,byte PosNum) 
{
  //D_Flash每256bytes一个扇区，每8bytes一个块
  unsigned int address;
  address = 0x0000 + 256*SecNum + 8*PieceNum + PosNum; 
  return (address);
}
dword CallGlobalAddress(byte SecNum,byte PieceNum,byte PosNum)   
{
  unsigned long address;
  address = 0x100000 + 256*SecNum + 8*PieceNum + PosNum; 
  return (address); 
}

/*************************************************************/
/*                    擦除DFLASH的一个分区                   */
/*            address为擦除扇区的首地址(偏移地址)            */
/*************************************************************/
void DFlash_EraseSector(byte SecNum)
{ 
  unsigned int address;
  address = CallOffsetAddress(SecNum,0,0);  
  while(FSTAT_CCIF==0);
  if(FSTAT_ACCERR)           //判断并清除标志位；
      FSTAT_ACCERR=1;
  if(FSTAT_FPVIOL)           //判断并清除标志位；
      FSTAT_FPVIOL=1;
  
  FCCOBIX_CCOBIX=0x00;
  FCCOB=0x1210;           //写入擦除命令和高位地址
  FCCOBIX_CCOBIX=0x01;   
  FCCOB=address;          //写入低16位的地址
  FSTAT_CCIF=1;           //启动执行命令
  while(FSTAT_CCIF==0);   //等待执行完成
}

/*************************************************************/
/*                  向DFlash写入数据(word为单位)             */
/*              address为写入数据的首地址(偏移地址)          */
/*                  a，b，c，d为写入的数据                   */
/*************************************************************/
void DFlash_WriteBlock(byte SecNum,byte PieceNum,word a,word b,word c,word d)
{
    unsigned int address;
    address = CallOffsetAddress(SecNum,PieceNum,0);  
    while(FSTAT_CCIF==0); 
    if(FSTAT_ACCERR)           //判断并清除标志位；
        FSTAT_ACCERR=1;
    if(FSTAT_FPVIOL)           //判断并清除标志位；
        FSTAT_FPVIOL=1;
    FCCOBIX_CCOBIX=0x00; 
    FCCOB=0x1110;         //写入命令和高位地址，写入命令在高8位，低8位为高位地址，此处为16Byte
    FCCOBIX_CCOBIX=0x01;  //地址后16位
    FCCOB=address;         //写入低16位地址
    FCCOBIX_CCOBIX=0x02;  //写入第一个数据
    FCCOB=a;
    FCCOBIX_CCOBIX=0x03;  //写入第二个数据
    FCCOB=b;
    FCCOBIX_CCOBIX=0x04;  //写入第三个数据
    FCCOB=c;
    FCCOBIX_CCOBIX=0x05;  //写入第四个数据
    FCCOB=d;
      
    FSTAT_CCIF=1;         //写入执行命令
    while(FSTAT_CCIF==0); //等待执行完毕
}

/*************************************************************/
/*              由DFLASH读取数据(byte为单位)                 */
/*              address为读取数据的全局地址                  */
/*************************************************************/
byte DFlash_READbyte(byte Epage,byte SecNum,byte PieceNum,byte PosNum)   //按字节读取
{
  byte lastepage;    //用于存储EPAGE的值
  word address;
  byte data;
  
  address = CallOffsetAddress(SecNum,PieceNum,PosNum);
  lastepage = EPAGE;   //保存EPAGE的值
  EPAGE=Epage;  //给EPAGE赋值
  data = READbyte(DFLASH_PAGE_WINDOW_START + address);  //读取页面窗口中的数据
  EPAGE= lastepage;       //恢复EPAGE的值
  
  return (data);
}
word DFlash_READword(byte Epage,word index)   //按字读取(不关心所在扇区、块，仅以在窗口中的相对位置定位)
{
  byte lastepage;    //用于存储EPAGE的值
  word data;
  
  lastepage = EPAGE;   //保存EPAGE的值
  EPAGE=Epage;  //给EPAGE赋值
  data = READword(DFLASH_PAGE_WINDOW_START + index);  //读取页面窗口中的数据
  EPAGE= lastepage;       //恢复EPAGE的值


  return(data);
}





























