#ifndef __TIMER1_H
#define __TIMER1_H

#include "stm32f10x.h"

// =============================
// 红外传感器读取宏定义（15路）
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
// 外部变量：红外数据缓冲区
// =============================
// irm_data[i][0]：当前周期接收到的脉冲数
// irm_data[i][1]：通道编号（1~15，初始化后固定）
extern u32 irm_data[15][2];

// 标志数组：1表示该通道有效，0表示无效（由中断逻辑判断得出）
extern int irm_flag[15];

// =============================
// 接口函数
// =============================

void TIM3_Init(void);            // TIM3 初始化，每 100ms 中断一次
void TIM3_IRQHandler(void);      // TIM3 中断服务函数

#endif