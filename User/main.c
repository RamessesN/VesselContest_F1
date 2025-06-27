#include "stm32f10x.h"
#include "pwm.h"
#include "timer1.h"
#include "GPIO.h"
#include "Usart1.h"

/**
 * @brief 主函数入口
 * 
 * 初始化外设后进入主循环，持续采集红外传感器状态。
 */
int main(void) {
    TIM4_PWM_Init(19999, 71); // 初始化 TIM4 PWM，周期19999，预分频71
    GPIO_Config(); // 初始化 GPIO
    Usart1_Init(); // 初始化 GPIO
    TIM_SetCompare1(TIM4, 1500); // 设置 PWM 输出占空比初值
    TIM1_Init(); // 初始化 TIM1 定时器

    while (1) {
        for (int i = 0; i < 15; ++i) {
            if (irm_readers[i]() == 0) { // 低电平表示接收到红外信号
                ++irm[i].count; // 计数加1
                irm[i].flag = 1; // 标志位设置为接收状态
            }
        }
    }
}