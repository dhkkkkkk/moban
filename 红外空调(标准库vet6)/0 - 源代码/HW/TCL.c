#include "TCL.h"


const uint8_t TCL_CLOSE_AIR[113] = {1,1,0,0,0,1,0,0,1,1,0,1,0,0,1,1,
																	 0,1,1,0,0,1,0,0,1,0,0,0,0,0,0,0,
																	 0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,
																	 1,1,0,0,0,0,0,0,1,0,1,0,0,0,0,0,
																	 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
																	 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
																	 0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0};			
	const uint8_t TCL_OPEN_AIR[113] = {1,1,0,0,0,1,0,0,1,1,0,1,0,0,1,1,
																		0,1,1,0,0,1,0,0,1,0,0,0,0,0,0,0,
																		0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,
																		1,1,0,0,0,0,0,0,1,0,1,0,0,0,0,0,
																		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
																		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
																		0,0,0,0,0,0,0,0,1,0,1,1,1,1,0,0,0};		
	
																				
/*******************************************************************************
* �� �� ��         : OPEN_TCL_AIR
* ��������		     : ���յ� 
* ��    ��         : ��
* ��    ��         : ��
*******************************************************************************/
void OPEN_TCL_AIR(void)		
{	
		uint8_t i; 
	
		Sys_Status.LED1 = 1;
	
		TIM_Cmd(TIM4, ENABLE); 
		delay_us(3000); 
		TIM_Cmd(TIM4, DISABLE); 
		delay_us(2500);
		TIM_Cmd(TIM4, ENABLE); 	
		
		for(i=0; i<sizeof(TCL_OPEN_AIR); i++) 
		{ 
			delay_us(565);//480
			TIM_Cmd(TIM4, DISABLE); 
			
			if(TCL_OPEN_AIR[i]==0)   
				delay_us(300);   //0.56ms 620
			else  
				delay_us(1000); //1.69ms 

			TIM_Cmd(TIM4, ENABLE); 
		}
		delay_us(560); 
		TIM_Cmd(TIM4, DISABLE); 	
}
/*******************************************************************************
* �� �� ��         : CLOSE_TCL_AIR
* ��������		     : ���յ� 
* ��    ��         : ��
* ��    ��         : ��
*******************************************************************************/
void CLOSE_TCL_AIR(void)		
{
		uint8_t i; 
	
		Sys_Status.LED1 = 1;
	
		TIM_Cmd(TIM4, ENABLE); 
		delay_us(3000); 
		TIM_Cmd(TIM4, DISABLE); 
		delay_us(2500);
		TIM_Cmd(TIM4, ENABLE); 	
		
		for(i=0; i<sizeof(TCL_CLOSE_AIR); i++) 
		{ 
			delay_us(565);//480
			TIM_Cmd(TIM4, DISABLE); 
			
			if(TCL_CLOSE_AIR[i]==0)   
				delay_us(300);   //0.56ms 620
			else  
				delay_us(1000); //1.69ms 

			TIM_Cmd(TIM4, ENABLE); 
		}
		delay_us(560); 
		TIM_Cmd(TIM4, DISABLE); 	
	
}
