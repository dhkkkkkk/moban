#ifndef  __TEST_H
#define	 __TEST_H


/********************************** �û���Ҫ���õĲ���**********************************/

#define   macUser_ESP8266_ApSsid              "embedfire2"         //Ҫ���ӵ��ȵ������
#define   macUser_ESP8266_ApPwd               "wildfire"           //Ҫ���ӵ��ȵ����Կ

#define   macUser_ESP8266_BulitApSsid         "dhk"      //Ҫ�������ȵ������
#define   macUser_ESP8266_BulitApEcn           OPEN               //Ҫ�������ȵ�ļ��ܷ�ʽ
#define   macUser_ESP8266_BulitApPwd           "wildfire"         //Ҫ�������ȵ����Կ



#define   macUser_ESP8266_TcpServer_IP         "192.168.0.45"      //������������IP��ַ
#define   macUser_ESP8266_TcpServer_Port       "8080"             //�����������Ķ˿�   

#define   macUser_ESP8266_TcpServer_OverTime   "1800"             //��������ʱʱ�䣨��λ���룩

 void ESP8266_ApTcpServer_ConfigTest(void);
 void ESP8266_CheckRecv_SendDataTest(void);
#endif