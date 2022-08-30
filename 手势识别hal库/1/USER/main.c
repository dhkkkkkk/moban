#include "led.h"
#include "delay.h"
#include "sys.h"
#include "key.h"
#include "usart.h"
#include "usmart.h"
#include "paj7620u2.h"

/************************************************
 ALIENTEK NANO STM32������ ��չʵ��4
 ATK-PAJ7620U2����ʶ��ģ�����ʵ��-HAL��汾
 ����֧�֣�www.openedv.com
 �Ա����̣�http://eboard.taobao.com 
 ��ע΢�Ź���ƽ̨΢�źţ�"����ԭ��"����ѻ�ȡSTM32���ϡ�
 ������������ӿƼ����޹�˾  
 ���ߣ�����ԭ�� @ALIENTEK
************************************************/


int main(void)
{
  
    HAL_Init();                    	//��ʼ��HAL��    
    Stm32_Clock_Init(RCC_PLL_MUL9); //����ʱ��,72M
    delay_init(72);                 //��ʼ����ʱ����
	uart_init(115200);				//��ʼ������115200
    LED_Init();                     //��ʼ��LED 
	KEY_Init();						//��ʼ������
	usmart_init(72);                //USMART��ʼ��
	printf("ALIENTEK NANO STM32\r\n");
    printf("Sensor PAJ7620U2 TEST\r\n");
    while(!paj7620u2_init())//PAJ7620U2��������ʼ��
	{
	    printf("PAJ7620U2 Error!!!\r\n");
		delay_ms(500);
		LED0=!LED0;//DS0��˸
		
	}
    printf("PAJ7620U2 OK\r\n");
	while(1)
	{
		paj7620u2_sensor_test();//PAJ7620U2����������
	}
}

