//ʹ��SPI��OLED���в���
#include "Easy_SSD1306_STM32F1.h"

/* ����ͼ������ */
#include "Easy_Bitmap.h"

#ifdef SSD1306_12864

#define SSD1306_W (128)
#define SSD1306_H (64)

#elif SSD1306_12832

#define SSD1306_W (128)
#define SSD1306_H (32)

#endif

//��ʾ����
static unsigned char OLED_GRAM[SSD1306_W * SSD1306_H / 8];

//ssd1306�����ṹ��
static _SSD1306 ssd1306 = {SSD1306_W, SSD1306_H, &Font_8x16};//ssd1306�����ṹ��

static void ssd1306_reset(void)//��λ
{
	SSD1306_CS_PORT->BSRR = SSD1306_CS_PIN;//����Ƭѡ
	
	SSD1306_RES_PORT->BRR = SSD1306_RES_PIN;//���͸�λ
	//SSD1306_DELAY_US(10);
	SSD1306_RES_PORT->BSRR = SSD1306_RES_PIN;//���߸�λ
}

static void ssd1306_write_cmd(unsigned char cmd)//дָ��
{
	SSD1306_DC_PORT->BRR = SSD1306_DC_PIN;//дָ��
	SSD1306_CS_PORT->BRR = SSD1306_CS_PIN;//����Ƭѡ

	SSD1306_SPI_PORT->DR = cmd;//д����
	
	//SSD1306_DC_PORT->BSRR = SSD1306_DC_PIN;//д�˲���
	SSD1306_CS_PORT->BSRR = SSD1306_CS_PIN;//����Ƭѡ
}

static void ssd1306_write_data(unsigned char *data, unsigned int size)//д����
{
	unsigned int i;
	
	SSD1306_DC_PORT->BSRR = SSD1306_DC_PIN;//д����
	SSD1306_CS_PORT->BRR = SSD1306_CS_PIN;//����Ƭѡ
	
	for(i = 0; i < size; i++)
	{
		SSD1306_SPI_PORT->DR = data[i];//д����
	}
	
	SSD1306_CS_PORT->BSRR = SSD1306_CS_PIN;//����Ƭѡ
	SSD1306_DC_PORT->BSRR = SSD1306_DC_PIN;
}

//m^n����
static u32 ssd1306_pow(u8 m,u8 n)
{
	u32 result=1;
	while(n--)result*=m;
	return result;
}

//���õ�ǰ����
void ssd1306_SetFont(_FontDef *Font)
{
	ssd1306.cFont = Font;
}

//ˢ������
void ssd1306_RefreshGram(void)
{
	ssd1306_write_cmd(0x21);    	//��������ʼֵ����ֵֹ
	ssd1306_write_cmd(0x00);      	
	ssd1306_write_cmd(0x7F);      	  
	ssd1306_write_cmd(0x22);		//��������ʼֵ����ֵֹ
	ssd1306_write_cmd(0x00);
	ssd1306_write_cmd(0x07);
	
	ssd1306_write_data(OLED_GRAM, SSD1306_W * SSD1306_H/8);
}

//��������	  
void ssd1306_Clear(void) 
{  
	int i;
	for(i = 0; i < 8 * 128; i++)OLED_GRAM[i]=0X00;
}			  

void ssd1306_DrawChar(int x, int y, unsigned char ch)
{
	bitmap_DrawChar(OLED_GRAM, x, y, ch, ssd1306.cFont);
}

void ssd1306_DrawString(int x, int y, const char *str)
{
	int xIndex;
	
	xIndex = x;
	while(*str >= ' ' && *str <= '~')
	{
		bitmap_DrawChar(OLED_GRAM, xIndex, y, *str, ssd1306.cFont);
		
		xIndex += ssd1306.cFont->FontWidth;
		str++;
	}
}

///////////////////////////////////////////////////////////////////////////
static void SSD1306_Config(void)
{
	ssd1306_write_cmd(0xAE); //�ر���ʾ
	
	ssd1306_write_cmd(0xD5); //����ʱ�ӷ�Ƶ����,��Ƶ��
	ssd1306_write_cmd(0x80);   //[3:0],��Ƶ����;[7:4],��Ƶ��
	ssd1306_write_cmd(0xA8); //��������·��
	ssd1306_write_cmd(0X3F); //Ĭ��0X3F(1/64) 
	
	ssd1306_write_cmd(0xD3); //������ʾƫ��
	ssd1306_write_cmd(0X00); //Ĭ��Ϊ0

	ssd1306_write_cmd(0x40); //������ʾ��ʼ�� [5:0],����.
													    
	ssd1306_write_cmd(0x8D); //��ɱ�����
	ssd1306_write_cmd(0x14); //bit2������/�ر�
	ssd1306_write_cmd(0x20); //�����ڴ��ַģʽ
	ssd1306_write_cmd(0x00); //[1:0],00���е�ַģʽ;01���е�ַģʽ;10,ҳ��ַģʽ;Ĭ��10;
	
	ssd1306_write_cmd(0xA1); //���ض�������,bit0:0,0->0;1,0->127;
	ssd1306_write_cmd(0xC0); //����COMɨ�跽��;bit3:0,��ͨģʽ;1,�ض���ģʽ COM[N-1]->COM0;N:����·��
	ssd1306_write_cmd(0xDA); //����COMӲ����������
	ssd1306_write_cmd(0x12); //[5:4]����
		 
	ssd1306_write_cmd(0x81); //�Աȶ�����
	ssd1306_write_cmd(0xEF); //1~255;Ĭ��0X7F (��������,Խ��Խ��)
	ssd1306_write_cmd(0xD9); //����Ԥ�������
	ssd1306_write_cmd(0xf1); //[3:0],PHASE 1;[7:4],PHASE 2;
	ssd1306_write_cmd(0xDB); //����VCOMH ��ѹ����
	ssd1306_write_cmd(0x30); //[6:4] 000,0.65*vcc;001,0.77*vcc;011,0.83*vcc;

	ssd1306_write_cmd(0xA4); //ȫ����ʾ����;bit0:1,����;0,�ر�;(����/����)
	ssd1306_write_cmd(0xA6); //������ʾ��ʽ;bit0:1,������ʾ;0,������ʾ	    						   
	ssd1306_write_cmd(0xAF); //������ʾ
}

//��Ҫʵ�ֵ����ų�ʼ��
static void _init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	SPI_InitTypeDef SPI_InitStructure;
 	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO | RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
	
	/* SPI���ų�ʼ�� */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	/* OLED���ų�ʼ�� */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_4 | GPIO_Pin_8;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	/* ���� */
	GPIO_SetBits(GPIOA, GPIO_Pin_1 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_7 | GPIO_Pin_8);
	
	/* ��ʼ��SPI1 */
	SPI_I2S_DeInit(SPI1);
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;
	SPI_InitStructure.SPI_CRCPolynomial = 7;
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
	SPI_Init(SPI1,&SPI_InitStructure);	
	
	SPI_Cmd(SPI1, ENABLE);//ʹ��SPI
}

//��ʼ��SSD1306					    
void ssd1306_Init(void)
{
	_init();
	
	ssd1306_reset();
	
	SSD1306_Config();

	ssd1306_Clear();
	ssd1306_RefreshGram();
}
