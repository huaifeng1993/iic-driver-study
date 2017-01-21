/******************** (C) COPYRIGHT 2017 shen hui xiang **************************
 * �ļ���  ��iic.h
 * ����    ��iic�����ļ���д����������ԭ�ӵ�iic�����ļ������ļ�������ѧϰiic���Լ���д������˼·�ο���ԭ�ӵ�iic����       
 * ʵ��ƽ̨��ԭ�ӿ�����mini��
 * ��汾  ��ST3.5.0
 * ����    ��2017
 * ����    �������
**********************************************************************************/
#include "iic.h"

/*********************************************************************************/
/*
��������iic_init
��  �ܣ�����SDA ��SCL�˿�
��  ������
����ֵ����
*/
void iic_init(void)
{
	/*****����GPIO��**************************************/
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
   
	GPIO_InitStructure.GPIO_Pin=IIC_SCL_Pin|IIC_SDA_Pin;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	
	GPIO_Init(GPIO_IIC, &GPIO_InitStructure);	
	
	/********��IIC�� SCL SDA �����ͷ�����******************/
	SDA_PIN_OUT=1;
	SCL_PIN_OUT=1;
	
}
/*
��������iic_start
��  �ܣ�����iic��������ʽ����SCL�ߵ�ƽ�ڼ佫SDA�ɸ��õ�
��  ������
����ֵ����
*/
void iic_start(void)
{
	IIC_SDA_OUT();
	SDA_PIN_OUT=1;
	delay_us(5);
	SCL_PIN_OUT=1;
	delay_us(5);
	SDA_PIN_OUT=0;
	delay_us(5);
}
/*
��������iic_stop
��  �ܣ�ֹͣ�������ݣ�ʵ�ַ�ʽ��SCL�ߵ�ƽ�ڼ佫SDA�ɵ��ø�
��  ������
����ֵ����
*/
void iic_stop(void)
{
	IIC_SDA_OUT();	
	SDA_PIN_OUT=0;
	delay_us(5);
	SCL_PIN_OUT=1;
	delay_us(5);
	SDA_PIN_OUT=1;
	delay_us(5);
}
/*
��������iic_ack
��  �ܣ����մӻ�Ӧ���źţ��ͷŵ����߶�ȡSDA�ÿ��Ƿ��и�����,
        ��һ��ʱ����Ӧ��Ĭ�Ͻ������
��  ������
����ֵ����
*/
u8 iic_wait_ack(void)
{
	u8 i=0;
	IIC_SDA_IN();
    SDA_PIN_OUT=1;delay_us(5);
	SCL_PIN_OUT=1;delay_us(5);
	while(SDA_PIN_IN)
	{
		i++;
		if(i>250) 
		{		
            iic_stop();			//���i>255�������Ӧ���źţ�iicֹͣ
			return 1;
		}
		
	}
	SCL_PIN_OUT=0;//ʱ�����0 
	return 0;
}
/*
��������iic_nask
��  �ܣ�������Ӧ���ź�
��  ������
��  �أ���
*/
void iic_nack(void)
{
	IIC_SDA_OUT();
	SCL_PIN_OUT=0;
	delay_us(5);
	SDA_PIN_OUT=1;
	delay_us(5);
	SCL_PIN_OUT=1;
	delay_us(5);
	SCL_PIN_OUT=0;
}	
/*
��������iic_ask
��  �ܣ�����askӦ��
��  ������
��  �أ���
*/
void iic_ack(void)
{
	IIC_SDA_OUT();
	SCL_PIN_OUT=0;
	delay_us(5);
	SDA_PIN_OUT=0;
	delay_us(5);
	SCL_PIN_OUT=1;
	delay_us(5);
	SCL_PIN_OUT=0;
}
/*
��������iic_bit_write
��  �ܣ�����һ���ֽ�
��  ����u8
����ֵ����
*/
void iic_byte_write(u8 buf)
{
    u8 i;
	IIC_SDA_OUT();
	for(i=1;i<=8;i++)
	{
		SCL_PIN_OUT=0;
		delay_us(5);
		SDA_PIN_OUT=(buf>>(8-i))&0x01;
		delay_us(5);
		SCL_PIN_OUT=1;
		delay_us(5);	
	}
	SCL_PIN_OUT=0;
}
/*
��������iic_bit_read
��  �ܣ�������ȡһ���ֽ�
��  ����ask
����ֵ��
*/
u8 iic_byte_read(unsigned char ask)
{
	unsigned char  i,buf=0;
	IIC_SDA_IN();
	for(i=0;i<8;i++)
	{
	   SCL_PIN_OUT=0;
	   delay_us(5);
	   SCL_PIN_OUT=1;
	   buf <<=1;
	   if(SDA_PIN_IN)
		   buf++;
	    delay_us(5);
	}
	if(!ask)
		iic_nack();
	else
		iic_ack();
	return buf;
}