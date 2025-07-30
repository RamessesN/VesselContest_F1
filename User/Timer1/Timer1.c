#include "timer1.h"
#include <stdio.h>

#define bluetoothsend 1 // 是否允许向蓝牙或串口发送信息，0表示不发送，1表示发送

extern int irm_flag[15];

float angle = 8 ,anglelast=8;
int angle_pwm = 0;
int tim1_counter = 0;
int isStraight=0;

int irm_maxtrue[15][2] = {
    {0, 1}, {0, 2}, {0, 3}, {0, 4}, {0, 5},
    {0, 6}, {0, 7}, {0, 8}, {0, 9}, {0, 10},
    {0, 11}, {0, 12}, {0, 13}, {0, 14}, {0, 15}
}; // 经过寻找最大区块后剔除干扰的真实数据
int irm_maxtrue_sum = 0;
u32 irm_datasum = 0;

int irm_leftflag_sum = 0;
int irm_midflag_sum = 0;
int irm_rightflag_sum = 0;

// 定时器初始化
void TIM1_Init(void) {
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE); // 时钟使能

    TIM_TimeBaseStructure.TIM_Period = 674; // 设置自动重装载寄存器周期值
    TIM_TimeBaseStructure.TIM_Prescaler =7199; // 设置预分频值
    TIM_TimeBaseStructure.TIM_ClockDivision = 0; // 设置时钟分割
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; // 向上计数模式
    TIM_TimeBaseStructure.TIM_RepetitionCounter = 0; // 重复计数设置
    TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure); // 参数初始化
    TIM_ClearFlag(TIM1, TIM_FLAG_Update); // 清中断标志位

    TIM_ITConfig(      // 使能或者失能指定的TIM中断
        TIM1,            // TIM1
        TIM_IT_Update  | // TIM 更新中断源
        TIM_IT_Trigger,  // TIM 触发中断源 
        ENABLE  	     // 使能
    );
    
    // 设置优先级
    NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_IRQn;  
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2; // 先占优先级0级
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;  	   // 从优先级0级
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure); 

    TIM_Cmd(TIM1, ENABLE);  // 使能TIMx外设
}

// 红外区域标志统计
static void IRM_ProcessFlags(void) {
    irm_leftflag_sum = irm_flag[0] + irm_flag[1] + irm_flag[2] + irm_flag[3] + irm_flag[4];
    irm_midflag_sum = irm_flag[5] + irm_flag[6] + irm_flag[7] + irm_flag[8] + irm_flag[9]; // 中间设置为5经测试是一个比较好的选择
    irm_rightflag_sum = irm_flag[10] + irm_flag[11] + irm_flag[12] + irm_flag[13] + irm_flag[14];
}

// 主算法：角度计算
static void IRM_CalculateAngle(void) {
    int i, j, k;
    int sum = 0, sumMax = 0;

    for (i = 0; i < 15; ++i) {
        int max_temp = 0; // 连续区域的信号总数
        for (j = i; j < 15 && irm_flag[j]; ++j) // 从该信号口接受口往后面便利直到找到一个没有接收到信号的信号口
            ++sum;
        for (k = i; k < j; ++k) // 便利算出连续信号总数
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

// 更新 PWM 输出
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

// 清除数据准备下一周期
static void IRM_ClearData(void) {
    for (int i = 0; i < 15; ++i) { // 将数组和标志位还原
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
        
        if (irm_leftflag_sum <= 1 && irm_midflag_sum == 0 && irm_rightflag_sum <= 1) { // 丢信号
            angle = anglelast;  // 丢失信号处理，按照上次的角度
            isStraight = 0;
        } else if (irm_leftflag_sum >= 5 && irm_midflag_sum == 3 && irm_rightflag_sum >= 5) { // 全收到信号直走
            angle = 8; // 直走
            isStraight = 1;
        } else { // 正常接收情况
            isStraight = 0; // 在irm_flag数组中寻找收到信号的最大区块，该算法经验证可以有效处理反射问题
            IRM_CalculateAngle();
        }
        
        IRM_UpdatePWM();
        IRM_ClearData();
        anglelast = angle;
        
        TIM_ClearITPendingBit(TIM1, TIM_FLAG_Update);
    }
}	