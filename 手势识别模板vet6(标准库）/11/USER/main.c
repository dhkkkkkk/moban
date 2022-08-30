#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "lcd.h"
#include "key.h"
#include "usmart.h"
#include "paj7620u2.h"

/************************************************
 ALIENTEK MiniV3 STM32��������չʵ��22
 ATK-PAJ7620U2����ʶ��ģ�����ʵ�� 
 ����֧�֣�www.openedv.com
 �Ա����̣�http://eboard.taobao.com 
 ��ע΢�Ź���ƽ̨΢�źţ�"����ԭ��"����ѻ�ȡSTM32���ϡ�
 ������������ӿƼ����޹�˾  
 ���ߣ�����ԭ�� @ALIENTEK
************************************************/
   	
 int main(void)
 { 

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);// �����ж����ȼ�����2
	delay_init();	    	 //��ʱ������ʼ��	  
	uart_init(115200);	 	 //���ڳ�ʼ��Ϊ115200
	KEY_Init();				 //������ʼ��
	
 	while(!paj7620u2_init())//PAJ7620U2��������ʼ��
	{
	    printf("PAJ7620U2 Error!!!\r\n");
	    delay_ms(500);
		delay_ms(500);
		
	}
    printf("PAJ7620U2 OK\r\n");
	while(1)
	{
		paj7620u2_sensor_test();//PAJ7620U2����������
	}
}
