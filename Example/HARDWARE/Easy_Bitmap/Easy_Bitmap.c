#include "Easy_Bitmap.h"

//��ֹδ�������
#ifndef GRAM_W
#define GRAM_W	(128)
#endif

//��ֹδ�������
#ifndef GRAM_H
#define GRAM_H	(64)
#endif

//����
void bitmap_DrawPixel(unsigned char *gram, unsigned int x, unsigned int y, unsigned char mask)
{
    //�ж��Ƿ�Խ��
    if(x >= GRAM_W || y >= GRAM_H) return;

    //y�ᷴ��
    y = GRAM_H - y - 1;

    //�ҵ���Ҫ�������ֽ�
    if(mask) 	gram[x + (y/8) * GRAM_W] |=  (1 << (y % 8));
    else 		gram[x + (y/8) * GRAM_W] &= ~(1 << (y % 8));
}

//��ʾһ���ַ�
void bitmap_DrawChar(unsigned char *gram, int x, int y, char ch, _FontDef *font)
{
    const unsigned char *fontOffset;
	int xOffset, yOffset;
	unsigned int i, j, k;
	unsigned int bits;//��ǰ�ֽڵ���Чλ��
    unsigned char temp;
	
	int Lbytes;//��ǰ��������ռ�õ��ֽ���

    //�ж��Ƿ��ǺϷ��ַ�
    if(ch < ' ' || ch > '~') return;

    fontOffset = font->data + ((ch - ' ') * font->FontSize);//��ȡ�ַ�ƫ����
	
	Lbytes = font->FontSize / font->FontWidth;//��ȡ��ǰ��������ֱ������ռ�õ��ֽ���
	
	for(i = 0; i < Lbytes; i++)//һ��һ�ŵı���
	{
		bits = font->FontHeight - (i * 8);//��ǰ���ַ�����Чλ
		bits = (bits > 8) ? (8) : (bits);
		
		yOffset = y + (i * 8);//��ǰ�ֽڵ�yƫ����
		
		for(j = 0; j < font->FontWidth; j++)
		{
			xOffset = x + j;//��ǰ�ֽڵ�xƫ����
			if(xOffset < 0 || xOffset >= GRAM_W) continue;//�жϵ�ǰ���Ƿ�Խ��
			
			temp = fontOffset[i * font->FontWidth + j];//�ó���ǰ�ֽ�
			
			for(k = 0; k < bits; k++)
			{
				bitmap_DrawPixel(gram, xOffset, yOffset + k, temp & 0x01);
				temp = temp >> 1;
			}
		}
	}
	
/*
    for(i = 0; i < font->FontSize; i++)//�ó�ÿһ������
    {
        temp = fontOffset[i];//�ó���ǰ�ֽ�

        
        yOffset = y + ((i / font->FontWidth) * 8);

        bits = font->FontHeight - ((i/font->FontWidth) * 8);//��ǰ�ַ�����Чλ
		bits = (bits > 8) ? (8) : (bits);

        for(j = 0; j < bits; j++)
        {
            bitmap_DrawPixel(gram, xOffset, yOffset + j, temp&0x01);
            temp = temp >> 1;
        }
    }
	*/
}
