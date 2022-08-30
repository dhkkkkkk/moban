#include "control.h"
/**************************************************************************
函数功能：所有的控制代码都在这里面
          TIM1控制的定时中断 
**************************************************************************/
u8 Flag_Velocity=1;
int a;
static pid_type_def moto_pid_0;
const float pid0[3] = {KP,KI,KD};
int Amplitude=7100; 
float wh_speed[4]={0.0f,0.0f,0.0f,0.0f};
int error1=0,delta_ecd=0;
int i;
float V;
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
if (htim == (&htim1))
{
	 if(++Flag_Velocity>1)	//设置更新频率10ms
	{
	 Flag_Velocity=1;
	  i=0;
		 ////////////////////////////////
	 chassis_vector_to_mecanum_wheel_speed(1.0,1.0,0.0,wh_speed);
		//////////////////////////////////
		if(Flag_Stop==1)  //按键1    运动模式
		 {
			HAL_GPIO_TogglePin(led2_GPIO_Port,led2_Pin);
			HAL_Delay(100);
			for(i=0;i<=0;i++)
			 {	 
				Encoder[i]=Read_Velocity(i); 
				if(Encoder[i]<-5) Encoder[i]=-5;   //-50
				 
				 ///////////////////////////////////
				 if(Encoder[1]<100) delta_ecd=0,error1=0;
				 delta_ecd=Encoder[1]-error1;
				 error1= Encoder[1];
				 EtoV(delta_ecd);
				 PID_calc(&moto_pid_0,V,0.5f);
				 ////////////////////////////////////
				 //********************************//
				 ////////////////////////////////////
				//PID_calc(&moto_pid_0,Encoder[0],Target_Position);
				 ////////////////////////////////////
				Moto[i]=moto_pid_0.out;
				Xianfu_Pwm(Moto[i]);
				Set_Pwm(Moto[i]);		
			  }
			}
			else if (Flag_Stop==2)                       //按键2 停止模式
			{
			  for(i=0;i<3;i++)
					{
					 Encoder[i]=Read_Velocity(i); 
					 PID_calc(&moto_pid_0,Encoder[0],stop_encoder[0]);
					 Moto[i]=moto_pid_0.out;
					 Xianfu_Pwm(Moto[i]);
					 Set_Pwm(Moto[i]);	 
					 }
			}
			else if (Flag_Stop==0) Set_Pwm(0);           //初始 无力模式
	 }				      			 
}
}	

/**************************************************************************
函数功能：限制PWM赋值 
入口参数：无
返回  值：无
**************************************************************************/
void Xianfu_Pwm(int moto)
{	
		int Amplitude=7100;    //===PWM满幅是7200 限制在7100
	  if(moto<-Amplitude) moto=-Amplitude;	
		if(moto>Amplitude)  moto=Amplitude;		
}

/**************************************************************************
函数功能：取绝对值
入口参数：int
返回  值：unsigned int
**************************************************************************/
int myabs(int a)
{ 		   
	  int temp;
		if(a<0)  temp=-a;  
	  else temp=a;
	  return temp;
}

/**************************************************************************
函数功能：增量PI控制器
入口参数：编码器测量值，目标速度
返回  值：电机PWM
根据增量式离散PID公式 
pwm+=Kp[e（k）-e(k-1)]+Ki*e(k)+Kd[e(k)-2e(k-1)+e(k-2)]
e(k)代表本次偏差 
e(k-1)代表上一次的偏差  以此类推 
pwm代表增量输出
在我们的速度控制闭环系统里面，只使用PI控制
pwm+=Kp[e（k）-e(k-1)]+Ki*e(k)
**************************************************************************/
int Incremental_PI (int encoder,int Target)
{ 	
	 static float Bias,Pwm,Last_bias;
	 Bias=0.1*(encoder-Target);                                  //计算偏差
	 Pwm+=Velocity_KP*(Bias-Last_bias)+Velocity_KI*Bias;   //增量式PI控制器
	 Last_bias=Bias;	                                     //保存上一次偏差 
	 return Pwm;                                           //增量输出
}
	
/**************************************************************************
函数功能：位置式PID控制器
入口参数：编码器测量位置信息，目标位置
返回  值：电机PWM
根据位置式离散PID公式 
pwm=Kp*e(k)+Ki*∑e(k)+Kd[e（k）-e(k-1)]
e(k)代表本次偏差 
e(k-1)代表上一次的偏差  
∑e(k)代表e(k)以及之前的偏差的累积和;其中k为1,2,,k;
pwm代表输出
**************************************************************************/
int Position_PID (int encoder,int Target)
{ 	
	  float Bias,Pwm,Integral_bias,Last_Bias;
	 Bias=encoder-Target;                                  //计算偏差
	 Integral_bias+=Bias;	                                 //求出偏差的积分
	 Pwm=Position_KP*Bias+Position_KI*Integral_bias+Position_KD*(Bias-Last_Bias);       //位置式PID控制器
	 Last_Bias=Bias;                                       //保存上一次偏差 
	 return Pwm;                                           //增量输出
}

/**************************************************************************
函数功能：赋值给PWM寄存器
入口参数：PWM
返回  值：无
**************************************************************************/
void Set_Pwm(int moto)
{
	int PWM1,PWM2,PWM3,PWM4;
    	if(moto<0)			
			{
//				HAL_GPIO_WritePin(AN2_GPIO_Port,AN2_Pin,SET);
//				HAL_GPIO_WritePin(AN1_GPIO_Port,AN1_Pin,RESET);
				backwards();
			}
			else if (moto>0)
			{	
//				HAL_GPIO_WritePin(AN2_GPIO_Port,AN2_Pin,RESET);
//				HAL_GPIO_WritePin(AN1_GPIO_Port,AN1_Pin,SET);
				forwards();
			}
			PWM1=myabs(moto);
			PWM2=myabs(moto);
			PWM3=myabs(moto);
			PWM4=myabs(moto);
			__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1,PWM1);
			__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2,PWM2);
			__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3,PWM3);
			__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4,PWM4);
}		 
void pid_init(void)
{
PID_Init(&moto_pid_0,PID_POSITION,pid0,7100.0,5000.0);
}	

void forwards(void)    //前进函数
{
	//前1逆时针
  HAL_GPIO_WritePin(AN2_GPIO_Port,AN2_Pin,SET);
	HAL_GPIO_WritePin(AN1_GPIO_Port,AN1_Pin,RESET);
	//前2顺时针
	HAL_GPIO_WritePin(AN4_GPIO_Port,AN4_Pin,RESET);
	HAL_GPIO_WritePin(AN3_GPIO_Port,AN4_Pin,SET);
	//后1逆时针
	HAL_GPIO_WritePin(BN2_GPIO_Port,BN2_Pin,SET);
	HAL_GPIO_WritePin(BN1_GPIO_Port,BN1_Pin,RESET);
	//后2顺时针
	HAL_GPIO_WritePin(BN4_GPIO_Port,BN4_Pin,RESET);
	HAL_GPIO_WritePin(BN3_GPIO_Port,BN3_Pin,SET);
  //
}
void backwards(void)
{
  //前1顺时针
  HAL_GPIO_WritePin(AN2_GPIO_Port,AN2_Pin,RESET);
	HAL_GPIO_WritePin(AN1_GPIO_Port,AN1_Pin,SET);
	//前2逆时针
	HAL_GPIO_WritePin(AN4_GPIO_Port,AN4_Pin,SET);
	HAL_GPIO_WritePin(AN3_GPIO_Port,AN4_Pin,RESET);
	//后1顺时针
	HAL_GPIO_WritePin(BN2_GPIO_Port,BN2_Pin,RESET);
	HAL_GPIO_WritePin(BN1_GPIO_Port,BN1_Pin,SET);
	//后2逆时针
	HAL_GPIO_WritePin(BN4_GPIO_Port,BN4_Pin,SET);
	HAL_GPIO_WritePin(BN3_GPIO_Port,BN3_Pin,RESET);
  //
}
//编码器变化值转轮线速度函数 r=30mm
void EtoV(int delta_ECD)
{
 V=( 30.0f*(float)delta_ECD*PI)/(10.0f*20.0f*180.0f);
}


/*------------------------------------------------------*/	
/*                     麦克纳姆轮速度分解                */	
/*------------------------------------------------------*/
void chassis_vector_to_mecanum_wheel_speed(const float vx_set, const float vy_set, const float wz_set, float wheel_speed[4])
{
    //旋转的时候， 由于云台靠前，所以是前面两轮 0 ，1 旋转的速度变慢， 后面两轮 2,3 旋转的速度变快
//    wheel_speed[0] = -vx_set - vy_set + ( - 1.0f) * 0.0246785f * MOTOR_DISTANCE_TO_CENTER * wz_set;
//    wheel_speed[1] =  vx_set - vy_set + ( - 1.0f) * 0.0246785f * MOTOR_DISTANCE_TO_CENTER * wz_set;
//    wheel_speed[2] =  vx_set + vy_set + ( - 1.0f) * 0.0246785f * MOTOR_DISTANCE_TO_CENTER * wz_set;
//    wheel_speed[3] = -vx_set + vy_set + ( - 1.0f) * 0.0246785f * MOTOR_DISTANCE_TO_CENTER * wz_set;
	//0      1
	//2      3
	  wheel_speed[0] = -vx_set - vy_set ;
    wheel_speed[1] =  vx_set + vy_set ;
    wheel_speed[2] =  vx_set - vy_set ;
    wheel_speed[3] = -vx_set + vy_set ;
	
	
}
