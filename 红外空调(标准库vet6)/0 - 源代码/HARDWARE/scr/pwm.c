/*-------------------------------------------------*/
/*         超纬电子STM32F407ZGT6开发板             */
/*    淘宝地址： http://chaoweidianzi.taobao.com   */
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*            PWM源文件,有个1函数                  */
/*-------------------------------------------------*/
/*  void TIM4_PWM_Init(u32 arr,u32 psc)            */
/*-------------------------------------------------*/

#include "pwm.h"

/*-------------------------------------------------*/
/*函数名：TIM3通道3的PWM初始化                     */
/*参  数：arr：自动重装值                          */
/*参  数：psc：时钟预分频数                        */
/*返回值：无                                       */
/*-------------------------------------------------*/
void TIM4_PWM_Init(u32 arr,u32 psc)
{		 					 	
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);	                      //使能定时器4时钟
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD  | RCC_APB2Periph_AFIO, ENABLE);  //使能GPIOD外设和AFIO复用功能模块时钟
	
	GPIO_PinRemapConfig(GPIO_Remap_TIM4, ENABLE);                                //Timer4重映射  TIM4_CH1->PD12    
  
   
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;           //TIM4_CH1
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;      //复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOD, &GPIO_InitStructure);               //初始化GPIO
 
	TIM_TimeBaseStructure.TIM_Period = arr-1;                     //设置在下一个更新事件装入活动的自动重装载寄存器周期的值
	TIM_TimeBaseStructure.TIM_Prescaler =psc-1;                   //设置用来作为TIMx时钟频率除数的预分频值 
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;                  //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;   //TIM向上计数模式

	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);               //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;             //选择定时器模式:TIM脉冲宽度调制模式2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;     //输出极性:TIM输出比较极性高
	TIM_OC1Init(TIM4, &TIM_OCInitStructure);                      //根据T指定的参数初始化外设TIM4 OC1

	TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);             //使能TIM4在CCR1上的预装载寄存器
 
	TIM_Cmd(TIM4, ENABLE);                                        //使能TIM4								  
}  


