/*-------------------------------------------------*/
/*             超纬电子STM32系列开发板              */
/*    淘宝地址： http://chaoweidianzi.taobao.com   */
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*          外部中断源文件,有1个函数               */
/*-------------------------------------------------*/
/* void KEY_EXTI_Init(void);	外部中断初始化     */     
/*-------------------------------------------------*/

#include "exti.h"
#include "key.h"

/*-------------------------------------------------*/
/*函数名：按键外部中断初始化程序.                  */
/*参  数：无                                       */
/*返回值：无                                       */
/*-------------------------------------------------*/	   
void KEY_EXTI_Init(void)
{
	NVIC_InitTypeDef   NVIC_InitStructure;
	EXTI_InitTypeDef   EXTI_InitStructure;

	KEY_Init();       //初始化按键

  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	          //使能复用功能时钟

  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource0);    //配置PC0中断线
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource2);    //配置PC2中断线
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource3);    //配置PC3中断线
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOD,GPIO_PinSource7);    //配置PD7中断线

  	EXTI_InitStructure.EXTI_Line = EXTI_Line0 | EXTI_Line2 |EXTI_Line3 |EXTI_Line7;	
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	          //外部中断
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;       //下降沿
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;                     //使能
  	EXTI_Init(&EXTI_InitStructure);	 	                          //根据配置初始化

  	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;			  //使能K1所在的外部中断通道
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;  //抢占优先级2， 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x03;		  //子优先级3
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			      //使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure); 

    NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;			  //使能按键K2所在的外部中断通道
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;  //抢占优先级2
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;		  //子优先级2
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;				  //使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure);                               //根据配置初始化

  	NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;			  //使能按键K3所在的外部中断通道
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;  //抢占优先级2 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;		  //子优先级1 
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;				  //使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure);  	                          //根据配置初始化

	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;			  //使能按键K4所在的外部中断通道
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;  //抢占优先级2 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;		  //子优先级0 
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;				  //使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure);  	 						  //根据配置初始化
}
