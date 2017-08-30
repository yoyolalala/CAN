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
	LED_Init();
	CAN1_Mode_Init(CAN_SJW_1tq,CAN_BS2_6tq,CAN_BS1_7tq,6,normolMode);//CAN初始化 波特率500Kbps
}
int main(void)
{ 
	u8 canbuf[8];
	bool isSendData = 0;
	bool index = true;
	setup();
	
	while(1)
	{
		if(index)
			for(int i=0;i<8;i++)
				canbuf[i] = i;
		else for(int i=8;i>0;i--)
				canbuf[i] = 8 - i;
		//index = !index;
		isSendData = CAN1_Send_Msg(canbuf,8);
		if(isSendData)
			LED1 = 1; //send failed
		else PE12Toggle();
	}
	
}
