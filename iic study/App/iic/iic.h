/******************** (C) COPYRIGHT 2017 shen hui xiang **************************
 * �ļ���  ��iic.h
 * ����    ��iic�����ļ���д����������ԭ�ӵ�iic�����ļ������ļ�������ѧϰiic���Լ���д������˼·�ο���ԭ�ӵ�iic����       
 * ʵ��ƽ̨��ԭ�ӿ�����mini��
 * ��汾  ��ST3.5.0
 * ����    ��2017
 * ����    �������
**********************************************************************************/
#ifndef __IIC__H_
#define __IIC__H_
#include "delay.h"

#define IIC_SCL_Pin  GPIO_Pin_12
#define IIC_SDA_Pin  GPIO_Pin_11
#define GPIO_IIC     GPIOC

#define IIC_SDA_OUT()  {GPIOC->CRH&=0XFFFF0FFF;GPIOC->CRH|=3<<12;}//����ģʽ������������ģʽ
#define IIC_SDA_IN()   {GPIOC->CRH&=0XFFFF0FFF;GPIOC->CRH|=8<<12;}//ͨ���������50MZ

#define SDA_PIN_OUT       PCout(11)
#define SCL_PIN_OUT       PCout(12)
#define SDA_PIN_IN        PCin(11)

void iic_init(void);
void iic_start(void);
void iic_stop(void);
u8 iic_wait_ack(void);
void iic_byte_write(u8 buf);
u8 iic_byte_read(unsigned char ask);
#endif