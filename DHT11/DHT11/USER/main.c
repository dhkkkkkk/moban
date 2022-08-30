#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "usart.h"	 
#include "dht11.h" 	 
 
 
/************************************************  
 ALIENTEK精英STM32开发板     
 作者：唯恋殊雨    
 CSDN博客：https://blog.csdn.net/tichimi3375    
 OUT-PG11 
************************************************/  
 
 int main(void)
 {	 			    
	u8 temperature;  	    
	u8 humidity;    	   

	delay_init();	    	 //延时函数初始化	  
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断优先级分组为组2：2位抢占优先级，2位响应优先级
	uart_init(115200);	 	//串口初始化为115200
	//LED_Init();		  		//初始化与LED连接的硬件接口
 	while(DHT11_Init())	//DHT11初始化	
	{
		printf("DHT11 Error");
		delay_ms(200);
	}								   	 
	while(1)
	{	    	    								  
		DHT11_Read_Data(&temperature,&humidity);	//读取温湿度值					    
		printf("温度为：%d",temperature);	//显示温度	   		   
		printf("湿度为：%d",humidity);		//显示湿度	 	   				   
	 	delay_ms(200);
	}
}




