/*-------------------------------------------------*/
/*            ��γ����STM32Fϵ�п�����              */
/*    �Ա���ַ�� http://chaoweidianzi.taobao.com   */
/*-------------------------------------------------*/
#ifndef __KEY_H
#define __KEY_H	

#include "main.h" 

 
//��ȡ����״̬
#define KEY1			PAin(0) 
#define KEY2 			PCin(13)
//#define KEY3 			PEin(12) 
//#define KEY4 	    PDin(7) 

//����ֵ
#define NONE_PRES_NUM 	 0
#define KEY1_PRES_NUM 	 1
#define KEY2_PRES_NUM	 	 2
#define KEY3_PRES_NUM	   3
#define KEY4_PRES_NUM    4

void KEY_Init(void);	//������ʼ��
u8 KEY_Scan(u8 mode);   //����������	

#endif
