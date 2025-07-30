#include "Usart1.h"

/**
 * @brief ��ʼ�� USART1��PA9 TX, PA10 RX��
 * 
 * ���ò����� 9600��8λ���ݣ���У�飬1ֹͣλ����Ӳ������
 */
void Usart1_Init(void) {
	GPIO_InitTypeDef gpio_initstruct;
	USART_InitTypeDef usart_initstruct;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

	// USART1 TX ���� PA9�������������
	gpio_initstruct.GPIO_Mode = GPIO_Mode_AF_PP;
	gpio_initstruct.GPIO_Pin = GPIO_Pin_9;
	gpio_initstruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &gpio_initstruct);

	// USART1 RX ���� PA10����������
	gpio_initstruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	gpio_initstruct.GPIO_Pin = GPIO_Pin_10;
	GPIO_Init(GPIOA, &gpio_initstruct);

	// // USART1 ��������
	usart_initstruct.USART_BaudRate = 9600;
	usart_initstruct.USART_WordLength = USART_WordLength_8b;
	usart_initstruct.USART_Parity = USART_Parity_No;
	usart_initstruct.USART_StopBits = USART_StopBits_1;
	usart_initstruct.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
	usart_initstruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_Init(USART1, &usart_initstruct);

	//USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);    //��Ҫ�ж�ʱд�����

	// ʹ�� USART1
	USART_Cmd( USART1, ENABLE);
}

/**
 * @brief ����һ���ֽ�����
 * @param pUSARTx USART����ָ�� (�� USART1)
 * @param Data Ҫ���͵������ֽ�
 */
void Usart_Send_Byte(USART_TypeDef* pUSARTx, uint8_t Data) {
	USART_SendData( pUSARTx,  Data);
	while(USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);
}

/**
 * @brief ����һ��16λ���ݣ���8λ�ȷ�����8λ�󷢣�
 * @param pUSARTx USART����ָ��
 * @param Data Ҫ���͵�16λ����
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
 * @brief ����ָ�����ȵ��ֽ�����
 * @param pUSARTx USART����ָ��
 * @param p ָ�����������ָ��
 * @param sum Ҫ���͵��ֽ���
 */
void Usart_Send_Array(USART_TypeDef* pUSARTx, uint8_t* p, uint8_t sum) {
	uint8_t i;
	for(i = 0;i < sum; i++) {
		USART_SendData( pUSARTx, *(p + i));
		while(USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);
	}
}

/**
 * @brief �ض��� fputc������printf�ض���USART1
 * @param ch ���͵��ַ�
 * @param f �ļ�ָ��
 * @return ���͵��ַ�
 */
int fputc(int ch, FILE *f) {      
	while((USART1->SR&0X40) == 0); //�ȴ����ͻ�������
    USART1->DR = (u8) ch;      
	return ch;
}

/**
 * @brief ������'\0'��β���ַ���
 * @param pUSARTx USART����ָ��
 * @param p �ַ���ָ��
 */
void Usart_Send_String(USART_TypeDef* pUSARTx, uint8_t* p) {
	uint8_t i = 0;
	do {
		USART_SendData( pUSARTx, *(p + i));
		while(USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);
			i++;
	} while(*(p + i) != '\0');
}