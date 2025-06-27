#include "pwm.h"

/**
 * @brief  ��ʼ�� TIM4 �� PWM �����ͨ�� 1 �� 2 ӳ�䵽 PB6 �� PB7��
 * 
 * �ú������� GPIOB �� PB6 �� PB7 Ϊ�������������AF_PP��ģʽ��
 * ���� TIM4 ����Ϊ PWM ģʽ 1�����������ռ�ձȿ��ɲ������ơ�
 * �����ڿ��ƶ�����������Ҫ PWM �źŵ�ģ�顣
 * 
 * @param arr  �Զ���װ��ֵ������ PWM ���ڣ�
 * @param psc  Ԥ��Ƶ��ֵ������������Ƶ�ʣ�
 */
void TIM4_PWM_Init(u16 arr, u16 psc)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_OCInitTypeDef TIM_OCInitStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);       // ���� TIM4 ʱ��
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);      // ���� GPIOB ʱ��

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;     // ���� TIM4 �� CH1 �� CH2
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;            // �����������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    TIM_TimeBaseStructure.TIM_Period = arr;
    TIM_TimeBaseStructure.TIM_Prescaler = psc;
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);

    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OCInitStructure.TIM_Pulse = 1500;  // Ĭ��ռ�ձ���ֵ��ԼΪ 1.5ms

    TIM_OC1Init(TIM4, &TIM_OCInitStructure);
    TIM_OC2Init(TIM4, &TIM_OCInitStructure);

    TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);
    TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);

    TIM_Cmd(TIM4, ENABLE);
}