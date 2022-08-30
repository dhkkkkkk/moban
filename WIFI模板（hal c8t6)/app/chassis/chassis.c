#include "main.h"
#include "tim.h"
#include "gpio.h"
#include "chassis.h"

void front_left_move(int direction);
void rear_left_move(int direction);
void front_right_move(int direction);
void rear_right_move(int direction);

void move_straight()
{
  front_left_move(1);
	rear_left_move(1);
	front_right_move(-1);
	rear_right_move(-1);
}

void move_back()
{
	front_left_move(-1);
	rear_left_move(-1);
	front_right_move(1);
	rear_right_move(1);
}

void move_left()
{
	front_left_move(-1);
	rear_left_move(1);
	front_right_move(-1);
	rear_right_move(1);
}

void move_right()
{
	front_left_move(1);
	rear_left_move(-1);
	front_right_move(1);
	rear_right_move(-1);
}

void move_stop()
{
	front_left_move(0);
	rear_left_move(0);
	front_right_move(0);
	rear_right_move(0);
}


void front_left_move(int direction)  
{
	if(direction==1)
	{
		HAL_GPIO_WritePin(Chassis_A1_GPIO_Port,Chassis_A1_Pin,GPIO_PIN_SET);
		HAL_GPIO_WritePin(Chassis_A2_GPIO_Port,Chassis_A2_Pin,GPIO_PIN_RESET);
	}
	else if (direction==-1)
	{
		HAL_GPIO_WritePin(Chassis_A1_GPIO_Port,Chassis_A1_Pin,GPIO_PIN_RESET);
		HAL_GPIO_WritePin(Chassis_A2_GPIO_Port,Chassis_A2_Pin,GPIO_PIN_SET);
	}
	else if(direction==0)
  { 
		HAL_GPIO_WritePin(Chassis_A1_GPIO_Port,Chassis_A1_Pin,GPIO_PIN_RESET);
		HAL_GPIO_WritePin(Chassis_A2_GPIO_Port,Chassis_A2_Pin,GPIO_PIN_RESET);
	}
}

void rear_left_move(int direction)
{
	if(direction==1)
	{
		HAL_GPIO_WritePin(Chassis_C1_GPIO_Port,Chassis_C1_Pin,GPIO_PIN_SET);
		HAL_GPIO_WritePin(Chassis_C2_GPIO_Port,Chassis_C2_Pin,GPIO_PIN_RESET);
	}
	else if (direction==-1)
	{
		HAL_GPIO_WritePin(Chassis_C1_GPIO_Port,Chassis_C1_Pin,GPIO_PIN_RESET);
		HAL_GPIO_WritePin(Chassis_C2_GPIO_Port,Chassis_C2_Pin,GPIO_PIN_SET);
	}
	else if (direction==0)
	{
		HAL_GPIO_WritePin(Chassis_C1_GPIO_Port,Chassis_C1_Pin,GPIO_PIN_RESET);
		HAL_GPIO_WritePin(Chassis_C2_GPIO_Port,Chassis_C2_Pin,GPIO_PIN_RESET);
	}

}

void front_right_move(int direction)
{
	if(direction==1)
	{
		HAL_GPIO_WritePin(Chassis_B1_GPIO_Port,Chassis_B1_Pin,GPIO_PIN_SET);
		HAL_GPIO_WritePin(Chassis_B2_GPIO_Port,Chassis_B2_Pin,GPIO_PIN_RESET);
	}
	else if (direction==-1)
	{
		HAL_GPIO_WritePin(Chassis_B1_GPIO_Port,Chassis_B1_Pin,GPIO_PIN_RESET);
		HAL_GPIO_WritePin(Chassis_B2_GPIO_Port,Chassis_B2_Pin,GPIO_PIN_SET);
	}
	else if (direction==0)
	{
		HAL_GPIO_WritePin(Chassis_B1_GPIO_Port,Chassis_B1_Pin,GPIO_PIN_RESET);
		HAL_GPIO_WritePin(Chassis_B2_GPIO_Port,Chassis_B2_Pin,GPIO_PIN_RESET);
	}

}

void rear_right_move(int direction)
{
	if(direction==1)
	{
		HAL_GPIO_WritePin(Chassis_D1_GPIO_Port,Chassis_D1_Pin,GPIO_PIN_SET);
		HAL_GPIO_WritePin(Chassis_D2_GPIO_Port,Chassis_D2_Pin,GPIO_PIN_RESET);
	}
	else if (direction==-1)
	{
		HAL_GPIO_WritePin(Chassis_D1_GPIO_Port,Chassis_D1_Pin,GPIO_PIN_RESET);
		HAL_GPIO_WritePin(Chassis_D2_GPIO_Port,Chassis_D2_Pin,GPIO_PIN_SET);
	}
	else if (direction==0)
	{
		HAL_GPIO_WritePin(Chassis_D1_GPIO_Port,Chassis_D1_Pin,GPIO_PIN_RESET);
		HAL_GPIO_WritePin(Chassis_D2_GPIO_Port,Chassis_D2_Pin,GPIO_PIN_RESET);
	}

}


