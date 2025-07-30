#include "stm32f10x.h"
#include "pwm.h"
#include "timer1.h"
#include "GPIO.h"
#include "Usart1.h"

u32 irm_data[15][2] = {
    {0, 1}, {0, 2}, {0, 3}, {0, 4}, {0, 5},
    {0, 6}, {0, 7}, {0, 8}, {0, 9}, {0, 10},
    {0, 11}, {0, 12}, {0, 13}, {0, 14}, {0, 15}
}; // [i][0]��һ���������յ����ź�������[i][1]��ÿ���źŽ���Դ�ı��

int irm_flag[15] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; // ÿ������ͷ�Ƿ��յ��ı�־λ

// ��Ӿ�̬���������ڼ�¼��һ�ε�����״̬
static uint8_t last_irm_state[15] = {0}; // ��ʼ��Ϊ0

int main(void) {
    TIM1_PWM_Init(19999, 71);
    // TIM3_PWM_Init(19999, 71);
    
    GPIO_Config(); // ʹ�ܺ�����ն˿�
    Usart1_Init();
    
    TIM_SetCompare1(TIM1,1500);
    // TIM_SetCompare2(TIM3,5000);
    
    TIM3_Init(); // TIM3��ʱ���ڿ���67ms���ж�
    
    // �ڽ���ѭ��ǰ���ȶ�ȡһ����������״̬����Ϊ��ʼֵ
    last_irm_state[0] = irm1;
    last_irm_state[1] = irm2;
    last_irm_state[2] = irm3;
    last_irm_state[3] = irm4;
    last_irm_state[4] = irm5;
    last_irm_state[5] = irm6;
    last_irm_state[6] = irm7;
    last_irm_state[7] = irm8;
    last_irm_state[8] = irm9;
    last_irm_state[9] = irm10;
    last_irm_state[10] = irm11;
    last_irm_state[11] = irm12;
    last_irm_state[12] = irm13;
    last_irm_state[13] = irm14;
    last_irm_state[14] = irm15;
    
    while(1) {
        // ���ÿ�����ŵ��½��أ���->�ͣ�
        if (irm1 == 0 && last_irm_state[0] == 1) {
            irm_data[0][0]++;
            irm_flag[0] = 1;
        } if (irm2 == 0 && last_irm_state[1] == 1) {
            irm_data[1][0]++;
            irm_flag[1] = 1;
        } if (irm3 == 0 && last_irm_state[2] == 1) {
            irm_data[2][0]++;
            irm_flag[2] = 1;
        } if (irm4 == 0 && last_irm_state[3] == 1) {
            irm_data[3][0]++;
            irm_flag[3] = 1;
        } if (irm5 == 0 && last_irm_state[4] == 1) {
            irm_data[4][0]++;
            irm_flag[4] = 1;
        } if (irm6 == 0 && last_irm_state[5] == 1) {
            irm_data[5][0]++;
            irm_flag[5] = 1;
        } if (irm7 == 0 && last_irm_state[6] == 1) {
            irm_data[6][0]++;
            irm_flag[6] = 1;
        } if (irm8 == 0 && last_irm_state[7] == 1) {
            irm_data[7][0]++;
            irm_flag[7] = 1;
        } if (irm9 == 0 && last_irm_state[8] == 1) {
            irm_data[8][0]++;
            irm_flag[8] = 1;
        } if (irm10 == 0 && last_irm_state[9] == 1) {
            irm_data[9][0]++;
            irm_flag[9] = 1;
        } if (irm11 == 0 && last_irm_state[10] == 1) {
            irm_data[10][0]++;
            irm_flag[10] = 1;
        } if (irm12 == 0 && last_irm_state[11] == 1) {
            irm_data[11][0]++;
            irm_flag[11] = 1;
        } if (irm13 == 0 && last_irm_state[12] == 1) {
            irm_data[12][0]++;
            irm_flag[12] = 1;
        } if (irm14 == 0 && last_irm_state[13] == 1) {
            irm_data[13][0]++;
            irm_flag[13] = 1;
        } if (irm15 == 0 && last_irm_state[14] == 1) {
            irm_data[14][0]++;
            irm_flag[14] = 1;
        }

        // ������һ�ε�״̬
        last_irm_state[0] = irm1;
        last_irm_state[1] = irm2;
        last_irm_state[2] = irm3;
        last_irm_state[3] = irm4;
        last_irm_state[4] = irm5;
        last_irm_state[5] = irm6;
        last_irm_state[6] = irm7;
        last_irm_state[7] = irm8;
        last_irm_state[8] = irm9;
        last_irm_state[9] = irm10;
        last_irm_state[10] = irm11;
        last_irm_state[11] = irm12;
        last_irm_state[12] = irm13;
        last_irm_state[13] = irm14;
        last_irm_state[14] = irm15;
    }
}