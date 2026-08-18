# openbl_f4bl — PX4 固件编译说明

## 硬件平台
- **MCU**: STM32F405RGT6 (Cortex-M4, 168MHz, 1024KB Flash)
- **IMU**: MPU6500 (SPI1, CS=PA4, ROTATION_ROLL_180)
- **气压计**: BMP280 / SPL06 (I2C1, PB8/PB7)
- **OSD**: AT7456E (SPI1, CS=PB12)
- **LED**: PA14 (蓝), PA13 (绿)

## Flash 布局

| 区域 | 起始地址 | 大小 |
|------|----------|------|
| Bootloader | `0x08000000` | 64KB (APM bootloader, ~16KB 实际) |
| 参数存储 | `0x08004000` | 16KB |
| 固件 | `0x08010000` | 960KB |

## 编译

### 1. 部署板级配置

```
cp -r openbl_f4bl /home/<username>/PX4-Autopilot/boards/openbl/f4bl
```

### 2. 应用框架补丁

PX4 框架 `io_timer.c` 需要打补丁以支持 TIM1/TIM8 高级定时器的互补通道 (CHxN) 输出。

文件: `platforms/nuttx/src/px4/stm/stm32_common/io_pins/io_timer.c`

补丁文件: `patches/io_timer.c` (完整的修改后文件)

修改内容:
- 在 `io_timer_channel_init()` 中，CCER 配置后添加互补输出使能 (CCxNE) 和互补极性 (CCxNP) 位
- 仅对 TIM1 和 TIM8 生效

```bash
cp patches/io_timer.c /home/<username>/PX4-Autopilot/platforms/nuttx/src/px4/stm/stm32_common/io_pins/io_timer.c
```

### 3. 编译固件

```bash
cd /home/<username>/PX4-Autopilot
make openbl_f4bl_default
```

### 4. 生成 HEX

```bash
arm-none-eabi-objcopy -O ihex build/openbl_f4bl_default/openbl_f4bl_default.elf openbl_f4bl_default.hex
```

## 产物

| 文件 | 说明 |
|------|------|
| `openbl_f4bl_default.bin` | 原始固件 (~888KB) |
| `openbl_f4bl_default.px4` | PX4 固件包 |
| `openbl_f4bl_default.hex` | Intel HEX 格式 |

## 修改文件清单

### 板级配置 (`boards/openbl/f4bl/`)

| 文件 | 说明 |
|------|------|
| `default.px4board` | PX4 模块/驱动/串口映射配置 |
| `firmware.prototype` | 固件元数据 (board_id=18880) |
| `init/rc.board_defaults` | 默认参数 (BAT, ATT_EN, SYS_HAS_MAG) |
| `init/rc.board_sensors` | 传感器启动脚本 (MPU6500, BMP280, SPL06) |
| `init/rc.board_extras` | OSD 启动脚本 |
| `src/board_config.h` | GPIO/ADC/PWM/LED 定义, BOARD_NUM_IO_TIMERS=3 |
| `src/timer_config.cpp` | PWM 定时器映射 (TIM8+TIM1+TIM2, 4 通道) |
| `src/spi.cpp` | SPI 总线设备声明 (MPU6500, OSD, SD) |
| `src/i2c.cpp` | I2C1 总线声明 |
| `src/init.c` | 板级初始化 (SPI, SD, Flash参数, ADC) |
| `src/led.c` | LED 控制 (PA14/PA13, 低电平有效) |
| `src/usb.c` | USB VBUS (始终报告在线) |
| `src/CMakeLists.txt` | 驱动编译定义 |
| `nuttx-config/include/board.h` | NuttX 时钟/引脚复用 (8MHz→168MHz) |
| `nuttx-config/include/board_dma_map.h` | DMA 流/通道分配 |
| `nuttx-config/nsh/defconfig` | NuttX 内核配置 |
| `nuttx-config/scripts/script.ld` | 链接脚本 (flash: 0x08010000, 960K) |

### PX4 框架修改

| 文件 | 说明 |
|------|------|
| `platforms/nuttx/src/px4/stm/stm32_common/io_pins/io_timer.c` | 添加 TIM1/TIM8 互补通道使能 (CCxNE+CCxNP) |

### NuttX Kconfig 路径修复 (编译环境相关)

| 文件 | 说明 |
|------|------|
| `platforms/nuttx/NuttX/apps/Kconfig` | 将 `/home/openbl/` 替换为 `/home/<username>/` |
| `platforms/nuttx/NuttX/apps/*/Kconfig` | 同上 (20 个子目录) |

## PWM 输出

| 通道 | 引脚 | 定时器 | 说明 |
|------|------|--------|------|
| 1 | PC9 | TIM8_CH4 | 电机 1 |
| 2 | PC8 | TIM8_CH3 | 电机 2 |
| 3 | PB15 | TIM1_CH3N | 电机 3 (互补通道, 需框架补丁) |
| 4 | PA8 | TIM1_CH1 | 电机 4 |

## 串口映射

| 硬件 | 设备 | PX4 命名 |
|------|------|----------|
| USART2 (PA2/PA3) | ttyS1 | TEL1 |
| UART5 (PC12/PD2) | ttyS2 | GPS1 |

## Bootloader

APM bootloader，基于 `hwdef-bl.dat` 编译。与 PX4 协议兼容。

构建:
```bash
cd /home/<username>/ardupilot
./waf configure --board OpenblF405RGT6 --bootloader
./waf bootloader
```

预编译 bootloader: `extras/openbl_f405_bootloader.bin`

## 烧录

```bash
# 首次: bootloader + 固件
STM32_Programmer_CLI -c port=usb1 -w extras/openbl_f405_bootloader.bin 0x08000000
STM32_Programmer_CLI -c port=usb1 -w openbl_f4bl_default.bin 0x08010000

# 仅固件 (QGC USB 直刷)
```

或 SD 卡: 将 `.px4` 复制到 SD 卡根目录，bootloader 自动刷写。
