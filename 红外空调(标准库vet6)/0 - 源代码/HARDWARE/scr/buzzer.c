/*-------------------------------------------------*/
/*             超纬电子STM32系列开发板              */
/*    淘宝地址： http://chaoweidianzi.taobao.com   */
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*            蜂鸣器源文件,有1个函数               */
/*-------------------------------------------------*/
/* void Buzzer_Init(void);  初始化蜂鸣器控制引脚   */
/*-------------------------------------------------*/

#include "buzzer.h" 
		    
/*-------------------------------------------------*/
/*函数名：初始化蜂鸣器控制引脚函数                 */
/*参  数：无                                       */
/*返回值：无                                       */
/*-------------------------------------------------*/
void Buzzer_Init(void)
{    	 
	GPIO_InitTypeDef GPIO_InitStructure;                                   //定义一个IO端口参数结构体
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB , ENABLE);  			   //使能PB端口时钟
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14 ;                            //初始化PB14端口
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;                      //速率50Mhz
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   					   //推免输出方式
	GPIO_Init(GPIOB, &GPIO_InitStructure);            					   //初始化PB14
	
	BUZZE=0;                                             //初始化后，关闭蜂鸣器
}






