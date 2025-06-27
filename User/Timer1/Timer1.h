#ifndef __TIMER1_H
#define __TIMER1_H

#include "stm32f10x.h"

/**
 * @brief ���⴫�������ݽṹ��
 * 
 * ���ڴ洢ÿ�����������յ����źż�������־λ�Լ���������š�
 */
typedef struct {
    uint16_t count;  // ���յ����ź���
    uint8_t flag;    // �Ƿ���յ��ź�
    uint8_t id;      // ��ţ�1~15��
} IRMSensor;


/**
 * @brief ���⴫�������ŵ�ƽ��ȡ�궨��
 * 
 * ͨ�� GPIO_ReadInputDataBit ��ȡ��Ӧ����״̬���ж��Ƿ���յ������źš�
 */
#define IRM1   GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_7)
#define IRM2   GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_6)
#define IRM3   GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_15)
#define IRM4   GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_14)
#define IRM5   GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_13)
#define IRM6   GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_12)
#define IRM7   GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11)
#define IRM8   GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_10)
#define IRM9   GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_4)
#define IRM10  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_3)
#define IRM11  GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_2)
#define IRM12  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_12)
#define IRM13  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_11)
#define IRM14  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_10)
#define IRM15  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_15)

/**
 * @brief ���⴫������ȡ����ָ�����Ͷ���
 * 
 * ���ж�ȡ�������⴫����״̬�ĺ�����Ӧ���ϴ�ǩ����
 */
typedef uint8_t (*IRM_ReadFunc)(void);

/**
 * @brief �ⲿ���������⴫�������ݽṹ������
 */
extern IRMSensor irm[15];

/**
 * @brief �ⲿ���������⴫������ȡ����ָ������
 */
extern IRM_ReadFunc irm_readers[15];

/**
 * @brief ��ʼ�� TIM1 ��ʱ�������ж�
 * 
 * ���� TIM1 �����������жϣ����ڲɼ��ʹ�����⴫�����źš�
 */
void TIM1_Init(void);

#endif