#include "GPIO.h"

/**
 * @brief 配置GPIO端口及相关复用功能
 * 
 * - 使能GPIOA、GPIOB、GPIOC、GPIOD和AFIO时钟
 * - 关闭JTAG以释放 PB3~PB5 口
 * - 配置PWM相关引脚为复用推挽输出
 * - 配置多路输入引脚为浮空输入
 */
void GPIO_Config(void) {
	GPIO_InitTypeDef GPIO_InitStructure;
    
	// 开启GPIO及复用时钟
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB |
							  RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD |
							  RCC_APB2Periph_AFIO, ENABLE);
	  
	// 关闭JTAG，释放PB3~PB5W
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);

    // === 配置PWM输出引脚 === //
    // PA8 作为 TIM1_CH1（PWM1）输出
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
    
    // PA7 作为 TIM3_CH2（PWM2）输出
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	// === 配置输入引脚 === //
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; // 浮空输入

    // 初始化PA端口
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;	
	GPIO_Init(GPIOA, &GPIO_InitStructure);
    
    // 初始化PB端口
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15 |
								  GPIO_Pin_12 | GPIO_Pin_11 | GPIO_Pin_10 |
								  GPIO_Pin_4  | GPIO_Pin_3;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
    
    // 初始化PC端口
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_10 |
								  GPIO_Pin_11 | GPIO_Pin_12;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

    // 初始化PD端口
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
}