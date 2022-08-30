/*-------------------------------------------------*/
/*             ��γ����STM32ϵ�п�����              */
/*    �Ա���ַ�� http://chaoweidianzi.taobao.com   */
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*            ������Դ�ļ�,��1������               */
/*-------------------------------------------------*/
/* void Buzzer_Init(void);  ��ʼ����������������   */
/*-------------------------------------------------*/

#include "buzzer.h" 
		    
/*-------------------------------------------------*/
/*����������ʼ���������������ź���                 */
/*��  ������                                       */
/*����ֵ����                                       */
/*-------------------------------------------------*/
void Buzzer_Init(void)
{    	 
	GPIO_InitTypeDef GPIO_InitStructure;                                   //����һ��IO�˿ڲ����ṹ��
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB , ENABLE);  			   //ʹ��PB�˿�ʱ��
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14 ;                            //��ʼ��PB14�˿�
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;                      //����50Mhz
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   					   //���������ʽ
	GPIO_Init(GPIOB, &GPIO_InitStructure);            					   //��ʼ��PB14
	
	BUZZE=0;                                             //��ʼ���󣬹رշ�����
}






