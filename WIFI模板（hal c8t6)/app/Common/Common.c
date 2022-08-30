
//#include "common.h"
//#include <stdarg.h>
//#include "usart.h"
//#include "stm32f1xx_hal.h"
//static char *                 itoa            ( int value, char * string, int radix );
//uint8_t HC[]="/r";
//uint8_t HH[]="/n";

///*
// * 函数名：USART2_printf
// * 描述  ：格式化输出，类似于C库中的printf，但这里没有用到C库
// * 输入  ：-USARTx 串口通道，这里只用到了串口2，即USART2
// *		     -Data   要发送到串口的内容的指针
// *			   -...    其他参数
// * 输出  ：无
// * 返回  ：无 
// * 调用  ：外部调用
// *         典型应用USART2_printf( USART2, "\r\n this is a demo \r\n" );
// *            		 USART2_printf( USART2, "\r\n %d \r\n", i );
// *            		 USART2_printf( USART2, "\r\n %s \r\n", j );
// */
//void USART_printf ( UART_HandleTypeDef * USARTx, char * Data, ... )
//{
//	const char *s;
//	int d;   
//	char buf[16];

//	
//	va_list ap;
//	va_start(ap, Data);

//	while ( * Data != 0 )     // 判断是否到达字符串结束符
//	{				                          
//		if ( * Data == 0x5c )  //'\'
//		{									  
//			switch ( *++Data )
//			{
//				case 'r':							          //回车符
//					HAL_UART_Transmit(USARTx,HC,sizeof(HC),100);
////				USART_SendData(USARTx, 0x0d);
//				Data ++;
//				break;

//				case 'n':							          //换行符
//						HAL_UART_Transmit(USARTx,HH,sizeof(HH),100);
////				USART_SendData(USARTx, 0x0a);	
//				Data ++;
//				break;

//				default:
//				Data ++;
//				break;
//			}			 
//		}
//		
//		else if ( * Data == '%')
//		{									  //
//			switch ( *++Data )
//			{				
//				case 's':										  //字符串
//				s = va_arg(ap, const char *);
//				
//				for ( ; *s; s++) 
//				{
//					HAL_UART_Transmit(USARTx,(uint8_t *)s,sizeof(*s),100);
//					//USART_SendData(USARTx,*s);
////					while( USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET );
//				}
//				
//				Data++;
//				
//				break;

//				case 'd':			
//					//十进制
//				d = va_arg(ap, int);
//				
//				itoa(d, buf, 10);
//				
//				for (s = buf; *s; s++) 
//				{
//						HAL_UART_Transmit(USARTx,(uint8_t *)s,sizeof(*s),100);
////					while( USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET );
//				}
//				
//				Data++;
//				
//				break;
//				
//				default:
//				Data++;
//				
//				break;
//				
//			}		 
//		}
//		else HAL_UART_Transmit(USARTx,(uint8_t *)s,sizeof(*s),100);
//		//else USART_SendData(USARTx, *Data++);
//		
//		while ( USART_GetFlagStatus ( USARTx, USART_FLAG_TXE ) == RESET );
//		
//	}
//}