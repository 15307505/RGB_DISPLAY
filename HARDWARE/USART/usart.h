#ifndef _USART_H
#define _USART_H
#include "sys.h"

#define USART1_MAX_RECV_LEN		800					//最大接收缓存字节数
#define USART1_MAX_SEND_LEN		800					//最大发送缓存字节数
#define USART1_RX_EN 			1					//0,不接收;1,接收.

extern u8  USART1_RX_BUF[USART1_MAX_RECV_LEN]; 		//接收缓冲,最大USART3_MAX_RECV_LEN字节
extern u8  USART1_TX_BUF[USART1_MAX_SEND_LEN]; 		//发送缓冲,最大USART3_MAX_SEND_LEN字节
extern vu16 USART1_RX_STA;   						//接收数据状态
extern u16 USART1_RXD_Chaoshi;
extern u8  USART1_RXD_Flag;
void usart1_init(u32 bound);

#endif
