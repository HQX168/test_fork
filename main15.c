#include "config.h"
#include "oled.h"
#include "onewire.h"
#include "smoke.h"
#include <uart.h>
#include "STC_BH1750.h"

#include "GPIO.h"
#include "dht11.h"



sbit fan = P0^3;
sbit bell = P2^6;
sbit bump = P0^2;
//sbit smoke = P0^1;
sbit k11=P1^2;//�޸�ģʽ
sbit k21=P1^3;//��
sbit k31=P1^4;//��



void fFan(int i);
void fBell(int i);
void fBump(int i);
unsigned int read_temp();
void DS18B20_Init();
u8 temp,humi;//�¶�ʪ�ȱ���
int max[3] = {15,0,1};
unsigned int count=0;
int flags1=0;//�޸�ģʽ0���޸ģ�1�޸�
bit flags2=0;//��flag
bit flags3=0;//��flag
bit flag1=0;

u16 light;//���ձ���
bit B20_Ready;//ʶ��B20��־λ
unsigned int TempH=22;//�¶�����
bit BEE_flag=0;//��������
bit Receive_Smoke;//�������
u16 LightH=500;//��������
u16 i=0;



    



void Init()
{
     fFan(1);
     fBump(0);
     fBell(0);
}


//void Delay10ms()		//@11.0592MHz
//{
//	unsigned char i, j;

//	i = 108;
//	j = 145;
//	do
//	{
//		while (--j);
//	} while (--i);
//}
//void Key_Scan()
//{
//    
//    if(k11==0)
//    {
//        Delay10ms();
//        if(k11==0)
//        {
//            flags1++;
//        }
//        while(!k11);
//    }
//    if(flags1%2==1)
//    {
//        if(k21==0)
//        {
//            Delay10ms();
//            if(k21==0)
//            {
//                flags2=1;
//            }
//            while(!k21);
//        }
//        if(k31==0)
//        {
//            Delay10ms();
//            if(k31==0)
//            {
//                flags3=1;
//            }
//            while(!k31);
//        }
//    }
//    
//}

//void Key_DataCope()
//{
//    
//       if(flags2==1)
//       {
//          flags2=0;
//          TempH++;
//       }
//       if(flags3==1)
//       {
//           flags3=0;
//           TempH--;
//       }
//   
//}

void GPIO_Init()
{
    GPIO_InitTypeDef	GPIO_InitStructure;		//�ṹ����
	GPIO_InitStructure.Pin  = GPIO_Pin_2|GPIO_Pin_3;		//ָ��Ҫ��ʼ����IO, GPIO_Pin_0 ~ GPIO_Pin_7, �����
	GPIO_InitStructure.Mode = GPIO_OUT_PP;		//ָ��IO������������ʽ,GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
	GPIO_Inilize(GPIO_P0,&GPIO_InitStructure);	//��ʼ��
    
	GPIO_InitStructure.Pin  = GPIO_Pin_1;		//ָ��Ҫ��ʼ����IO, GPIO_Pin_0 ~ GPIO_Pin_7, �����
	GPIO_InitStructure.Mode = GPIO_HighZ;		//ָ��IO������������ʽ,GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
	GPIO_Inilize(GPIO_P0,&GPIO_InitStructure);	//��ʼ��
    
}

void display()
{
    if(count%=100)
    {
        DHT11_Read_Data(&temp,&humi);
	   // temp=read_temp();
        light=Receive_Data();
        Receive_Smoke=Smoke1();
    }
    OLED_ShowString(0,2,"Temp",16);
    OLED_ShowChar(36,2,':',16);
    OLED_ShowNum(44,2,temp,2,16);
    OLED_ShowString(0,4,"Lux",16);
    OLED_ShowChar(36,4,':',16); 
    OLED_ShowNum(44,4,light,4,16);
    if((temp>TempH)&(Receive_Smoke==BEE_flag)&(light>=LightH))
    {
        fFan(0);
        fBell(1);
        fBump(1);
        if(i==0)
        {
           Send_text();
					i ++;
        }
        OLED_ShowString(0,6,"Status:Warning",16);

    }
    else
    {
			i= 0;
        fFan(1);
        fBump(0);
        fBell(0);
			OLED_ShowString(0,6,"Status:Normal ",16);
			
    }
}
    
void main()
{

    Init();
	 DHT11_Init();
    dht11_gpio_OUT();
    GPIO_Init();   
	OLED_Init();
    OLED_Clear(); 
    UartInit();
    
    while(1)
    {
         //Key_Driver();
        // Key_DataCope();
      
        count++;
        display();
		}
}



void fFan(int i)
{
	fan = i;
}

void fBell(int i)
{
  bell = i;   
}

void fBump(int i)
{
	bump = i;
}




void reflesh() interrupt 1
{
   
//   count++;
//   if(count>=1)
//   {
//       count=0;
//       flag1=1;
//   }
   //Key_Scan();
                                                         
    
}

