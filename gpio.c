
#include "gpio.h"
#include "stm32f10x.h"                  // Device header


/****
*******	LED IO初始化
*****/    
void Gpio_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC,ENABLE);			    //使能端口时钟

	GPIO_InitStructure.GPIO_Pin  = LEDS_GPIO_PIN;  					//引脚配置
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 				//设置成推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 		//IO口速度为50MHz
 	GPIO_Init(LEDS_GPIO_PORT, &GPIO_InitStructure);					//根据设定参数初始化
	GPIO_SetBits(LEDS_GPIO_PORT,LEDS_GPIO_PIN);  						//IO口输出高

	GPIO_InitStructure.GPIO_Pin  = LED_PIN; 									//引脚配置
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD; 					//设置成开漏输出
 	GPIO_Init(LED_PORT, &GPIO_InitStructure);									//根据设定参数初始化
	GPIO_SetBits(LED_PORT,LED_PIN); 				 									//IO口输出高

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 					//设置成推挽输出
	GPIO_InitStructure.GPIO_Pin  = BEEP_PIN; 									//引脚配置
	GPIO_Init(BEEP_PORT, &GPIO_InitStructure);								//根据设定参数初始化
	GPIO_ResetBits(BEEP_PORT,BEEP_PIN); 				 							//IO口输出低

	GPIO_InitStructure.GPIO_Pin  = RELAY_TF_PIN; 							//引脚配置
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 					//设置成推挽输出
 	GPIO_Init(RELAY_TF_PORT, &GPIO_InitStructure);						//根据设定参数初始化
	GPIO_ResetBits(RELAY_TF_PORT,RELAY_TF_PIN);							 	//IO口输出低

	GPIO_InitStructure.GPIO_Pin  = RELAY_BG_PIN; 							//引脚配置
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 					//设置成推挽输出
 	GPIO_Init(RELAY_BG_PORT, &GPIO_InitStructure);						//根据设定参数初始化
	GPIO_ResetBits(RELAY_BG_PORT,RELAY_BG_PIN);							 	//IO口输出低
	
	GPIO_InitStructure.GPIO_Pin  = RELAY_JS_PIN; 							//引脚配置
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 					//设置成推挽输出
 	GPIO_Init(RELAY_JS_PORT, &GPIO_InitStructure);						//根据设定参数初始化
	GPIO_ResetBits(RELAY_JS_PORT,RELAY_JS_PIN);								//IO口输出低
	
	GPIO_InitStructure.GPIO_Pin  = RELAY_ZHY_PIN; 						//引脚配置
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 					//设置成推挽输出
 	GPIO_Init(RELAY_ZHY_PORT, &GPIO_InitStructure);						//根据设定参数初始化
	GPIO_ResetBits(RELAY_ZHY_PORT,RELAY_ZHY_PIN);							//IO口输出低
	
	GPIO_InitStructure.GPIO_Pin  = RELAY_YYY_PIN; 						//引脚配置
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 					//设置成推挽输出
 	GPIO_Init(RELAY_YYY_PORT, &GPIO_InitStructure);						//根据设定参数初始化
	GPIO_ResetBits(RELAY_YYY_PORT,RELAY_YYY_PIN);							//IO口输出低
}

