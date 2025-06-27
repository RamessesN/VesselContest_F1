#include "timer1.h"
#include "stdio.h"
#include "pwm.h"

/**
 * @brief ������մ��������ݽṹ���飬�洢ÿ�����������źż�������־λ���š�
 * 
 * - count���������ڽ��յ����źŴ���
 * - flag���Ƿ���յ��źŵı�־λ
 * - id����������ţ�1~15��
 */
IRMSensor irm[15] = {
    {0, 0, 1}, {0, 0, 2}, {0, 0, 3}, {0, 0, 4}, {0, 0, 5},
    {0, 0, 6}, {0, 0, 7}, {0, 0, 8}, {0, 0, 9}, {0, 0, 10},
    {0, 0, 11}, {0, 0, 12}, {0, 0, 13}, {0, 0, 14}, {0, 0, 15}
};

/**
 * @brief �����⴫�������Ŷ�ȡ������
 * 
 * ÿ���������ض�Ӧ���ŵ�ƽ���ߵ�ƽ��͵�ƽ�������ڸ�֪�Ƿ���յ������źš�
 * һ�������ⲿ�жϻ�����ѭ����ѯ���á�
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
 * @brief ���⴫������ȡ����ָ�������ͳһ���ʸ����⴫������
 * 
 * - �����ڱ�����ʽ��ȡ���д�����״̬������д��� if �� switch��
 * - ��������� `irm1 == 0` ��Ӳ���뷽ʽ��������ά���ԡ�
 */
IRM_ReadFunc irm_readers[15] = {
    Read_IRM1, Read_IRM2, Read_IRM3, Read_IRM4, Read_IRM5,
    Read_IRM6, Read_IRM7, Read_IRM8, Read_IRM9, Read_IRM10,
    Read_IRM11, Read_IRM12, Read_IRM13, Read_IRM14, Read_IRM15
};

/**
 * @brief ��ʼ�� TIM1 Ϊ��ʱ�ж�ģʽ��
 * 
 * TIM1 ����Ϊ����Ϊ 67.5ms��Period=674��Prescaler=7199������һ���жϣ�
 * ���ڴ�������ź����ݵ�ͳ�ơ�������Ƕ�������ж����ȼ���Ϊ�еȡ�
 * 
 * TIM1 ��Ϊ�߼���ʱ����֧���жϴ�����PWM ͬ�������صȸ߼����ܡ�
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