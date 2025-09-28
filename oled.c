#include "stm32f10x.h"                  // Device header

#include "oled.h"
#include "oled_tab.h"


/****
*******��ʱ����
*****/
void Oled_Delay(uint32_t i)
{
	while(i--);
}

/****
*******I2C��ʼ����
*****/
void Oled_IIC_Start()
{
	OLED_SCL = 1;
	Oled_Delay(20);	
	OLED_SDA = 1;
	Oled_Delay(20);
	OLED_SDA = 0;
	Oled_Delay(20);
	OLED_SCL = 0;
}

/****
*******I2Cֹͣ����
*****/
void Oled_IIC_Stop()
{
	OLED_SDA = 0;
	Oled_Delay(20);
	OLED_SCL = 1;
	Oled_Delay(20);
	OLED_SDA = 1;
}

/****
*******I2Cдһ���ֽ����ݺ���
*******����ֵ��Ack_Bit
*****/
uint8_t Oled_Write_IIC_Byte(uint8_t IIC_Byte)
{
	uint8_t i;
	uint8_t Ack_Bit;                    //Ӧ���ź�
	for(i=0;i<8;i++)		
	{
		if(IIC_Byte & 0x80)								//1?0?
		{
			OLED_SDA = 1;
		}
		else
		{
			OLED_SDA = 0;
		}
		Oled_Delay(20);
		OLED_SCL = 1;
		Oled_Delay(20);
		OLED_SCL = 0;
		Oled_Delay(20);
		IIC_Byte<<=1;											//loop
	}
	OLED_SDA = 1;		                		//�ͷ�IIC SDA����Ϊ���������մ���������Ӧ���ź�	
	Oled_Delay(20);
	OLED_SCL = 1;                     	//��9��ʱ������
	Oled_Delay(20);
	Ack_Bit = GPIO_ReadInputDataBit(OLED_SCL_PORT,OLED_SCL_PIN);		            //��ȡӦ���ź�
	OLED_SCL = 0;
	return Ack_Bit;	
}

/****
*******д���ݺ���
*****/
void Oled_Write_IIC_Com(uint8_t IIC_Command)
{
	Oled_IIC_Start();
	Oled_Write_IIC_Byte(0x78);          //Slave addre.ss,SA0=0
	Oled_Write_IIC_Byte(0x00);					//write command
	Oled_Write_IIC_Byte(IIC_Command); 
	Oled_IIC_Stop();
}

/****
*******д���ݺ���
*****/
void Oled_Write_IIC_Dat(uint8_t IIC_Data)
{
	Oled_IIC_Start();
	Oled_Write_IIC_Byte(0x78);			
	Oled_Write_IIC_Byte(0x40);					//write data
	Oled_Write_IIC_Byte(IIC_Data);
	Oled_IIC_Stop(); 
}

/****
*******OLED������ʼ���꺯��
*****/
void Oled_Set_Pos(uint8_t x, uint8_t y) 
{
        Oled_Write_IIC_Com(0xb0+x);                                                                //����ҳ����8ҳ��B0~B7
        Oled_Write_IIC_Com(((y&0xf0)>>4)|0x10);                //�����е�ַ��4λ
        Oled_Write_IIC_Com((y&0x0f));                                                        //�����е�ַ��4λ
}

/****
*******OLED��ʼ������
*****/
void Oled_Init(void) 
{
	GPIO_InitTypeDef  GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(OLED_SCL_GPIO_CLK_ENABLE, ENABLE);	 	//ʹ�ܶ˿�ʱ��
	RCC_APB2PeriphClockCmd(OLED_SDA_GPIO_CLK_ENABLE, ENABLE);	 	//ʹ�ܶ˿�ʱ��

	GPIO_InitStructure.GPIO_Pin = OLED_SCL_PIN;									//��������
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 				//�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 				//IO���ٶ�Ϊ50MHz
	GPIO_Init(OLED_SCL_PORT, &GPIO_InitStructure);					 		//�����趨������ʼ��
	
	GPIO_InitStructure.GPIO_Pin = OLED_SDA_PIN;									//��������
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 				//�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 				//IO���ٶ�Ϊ50MHz
	GPIO_Init(OLED_SDA_PORT, &GPIO_InitStructure);					 		//�����趨������ʼ��

	Oled_Write_IIC_Com(0xAE);   	//display off
	Oled_Write_IIC_Com(0x20);			//Set Memory Addressing Mode	
	Oled_Write_IIC_Com(0x10);			//00,Horizontal Addressing Mode;01,Vertical Addressing Mode;10,Page Addressing Mode (RESET);11,Invalid
	Oled_Write_IIC_Com(0xb0);			//Set Page Start Address for Page Addressing Mode,0-7
	Oled_Write_IIC_Com(0xc8);			//Set COM Output Scan Direction
	Oled_Write_IIC_Com(0x02);			//---set low column address
	Oled_Write_IIC_Com(0x10);			//---set high column address
	Oled_Write_IIC_Com(0x40);			//--set start line address
	Oled_Write_IIC_Com(0x81);			//--set contrast control register
	Oled_Write_IIC_Com(0x7f);
	Oled_Write_IIC_Com(0xa1);			//--set segment re-map 0 to 127
	Oled_Write_IIC_Com(0xa6);			//--set normal display
	Oled_Write_IIC_Com(0xa8);			//--set multiplex ratio(1 to 64)
	Oled_Write_IIC_Com(0x3F);			//
	Oled_Write_IIC_Com(0xa4);			//0xa4,Output follows RAM content;0xa5,Output ignores RAM content
	Oled_Write_IIC_Com(0xd3);			//-set display offset
	Oled_Write_IIC_Com(0x00);			//-not offset
	Oled_Write_IIC_Com(0xd5);			//--set display clock divide ratio/oscillator frequency
	Oled_Write_IIC_Com(0xf0);			//--set divide ratio
	Oled_Write_IIC_Com(0xd9);			//--set pre-charge period
	Oled_Write_IIC_Com(0x22);			//
	Oled_Write_IIC_Com(0xda);			//--set com pins hardware configuration
	Oled_Write_IIC_Com(0x12);
	Oled_Write_IIC_Com(0xdb);			//--set vcomh
	Oled_Write_IIC_Com(0x20);			//0x20,0.77xVcc
	Oled_Write_IIC_Com(0x8d);			//--set DC-DC enable
	Oled_Write_IIC_Com(0x14);			//
	Oled_Write_IIC_Com(0xaf);			//--turn on oled panel 	
}

/****
*******OLED��ȫ������
*****/
void Oled_Clear_All(void)  
{  
	uint8_t i,n;		    
	for(i=0;i<8;i++)
	{  
		Oled_Write_IIC_Com (0xb0+i);
		Oled_Write_IIC_Com (0x01);
		Oled_Write_IIC_Com (0x10);        
		for(n=0;n<128;n++)
			Oled_Write_IIC_Dat(0); 
	}
}

/****
*******OLED��ʾ�����ַ�����
*****/
void Oled_ShowChar(uint8_t x,uint8_t y,uint32_t chr)
{
	uint32_t c=0,i=0;
	c=chr-' ';			
	Oled_Set_Pos(x,y);	
	for(i=0;i<8;i++)
		Oled_Write_IIC_Dat(OLED_F8X16[c*16+i]);
	Oled_Set_Pos(x+1,y);
	for(i=0;i<8;i++)
		Oled_Write_IIC_Dat(OLED_F8X16[c*16+i+8]);
}

/****
*******OLED��ʾ�ַ�������
*****/
void Oled_ShowString(uint8_t x,uint8_t y,char *chr)
{
	uint32_t j=0;
	x = (x-1)*2;
	y = y*8;
	while(chr[j]!='\0')
	{		
		Oled_ShowChar(x,y,chr[j]);
		y+=8;
		if(y>120){y=0;x+=2;}
		j++;
	}
}

/****
*******OLED��ʾ���ĺ���
*****/
void Oled_ShowCHinese(uint8_t x,uint8_t y,char *p)
{
		uint8_t  t,wordNum,wordNumber;
		x = (x-1)*2;
		y = y*16;
		
		wordNumber=sizeof(OLED_HZK)/34;

		while(*p != '\0')
		{
			for(wordNum=0;wordNum<wordNumber;wordNum++)
			{
				if(OLED_HZK[wordNum].Char[0]== *p && OLED_HZK[wordNum].Char[1]== *(p+1))
				{
					Oled_Set_Pos(x,y);
					for(t=0;t<16;t++)
					{
						Oled_Write_IIC_Dat(OLED_HZK[wordNum].Hex[t]);
					}
					Oled_Set_Pos(x+1,y);
					for(t=0;t<16;t++)
					{
						Oled_Write_IIC_Dat(OLED_HZK[wordNum].Hex[t+16]);
					}
					break;
				}
			}
		p += 2;
		y+=16;
	}
}
	
