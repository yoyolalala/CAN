#ifndef __LED_H
#define __LED_H
#include "sys.h"
#include "stm32f4xx_gpio.h"
#include "delay.h"
#include "stm32f4xx_rcc.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32F407������
//LED��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2014/5/2
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	


//LED�˿ڶ���
#define LED1 PEout(12)	// DS1	 

void LED_Init(void);//��ʼ��	
void PE12Toggle(void);
#endif
