#ifndef __TIMER1_H
#define __TIMER1_H

#include "stm32f10x.h"

// =============================
// ���⴫������ȡ�궨�壨15·��
// =============================
#define irm1   GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_7)
#define irm2   GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_6)
#define irm3   GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_15)
#define irm4   GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_14)
#define irm5   GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_13)
#define irm6   GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_12)
#define irm7   GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_11)
#define irm8   GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_10)
#define irm9   GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_4)
#define irm10  GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_3)
#define irm11  GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_2)
#define irm12  GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_12)
#define irm13  GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_11)
#define irm14  GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_10)
#define irm15  GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_15)

// =============================
// �ⲿ�������������ݻ�����
// =============================
// irm_data[i][0]����ǰ���ڽ��յ���������
// irm_data[i][1]��ͨ����ţ�1~15����ʼ����̶���
extern u32 irm_data[15][2];

// ��־���飺1��ʾ��ͨ����Ч��0��ʾ��Ч�����ж��߼��жϵó���
extern int irm_flag[15];

// =============================
// �ӿں���
// =============================

void TIM3_Init(void);            // TIM3 ��ʼ����ÿ 100ms �ж�һ��
void TIM3_IRQHandler(void);      // TIM3 �жϷ�����

#endif