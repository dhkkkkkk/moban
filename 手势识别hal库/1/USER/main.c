#include "led.h"
#include "delay.h"
#include "sys.h"
#include "key.h"
#include "usart.h"
#include "usmart.h"
#include "paj7620u2.h"

/************************************************
 ALIENTEK NANO STM32开发板 扩展实验4
 ATK-PAJ7620U2手势识别模块测试实验-HAL库版本
 技术支持：www.openedv.com
 淘宝店铺：http://eboard.taobao.com 
 关注微信公众平台微信号："正点原子"，免费获取STM32资料。
 广州市星翼电子科技有限公司  
 作者：正点原子 @ALIENTEK
************************************************/


int main(void)
{
  
    HAL_Init();                    	//初始化HAL库    
    Stm32_Clock_Init(RCC_PLL_MUL9); //设置时钟,72M
    delay_init(72);                 //初始化延时函数
	uart_init(115200);				//初始化串口115200
    LED_Init();                     //初始化LED 
	KEY_Init();						//初始化按键
	usmart_init(72);                //USMART初始化
	printf("ALIENTEK NANO STM32\r\n");
    printf("Sensor PAJ7620U2 TEST\r\n");
    while(!paj7620u2_init())//PAJ7620U2传感器初始化
	{
	    printf("PAJ7620U2 Error!!!\r\n");
		delay_ms(500);
		LED0=!LED0;//DS0闪烁
		
	}
    printf("PAJ7620U2 OK\r\n");
	while(1)
	{
		paj7620u2_sensor_test();//PAJ7620U2传感器测试
	}
}

