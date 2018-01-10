#include "includes.h"
#ifndef _D_Flash_H_
#define _D_Flash_H_

  /*  Flash初始化状态  */
  #define FlashInitOk         0x00
  #define FlashInitOverTime   0x01
  #define FlashSyncOverTime   0X02
  /*  DFlash地址设置 */
  #define READword(address)     ((unsigned int)(*(volatile unsigned int *__near)(address)))
  #define READbyte(address)     ((unsigned int)(*(volatile unsigned char *__near)(address)))
  #define DFLASH_LOWEST_START_PAGE        0x00        //定义data flash的起始页
  #define DFLASH_START                    0x100000  //定义data flash的起始地址
  #define DFLASH_PAGE_SIZE                0x0400      //定义data flash的大小为1K.
  #define DFLASH_PAGE_WINDOW_START        0x0800      //定义data flash页面窗口的起始地址
  
  
  byte DFlash_Init(void);
  void DFlash_WriteBlock(byte SecNum,byte PieceNum,word a,word b,word c,word d);
  void DFlash_EraseSector(byte SecNum);
  byte DFlash_READbyte(byte Epage,byte SecNum,byte PieceNum,byte PosNum);

#endif