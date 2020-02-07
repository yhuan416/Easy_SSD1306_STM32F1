#include "Easy_Bitmap.h"

//防止未定义错误
#ifndef GRAM_W
#define GRAM_W	(128)
#endif

//防止未定义错误
#ifndef GRAM_H
#define GRAM_H	(64)
#endif

//画点
void bitmap_DrawPixel(unsigned char *gram, unsigned int x, unsigned int y, unsigned char mask)
{
    //判断是否越界
    if(x >= GRAM_W || y >= GRAM_H) return;

    //y轴反向
    y = GRAM_H - y - 1;

    //找到需要操作的字节
    if(mask) 	gram[x + (y/8) * GRAM_W] |=  (1 << (y % 8));
    else 		gram[x + (y/8) * GRAM_W] &= ~(1 << (y % 8));
}

//显示一个字符
void bitmap_DrawChar(unsigned char *gram, int x, int y, char ch, _FontDef *font)
{
    const unsigned char *fontOffset;
	int xOffset, yOffset;
	unsigned int i, j, k;
	unsigned int bits;//当前字节的有效位数
    unsigned char temp;
	
	int Lbytes;//当前字体纵向占用的字节数

    //判断是否是合法字符
    if(ch < ' ' || ch > '~') return;

    fontOffset = font->data + ((ch - ' ') * font->FontSize);//获取字符偏移量
	
	Lbytes = font->FontSize / font->FontWidth;//获取当前字体在竖直方向上占用的字节数
	
	for(i = 0; i < Lbytes; i++)//一排一排的遍历
	{
		bits = font->FontHeight - (i * 8);//当前行字符的有效位
		bits = (bits > 8) ? (8) : (bits);
		
		yOffset = y + (i * 8);//当前字节的y偏移量
		
		for(j = 0; j < font->FontWidth; j++)
		{
			xOffset = x + j;//当前字节的x偏移量
			if(xOffset < 0 || xOffset >= GRAM_W) continue;//判断当前列是否越界
			
			temp = fontOffset[i * font->FontWidth + j];//拿出当前字节
			
			for(k = 0; k < bits; k++)
			{
				bitmap_DrawPixel(gram, xOffset, yOffset + k, temp & 0x01);
				temp = temp >> 1;
			}
		}
	}
	
/*
    for(i = 0; i < font->FontSize; i++)//拿出每一个数据
    {
        temp = fontOffset[i];//拿出当前字节

        
        yOffset = y + ((i / font->FontWidth) * 8);

        bits = font->FontHeight - ((i/font->FontWidth) * 8);//当前字符的有效位
		bits = (bits > 8) ? (8) : (bits);

        for(j = 0; j < bits; j++)
        {
            bitmap_DrawPixel(gram, xOffset, yOffset + j, temp&0x01);
            temp = temp >> 1;
        }
    }
	*/
}
