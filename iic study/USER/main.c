/******************** (C) COPYRIGHT 2017 shen hui xiang **************************
 * �ļ���  ��main.c
 * ����    ��ѧϰiic������д������iic.c��main.c�����Լ���д������ֲ��Ұ����������ֲ������ԭ�Ӵ��롣         
 * ʵ��ƽ̨��ԭ�ӿ�����
 * ��汾  ��ST3.5.0
 *
 * ����    �������
**********************************************************************************/
#include "stm32f10x.h"
#include "led.h"
#include "usart1.h"
#include "delay.h"
#include "iic.h"
/* 
 * ��������main
 * ����  : ������
 * ����  ����
 * ���  : ��
 */
int main(void)
{
	u8 iic_buf=0;
	 USART1_Config();
     delay_init();
	 iic_init();
	 
	
	 iic_start();
	 iic_byte_write(0xa0);
	 iic_wait_ack();
	 iic_byte_write(3);
	 iic_wait_ack();
	 iic_byte_write('a');
	 iic_wait_ack();
	 iic_stop();
	 delay_ms(10);
	
	 iic_start(); 
	 iic_byte_write(0xa0);
	 iic_wait_ack();
	 iic_byte_write(3);
	 iic_wait_ack();
	
	 iic_start();
	 iic_byte_write(0xa1);
	 iic_wait_ack();
	 iic_buf=iic_byte_read(0);
	 iic_stop();
	
  	 while(1)
	 {
		 printf("%c",iic_buf);
		 delay_ms(500);
	 };
}
/******************* (C) COPYRIGHT 2017 shen hui xiang *****END OF FILE************/


