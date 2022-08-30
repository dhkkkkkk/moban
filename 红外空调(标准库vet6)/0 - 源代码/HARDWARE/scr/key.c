/*-------------------------------------------------*/
/*             超纬电子STM32系列开发板              */
/*    淘宝地址： http://chaoweidianzi.taobao.com   */
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*            按键源文件,有2个函数                 */
/*-------------------------------------------------*/
/* void KEY_Init(void);	   按键初始化              */     
/* u8 KEY_Scan(u8 mode);   按键处理函数	           */
/*-------------------------------------------------*/

#include "key.h"
#include "delay.h" 

/*-------------------------------------------------*/
/*函数名：初始化KEY按键函数                        */
/*参  数：无                                       */
/*返回值：无                                       */
/*-------------------------------------------------*/
void KEY_Init(void)
{	
	GPIO_InitTypeDef GPIO_InitStructure;                                  	//定义一个IO端口参数结构体
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA , ENABLE);  			   			//使能PC端口时钟
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOC , ENABLE);  			   				//使能PD端口时钟
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 ;   //初始化PC0.2.3
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;                      	//速率50Mhz
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;   					   						//推免输出方式
	GPIO_Init(GPIOA, &GPIO_InitStructure);            					   					//初始化PC0.2.3
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 ;   //初始化PC0.2.3
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;                      	//速率50Mhz
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;   					   						//推免输出方式
	GPIO_Init(GPIOC, &GPIO_InitStructure);            					   					//初始化PC0.2.3
	
} 

/*-------------------------------------------------*/
/*函数名：按键处理函数                             */
/*参  数：mode：0-按下后触发   1-释放后触发        */
/*返回值：按键值                                   */
/*-------------------------------------------------*/
u8 KEY_Scan(u8 mode)
{	 	  
	u8 key_num;                //保存按键值

	key_num = NONE_PRES_NUM;     //先设置为无按键值(0)
	if(KEY1!=0)
	{
		delay_ms(10);                               //去抖动 
		if(KEY1!=0)        key_num = KEY1_PRES_NUM;//返回K1键值
		else if(KEY2!=0)   key_num = KEY2_PRES_NUM;//返回K2键值
		//else if(KEY3==0)   key_num = KEY3_PRES_NUM;//返回K3键值
		//else if(KEY4==0)   key_num = KEY4_PRES_NUM;//返回K4键值
		
		if(mode)                                       //mode位1的时候，释放按键后才触发
		while(KEY1!=0);//while(KEY1==0||KEY2==0); 					 //松手检测
	} 
	if(KEY2!=0)
	{
		delay_ms(10);                               //去抖动 
		if(KEY1!=0)        key_num = KEY1_PRES_NUM;//返回K1键值
		else if(KEY2!=0)   key_num = KEY2_PRES_NUM;//返回K2键值
		//else if(KEY3==0)   key_num = KEY3_PRES_NUM;//返回K3键值
		//else if(KEY4==0)   key_num = KEY4_PRES_NUM;//返回K4键值
		
		if(mode)                                       //mode位1的时候，释放按键后才触发
		while(KEY2!=0);
	}
	return key_num;                                //返回键值
}




















