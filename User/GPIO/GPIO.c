#include "GPIO.h"

/**
 * @brief ����GPIO�˿ڼ���ظ��ù���
 * 
 * - ʹ��GPIOA��GPIOB��GPIOC��GPIOD��AFIOʱ��
 * - �ر�JTAG���ͷ� PB3~PB5 ��
 * - ����PWM�������Ϊ�����������
 * - ���ö�·��������Ϊ��������
 */
void GPIO_Config(void) {
	GPIO_InitTypeDef GPIO_InitStructure;
    
	// ����GPIO������ʱ��
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB |
							  RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD |
							  RCC_APB2Periph_AFIO, ENABLE);
	  
	// �ر�JTAG���ͷ�PB3~PB5W
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);

    // === ����PWM������� === //
    // PA8 ��Ϊ TIM1_CH1��PWM1�����
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
    
    // PA7 ��Ϊ TIM3_CH2��PWM2�����
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	// === ������������ === //
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; // ��������

    // ��ʼ��PA�˿�
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;	
	GPIO_Init(GPIOA, &GPIO_InitStructure);
    
    // ��ʼ��PB�˿�
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15 |
								  GPIO_Pin_12 | GPIO_Pin_11 | GPIO_Pin_10 |
								  GPIO_Pin_4  | GPIO_Pin_3;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
    
    // ��ʼ��PC�˿�
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_10 |
								  GPIO_Pin_11 | GPIO_Pin_12;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

    // ��ʼ��PD�˿�
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
}