/**********************************
���ߣ���Ƭ�����ֲ�
��վ��https://www.mcuclub.cn/
**********************************/


#ifndef __SGP30_H
#define __SGP30_H


/**********************************
����ͷ�ļ�
**********************************/
#include "sys.h"


/**********************************
PIN�ڶ���
**********************************/
#define SGP30_SCL_GPIO_CLK_ENABLE      RCC_APB2Periph_GPIOB				//SGP30_SCL����
#define SGP30_SCL_PORT                 GPIOB
#define SGP30_SCL_PIN                  GPIO_Pin_12
#define SGP30_SCL  										 PBout(12)

#define SGP30_SDA_GPIO_CLK_ENABLE      RCC_APB2Periph_GPIOB				//SGP30_SDA����
#define SGP30_SDA_PORT                 GPIOB
#define SGP30_SDA_PIN                  GPIO_Pin_13
#define SGP30_SDA_OUT  								 PBout(13)
#define SGP30_SDA_IN  								 PBin(13)


/**********************************
�ض���ؼ���
**********************************/
#define SGP30_IIC_Address   		0xB0  		//�ӻ���ַ


/**********************************
��������
**********************************/
void SGP30_Init(void);																											//SGP30��ʼ��
void SGP30_Get_Co2_Tvoc_Value(uint16_t *co2_value, uint16_t *tvoc_value);		//��ȡCO2��TVOCֵ


#endif

