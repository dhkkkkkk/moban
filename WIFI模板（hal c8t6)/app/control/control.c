#include "control.h"
/**************************************************************************
�������ܣ����еĿ��ƴ��붼��������
          TIM1���ƵĶ�ʱ�ж� 
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
	 if(++Flag_Velocity>1)	//���ø���Ƶ��10ms
	{
	 Flag_Velocity=1;
	  i=0;
		 ////////////////////////////////
	 chassis_vector_to_mecanum_wheel_speed(1.0,1.0,0.0,wh_speed);
		//////////////////////////////////
		if(Flag_Stop==1)  //����1    �˶�ģʽ
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
			else if (Flag_Stop==2)                       //����2 ֹͣģʽ
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
			else if (Flag_Stop==0) Set_Pwm(0);           //��ʼ ����ģʽ
	 }				      			 
}
}	

/**************************************************************************
�������ܣ�����PWM��ֵ 
��ڲ�������
����  ֵ����
**************************************************************************/
void Xianfu_Pwm(int moto)
{	
		int Amplitude=7100;    //===PWM������7200 ������7100
	  if(moto<-Amplitude) moto=-Amplitude;	
		if(moto>Amplitude)  moto=Amplitude;		
}

/**************************************************************************
�������ܣ�ȡ����ֵ
��ڲ�����int
����  ֵ��unsigned int
**************************************************************************/
int myabs(int a)
{ 		   
	  int temp;
		if(a<0)  temp=-a;  
	  else temp=a;
	  return temp;
}

/**************************************************************************
�������ܣ�����PI������
��ڲ���������������ֵ��Ŀ���ٶ�
����  ֵ�����PWM
��������ʽ��ɢPID��ʽ 
pwm+=Kp[e��k��-e(k-1)]+Ki*e(k)+Kd[e(k)-2e(k-1)+e(k-2)]
e(k)������ƫ�� 
e(k-1)������һ�ε�ƫ��  �Դ����� 
pwm�����������
�����ǵ��ٶȿ��Ʊջ�ϵͳ���棬ֻʹ��PI����
pwm+=Kp[e��k��-e(k-1)]+Ki*e(k)
**************************************************************************/
int Incremental_PI (int encoder,int Target)
{ 	
	 static float Bias,Pwm,Last_bias;
	 Bias=0.1*(encoder-Target);                                  //����ƫ��
	 Pwm+=Velocity_KP*(Bias-Last_bias)+Velocity_KI*Bias;   //����ʽPI������
	 Last_bias=Bias;	                                     //������һ��ƫ�� 
	 return Pwm;                                           //�������
}
	
/**************************************************************************
�������ܣ�λ��ʽPID������
��ڲ���������������λ����Ϣ��Ŀ��λ��
����  ֵ�����PWM
����λ��ʽ��ɢPID��ʽ 
pwm=Kp*e(k)+Ki*��e(k)+Kd[e��k��-e(k-1)]
e(k)������ƫ�� 
e(k-1)������һ�ε�ƫ��  
��e(k)����e(k)�Լ�֮ǰ��ƫ����ۻ���;����kΪ1,2,,k;
pwm�������
**************************************************************************/
int Position_PID (int encoder,int Target)
{ 	
	  float Bias,Pwm,Integral_bias,Last_Bias;
	 Bias=encoder-Target;                                  //����ƫ��
	 Integral_bias+=Bias;	                                 //���ƫ��Ļ���
	 Pwm=Position_KP*Bias+Position_KI*Integral_bias+Position_KD*(Bias-Last_Bias);       //λ��ʽPID������
	 Last_Bias=Bias;                                       //������һ��ƫ�� 
	 return Pwm;                                           //�������
}

/**************************************************************************
�������ܣ���ֵ��PWM�Ĵ���
��ڲ�����PWM
����  ֵ����
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

void forwards(void)    //ǰ������
{
	//ǰ1��ʱ��
  HAL_GPIO_WritePin(AN2_GPIO_Port,AN2_Pin,SET);
	HAL_GPIO_WritePin(AN1_GPIO_Port,AN1_Pin,RESET);
	//ǰ2˳ʱ��
	HAL_GPIO_WritePin(AN4_GPIO_Port,AN4_Pin,RESET);
	HAL_GPIO_WritePin(AN3_GPIO_Port,AN4_Pin,SET);
	//��1��ʱ��
	HAL_GPIO_WritePin(BN2_GPIO_Port,BN2_Pin,SET);
	HAL_GPIO_WritePin(BN1_GPIO_Port,BN1_Pin,RESET);
	//��2˳ʱ��
	HAL_GPIO_WritePin(BN4_GPIO_Port,BN4_Pin,RESET);
	HAL_GPIO_WritePin(BN3_GPIO_Port,BN3_Pin,SET);
  //
}
void backwards(void)
{
  //ǰ1˳ʱ��
  HAL_GPIO_WritePin(AN2_GPIO_Port,AN2_Pin,RESET);
	HAL_GPIO_WritePin(AN1_GPIO_Port,AN1_Pin,SET);
	//ǰ2��ʱ��
	HAL_GPIO_WritePin(AN4_GPIO_Port,AN4_Pin,SET);
	HAL_GPIO_WritePin(AN3_GPIO_Port,AN4_Pin,RESET);
	//��1˳ʱ��
	HAL_GPIO_WritePin(BN2_GPIO_Port,BN2_Pin,RESET);
	HAL_GPIO_WritePin(BN1_GPIO_Port,BN1_Pin,SET);
	//��2��ʱ��
	HAL_GPIO_WritePin(BN4_GPIO_Port,BN4_Pin,SET);
	HAL_GPIO_WritePin(BN3_GPIO_Port,BN3_Pin,RESET);
  //
}
//�������仯ֵת�����ٶȺ��� r=30mm
void EtoV(int delta_ECD)
{
 V=( 30.0f*(float)delta_ECD*PI)/(10.0f*20.0f*180.0f);
}


/*------------------------------------------------------*/	
/*                     �����ķ���ٶȷֽ�                */	
/*------------------------------------------------------*/
void chassis_vector_to_mecanum_wheel_speed(const float vx_set, const float vy_set, const float wz_set, float wheel_speed[4])
{
    //��ת��ʱ�� ������̨��ǰ��������ǰ������ 0 ��1 ��ת���ٶȱ����� �������� 2,3 ��ת���ٶȱ��
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
