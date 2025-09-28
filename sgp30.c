
#include "sgp30.h"
#include "delay.h"


/****����
uint16_t co2_value = 0;								//CO2ֵ
uint16_t tvoc_value = 0;							//TVOCֵ

SGP30_Init();												//SGP30��ʼ��

SGP30_Get_Co2_Tvoc_Value(&co2_value, &tvoc_value);		//��ȡCO2��TVOCֵ
*****/

/****
*******SGP30�����������
*****/
void SGP30_GPIO_OUT(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(SGP30_SCL_GPIO_CLK_ENABLE, ENABLE);	 	//ʹ�ܶ˿�ʱ��
	GPIO_InitStructure.GPIO_Pin = SGP30_SCL_PIN;									//��������
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 						//�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 						//IO���ٶ�Ϊ50MHz
	GPIO_Init(SGP30_SCL_PORT, &GPIO_InitStructure);					 			//�����趨������ʼ��
	
	RCC_APB2PeriphClockCmd(SGP30_SDA_GPIO_CLK_ENABLE, ENABLE);	 	//ʹ�ܶ˿�ʱ��
	GPIO_InitStructure.GPIO_Pin = SGP30_SDA_PIN;				 					//��������
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 						//�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 						//IO���ٶ�Ϊ50MHz
	GPIO_Init(SGP30_SDA_PORT, &GPIO_InitStructure);					 			//�����趨������ʼ��
}

/****
*******SGP30������������
*****/
void SGP30_GPIO_IN(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(SGP30_SCL_GPIO_CLK_ENABLE, ENABLE);	 	//ʹ�ܶ˿�ʱ��
	GPIO_InitStructure.GPIO_Pin = SGP30_SCL_PIN;									//��������
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 						//�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 						//IO���ٶ�Ϊ50MHz
	GPIO_Init(SGP30_SCL_PORT, &GPIO_InitStructure);					 			//�����趨������ʼ��
	
	RCC_APB2PeriphClockCmd(SGP30_SDA_GPIO_CLK_ENABLE, ENABLE);	 	//ʹ�ܶ˿�ʱ��
	GPIO_InitStructure.GPIO_Pin = SGP30_SDA_PIN;				 					//��������
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		 							//���ó���������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 						//IO���ٶ�Ϊ50MHz
	GPIO_Init(SGP30_SDA_PORT, &GPIO_InitStructure);					 			//�����趨������ʼ��
}

/****
*******����SGP30_IIC��ʼ�ź�
*****/
void SGP30_IIC_Start(void)
{
	SGP30_GPIO_OUT();     //sda�����
	SGP30_SDA_OUT=1;	  	  
	SGP30_SCL=1;
	Delay_us(4);
 	SGP30_SDA_OUT=0;
	Delay_us(4);
	SGP30_SCL=0;					//ǯסI2C���ߣ�׼�����ͻ�������� 
}

/****
*******����SGP30_IICֹͣ�ź�
*****/
void SGP30_IIC_Stop(void)
{
	SGP30_GPIO_OUT();			//sda�����
	SGP30_SCL=0;
	SGP30_SDA_OUT=0;
 	Delay_us(4);
	SGP30_SCL=1; 
	SGP30_SDA_OUT=1;			//����I2C���߽����ź�
	Delay_us(4);							   	
}

/****
*******�ȴ�Ӧ���źŵ���
����ֵ��1������Ӧ��ʧ��
        0������Ӧ��ɹ�
*****/
uint8_t SGP30_IIC_Wait_Ack(void)
{
	uint8_t ucErrTime=0;
	
	SGP30_GPIO_IN();      //SDA����Ϊ����  
	SGP30_SDA_OUT=1;
	Delay_us(1);	   
	SGP30_SCL=1;
	Delay_us(1);
	
	while(SGP30_SDA_IN)   //IO�����ݶ���
	{
		ucErrTime++;
		if(ucErrTime > 250)
		{
			SGP30_IIC_Stop();
			return 1;
		}
	}
	
	SGP30_SCL=0;//ʱ�����0 	   

	return 0;  
}

/****
*******����ACKӦ��
*****/
void SGP30_IIC_Ack(void)
{
	SGP30_SCL=0;
	SGP30_GPIO_OUT();	//�ͷ�һ��������ʱ��ACKӦ���ź�Ϊ0ʱ
	SGP30_SDA_OUT=0;		//���ͳɹ�
	Delay_us(2);
	SGP30_SCL=1;
	Delay_us(2);
	SGP30_SCL=0;
}

/****
*******������ACKӦ��
*****/    
void SGP30_IIC_NAck(void)
{
	SGP30_SCL=0;
	SGP30_GPIO_OUT();
	SGP30_SDA_OUT=1;
	Delay_us(2);
	SGP30_SCL=1;
	Delay_us(2);
	SGP30_SCL=0;
}

/****
*******SGP30_IIC����һ���ֽ�
			���شӻ�����Ӧ��
			1����Ӧ��
			0����Ӧ��	
*****/
//		  
void SGP30_IIC_Send_Byte(uint8_t txd)
{                        
	uint8_t t;   
	SGP30_GPIO_OUT(); 	//�������
	SGP30_SCL=0;				//����ʱ�ӿ�ʼ���ݴ���
	for(t=0; t<8; t++)
	{              
		SGP30_SDA_OUT = (txd&0x80)>>7;		//io���������
		txd<<=1; 	  
		Delay_us(2);

		SGP30_SCL=1;
		Delay_us(2); 
		SGP30_SCL=0;	
		Delay_us(2);
	}	 
}

/****
*******��1���ֽڣ�ack=1ʱ������ACK��ack=0������nACK 
*****/
uint8_t SGP30_IIC_Read_Byte(uint8_t ack)
{
	unsigned char i,receive=0;
	SGP30_GPIO_IN();						//SDA����Ϊ����
  for(i=0; i<8; i++ )
	{
		SGP30_SCL=0; 
		Delay_us(2);

		SGP30_SCL=1;
		receive<<=1;

		if(SGP30_SDA_IN) 				 	//�����������ˣ���ȡһ���ֽ�
			receive++;
		
		Delay_us(1); 
  }
	
	if(!ack)
		SGP30_IIC_NAck();					//����nACK
	else
		SGP30_IIC_Ack(); 					//����ACK   

   return receive;
}


/****
��SGP30ָ����ַ����һ������
ReadAddr:��ʼ�����ĵ�ַ  
����ֵ  :��������
*****/
uint8_t SGP30_ReadOneByte(uint16_t ReadAddr)
{				  
	uint8_t data=0;
	
	SGP30_IIC_Start();
	
	SGP30_IIC_Send_Byte(SGP30_IIC_Address);	   	//����д����
	SGP30_IIC_Wait_Ack();

	SGP30_IIC_Send_Byte(ReadAddr);   							//���͵�ַ
	SGP30_IIC_Wait_Ack();
	
	SGP30_IIC_Start();
	
	SGP30_IIC_Send_Byte(SGP30_IIC_Address+1);   //�������ģʽ			   
	SGP30_IIC_Wait_Ack();
	
	data = SGP30_IIC_Read_Byte(0);		   
	SGP30_IIC_Stop();															//����һ��ֹͣ����
	
	return data;
}

/****
//��SGP30ָ����ַд��һ������
//WriteAddr  :д�����ݵ�Ŀ�ĵ�ַ    
//DataToWrite:Ҫд�������
*****/
void SGP30_WriteOneByte(uint16_t WriteAddr,uint8_t DataToWrite)
{				   	  	    																 
	SGP30_IIC_Start();
  
	SGP30_IIC_Send_Byte(SGP30_IIC_Address);	    //����д����
	SGP30_IIC_Wait_Ack();
	
	SGP30_IIC_Send_Byte(WriteAddr);   						//���͵͵�ַ
	SGP30_IIC_Wait_Ack(); 	 
	
	SGP30_IIC_Send_Byte(DataToWrite);     				//�����ֽ�							   
	SGP30_IIC_Wait_Ack();
	
	SGP30_IIC_Stop();															//����һ��ֹͣ���� 
	Delay_ms(100);
}

/****
*******��SGP30�ĵ�ַaddress�ж�ȡһ���ֽڵ�����
*****/
uint32_t SGP30_Read_Data()
{
	uint32_t dat;
	uint16_t crc;
	
	SGP30_IIC_Start();
	SGP30_IIC_Send_Byte(SGP30_IIC_Address + 1);
	SGP30_IIC_Wait_Ack();
	
	dat = SGP30_IIC_Read_Byte(1);						//CO2��λ����
	dat <<= 8;
	dat += SGP30_IIC_Read_Byte(1);					//CO2��λ����
	
	crc = SGP30_IIC_Read_Byte(1); 					//CRCУ��ֵ
	crc = crc;  														//Ϊ�˲��ó��ֱ��뾯��
	
	dat <<= 8;
	dat += SGP30_IIC_Read_Byte(1);					//TVOC��λ����
	dat <<= 8;
	dat += SGP30_IIC_Read_Byte(1);					//TVOC��λ����
	
	crc = SGP30_IIC_Read_Byte(0); 					//CRCУ��ֵ
	SGP30_IIC_Stop();
	
	return(dat);
}

/****
*******SGP30��ʼ������
*****/
void SGP30_Init(void)
{
	SGP30_WriteOneByte(0x20,0x03);
}

/****
*******SGP30��ȡCO2��TVOCֵ����
*****/
void SGP30_Get_Co2_Tvoc_Value(uint16_t *co2_value, uint16_t *tvoc_value)
{
	uint32_t sgp30_value = 0;
	
	SGP30_WriteOneByte(0x20,0x08);
	sgp30_value = SGP30_Read_Data();
	*co2_value = (sgp30_value & 0xffff0000) >> 16;
	*tvoc_value = sgp30_value & 0x0000ffff;
}
 
