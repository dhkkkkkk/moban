/*-------------------------------------------------*/
/*              超纬电子STM32系列开发板             */
/*    淘宝地址： http://chaoweidianzi.taobao.com   */
/*-------------------------------------------------*/
#ifndef __BUZZER_H
#define __BUZZER_H

#include "main.h"   


#define  BUZZE         PBout(14)	        // PB14控制蜂鸣器

void Buzzer_Init(void);

#endif
