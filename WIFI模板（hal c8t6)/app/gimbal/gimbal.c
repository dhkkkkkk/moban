//#include "main.h"
#include "tim.h"
#include "gpio.h"
#include "gimbal.h"


void jinmo_motor(int direction)
{
	if(direction==1)
	{
		HAL_GPIO_WritePin(AN1_GPIO_Port,AN1_Pin,GPIO_PIN_SET);
		HAL_GPIO_WritePin(AN2_GPIO_Port,AN2_Pin,GPIO_PIN_RESET);
	}
	else if (direction==-1)
	{
		HAL_GPIO_WritePin(AN1_GPIO_Port,AN1_Pin,GPIO_PIN_RESET);
		HAL_GPIO_WritePin(AN2_GPIO_Port,AN2_Pin,GPIO_PIN_SET);
	}
	else if(direction==0)
  { 
		HAL_GPIO_WritePin(AN1_GPIO_Port,AN1_Pin,GPIO_PIN_RESET);
		HAL_GPIO_WritePin(AN2_GPIO_Port,AN2_Pin,GPIO_PIN_RESET);
	}
}

void jiguang_motor(int direction)
{
	if(direction==1)
	{
		HAL_GPIO_WritePin(BN1_GPIO_Port,BN1_Pin,GPIO_PIN_SET);
		HAL_GPIO_WritePin(BN2_GPIO_Port,BN2_Pin,GPIO_PIN_RESET);
	}
	else if (direction==-1)
	{
		HAL_GPIO_WritePin(BN1_GPIO_Port,BN1_Pin,GPIO_PIN_RESET);
		HAL_GPIO_WritePin(BN2_GPIO_Port,BN2_Pin,GPIO_PIN_SET);
	}
	else if(direction==0)
  { 
		HAL_GPIO_WritePin(BN1_GPIO_Port,BN1_Pin,GPIO_PIN_RESET);
		HAL_GPIO_WritePin(BN2_GPIO_Port,BN2_Pin,GPIO_PIN_RESET);
	}
}

void chuansongdai_motor(int direction)
{
	if(direction==1)
	{
		HAL_GPIO_WritePin(CN1_GPIO_Port,CN1_Pin,GPIO_PIN_SET);
		HAL_GPIO_WritePin(CN2_GPIO_Port,CN2_Pin,GPIO_PIN_RESET);
	}
	else if (direction==-1)
	{
		HAL_GPIO_WritePin(CN1_GPIO_Port,CN1_Pin,GPIO_PIN_RESET);
		HAL_GPIO_WritePin(CN2_GPIO_Port,CN2_Pin,GPIO_PIN_SET);
	}
	else if(direction==0)
  { 
		HAL_GPIO_WritePin(CN1_GPIO_Port,CN1_Pin,GPIO_PIN_RESET);
		HAL_GPIO_WritePin(CN2_GPIO_Port,CN2_Pin,GPIO_PIN_RESET);
	}
}

void fengkou_motor(int direction)
{
	if(direction==1)
	{
		HAL_GPIO_WritePin(DN1_GPIO_Port,DN1_Pin,GPIO_PIN_SET);
		HAL_GPIO_WritePin(DN2_GPIO_Port,DN2_Pin,GPIO_PIN_RESET);
	}
	else if (direction==-1)
	{
		HAL_GPIO_WritePin(DN1_GPIO_Port,DN1_Pin,GPIO_PIN_RESET);
		HAL_GPIO_WritePin(DN2_GPIO_Port,DN2_Pin,GPIO_PIN_SET);
	}
	else if(direction==0)
  { 
		HAL_GPIO_WritePin(DN1_GPIO_Port,DN1_Pin,GPIO_PIN_RESET);
		HAL_GPIO_WritePin(DN2_GPIO_Port,DN2_Pin,GPIO_PIN_RESET);
	}
}

void tuigan_motor(int direction)
{
	if(direction==1)
	{
		HAL_GPIO_WritePin(TG1_GPIO_Port,TG1_Pin,GPIO_PIN_SET);
		HAL_GPIO_WritePin(TG2_GPIO_Port,TG2_Pin,GPIO_PIN_RESET);
	}
	else if (direction==-1)
	{
		HAL_GPIO_WritePin(TG1_GPIO_Port,TG1_Pin,GPIO_PIN_RESET);
		HAL_GPIO_WritePin(TG2_GPIO_Port,TG2_Pin,GPIO_PIN_SET);
	}
	else if(direction==0)
  { 
		HAL_GPIO_WritePin(TG1_GPIO_Port,TG1_Pin,GPIO_PIN_RESET);
		HAL_GPIO_WritePin(TG2_GPIO_Port,TG2_Pin,GPIO_PIN_RESET);
	}


}
void gimbal_STOP(void)
{
	jinmo_motor(0);
	jiguang_motor(0);
	chuansongdai_motor(0);
	fengkou_motor(0);
	tuigan_motor(0);
	HAL_TIM_PWM_Stop(&htim2,TIM_CHANNEL_1);
	HAL_TIM_PWM_Stop(&htim1,TIM_CHANNEL_1);
}


int DJ_val(int angle)  //小舵机70-110   大舵机不能超80
{
	if(angle<180)
	{
		int pwmval=180+angle*4;
		return pwmval;
	}
  else return 0;

}
