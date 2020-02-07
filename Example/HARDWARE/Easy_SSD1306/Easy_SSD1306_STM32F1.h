/*
ssd1306 --- stm32f1

ʹ��spi1��ssd1306���в���

��Ҫ���ⲿ�����ݽ��г�ʼ��

���������ﶨ��RES DC CS������

Ҳ������Դ�ļ���
ssd1306_reset/ssd1306_write_cmd/ssd1306_write_data
������������������

ʹ����bitmapģ��Ի�����в���

��������fonts.h�ļ�
*/
#ifndef _EASY_SSD1306_STM32F1_H_
#define _EASY_SSD1306_STM32F1_H_

#include "stm32f10x.h"

/* �ֿ� */
#include "font8_16.h"//8x16�ֿ�
#include "font6_12.h"//6x12�ֿ�
#include "font7_14.h"//7x14�ֿ�
#include "font12_24.h"//12x24�ֿ�
#include "font16_32.h"//16x32�ֿ�

//������Ļ�ߴ�
#define SSD1306_12864 /* 128 x 64 */
//#define SSD1306_12832 /* 128 x 32 */ // can not use

/* ���º궨��Ϊ��ѡ */
//����ʹ�õ�SPI�˿ں�
#define SSD1306_SPI_PORT	SPI1

//����RES�˿ں�����
#define SSD1306_RES_PORT 	GPIOA
#define SSD1306_RES_PIN	 	GPIO_Pin_4

//����DCʹ�õĶ˿ں�����
#define SSD1306_DC_PORT 	GPIOA
#define SSD1306_DC_PIN	 	GPIO_Pin_1

//����CSʹ�õĶ˿ں�����
#define SSD1306_CS_PORT 	GPIOA
#define SSD1306_CS_PIN	 	GPIO_Pin_8
/* ���Ϻ궨��Ϊ��ѡ */

/* SSD1306 ctrl struct */
typedef struct 
{
	unsigned char Width;
	unsigned char Height;
	
	_FontDef *cFont;
} _SSD1306;

/* ���õ�ǰ���� */
extern void ssd1306_SetFont(_FontDef *Font);

/* ˢ�»����� */
extern void ssd1306_RefreshGram(void);

/* ��ջ����� */
extern void ssd1306_Clear(void);

/* д���ݵ������� */
extern void ssd1306_DrawChar(int x, int y, unsigned char ch);
extern void ssd1306_DrawString(int x, int y, const char *str);

/* ��ʼ��SSD1306 */
extern void ssd1306_Init(void);

#endif
