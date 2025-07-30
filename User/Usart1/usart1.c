#include "Usart1.h"

/**
 * @brief 初始化 USART1（PA9 TX, PA10 RX）
 * 
 * 配置波特率 9600，8位数据，无校验，1停止位，无硬件流控
 */
void Usart1_Init(void) {
	GPIO_InitTypeDef gpio_initstruct;
	USART_InitTypeDef usart_initstruct;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

	// USART1 TX 引脚 PA9，复用推挽输出
	gpio_initstruct.GPIO_Mode = GPIO_Mode_AF_PP;
	gpio_initstruct.GPIO_Pin = GPIO_Pin_9;
	gpio_initstruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &gpio_initstruct);

	// USART1 RX 引脚 PA10，浮空输入
	gpio_initstruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	gpio_initstruct.GPIO_Pin = GPIO_Pin_10;
	GPIO_Init(GPIOA, &gpio_initstruct);

	// // USART1 参数配置
	usart_initstruct.USART_BaudRate = 9600;
	usart_initstruct.USART_WordLength = USART_WordLength_8b;
	usart_initstruct.USART_Parity = USART_Parity_No;
	usart_initstruct.USART_StopBits = USART_StopBits_1;
	usart_initstruct.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
	usart_initstruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_Init(USART1, &usart_initstruct);

	//USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);    //需要中断时写该语句

	// 使能 USART1
	USART_Cmd( USART1, ENABLE);
}

/**
 * @brief 发送一个字节数据
 * @param pUSARTx USART外设指针 (如 USART1)
 * @param Data 要发送的数据字节
 */
void Usart_Send_Byte(USART_TypeDef* pUSARTx, uint8_t Data) {
	USART_SendData( pUSARTx,  Data);
	while(USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);
}

/**
 * @brief 发送一个16位数据（高8位先发，低8位后发）
 * @param pUSARTx USART外设指针
 * @param Data 要发送的16位数据
 */
void Usart_Send_Word(USART_TypeDef* pUSARTx, uint16_t Data) {
	uint8_t temph, templ;

	templ=(Data&0x00FF);
	temph=(Data&0xFF00) >> 8;

	USART_SendData( pUSARTx, temph);
	while(USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);

	USART_SendData( pUSARTx, templ);
	while(USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);
}

/**
 * @brief 发送指定长度的字节数组
 * @param pUSARTx USART外设指针
 * @param p 指向数据数组的指针
 * @param sum 要发送的字节数
 */
void Usart_Send_Array(USART_TypeDef* pUSARTx, uint8_t* p, uint8_t sum) {
	uint8_t i;
	for(i = 0;i < sum; i++) {
		USART_SendData( pUSARTx, *(p + i));
		while(USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);
	}
}

/**
 * @brief 重定义 fputc，用于printf重定向到USART1
 * @param ch 发送的字符
 * @param f 文件指针
 * @return 发送的字符
 */
int fputc(int ch, FILE *f) {      
	while((USART1->SR&0X40) == 0); //等待发送缓冲区空
    USART1->DR = (u8) ch;      
	return ch;
}

/**
 * @brief 发送以'\0'结尾的字符串
 * @param pUSARTx USART外设指针
 * @param p 字符串指针
 */
void Usart_Send_String(USART_TypeDef* pUSARTx, uint8_t* p) {
	uint8_t i = 0;
	do {
		USART_SendData( pUSARTx, *(p + i));
		while(USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);
			i++;
	} while(*(p + i) != '\0');
}