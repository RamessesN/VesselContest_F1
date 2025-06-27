#include "stm32f10x.h"
#include "pwm.h"
#include "timer1.h"
#include "GPIO.h"
#include "Usart1.h"

/**
 * @brief ���������
 * 
 * ��ʼ������������ѭ���������ɼ����⴫����״̬��
 */
int main(void) {
    TIM4_PWM_Init(19999, 71); // ��ʼ�� TIM4 PWM������19999��Ԥ��Ƶ71
    GPIO_Config(); // ��ʼ�� GPIO
    Usart1_Init(); // ��ʼ�� GPIO
    TIM_SetCompare1(TIM4, 1500); // ���� PWM ���ռ�ձȳ�ֵ
    TIM1_Init(); // ��ʼ�� TIM1 ��ʱ��

    while (1) {
        for (int i = 0; i < 15; ++i) {
            if (irm_readers[i]() == 0) { // �͵�ƽ��ʾ���յ������ź�
                ++irm[i].count; // ������1
                irm[i].flag = 1; // ��־λ����Ϊ����״̬
            }
        }
    }
}