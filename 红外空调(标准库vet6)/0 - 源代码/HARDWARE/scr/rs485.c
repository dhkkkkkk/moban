/*-------------------------------------------------*/
/*         超纬电子STM32系列开发板                  */
/*    淘宝地址： http://chaoweidianzi.taobao.com   */
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*            RS485源文件,有2个函数                */
/*-------------------------------------------------*/
/* void RS485_Init(u32 bound)       485初始化串口3 */
/* void RS485_printf(char* fmt,...) 485printf函数  */
/*-------------------------------------------------*/

#include "rs485.h"
#include "delay.h"
	
u8  RS485_RX_BUF[RS485_RXBUFF_SIZE];  //接收缓存区 
u16 RS485_RX_STA=0;                   //接收状态标记 

/*-------------------------------------------------*/
/*函数名：初始化串口4--RS485                        */
/*参  数：bound：波特率                            */
/*返回值：无                                       */
/*-------------------------------------------------*/
void RS485_Init(u32 bound)
{  	 	
    GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	
 
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;            //PC10
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	     //复用推挽输出
    GPIO_Init(GPIOC, &GPIO_InitStructure);               //初始化PC10
   
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;            //PC11
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
    GPIO_Init(GPIOC, &GPIO_InitStructure);               //初始化PC11
	
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;            //PC12
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	 //复用推挽输出
    GPIO_Init(GPIOC, &GPIO_InitStructure);               //初始化PC12
	
	USART_InitStructure.USART_BaudRate = bound;                                    //波特率设置
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;                    //字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;                         //一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;                            //无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	               //收发模式
    USART_Init(UART4, &USART_InitStructure);                                      //按配置设置串口4
	
    USART_Cmd(UART4, ENABLE);                              //使能串口4
	USART_ClearFlag(UART4, USART_FLAG_TC);	                //清除标志位
	USART_ITConfig(UART4, USART_IT_RXNE, ENABLE);          //开启接受中断

    NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn;        //串口4中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2; //抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =2;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//中断通道使能
	NVIC_Init(&NVIC_InitStructure);	                        //根据配置设置
	
	RS485_RX_TX=0;				                            //接收模式
}



/*-------------------------------------------------*/
/*函数名：串口2printf                              */
/*参  数：无                                       */
/*返回值：无                                       */
/*-------------------------------------------------*/

__align(8) u8  RS485_TX_BUF[RS485_TXBUFF_SIZE];  

void RS485_printf(char* fmt,...) 
{  
	u16 i,length;
	
	va_list ap;
	va_start(ap,fmt);
	vsprintf((char*)RS485_TX_BUF,fmt,ap);
	va_end(ap);
	
	RS485_RX_TX=1;  //发送模式
	delay_ms(1);
	
	length=strlen((const char*)RS485_TX_BUF);	
	while((UART4->SR&0X40)==0);
	for(i = 0;i < length;i ++)
	{			
		UART4->DR = RS485_TX_BUF[i];
		while((UART4->SR&0X40)==0);	
	}	
	
	RS485_RX_TX=0;  //接收模式
	delay_ms(1);
}
