
#include "gpio.h"
#include "stm32f10x.h"                  // Device header


/****
*******	LED IO��ʼ��
*****/    
void Gpio_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC,ENABLE);			    //ʹ�ܶ˿�ʱ��

	GPIO_InitStructure.GPIO_Pin  = LEDS_GPIO_PIN;  					//��������
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 				//���ó��������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 		//IO���ٶ�Ϊ50MHz
 	GPIO_Init(LEDS_GPIO_PORT, &GPIO_InitStructure);					//�����趨������ʼ��
	GPIO_SetBits(LEDS_GPIO_PORT,LEDS_GPIO_PIN);  						//IO�������

	GPIO_InitStructure.GPIO_Pin  = LED_PIN; 									//��������
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD; 					//���óɿ�©���
 	GPIO_Init(LED_PORT, &GPIO_InitStructure);									//�����趨������ʼ��
	GPIO_SetBits(LED_PORT,LED_PIN); 				 									//IO�������

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 					//���ó��������
	GPIO_InitStructure.GPIO_Pin  = BEEP_PIN; 									//��������
	GPIO_Init(BEEP_PORT, &GPIO_InitStructure);								//�����趨������ʼ��
	GPIO_ResetBits(BEEP_PORT,BEEP_PIN); 				 							//IO�������

	GPIO_InitStructure.GPIO_Pin  = RELAY_TF_PIN; 							//��������
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 					//���ó��������
 	GPIO_Init(RELAY_TF_PORT, &GPIO_InitStructure);						//�����趨������ʼ��
	GPIO_ResetBits(RELAY_TF_PORT,RELAY_TF_PIN);							 	//IO�������

	GPIO_InitStructure.GPIO_Pin  = RELAY_BG_PIN; 							//��������
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 					//���ó��������
 	GPIO_Init(RELAY_BG_PORT, &GPIO_InitStructure);						//�����趨������ʼ��
	GPIO_ResetBits(RELAY_BG_PORT,RELAY_BG_PIN);							 	//IO�������
	
	GPIO_InitStructure.GPIO_Pin  = RELAY_JS_PIN; 							//��������
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 					//���ó��������
 	GPIO_Init(RELAY_JS_PORT, &GPIO_InitStructure);						//�����趨������ʼ��
	GPIO_ResetBits(RELAY_JS_PORT,RELAY_JS_PIN);								//IO�������
	
	GPIO_InitStructure.GPIO_Pin  = RELAY_ZHY_PIN; 						//��������
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 					//���ó��������
 	GPIO_Init(RELAY_ZHY_PORT, &GPIO_InitStructure);						//�����趨������ʼ��
	GPIO_ResetBits(RELAY_ZHY_PORT,RELAY_ZHY_PIN);							//IO�������
	
	GPIO_InitStructure.GPIO_Pin  = RELAY_YYY_PIN; 						//��������
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 					//���ó��������
 	GPIO_Init(RELAY_YYY_PORT, &GPIO_InitStructure);						//�����趨������ʼ��
	GPIO_ResetBits(RELAY_YYY_PORT,RELAY_YYY_PIN);							//IO�������
}

