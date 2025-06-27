#ifndef __TIMER1_H
#define __TIMER1_H

#include "stm32f10x.h"

/**
 * @brief 红外传感器数据结构体
 * 
 * 用于存储每个传感器接收到的信号计数、标志位以及传感器编号。
 */
typedef struct {
    uint16_t count;  // 接收到的信号数
    uint8_t flag;    // 是否接收到信号
    uint8_t id;      // 编号（1~15）
} IRMSensor;


/**
 * @brief 红外传感器引脚电平读取宏定义
 * 
 * 通过 GPIO_ReadInputDataBit 读取对应引脚状态，判断是否接收到红外信号。
 */
#define IRM1   GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_7)
#define IRM2   GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_6)
#define IRM3   GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_15)
#define IRM4   GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_14)
#define IRM5   GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_13)
#define IRM6   GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_12)
#define IRM7   GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11)
#define IRM8   GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_10)
#define IRM9   GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_4)
#define IRM10  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_3)
#define IRM11  GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_2)
#define IRM12  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_12)
#define IRM13  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_11)
#define IRM14  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_10)
#define IRM15  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_15)

/**
 * @brief 红外传感器读取函数指针类型定义
 * 
 * 所有读取单个红外传感器状态的函数都应符合此签名。
 */
typedef uint8_t (*IRM_ReadFunc)(void);

/**
 * @brief 外部声明：红外传感器数据结构体数组
 */
extern IRMSensor irm[15];

/**
 * @brief 外部声明：红外传感器读取函数指针数组
 */
extern IRM_ReadFunc irm_readers[15];

/**
 * @brief 初始化 TIM1 定时器及其中断
 * 
 * 配置 TIM1 产生周期性中断，用于采集和处理红外传感器信号。
 */
void TIM1_Init(void);

#endif