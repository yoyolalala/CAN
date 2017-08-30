#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "lcd.h"
#include "key.h"
#include "can.h"
#include <stdbool.h>
#define normolMode 0
//ALIENTEK 探索者STM32F407开发板 实验27
//CAN通信实验-库函数版本
//技术支持：www.openedv.com
//淘宝店铺：http://eboard.taobao.com  
//广州市星翼电子科技有限公司  
//作者：正点原子 @ALIENTEK
void setup()
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);//设置系统中断优先级分组4
	delay_init(168);    //初始化延时函数
	uart_init(115200);	//初始化串口波特率为115200
	LED_Init();					//初始化LED 
	LCD_Init();					//LCD初始化 
	KEY_Init(); 				//按键初始化  
	CAN1_Mode_Init(CAN_SJW_1tq,CAN_BS2_6tq,CAN_BS1_7tq,6,normolMode);	//CAN初始化 波特率500Kbps
	POINT_COLOR=BLACK;
	LCD_ShowString(30,70,200,16,16,"CAN TEST");	 		
	POINT_COLOR=BLUE;//设置字体为蓝色
	LCD_ShowString(30,190,200,16,16,"isRevData:");		//提示发送的数据	
	LCD_ShowString(30,250,200,16,16,"Receive Data:");	//提示接收到的数据		
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
		//if(key == WKUP_PRES)//WK_UP按下，改变CAN的工作模式
		//{	   
		//	mode = !mode;
		//}
	//	if(mode) //mode =1 环回模式
	//	{
	//		LCD_ShowString(30,130,200,16,16,"LoopBack Mode");
	//		res = CAN1_Send_Msg(canbuf,8);
	//		if(res)
	//			LCD_ShowString(30+80,190,200,16,16,"sendFailed");		//提示发送失败
	//		else
	//		{
	//			LCD_ShowString(30+80,190,200,16,16,"sendOK");
	//		}
	//	}
		
	//	if(!mode)//普通模式，需要2个开发板
	//	{
		LCD_ShowString(30,130,200,16,16,"normal Mode");	    
		isRev = CAN1_Receive_Msg(canbuf);
		if(isRev)
		{	
			LCD_ShowString(30+80,190,200,16,16,"revData!   ");
			LCD_Fill(30,270,160,310,WHITE);//清除之前的显示
			for(i=0;i<isRev;i++)
			{									    
				if(i<4)
					LCD_ShowxNum(30+(i)*32,270,canbuf[i],3,16,0X80);	//显示数据
				else 
					LCD_ShowxNum(30+(i-4)*32,290,canbuf[i],3,16,0X80);	//显示数据
			}
		}
		else
		{
			LCD_ShowString(30+80,190,200,16,16,"revNothing!");
		}
	//	}
	//	key=CAN1_Receive_Msg(canbuf);
	//	if(key)//接收到有数据
	//	{			
	//		LCD_Fill(30,270,160,310,WHITE);//清除之前的显示
	//		for(i=0;i<key;i++)
	//		{									    
	//			if(i<4)LCD_ShowxNum(30+i*32,270,canbuf[i],3,16,0X80);	//显示数据
	//			else LCD_ShowxNum(30+(i-4)*32,290,canbuf[i],3,16,0X80);	//显示数据
	//		}
	//	}
		delay_ms(100);
		LED0=!LED0;//提示系统正在运行	   
	}
	
}
