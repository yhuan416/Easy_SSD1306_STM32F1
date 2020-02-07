#ifndef _EASY_BITMAP_H_
#define _EASY_BITMAP_H_

#include "fonts.h"

//配置显示缓冲区的大小 (bit)
#define GRAM_W	(128)
#define GRAM_H	(64)

//显示一个点
extern void bitmap_DrawPixel(unsigned char *gram, unsigned int x, unsigned int y, unsigned char mask);

//显示一个字节
extern void bitmap_DrawChar(unsigned char *gram, int x, int y, char ch, _FontDef *font);

#endif
