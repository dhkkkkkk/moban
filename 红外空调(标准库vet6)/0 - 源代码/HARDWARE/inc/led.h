/*-------------------------------------------------*/
/*             超纬电子STM32系列开发板              */
/*    淘宝地址： http://chaoweidianzi.taobao.com   */
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*                   LED头文件                     */
/*-------------------------------------------------*/
#ifndef __LED_H
#define __LED_H

#include "main.h"   

#define   ON				0
#define 	OFF				1

#define  LED_D1    PBout(5)	   		// PD12控制D1
#define  LED_D2    PBout(0)	   		// PD13控制D2
#define  LED_D3    PBout(1)       	// PD14控制D3


void LED_Init(void);               //初始化	
void LED_AllOn(void);              //点亮所有LED
void LED_AllOff(void);             //熄灭所有LED

#endif
