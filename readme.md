包含一个5v-dcdc（bec），一个大疆高清图传（可拓展4G数传）直插口，sbus接口，elrs接收机接口，gps接口，
icm42605/42688p（mpu6500）加速度计，SPL06（bmp280）气压计，12组PWM输出（支持dshut）。
目前已编译和兼容APM、INAV、BF平台，px4平台代码迁移工作进行中。
It includes a 5v-dcdc (bec), a DJI high-definition image transmission (expandable to 4G data transmission) direct plug-in port, SBUS interface, ELRS receiver interface, and GPS interface,
ICM42605/42688P (MPU6500) accelerometer, SPL06 (BMP280) barometer, 12 sets of PWM outputs (supporting DSHUT).
Currently, it has been compiled and is compatible with APM, INAV, and BF platforms, with the code migration to the PX4 platform in progress.

请注意，使用APM固件时，如果不使用sbus接收机想要释放uart2号串口用于接elrs接收机或者数传链路设备时，
需要修改参数表BRD_ALT_CONFIG 引脚功能复用值为1（默认为0）来禁用sbus和释放uart为通用模式。
由于没有黑匣子芯片（原版要预留拓展的，后来放弃了）需要设置LOG_BACKEND_TYPE = 0，禁用日志功能。
Please note that when using APM firmware, if you want to free up UART2 serial port for connecting an ELRS receiver or a telemetry link device without using an SBus receiver,
The parameter table BRD_ALT_CONFIG needs to be modified by setting the pin function multiplexing value to 1 (default is 0) to disable SBus and release UART to general-purpose mode.
Due to the absence of a black box chip (originally intended for expansion but later abandoned), it is necessary to set LOG_BACKEND_TYPE = 0 to disable the logging function

PCB_BOM:https://oshwhub.com/yangyangyou/stm32f405_bl_matekf405_te_copy
请注意:此电路板为matekf405_te的改进版本，固件并不兼容。
Please note: This circuit board is an improved version of matekf405_te, and the firmware is not compatible.


![p1](p1.png)
![p1](p1.png)