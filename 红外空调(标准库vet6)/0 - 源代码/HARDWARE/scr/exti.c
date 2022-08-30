/*-------------------------------------------------*/
/*             ��γ����STM32ϵ�п�����              */
/*    �Ա���ַ�� http://chaoweidianzi.taobao.com   */
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*          �ⲿ�ж�Դ�ļ�,��1������               */
/*-------------------------------------------------*/
/* void KEY_EXTI_Init(void);	�ⲿ�жϳ�ʼ��     */     
/*-------------------------------------------------*/

#include "exti.h"
#include "key.h"

/*-------------------------------------------------*/
/*�������������ⲿ�жϳ�ʼ������.                  */
/*��  ������                                       */
/*����ֵ����                                       */
/*-------------------------------------------------*/	   
void KEY_EXTI_Init(void)
{
	NVIC_InitTypeDef   NVIC_InitStructure;
	EXTI_InitTypeDef   EXTI_InitStructure;

	KEY_Init();       //��ʼ������

  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	          //ʹ�ܸ��ù���ʱ��

  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource0);    //����PC0�ж���
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource2);    //����PC2�ж���
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource3);    //����PC3�ж���
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOD,GPIO_PinSource7);    //����PD7�ж���

  	EXTI_InitStructure.EXTI_Line = EXTI_Line0 | EXTI_Line2 |EXTI_Line3 |EXTI_Line7;	
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	          //�ⲿ�ж�
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;       //�½���
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;                     //ʹ��
  	EXTI_Init(&EXTI_InitStructure);	 	                          //�������ó�ʼ��

  	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;			  //ʹ��K1���ڵ��ⲿ�ж�ͨ��
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;  //��ռ���ȼ�2�� 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x03;		  //�����ȼ�3
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			      //ʹ���ⲿ�ж�ͨ��
  	NVIC_Init(&NVIC_InitStructure); 

    NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;			  //ʹ�ܰ���K2���ڵ��ⲿ�ж�ͨ��
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;  //��ռ���ȼ�2
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;		  //�����ȼ�2
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;				  //ʹ���ⲿ�ж�ͨ��
  	NVIC_Init(&NVIC_InitStructure);                               //�������ó�ʼ��

  	NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;			  //ʹ�ܰ���K3���ڵ��ⲿ�ж�ͨ��
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;  //��ռ���ȼ�2 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;		  //�����ȼ�1 
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;				  //ʹ���ⲿ�ж�ͨ��
  	NVIC_Init(&NVIC_InitStructure);  	                          //�������ó�ʼ��

	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;			  //ʹ�ܰ���K4���ڵ��ⲿ�ж�ͨ��
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;  //��ռ���ȼ�2 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;		  //�����ȼ�0 
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;				  //ʹ���ⲿ�ж�ͨ��
  	NVIC_Init(&NVIC_InitStructure);  	 						  //�������ó�ʼ��
}
