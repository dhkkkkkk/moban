/*-------------------------------------------------*/
/*             ��γ����STM32ϵ�п�����              */
/*    �Ա���ַ�� http://chaoweidianzi.taobao.com   */
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*                   LEDͷ�ļ�                     */
/*-------------------------------------------------*/
#ifndef __LED_H
#define __LED_H

#include "main.h"   

#define   ON				0
#define 	OFF				1

#define  LED_D1    PBout(5)	   		// PD12����D1
#define  LED_D2    PBout(0)	   		// PD13����D2
#define  LED_D3    PBout(1)       	// PD14����D3


void LED_Init(void);               //��ʼ��	
void LED_AllOn(void);              //��������LED
void LED_AllOff(void);             //Ϩ������LED

#endif
