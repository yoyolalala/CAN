#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "lcd.h"
#include "key.h"
#include "can.h"
#include <stdbool.h>
#define normolMode 0
//ALIENTEK ̽����STM32F407������ ʵ��27
//CANͨ��ʵ��-�⺯���汾
//����֧�֣�www.openedv.com
//�Ա����̣�http://eboard.taobao.com  
//������������ӿƼ����޹�˾  
//���ߣ�����ԭ�� @ALIENTEK
void setup()
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);//����ϵͳ�ж����ȼ�����4
	delay_init(168);    //��ʼ����ʱ����
	uart_init(115200);	//��ʼ�����ڲ�����Ϊ115200
	LED_Init();					//��ʼ��LED 
	LCD_Init();					//LCD��ʼ�� 
	KEY_Init(); 				//������ʼ��  
	CAN1_Mode_Init(CAN_SJW_1tq,CAN_BS2_6tq,CAN_BS1_7tq,6,normolMode);	//CAN��ʼ�� ������500Kbps
	POINT_COLOR=BLACK;
	LCD_ShowString(30,70,200,16,16,"CAN TEST");	 		
	POINT_COLOR=BLUE;//��������Ϊ��ɫ
	LCD_ShowString(30,190,200,16,16,"isRevData:");		//��ʾ���͵�����	
	LCD_ShowString(30,250,200,16,16,"Receive Data:");	//��ʾ���յ�������		
}
int main(void)
{ 
//	u8 key;
	u8 isRev;
	u8 i=0;
	u8 canbuf[8];
	setup();
	
	while(1)
	{
		//key = KEY_Scan(0);
		//if(key == WKUP_PRES)//WK_UP���£��ı�CAN�Ĺ���ģʽ
		//{	   
		//	mode = !mode;
		//}
	//	if(mode) //mode =1 ����ģʽ
	//	{
	//		LCD_ShowString(30,130,200,16,16,"LoopBack Mode");
	//		res = CAN1_Send_Msg(canbuf,8);
	//		if(res)
	//			LCD_ShowString(30+80,190,200,16,16,"sendFailed");		//��ʾ����ʧ��
	//		else
	//		{
	//			LCD_ShowString(30+80,190,200,16,16,"sendOK");
	//		}
	//	}
		
	//	if(!mode)//��ͨģʽ����Ҫ2��������
	//	{
		LCD_ShowString(30,130,200,16,16,"normal Mode");	    
		isRev = CAN1_Receive_Msg(canbuf);
		if(isRev)
		{	
			LCD_ShowString(30+80,190,200,16,16,"revData!   ");
			LCD_Fill(30,270,160,310,WHITE);//���֮ǰ����ʾ
			for(i=0;i<isRev;i++)
			{									    
				if(i<4)
					LCD_ShowxNum(30+(i)*32,270,canbuf[i],3,16,0X80);	//��ʾ����
				else 
					LCD_ShowxNum(30+(i-4)*32,290,canbuf[i],3,16,0X80);	//��ʾ����
			}
		}
		else
		{
			LCD_ShowString(30+80,190,200,16,16,"revNothing!");
		}
	//	}
	//	key=CAN1_Receive_Msg(canbuf);
	//	if(key)//���յ�������
	//	{			
	//		LCD_Fill(30,270,160,310,WHITE);//���֮ǰ����ʾ
	//		for(i=0;i<key;i++)
	//		{									    
	//			if(i<4)LCD_ShowxNum(30+i*32,270,canbuf[i],3,16,0X80);	//��ʾ����
	//			else LCD_ShowxNum(30+(i-4)*32,290,canbuf[i],3,16,0X80);	//��ʾ����
	//		}
	//	}
		delay_ms(100);
		LED0=!LED0;//��ʾϵͳ��������	   
	}
	
}
