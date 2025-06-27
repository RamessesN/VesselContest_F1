#include "timer1.h"
#include "stdio.h"
#include "pwm.h"

/**
 * @brief 红外接收传感器数据结构数组，存储每个传感器的信号计数、标志位与编号。
 * 
 * - count：该周期内接收到的信号次数
 * - flag：是否接收到信号的标志位
 * - id：传感器编号（1~15）
 */
IRMSensor irm[15] = {
    {0, 0, 1}, {0, 0, 2}, {0, 0, 3}, {0, 0, 4}, {0, 0, 5},
    {0, 0, 6}, {0, 0, 7}, {0, 0, 8}, {0, 0, 9}, {0, 0, 10},
    {0, 0, 11}, {0, 0, 12}, {0, 0, 13}, {0, 0, 14}, {0, 0, 15}
};

/**
 * @brief 各红外传感器引脚读取函数。
 * 
 * 每个函数返回对应引脚电平（高电平或低电平），用于感知是否接收到红外信号。
 * 一般连接外部中断或在主循环轮询调用。
 */
uint8_t Read_IRM1(void)  { return IRM1; }
uint8_t Read_IRM2(void)  { return IRM2; }
uint8_t Read_IRM3(void)  { return IRM3; }
uint8_t Read_IRM4(void)  { return IRM4; }
uint8_t Read_IRM5(void)  { return IRM5; }
uint8_t Read_IRM6(void)  { return IRM6; }
uint8_t Read_IRM7(void)  { return IRM7; }
uint8_t Read_IRM8(void)  { return IRM8; }
uint8_t Read_IRM9(void)  { return IRM9; }
uint8_t Read_IRM10(void) { return IRM10; }
uint8_t Read_IRM11(void) { return IRM11; }
uint8_t Read_IRM12(void) { return IRM12; }
uint8_t Read_IRM13(void) { return IRM13; }
uint8_t Read_IRM14(void) { return IRM14; }
uint8_t Read_IRM15(void) { return IRM15; }

/**
 * @brief 红外传感器读取函数指针表，用于统一访问各红外传感器。
 * 
 * - 适用于遍历方式读取所有传感器状态，避免写多个 if 或 switch。
 * - 可用于替代 `irm1 == 0` 的硬编码方式，提升可维护性。
 */
IRM_ReadFunc irm_readers[15] = {
    Read_IRM1, Read_IRM2, Read_IRM3, Read_IRM4, Read_IRM5,
    Read_IRM6, Read_IRM7, Read_IRM8, Read_IRM9, Read_IRM10,
    Read_IRM11, Read_IRM12, Read_IRM13, Read_IRM14, Read_IRM15
};

/**
 * @brief 初始化 TIM1 为定时中断模式。
 * 
 * TIM1 设置为周期为 67.5ms（Period=674，Prescaler=7199）触发一次中断，
 * 用于处理红外信号数据的统计、分析与角度输出。中断优先级设为中等。
 * 
 * TIM1 作为高级定时器，支持中断触发、PWM 同步、重载等高级功能。
 */
void TIM1_Init(void) {
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
    TIM_TimeBaseStructure.TIM_Period = 674;
    TIM_TimeBaseStructure.TIM_Prescaler = 7199;
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);
    TIM_ClearFlag(TIM1, TIM_FLAG_Update);

    TIM_ITConfig(TIM1, TIM_IT_Update | TIM_IT_Trigger, ENABLE);
    NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    TIM_Cmd(TIM1, ENABLE);
}