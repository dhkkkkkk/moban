/*-------------------------------------------------*/
/*           超纬电子STM32系列开发板                */
/*    淘宝地址： http://chaoweidianzi.taobao.com   */
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*                   LED源文件                     */
/*-------------------------------------------------*/

#include "led.h" 
		    
/*-------------------------------------------------*/
/*函数名：初始化LED函数                            */
/*参  数：无                                       */
/*返回值：无                                       */
/*-------------------------------------------------*/
void LED_Init(void)
{    	 
	GPIO_InitTypeDef GPIO_InitStructure;                                   //定义一个IO端口参数结构体
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB , ENABLE);  			   //使能PD端口时钟
	
	GPIO_InitStructure.GPIO_Pin =   GPIO_Pin_5 | GPIO_Pin_0 | GPIO_Pin_1;//初始化PD12.13.14端口
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;                      //速率50Mhz
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   					   //推免输出方式
	GPIO_Init(GPIOB, &GPIO_InitStructure);            					   //初始化PD12.13.14
	
	LED_AllOff();       //初始化引脚后，所有LED处于熄灭状态
}

/*-------------------------------------------------*/
/*函数名：点亮所有LED                              */
/*参  数：无                                       */
/*返回值：无                                       */
/*-------------------------------------------------*/
void LED_AllOn(void)
{
	LED_D1 = LED_D2 = LED_D3 = 0;   //共阳极，拉低IO，点亮D1.2.3
}

/*-------------------------------------------------*/
/*函数名：熄灭所有LED                              */
/*参  数：无                                       */
/*返回值：无                                       */
/*-------------------------------------------------*/
void LED_AllOff(void)
{
	LED_D1 = LED_D2 = LED_D3 = 1;   //共阳极，拉高IO，熄灭D1.2.3
}





