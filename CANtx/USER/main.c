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
	LED_Init();
	CAN1_Mode_Init(CAN_SJW_1tq,CAN_BS2_6tq,CAN_BS1_7tq,6,normolMode);//CAN��ʼ�� ������500Kbps
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
