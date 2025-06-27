#ifndef _USART1_H
#define	_USART1_H
#include "stm32f10x.h"
#include "stdio.h"
void Usart1_Init(void);
void Usart_Send_Byte(USART_TypeDef* pUSARTx, uint8_t Data);
void Usart_Send_Word(USART_TypeDef* pUSARTx, uint16_t Data);
void Usart_Send_Array(USART_TypeDef* pUSARTx, uint8_t* p,uint8_t sum);
void Usart_Send_String(USART_TypeDef* pUSARTx, uint8_t* p);
#endif 





