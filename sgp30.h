/**********************************
作者：单片机俱乐部
网站：https://www.mcuclub.cn/
**********************************/


#ifndef __SGP30_H
#define __SGP30_H


/**********************************
包含头文件
**********************************/
#include "sys.h"


/**********************************
PIN口定义
**********************************/
#define SGP30_SCL_GPIO_CLK_ENABLE      RCC_APB2Periph_GPIOB				//SGP30_SCL引脚
#define SGP30_SCL_PORT                 GPIOB
#define SGP30_SCL_PIN                  GPIO_Pin_12
#define SGP30_SCL  										 PBout(12)

#define SGP30_SDA_GPIO_CLK_ENABLE      RCC_APB2Periph_GPIOB				//SGP30_SDA引脚
#define SGP30_SDA_PORT                 GPIOB
#define SGP30_SDA_PIN                  GPIO_Pin_13
#define SGP30_SDA_OUT  								 PBout(13)
#define SGP30_SDA_IN  								 PBin(13)


/**********************************
重定义关键词
**********************************/
#define SGP30_IIC_Address   		0xB0  		//从机地址


/**********************************
函数声明
**********************************/
void SGP30_Init(void);																											//SGP30初始化
void SGP30_Get_Co2_Tvoc_Value(uint16_t *co2_value, uint16_t *tvoc_value);		//获取CO2和TVOC值


#endif

