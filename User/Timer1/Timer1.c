#include "timer1.h"
#include <stdio.h>

#define bluetoothsend 1 // �Ƿ������������򴮿ڷ�����Ϣ��0��ʾ�����ͣ�1��ʾ����

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
void TIM1_Init(void) {
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE); // ʱ��ʹ��

    TIM_TimeBaseStructure.TIM_Period = 674; // �����Զ���װ�ؼĴ�������ֵ
    TIM_TimeBaseStructure.TIM_Prescaler =7199; // ����Ԥ��Ƶֵ
    TIM_TimeBaseStructure.TIM_ClockDivision = 0; // ����ʱ�ӷָ�
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; // ���ϼ���ģʽ
    TIM_TimeBaseStructure.TIM_RepetitionCounter = 0; // �ظ���������
    TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure); // ������ʼ��
    TIM_ClearFlag(TIM1, TIM_FLAG_Update); // ���жϱ�־λ

    TIM_ITConfig(      // ʹ�ܻ���ʧ��ָ����TIM�ж�
        TIM1,            // TIM1
        TIM_IT_Update  | // TIM �����ж�Դ
        TIM_IT_Trigger,  // TIM �����ж�Դ 
        ENABLE  	     // ʹ��
    );
    
    // �������ȼ�
    NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_IRQn;  
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2; // ��ռ���ȼ�0��
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;  	   // �����ȼ�0��
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure); 

    TIM_Cmd(TIM1, ENABLE);  // ʹ��TIMx����
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

    if (irm_maxtrue_sum < 50)
        angle = 8;
    else
        angle = (float)irm_datasum / irm_maxtrue_sum;
    
#if bluetoothsend		
    printf("%s","\r\ndatasum=");
    printf("%d",irm_datasum);
    printf("%s","\r\nirm_maxtrue_sum=");
    printf("%d",irm_maxtrue_sum);
    printf("%s","\r\nangle=");
    printf("%.2f",angle);
    printf("%s","\r\ndata0=");
    printf("%d",irm_data[0][0]);
    printf("%s","\r\ndata1=");
    printf("%d",irm_data[1][0]);
    printf("%s","\r\ndata2=");
    printf("%d",irm_data[2][0]);
    printf("%s","\r\ndata3=");
    printf("%d",irm_data[3][0]);
    printf("%s","\r\ndata4=");
    printf("%d",irm_data[4][0]);	
    printf("%s","\r\ndata5=");
    printf("%d",irm_data[5][0]);	
    printf("%s","\r\ndata6=");
    printf("%d",irm_data[6][0]);	
    printf("%s","\r\ndata7=");
    printf("%d",irm_data[7][0]);	
    printf("%s","\r\ndata8=");
    printf("%d",irm_data[8][0]);	
    printf("%s","\r\ndata9=");
    printf("%d",irm_data[9][0]);	
    printf("%s","\r\ndata10=");
    printf("%d",irm_data[10][0]);			
    printf("%s","\r\ndata11=");
    printf("%d",irm_data[11][0]);
    printf("%s","\r\ndata12=");
    printf("%d",irm_data[12][0]);
    printf("%s","\r\ndata13=");
    printf("%d",irm_data[13][0]);	
    printf("%s","\r\ndata14=");
    printf("%d",irm_data[14][0]);					
    printf("%s","\r\n\r\n");
#endif
}

// ���� PWM ���
static void IRM_UpdatePWM(void) {
    angle_pwm = 1500 + (int)((angle - 8) * 200) + (angle - anglelast) * 40;
    if (angle_pwm >= 2100) angle_pwm = 2100;
    else if (angle_pwm <= 900) angle_pwm = 900;

    TIM_SetCompare1(TIM4, angle_pwm);

#if bluetoothsend
    printf("%s","\r\nirm_leftflag_sum=");
    printf("%d",irm_leftflag_sum);
    printf("%s","\r\nirm_midflag_sum=");
    printf("%d",irm_midflag_sum);
    printf("%s","\r\nirm_rightflag_sum=");
    printf("%d",irm_rightflag_sum);
    printf("\r\nangle_pwm = %d", angle_pwm);
#endif
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

void TIM1_UP_IRQHandler(void) {
    if (TIM_GetITStatus(TIM1,TIM_IT_Update) != RESET) {
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
        
        TIM_ClearITPendingBit(TIM1, TIM_FLAG_Update);
    }
}	