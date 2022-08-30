


#include "main.h"
#include "delay.h"
#include "can.h"
#include "key.h"
#include "led.h"
#include "usart2.h"
#include "timer3.h"
//#include "DS18B20.h"
	
	
SYS_STATUS   Sys_Status;
SYS_CLOCK    Sys_Clock;
SYS_DATA     Sys_Data;



///*
//		每秒
//		
//*/
//void TaskWorkOneSecond(void)
//{
//		if(Sys_Clock.sFlag != 1)
//			return;
//		
//		Sys_Clock.sFlag = 0;
//		
//		if(Sys_Status.LED3 == ON)
//		{Sys_Status.LED3 = 1;LED_D3 = OFF;}
//		else
//		{Sys_Status.LED3 = 0;LED_D3 = ON;}

//}

/*
		每分钟检测一次温度变化，连续3次以上大于28℃ 开空调，连续三次检测小于25℃关空调
		
*/
//void TaskWorkOneMinute(void)
//{	
//		if(Sys_Clock.mFlag != 1)
//				return;
//		
//		Sys_Clock.mFlag = 0;
//	
//		Sys_Data.Temp = DS18B20_GetTemperture();
//		Log_printf("DS18B20_GetTemperture = %.1f\n",Sys_Data.Temp);
//		
//		if(Sys_Data.Temp < 10)
//			return;
//		else if(Sys_Data.Temp > 40)
//			return;
//		else if(Sys_Data.Temp <= 25)
//				Sys_Status.LowTemp++;
//		else if(Sys_Data.Temp >= 28)
//				Sys_Status.HighTemp++;
//		else
//				Sys_Status.HighTemp = Sys_Status.LowTemp = 0;
//		
//		if((!Sys_Status.AirConditioning) && (Sys_Status.HighTemp >= 3))
//			OPEN_GREE_AIR();
//		else if((Sys_Status.AirConditioning) && (Sys_Status.LowTemp >= 3))
//			CLOSE_GREE_AIR();
//		
//}

int main()
{ 

	
	delay_init();       //滴答定时器
//	SysTick_Init(72);		//滴答定时器
	//Usart2_init(115200);//串口1初始化
	KEY_Init();         //按键初始化
	LED_Init();         //LED初始化
	//TIM3_Init(7200,100);//10ms中断
	TIM4_Configuration(1895);//配置PWM输出
	//TIM_SetCompare4(TIM4,0);
	//TIM_Cmd(TIM4, DISABLE); 
	/*************	USER WORK	*************/
	//Log_printf("***********************System Start************************\n");
	//Log_printf("***********************System Start************************\n");
	//Log_printf("***********************System Start************************\n");
	
	//Sys_Data.res = DS18B20_Init();
	//Sys_Data.Temp = DS18B20_GetTemperture();
	//Log_printf("DS18B20_GetTemperture = %.1f\n",Sys_Data.Temp);
	while(1)
	{
		//TaskWorkOneSecond();		
		
		//TaskWorkOneMinute();
		

		
		Sys_Status.Key = KEY_Scan(1);
		if(Sys_Status.Key == KEY1_PRES_NUM)
			OPEN_GREE_AIR();
			//OPEN_RESHUIQI();
		else if(Sys_Status.Key == KEY2_PRES_NUM)
			CLOSE_GREE_AIR();
	}
}


