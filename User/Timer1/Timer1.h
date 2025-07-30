#ifndef __Timer1_H
#define	__Timer1_H

#include "stm32f10x.h"

// 红外传感器读取宏定义
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

// 红外数据数组 [15][2]：第0列存当前值，第1列存上一次值
extern u32 irm_data[15][2];

void TIM1_Init(void); // 定时器初始化
void TIM1_UP_IRQHandler(void); // 中断服务函数

void IRM_UpdateAll(void); // 更新所有红外状态
void IRM_ProcessSignal(void); // 根据变化做出反应（如PWM控制）

#endif