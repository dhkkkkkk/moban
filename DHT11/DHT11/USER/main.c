#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "usart.h"	 
#include "dht11.h" 	 
 
 
/************************************************  
 ALIENTEK��ӢSTM32������     
 ���ߣ�Ψ������    
 CSDN���ͣ�https://blog.csdn.net/tichimi3375    
 OUT-PG11 
************************************************/  
 
 int main(void)
 {	 			    
	u8 temperature;  	    
	u8 humidity;    	   

	delay_init();	    	 //��ʱ������ʼ��	  
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(115200);	 	//���ڳ�ʼ��Ϊ115200
	//LED_Init();		  		//��ʼ����LED���ӵ�Ӳ���ӿ�
 	while(DHT11_Init())	//DHT11��ʼ��	
	{
		printf("DHT11 Error");
		delay_ms(200);
	}								   	 
	while(1)
	{	    	    								  
		DHT11_Read_Data(&temperature,&humidity);	//��ȡ��ʪ��ֵ					    
		printf("�¶�Ϊ��%d",temperature);	//��ʾ�¶�	   		   
		printf("ʪ��Ϊ��%d",humidity);		//��ʾʪ��	 	   				   
	 	delay_ms(200);
	}
}




