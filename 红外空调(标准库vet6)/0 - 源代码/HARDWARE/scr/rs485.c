/*-------------------------------------------------*/
/*         ��γ����STM32ϵ�п�����                  */
/*    �Ա���ַ�� http://chaoweidianzi.taobao.com   */
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*            RS485Դ�ļ�,��2������                */
/*-------------------------------------------------*/
/* void RS485_Init(u32 bound)       485��ʼ������3 */
/* void RS485_printf(char* fmt,...) 485printf����  */
/*-------------------------------------------------*/

#include "rs485.h"
#include "delay.h"
	
u8  RS485_RX_BUF[RS485_RXBUFF_SIZE];  //���ջ����� 
u16 RS485_RX_STA=0;                   //����״̬��� 

/*-------------------------------------------------*/
/*����������ʼ������4--RS485                        */
/*��  ����bound��������                            */
/*����ֵ����                                       */
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
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	     //�����������
    GPIO_Init(GPIOC, &GPIO_InitStructure);               //��ʼ��PC10
   
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;            //PC11
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
    GPIO_Init(GPIOC, &GPIO_InitStructure);               //��ʼ��PC11
	
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;            //PC12
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	 //�����������
    GPIO_Init(GPIOC, &GPIO_InitStructure);               //��ʼ��PC12
	
	USART_InitStructure.USART_BaudRate = bound;                                    //����������
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;                    //�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;                         //һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;                            //����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	               //�շ�ģʽ
    USART_Init(UART4, &USART_InitStructure);                                      //���������ô���4
	
    USART_Cmd(UART4, ENABLE);                              //ʹ�ܴ���4
	USART_ClearFlag(UART4, USART_FLAG_TC);	                //�����־λ
	USART_ITConfig(UART4, USART_IT_RXNE, ENABLE);          //���������ж�

    NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn;        //����4�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2; //��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =2;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//�ж�ͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	                        //������������
	
	RS485_RX_TX=0;				                            //����ģʽ
}



/*-------------------------------------------------*/
/*������������2printf                              */
/*��  ������                                       */
/*����ֵ����                                       */
/*-------------------------------------------------*/

__align(8) u8  RS485_TX_BUF[RS485_TXBUFF_SIZE];  

void RS485_printf(char* fmt,...) 
{  
	u16 i,length;
	
	va_list ap;
	va_start(ap,fmt);
	vsprintf((char*)RS485_TX_BUF,fmt,ap);
	va_end(ap);
	
	RS485_RX_TX=1;  //����ģʽ
	delay_ms(1);
	
	length=strlen((const char*)RS485_TX_BUF);	
	while((UART4->SR&0X40)==0);
	for(i = 0;i < length;i ++)
	{			
		UART4->DR = RS485_TX_BUF[i];
		while((UART4->SR&0X40)==0);	
	}	
	
	RS485_RX_TX=0;  //����ģʽ
	delay_ms(1);
}
