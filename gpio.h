/**********************************
作者：单片机俱乐部
网站：https://www.mcuclub.cn/
**********************************/


#ifndef __GPIO_H
#define __GPIO_H


/**********************************
包含头文件
**********************************/
#include "sys.h"


/**********************************
重定义关键词
**********************************/
#define LEDS_GPIO_PORT                GPIOC
#define LEDS_GPIO_PIN                 GPIO_Pin_13
#define LED_SYS                       PCout(13)       //最小系统LED

#define BEEP_PORT                     GPIOB
#define BEEP_PIN                      GPIO_Pin_1
#define BEEP 									    		PBout(1)				//蜂鸣器引脚

#define LED_PORT                      GPIOB
#define LED_PIN                       GPIO_Pin_0
#define LED 									    		PBout(0)				//LED灯引脚

#define RELAY_TF_PORT                 GPIOB
#define RELAY_TF_PIN                 	GPIO_Pin_14
#define RELAY_TF 											PBout(14)				//通风继电器引脚

#define RELAY_BG_PORT                 GPIOA
#define RELAY_BG_PIN                 	GPIO_Pin_7
#define RELAY_BG 											PAout(7)				//补光继电器引脚

#define RELAY_JS_PORT               	GPIOA
#define RELAY_JS_PIN                	GPIO_Pin_6
#define RELAY_JS 											PAout(6)				//补氮继电器引脚

#define RELAY_ZHY_PORT                GPIOA
#define RELAY_ZHY_PIN                 GPIO_Pin_5
#define RELAY_ZHY 										PAout(5)				//补磷继电器引脚

#define RELAY_YYY_PORT                GPIOA
#define RELAY_YYY_PIN                 GPIO_Pin_4
#define RELAY_YYY 										PAout(4)				//补钾继电器引脚


/**********************************
函数声明
**********************************/
void Gpio_Init(void);													//GPIO初始化


#endif
