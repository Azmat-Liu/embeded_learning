#include "IIC.h"


#define i2c_SCL PTJ_PTJ7
#define i2c_SDA PTJ_PTJ6

#define SCL_dir DDRJ_DDRJ7
#define SDA_dir DDRJ_DDRJ6

#define somenop(); asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");\
                   asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");\
                   asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");\
                   asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");\
                   asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");\
                   asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");
                   
#define i2cStart()
#define i2cStop()

#define DEVICE_ADDR 0x1234

struct i2c_msg {
	word s_addr;	/* slave address			*/
	word flags;

	word len;		/* msg length				*/
	byte *buf;		/* pointer to msg data			*/
};

void InitI2C(void) 
{
  SCL_dir = 1;
  SDA_dir = 1;
}