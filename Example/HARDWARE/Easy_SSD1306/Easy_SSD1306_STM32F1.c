//使用SPI对OLED进行操作
#include "Easy_SSD1306_STM32F1.h"

/* 点阵图操作库 */
#include "Easy_Bitmap.h"

#ifdef SSD1306_12864

#define SSD1306_W (128)
#define SSD1306_H (64)

#elif SSD1306_12832

#define SSD1306_W (128)
#define SSD1306_H (32)

#endif

//显示缓存
static unsigned char OLED_GRAM[SSD1306_W * SSD1306_H / 8];

//ssd1306操作结构体
static _SSD1306 ssd1306 = {SSD1306_W, SSD1306_H, &Font_8x16};//ssd1306操作结构体

static void ssd1306_reset(void)//复位
{
	SSD1306_CS_PORT->BSRR = SSD1306_CS_PIN;//拉高片选
	
	SSD1306_RES_PORT->BRR = SSD1306_RES_PIN;//拉低复位
	//SSD1306_DELAY_US(10);
	SSD1306_RES_PORT->BSRR = SSD1306_RES_PIN;//拉高复位
}

static void ssd1306_write_cmd(unsigned char cmd)//写指令
{
	SSD1306_DC_PORT->BRR = SSD1306_DC_PIN;//写指令
	SSD1306_CS_PORT->BRR = SSD1306_CS_PIN;//拉低片选

	SSD1306_SPI_PORT->DR = cmd;//写数据
	
	//SSD1306_DC_PORT->BSRR = SSD1306_DC_PIN;//写了不行
	SSD1306_CS_PORT->BSRR = SSD1306_CS_PIN;//拉高片选
}

static void ssd1306_write_data(unsigned char *data, unsigned int size)//写数据
{
	unsigned int i;
	
	SSD1306_DC_PORT->BSRR = SSD1306_DC_PIN;//写数据
	SSD1306_CS_PORT->BRR = SSD1306_CS_PIN;//拉低片选
	
	for(i = 0; i < size; i++)
	{
		SSD1306_SPI_PORT->DR = data[i];//写数据
	}
	
	SSD1306_CS_PORT->BSRR = SSD1306_CS_PIN;//拉高片选
	SSD1306_DC_PORT->BSRR = SSD1306_DC_PIN;
}

//m^n函数
static u32 ssd1306_pow(u8 m,u8 n)
{
	u32 result=1;
	while(n--)result*=m;
	return result;
}

//设置当前字体
void ssd1306_SetFont(_FontDef *Font)
{
	ssd1306.cFont = Font;
}

//刷新数据
void ssd1306_RefreshGram(void)
{
	ssd1306_write_cmd(0x21);    	//设置列起始值与终止值
	ssd1306_write_cmd(0x00);      	
	ssd1306_write_cmd(0x7F);      	  
	ssd1306_write_cmd(0x22);		//设置行起始值与终止值
	ssd1306_write_cmd(0x00);
	ssd1306_write_cmd(0x07);
	
	ssd1306_write_data(OLED_GRAM, SSD1306_W * SSD1306_H/8);
}

//清屏函数	  
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
	ssd1306_write_cmd(0xAE); //关闭显示
	
	ssd1306_write_cmd(0xD5); //设置时钟分频因子,震荡频率
	ssd1306_write_cmd(0x80);   //[3:0],分频因子;[7:4],震荡频率
	ssd1306_write_cmd(0xA8); //设置驱动路数
	ssd1306_write_cmd(0X3F); //默认0X3F(1/64) 
	
	ssd1306_write_cmd(0xD3); //设置显示偏移
	ssd1306_write_cmd(0X00); //默认为0

	ssd1306_write_cmd(0x40); //设置显示开始行 [5:0],行数.
													    
	ssd1306_write_cmd(0x8D); //电荷泵设置
	ssd1306_write_cmd(0x14); //bit2，开启/关闭
	ssd1306_write_cmd(0x20); //设置内存地址模式
	ssd1306_write_cmd(0x00); //[1:0],00，列地址模式;01，行地址模式;10,页地址模式;默认10;
	
	ssd1306_write_cmd(0xA1); //段重定义设置,bit0:0,0->0;1,0->127;
	ssd1306_write_cmd(0xC0); //设置COM扫描方向;bit3:0,普通模式;1,重定义模式 COM[N-1]->COM0;N:驱动路数
	ssd1306_write_cmd(0xDA); //设置COM硬件引脚配置
	ssd1306_write_cmd(0x12); //[5:4]配置
		 
	ssd1306_write_cmd(0x81); //对比度设置
	ssd1306_write_cmd(0xEF); //1~255;默认0X7F (亮度设置,越大越亮)
	ssd1306_write_cmd(0xD9); //设置预充电周期
	ssd1306_write_cmd(0xf1); //[3:0],PHASE 1;[7:4],PHASE 2;
	ssd1306_write_cmd(0xDB); //设置VCOMH 电压倍率
	ssd1306_write_cmd(0x30); //[6:4] 000,0.65*vcc;001,0.77*vcc;011,0.83*vcc;

	ssd1306_write_cmd(0xA4); //全局显示开启;bit0:1,开启;0,关闭;(白屏/黑屏)
	ssd1306_write_cmd(0xA6); //设置显示方式;bit0:1,反相显示;0,正常显示	    						   
	ssd1306_write_cmd(0xAF); //开启显示
}

//需要实现的引脚初始化
static void _init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	SPI_InitTypeDef SPI_InitStructure;
 	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO | RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
	
	/* SPI引脚初始化 */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	/* OLED引脚初始化 */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_4 | GPIO_Pin_8;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	/* 拉高 */
	GPIO_SetBits(GPIOA, GPIO_Pin_1 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_7 | GPIO_Pin_8);
	
	/* 初始化SPI1 */
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
	
	SPI_Cmd(SPI1, ENABLE);//使能SPI
}

//初始化SSD1306					    
void ssd1306_Init(void)
{
	_init();
	
	ssd1306_reset();
	
	SSD1306_Config();

	ssd1306_Clear();
	ssd1306_RefreshGram();
}
