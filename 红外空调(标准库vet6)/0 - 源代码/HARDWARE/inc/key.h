/*-------------------------------------------------*/
/*            超纬电子STM32F系列开发板              */
/*    淘宝地址： http://chaoweidianzi.taobao.com   */
/*-------------------------------------------------*/
#ifndef __KEY_H
#define __KEY_H	

#include "main.h" 

 
//读取按键状态
#define KEY1			PAin(0) 
#define KEY2 			PCin(13)
//#define KEY3 			PEin(12) 
//#define KEY4 	    PDin(7) 

//按键值
#define NONE_PRES_NUM 	 0
#define KEY1_PRES_NUM 	 1
#define KEY2_PRES_NUM	 	 2
#define KEY3_PRES_NUM	   3
#define KEY4_PRES_NUM    4

void KEY_Init(void);	//按键初始化
u8 KEY_Scan(u8 mode);   //按键处理函数	

#endif
