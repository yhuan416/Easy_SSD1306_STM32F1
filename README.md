**2020.2.7**  
**Author : [YHUAN](https://github.com/yhuan416)**  
**简易 STM32 SSD1306 OLED 模块库**  

# 使用说明

该库使用了[Easy_Bitmap](https://github.com/yhuan416/Easy_Bitmap)库对数据缓冲区进行操作

需要自行实现通信引脚的初始化并根据实际情况实现操作函数


# 使用前的配置

1. 定义屏幕尺寸  
```
	#define SSD1306_12864 /* 128 x 64 */
```

2. 根据实际情况自行初始化相关的通信引脚  
```
	static void _init(void);
```
> ps:该函数只是例子,具体实现可以自行实现

3. 根据实际情况实现以下三个函数  
```
	static void ssd1306_reset(void);
	static void ssd1306_write_cmd(unsigned char cmd);
	static void ssd1306_write_data(unsigned char *data, unsigned int size);
```

4. 实现相关的打印函数  
```
	void ssd1306_DrawChar(int x, int y, unsigned char ch);
	void ssd1306_DrawString(int x, int y, const char *str);
```
> ps:以上两个函数已经实现了,可以参考并实现别的函数接口

5. 调用函数操作缓存区并刷新显示
```
	extern void ssd1306_RefreshGram(void);
```
---

