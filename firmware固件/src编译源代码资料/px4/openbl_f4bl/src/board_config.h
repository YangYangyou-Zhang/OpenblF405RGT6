/****************************************************************************
 *
 *   Copyright (c) 2018, 2014 PX4 Development Team. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name PX4 nor the names of its contributors may be
 *    used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 ****************************************************************************/

/**
 * @file board_config.h
 *
 * openbl_f4bl internal definitions - based on verified APM OpenblF405RGT6 hwdef.dat
 */

#pragma once

/****************************************************************************************************
 * Included Files
 ****************************************************************************************************/

#include <px4_platform_common/px4_config.h>
#include <nuttx/compiler.h>
#include <stdint.h>

/****************************************************************************************************
 * Definitions
 ****************************************************************************************************/
/* Configuration ************************************************************************************/

/* openbl_f4bl GPIOs ********************************************************************************/
/* LEDs */
/* PA14 - Blue (ACT), active LOW */
/* PA13 - Green (B/E), active LOW */
#define GPIO_LED1       (GPIO_OUTPUT|GPIO_PUSHPULL|GPIO_SPEED_50MHz|GPIO_OUTPUT_CLEAR|GPIO_PORTA|GPIO_PIN14)
#define GPIO_LED_BLUE   GPIO_LED1

#define GPIO_LED2       (GPIO_OUTPUT|GPIO_PUSHPULL|GPIO_SPEED_50MHz|GPIO_OUTPUT_CLEAR|GPIO_PORTA|GPIO_PIN13)
#define GPIO_LED_GREEN  GPIO_LED2

#define BOARD_OVERLOAD_LED     LED_BLUE
#define BOARD_OVERLOAD_LED2    LED_GREEN

#define FLASH_BASED_PARAMS

/*
 * ADC channels
 *
 * These are the channel numbers of the ADCs of the microcontroller that can be used by the Px4 Firmware in the adc driver
 * PC4 = BATT_VOLTAGE_SENS (ADC1 Ch14)
 * PC5 = BATT_CURRENT_SENS (ADC1 Ch15)
 * PB0 = RSSI_ADC_PIN      (ADC1 Ch8)
 * PC0 = PRESSURE_SENS     (ADC1 Ch10)
 */
#define ADC_CHANNELS (1 << 8) | (1 << 10) | (1 << 14) | (1 << 15)

#define ADC_BATTERY_VOLTAGE_CHANNEL  14
#define ADC_BATTERY_CURRENT_CHANNEL  15
#define ADC_RC_RSSI_CHANNEL          8
#define ADC_AIRSPEED_VOLTAGE_CHANNEL 10

/* User GPIOs
 *
 * PWM output GPIOs matching APM OpenblF405RGT6 hwdef.dat:
 *   PC9  TIM8_CH4   TIM8  PWM(1)  GPIO(50)
 *   PC8  TIM8_CH3   TIM8  PWM(2)  GPIO(51)
 *   PB15 TIM1_CH3N  TIM1  PWM(3)  GPIO(52)
 *   PA8  TIM1_CH1   TIM1  PWM(4)  GPIO(53)
 *   PB11 TIM2_CH4   TIM2  PWM(5)  GPIO(54)
 *   PB10 TIM2_CH3   TIM2  PWM(6)  GPIO(55)
 *   PB3  TIM2_CH2   TIM2  PWM(7)  GPIO(56)
 *   PA15 TIM2_CH1   TIM2  PWM(8)  GPIO(57)
 *   PB14 TIM12_CH1  TIM12 PWM(9)  GPIO(58) NODMA
 *   PA6  TIM13_CH1  TIM13 PWM(10) GPIO(59) NODMA
 *   PB6  TIM4_CH1   TIM4  PWM(11) GPIO(60) NODMA
 *   PB1  TIM3_CH4   TIM3  PWM(12) GPIO(61)
 */

#define _MK_GPIO_INPUT(def) (((def) & (GPIO_PORT_MASK | GPIO_PIN_MASK)) | (GPIO_INPUT|GPIO_PULLUP))

#define GPIO_GPIO0_INPUT             _MK_GPIO_INPUT(GPIO_TIM8_CH4IN_1)
#define GPIO_GPIO1_INPUT             _MK_GPIO_INPUT(GPIO_TIM8_CH3IN_1)
#define GPIO_GPIO2_INPUT             _MK_GPIO_INPUT(GPIO_TIM1_CH3N_2)
#define GPIO_GPIO3_INPUT             _MK_GPIO_INPUT(GPIO_TIM1_CH1IN_1)

#define _MK_GPIO_OUTPUT(def) (((def) & (GPIO_PORT_MASK | GPIO_PIN_MASK)) | (GPIO_OUTPUT|GPIO_PUSHPULL|GPIO_SPEED_2MHz|GPIO_OUTPUT_CLEAR))

#define GPIO_GPIO0_OUTPUT            _MK_GPIO_OUTPUT(GPIO_TIM8_CH4OUT_1)
#define GPIO_GPIO1_OUTPUT            _MK_GPIO_OUTPUT(GPIO_TIM8_CH3OUT_1)
#define GPIO_GPIO2_OUTPUT            _MK_GPIO_OUTPUT(GPIO_TIM1_CH3N_2)
#define GPIO_GPIO3_OUTPUT            _MK_GPIO_OUTPUT(GPIO_TIM1_CH1OUT_1)
#define GPIO_GPIO4_OUTPUT            _MK_GPIO_OUTPUT(GPIO_TIM2_CH4OUT_2)
#define GPIO_GPIO5_OUTPUT            _MK_GPIO_OUTPUT(GPIO_TIM2_CH3OUT_2)
#define GPIO_GPIO6_OUTPUT            _MK_GPIO_OUTPUT(GPIO_TIM2_CH2OUT_2)
#define GPIO_GPIO7_OUTPUT            _MK_GPIO_OUTPUT(GPIO_TIM2_CH1OUT_2)
#define GPIO_GPIO8_OUTPUT            _MK_GPIO_OUTPUT(GPIO_TIM12_CH1OUT_2)
#define GPIO_GPIO9_OUTPUT            _MK_GPIO_OUTPUT(GPIO_TIM13_CH1OUT_1)
#define GPIO_GPIO10_OUTPUT           _MK_GPIO_OUTPUT(GPIO_TIM4_CH1OUT_1)
#define GPIO_GPIO11_OUTPUT           _MK_GPIO_OUTPUT(GPIO_TIM3_CH4OUT_1)

/* USB OTG FS
 *
 * PC5 OTG_FS_VBUS VBUS sensing
 */
//#define GPIO_OTGFS_VBUS     (GPIO_INPUT|GPIO_FLOAT|GPIO_SPEED_100MHz|GPIO_OPENDRAIN|GPIO_PORTC|GPIO_PIN5)

/* PWM */
#define BOARD_NUM_IO_TIMERS 3
#define DIRECT_PWM_OUTPUT_CHANNELS      4

/* High-resolution timer */
#define HRT_TIMER                    4 // T4C1
#define HRT_TIMER_CHANNEL            1 // use capture/compare channel 1

#define HRT_PPM_CHANNEL              3 // capture/compare channel 3
#define GPIO_PPM_IN                  (GPIO_ALT|GPIO_AF2|GPIO_PULLUP|GPIO_PORTA|GPIO_PIN3)

#define BOARD_SUPPORTS_RC_SERIAL_PORT_OUTPUT

/* This board provides a DMA pool and APIs */
#define BOARD_DMA_ALLOC_POOL_SIZE 5120

#define BOARD_HAS_ON_RESET 1

#define BOARD_ENABLE_CONSOLE_BUFFER
#define BOARD_CONSOLE_BUFFER_SIZE (1024*3)


__BEGIN_DECLS

/****************************************************************************************************
 * Public Types
 ****************************************************************************************************/

/****************************************************************************************************
 * Public data
 ****************************************************************************************************/

#ifndef __ASSEMBLY__

/****************************************************************************************************
 * Public Functions
 ****************************************************************************************************/

/****************************************************************************************************
 * Name: stm32_spiinitialize
 *
 * Description:
 *   Called to configure SPI chip select GPIO pins for the PX4FMU board.
 *
 ****************************************************************************************************/

extern void stm32_spiinitialize(void);


/****************************************************************************************************
 * Name: stm32_usbinitialize
 *
 * Description:
 *   Called to configure USB IO.
 *
 ****************************************************************************************************/

extern void stm32_usbinitialize(void);

extern void board_peripheral_reset(int ms);

#include <px4_platform_common/board_common.h>

#endif /* __ASSEMBLY__ */

__END_DECLS
