/**********************************
���ߣ���Ƭ�����ֲ�
��վ��https://www.mcuclub.cn/
**********************************/


#ifndef __OLED_H__
#define __OLED_H__


/**********************************
����ͷ�ļ�
**********************************/
#include "sys.h" 


/**********************************
PIN�ڶ���
**********************************/
#define OLED_SCL_GPIO_CLK_ENABLE      RCC_APB2Periph_GPIOB				//SCL����
#define OLED_SCL_PORT                 GPIOB
#define OLED_SCL_PIN                  GPIO_Pin_5
#define OLED_SCL  										PBout(5)

#define OLED_SDA_GPIO_CLK_ENABLE      RCC_APB2Periph_GPIOB				//SDA����
#define OLED_SDA_PORT                 GPIOB
#define OLED_SDA_PIN                  GPIO_Pin_6
#define OLED_SDA  										PBout(6)


/**********************************
��������
**********************************/
void Oled_Init(void);																							//OLED��ʼ������
void Oled_Clear_All(void);																				//OLED��ȫ������
void Oled_ShowString(uint8_t x,uint8_t y,char *chr);							//OLED��ʾ�ַ�������
void Oled_ShowCHinese(uint8_t x,uint8_t y,char *P);								//OLED��ʾ���ĺ���


#endif

