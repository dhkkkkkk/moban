#include "bsp_esp8266_test.h"
#include "bsp_esp8266.h"
#include <stdio.h>  
#include <string.h>  
#include <stdbool.h>
#include "stm32f1xx_hal.h"
#include "chassis.h"
#include "gimbal.h"
#include "tim.h"
#include "main.h"
// ���Ժ�����ȫ�ֱ���
uint8_t ucId, ucLen;
uint8_t ucLed1Status = 0, ucLed2Status = 0, ucLed3Status = 0, ucBuzzerStatus = 0;
char cStr [ 100 ] = { 0 }, cCh;
char * pCh, * pCh1;

/**
  * @brief  ESP8266 ApTcpServer ���ò��Ժ���
  * @param  ��
  * @retval ��
  */
void ESP8266_ApTcpServer_ConfigTest(void)
{  
 
	macESP8266_CH_ENABLE();
	while( ! ESP8266_AT_Test() );
	while( ! ESP8266_Net_Mode_Choose ( AP ) ){};
  while ( ! ESP8266_CIPAP ( macUser_ESP8266_TcpServer_IP ) ); //����ģ��� AP IP
  while ( ! ESP8266_BuildAP ( macUser_ESP8266_BulitApSsid, macUser_ESP8266_BulitApPwd, macUser_ESP8266_BulitApEcn ) );
	while( ! ESP8266_Enable_MultipleId ( ENABLE ) );
	while ( !	ESP8266_StartOrShutServer ( ENABLE, macUser_ESP8266_TcpServer_Port, macUser_ESP8266_TcpServer_OverTime ) ){};
  ESP8266_Inquire_ApIp ( cStr, 20 );
	strEsp8266_Fram_Record .InfBit .FramLength = 0;
	strEsp8266_Fram_Record.InfBit.FramFinishFlag=0;
	
  
}

/**
  * @brief  ESP8266 ��������Ϣ���������ݲ��Ժ���
  * @param  ��
  * @retval ��
  */

void ESP8266_CheckRecv_SendDataTest(void)
{
  
  if ( strEsp8266_Fram_Record .InfBit .FramFinishFlag )
  {
//    USART_ITConfig ( macESP8266_USARTx, USART_IT_RXNE, DISABLE ); //���ô��ڽ����ж�  
		__HAL_UART_DISABLE_IT(&huart3, UART_IT_IDLE);
    strEsp8266_Fram_Record .Data_RX_BUF [ strEsp8266_Fram_Record .InfBit .FramLength ]  = '\0';
    if ( ( pCh = strstr ( strEsp8266_Fram_Record .Data_RX_BUF, "MOVE_" ) ) != 0 )    //���̿���  ֱ�Ӹ���Ϊ*******?*?
    {
      cCh = * ( pCh + 5 );  //��ַ+5λ����ӦMOVE_?
      switch ( cCh )  //�ڰ�λ
      {
        case 'Q':
          cCh = * ( pCh + 7 );  //��ַ+7λ����ӦMOVE_*_?
          switch ( cCh )  //��7λ
          {
            case '0':
						move_stop();
              ucLed1Status = 0;
              break;
            case '1':
						move_straight();
              ucLed1Status = 1;
              break;
            default :
              break;
          }
          break;
          
        case 'H':
          cCh = * ( pCh + 7 );  //��ַ+7λ����ӦMOVE_*_?
          switch ( cCh )  //��7λ
          {
            case '0':
							move_stop();
              ucLed1Status = 0;
              break;
            case '1':
							move_back();
              ucLed1Status = 1;
              break;
            default :
              break;
          }
          break;
					
        case 'Z':
          cCh = * ( pCh + 7 );  //��ַ+7λ����ӦMOVE_*_?
          switch ( cCh )  //��7λ
          {
            case '0':
							move_stop();
              ucLed1Status = 0;
              break;
            case '1':
							move_left();
              ucLed1Status = 1;
              break;
            default :
              break;
          }
          break;
					
        case 'Y':
          cCh = * ( pCh + 7 );  //��ַ+7λ����ӦMOVE_*_?
          switch ( cCh )  //��7λ
          {
            case '0':
							move_stop();
              ucLed1Status = 0;
              break;
            case '1':
							move_right();
              ucLed1Status = 1;
              break;
            default :
              break;
          }
          break;


					case 'S':
          cCh = * ( pCh + 7 );  //��ַ+7λ����ӦMOVE_*_?
          switch ( cCh )  //��7λ
          {
            case '0':
							move_stop();
              ucLed1Status = 0;
              break;
            case '1':
							move_stop();
              ucLed1Status = 1;
              break;
            default :
              break;
          }
          break;
        default :
					break;						
      }
      
      sprintf ( cStr, "CMD_LED_%d_%d_%d_ENDLED_END", ucLed1Status, ucLed2Status, ucLed3Status );
      
    }
    
    else if ( ( pCh = strstr ( strEsp8266_Fram_Record .Data_RX_BUF, "GIMBAL_" ) ) != 0 )  //��̨����
    {
      cCh = * ( pCh + 7 );  // Mo,Jiguang,Chuansongdai,Fengkou,DuoJi1/2
      
      switch ( cCh )
      {
				case 'T':   //�Ƹ�  ��Ҫ����
					cCh = * ( pCh + 9 );  //GIMBAL_M_?
				//HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_1);
				  switch ( cCh )
					{
						case '0':
						tuigan_motor(-1);
//						HAL_Delay(8000);  
//						tuigan_motor(0);
						break;
						case '1':
						tuigan_motor(1);
//						HAL_Delay(8000);  
//						tuigan_motor(0);
						break;
						default :
						break;
					}
					break;
        case 'M':  //��Ĥ  ����Ҫ����
					cCh = * ( pCh + 9 );  //GIMBAL_M_?
				  switch ( cCh )
					{
						case '0':
//						jinmo_motor(1);
//						HAL_Delay(3000);  
						jinmo_motor(0);
						ucBuzzerStatus = 0;
						break;
						case '1':
						jinmo_motor(1);
						ucBuzzerStatus = 0;
//						HAL_Delay(15000);  
//						jinmo_motor(0);
						break;
						default :
						break;
					}
					break;
        case 'J':  //��������  ��Ҫ����
					cCh = * ( pCh + 9 );  //GIMBAL_J_?
				  switch ( cCh )
					{
						case '1':
							pwm_signal=!0;
						__HAL_TIM_SetCompare(&htim1,TIM_CHANNEL_1,99);
						jiguang_motor(1);
//						ucBuzzerStatus = 0;
//						HAL_Delay(12000);  //???????????????????
//						__HAL_TIM_SetCompare(&htim1,TIM_CHANNEL_1,0);
//						jiguang_motor(0);
						break;
						case '0':
							pwm_signal=0;
						__HAL_TIM_SetCompare(&htim1,TIM_CHANNEL_1,0);
						jiguang_motor(-1);
//						HAL_Delay(3000);  //???????????????????
//						jinmo_motor(0);
						ucBuzzerStatus = 0;
						break;
						default :
						break;
					}
					break;
				case 'C'://���ʹ�   ����Ҫ����
					cCh = * ( pCh + 9 );  //GIMBAL_C_?
				  switch ( cCh )
					{
						case '1':
						chuansongdai_motor(1);
//						HAL_Delay(10000);  //???????????????????
//						chuansongdai_motor(0);
						ucBuzzerStatus = 0;
						break;
						case '0':
						chuansongdai_motor(0);
						ucBuzzerStatus = 0;
						break;
						default :
						break;
					}
					break;
				case 'F':  //��� ��Ҫ����
					cCh = * ( pCh + 9 );  //GIMBAL_F_?
				  switch ( cCh )
					{
						case '1':
						fengkou_motor(1);
						HAL_Delay(10000);  //???????????????????
						fengkou_motor(0);
						ucBuzzerStatus = 0;
						break;
						case '0':
						fengkou_motor(-1);
						HAL_Delay(10000);  //???????????????????
						fengkou_motor(0);
						ucBuzzerStatus = 0;
						break;
						default :
						break;
					}
					break;
				case 'S':  //ȫ�弱ͣ
					cCh = * ( pCh + 9 );  //GIMBAL_S_?
				  switch ( cCh )
					{
						case '0':
						gimbal_STOP();
						ucBuzzerStatus = 0;
						break;
						case '1':
						gimbal_STOP();
						ucBuzzerStatus = 0;
						break;
						default :
						gimbal_STOP();	
						break;
					}
					break;
				case 'D':  //��ȡ���
					cCh = * ( pCh + 9 );  //GIMBAL_D_?
				  switch ( cCh )
					{
						case '1':
						HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_1);
						__HAL_TIM_SetCompare(&htim2,TIM_CHANNEL_1,DJ_val(80));
						break;
						case '0':
//						HAL_TIM_PWM_Stop(&htim2,TIM_CHANNEL_1);
						break;
						default :
						//
						break;
					}
					break;
				default:
          break;
      }
      
      sprintf ( cStr, "CMD_BUZZER_%d_ENDBUZZER_END", ucBuzzerStatus );
      
    }
      
    else if ( ( ( pCh  = strstr ( strEsp8266_Fram_Record .Data_RX_BUF, "CMD_UART_" ) ) != 0 ) && 
              ( ( pCh1 = strstr ( strEsp8266_Fram_Record .Data_RX_BUF, "_ENDUART_END" ) )  != 0 ) ) 
    {
      if ( pCh < pCh1)
      {
        ucLen = pCh1 - pCh + 12;
        memcpy ( cStr, pCh, ucLen );
        cStr [ ucLen ] = '\0';
      }
    }

    else if ( strstr ( strEsp8266_Fram_Record .Data_RX_BUF, "CMD_READ_ALL_END" ) != 0 )     //��ȡ״̬����
    {
//      DHT11_Read_TempAndHumidity ( & DHT11_Data );
//      sprintf ( cStr, "CMD_LED_%d_%d_%d_ENDLED_DHT11_%d.%d_%d.%d_ENDDHT11_BUZZER_%d_ENDBUZZER_END", 
//                ucLed1Status, ucLed2Status, ucLed3Status, DHT11_Data .temp_int, 
//                DHT11_Data .temp_deci, DHT11_Data .humi_int, DHT11_Data .humi_deci,
//                ucBuzzerStatus );
    }
    
      
    if ( ( pCh = strstr ( strEsp8266_Fram_Record .Data_RX_BUF, "+IPD," ) ) != 0 ) 
    {
      ucId = * ( pCh + strlen ( "+IPD," ) ) - '0';
      ESP8266_SendString ( DISABLE, cStr, strlen ( cStr ), ( ENUM_ID_NO_TypeDef ) ucId );
    }
    
    strEsp8266_Fram_Record .InfBit .FramLength = 0;
    strEsp8266_Fram_Record .InfBit .FramFinishFlag = 0;	
    
//    USART_ITConfig ( macESP8266_USARTx, USART_IT_RXNE, ENABLE ); //ʹ�ܴ��ڽ����ж�
		__HAL_UART_ENABLE_IT(&huart3, UART_IT_IDLE);
    
  }
  
}

