#ifndef	__PROTOCOL_H__
#define	__PROTOCOL_H__
#include "sys.h"

extern unsigned char buffSize(void);
extern unsigned char isEmpty(void);
extern unsigned char isFull(void);
 
extern u8 popBuff(void);                                        //定义一个串口一接收数据的缓冲区
extern void pushBuff (u8 data);
#endif
