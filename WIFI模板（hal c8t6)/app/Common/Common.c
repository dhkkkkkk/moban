
//#include "common.h"
//#include <stdarg.h>
//#include "usart.h"
//#include "stm32f1xx_hal.h"
//static char *                 itoa            ( int value, char * string, int radix );
//uint8_t HC[]="/r";
//uint8_t HH[]="/n";

///*
// * ��������USART2_printf
// * ����  ����ʽ�������������C���е�printf��������û���õ�C��
// * ����  ��-USARTx ����ͨ��������ֻ�õ��˴���2����USART2
// *		     -Data   Ҫ���͵����ڵ����ݵ�ָ��
// *			   -...    ��������
// * ���  ����
// * ����  ���� 
// * ����  ���ⲿ����
// *         ����Ӧ��USART2_printf( USART2, "\r\n this is a demo \r\n" );
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

//	while ( * Data != 0 )     // �ж��Ƿ񵽴��ַ���������
//	{				                          
//		if ( * Data == 0x5c )  //'\'
//		{									  
//			switch ( *++Data )
//			{
//				case 'r':							          //�س���
//					HAL_UART_Transmit(USARTx,HC,sizeof(HC),100);
////				USART_SendData(USARTx, 0x0d);
//				Data ++;
//				break;

//				case 'n':							          //���з�
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
//				case 's':										  //�ַ���
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
//					//ʮ����
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