#include "sys.h"
#include "delay.h"
#include "usart.h"

#include "Easy_SSD1306_STM32F1.h"

void Init(void)
{
	NVIC_SetPriorityGrouping(NVIC_PriorityGroup_2);//�����жϷ���
	delay_init();//ϵͳ��ʱ��ʼ��
	uart_init(115200);//����1��ʼ��
	
	ssd1306_Init();
	
	ssd1306_SetFont(&Font_12x24);
}

int main(void)
{	
	u8 i = 0;
	Init();
	
	while(1)
	{
		ssd1306_SetFont(&Font_6x12);
		ssd1306_DrawChar(0, 0, i + 32);
		ssd1306_SetFont(&Font_8x16);
		ssd1306_DrawChar(6, 0, i + 32);
		ssd1306_SetFont(&Font_12x24);
		ssd1306_DrawChar(14, 0, i + 32);
		ssd1306_SetFont(&Font_16x32);
		ssd1306_DrawChar(26, 0, i + 32);
		
		ssd1306_RefreshGram();
		
		i++;
		if(i > '~' - ' ') i = 0;
		
		delay_ms(1000);
	}
	
}
