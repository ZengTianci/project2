/**********************************
���ߣ���Ƭ�����ֲ�
��վ��https://www.mcuclub.cn/
**********************************/


#ifndef __GPIO_H
#define __GPIO_H


/**********************************
����ͷ�ļ�
**********************************/
#include "sys.h"


/**********************************
�ض���ؼ���
**********************************/
#define LEDS_GPIO_PORT                GPIOC
#define LEDS_GPIO_PIN                 GPIO_Pin_13
#define LED_SYS                       PCout(13)       //��СϵͳLED

#define BEEP_PORT                     GPIOB
#define BEEP_PIN                      GPIO_Pin_1
#define BEEP 									    		PBout(1)				//����������

#define LED_PORT                      GPIOB
#define LED_PIN                       GPIO_Pin_0
#define LED 									    		PBout(0)				//LED������

#define RELAY_TF_PORT                 GPIOB
#define RELAY_TF_PIN                 	GPIO_Pin_14
#define RELAY_TF 											PBout(14)				//ͨ��̵�������

#define RELAY_BG_PORT                 GPIOA
#define RELAY_BG_PIN                 	GPIO_Pin_7
#define RELAY_BG 											PAout(7)				//����̵�������

#define RELAY_JS_PORT               	GPIOA
#define RELAY_JS_PIN                	GPIO_Pin_6
#define RELAY_JS 											PAout(6)				//�����̵�������

#define RELAY_ZHY_PORT                GPIOA
#define RELAY_ZHY_PIN                 GPIO_Pin_5
#define RELAY_ZHY 										PAout(5)				//���׼̵�������

#define RELAY_YYY_PORT                GPIOA
#define RELAY_YYY_PIN                 GPIO_Pin_4
#define RELAY_YYY 										PAout(4)				//���ؼ̵�������


/**********************************
��������
**********************************/
void Gpio_Init(void);													//GPIO��ʼ��


#endif
