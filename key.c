
#include "key.h"
#include "delay.h"


/****
*******	KEY IO��ʼ��
*****/
void Key_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(KEY1_GPIO_CLK_ENABLE,ENABLE);								//ʹ�ܶ˿�ʱ��
	GPIO_InitStructure.GPIO_Pin  = KEY1_PIN;														//��������
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 											//���ó���������
 	GPIO_Init(KEY1_PORT, &GPIO_InitStructure);													//�����趨������ʼ��
	GPIO_SetBits(KEY1_PORT,KEY1_PIN);						 												//IO�������
	
	RCC_APB2PeriphClockCmd(KEY2_GPIO_CLK_ENABLE,ENABLE);								//ʹ�ܶ˿�ʱ��
	GPIO_InitStructure.GPIO_Pin  = KEY2_PIN;														//��������
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 											//���ó���������
 	GPIO_Init(KEY2_PORT, &GPIO_InitStructure);													//�����趨������ʼ��
	GPIO_SetBits(KEY2_PORT,KEY2_PIN);						 												//IO�������
	
	RCC_APB2PeriphClockCmd(KEY3_GPIO_CLK_ENABLE,ENABLE);								//ʹ�ܶ˿�ʱ��
	GPIO_InitStructure.GPIO_Pin  = KEY3_PIN;														//��������
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 											//���ó���������
 	GPIO_Init(KEY3_PORT, &GPIO_InitStructure);													//�����趨������ʼ��
	GPIO_SetBits(KEY3_PORT,KEY3_PIN);						 												//IO�������
}

/****
*******	����������
mode:0,��֧��������;1,֧��������;
*****/
u8 Chiclet_Keyboard_Scan(u8 mode)
{	 
	static u8 key_up=1;			//�����ɿ���־

	if(mode)  							//mode=1,֧������
		key_up=1;

	if(key_up && (KEY1==0||KEY2==0||KEY3==0))
	{
		Delay_ms(10);					//ȥ���� 
		key_up=0;
		
		if(KEY1==0)						//����1���£�����1
			return 1;
		else if(KEY2==0)			//����2���£�����2
			return 2;
		else if(KEY3==0)			//����3���£�����3
			return 3;
	}
	else if(KEY1==1&&KEY2==1&&KEY3==1)		//û�а������£��ɿ���־λ��1
	{
		key_up=1;
	}
	
	return 0;								// �ް�������.����0
}
