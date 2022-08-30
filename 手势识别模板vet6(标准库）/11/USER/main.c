#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "lcd.h"
#include "key.h"
#include "usmart.h"
#include "paj7620u2.h"

/************************************************
 ALIENTEK MiniV3 STM32开发板扩展实验22
 ATK-PAJ7620U2手势识别模块测试实验 
 技术支持：www.openedv.com
 淘宝店铺：http://eboard.taobao.com 
 关注微信公众平台微信号："正点原子"，免费获取STM32资料。
 广州市星翼电子科技有限公司  
 作者：正点原子 @ALIENTEK
************************************************/
   	
 int main(void)
 { 

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);// 设置中断优先级分组2
	delay_init();	    	 //延时函数初始化	  
	uart_init(115200);	 	 //串口初始化为115200
	KEY_Init();				 //按键初始化
	
 	while(!paj7620u2_init())//PAJ7620U2传感器初始化
	{
	    printf("PAJ7620U2 Error!!!\r\n");
	    delay_ms(500);
		delay_ms(500);
		
	}
    printf("PAJ7620U2 OK\r\n");
	while(1)
	{
		paj7620u2_sensor_test();//PAJ7620U2传感器测试
	}
}
