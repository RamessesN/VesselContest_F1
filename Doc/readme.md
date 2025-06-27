# 全国海洋航行器设计与制作大赛F1-现代帆船竞速

基于 STM32F103RCT6 的红外传感器阵列信号采集与智能舵机转向控制系统

## 🧠 项目简介

本项目使用 15 个红外传感器采集地面黑/白线信号，结合连续区块信号分析与角度加权算法实现帆船循迹控制。系统通过 PWM 驱动舵机完成转向控制，并支持通过串口调试查看角度与信号分布等信息。

- 微控制器：STM32F103RCT6
- 编程语言：C (Keil uVision5)
- 中间件：标准固件库 STM32F10x
- 串口输出：USART1（波特率 115200）
- 主要接口：PWM 输出、GPIO 输入、USART

## 📦 项目结构

STM32_IR_Tracking/
├── Core/
│   ├── main.c                 # 主循环逻辑
│   ├── Usart1.c/.h           # 串口初始化与发送接口
│   ├── pwm.c/.h              # TIM4 PWM 驱动舵机
│   ├── timer1.c/.h           # TIM1 定时器采样中断 & 算法处理
│   ├── GPIO.c/.h             # GPIO 初始化
│   ├── system_stm32f10x.c    # 时钟系统配置（标准库）
├── README.md                 # 项目说明文档
└── …

## ⚙️ 系统功能

### 🚦 红外信号采集

- 共 15 个红外传感器，编号 1~15，GPIO 引脚详见 `timer1.h`
- 通过 `irm_readers[]` 函数指针数组读取各通道状态

### ⏱️ 周期性采样

- 使用 TIM1 每 67.5ms 进入一次中断
- 统计每通道在一个周期内的信号触发次数 `irm[].count`
- 标志是否有信号 `irm[].flag`

### 📐 中心角计算

- 寻找连续信号区域的最大块，避免反射干扰
- 加权计算中心角度 angle = ∑(通道编号 × 信号数) / 总信号数
- 控制舵机 PWM 输出，使其偏转到对应角度

### 🔧 舵机输出控制

- 使用 TIM4 通道1 输出 PWM
- 中位角度 1500us，对应“直走”
- 输出范围限制在 900~2100us，避免过偏转

### 📤 串口调试

可通过 USART1 打印以下调试信息（可在代码中开启）：

- `angle_pwm`: PWM 输出值
- 各通道的信号计数（可选打印）

## 🛠️ 开发与编译环境

- **Keil uVision5**
- **STM32F10x Standard Peripheral Library**
- **ST-Link** 下载器

## 🧩 外设连接表

| IR通道 | 引脚编号 | GPIO端口 |
|--------|----------|----------|
| IRM1   | PC7      | GPIOC    |
| IRM2   | PC6      | GPIOC    |
| IRM3   | PB15     | GPIOB    |
| IRM4   | PB14     | GPIOB    |
| IRM5   | PB13     | GPIOB    |
| IRM6   | PB12     | GPIOB    |
| IRM7   | PB11     | GPIOB    |
| IRM8   | PB10     | GPIOB    |
| IRM9   | PB4      | GPIOB    |
| IRM10  | PB3      | GPIOB    |
| IRM11  | PD2      | GPIOD    |
| IRM12  | PC12     | GPIOC    |
| IRM13  | PC11     | GPIOC    |
| IRM14  | PC10     | GPIOC    |
| IRM15  | PA15     | GPIOA    |

## ✨ 特点与优势

- 使用结构体封装红外数据，逻辑清晰易扩展
- 支持 Doxygen 注释，文档生成友好
- 高鲁棒性角度计算，适应复杂光照干扰
- 模块分离，便于移植与调试

## 📎 示例输出（串口）

```text
angle_pwm=1640
angle_pwm=1510
angle_pwm=1420

📢 TODO
	•	集成 EEPROM 保存偏置参数
	•	增加 蓝牙 状态实时显示
