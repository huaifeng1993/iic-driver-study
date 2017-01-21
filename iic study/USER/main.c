/******************** (C) COPYRIGHT 2017 shen hui xiang **************************
 * 文件名  ：main.c
 * 描述    ：学习iic驱动编写，除了iic.c和main.c是我自己编写串口移植的野火其他的移植的正点原子代码。         
 * 实验平台：原子开发板
 * 库版本  ：ST3.5.0
 *
 * 作者    ：沈慧想
**********************************************************************************/
#include "stm32f10x.h"
#include "led.h"
#include "usart1.h"
#include "delay.h"
#include "iic.h"
/* 
 * 函数名：main
 * 描述  : 主函数
 * 输入  ：无
 * 输出  : 无
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


