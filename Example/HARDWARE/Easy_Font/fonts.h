#ifndef _FONTS_H_
#define _FONTS_H_

/*

�ַ�(ƫ���� 32/[ch - ' ']):
( !"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\]^_`abcdefghijklmnopqrstuvwxyz{|}~)

ʹ��Pctolcd2002�������ȡģ

����/����/����/ʮ������/C51

���Բο�font8_16.c/font8_16.h

*/

typedef struct
{
	unsigned char FontWidth;//������
	unsigned char FontHeight;//����߶�
	
	unsigned char FontSize;//ÿ���ַ�ռ�õĴ�С
	const unsigned char *data;//��������
} _FontDef;

#endif
