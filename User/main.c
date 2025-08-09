#include "stm32f10x.h"
#include "pwm.h"
#include "timer1.h"
#include "GPIO.h"
#include "Usart1.h"

u32 irm_data[15][2] = { //[i][0]是一个周期内收到的信号总数，[i][1]是每个信号接收源的标号
    {0, 1}, {0, 2}, {0, 3}, {0, 4}, {0, 5}, 
    {0, 6}, {0, 7}, {0, 8}, {0, 9}, {0, 10}, 
    {0, 11}, {0, 12}, {0, 13}, {0, 14}, {0, 15}
};

int irm_flag[15]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}; //每个接收头是否收到的标志位

int main(void) {
    TIM1_PWM_Init(19999,71);
    // TIM3_PWM_Init(19999, 71);
    
    GPIO_Config(); //使能红外接收端口
    Usart1_Init();
    
    TIM_SetCompare1(TIM1,1500);
    // TIM_SetCompare2(TIM3,5000);
    
	TIM3_Init(); // TIM3计时用于开启67ms的中断

	while(1)	{
		//前置++执行速度更快，因为不会像后置++一样保留副本
		 if(irm1 == 0) { ++ irm_data[0][0]; irm_flag[0] = 1; }
		 if(irm2 == 0) { ++ irm_data[1][0]; irm_flag[1] = 1; }
		 if(irm3 == 0) { ++ irm_data[2][0]; irm_flag[2] = 1; }
		 if(irm4 == 0) { ++ irm_data[3][0]; irm_flag[3] = 1; }
		 if(irm5 == 0) { ++ irm_data[4][0]; irm_flag[4] = 1; }
		 if(irm6 == 0) { ++ irm_data[5][0]; irm_flag[5] = 1; }
		 if(irm7 == 0) { ++ irm_data[6][0]; irm_flag[6] = 1; }
		 if(irm8 == 0) { ++ irm_data[7][0]; irm_flag[7] = 1; }
		 if(irm9 == 0) { ++ irm_data[8][0]; irm_flag[8] = 1; }
		 if(irm10 == 0) { ++ irm_data[9][0]; irm_flag[9] = 1; }
		 if(irm11 == 0) { ++ irm_data[10][0]; irm_flag[10] = 1; }
		 if(irm12 == 0) { ++ irm_data[11][0]; irm_flag[11] = 1; }
		 if(irm13 == 0) { ++ irm_data[12][0]; irm_flag[12] = 1; }
		 if(irm14 == 0) { ++ irm_data[13][0]; irm_flag[13] = 1; }
		 if(irm15 == 0) { ++ irm_data[14][0]; irm_flag[14] = 1; }
	}
}