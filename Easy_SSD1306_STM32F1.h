/*
ssd1306 --- stm32f1

使用spi1对ssd1306进行操作

需要在外部对数据进行初始化

可以在这里定义RES DC CS等引脚

也可以在源文件对
ssd1306_reset/ssd1306_write_cmd/ssd1306_write_data
这三个函数进行配置

使用了bitmap模块对缓存进行操作

字体库详见fonts.h文件
*/
#ifndef _EASY_SSD1306_STM32F1_H_
#define _EASY_SSD1306_STM32F1_H_

#include "stm32f10x.h"

/* 字库 */
#include "font8_16.h"//8x16字库
#include "font6_12.h"//6x12字库
#include "font7_14.h"//7x14字库
#include "font12_24.h"//12x24字库
#include "font16_32.h"//16x32字库

//定义屏幕尺寸
#define SSD1306_12864 /* 128 x 64 */
//#define SSD1306_12832 /* 128 x 32 */ // can not use

/* 以下宏定义为可选 */
//定义使用的SPI端口号
#define SSD1306_SPI_PORT	SPI1

//定义RES端口和引脚
#define SSD1306_RES_PORT 	GPIOA
#define SSD1306_RES_PIN	 	GPIO_Pin_4

//定义DC使用的端口和引脚
#define SSD1306_DC_PORT 	GPIOA
#define SSD1306_DC_PIN	 	GPIO_Pin_1

//定义CS使用的端口和引脚
#define SSD1306_CS_PORT 	GPIOA
#define SSD1306_CS_PIN	 	GPIO_Pin_8
/* 以上宏定义为可选 */

/* SSD1306 ctrl struct */
typedef struct 
{
	unsigned char Width;
	unsigned char Height;
	
	_FontDef *cFont;
} _SSD1306;

/* 设置当前字体 */
extern void ssd1306_SetFont(_FontDef *Font);

/* 刷新缓存区 */
extern void ssd1306_RefreshGram(void);

/* 清空缓冲区 */
extern void ssd1306_Clear(void);

/* 写数据到缓存中 */
extern void ssd1306_DrawChar(int x, int y, unsigned char ch);
extern void ssd1306_DrawString(int x, int y, const char *str);

/* 初始化SSD1306 */
extern void ssd1306_Init(void);

#endif
