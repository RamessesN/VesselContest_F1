#include "timer1.h"
#include <stdio.h>

extern int irm_flag[15];

float angle = 8 ,anglelast=8;
int angle_pwm = 0;
int tim1_counter = 0;
int isStraight=0;

int irm_maxtrue[15][2] = {
    {0, 1}, {0, 2}, {0, 3}, {0, 4}, {0, 5},
    {0, 6}, {0, 7}, {0, 8}, {0, 9}, {0, 10},
    {0, 11}, {0, 12}, {0, 13}, {0, 14}, {0, 15}
}; // ����Ѱ�����������޳����ŵ���ʵ����
int irm_maxtrue_sum = 0;
u32 irm_datasum = 0;

int irm_leftflag_sum = 0;
int irm_midflag_sum = 0;
int irm_rightflag_sum = 0;

// ��ʱ����ʼ��
void TIM3_Init(void) {
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);  // ʱ��ʹ��

    TIM_TimeBaseStructure.TIM_Period = 674; // �����Զ���װ�ؼĴ�������ֵ
    TIM_TimeBaseStructure.TIM_Prescaler =7199; // ����Ԥ��Ƶֵ
    TIM_TimeBaseStructure.TIM_ClockDivision = 0; // ����ʱ�ӷָ�
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; // ���ϼ���ģʽ
    TIM_TimeBaseStructure.TIM_RepetitionCounter = 0; // �ظ���������
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); // ������ʼ��
    TIM_ClearFlag(TIM3, TIM_FLAG_Update); // ���жϱ�־λ

    TIM_ITConfig(      // ʹ�ܻ���ʧ��ָ����TIM�ж�
        TIM3,            // TIM3
        TIM_IT_Update  | // TIM �����ж�Դ
        TIM_IT_Trigger,  // TIM �����ж�Դ 
        ENABLE  	     // ʹ��
    );
    
    // �������ȼ�
    NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2; // ��ռ���ȼ�0��
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;  	   // �����ȼ�0��
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure); 

    TIM_Cmd(TIM3, ENABLE);  // ʹ��TiM3����
}

// ���������־ͳ��
static void IRM_ProcessFlags(void) {
    irm_leftflag_sum = irm_flag[0] + irm_flag[1] + irm_flag[2] + irm_flag[3] + irm_flag[4];
    irm_midflag_sum = irm_flag[5] + irm_flag[6] + irm_flag[7] + irm_flag[8] + irm_flag[9]; // �м�����Ϊ5��������һ���ȽϺõ�ѡ��
    irm_rightflag_sum = irm_flag[10] + irm_flag[11] + irm_flag[12] + irm_flag[13] + irm_flag[14];
}

// ���㷨���Ƕȼ���
static void IRM_CalculateAngle(void) {
    int i, j, k;
    int sum = 0, sumMax = 0;

    for (i = 0; i < 15; ++i) {
        int max_temp = 0; // ����������ź�����
        for (j = i; j < 15 && irm_flag[j]; ++j) // �Ӹ��źſڽ��ܿ����������ֱ���ҵ�һ��û�н��յ��źŵ��źſ�
            ++sum;
        for (k = i; k < j; ++k) // ������������ź�����
            max_temp += irm_data[k][0];

        if (max_temp > irm_maxtrue_sum) {
            irm_maxtrue_sum = max_temp;
            sumMax = sum;
            for (k = i; k < j; ++k) {
                irm_maxtrue[k - i][0] = irm_data[k][0];
                irm_maxtrue[k - i][1] = irm_data[k][1];
            }
        }
        sum = 0;
    }

    for (i = 0; i < sumMax; ++i)
        irm_datasum += irm_maxtrue[i][0] * irm_maxtrue[i][1];

    if (irm_maxtrue_sum < 2) // Ψһ�ɵ�����
        angle = 8;
    else
        angle = (float)irm_datasum / irm_maxtrue_sum;
}

// ���� PWM ���
static void IRM_UpdatePWM(void) {
    angle_pwm = 1500 - (int)((angle - 8) * 200) + (angle - anglelast) * 40;
    if (angle_pwm >= 2100) angle_pwm = 2100;
    else if (angle_pwm <= 900) angle_pwm = 900;

    TIM_SetCompare1(TIM1, angle_pwm);
}

// �������׼����һ����
static void IRM_ClearData(void) {
    for (int i = 0; i < 15; ++i) { // ������ͱ�־λ��ԭ
        irm_data[i][0] = 0;
        irm_data[i][1] = i + 1;
        irm_flag[i] = 0;
        irm_maxtrue[i][0] = 0;
        irm_maxtrue[i][1] = 0;
    }
    irm_leftflag_sum = irm_midflag_sum = irm_rightflag_sum = 0;
    irm_maxtrue_sum = irm_datasum = 0;
}

void TIM3_IRQHandler(void) {
    if (TIM_GetITStatus(TIM3,TIM_IT_Update) != RESET) {
        tim1_counter = (tim1_counter + 1) % 11;
        
        IRM_ProcessFlags();
        
        if (irm_leftflag_sum <= 1 && irm_midflag_sum == 0 && irm_rightflag_sum <= 1) { // ���ź�
            angle = anglelast;  // ��ʧ�źŴ��������ϴεĽǶ�
            isStraight = 0;
        } else if (irm_leftflag_sum >= 5 && irm_midflag_sum == 3 && irm_rightflag_sum >= 5) { // ȫ�յ��ź�ֱ��
            angle = 8; // ֱ��
            isStraight = 1;
        } else { // �����������
            isStraight = 0; // ��irm_flag������Ѱ���յ��źŵ�������飬���㷨����֤������Ч����������
            IRM_CalculateAngle();
        }
        
        IRM_UpdatePWM();
        IRM_ClearData();
        anglelast = angle;
        
        TIM_ClearITPendingBit(TIM3, TIM_FLAG_Update);
    }
}	