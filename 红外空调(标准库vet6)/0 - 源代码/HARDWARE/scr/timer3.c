/*-------------------------------------------------*/
/*            超纬电子STM32系列开发板               */
/*    淘宝地址： http://chaoweidianzi.taobao.com   */
/*-------------------------------------------------*/
/*-----------------------------------------------------*/
/*           定时器3源文件,有1个函数                   */
/*-----------------------------------------------------*/
/*void TIM3_Init(u16 arr,u16 psc); 定时器3初始化       */
/*-----------------------------------------------------*/

#include "timer3.h"

/*-------------------------------------------------*/
/*函数名：定时器3初始化                            */
/*参  数：arr：自动重装值                          */
/*        psc：时钟预分频数                        */
/*返回值：无                                       */
/*-------------------------------------------------*/
void TIM3_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);           //使能TIM3时钟	
  TIM_TimeBaseInitStructure.TIM_Period = arr-1; 	              //自动重装载值
	TIM_TimeBaseInitStructure.TIM_Prescaler=psc-1;                //定时器分频	
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数模式
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;     //1分频
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);            //按配置设置TIM3
	
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);                      //允许定时器3更新中断
	TIM_Cmd(TIM3,ENABLE);                                         //使能定时器3
	
	NVIC_InitStructure.NVIC_IRQChannel=TIM3_IRQn;                 //定时器3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x01;    //抢占优先级1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x03;           //子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;                 //使能中断
	NVIC_Init(&NVIC_InitStructure);                               //按配置设置 
}

/******************************************************************************
*                           TIM4  PWM配置和启动
*******************************************************************************
* Description  : 
*
* Input        : dt =周期
* Output       : None
* Return       : None
* 备注         : 频率=720000/dt
*******************************************************************************/

void TIM4_Configuration(u16 Period)
{
	 	
	GPIO_InitTypeDef GPIO_InitStructure;						//配置使用的GPIO

	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;

	TIM_OCInitTypeDef  TIM_OCInitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 //GPIO使用的RCC时钟使能
		  	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 ;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;				//GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE); //时钟使能

	TIM_InternalClockConfig(TIM4); 							//配置 TIMx 内部时钟
	TIM_TimeBaseStructure.TIM_Period = Period-1; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	 Period这个即是设置TIMx_ARR的值，即用来设置pwm的频率
	TIM_TimeBaseStructure.TIM_Prescaler = 0; //设置用来作为TIMx时钟频率除数的预分频值  (72-1)10Khz的计数频率  
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0x0;
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
 
	

	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //选择定时器模式:TIM脉冲宽度调制模式2
	TIM_OCInitStructure.TIM_Pulse = 600; //设置待装入捕获比较寄存器的脉冲值，设置占空比
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //输出极性:TIM输出比较极性高
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; 
	TIM_OC4Init(TIM4, &TIM_OCInitStructure); //根据TIM_OCInitStruct中指定的参数初始化外设TIMx

 	TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable); //使能TIMx在CCR1上的预装载寄存器

	TIM_ARRPreloadConfig(TIM4, ENABLE); //使能TIMx在ARR上的预装载寄存器

	TIM_ITConfig(TIM4, TIM_IT_Update,          //溢出中断
					   // | TIM_IT_Trigger,     //触发中断
					   ENABLE );//使能TIM3触发中断

	TIM_CtrlPWMOutputs(TIM4,ENABLE);	 //PWM功能使能

	TIM_Cmd(TIM4, DISABLE);  //使能TIMx外设							 
}
