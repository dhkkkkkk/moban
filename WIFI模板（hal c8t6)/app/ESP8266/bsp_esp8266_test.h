#ifndef  __TEST_H
#define	 __TEST_H


/********************************** 用户需要设置的参数**********************************/

#define   macUser_ESP8266_ApSsid              "embedfire2"         //要连接的热点的名称
#define   macUser_ESP8266_ApPwd               "wildfire"           //要连接的热点的密钥

#define   macUser_ESP8266_BulitApSsid         "dhk"      //要建立的热点的名称
#define   macUser_ESP8266_BulitApEcn           OPEN               //要建立的热点的加密方式
#define   macUser_ESP8266_BulitApPwd           "wildfire"         //要建立的热点的密钥



#define   macUser_ESP8266_TcpServer_IP         "192.168.0.45"      //服务器开启的IP地址
#define   macUser_ESP8266_TcpServer_Port       "8080"             //服务器开启的端口   

#define   macUser_ESP8266_TcpServer_OverTime   "1800"             //服务器超时时间（单位：秒）

 void ESP8266_ApTcpServer_ConfigTest(void);
 void ESP8266_CheckRecv_SendDataTest(void);
#endif