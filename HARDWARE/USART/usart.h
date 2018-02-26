#ifndef _USART_H
#define _USART_H
#include "sys.h"

#define USART1_MAX_RECV_LEN		800					//�����ջ����ֽ���
#define USART1_MAX_SEND_LEN		800					//����ͻ����ֽ���
#define USART1_RX_EN 			1					//0,������;1,����.

extern u8  USART1_RX_BUF[USART1_MAX_RECV_LEN]; 		//���ջ���,���USART3_MAX_RECV_LEN�ֽ�
extern u8  USART1_TX_BUF[USART1_MAX_SEND_LEN]; 		//���ͻ���,���USART3_MAX_SEND_LEN�ֽ�
extern vu16 USART1_RX_STA;   						//��������״̬
extern u16 USART1_RXD_Chaoshi;
extern u8  USART1_RXD_Flag;
void usart1_init(u32 bound);

#endif