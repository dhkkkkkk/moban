/*-------------------------------------------------*/
/*            ��γ����STM32ϵ�п�����               */
/*    �Ա���ַ�� http://chaoweidianzi.taobao.com   */
/*-------------------------------------------------*/
/*-----------------------------------------------------*/
/*           ��ʱ��3Դ�ļ�,��1������                   */
/*-----------------------------------------------------*/
/*void TIM3_Init(u16 arr,u16 psc); ��ʱ��3��ʼ��       */
/*-----------------------------------------------------*/

#include "timer3.h"

/*-------------------------------------------------*/
/*����������ʱ��3��ʼ��                            */
/*��  ����arr���Զ���װֵ                          */
/*        psc��ʱ��Ԥ��Ƶ��                        */
/*����ֵ����                                       */
/*-------------------------------------------------*/
void TIM3_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);           //ʹ��TIM3ʱ��	
  TIM_TimeBaseInitStructure.TIM_Period = arr-1; 	              //�Զ���װ��ֵ
	TIM_TimeBaseInitStructure.TIM_Prescaler=psc-1;                //��ʱ����Ƶ	
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;     //1��Ƶ
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);            //����������TIM3
	
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);                      //����ʱ��3�����ж�
	TIM_Cmd(TIM3,ENABLE);                                         //ʹ�ܶ�ʱ��3
	
	NVIC_InitStructure.NVIC_IRQChannel=TIM3_IRQn;                 //��ʱ��3�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x01;    //��ռ���ȼ�1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x03;           //�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;                 //ʹ���ж�
	NVIC_Init(&NVIC_InitStructure);                               //���������� 
}

/******************************************************************************
*                           TIM4  PWM���ú�����
*******************************************************************************
* Description  : 
*
* Input        : dt =����
* Output       : None
* Return       : None
* ��ע         : Ƶ��=720000/dt
*******************************************************************************/

void TIM4_Configuration(u16 Period)
{
	 	
	GPIO_InitTypeDef GPIO_InitStructure;						//����ʹ�õ�GPIO

	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;

	TIM_OCInitTypeDef  TIM_OCInitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 //GPIOʹ�õ�RCCʱ��ʹ��
		  	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 ;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;				//GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE); //ʱ��ʹ��

	TIM_InternalClockConfig(TIM4); 							//���� TIMx �ڲ�ʱ��
	TIM_TimeBaseStructure.TIM_Period = Period-1; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	 Period�����������TIMx_ARR��ֵ������������pwm��Ƶ��
	TIM_TimeBaseStructure.TIM_Prescaler = 0; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ  (72-1)10Khz�ļ���Ƶ��  
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0x0;
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
 
	

	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
	TIM_OCInitStructure.TIM_Pulse = 600; //���ô�װ�벶��ȽϼĴ���������ֵ������ռ�ձ�
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //�������:TIM����Ƚϼ��Ը�
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; 
	TIM_OC4Init(TIM4, &TIM_OCInitStructure); //����TIM_OCInitStruct��ָ���Ĳ�����ʼ������TIMx

 	TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable); //ʹ��TIMx��CCR1�ϵ�Ԥװ�ؼĴ���

	TIM_ARRPreloadConfig(TIM4, ENABLE); //ʹ��TIMx��ARR�ϵ�Ԥװ�ؼĴ���

	TIM_ITConfig(TIM4, TIM_IT_Update,          //����ж�
					   // | TIM_IT_Trigger,     //�����ж�
					   ENABLE );//ʹ��TIM3�����ж�

	TIM_CtrlPWMOutputs(TIM4,ENABLE);	 //PWM����ʹ��

	TIM_Cmd(TIM4, DISABLE);  //ʹ��TIMx����							 
}
