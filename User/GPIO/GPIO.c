#include"GPIO.h"

/**
 * @brief ����GPIO�˿ڼ���ظ��ù���
 * 
 * - ʹ��GPIOA��GPIOB��GPIOC��GPIOD��AFIOʱ��
 * - �ر�JTAG���ͷ�PB3��PB4��PB5��
 * - ����PWM�������Ϊ�����������
 * - ���ö�·��������Ϊ��������
 */
void GPIO_Config(void) {
	GPIO_InitTypeDef GPIO_InitStructure;
	// ʹ��GPIOA��GPIOB��GPIOC��GPIOD�Լ�AFIOʱ��
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB |
							  RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD |
							  RCC_APB2Periph_AFIO, ENABLE); // ʱ�ӿ���
	  
	// �ر�JTAG���ͷ�PB3 PB4 PB5
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);

	//PWM2���� PB0 ����Ϊ�����������
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	// PWM1���� PC6 ����Ϊ�������������TIM3_CH1��
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15 |
								 GPIO_Pin_12 | GPIO_Pin_11 | GPIO_Pin_10 |
								 GPIO_Pin_4  | GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
}