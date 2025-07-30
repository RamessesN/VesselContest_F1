<div align="center">
    <h1>第十四届全国海洋航行器设计与制作大赛
    <h2>F1帆船模型竞速 - 现代帆船竞速
</div>

---

<img src="./Doc/img/ouc.png" alt="ouc_alt" title="ouc_img">

<div align="center">
  <h3> 团队名：海洋Rose队
  <h3> 队长：徐子正 &nbsp;&nbsp; 队员：赵禹惟、王昊凯、张浩、胡焕峥
  <h3> 指导老师：闫劢、冯晨
</div>

---

## 一、项目简介
本项目为 “第十四届全国海洋航行器设计与制作大赛 - F1帆船模型竞速” 的软件控制部分，使用 **STM32F103C8T6** 微控制器实现红外数据采集、舵机角度控制与通信调试，完成自动控制路径跟踪功能。

---

## 二、成果展示
<p align="center">
  *** Sailboat ***
  <br>
  <img src="">
  <img src="">
  <img src="">
  <br>
  <br>
  *** Board ***
  <br>
  <img src="./Doc/img/board_front.png" alt="board_front_alt" title="bf_img" width=300>
  <img src="./Doc/img/board_back.png" alt="board_back_alt" title="bb_img" width=300>
  <br>
</p>

---

## 三、项目主体结构
<pre><code>
User/
├── GPIO/                   # GPIO初始化，包含红外、PWM引脚配置
│   ├── GPIO.c
│   └── GPIO.h
│
├── Timer1/                 # TIM3定时中断，每67ms触发一次数据处理与舵机控制
│   ├── Timer1.c
│   └── Timer1.h
│
├── Usart1/                 # USART1串口初始化及数据发送函数
│   ├── usart1.c
│   └── usart1.h
│
├── pwm/                    # PWM输出模块（TIM1与TIM3控制舵机）
│   ├── pwm.c
│   └── pwm.h
│
├── main.c                  # 主程序入口，包含红外采集与控制主循环
│
├── stm32f10x_conf.h        # 标准外设库配置文件
├── stm32f10x_it.c          # 中断服务函数实现
└── stm32f10x_it.h          # 中断服务函数声明
</code></pre>

---

## 四、具体说明
### 1. 功能概述
| 模块     | 功能描述 |
|----------|----------|
| GPIO     | 配置红外接收输入、PWM输出及串口通信引脚 |
| PWM      | 通过 TIM1（PA8）和 TIM3（PA7）输出 PWM 控制信号 |
| Timer1   | 配置 TIM3 每 67ms 触发一次中断，用于红外信号处理与舵机角度计算 |
| USART1   | 初始化串口 9600 波特率，支持 `printf` 重定向，便于蓝牙或串口调试 |
| 主逻辑   | 实时读取 15 路红外传感器数据，识别红外信号区域，计算舵机角度，并输出控制信号 |

---

### 2. 硬件引脚连接
| 模块        | 引脚      | 说明                     |
|-------------|-----------|--------------------------|
| PWM输出1    | PA8       | TIM1_CH1 控制主舵机角度 |
| PWM输出2    | PA7       | TIM3_CH2 预留控制第二通道 |
| USART1 - TX   | PA9       | 串口发送（连接蓝牙模块） |
| USART1 - RX   | PA10      | 串口接收                 |
| 红外接收    | PB3\~PB5、PB10\~PB15、PC6\~PC7、PC10\~PC12、PD2、PA15 | 共15路红外输入信号 |
> 注：通过关闭 JTAG 释放 PB3~PB5 端口用于红外输入

---

### 3. 核心控制算法
- **红外采样逻辑**：采用边沿检测替代电平累加，将高速信号采集与低速控制决策分离，保证红外脉冲计数的准确性和系统控制的稳定性
- **定时处理**：TIM3中断每67ms触发一次，完成以下任务：
  1. 分类红外区域（左/中/右）信号强度
  2. 丢信号检测与上次角度保持处理
  3. 寻找信号连续的最大块，计算其重心位置作为角度输入
  4. 输出 PWM 控制信号至舵机（角度范围 900 ~ 2100）
- **调试信息**：当开启 `bluetoothsend = 1` 时，通过串口输出传感器数据、角度值、PWM控制量等调试信息。

### 4. PWM 占空比角度转化 PD 算法
```c {.line-numbers}
angle_pwm = 1500 + (int)((angle - 8) * 200) + (angle - anglelast) * 40;
```
> 注：angle_pwm 限制在 [900, 2100] 范围内

---

### 5. 烧录方法 (兼容 win / macOS)
> 注：由于 Coder 是一名 mac 重度使用者🧑🏻‍💻，这里以少为人知的 mac 使用方法作为讲解
1.	通过 Terminal 执行 `brew install stlink` 下载烧录工具，用于与ST-Link V2和电脑之间通信
2. 通过 `st-info --probe` 查看电脑是否识别到 STM 芯片，如果识别到，大致格式如下：
```
Found 1 stlink programmers
  version:    V2J37S7
  serial:     37FF71064E573436FC871343
  flash:      262144 (pagesize: 2048)
  sram:       65536
  chipid:     0x414
  dev-type:   F1xx_HD
```
3. 通过 Crossover 基于 x86 to arm 的 wine 配置转译运行的 Keil µVision5 生成项目对应 .bin 二进制文件
4. 通过 `st-flash write XXX.bin 0x8000000` 将 .bin 文件 (如 [BH-F103.bin](./Project/Objects/BH-F103.bin))
烧录到对应 STM 芯片中
> 注1：执行 st-flash 一般需要先执行 `st-flash erase` 用于擦除芯片旧二进制信息
>
> 注2：据 st-link 命令行工具官方说明，st-link version 1.8.0 之后将不再提供对 mac 的支持，详见 [stlink-org/stlink](https://github.com/stlink-org/stlink.git)

---

### 6. 蓝牙串口读取方法 (兼容 win / macOS)
1. 下载 **bleak** 库实现 **BLE 协议** 蓝牙通信`pip install bleak`
2. 配置 UUID 为 BT16 模块，即
    - Service UUID: 0000FFE0-0000-1000-8000-00805F9B34FB
    - Notify UUID: 0000FFE1-0000-1000-8000-00805F9B34FB
    - Write UUID: 0000FFE2-0000-1000-8000-00805F9B34FB
3. 执行对应 **[监听代码](./BlueTooth/BLE_Read.py)** 即可读取串口信息
4. 通过 **正则表达式** 过滤无关信息获得 `Vendor specific: bytearray` 中串口内容
> 注：在 macOS Sequoia 大版本之后，mac 在 kernal 层不再支持对传统 SPP 协议蓝牙模块的支持 (如 HC-05)，BLE 因而成为首选

---

### 7. 关键参数说明
| 参数 | 默认值 | 说明 |
|-------------|-----------|--------------------------|
| TIM3 周期 | 674 | 对应约 67ms 中断周期 |
| PWM 主舵机通道 | TIM1_CH1 / PA8 | 控制主向偏转角 |
| 中心角度基准 | 1500 | 舵机中位值 |
| 红外采样窗口 | 15通道 | 从 IRM1 ~ IRM15 并行处理 |

---

### ⚠️ License: 该项目非开源. 详见 [LICENSE](./LICENSE).

<img src="./Doc/img/ouc2.png" alt="ouc2_alt" title="ouc2_img">