#ifndef _EASY_BITMAP_H_
#define _EASY_BITMAP_H_

#include "fonts.h"

//������ʾ�������Ĵ�С (bit)
#define GRAM_W	(128)
#define GRAM_H	(64)

//��ʾһ����
extern void bitmap_DrawPixel(unsigned char *gram, unsigned int x, unsigned int y, unsigned char mask);

//��ʾһ���ֽ�
extern void bitmap_DrawChar(unsigned char *gram, int x, int y, char ch, _FontDef *font);

#endif
