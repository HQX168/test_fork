#ifndef _dht11_H
#define _dht11_H

#include "delay.h"

//�ܽŶ���
sbit DHT11_DQ=P0^0;

//��������
void Delay30us();
void Delay10us();
void dht11_gpio_OUT();
u8 DHT11_Init(void);//DHT11��ʼ�� 
void DHT11_Rst(void);//��λDHT11
u8 DHT11_Check(void);//�ȴ�DHT11�Ļ�Ӧ
u8 DHT11_Read_Byte(void);//��DHT11��ȡһ���ֽ�
u8 DHT11_Read_Data(u8 *temp,u8 *humi);//��DHT11��ȡһ������

#endif