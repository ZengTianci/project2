
#include "sgp30.h"
#include "delay.h"


/****范例
uint16_t co2_value = 0;								//CO2值
uint16_t tvoc_value = 0;							//TVOC值

SGP30_Init();												//SGP30初始化

SGP30_Get_Co2_Tvoc_Value(&co2_value, &tvoc_value);		//获取CO2和TVOC值
*****/

/****
*******SGP30引脚输出配置
*****/
void SGP30_GPIO_OUT(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(SGP30_SCL_GPIO_CLK_ENABLE, ENABLE);	 	//使能端口时钟
	GPIO_InitStructure.GPIO_Pin = SGP30_SCL_PIN;									//引脚配置
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 						//推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 						//IO口速度为50MHz
	GPIO_Init(SGP30_SCL_PORT, &GPIO_InitStructure);					 			//根据设定参数初始化
	
	RCC_APB2PeriphClockCmd(SGP30_SDA_GPIO_CLK_ENABLE, ENABLE);	 	//使能端口时钟
	GPIO_InitStructure.GPIO_Pin = SGP30_SDA_PIN;				 					//引脚配置
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 						//推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 						//IO口速度为50MHz
	GPIO_Init(SGP30_SDA_PORT, &GPIO_InitStructure);					 			//根据设定参数初始化
}

/****
*******SGP30引脚输入配置
*****/
void SGP30_GPIO_IN(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(SGP30_SCL_GPIO_CLK_ENABLE, ENABLE);	 	//使能端口时钟
	GPIO_InitStructure.GPIO_Pin = SGP30_SCL_PIN;									//引脚配置
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 						//推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 						//IO口速度为50MHz
	GPIO_Init(SGP30_SCL_PORT, &GPIO_InitStructure);					 			//根据设定参数初始化
	
	RCC_APB2PeriphClockCmd(SGP30_SDA_GPIO_CLK_ENABLE, ENABLE);	 	//使能端口时钟
	GPIO_InitStructure.GPIO_Pin = SGP30_SDA_PIN;				 					//引脚配置
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		 							//设置成上拉输入
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 						//IO口速度为50MHz
	GPIO_Init(SGP30_SDA_PORT, &GPIO_InitStructure);					 			//根据设定参数初始化
}

/****
*******产生SGP30_IIC起始信号
*****/
void SGP30_IIC_Start(void)
{
	SGP30_GPIO_OUT();     //sda线输出
	SGP30_SDA_OUT=1;	  	  
	SGP30_SCL=1;
	Delay_us(4);
 	SGP30_SDA_OUT=0;
	Delay_us(4);
	SGP30_SCL=0;					//钳住I2C总线，准备发送或接收数据 
}

/****
*******产生SGP30_IIC停止信号
*****/
void SGP30_IIC_Stop(void)
{
	SGP30_GPIO_OUT();			//sda线输出
	SGP30_SCL=0;
	SGP30_SDA_OUT=0;
 	Delay_us(4);
	SGP30_SCL=1; 
	SGP30_SDA_OUT=1;			//发送I2C总线结束信号
	Delay_us(4);							   	
}

/****
*******等待应答信号到来
返回值：1，接收应答失败
        0，接收应答成功
*****/
uint8_t SGP30_IIC_Wait_Ack(void)
{
	uint8_t ucErrTime=0;
	
	SGP30_GPIO_IN();      //SDA设置为输入  
	SGP30_SDA_OUT=1;
	Delay_us(1);	   
	SGP30_SCL=1;
	Delay_us(1);
	
	while(SGP30_SDA_IN)   //IO口数据读入
	{
		ucErrTime++;
		if(ucErrTime > 250)
		{
			SGP30_IIC_Stop();
			return 1;
		}
	}
	
	SGP30_SCL=0;//时钟输出0 	   

	return 0;  
}

/****
*******产生ACK应答
*****/
void SGP30_IIC_Ack(void)
{
	SGP30_SCL=0;
	SGP30_GPIO_OUT();	//释放一个数据线时，ACK应答信号为0时
	SGP30_SDA_OUT=0;		//发送成功
	Delay_us(2);
	SGP30_SCL=1;
	Delay_us(2);
	SGP30_SCL=0;
}

/****
*******不产生ACK应答
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
*******SGP30_IIC发送一个字节
			返回从机有无应答
			1，有应答
			0，无应答	
*****/
//		  
void SGP30_IIC_Send_Byte(uint8_t txd)
{                        
	uint8_t t;   
	SGP30_GPIO_OUT(); 	//数据输出
	SGP30_SCL=0;				//拉低时钟开始数据传输
	for(t=0; t<8; t++)
	{              
		SGP30_SDA_OUT = (txd&0x80)>>7;		//io口数据输出
		txd<<=1; 	  
		Delay_us(2);

		SGP30_SCL=1;
		Delay_us(2); 
		SGP30_SCL=0;	
		Delay_us(2);
	}	 
}

/****
*******读1个字节，ack=1时，发送ACK，ack=0，发送nACK 
*****/
uint8_t SGP30_IIC_Read_Byte(uint8_t ack)
{
	unsigned char i,receive=0;
	SGP30_GPIO_IN();						//SDA设置为输入
  for(i=0; i<8; i++ )
	{
		SGP30_SCL=0; 
		Delay_us(2);

		SGP30_SCL=1;
		receive<<=1;

		if(SGP30_SDA_IN) 				 	//如果数据输出了，读取一个字节
			receive++;
		
		Delay_us(1); 
  }
	
	if(!ack)
		SGP30_IIC_NAck();					//发送nACK
	else
		SGP30_IIC_Ack(); 					//发送ACK   

   return receive;
}


/****
在SGP30指定地址读出一个数据
ReadAddr:开始读数的地址  
返回值  :读到的数
*****/
uint8_t SGP30_ReadOneByte(uint16_t ReadAddr)
{				  
	uint8_t data=0;
	
	SGP30_IIC_Start();
	
	SGP30_IIC_Send_Byte(SGP30_IIC_Address);	   	//发送写命令
	SGP30_IIC_Wait_Ack();

	SGP30_IIC_Send_Byte(ReadAddr);   							//发送地址
	SGP30_IIC_Wait_Ack();
	
	SGP30_IIC_Start();
	
	SGP30_IIC_Send_Byte(SGP30_IIC_Address+1);   //进入接收模式			   
	SGP30_IIC_Wait_Ack();
	
	data = SGP30_IIC_Read_Byte(0);		   
	SGP30_IIC_Stop();															//产生一个停止条件
	
	return data;
}

/****
//在SGP30指定地址写入一个数据
//WriteAddr  :写入数据的目的地址    
//DataToWrite:要写入的数据
*****/
void SGP30_WriteOneByte(uint16_t WriteAddr,uint8_t DataToWrite)
{				   	  	    																 
	SGP30_IIC_Start();
  
	SGP30_IIC_Send_Byte(SGP30_IIC_Address);	    //发送写命令
	SGP30_IIC_Wait_Ack();
	
	SGP30_IIC_Send_Byte(WriteAddr);   						//发送低地址
	SGP30_IIC_Wait_Ack(); 	 
	
	SGP30_IIC_Send_Byte(DataToWrite);     				//发送字节							   
	SGP30_IIC_Wait_Ack();
	
	SGP30_IIC_Stop();															//产生一个停止条件 
	Delay_ms(100);
}

/****
*******从SGP30的地址address中读取一个字节的数据
*****/
uint32_t SGP30_Read_Data()
{
	uint32_t dat;
	uint16_t crc;
	
	SGP30_IIC_Start();
	SGP30_IIC_Send_Byte(SGP30_IIC_Address + 1);
	SGP30_IIC_Wait_Ack();
	
	dat = SGP30_IIC_Read_Byte(1);						//CO2高位数据
	dat <<= 8;
	dat += SGP30_IIC_Read_Byte(1);					//CO2低位数据
	
	crc = SGP30_IIC_Read_Byte(1); 					//CRC校验值
	crc = crc;  														//为了不让出现编译警告
	
	dat <<= 8;
	dat += SGP30_IIC_Read_Byte(1);					//TVOC高位数据
	dat <<= 8;
	dat += SGP30_IIC_Read_Byte(1);					//TVOC低位数据
	
	crc = SGP30_IIC_Read_Byte(0); 					//CRC校验值
	SGP30_IIC_Stop();
	
	return(dat);
}

/****
*******SGP30初始化函数
*****/
void SGP30_Init(void)
{
	SGP30_WriteOneByte(0x20,0x03);
}

/****
*******SGP30获取CO2和TVOC值函数
*****/
void SGP30_Get_Co2_Tvoc_Value(uint16_t *co2_value, uint16_t *tvoc_value)
{
	uint32_t sgp30_value = 0;
	
	SGP30_WriteOneByte(0x20,0x08);
	sgp30_value = SGP30_Read_Data();
	*co2_value = (sgp30_value & 0xffff0000) >> 16;
	*tvoc_value = sgp30_value & 0x0000ffff;
}
 
