/*-------------------------------------------------*/
/*             ��γ����STM32ϵ�п�����              */
/*    �Ա���ַ�� http://chaoweidianzi.taobao.com   */
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*            ����Դ�ļ�,��2������                 */
/*-------------------------------------------------*/
/* void KEY_Init(void);	   ������ʼ��              */     
/* u8 KEY_Scan(u8 mode);   ����������	           */
/*-------------------------------------------------*/

#include "key.h"
#include "delay.h" 

/*-------------------------------------------------*/
/*����������ʼ��KEY��������                        */
/*��  ������                                       */
/*����ֵ����                                       */
/*-------------------------------------------------*/
void KEY_Init(void)
{	
	GPIO_InitTypeDef GPIO_InitStructure;                                  	//����һ��IO�˿ڲ����ṹ��
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA , ENABLE);  			   			//ʹ��PC�˿�ʱ��
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOC , ENABLE);  			   				//ʹ��PD�˿�ʱ��
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 ;   //��ʼ��PC0.2.3
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;                      	//����50Mhz
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;   					   						//���������ʽ
	GPIO_Init(GPIOA, &GPIO_InitStructure);            					   					//��ʼ��PC0.2.3
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 ;   //��ʼ��PC0.2.3
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;                      	//����50Mhz
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;   					   						//���������ʽ
	GPIO_Init(GPIOC, &GPIO_InitStructure);            					   					//��ʼ��PC0.2.3
	
} 

/*-------------------------------------------------*/
/*������������������                             */
/*��  ����mode��0-���º󴥷�   1-�ͷź󴥷�        */
/*����ֵ������ֵ                                   */
/*-------------------------------------------------*/
u8 KEY_Scan(u8 mode)
{	 	  
	u8 key_num;                //���水��ֵ

	key_num = NONE_PRES_NUM;     //������Ϊ�ް���ֵ(0)
	if(KEY1!=0)
	{
		delay_ms(10);                               //ȥ���� 
		if(KEY1!=0)        key_num = KEY1_PRES_NUM;//����K1��ֵ
		else if(KEY2!=0)   key_num = KEY2_PRES_NUM;//����K2��ֵ
		//else if(KEY3==0)   key_num = KEY3_PRES_NUM;//����K3��ֵ
		//else if(KEY4==0)   key_num = KEY4_PRES_NUM;//����K4��ֵ
		
		if(mode)                                       //modeλ1��ʱ���ͷŰ�����Ŵ���
		while(KEY1!=0);//while(KEY1==0||KEY2==0); 					 //���ּ��
	} 
	if(KEY2!=0)
	{
		delay_ms(10);                               //ȥ���� 
		if(KEY1!=0)        key_num = KEY1_PRES_NUM;//����K1��ֵ
		else if(KEY2!=0)   key_num = KEY2_PRES_NUM;//����K2��ֵ
		//else if(KEY3==0)   key_num = KEY3_PRES_NUM;//����K3��ֵ
		//else if(KEY4==0)   key_num = KEY4_PRES_NUM;//����K4��ֵ
		
		if(mode)                                       //modeλ1��ʱ���ͷŰ�����Ŵ���
		while(KEY2!=0);
	}
	return key_num;                                //���ؼ�ֵ
}




















