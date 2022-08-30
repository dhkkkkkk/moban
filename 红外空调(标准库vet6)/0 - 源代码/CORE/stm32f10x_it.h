/*-------------------------------------------------*/
/*            超纬电子STM32系列开发板               */
/*    淘宝地址： http://chaoweidianzi.taobao.com   */
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*                                                 */
/*    中断处理头文件模板文件(ST提供,略做修改)        */
/*                                                 */
/*-------------------------------------------------*/
/*-------------------------------------------------*/

#ifndef __STM32F10x_IT_H
#define __STM32F10x_IT_H

#include "stm32f10x.h"

/*-------------------------------------------------*/
/*                                                 */
/*                    系统中断                     */
/*                                                 */
/*-------------------------------------------------*/

void NMI_Handler(void);
void HardFault_Handler(void);
void MemManage_Handler(void);
void BusFault_Handler(void);
void UsageFault_Handler(void);
void SVC_Handler(void);
void DebugMon_Handler(void);
void PendSV_Handler(void);
void SysTick_Handler(void);


/*-------------------------------------------------*/
/*                                                 */
/*                    应用中断                     */
/*                                                 */
/*-------------------------------------------------*/

void USART2_IRQHandler(void);

#endif 
