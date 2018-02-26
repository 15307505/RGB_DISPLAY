#include  "bsp.h"

short writeIndex,readIndex;
/**************************************************************************************************
 * 缓冲区当前所有数据长度
 *************************************************************************************************/
unsigned char buffSize(void)
{
    short  wi = writeIndex;
    short  ri = readIndex;
//	SendData1(wi);
//	SendData1(ri);
    return (wi >= ri) ? (wi - ri) : (USART1_MAX_SEND_LEN - ri + wi);
}

/**************************************************************************************************
 * 缓冲区是否空了
 *************************************************************************************************/
unsigned char isEmpty(void)
{
    short  wi = writeIndex;
    short  ri = readIndex;
    return (wi == ri);
}

/**************************************************************************************************
 * 缓冲区是否满了
 *************************************************************************************************/
unsigned char isFull(void)
{
    short  wi = writeIndex;
    short  ri = readIndex;
    return ((wi + 1) % USART1_MAX_SEND_LEN == ri);
}

/**************************************************************************************************
 * 将串口接收到的 数据 从顶部压入堆栈
 *************************************************************************************************/
void pushBuff (u8 data)
{
    if (isFull())
    {
        return;
    }
    //memcpy(uart1Buf[_uartReceive.writeIndex].rbuf,data.rbuf,data.len);          //rbuf 数值传递
    //uart1Buf[_uartReceive.writeIndex].len = data.len;                           //len数值传递
    writeIndex = (writeIndex + 1) % USART1_MAX_SEND_LEN;
}  

/**************************************************************************************************
 * 将堆栈里面的数据从底部弹出
 *************************************************************************************************/

u8 popBuff(void)
{
  u8 d;
  //memcpy(d.rbuf,uart1Buf[_uartReceive.readIndex].rbuf,uart1Buf[_uartReceive.readIndex].len);
	//d.len = uart1Buf[_uartReceive.readIndex].len;
	readIndex = (readIndex + 1) % USART1_MAX_SEND_LEN;    
	return d;
}
