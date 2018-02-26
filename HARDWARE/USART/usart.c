#include "bsp.h"

UART_HandleTypeDef UART1_Handler; //UART1句柄
//TIM_HandleTypeDef TIM7_Handler;   //定时器7句柄

//串口发送缓存区 	
__align(8) u8 USART1_TX_BUF[USART1_MAX_SEND_LEN]; 	//发送缓冲,最大USART1_MAX_SEND_LEN字节
//串口接收缓存区 	
u8 USART1_RX_BUF[USART1_MAX_RECV_LEN]; 				      //接收缓冲,最大USART1_MAX_RECV_LEN个字节.
u16 USART1_RXD_Chaoshi;  //串口1超时定时器
u8  USART1_RXD_Flag;

//通过判断接收连续2个字符之间的时间差不大于20ms来决定是不是一次连续的数据.
//如果2个字符接收间隔超过20ms,则认为不是1次连续数据.也就是超过20ms没有接收到
//任何数据,则表示此次接收完毕.
//接收到的数据状态
//[15]:0,没有接收到数据;1,接收到了一批数据.
//[14:0]:接收到的数据长度
vu16 USART1_RX_STA=0;   	 
void USART1_IRQHandler(void)
{
	u8 res;
	//__HAL_TIM_ENABLE(&TIM7_Handler); //使能定时器7
	if((__HAL_UART_GET_FLAG(&UART1_Handler,UART_FLAG_RXNE)!=RESET))  //接收中断
	{
        HAL_UART_Receive(&UART1_Handler,&res,1,1000); 
        //__HAL_TIM_SET_COUNTER(&TIM7_Handler,0);	//计数器清空			     
				USART1_RX_BUF[USART1_RX_STA++]=res;	//记录接收到的值
        USART1_RXD_Chaoshi = 20;		//15ms超时检测
        if(USART1_RX_STA > USART1_MAX_RECV_LEN)	
				{
						USART1_RX_STA = 0;
				}					
	}  													 
}   

//初始化IO 串口1
//bound:波特率 
void usart1_init(u32 bound)
{  	 
	GPIO_InitTypeDef GPIO_Initure;
	       
	//UART3 初始化设置
	__HAL_RCC_GPIOA_CLK_ENABLE();			//使能GPIOA时钟
	__HAL_RCC_USART1_CLK_ENABLE();			//使能USART1时钟

	GPIO_Initure.Pin=GPIO_PIN_9;			//PA9
	GPIO_Initure.Mode=GPIO_MODE_AF_PP;		//复用推挽输出
	GPIO_Initure.Pull=GPIO_PULLUP;			//上拉
	GPIO_Initure.Speed=GPIO_SPEED_FAST;		//高速
	GPIO_Initure.Alternate=GPIO_AF7_USART1;	//复用为USART1
	HAL_GPIO_Init(GPIOA,&GPIO_Initure);	   	//初始化PB10

	GPIO_Initure.Pin=GPIO_PIN_10;			      //PB11
	GPIO_Initure.Pull=GPIO_PULLDOWN;			//上拉
	HAL_GPIO_Init(GPIOA,&GPIO_Initure);	   	//初始化PB11

	UART1_Handler.Instance=USART1;					    //USART1
	UART1_Handler.Init.BaudRate=bound;				    //波特率
	UART1_Handler.Init.WordLength=UART_WORDLENGTH_8B;   //字长为8位数据格式
	UART1_Handler.Init.StopBits=UART_STOPBITS_1;	    //一个停止位
	UART1_Handler.Init.Parity=UART_PARITY_NONE;		    //无奇偶校验位
	UART1_Handler.Init.HwFlowCtl=UART_HWCONTROL_NONE;   //无硬件流控
	UART1_Handler.Init.Mode=UART_MODE_TX_RX;		    //收发模式
	HAL_UART_Init(&UART1_Handler);					    //HAL_UART_Init()会使能UART1
    
  __HAL_UART_ENABLE_IT(&UART1_Handler,UART_IT_RXNE);  //开启接收中断
	HAL_NVIC_EnableIRQ(USART1_IRQn);				    //使能USART1中断通道
	HAL_NVIC_SetPriority(USART1_IRQn,0,2);			    //组2，优先级0,2,最高优先级 
 
	USART1_RX_STA=0;				    //清零 
}
