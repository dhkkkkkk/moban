#ifndef __CONTROL_H
#define __CONTROL_H
  /**************************************************************************
作者：平衡小车之家
我的淘宝小店：http://shop114407458.taobao.com/
**************************************************************************/
#include "main.h"
#include "tim.h"
#include "gpio.h"
//#include "ecd.h"
//#include "pid.h"
#define PI 3.14159265
#define ZHONGZHI 3085
#define KP 0.1
#define KI 0.01
#define KD 0.01
//设置车身中心轮距
#define MOTOR_DISTANCE_TO_CENTER      0.373f
int motor_control(void);
int Incremental_PI (int Encoder,int Target);  //PI控制器
void Xianfu_Pwm(int moto);
int myabs(int a);
void Set_Pwm(int moto);
extern uint8_t Flag_Velocity;
int Position_PID (int Encoder,int Target);
extern const float pid[3];
void pid_init(void);
void forwards(void);
void backwards(void);
void chassis_vector_to_mecanum_wheel_speed(const float vx_set, const float vy_set, const float wz_set, float wheel_speed[4]);
void EtoV(int delta_ECD);

#endif