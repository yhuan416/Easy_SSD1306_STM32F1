#ifndef _FONTS_H_
#define _FONTS_H_

/*

字符(偏移量 32/[ch - ' ']):
( !"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\]^_`abcdefghijklmnopqrstuvwxyz{|}~)

使用Pctolcd2002软件进行取模

阴码/列行/逆向/十六进制/C51

可以参考font8_16.c/font8_16.h

*/

typedef struct
{
	unsigned char FontWidth;//字体宽度
	unsigned char FontHeight;//字体高度
	
	unsigned char FontSize;//每个字符占用的大小
	const unsigned char *data;//字体数据
} _FontDef;

#endif
