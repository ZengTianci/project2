/**********************************
���ߣ���Ƭ�����ֲ�
��վ��https://www.mcuclub.cn/
**********************************/


#ifndef __KEY_H
#define __KEY_H


/**********************************
����ͷ�ļ�
**********************************/
#include "sys.h" 


/**********************************
�ض���ؼ���
**********************************/
#define KEY1_GPIO_CLK_ENABLE      RCC_APB2Periph_GPIOB		//����2����
#define KEY1_PORT                 GPIOB
#define KEY1_PIN                  GPIO_Pin_7
#define KEY1  										PBin(7)

#define KEY2_GPIO_CLK_ENABLE      RCC_APB2Periph_GPIOB		//����3����
#define KEY2_PORT                 GPIOB
#define KEY2_PIN                  GPIO_Pin_8
#define KEY2  										PBin(8)

#define KEY3_GPIO_CLK_ENABLE      RCC_APB2Periph_GPIOB		//����3����
#define KEY3_PORT                 GPIOB
#define KEY3_PIN                  GPIO_Pin_9
#define KEY3  										PBin(9)


/**********************************
��������
**********************************/
void Key_Init(void);																			//IO��ʼ��
u8 Chiclet_Keyboard_Scan(u8 mode);  											//����ɨ�躯��


#endif

