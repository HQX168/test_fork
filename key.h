#ifndef _KEY_H
#define _KEY_H

#include "config.h"

sbit k1=P1^2;//�޸�ģʽ
sbit k2=P1^3;//��
sbit k3=P1^4;//��

void Delay10ms();
unsigned char Key_Scan();



#endif