#include "GREE.h"
#include "LED.h"
#include "Timer3.h"
#include "delay.h"


/*
遥控器 格力
关机
head
100 0 10 0 0 0101 000000000100000010100100    共36位
20ms
0000000000000100000000000000111 0 0         共33位
40ms
head
100 01000 01010000 00000100 00001110 0100
20ms
00000000 00000000 00001000 00000110 0
*/

/*
遥控器 格力
开机 制冷 26℃
head
100 11000 01010000 00000100 00001010 0100
20ms
00000000 00000100 00000000 0000111 1 0
40ms
head
100 11000 01010000 00000100 00001110 0100
20ms
00000000 00000000 00001000 00000111 0
*/   
//26度0101对应1111 25度1001对应0111
//100制冷 1打开 10一级风 0扫风 0睡眠 0101 26度00000000定时 0超强 1灯光 0健康 0干燥0换气|0,0,0,1,0,1,0,0,1,0 ↓多一位未知
const uint8_t GREE_OPEN_AIR[138] = {1,0,0,1,1,1,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,1,0,0,1,0,0,  //36
																		0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,				//33
																		1,0,0,1,1,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,1,1,0,0,1,0,0,	//36
																		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,1,1,0					//33
};
//0上下扫风 000默认 0左右扫风 000默认 00温度显示 0001000000000000
const uint8_t GREE_CLOSE_AIR[138] ={1,0,0,0,1,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,1,0,0,1,0,0,   //共36位
																		0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,         //共33位
																		1,0,0,0,1,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,1,1,0,0,1,0,0,	 //共36位
																		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,1,0,0			     //共33位
};


																			
/*******************************************************************************
* 函 数 名         : OPEN_GREE_AIR
* 函数功能		     : 开空调 
* 输    入         : 无
* 输    出         : 无
*******************************************************************************/
void OPEN_GREE_AIR(void)
{
		uint8_t i;
	  //TIM_SetCompare4(TIM4,569);
		TIM_Cmd(TIM4, ENABLE); 
		delay_us(9000); 
		TIM_Cmd(TIM4, DISABLE); 
		delay_us(4500);	

		 
		for(i=0;i<36;i++)
		{
			TIM_Cmd(TIM4, ENABLE);
			delay_us(656);//560
			TIM_Cmd(TIM4, DISABLE); 			
			if(GREE_OPEN_AIR[i]==0)   
				delay_us(544);   //0.56ms 620
			else  
				delay_us(1640); //1.69ms			
		}
		
		delay_ms(20); //20ms
		
		for(;i<36+33;i++)
		{
			TIM_Cmd(TIM4, ENABLE);
			delay_us(656);//480
			TIM_Cmd(TIM4, DISABLE); 			
			if(GREE_OPEN_AIR[i]==0)   
				delay_us(544);   //0.56ms 620
			else  
				delay_us(1640); //1.69ms			
		}		
		
		delay_ms(40); //40ms
		
		TIM_Cmd(TIM4, ENABLE); 
		delay_us(9000); 
		TIM_Cmd(TIM4, DISABLE); 
		delay_us(4500);			
		
		for(;i<36+33+36;i++)
		{
			TIM_Cmd(TIM4, ENABLE);
			delay_us(656);//480
			TIM_Cmd(TIM4, DISABLE); 			
			if(GREE_OPEN_AIR[i]==0)   
				delay_us(544);   //0.56ms 620
			else  
				delay_us(1640); //1.69ms			
		}		
		
		delay_ms(20); //20ms
		
		for(;i<36+33+36+33;i++)
		{
			TIM_Cmd(TIM4, ENABLE);
			delay_us(656);//480
			TIM_Cmd(TIM4, DISABLE); 			
			if(GREE_OPEN_AIR[i]==0)   
				delay_us(544);   //0.56ms 620
			else  
				delay_us(1640); //1.69ms			
		}			
		

}


/*******************************************************************************
* 函 数 名         : CLOSE_GREE_AIR
* 函数功能		     : 开空调 
* 输    入         : 无
* 输    出         : 无
*******************************************************************************/
void CLOSE_GREE_AIR(void)
{
		uint8_t i;
		TIM_Cmd(TIM4, ENABLE); 
		delay_us(9000); 
		TIM_Cmd(TIM4, DISABLE); 
		delay_us(4500);	

		 
		for(i=0;i<36;i++)
		{
			TIM_Cmd(TIM4, ENABLE);
			delay_us(656);//480
			TIM_Cmd(TIM4, DISABLE); 			
			if(GREE_CLOSE_AIR[i]==0)   
				delay_us(544);   //0.56ms 620
			else  
				delay_us(1640); //1.69ms			
		}
		
		delay_ms(20); //20ms
		
		for(;i<36+33;i++)
		{
			TIM_Cmd(TIM4, ENABLE);
			delay_us(656);//480
			TIM_Cmd(TIM4, DISABLE); 			
			if(GREE_CLOSE_AIR[i]==0)   
				delay_us(544);   //0.56ms 620
			else  
				delay_us(1640); //1.69ms			
		}		
		
		delay_ms(40); //40ms
		
		TIM_Cmd(TIM4, ENABLE); 
		delay_us(9000); 
		TIM_Cmd(TIM4, DISABLE); 
		delay_us(4500);			
		
		for(;i<36+33+36;i++)
		{
			TIM_Cmd(TIM4, ENABLE);
			delay_us(656);//480
			TIM_Cmd(TIM4, DISABLE); 			
			if(GREE_CLOSE_AIR[i]==0)   
				delay_us(544);   //0.56ms 620
			else  
				delay_us(1640); //1.69ms			
		}		
		
		delay_ms(20); //20ms
		
		for(;i<36+33+36+33;i++)
		{
			TIM_Cmd(TIM4, ENABLE);
			delay_us(656);//480
			TIM_Cmd(TIM4, DISABLE); 			
			if(GREE_CLOSE_AIR[i]==0)   
				delay_us(544);   //0.56ms 620
			else  
				delay_us(1640); //1.69ms			
		}		
}



