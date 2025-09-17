/**
  ******************************************************************************
  * @file    stm32c5xx_hal_rcc.c
  * @author  GPM Application Team
  * @brief   RCC HAL module driver.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32_hal.h"

/** @addtogroup STM32C5xx_HAL_Driver
  * @{
  */

/** @defgroup RCC RCC
  * @{
This file provides firmware functions to manage the following
functionalities of the Reset and Clock Control (RCC) peripheral:

- Configuration and reset functions
- Oscillators and Peripherals Control functions
- Bus configuration functions

Main APIs are not allowed to perform any other actions that their main objectif (for instance, it is not allowed to
disable a PLL or an oscillator inside an enable function).

For performance reasons, few functionalities are not supported by the HAL driver but these functionalities are covered
by the LL driver (for instance, interrupt management).

The driver is responsible of the update of SystemCoreClock variable (used by CMSIS) and System tick.

## RCC specific features

After exiting from standby or reset, the device is running from High Speed Internal System (HSI) oscillator
(by default to 16MHz).

- There is no prescaler on High speed (AHBs) and Low speed (APBs) busses:
all peripherals mapped on these busses are running at sysclk frequency.
- The clock for all peripherals is switched off, except the SRAM and FLASH.

Once the device started from reset, the user application could:

- Configure the clock source to be used to drive the System clock
(if the application needs higher frequency/performance)
- Configure the System clock frequency and Flash settings
- Configure the AHB and APB busses prescalers
- Enable the clock for the peripheral(s) to be used
- Configure the clock source(s) for peripherals which clocks receive an independent kernel clocks.
- Configure peripherals supporting the autonomous mode (These peripherals are able to generate a kernel clock
request and a AHB/APB bus clock request when they need, in order to operate and update their status register
even in Stop mode).

## Configuration inside the RCC driver

Config defines            | Description               | Default value | Note
------------------------- | ------------------------- | ------------- | ------------------------------------
PRODUCT                   | from IDE                  | Defined       | The selected product (ex STM32C562xx)
PERIPHERAL                | from CMSIS                | Defined       | Peripheral available on the selected product
USE_ASSERT_DBG_PARAM      | from IDE                  | None          | When defined, enable the params assert
USE_HAL_CHECK_PARAM       | from hal_conf.h           | 0             | When set, parameters are checked in runtime
USE_HAL_RCC_MODULE        | from hal_conf.h           | 1             | When set, HAL RCC module is enabled
USE_EXTERNAL_ENV          | from IDE                  | Defined       | When set, ext. oscillators values are defined
LSE_VALUE                 | From stm32_external_env.h | 32 KHz        | Frequency of LSE oscillator (USE_EXTERNAL_ENV)
HSE_VALUE                 | From stm32_external_env.h | 32 MHz        | Frequency of HSE oscillator (USE_EXTERNAL_ENV)
HSI_VALUE                 | st32c5xxxx.h              | 64 MHz        | Frequency of HSI oscillator
HSI48_VALUE               | st32c5xxxx.h              | 48 MHz        | Frequency of HSI48 oscillator
HSI_RESET_VALUE           | st32c5xxxx.h              | 48 MHz        | Frequency of system core clock after reset
USE_HAL_RCC_RESET_PERIPH_CLOCK_MANAGEMENT   | from hal_conf.h  | 0    | When set, RCC peripherals configuration reset
USE_HAL_RCC_RESET_RTC_DOMAIN                | from hal_conf.h  | 0    | When set, Resources under backup domain reset
  *
  */


#if defined(USE_HAL_RCC_MODULE) && (USE_HAL_RCC_MODULE == 1)

/* Private typedef -----------------------------------------------------------*/
/** @defgroup RCC_Private_Typedef RCC Private Type definition
  * @{
  */
typedef  uint32_t (*rcc_cb_timeout_t)(void); /*!< RCC internal Callback pointer definition */
/**
  * @}
  */

/* Private constants ---------------------------------------------------------*/
/** @defgroup RCC_Private_Constants RCC Private Constants and enumerations
  * @{
  */
/**
  * @brief Timeout values
  * @{
  */
#if defined(HSE_VALUE)
#define RCC_HSE_TIMEOUT_VALUE         HSE_STARTUP_TIMEOUT /*!< HSE Timeout value                                */
#endif /* HSE_VALUE */
#if defined(LSE_VALUE)
#define RCC_LSE_TIMEOUT_VALUE         LSE_STARTUP_TIMEOUT /*!< LSE Timeout value                                */
#endif /* LSE_VALUE */
#define RCC_LSI_TIMEOUT_VALUE         ((20u * 128u * 1000u) / LSI_VALUE) /*!< 80 ms for LSI at 32KHz            */
#define RCC_HSI_TIMEOUT_VALUE         2UL    /*!< 2 ms (minimum Tick + 1)                                       */
#define RCC_PSI_TIMEOUT_VALUE         2UL    /*!< 2 ms (minimum Tick + 1)                                       */
#define RCC_CLOCKSWITCH_TIMEOUT_VALUE 5000UL /*!< 5 s                                                           */

/**
  * @}
  */

/**
  * @brief PSI Output values
  * @{
  */
#define PSI_LSE_100 100016000U
#define PSI_LSE_144 144015000U
#define PSI_LSE_160 160006000U
#define PSI_NOT_LSE_100 100000000U
#define PSI_NOT_LSE_144 144000000U
#define PSI_NOT_LSE_160 160000000U

/**
  * @}
  */

/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/
/** @defgroup RCC_Private_Macros RCC Private Macros
  * @{
  */
#if defined(HSE_VALUE)
#define IS_RCC_HSE_MODE_ENABLE(mode)  (((mode) == HAL_RCC_HSE_ON)                  \
                                       || ((mode) == HAL_RCC_HSE_BYPASS)           \
                                       ||((mode) == HAL_RCC_HSE_BYPASS_DIGITAL))

#endif /* HSE_VALUE */
#if defined(LSE_VALUE)
#define IS_RCC_LSE_MODE_ENABLE(mode)  (((mode) == HAL_RCC_LSE_ON)                  \
                                       || ((mode) == HAL_RCC_LSE_BYPASS)           \
                                       || ((mode) == HAL_RCC_LSE_BYPASS_DIGITAL))

#define IS_RCC_LSE_DRIVE(drive) (((drive) == HAL_RCC_LSE_DRIVE_LOW)                \
                                 || ((drive) == HAL_RCC_LSE_DRIVE_MEDIUMLOW)       \
                                 || ((drive) == HAL_RCC_LSE_DRIVE_MEDIUMHIGH)      \
                                 || ((drive) == HAL_RCC_LSE_DRIVE_HIGH))

#endif /* LSE_VALUE */
#define IS_RCC_HSIS(hsi) (((hsi) == HAL_RCC_HSIS_OFF) || ((hsi) == HAL_RCC_HSIS_ON))

#define IS_RCC_HSIDIV3(hsi)  (((hsi) == HAL_RCC_HSIDIV3_OFF) || ((hsi) == HAL_RCC_HSIDIV3_ON))

#define IS_RCC_HSIK(hsi)  (((hsi) == HAL_RCC_HSIK_OFF) || ((hsi) == HAL_RCC_HSIK_ON))

#define IS_RCC_HSIKDIV(div) (((div) == HAL_RCC_HSIK_DIV1) || ((div) == HAL_RCC_HSIK_DIV1_5)       \
                             || ((div) == HAL_RCC_HSIK_DIV2) || ((div) == HAL_RCC_HSIK_DIV2_5)    \
                             || ((div) == HAL_RCC_HSIK_DIV3) || ((div) == HAL_RCC_HSIK_DIV3_5)    \
                             || ((div) == HAL_RCC_HSIK_DIV4) || ((div) == HAL_RCC_HSIK_DIV4_5)    \
                             || ((div) == HAL_RCC_HSIK_DIV5) || ((div) == HAL_RCC_HSIK_DIV5_5)    \
                             || ((div) == HAL_RCC_HSIK_DIV6) || ((div) == HAL_RCC_HSIK_DIV6_5)    \
                             || ((div) == HAL_RCC_HSIK_DIV7) || ((div) == HAL_RCC_HSIK_DIV7_5)    \
                             || ((div) == HAL_RCC_HSIK_DIV8))

#define IS_RCC_PSIS(psi)  (((psi) == HAL_RCC_PSIS_OFF) || ((psi) == HAL_RCC_PSIS_ON))

#define IS_RCC_PSIDIV3(psi)  (((psi) == HAL_RCC_PSIDIV3_OFF) || ((psi) == HAL_RCC_PSIDIV3_ON))

#define IS_RCC_PSIK(psi)  (((psi) == HAL_RCC_PSIK_OFF) || ((psi) == HAL_RCC_PSIK_ON))

#define IS_RCC_PSIKDIV(div) (((div) == HAL_RCC_PSIK_DIV1) || ((div) == HAL_RCC_PSIK_DIV1_5)       \
                             || ((div) == HAL_RCC_PSIK_DIV2) || ((div) == HAL_RCC_PSIK_DIV2_5)    \
                             || ((div) == HAL_RCC_PSIK_DIV3) || ((div) == HAL_RCC_PSIK_DIV3_5)    \
                             || ((div) == HAL_RCC_PSIK_DIV4) || ((div) == HAL_RCC_PSIK_DIV4_5)    \
                             || ((div) == HAL_RCC_PSIK_DIV5) || ((div) == HAL_RCC_PSIK_DIV5_5)    \
                             || ((div) == HAL_RCC_PSIK_DIV6) || ((div) == HAL_RCC_PSIK_DIV6_5)    \
                             || ((div) == HAL_RCC_PSIK_DIV7) || ((div) == HAL_RCC_PSIK_DIV7_5)    \
                             || ((div) == HAL_RCC_PSIK_DIV8))

#define IS_RCC_PSISOURCE(src) (((src) == HAL_RCC_PSI_SRC_HSE) || ((src) == HAL_RCC_PSI_SRC_LSE) \
                               || ((src) == HAL_RCC_PSI_SRC_HSI_8MHz))

#define IS_RCC_PSIREF(ref) (((ref) == HAL_RCC_PSI_REF_32768HZ) || ((ref) == HAL_RCC_PSI_REF_8MHZ)   \
                            || ((ref) == HAL_RCC_PSI_REF_16MHZ) || ((ref) == HAL_RCC_PSI_REF_24MHZ) \
                            || ((ref) == HAL_RCC_PSI_REF_25MHZ) || ((ref) == HAL_RCC_PSI_REF_32MHZ) \
                            || ((ref) == HAL_RCC_PSI_REF_48MHZ) || ((ref) == HAL_RCC_PSI_REF_50MHZ))

#define IS_RCC_PSIOUT(out) (((out) == HAL_RCC_PSI_OUT_100MHZ) || ((out) == HAL_RCC_PSI_OUT_144MHZ)  \
                            || ((out) == HAL_RCC_PSI_OUT_160MHZ))


#define IS_RCC_LSI(lsi)  (((lsi) == HAL_RCC_LSI_OFF) || ((lsi) == HAL_RCC_LSI_ON))

#define IS_RCC_CLOCKTYPE(clk) ((1U <= (clk)) && ((clk) <= 0x1FU))

#define IS_RCC_ITEM_ATTRIBUTES(item) ((0U < (item)) && ((item) <= 0x1FFFU))

#define IS_RCC_STOP_WAKEUPCLOCK(source) (((source) == HAL_RCC_STOP_WAKEUPCLOCK_HSIDIV3)        \
                                         || ((source) == HAL_RCC_STOP_WAKEUPCLOCK_HSIS))

#define IS_RCC_PERIPHCLOCK(selection)   ((((selection) & HAL_RCC_PERIPHCLOCK_ALL) != 0x00u)    \
                                         && (((selection) & ~HAL_RCC_PERIPHCLOCK_ALL) == 0x00u))

#define IS_RCC_SYSCLKSOURCE(source) (((source) == HAL_RCC_SYSCLK_SRC_HSIS)        \
                                     || ((source) == HAL_RCC_SYSCLK_SRC_HSIDIV3)  \
                                     || ((source) == HAL_RCC_SYSCLK_SRC_HSE)      \
                                     || ((source) == HAL_RCC_SYSCLK_SRC_PSIS))

#define IS_RCC_HCLK(hclk) (((hclk) == HAL_RCC_HCLK_PRESCALER1) || ((hclk) == HAL_RCC_HCLK_PRESCALER2)        \
                           || ((hclk) == HAL_RCC_HCLK_PRESCALER4) || ((hclk) == HAL_RCC_HCLK_PRESCALER8)     \
                           || ((hclk) == HAL_RCC_HCLK_PRESCALER16) || ((hclk) == HAL_RCC_HCLK_PRESCALER64)   \
                           || ((hclk) == HAL_RCC_HCLK_PRESCALER128) || ((hclk) == HAL_RCC_HCLK_PRESCALER256) \
                           || ((hclk) == HAL_RCC_HCLK_PRESCALER512))

#define IS_RCC_PCLK(pclk) (((pclk) == HAL_RCC_PCLK_PRESCALER1) || ((pclk) == HAL_RCC_PCLK_PRESCALER2)        \
                           || ((pclk) == HAL_RCC_PCLK_PRESCALER4) || ((pclk) == HAL_RCC_PCLK_PRESCALER8)     \
                           || ((pclk) == HAL_RCC_PCLK_PRESCALER16))

#define IS_RCC_MCOSOURCE(source)  (((source) == HAL_RCC_MCO1_SRC_SYSCLK)      \
                                   || ((source) == HAL_RCC_MCO1_SRC_HSE)      \
                                   || ((source) == HAL_RCC_MCO1_SRC_LSE)      \
                                   || ((source) == HAL_RCC_MCO1_SRC_LSI)      \
                                   || ((source) == HAL_RCC_MCO1_SRC_PSIK)     \
                                   || ((source) == HAL_RCC_MCO1_SRC_HSIK)     \
                                   || ((source) == HAL_RCC_MCO1_SRC_PSIS)     \
                                   || ((source) == HAL_RCC_MCO1_SRC_HSIS)     \
                                   || ((source) == HAL_RCC_MCO2_SRC_SYSCLK)   \
                                   || ((source) == HAL_RCC_MCO2_SRC_HSE)      \
                                   || ((source) == HAL_RCC_MCO2_SRC_LSE)      \
                                   || ((source) == HAL_RCC_MCO2_SRC_LSI)      \
                                   || ((source) == HAL_RCC_MCO2_SRC_PSIK)     \
                                   || ((source) == HAL_RCC_MCO2_SRC_HSIK)     \
                                   || ((source) == HAL_RCC_MCO2_SRC_PSIDIV3)  \
                                   || ((source) == HAL_RCC_MCO2_SRC_HSIDIV3))

#define IS_RCC_MCOPRE(div) (((div) == HAL_RCC_MCO1_NO_CLK) || ((div) == HAL_RCC_MCO1_PRESCALER1)     \
                            || ((div) == HAL_RCC_MCO1_PRESCALER2) || ((div) == HAL_RCC_MCO1_PRESCALER3)    \
                            || ((div) == HAL_RCC_MCO1_PRESCALER4) || ((div) == HAL_RCC_MCO1_PRESCALER5)    \
                            || ((div) == HAL_RCC_MCO1_PRESCALER6) || ((div) == HAL_RCC_MCO1_PRESCALER7)    \
                            || ((div) == HAL_RCC_MCO1_PRESCALER8) || ((div) == HAL_RCC_MCO1_PRESCALER9)    \
                            || ((div) == HAL_RCC_MCO1_PRESCALER10) || ((div) == HAL_RCC_MCO1_PRESCALER11)  \
                            || ((div) == HAL_RCC_MCO1_PRESCALER12) || ((div) == HAL_RCC_MCO1_PRESCALER13)  \
                            || ((div) == HAL_RCC_MCO1_PRESCALER14) || ((div) == HAL_RCC_MCO1_PRESCALER15)  \
                            || ((div) == HAL_RCC_MCO2_NO_CLK) || ((div) == HAL_RCC_MCO2_PRESCALER1)  \
                            || ((div) == HAL_RCC_MCO2_PRESCALER2) || ((div) == HAL_RCC_MCO2_PRESCALER3)    \
                            || ((div) == HAL_RCC_MCO2_PRESCALER4) || ((div) == HAL_RCC_MCO2_PRESCALER5)    \
                            || ((div) == HAL_RCC_MCO2_PRESCALER6) || ((div) == HAL_RCC_MCO2_PRESCALER7)    \
                            || ((div) == HAL_RCC_MCO2_PRESCALER8) || ((div) == HAL_RCC_MCO2_PRESCALER9)    \
                            || ((div) == HAL_RCC_MCO2_PRESCALER10) || ((div) == HAL_RCC_MCO2_PRESCALER11)  \
                            || ((div) == HAL_RCC_MCO2_PRESCALER12) || ((div) == HAL_RCC_MCO2_PRESCALER13)  \
                            || ((div) == HAL_RCC_MCO2_PRESCALER14) || ((div) == HAL_RCC_MCO2_PRESCALER15))

#define IS_RCC_LSCOSOURCE(source) (((source) == HAL_RCC_LSCO_SRC_LSI)     \
                                   || ((source) == HAL_RCC_LSCO_SRC_LSE))

#define IS_RCC_ATTRIBUTES(__ATTRIBUTES__)       (((__ATTRIBUTES__)  == RCC_ATTR)           \
                                                 || ((__ATTRIBUTES__)  == RCC_ATTR_PRIV)   \
                                                 || ((__ATTRIBUTES__)  == RCC_ATTR_NPRIV))

#define IS_RCC_USART1_CLK(source)                  \
  (((source) == HAL_RCC_USART1_CLK_SRC_PCLK2)      \
   || ((source) == HAL_RCC_USART1_CLK_SRC_PSIK)    \
   || ((source) == HAL_RCC_USART1_CLK_SRC_HSIK)    \
   || ((source) == HAL_RCC_USART1_CLK_SRC_LSE))

#define IS_RCC_USART2_CLK(source)                  \
  (((source) == HAL_RCC_USART2_CLK_SRC_PCLK1)      \
   || ((source) == HAL_RCC_USART2_CLK_SRC_PSIK)    \
   || ((source) == HAL_RCC_USART2_CLK_SRC_HSIK)    \
   || ((source) == HAL_RCC_USART2_CLK_SRC_LSE))
#if defined(USART3)

#define IS_RCC_USART3_CLK(source)                  \
  (((source) == HAL_RCC_USART3_CLK_SRC_PCLK1)      \
   || ((source) == HAL_RCC_USART3_CLK_SRC_PSIK)    \
   || ((source) == HAL_RCC_USART3_CLK_SRC_HSIK)    \
   || ((source) == HAL_RCC_USART3_CLK_SRC_LSE))
#endif /* USART3 */

#define IS_RCC_UART4_CLK(source)                  \
  (((source) == HAL_RCC_UART4_CLK_SRC_PCLK1)      \
   || ((source) == HAL_RCC_UART4_CLK_SRC_PSIK)    \
   || ((source) == HAL_RCC_UART4_CLK_SRC_HSIK)    \
   || ((source) == HAL_RCC_UART4_CLK_SRC_LSE))

#define IS_RCC_UART5_CLK(source)                  \
  (((source) == HAL_RCC_UART5_CLK_SRC_PCLK1)      \
   || ((source) == HAL_RCC_UART5_CLK_SRC_PSIK)    \
   || ((source) == HAL_RCC_UART5_CLK_SRC_HSIK)    \
   || ((source) == HAL_RCC_UART5_CLK_SRC_LSE))
#if defined(USART6)

#define IS_RCC_USART6_CLK(source)                 \
  (((source) == HAL_RCC_USART6_CLK_SRC_PCLK1)     \
   || ((source) == HAL_RCC_USART6_CLK_SRC_PSIK)   \
   || ((source) == HAL_RCC_USART6_CLK_SRC_HSIK)   \
   || ((source) == HAL_RCC_USART6_CLK_SRC_LSE))
#endif /* USART6 */
#if defined(USART7)

#define IS_RCC_UART7_CLK(source)                  \
  (((source) == HAL_RCC_UART7_CLK_SRC_PCLK1)      \
   || ((source) == HAL_RCC_UART7_CLK_SRC_PSIK)    \
   || ((source) == HAL_RCC_UART7_CLK_SRC_HSIK)    \
   || ((source) == HAL_RCC_UART7_CLK_SRC_LSE))
#endif /* USART7 */

#define IS_RCC_LPUART1_CLK(source)                \
  (((source) == HAL_RCC_LPUART1_CLK_SRC_PCLK3)    \
   || ((source) == HAL_RCC_LPUART1_CLK_SRC_HSIK)  \
   || ((source) == HAL_RCC_LPUART1_CLK_SRC_LSE)   \
   || ((source) == HAL_RCC_LPUART1_CLK_SRC_LSI))

#define IS_RCC_SPI1_CLK(source)                   \
  (((source) == HAL_RCC_SPI1_CLK_SRC_PCLK2)       \
   || ((source) == HAL_RCC_SPI1_CLK_SRC_PSIK)     \
   || ((source) == HAL_RCC_SPI1_CLK_SRC_HSIK)     \
   || ((source) == HAL_RCC_SPI1_CLK_SRC_AUDIOCLK))

#define IS_RCC_SPI2_CLK(source)                   \
  (((source) == HAL_RCC_SPI2_CLK_SRC_PCLK1)       \
   || ((source) == HAL_RCC_SPI2_CLK_SRC_PSIK)     \
   || ((source) == HAL_RCC_SPI2_CLK_SRC_HSIK)     \
   || ((source) == HAL_RCC_SPI2_CLK_SRC_AUDIOCLK))
#if defined(SPI3)

#define IS_RCC_SPI3_CLK(source)                   \
  (((source) == HAL_RCC_SPI3_CLK_SRC_PCLK1)       \
   || ((source) == HAL_RCC_SPI3_CLK_SRC_PSIK)     \
   || ((source) == HAL_RCC_SPI3_CLK_SRC_HSIK)     \
   || ((source) == HAL_RCC_SPI3_CLK_SRC_AUDIOCLK))
#endif /* SPI3 */
#if defined(FDCAN1)

#define IS_RCC_FDCAN_CLK(source)                  \
  (((source) == HAL_RCC_FDCAN_CLK_SRC_PCLK1)      \
   || ((source) == HAL_RCC_FDCAN_CLK_SRC_PSIS)    \
   || ((source) == HAL_RCC_FDCAN_CLK_SRC_PSIK)    \
   || ((source) == HAL_RCC_FDCAN_CLK_SRC_HSE))
#endif /* FDCAN1 */

#define IS_RCC_I2C1_CLK(source)                   \
  (((source) == HAL_RCC_I2C1_CLK_SRC_PCLK1)       \
   || ((source) == HAL_RCC_I2C1_CLK_SRC_PSIK)     \
   || ((source) == HAL_RCC_I2C1_CLK_SRC_HSIK))
#if defined(I2C2)

#define IS_RCC_I2C2_CLK(source)                   \
  (((source) == HAL_RCC_I2C2_CLK_SRC_PCLK1)       \
   || ((source) == HAL_RCC_I2C2_CLK_SRC_PSIK)     \
   || ((source) == HAL_RCC_I2C2_CLK_SRC_HSIK))
#endif /* I2C2 */

#define IS_RCC_I3C1_CLK(source)                   \
  (((source) == HAL_RCC_I3C1_CLK_SRC_PCLK1)       \
   || ((source) == HAL_RCC_I3C1_CLK_SRC_PSIK)      \
   || ((source) == HAL_RCC_I3C1_CLK_SRC_HSIK))

#define IS_RCC_ADCDAC_CLK(source)                 \
  (((source) == HAL_RCC_ADCDAC_CLK_SRC_HCLK)      \
   || ((source) == HAL_RCC_ADCDAC_CLK_SRC_PSIS)   \
   || ((source) == HAL_RCC_ADCDAC_CLK_SRC_PSIK)   \
   || ((source) == HAL_RCC_ADCDAC_CLK_SRC_HSIK))

#define IS_RCC_DAC1_CLK(source) \
  (((source) == HAL_RCC_DAC1_SH_CLK_SRC_LSE)         \
   || ((source) == HAL_RCC_DAC1_SH_CLK_SRC_LSI))

#define IS_RCC_ADCDAC_PRESCALER(prescaler)          \
  (((prescaler) == HAL_RCC_ADCDAC_PRESCALER1)       \
   || ((prescaler) == HAL_RCC_ADCDAC_PRESCALER2)    \
   || ((prescaler) == HAL_RCC_ADCDAC_PRESCALER4)    \
   || ((prescaler) == HAL_RCC_ADCDAC_PRESCALER8)    \
   || ((prescaler) == HAL_RCC_ADCDAC_PRESCALER16)   \
   || ((prescaler) == HAL_RCC_ADCDAC_PRESCALER32)   \
   || ((prescaler) == HAL_RCC_ADCDAC_PRESCALER64)   \
   || ((prescaler) == HAL_RCC_ADCDAC_PRESCALER128))

#define IS_RCC_LPTIM1_CLK(source)                 \
  (((source) == HAL_RCC_LPTIM1_CLK_SRC_PCLK3)     \
   || ((source) == HAL_RCC_LPTIM1_CLK_SRC_HSIK)   \
   || ((source) == HAL_RCC_LPTIM1_CLK_SRC_LSE)    \
   || ((source) == HAL_RCC_LPTIM1_CLK_SRC_LSI))

#define IS_RCC_RTC_CLK(source)                    \
  (((source) == HAL_RCC_RTC_CLK_SRC_NO_CLK)       \
   || ((source) == HAL_RCC_RTC_CLK_SRC_LSE)       \
   || ((source) == HAL_RCC_RTC_CLK_SRC_LSI)       \
   || ((source) == HAL_RCC_RTC_CLK_SRC_HSE_DIV))

#define IS_RCC_RTC_HSEDIV(div)      ((div) <= 511U)

#define IS_RCC_CK48_CLK(source)                   \
  (((source) == HAL_RCC_CK48_CLK_SRC_PSIDIV3)     \
   || ((source) == HAL_RCC_CK48_CLK_SRC_HSIDIV3)  \
   || ((source) == HAL_RCC_CK48_CLK_SRC_HSE))
#if defined(XSPI1)

#define IS_RCC_XSPI1_CLK(source)                  \
  (((source) == HAL_RCC_XSPI1_CLK_SRC_HCLK)       \
   || ((source) == HAL_RCC_XSPI1_CLK_SRC_PSIK)    \
   || ((source) == HAL_RCC_XSPI1_CLK_SRC_HSIK))
#endif /* XSPI1 */
#if defined(ETH)

#define IS_RCC_ETHREF_CLK(source)                 \
  (((source) == HAL_RCC_ETHREF_CLK_SRC_RMII)      \
   || ((source) == HAL_RCC_ETHREF_CLK_SRC_FB))

#define IS_RCC_ETHPTP_CLK(source)                 \
  (((source) == HAL_RCC_ETHPTP_CLK_SRC_NONE)      \
   || ((source) == HAL_RCC_ETHPTP_CLK_SRC_HCLK)   \
   || ((source) == HAL_RCC_ETHPTP_CLK_SRC_PSIS)   \
   || ((source) == HAL_RCC_ETHPTP_CLK_SRC_PSIK))

#define IS_RCC_ETH_CLK(source)                    \
  (((source) == HAL_RCC_ETH_CLK_SRC_NONE)         \
   || ((source) == HAL_RCC_ETH_CLK_SRC_PSIS)      \
   || ((source) == HAL_RCC_ETH_CLK_SRC_PSIK)      \
   || ((source) == HAL_RCC_ETH_CLK_SRC_HSE))

#define IS_RCC_ETH_PRESCALER(prescaler)           \
  (((prescaler) == LL_RCC_ETH_DIV_1)              \
   || ((prescaler) == LL_RCC_ETH_DIV_2)           \
   || ((prescaler) == LL_RCC_ETH_DIV_4))

#define IS_RCC_ETHPTP_PRESCALER(prescaler)        \
  (((prescaler) == LL_RCC_ETHPTP_DIV_1)           \
   || ((prescaler) == LL_RCC_ETHPTP_DIV_2)        \
   || ((prescaler) == LL_RCC_ETHPTP_DIV_3)        \
   || ((prescaler) == LL_RCC_ETHPTP_DIV_4)        \
   || ((prescaler) == LL_RCC_ETHPTP_DIV_5)        \
   || ((prescaler) == LL_RCC_ETHPTP_DIV_6)        \
   || ((prescaler) == LL_RCC_ETHPTP_DIV_7)        \
   || ((prescaler) == LL_RCC_ETHPTP_DIV_8))
#endif /* ETH */

#define IS_RCC_SYSTICK_CLK(source) (((source) == HAL_RCC_SYSTICK_CLK_SRC_HCLK_DIV8)    \
                                    || ((source) == HAL_RCC_SYSTICK_CLK_SRC_LSE)         \
                                    || ((source) == HAL_RCC_SYSTICK_CLK_SRC_LSI))

#define RCC_UPDATE_SYSTEMCORECLOCK()  (SystemCoreClock = (HAL_RCC_GetSYSCLKFreq() >> \
                                                          (AHBPrescTable[LL_RCC_GetAHBPrescaler()])))

/**
  * @brief Get the ADC kernel clock divider
  */
#define RCC_ADCDIV_BIT_VALUE  ((LL_RCC_GetADCPrescaler() >> RCC_CCIPR2_ADCDACPRE_Pos))
#define RCC_GET_ADC_DIVIDER() ((RCC_ADCDIV_BIT_VALUE) == 0x0U ? 1U :   \
                               (RCC_ADCDIV_BIT_VALUE) == 0x1U ? 2U :   \
                               (RCC_ADCDIV_BIT_VALUE) == 0x2U ? 4U :   \
                               (RCC_ADCDIV_BIT_VALUE) == 0x3U ? 8U :   \
                               (RCC_ADCDIV_BIT_VALUE) == 0x4U ? 16U :  \
                               (RCC_ADCDIV_BIT_VALUE) == 0x5U ? 32U :  \
                               (RCC_ADCDIV_BIT_VALUE) == 0x6U ? 64U :  \
                               (RCC_ADCDIV_BIT_VALUE) == 0x7U ? 128U : 1U)
/**
  * @}
  */

#if defined(ETH)
/**
  * @brief Get the ETH kernel clock divider
  */
#define RCC_ETHDIV_BIT_VALUE  ((LL_RCC_GetETHPrescaler() >> RCC_CCIPR3_ETHCLKDIVSEL_Pos))
#define RCC_GET_ETH_DIVIDER() ((RCC_ETHDIV_BIT_VALUE) == 0x0U ? 1U :   \
                               (RCC_ETHDIV_BIT_VALUE) == 0x1U ? 2U :   \
                               (RCC_ETHDIV_BIT_VALUE) == 0x2U ? 4U : 1U)

/**
  * @brief Get the ETHPTP kernel clock divider
  */
#define RCC_ETHPTPDIV_BIT_VALUE  ((LL_RCC_GetETHPTPPrescaler() >> RCC_CCIPR3_ETHPTPDIVSEL_Pos))
#define RCC_GET_ETHPTP_DIVIDER() ((RCC_ETHPTPDIV_BIT_VALUE) == 0x0U ? 1U :   \
                                  (RCC_ETHPTPDIV_BIT_VALUE) == 0x1U ? 2U :   \
                                  (RCC_ETHPTPDIV_BIT_VALUE) == 0x2U ? 4U : 1U)

/**
  * @}
  */

#endif /* ETH */
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/** @defgroup RCC_Private_Functions RCC Private Functions
  * @{
  */
static hal_status_t RCC_WaitForTimeout(const rcc_cb_timeout_t p_timeout_cb, uint32_t timeout, uint32_t status);
static uint32_t RCC_GetDividerValue(uint32_t divider);
/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/

/** @addtogroup RCC_Exported_Functions
  * @{
  */

/** @addtogroup RCC_Exported_Functions_Group1
  * @{
  */

/** @addtogroup RCC_Exported_Functions_Group1_0
  * @{
  */

/**
  * @brief   Reset the RCC clock configuration to the default reset state.
  * @note    SystemCoreClock and HAL timebase are updated in this function.
  * @note    Resources under backup domain reset if USE_HAL_RCC_RESET_RTC_DOMAIN set to 1U
  * @note    Peripherals clock enable and source selection reset if USE_HAL_RCC_RESET_PERIPH_CLOCK_MANAGEMENT set to 1U
  * @warning Access to RTC domain must be enabled to disable RTC domain source clock.
  */
void HAL_RCC_Reset(void)
{
  uint32_t tickstart;
  uint32_t read_value;

  /* Disable RCC interrupts */
  LL_RCC_DisableIT(LL_RCC_IT_LSIRDY | LL_RCC_IT_LSERDY | LL_RCC_IT_HSIRDY | LL_RCC_IT_HSIDIV3RDY | \
                   LL_RCC_IT_HSIKRDY | LL_RCC_IT_PSIRDY | LL_RCC_IT_PSIDIV3RDY | LL_RCC_IT_PSIKRDY | LL_RCC_IT_HSERDY);

#if defined(USE_HAL_RCC_RESET_PERIPH_CLOCK_MANAGEMENT) && (USE_HAL_RCC_RESET_PERIPH_CLOCK_MANAGEMENT == 1U)
  /* Reset peripheral clock enable */
  read_value = LL_RCC_READ_REG(CFGR2);
#define RCC_CFGR2_RESET (RCC_CFGR2_AHB1DIS |\
                         RCC_CFGR2_AHB2DIS | RCC_CFGR2_APB1DIS | RCC_CFGR2_APB2DIS | RCC_CFGR2_APB3DIS)
  LL_RCC_WRITE_REG(CFGR2, (read_value & ~RCC_CFGR2_RESET));

  LL_AHB1_GRP1_DisableClock(LL_AHB2_GRP1_PERIPH_ALL & (~(RCC_AHB1ENR_FLITFEN | RCC_AHB1ENR_SRAM2EN |
                                                         RCC_AHB1ENR_SRAM1EN)));
  LL_AHB2_GRP1_DisableClock(LL_AHB2_GRP1_PERIPH_ALL);
#if defined(AHB4)
  LL_AHB4_GRP1_DisableClock(LL_AHB4_GRP1_PERIPH_ALL);
#endif /* AHB4 */
  LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_ALL);
  LL_APB1_GRP2_DisableClock(LL_APB1_GRP2_PERIPH_ALL);
  LL_APB2_GRP1_DisableClock(LL_APB2_GRP1_PERIPH_ALL);
  LL_APB3_GRP1_DisableClock(LL_APB3_GRP1_PERIPH_ALL);

  LL_AHB1_GRP1_EnableClockLowPower(LL_AHB2_GRP1_PERIPH_ALL);
  LL_AHB2_GRP1_EnableClockLowPower(LL_AHB2_GRP1_PERIPH_ALL);
#if defined(AHB4)
  LL_AHB4_GRP1_EnableClockLowPower(LL_AHB4_GRP1_PERIPH_ALL);
#endif /* AHB4 */
  LL_APB1_GRP1_EnableClockLowPower(LL_APB1_GRP1_PERIPH_ALL);
  LL_APB1_GRP2_EnableClockLowPower(LL_APB1_GRP2_PERIPH_ALL);
  LL_APB2_GRP1_EnableClockLowPower(LL_APB2_GRP1_PERIPH_ALL);
  LL_APB3_GRP1_EnableClockLowPower(LL_APB3_GRP1_PERIPH_ALL);

  /* Reset peripheral clock source selection */
  read_value = LL_RCC_READ_REG(CCIPR1);

#if defined(UART7)
#if defined(FDCAN1)
#define RCC_CCIPR1_RESET (RCC_CCIPR1_USART1SEL | RCC_CCIPR1_USART2SEL | RCC_CCIPR1_USART3SEL | RCC_CCIPR1_UART4SEL \
                          | RCC_CCIPR1_UART5SEL | RCC_CCIPR1_USART6SEL | RCC_CCIPR1_UART7SEL | RCC_CCIPR1_LPUART1SEL \
                          | RCC_CCIPR1_SPI1SEL | RCC_CCIPR1_SPI2SEL | RCC_CCIPR1_SPI3SEL | RCC_CCIPR1_FDCANSEL)
#else
#define RCC_CCIPR1_RESET (RCC_CCIPR1_USART1SEL | RCC_CCIPR1_USART2SEL | RCC_CCIPR1_USART3SEL | RCC_CCIPR1_UART4SEL \
                          | RCC_CCIPR1_UART5SEL | RCC_CCIPR1_USART6SEL | RCC_CCIPR1_UART7SEL | RCC_CCIPR1_LPUART1SEL \
                          | RCC_CCIPR1_SPI1SEL | RCC_CCIPR1_SPI2SEL | RCC_CCIPR1_SPI3SEL)
#endif /* FDCAN1 */
#elif defined(SPI3)
#if defined(FDCAN1)
#define RCC_CCIPR1_RESET (RCC_CCIPR1_USART1SEL | RCC_CCIPR1_USART2SEL | RCC_CCIPR1_USART3SEL | RCC_CCIPR1_UART4SEL \
                          | RCC_CCIPR1_UART5SEL | RCC_CCIPR1_LPUART1SEL | RCC_CCIPR1_SPI1SEL | RCC_CCIPR1_SPI2SEL \
                          | RCC_CCIPR1_SPI3SEL | RCC_CCIPR1_FDCANSEL)
#else
#define RCC_CCIPR1_RESET (RCC_CCIPR1_USART1SEL | RCC_CCIPR1_USART2SEL | RCC_CCIPR1_USART3SEL | RCC_CCIPR1_UART4SEL \
                          | RCC_CCIPR1_UART5SEL | RCC_CCIPR1_LPUART1SEL | RCC_CCIPR1_SPI1SEL | RCC_CCIPR1_SPI2SEL \
                          | RCC_CCIPR1_SPI3SEL)
#endif /* FDCAN1 */
#else
#if defined(FDCAN1)
#define RCC_CCIPR1_RESET (RCC_CCIPR1_USART1SEL | RCC_CCIPR1_USART2SEL  | RCC_CCIPR1_UART4SEL | RCC_CCIPR1_UART5SEL \
                          | RCC_CCIPR1_LPUART1SEL | RCC_CCIPR1_SPI1SEL | RCC_CCIPR1_SPI2SEL | RCC_CCIPR1_FDCANSEL)
#else
#define RCC_CCIPR1_RESET (RCC_CCIPR1_USART1SEL | RCC_CCIPR1_USART2SEL  | RCC_CCIPR1_UART4SEL | RCC_CCIPR1_UART5SEL \
                          | RCC_CCIPR1_LPUART1SEL | RCC_CCIPR1_SPI1SEL | RCC_CCIPR1_SPI2SEL)
#endif /* FDCAN1 */
#endif /* UART7 */
  LL_RCC_WRITE_REG(CCIPR1, (read_value & ~RCC_CCIPR1_RESET));

  read_value = LL_RCC_READ_REG(CCIPR2);
#if defined(I2C2)
#define RCC_CCIPR2_RESET (RCC_CCIPR2_I2C1SEL | RCC_CCIPR2_I2C2SEL | RCC_CCIPR2_I3C1SEL | RCC_CCIPR2_ADCDACSEL \
                          | RCC_CCIPR2_ADCDACPRE | RCC_CCIPR2_DACSEL | RCC_CCIPR2_LPTIM1SEL | RCC_CCIPR2_CK48SEL \
                          | RCC_CCIPR2_SYSTICKSEL)
#else
#define RCC_CCIPR2_RESET (RCC_CCIPR2_I2C1SEL  | RCC_CCIPR2_I3C1SEL | RCC_CCIPR2_ADCDACSEL | RCC_CCIPR2_DACSEL \
                          | RCC_CCIPR2_ADCDACPRE | RCC_CCIPR2_LPTIM1SEL | RCC_CCIPR2_CK48SEL | RCC_CCIPR2_SYSTICKSEL)
#endif /* I2C2 */
  LL_RCC_WRITE_REG(CCIPR2, (read_value & ~RCC_CCIPR2_RESET));

#if defined(ETH)
  read_value = LL_RCC_READ_REG(CCIPR3);
#define RCC_CCIPR3_RESET (RCC_CCIPR3_XSPI1SEL | RCC_CCIPR3_ETHREFCLKSEL | RCC_CCIPR3_ETHPTPCLKSEL \
                          | RCC_CCIPR3_ETHCLKSEL | RCC_CCIPR3_ETHCLKDIVSEL | RCC_CCIPR3_ETHPTPDIVSEL)
  LL_RCC_WRITE_REG(CCIPR3, (read_value & ~RCC_CCIPR3_RESET));
#endif /* ETH */
#endif /* USE_HAL_RCC_RESET_PERIPH_CLOCK_MANAGEMENT */

  /* Reset System clock */
  LL_RCC_HSIDIV3_Enable();

  (void)RCC_WaitForTimeout(LL_RCC_HSIDIV3_IsReady, RCC_HSI_TIMEOUT_VALUE, 1U);

  tickstart = HAL_GetTick();

  /* HSIDIV3 is selected as system clock source */
  LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_HSIDIV3);

  /* Wait till clock switch is ready */
  while (LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_HSIDIV3)
  {
    if ((HAL_GetTick() - tickstart) > RCC_CLOCKSWITCH_TIMEOUT_VALUE)
    {
      break;
    }
  }

  /* Reset all bus dividers */
  LL_RCC_ConfigBusClock((uint32_t)LL_RCC_HCLK_PRESCALER_1 | (uint32_t)LL_RCC_APB1_PRESCALER_1 |
                        (uint32_t)LL_RCC_APB2_PRESCALER_1 |
                        (uint32_t)LL_RCC_APB3_PRESCALER_1);

  SystemCoreClock = HSI_RESET_VALUE;

  LL_RCC_SetSystickClockSource(LL_RCC_SYSTICK_CLKSOURCE_HCLKDIV8);

  /* Adapt Systick interrupt period */
  HAL_InitTick(HAL_TICK_FREQ_DEFAULT, uwTickPrio);

#if defined(USE_HAL_RCC_RESET_RTC_DOMAIN) && (USE_HAL_RCC_RESET_RTC_DOMAIN == 1U)
  /* Reset backup domain */
  LL_RCC_ForceRTCDomainReset();
  LL_RCC_ReleaseRTCDomainReset();
#endif /* USE_HAL_RCC_RESET_RTC_DOMAIN */

  /* Reset all remaining oscillators not in backup domain (excepted the one used for System clock) */
  read_value = LL_RCC_READ_REG(CR1);
#define RCC_CR1_RESET1 (RCC_CR1_HSISON | RCC_CR1_HSIKON | RCC_CR1_HSIKERON | RCC_CR1_PSISON | RCC_CR1_PSIDIV3ON \
                        | RCC_CR1_PSIKON | RCC_CR1_PSIKERON | RCC_CR1_HSEON)
#define RCC_CR1_RESET2 (RCC_CR1_RESET1 | RCC_CR1_HSEBYP | RCC_CR1_HSEEXT)
  LL_RCC_WRITE_REG(CR1, (read_value & ~RCC_CR1_RESET1));
  LL_RCC_WRITE_REG(CR1, (read_value & ~RCC_CR1_RESET2)); /* HSE EXT and BYP disabled only when HSE has been disabled */
  read_value = LL_RCC_READ_REG(CR2);
#define RCC_CR2_RESET (RCC_CR2_HSIKDIV | RCC_CR2_PSIKDIV | RCC_CR2_PSIREFSRC | RCC_CR2_PSIREF | RCC_CR2_PSIFREQ)
  LL_RCC_WRITE_REG(CR2, (read_value & ~RCC_CR2_RESET));
  LL_RCC_LSI_Disable();

  /* Reset MCO, RTC prescaler and wake up system clock */
  read_value = LL_RCC_READ_REG(CFGR1);
#if defined(USE_HAL_RCC_RESET_PERIPH_CLOCK_MANAGEMENT) && (USE_HAL_RCC_RESET_PERIPH_CLOCK_MANAGEMENT == 1U)
#define RCC_CFGR1_RESET (RCC_CFGR1_STOPWUCK | RCC_CFGR1_RTCPRE | RCC_CFGR1_MCO1PRE | RCC_CFGR1_MCO1SEL \
                         | RCC_CFGR1_MCO2PRE | RCC_CFGR1_MCO2SEL)
#else
#define RCC_CFGR1_RESET (RCC_CFGR1_STOPWUCK | RCC_CFGR1_MCO1PRE | RCC_CFGR1_MCO1SEL | RCC_CFGR1_MCO2PRE \
                         | RCC_CFGR1_MCO2SEL)
#endif /* USE_HAL_RCC_RESET_PERIPH_CLOCK_MANAGEMENT */

  LL_RCC_WRITE_REG(CFGR1, (read_value & ~RCC_CFGR1_RESET));

  /* Clear RCC flags */
  LL_RCC_ClearFlag(LL_RCC_IT_LSIRDY | LL_RCC_IT_LSERDY | LL_RCC_IT_HSIRDY | LL_RCC_IT_HSIDIV3RDY | \
                   LL_RCC_IT_HSIKRDY | LL_RCC_IT_PSIRDY | LL_RCC_IT_PSIDIV3RDY | LL_RCC_IT_PSIKRDY | \
                   LL_RCC_IT_HSERDY | LL_RCC_IT_HSECSS | LL_RCC_IT_LSECSS);
  LL_RCC_ClearResetFlags();
}

/**
  * @brief  Reset the RCC clock configuration to the default system clock (HSIDIV3 at 48 MHz)
  * @note   SystemCoreClock and Systick are updated in this function.
  * @retval HAL_OK    System clock switched to HSIDIV3 (48MHz)
  * @retval HAL_ERROR Timeout issue to enable the HSIDIV3 clocl\n
  *                   Switch to HSIDIV3 as source clock failed\n
  *                   Issue to reconfigure the System tick
  */
hal_status_t HAL_RCC_ResetSystemClock(void)
{
  uint32_t tickstart;

  LL_RCC_HSIDIV3_Enable();

  if (RCC_WaitForTimeout(LL_RCC_HSIDIV3_IsReady, RCC_HSI_TIMEOUT_VALUE, 1U) != HAL_OK)
  {
    return HAL_ERROR;
  }

  tickstart = HAL_GetTick();

  /* HSIDIV3 is selected as system clock source */
  LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_HSIDIV3);

  /* Wait till clock switch is ready */
  while (LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_HSIDIV3)
  {
    if ((HAL_GetTick() - tickstart) > RCC_CLOCKSWITCH_TIMEOUT_VALUE)
    {
      /* New check to avoid false timeout detection in case of preemption */
      if (LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_HSIDIV3)
      {
        return HAL_ERROR;
      }
    }
  }

  SystemCoreClock = HSI_RESET_VALUE;

  if (LL_RCC_GetSystickClockSource() == LL_RCC_SYSTICK_CLKSOURCE_HCLKDIV8)
  {
    /* Adapt Systick interrupt period */
    return (HAL_InitTick(HAL_TICK_FREQ_DEFAULT, uwTickPrio));
  }

  return HAL_OK;
}

/**
  * @}
  */

/** @addtogroup RCC_Exported_Functions_Group1_1
  * @{
  */
/**
  * @brief  Enable the HSI oscillator in Stop mode.
  * @retval HAL_OK      HSI oscillator is forced ON even in Stop mode.
  */
hal_status_t HAL_RCC_HSI_EnableInStopMode(void)
{
  LL_RCC_HSI_EnableInStopMode();
  return HAL_OK;
}

/**
  * @brief  Disable the HSI oscillator in Stop mode.
  * @retval HAL_OK      HSI oscillator is disable in Stop mode.
  */
hal_status_t HAL_RCC_HSI_DisableInStopMode(void)
{
  LL_RCC_HSI_DisableInStopMode();
  return HAL_OK;
}

/**
  * @brief  Check if HSI in stop mode is enabled.
  * @retval status based on @ref hal_rcc_osc_stop_mode_status_t
  * @retval HAL_RCC_OSC_DISABLED_IN_STOP_MODE   HSI is disabled in stop mode
  * @retval HAL_RCC_OSC_ENABLED_IN_STOP_MODE    HSI is enabled in stop mode
  */
hal_rcc_osc_stop_mode_status_t HAL_RCC_HSI_IsEnabledInStopMode(void)
{
  return (hal_rcc_osc_stop_mode_status_t)LL_RCC_HSI_IsEnabledInStopMode();
}

/**
  * @brief  Enable the HSIS clock for system.
  * @retval HAL_OK      HSIS clock has been activated successfully
  * @retval HAL_ERROR   Timeout linked to HSIS ready flag not set
  * @note               If HSI oscillator is disabled, enabled it.
  */
hal_status_t HAL_RCC_HSIS_Enable(void)
{
  LL_RCC_HSIS_Enable();

  return RCC_WaitForTimeout(LL_RCC_HSIS_IsReady, RCC_HSI_TIMEOUT_VALUE, 1U);
}

/**
  * @brief  Disable the HSIS clock for system.
  * @retval HAL_OK      HSIS clock has been deactivated successfully
  * @retval HAL_ERROR   HSIS clock is used as system clock\n
  *                     HSIDIV18 clock is used as source clock of the PSI oscillator and PSI is used as system clock\n
  *                     Timeout linked to HSIS ready flag not reset
  * @note               If HSIDIV3ON and HSIKON are cleared, disabled the HSI oscillator.
  */
hal_status_t HAL_RCC_HSIS_Disable(void)
{
  uint32_t psiclk_source;
  uint32_t sysclk_source;
  hal_status_t status;

  sysclk_source = LL_RCC_GetSysClkSource();
  psiclk_source = LL_RCC_GetPSIClkSource();

  /* Check that HSIS is not used as system clock */
  if ((sysclk_source == LL_RCC_SYS_CLKSOURCE_STATUS_HSIS)
      || ((sysclk_source == LL_RCC_SYS_CLKSOURCE_STATUS_PSIS) && (psiclk_source == LL_RCC_PSISOURCE_HSIDIV18)))
  {
    status = HAL_ERROR;
  }
  else
  {
    LL_RCC_HSIS_Disable();
    status = RCC_WaitForTimeout(LL_RCC_HSIS_IsReady, RCC_HSI_TIMEOUT_VALUE, 0U);
  }

  return status;
}

/**
  * @brief  Check if HSIS is enabled.
  * @retval hal_rcc_osc_enable_status_t HSIS enable state
  */
hal_rcc_osc_enable_status_t HAL_RCC_HSIS_IsEnabled(void)
{
  return (hal_rcc_osc_enable_status_t)LL_RCC_HSIS_IsEnabled();
}

/**
  * @brief  Check if HSIS is ready.
  * @retval status based on @ref hal_rcc_osc_ready_status_t
  * @retval HAL_RCC_OSC_READY       HSIS is enabled and ready
  * @retval HAL_RCC_OSC_NOT_READY   HSIS can be enabled but not ready
  */
hal_rcc_osc_ready_status_t HAL_RCC_HSIS_IsReady(void)
{
  return (hal_rcc_osc_ready_status_t)LL_RCC_HSIS_IsReady();
}

/**
  * @brief  Enable the HSIDIV3 clock for system or for peripheral clock source.
  * @retval HAL_OK      HSIDIV3 clock has been activated successfully
  * @retval HAL_ERROR   Timeout linked to HSIDIV3 ready flag not set
  * @note               If HSI oscillator is disabled, enabled it.
  */
hal_status_t HAL_RCC_HSIDIV3_Enable(void)
{
  LL_RCC_HSIDIV3_Enable();

  return RCC_WaitForTimeout(LL_RCC_HSIDIV3_IsReady, RCC_HSI_TIMEOUT_VALUE, 1U);
}

/**
  * @brief  Disable the HSIDIV3 clock for system or for peripheral clock source.
  * @warning This HSIDIV3 clock might be used as peripheral clock source
  *         and this function will stop any peripheral functions.
  * @retval HAL_OK      HSIDIV3 clock has been deactivated successfully
  * @retval HAL_ERROR   HSIDIV3 clock is used as system clock\n
  *                     Timeout linked to HSIDIV3 ready flag not reset
  * @note               If HSISON and HSIKON are cleared, disabled the HSI oscillator.
  */
hal_status_t HAL_RCC_HSIDIV3_Disable(void)
{
  uint32_t sysclk_source;
  hal_status_t status;

  sysclk_source = LL_RCC_GetSysClkSource();

  /* Check that HSIDIV3 is not used as system clock */
  if (sysclk_source == LL_RCC_SYS_CLKSOURCE_STATUS_HSIDIV3)
  {
    status = HAL_ERROR;
  }
  else
  {
    LL_RCC_HSIDIV3_Disable();
    status = RCC_WaitForTimeout(LL_RCC_HSIDIV3_IsReady, RCC_HSI_TIMEOUT_VALUE, 0U);
  }

  return status;
}

/**
  * @brief  Check if HSIDIV3 is enabled.
  * @retval hal_rcc_osc_enable_status_t HSIDIV3 enable state
  */
hal_rcc_osc_enable_status_t HAL_RCC_HSIDIV3_IsEnabled(void)
{
  return (hal_rcc_osc_enable_status_t)LL_RCC_HSIDIV3_IsEnabled();
}

/**
  * @brief  Check if HSIDIV3 is ready.
  * @retval status based on @ref hal_rcc_osc_ready_status_t
  * @retval HAL_RCC_OSC_READY       HSIDIV3 is enabled and ready
  * @retval HAL_RCC_OSC_NOT_READY   HSIDIV3 can be enabled but not ready
  */
hal_rcc_osc_ready_status_t HAL_RCC_HSIDIV3_IsReady(void)
{
  return (hal_rcc_osc_ready_status_t)LL_RCC_HSIDIV3_IsReady();
}

/**
  * @brief  Enable the HSIK clock for peripheral clock source.
  * @param  prescaler   Prescaler value
  * @retval HAL_OK      HSIK clock has been activated successfully
  * @retval HAL_ERROR   Timeout linked to HSIK ready flag not set\n
  * @note               If HSI oscillator is disabled, enabled it.
  */
hal_status_t HAL_RCC_HSIK_Enable(hal_rcc_hsik_div_t prescaler)
{
  ASSERT_DBG_PARAM(IS_RCC_HSIKDIV(prescaler));

  LL_RCC_HSIK_SetDivider((uint32_t)prescaler);

  LL_RCC_HSIK_Enable();

  return RCC_WaitForTimeout(LL_RCC_HSIK_IsReady, RCC_HSI_TIMEOUT_VALUE, 1U);
}

/**
  * @brief  Disable the HSIK clock for peripheral clock source.
  * @warning This HSIK clock might be used as peripheral clock source
  *         and this function will stop any peripheral functions.
  * @retval HAL_OK      HSIK clock has been deactivated successfully
  *                     Timeout linked to HSIK ready flag not reset
  * @note               If HSISON and HSIDIV3ON are cleared, disabled the HSI oscillator.
  */
hal_status_t HAL_RCC_HSIK_Disable(void)
{
  hal_status_t status;

  LL_RCC_HSIK_Disable();
  status = RCC_WaitForTimeout(LL_RCC_HSIK_IsReady, RCC_HSI_TIMEOUT_VALUE, 0U);

  return status;
}

/**
  * @brief  Check if HSIK is enabled.
  * @retval hal_rcc_osc_enable_status_t HSIK enable state
  */
hal_rcc_osc_enable_status_t HAL_RCC_HSIK_IsEnabled(void)
{
  return (hal_rcc_osc_enable_status_t)LL_RCC_HSIK_IsEnabled();
}

/**
  * @brief  Check if HSIK is ready.
  * @retval status based on @ref hal_rcc_osc_ready_status_t
  * @retval HAL_RCC_OSC_READY       HSIK is enabled and ready
  * @retval HAL_RCC_OSC_NOT_READY   HSIK can be enabled but not ready
  */
hal_rcc_osc_ready_status_t HAL_RCC_HSIK_IsReady(void)
{
  return (hal_rcc_osc_ready_status_t)LL_RCC_HSIK_IsReady();
}

/**
  * @brief  Get HSIK prescaler value.
  * @retval value based on @ref hal_rcc_hsik_div_t
  */
hal_rcc_hsik_div_t HAL_RCC_HSIK_GetPrescaler(void)
{
  return (hal_rcc_hsik_div_t)LL_RCC_HSIK_GetDivider();
}

/**
  * @brief  Enable the Internal Low Speed oscillator (LSI).
  * @retval HAL_OK      LSI oscillator has been configured successfully
  * @retval HAL_ERROR   Timeout linked to LSI ready flag not set\n
  */
hal_status_t HAL_RCC_LSI_Enable(void)
{
  /* Enable the Internal Low Speed oscillator (LSI) */
  LL_RCC_LSI_Enable();

  return RCC_WaitForTimeout(LL_RCC_LSI_IsReady, RCC_LSI_TIMEOUT_VALUE, 1U);
}

/**
  * @brief  Disable the LSI oscillator.
  * @warning This oscillator might be used as peripheral clock source
  *         and this function will stop any peripheral functions.
  * @retval HAL_OK      LSI oscillator has been deactivated successfully
  * @retval HAL_ERROR   Timeout linked to LSI ready flag not reset\n
  */
hal_status_t HAL_RCC_LSI_Disable(void)
{
  LL_RCC_LSI_Disable();

  return RCC_WaitForTimeout(LL_RCC_LSI_IsReady, RCC_LSI_TIMEOUT_VALUE, 0U);
}

/**
  * @brief  Check if LSI is enabled.
  * @retval hal_rcc_osc_enable_status_t LSI enable state
  */
hal_rcc_osc_enable_status_t HAL_RCC_LSI_IsEnabled(void)
{
  return (hal_rcc_osc_enable_status_t)LL_RCC_LSI_IsEnabled();
}

/**
  * @brief  Check if LSI is ready.
  * @retval status based on @ref hal_rcc_osc_ready_status_t
  * @retval HAL_RCC_OSC_READY       LSI is enabled and ready
  * @retval HAL_RCC_OSC_NOT_READY   LSI can be enabled but not ready
  */
hal_rcc_osc_ready_status_t HAL_RCC_LSI_IsReady(void)
{
  return (hal_rcc_osc_ready_status_t)LL_RCC_LSI_IsReady();
}

#if defined(HSE_VALUE)
/**
  * @brief  Enable the HSE oscillator in the selected mode.
  * @param  mode        HSE mode.\n This parameter can be one of the following values:
  *         @arg @ref HAL_RCC_HSE_ON
  *         @arg @ref HAL_RCC_HSE_BYPASS
  *         @arg @ref HAL_RCC_HSE_BYPASS_DIGITAL
  * @note   Transitions HSE Bypass to HSE On and HSE On to HSE Bypass are not
  *         supported by this function.
  * @retval HAL_OK      HSE oscillator has been activated configured
  * @retval HAL_ERROR   Timeout linked to HSE ready flag not set
  */
hal_status_t HAL_RCC_HSE_Enable(hal_rcc_hse_t mode)
{
  ASSERT_DBG_PARAM(IS_RCC_HSE_MODE_ENABLE(mode));

  /* Set the new HSE configuration */
  if (((uint32_t)mode & RCC_CR1_HSEBYP) == RCC_CR1_HSEBYP)
  {
    LL_RCC_HSE_ConfigBypass((uint32_t)mode & RCC_CR1_HSEEXT);
  }

  LL_RCC_HSE_Enable();

  return RCC_WaitForTimeout(LL_RCC_HSE_IsReady, RCC_HSE_TIMEOUT_VALUE, 1U);
}

/**
  * @brief  Disable the HSE oscillator.
  * @warning This oscillator might be used as peripheral clock source
  *         and this function will stop any peripheral functions.
  * @retval HAL_OK      HSE oscillator has been deactivated successfully
  * @retval HAL_ERROR   HSE is used as source clock of the PSI oscillator and PSI is used as system clock\n
  * @retval HAL_ERROR   HSE clock is used as system clock\n
  *                     Timeout linked to HSE ready flag not reset
  */
hal_status_t HAL_RCC_HSE_Disable(void)
{
  uint32_t sysclk_source;
  uint32_t psiclk_source;
  hal_status_t status;

  sysclk_source = LL_RCC_GetSysClkSource();
  psiclk_source = LL_RCC_GetPSIClkSource();

  /* Check that HSE is not used as system clock */
  if ((sysclk_source == LL_RCC_SYS_CLKSOURCE_STATUS_HSE)
      || ((sysclk_source == LL_RCC_SYS_CLKSOURCE_STATUS_PSIS) && (psiclk_source == LL_RCC_PSISOURCE_HSE)))
  {
    status = HAL_ERROR;
  }
  else
  {
    LL_RCC_HSE_Disable();
    LL_RCC_HSE_DisableBypass();
    LL_RCC_HSE_SetClockMode(LL_RCC_HSE_ANALOG_MODE);
    status = RCC_WaitForTimeout(LL_RCC_HSE_IsReady, RCC_HSE_TIMEOUT_VALUE, 0U);

  }

  return status;
}

/**
  * @brief  Check if HSE is enabled.
  * @retval hal_rcc_osc_enable_status_t HSE enable state
  */
hal_rcc_osc_enable_status_t HAL_RCC_HSE_IsEnabled(void)
{
  return (hal_rcc_osc_enable_status_t)LL_RCC_HSE_IsEnabled();
}

/**
  * @brief  Check if HSE is ready.
  * @retval status based on @ref hal_rcc_osc_ready_status_t
  * @retval HAL_RCC_OSC_READY       HSE is enabled and ready
  * @retval HAL_RCC_OSC_NOT_READY   HSE can be enabled but not ready
  */
hal_rcc_osc_ready_status_t HAL_RCC_HSE_IsReady(void)
{
  return (hal_rcc_osc_ready_status_t)LL_RCC_HSE_IsReady();
}

#endif /* HSE_VALUE */
#if defined(LSE_VALUE)
/**
  * @brief  Enable the LSE oscillator in the selected mode with a oscillator drive capability.
  * @param  mode        LSE mode.\n This parameter can be one of the following values:
  *         @arg @ref HAL_RCC_LSE_ON
  *         @arg @ref HAL_RCC_LSE_BYPASS
  *         @arg @ref HAL_RCC_LSE_BYPASS_DIGITAL
  * @param  drive         LSE drive capability
  * @warning Access to backup domain must be enabled.
  * @note   Transitions LSE Bypass to LSE On and LSE On to LSE Bypass are not
  *         supported by this function. Transitions between drive capability not supported.
  * @note   Drive capability is relevant only in Xtal mode (means not in bypass mode)
  * @retval HAL_OK      LSE oscillator has been configured successfully
  * @retval HAL_ERROR   Backup domain is not enabled\n
  *                     Timeout linked to LSE ready flag not set\n
  */
hal_status_t HAL_RCC_LSE_Enable(hal_rcc_lse_t mode, hal_rcc_lse_drive_t drive)
{

  ASSERT_DBG_PARAM(IS_RCC_LSE_MODE_ENABLE(mode));
  ASSERT_DBG_PARAM(IS_RCC_LSE_DRIVE(drive));

  if (LL_PWR_IsEnabledRTCDomainWriteProtection() != 0U)
  {
    return HAL_ERROR;
  }

  /* Set the new LSE configuration ---------------------------------------*/
  if (((uint32_t)mode & RCC_RTCCR_LSEBYP) == RCC_RTCCR_LSEBYP)
  {
    LL_RCC_LSE_ConfigBypass((uint32_t)mode & RCC_RTCCR_LSEEXT);
  }

  LL_RCC_LSE_SetDriveCapability((uint32_t)drive);
  /* Enable LSE and wait for activation */
  LL_RCC_LSE_Enable();
  if (RCC_WaitForTimeout(LL_RCC_LSE_IsReady, RCC_LSE_TIMEOUT_VALUE, 1U) != HAL_OK)
  {
    return HAL_ERROR;
  }

  return HAL_OK;
}

/**
  * @brief  Disable the LSE oscillator.
  * @warning This oscillator might be used as peripheral clock source
  *         and this function will stop any peripheral functions.
  * @warning Access to backup domain must be enabled.
  * @retval HAL_OK      LSE oscillator has been configured successfully
  * @retval HAL_ERROR   Backup domain is not enabled\n
  *                     Timeout linked to LSE ready flag not reset\n
  */
hal_status_t HAL_RCC_LSE_Disable(void)
{
  uint32_t sysclk_source;
  uint32_t psiclk_source;

  if (LL_PWR_IsEnabledRTCDomainWriteProtection() != 0U)
  {
    return HAL_ERROR;
  }

  sysclk_source = LL_RCC_GetSysClkSource();
  psiclk_source = LL_RCC_GetPSIClkSource();
  /* Check that LSE is not used as system clock */
  if ((sysclk_source == LL_RCC_SYS_CLKSOURCE_STATUS_PSIS) && (psiclk_source == LL_RCC_PSISOURCE_LSE))
  {
    return HAL_ERROR;
  }

  LL_RCC_LSE_Disable();
  LL_RCC_LSE_DisableBypass();
  LL_RCC_LSE_SetClockMode(LL_RCC_LSE_ANALOG_MODE);
  if (RCC_WaitForTimeout(LL_RCC_LSE_IsReady, RCC_LSE_TIMEOUT_VALUE, 0U) != HAL_OK)
  {
    return HAL_ERROR;
  }

  /* Reset LSE drive to low value (default) */
  LL_RCC_LSE_SetDriveCapability(HAL_RCC_LSE_DRIVE_LOW);

  return HAL_OK;
}

/**
  * @brief  Check if LSE is enabled.
  * @retval hal_rcc_osc_enable_status_t LSE enable state
  */
hal_rcc_osc_enable_status_t HAL_RCC_LSE_IsEnabled(void)
{
  return (hal_rcc_osc_enable_status_t)LL_RCC_LSE_IsEnabled();
}

/**
  * @brief  Check if LSE is ready.
  * @retval status based on @ref hal_rcc_osc_ready_status_t
  * @retval HAL_RCC_OSC_READY       LSE is enabled and ready
  * @retval HAL_RCC_OSC_NOT_READY   LSE can be enabled but not ready
  */
hal_rcc_osc_ready_status_t HAL_RCC_LSE_IsReady(void)
{
  return (hal_rcc_osc_ready_status_t)LL_RCC_LSE_IsReady();
}

#endif /* LSE_VALUE */
/**
  * @brief  Enable the PSI oscillator in Stop mode.
  * @retval HAL_OK      PSI oscillator is forced ON even in Stop mode.
  */
hal_status_t HAL_RCC_PSI_EnableInStopMode(void)
{
  LL_RCC_PSI_EnableInStopMode();
  return HAL_OK;
}

/**
  * @brief  Disable the PSI oscillator in Stop mode.
  * @retval HAL_OK      PSI oscillator is disable in Stop mode.
  */
hal_status_t HAL_RCC_PSI_DisableInStopMode(void)
{
  LL_RCC_PSI_DisableInStopMode();
  return HAL_OK;
}

/**
  * @brief  Check if PSI in stop mode is enabled.
  * @retval status based on @ref hal_rcc_osc_stop_mode_status_t
  * @retval HAL_RCC_OSC_DISABLED_IN_STOP_MODE   PSI is disabled in stop mode
  * @retval HAL_RCC_OSC_ENABLED_IN_STOP_MODE    PSI is enabled in stop mode
  */
hal_rcc_osc_stop_mode_status_t HAL_RCC_PSI_IsEnabledInStopMode(void)
{
  return (hal_rcc_osc_stop_mode_status_t)LL_RCC_PSI_IsEnabledInStopMode();
}

/**
  * @brief  Enable the PSIS clock for system.
  * @retval HAL_OK      PSIS clock has been activated successfully
  * @retval HAL_ERROR   Timeout linked to PSIS ready flag not set
  * @note               If PSI oscillator is disabled, enabled it.
  */
hal_status_t HAL_RCC_PSIS_Enable(void)
{
  LL_RCC_PSIS_Enable();

  return RCC_WaitForTimeout(LL_RCC_PSIS_IsReady, RCC_PSI_TIMEOUT_VALUE, 1U);
}

/**
  * @brief  Disable the PSIS clock for system.
  * @retval HAL_OK      PSIS clock has been deactivated successfully
  * @retval HAL_ERROR   PSIS clock is used as system clock\n
  *                     Timeout linked to PSIS ready flag not reset
  * @note               If PSIDIV3ON and PSIKON are cleared, disabled the PSI oscillator.
  */
hal_status_t HAL_RCC_PSIS_Disable(void)
{
  uint32_t sysclk_source;
  hal_status_t status;

  sysclk_source = LL_RCC_GetSysClkSource();

  /* Check that PSIS is not used as system clock */
  if (sysclk_source == LL_RCC_SYS_CLKSOURCE_STATUS_PSIS)
  {
    status = HAL_ERROR;
  }
  else
  {
    LL_RCC_PSIS_Disable();
    status = RCC_WaitForTimeout(LL_RCC_PSIS_IsReady, RCC_PSI_TIMEOUT_VALUE, 0U);
  }

  return status;
}

/**
  * @brief  Check if PSIS is enabled.
  * @retval hal_rcc_osc_enable_status_t PSIS enable state
  */
hal_rcc_osc_enable_status_t HAL_RCC_PSIS_IsEnabled(void)
{
  return (hal_rcc_osc_enable_status_t)LL_RCC_PSIS_IsEnabled();
}

/**
  * @brief  Check if PSIS is ready.
  * @retval status based on @ref hal_rcc_osc_ready_status_t
  * @retval HAL_RCC_OSC_READY       PSIS is enabled and ready
  * @retval HAL_RCC_OSC_NOT_READY   PSIS can be enabled but not ready
  */
hal_rcc_osc_ready_status_t HAL_RCC_PSIS_IsReady(void)
{
  return (hal_rcc_osc_ready_status_t)LL_RCC_PSIS_IsReady();
}

/**
  * @brief  Enable the PSIDIV3 clock for system or for peripheral clock source.
  * @retval HAL_OK      PSIDIV3 clock has been activated successfully
  * @retval HAL_ERROR   Timeout linked to PSIDIV3 ready flag not set
  * @note               If PSI oscillator is disabled, enabled it.
  */
hal_status_t HAL_RCC_PSIDIV3_Enable(void)
{
  LL_RCC_PSIDIV3_Enable();

  return RCC_WaitForTimeout(LL_RCC_PSIDIV3_IsReady, RCC_PSI_TIMEOUT_VALUE, 1U);
}

/**
  * @brief  Disable the PSIDIV3 clock for system or for peripheral clock source.
  * @warning This PSIDIV3 clock might be used as peripheral clock source
  *         and this function will stop any peripheral functions.
  * @retval HAL_OK      PSIDIV3 clock has been deactivated successfully
  *                     Timeout linked to PSIDIV3 ready flag not reset
  * @note               If PSISON and PSIKON are cleared, disabled the PSI oscillator.
  */
hal_status_t HAL_RCC_PSIDIV3_Disable(void)
{
  hal_status_t status;


  LL_RCC_PSIDIV3_Disable();
  status = RCC_WaitForTimeout(LL_RCC_PSIDIV3_IsReady, RCC_PSI_TIMEOUT_VALUE, 0U);

  return status;
}

/**
  * @brief  Check if PSIDIV3 is enabled.
  * @retval hal_rcc_osc_enable_status_t PSIDIV3 enable state
  */
hal_rcc_osc_enable_status_t HAL_RCC_PSIDIV3_IsEnabled(void)
{
  return (hal_rcc_osc_enable_status_t)LL_RCC_PSIDIV3_IsEnabled();
}

/**
  * @brief  Check if PSIDIV3 is ready.
  * @retval status based on @ref hal_rcc_osc_ready_status_t
  * @retval HAL_RCC_OSC_READY       PSIDIV3 is enabled and ready
  * @retval HAL_RCC_OSC_NOT_READY   PSIDIV3 can be enabled but not ready
  */
hal_rcc_osc_ready_status_t HAL_RCC_PSIDIV3_IsReady(void)
{
  return (hal_rcc_osc_ready_status_t)LL_RCC_PSIDIV3_IsReady();
}

/**
  * @brief  Enable the PSIK clock for peripheral clock source.
  * @param  prescaler   Prescaler value
  * @retval HAL_OK      PSIK clock has been activated successfully
  * @retval HAL_ERROR   Timeout linked to PSIK ready flag not set\n
  * @note               If PSI oscillator is disabled, enabled it.
  */
hal_status_t HAL_RCC_PSIK_Enable(hal_rcc_psik_div_t prescaler)
{
  ASSERT_DBG_PARAM(IS_RCC_PSIKDIV(prescaler));

  LL_RCC_PSIK_SetDivider((uint32_t)prescaler);

  LL_RCC_PSIK_Enable();

  return RCC_WaitForTimeout(LL_RCC_PSIK_IsReady, RCC_PSI_TIMEOUT_VALUE, 1U);
}

/**
  * @brief  Disable the PSIK clock for peripheral clock source.
  * @warning This PSIK clock might be used as peripheral clock source
  *         and this function will stop any peripheral functions.
  * @retval HAL_OK      PSIK clock has been deactivated successfully
  *                     Timeout linked to PSIK ready flag not reset
  * @note               If PSISON and PSIDIV3ON are cleared, disabled the PSI oscillator.
  */
hal_status_t HAL_RCC_PSIK_Disable(void)
{
  hal_status_t status;

  LL_RCC_PSIK_Disable();
  status = RCC_WaitForTimeout(LL_RCC_PSIK_IsReady, RCC_PSI_TIMEOUT_VALUE, 0U);

  return status;
}

/**
  * @brief  Check if PSIK is enabled.
  * @retval hal_rcc_osc_enable_status_t PSIK enable state
  */
hal_rcc_osc_enable_status_t HAL_RCC_PSIK_IsEnabled(void)
{
  return (hal_rcc_osc_enable_status_t)LL_RCC_PSIK_IsEnabled();
}

/**
  * @brief  Check if PSIK is ready.
  * @retval status based on @ref hal_rcc_osc_ready_status_t
  * @retval HAL_RCC_OSC_READY       PSIK is enabled and ready
  * @retval HAL_RCC_OSC_NOT_READY   PSIK can be enabled but not ready
  */
hal_rcc_osc_ready_status_t HAL_RCC_PSIK_IsReady(void)
{
  return (hal_rcc_osc_ready_status_t)LL_RCC_PSIK_IsReady();
}

/**
  * @brief  Get PSIK prescaler value.
  * @retval value based on @ref hal_rcc_psik_div_t
  */
hal_rcc_psik_div_t HAL_RCC_PSIK_GetPrescaler(void)
{
  return (hal_rcc_psik_div_t)LL_RCC_PSIK_GetDivider();
}

/**
  * @brief   Configure PSI oscillator without enabling outputs clock.
  * @details The config function will perform the following actions:
  *           - Check in PSI is well deactivated (if enabled exit from this function)
  *           - Configure the PSI with full list of parameters
  * @param p_config pointer to a @ref hal_rcc_psi_config_t structure that
  *          contains the configuration information for the PSI
  * @retval HAL_OK            PSI has been correctly configured
  * @retval HAL_INVALID_PARAM Input parameter not valid (USE_HAL_CHECK_PARAM enabled)
  * @retval HAL_ERROR         PSI is already enabled and can not be modified.
  */
hal_status_t HAL_RCC_PSI_SetConfig(const hal_rcc_psi_config_t *p_config)
{

  ASSERT_DBG_PARAM(p_config != (void *)NULL);
#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_config == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */
  ASSERT_DBG_PARAM(IS_RCC_PSISOURCE(p_config->psi_source));
  ASSERT_DBG_PARAM(IS_RCC_PSIREF(p_config->psi_ref));
  ASSERT_DBG_PARAM(IS_RCC_PSIOUT(p_config->psi_out));

  /* Check if PSI is disabled */
  if ((LL_RCC_PSIS_IsReady() == 0U) && (LL_RCC_PSIDIV3_IsReady() == 0U) && (LL_RCC_PSIK_IsReady() == 0U))
  {
    LL_RCC_ConfigPSI((uint32_t)(p_config->psi_out), (uint32_t)(p_config->psi_ref), (uint32_t)(p_config->psi_source));
    return HAL_OK;
  }
  else
  {
    return HAL_ERROR;
  }
}

/**
  * @brief Return the configuration of PSI.
  * @param p_config  pointer to a @ref hal_rcc_psi_config_t structure that
  *          contains the configuration information for the PSI
  */
void HAL_RCC_PSI_GetConfig(hal_rcc_psi_config_t *p_config)
{
  ASSERT_DBG_PARAM(p_config != (void *)NULL);

  uint32_t psi_source;
  uint32_t psi_ref;
  uint32_t psi_out;

  /* Get PSI config */
  LL_RCC_GetConfigPSI(&psi_out, &psi_ref, &psi_source);

  p_config->psi_source  = (hal_rcc_psi_src_t)psi_source;
  p_config->psi_ref  = (hal_rcc_psi_ref_t)psi_ref;
  p_config->psi_out  = (hal_rcc_psi_out_t)psi_out;
}
/**
  * @}
  */

/** @addtogroup RCC_Exported_Functions_Group1_2
  * @{
  */
/**
  * @brief  Set the CPU bus clock source (SYSCLK).
  * @param  source  System clock source based on @ref hal_rcc_sysclk_src_t
  * @note   SystemCoreClock and Systick are updated in this function.
  * @retval HAL_OK    Success\n
  * @retval HAL_ERROR System clock source has not been applied\n
  *                   HSIS not enabled to switch to HSIS as system clock\n
  *                   HSIDIV3 not enabled to switch to HSIDIV3 as system clock\n
  *                   PSIS not enabled to switch to PSIS as system clock\n
  *                   Issue to reconfigure the System tick
  */
hal_status_t HAL_RCC_SetSYSCLKSource(hal_rcc_sysclk_src_t source)
{
  uint32_t tickstart;
  hal_status_t status = HAL_OK;

  ASSERT_DBG_PARAM(IS_RCC_SYSCLKSOURCE(source));

  LL_RCC_SetSysClkSource((uint32_t)source);

  tickstart = HAL_GetTick();

  while (HAL_RCC_GetSYSCLKSource() != source)
  {
    if ((HAL_GetTick() - tickstart) > RCC_CLOCKSWITCH_TIMEOUT_VALUE)
    {
      status = HAL_ERROR;
      break;
    }
  }

  if (status == HAL_OK)
  {
    RCC_UPDATE_SYSTEMCORECLOCK();

    /* Configure the source of time base considering new system clocks settings*/
    status = HAL_InitTick(uwTickFreq, uwTickPrio);
  }

  return status;
}

/**
  * @brief   Get the system clock source (SYSCLK).
  * @retval  hal_rcc_sysclk_src_t System Clock source
  */
hal_rcc_sysclk_src_t HAL_RCC_GetSYSCLKSource(void)
{
  return (hal_rcc_sysclk_src_t)(uint32_t)((LL_RCC_GetSysClkSource() >> RCC_CFGR1_SWS_Pos) << RCC_CFGR1_SW_Pos);
}

/**
  * @brief  Set the Systick external clock source
  * @param  clk_src Systick external clock source selection based on @ref hal_rcc_systick_clk_src_t
  */
void HAL_RCC_SetSysTickExternalClkSource(hal_rcc_systick_clk_src_t clk_src)
{
  ASSERT_DBG_PARAM(IS_RCC_SYSTICK_CLK(clk_src));

  LL_RCC_SetSystickClockSource((uint32_t)clk_src);
}

/**
  * @brief  Get the Systick external clock source
  * @retval Systick external clock source based on @ref hal_rcc_systick_clk_src_t
  */
hal_rcc_systick_clk_src_t HAL_RCC_GetSysTickExternalClkSource(void)
{
  return (hal_rcc_systick_clk_src_t)LL_RCC_GetSystickClockSource();
}

/**
  * @brief  Set the AHB clock (HCLK) divider.
  * @param  prescaler  Prescaler value
  * @note   SystemCoreClock and Systick are updated in this function.
  * @retval HAL_OK     HCLK prescaler has been changed successfully
  * @retval HAL_ERROR  Issue to reconfigure the System tick
  */
hal_status_t HAL_RCC_SetHCLKPrescaler(hal_rcc_hclk_prescaler_t prescaler)
{
  ASSERT_DBG_PARAM(IS_RCC_HCLK(prescaler));

  LL_RCC_SetAHBPrescaler((uint32_t)prescaler);

  RCC_UPDATE_SYSTEMCORECLOCK();

  /* Configure the source of time base considering new system clocks settings */
  return HAL_InitTick(uwTickFreq, uwTickPrio);
}

/**
  * @brief  Set the APB1 clock (PCLK1) divider
  * @param prescaler  Prescaler value
  */
void HAL_RCC_SetPCLK1Prescaler(hal_rcc_pclk_prescaler_t prescaler)
{
  ASSERT_DBG_PARAM(IS_RCC_PCLK(prescaler));

  LL_RCC_SetAPB1Prescaler((uint32_t)prescaler);
}

/**
  * @brief  Set the APB2 clock (PCLK2) divider
  * @param prescaler  Prescaler value
  */
void HAL_RCC_SetPCLK2Prescaler(hal_rcc_pclk_prescaler_t prescaler)
{
  ASSERT_DBG_PARAM(IS_RCC_PCLK(prescaler));

  LL_RCC_SetAPB2Prescaler(((uint32_t)prescaler) << (RCC_CFGR2_PPRE2_Pos - RCC_CFGR2_PPRE1_Pos));
}

/**
  * @brief  Set the APB3 clock (PCLK3) divider
  * @param prescaler  Prescaler value
  */
void HAL_RCC_SetPCLK3Prescaler(hal_rcc_pclk_prescaler_t prescaler)
{
  ASSERT_DBG_PARAM(IS_RCC_PCLK(prescaler));

  LL_RCC_SetAPB3Prescaler(((uint32_t)prescaler) << (RCC_CFGR2_PPRE3_Pos - RCC_CFGR2_PPRE1_Pos));
}

/**
  * @brief  Get the AHB bus clock prescaler (HCLK).
  * @retval hal_rcc_hclk_prescaler_t Prescaler value
  */
hal_rcc_hclk_prescaler_t HAL_RCC_GetHCLKPrescaler(void)
{
  return (hal_rcc_hclk_prescaler_t)LL_RCC_GetAHBPrescaler();
}

/**
  * @brief  Set the APB1 bus clock prescaler (PCLK1).
  * @retval hal_rcc_pclk_prescaler_t Prescaler value
  */
hal_rcc_pclk_prescaler_t HAL_RCC_GetPCLK1Prescaler(void)
{
  return (hal_rcc_pclk_prescaler_t)LL_RCC_GetAPB1Prescaler();
}

/**
  * @brief  Set the APB2 bus clock prescaler (PCLK2).
  * @retval hal_rcc_pclk_prescaler_t Prescaler value
  */
hal_rcc_pclk_prescaler_t HAL_RCC_GetPCLK2Prescaler(void)
{
  return (hal_rcc_pclk_prescaler_t)(uint32_t)(LL_RCC_GetAPB2Prescaler() >> (RCC_CFGR2_PPRE2_Pos - RCC_CFGR2_PPRE1_Pos));
}

/**
  * @brief  Set the APB3 bus clock prescaler (PCLK3).
  * @retval hal_rcc_pclk_prescaler_t Prescaler value
  */
hal_rcc_pclk_prescaler_t HAL_RCC_GetPCLK3Prescaler(void)
{
  return (hal_rcc_pclk_prescaler_t)(uint32_t)(LL_RCC_GetAPB3Prescaler() >> (RCC_CFGR2_PPRE3_Pos - RCC_CFGR2_PPRE1_Pos));
}

/**
  * @brief  Configure the bus dividers
  * @param  p_config Pointer based on @ref hal_rcc_bus_clk_config_t structure
  * @note   SystemCoreClock and Systick are updated in this function.
  * @warning FLASH latency must be adjusted according to the targeted system clock
  *          frequency and voltage scaling.
  * @retval HAL_OK            Success
  * @retval HAL_ERROR         Issue to reconfigure the System tick
  * @retval HAL_INVALID_PARAM Input parameter not valid (USE_HAL_CHECK_PARAM enabled)
  */
hal_status_t HAL_RCC_SetBusClockConfig(const hal_rcc_bus_clk_config_t *p_config)
{
  ASSERT_DBG_PARAM(p_config != (void *)NULL);
#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_config == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */
  ASSERT_DBG_PARAM(IS_RCC_HCLK(p_config->hclk_prescaler));
  ASSERT_DBG_PARAM(IS_RCC_PCLK(p_config->pclk1_prescaler));
  ASSERT_DBG_PARAM(IS_RCC_PCLK(p_config->pclk2_prescaler));
  ASSERT_DBG_PARAM(IS_RCC_PCLK(p_config->pclk3_prescaler));

  /* Configure prescalers for the available Bus */
  LL_RCC_ConfigBusClock((uint32_t)p_config->hclk_prescaler  |
                        (uint32_t)p_config->pclk1_prescaler |
                        (uint32_t)((uint32_t)p_config->pclk2_prescaler << (RCC_CFGR2_PPRE2_Pos - RCC_CFGR2_PPRE1_Pos)) |
                        (uint32_t)((uint32_t)p_config->pclk3_prescaler << (RCC_CFGR2_PPRE3_Pos - RCC_CFGR2_PPRE1_Pos)));

  RCC_UPDATE_SYSTEMCORECLOCK();

  /* Configure the source of time base considering new system clocks settings*/
  return HAL_InitTick(uwTickFreq, uwTickPrio);
}

/**
  * @brief Retrieve the bus dividers
  * @param p_config Pointer on @ref hal_rcc_bus_clk_config_t structure
  */
void HAL_RCC_GetBusClockConfig(hal_rcc_bus_clk_config_t *p_config)
{
  ASSERT_DBG_PARAM(p_config != (void *)NULL);

  /* Get Bus prescalers */
  p_config->hclk_prescaler = (hal_rcc_hclk_prescaler_t)LL_RCC_GetAHBPrescaler();
  p_config->pclk1_prescaler = (hal_rcc_pclk_prescaler_t)LL_RCC_GetAPB1Prescaler();
  p_config->pclk2_prescaler = (hal_rcc_pclk_prescaler_t)(uint32_t)(LL_RCC_GetAPB2Prescaler()
                                                                   >> (RCC_CFGR2_PPRE2_Pos - RCC_CFGR2_PPRE1_Pos));
  p_config->pclk3_prescaler = (hal_rcc_pclk_prescaler_t)(uint32_t)(LL_RCC_GetAPB3Prescaler()
                                                                   >> (RCC_CFGR2_PPRE3_Pos - RCC_CFGR2_PPRE1_Pos));
}

/**
  * @brief  Return the PSI output frequency.
  * @note   The PSI frequency computed by this function is not the real
  *         frequency in the chip. It is calculated based on the predefined
  *         constant and the selected clock source.
  * @note   If PSI source is HSIDIV3, function returns values based on HSI_VALUE.
  * @note   If PSI source is HSE, function returns values based on HSE_VALUE.
  * @note   If PSI source is LSE, function returns values based on LSE.
  * @retval uint32_t PSICLK frequency in Hz
  */
uint32_t HAL_RCC_GetPSIClockFreq(void)
{

  uint32_t psiclockfreq;

  hal_rcc_psi_config_t psi_config;

  HAL_RCC_PSI_GetConfig(&psi_config);

  /* Anticipate the intrinsic error when LSE is used as clock source for PSI */
  if (psi_config.psi_source == HAL_RCC_PSI_SRC_LSE)
  {
    switch (psi_config.psi_out)
    {
      case HAL_RCC_PSI_OUT_100MHZ:
        psiclockfreq = PSI_LSE_100; /* 100.016 MHz */
        break;

      case HAL_RCC_PSI_OUT_144MHZ:
        psiclockfreq = PSI_LSE_144; /* 144.015 MHz */
        break;

      case HAL_RCC_PSI_OUT_160MHZ:
        psiclockfreq = PSI_LSE_160; /* 160.006 MHz */
        break;
      default:
        psiclockfreq = PSI_LSE_100; /* 100.016 MHz */
        break;
    }
  }
  /* No error for other clock source */
  else
  {
    switch (psi_config.psi_out)
    {
      case HAL_RCC_PSI_OUT_100MHZ:
        psiclockfreq = PSI_NOT_LSE_100;  /* 100 MHz */
        break;

      case HAL_RCC_PSI_OUT_144MHZ:
        psiclockfreq = PSI_NOT_LSE_144;  /* 140 MHz */
        break;

      case HAL_RCC_PSI_OUT_160MHZ:
        psiclockfreq = PSI_NOT_LSE_160;  /* 160 MHz */
        break;
      default:
        psiclockfreq = PSI_NOT_LSE_100;  /* 100 MHz */
        break;
    }
  }

  return psiclockfreq;
}

/**
  * @brief  Return the SYSCLK frequency.
  * @note   The system frequency computed by this function is not the real
  *         frequency in the chip. It is calculated based on the predefined
  *         constant and the selected clock source.
  * @note   If SYSCLK source is HSIS or HSIDIV3, function returns values based on HSI_VALUE.
  * @note   If SYSCLK source is HSE, function returns values based on HSE_VALUE.
  * @note   If SYSCLK source is PSI, function returns values based on HSE_VALUE, LSE_VALUE or HSI_VALUE
  * @note   This function can be used by the user application to compute the
  *         baudrate for the communication peripherals or configure other parameters.
  * @warning Each time SYSCLK changes, this function must be called to update the
  *          right SYSCLK value. Otherwise, any configuration based on this function will be incorrect.
  * @retval uint32_t SYSCLK frequency in Hz
  */
uint32_t HAL_RCC_GetSYSCLKFreq(void)
{
  uint32_t sysclockfreq;
  uint32_t sysclk_source;

  sysclk_source = LL_RCC_GetSysClkSource();

  if (sysclk_source == LL_RCC_SYS_CLKSOURCE_STATUS_HSIS)
  {
    /* HSIS used as system clock source */
    sysclockfreq = HSI_VALUE;
  }
  else if (sysclk_source == LL_RCC_SYS_CLKSOURCE_STATUS_HSIDIV3)
  {
    /* HSIS used as system clock source */
    sysclockfreq = HSI_VALUE / 3;
  }
#if defined(HSE_VALUE)
  else if (sysclk_source == LL_RCC_SYS_CLKSOURCE_STATUS_HSE)
  {
    /* HSE used as system clock source */
    sysclockfreq = HSE_VALUE;
  }
#endif /* HSE_VALUE */
  else
  {
    sysclockfreq = HAL_RCC_GetPSIClockFreq();
  }
  return sysclockfreq;
}

/**
  * @brief  Return the HCLK frequency.
  * @warning Each time HCLK changes, this function must be called to update the
  *          right HCLK value. Otherwise, any configuration based on this function will be incorrect.
  * @note   The SystemCoreClock CMSIS variable is used to store System Clock Frequency.
  * @retval uint32_t HCLK frequency in Hz
  */
uint32_t HAL_RCC_GetHCLKFreq(void)
{
  RCC_UPDATE_SYSTEMCORECLOCK();
  return SystemCoreClock;
}

/**
  * @brief  Return the PCLK1 frequency.
  * @warning Each time PCLK1 changes, this function must be called to update the
  *          right PCLK1 value. Otherwise, any configuration based on this function will be incorrect.
  * @retval uint32_t PCLK1 frequency in Hz
  */
uint32_t HAL_RCC_GetPCLK1Freq(void)
{
  /* Get HCLK source and Compute PCLK1 frequency */
  return (HAL_RCC_GetHCLKFreq() >> APBPrescTable[LL_RCC_GetAPB1Prescaler() >> RCC_CFGR2_PPRE1_Pos]);
}

/**
  * @brief  Return the PCLK2 frequency.
  * @warning Each time PCLK2 changes, this function must be called to update the
  *          right PCLK2 value. Otherwise, any configuration based on this function will be incorrect.
  * @retval uint32_t PCLK2 frequency in Hz
  */
uint32_t HAL_RCC_GetPCLK2Freq(void)
{
  /* Get HCLK source and Compute PCLK2 frequency */
  return (HAL_RCC_GetHCLKFreq() >> APBPrescTable[LL_RCC_GetAPB2Prescaler() >> RCC_CFGR2_PPRE2_Pos]);
}

/**
  * @brief  Return the PCLK3 frequency.
  * @warning Each time PCLK3 changes, this function must be called to update the
  *          right PCLK3 value. Otherwise, any configuration based on this function will be incorrect.
  * @retval uint32_t PCLK3 frequency in Hz
  */
uint32_t HAL_RCC_GetPCLK3Freq(void)
{
  /* Get HCLK source and Compute PCLK2 frequency */
  return (HAL_RCC_GetHCLKFreq() >> APBPrescTable[LL_RCC_GetAPB3Prescaler() >> RCC_CFGR2_PPRE3_Pos]);
}

/**
  * @}
  */
/**
  * @}
  */

/** @addtogroup RCC_Exported_Functions_Group2
  * @{
  */

/**
  * @brief  Select the clock source to output on MCO pin.
  * @param  mcox_src  specifies the clock source to output.
  * @param  mcox_prescaler  specifies the MCO prescaler.
  * @warning MCO selected pin must be configured in alternate function mode.
  */
void HAL_RCC_SetConfigMCO(hal_rcc_mco_src_t mcox_src, hal_rcc_mco_prescaler_t mcox_prescaler)
{
  ASSERT_DBG_PARAM(IS_RCC_MCOSOURCE(mcox_src));
  ASSERT_DBG_PARAM(IS_RCC_MCOPRE(mcox_prescaler));

  LL_RCC_ConfigMCO((uint32_t)mcox_src, (uint32_t)mcox_prescaler);
}

/**
  * @brief  Get and clear reset flags
  * @note   Once reset flags are retrieved, this API is clearing them in order to isolate next reset source.
  * @retval uint32_t Reset flags based on a combination of @ref RCC_Reset_Flag
  */
uint32_t HAL_RCC_GetResetSource(void)
{
  uint32_t reset;

  /* Get all reset flags */
  reset = RCC->RSR & HAL_RCC_RESET_FLAG_ALL;

  LL_RCC_ClearResetFlags();

  return reset;
}

#if defined(HSE_VALUE)
/**
  * @brief  Enable the Clock Security System.
  * @note   If a failure is detected on the HSE oscillator clock, this oscillator
  *         is automatically disabled and an interrupt is generated to inform the
  *         software about the failure (Clock Security System Interrupt, CSS),
  *         allowing the MCU to perform rescue operations. The CSS is linked to
  *         the Cortex-M33 NMI (Non-Maskable Interrupt) exception vector.
  * @note   The Clock Security System can only be cleared by reset.
  */
void HAL_RCC_HSE_EnableCSS(void)
{
  LL_RCC_HSE_EnableCSS();
}

#endif /* HSE_VALUE */
/**
  * @brief Handle the RCC Clock Security System interrupt request.
  * @warning This API must be called under the NMI_Handler().
  */
hal_status_t HAL_RCC_NMI_IRQHandler(void)
{
  hal_status_t cb_status = HAL_ERROR;

#if defined(HSE_VALUE)
  if (LL_RCC_IsActiveFlag(LL_RCC_IT_HSECSS) != 0U)
  {
    if (HAL_RCC_HSE_CSSCallback() == HAL_OK)
    {
      LL_RCC_ClearFlag(LL_RCC_IT_HSECSS);
      cb_status = HAL_OK;
    }
  }
#endif /* HSE_VALUE */
#if defined(LSE_VALUE)
  if (LL_RCC_IsActiveFlag(LL_RCC_IT_LSECSS) != 0U)
  {
    if (HAL_RCC_LSE_CSSCallback() == HAL_OK)
    {
      LL_RCC_ClearFlag(LL_RCC_IT_LSECSS);
      cb_status = HAL_OK;
    }
  }
#endif /* LSE_VALUE */
  return cb_status;
}

#if defined(HSE_VALUE)
/**
  * @brief  RCC Clock Security System interrupt callback.
  */
__WEAK hal_status_t HAL_RCC_HSE_CSSCallback(void)
{
  /* NOTE : This function must not be modified, when the callback is needed,
            the HAL_RCC_CSSCallback must be implemented in the user file
   */
  /* Status to be updated to HAL_OK when the user callback managed the CSS error */
  return HAL_ERROR;
}

/**
  * @brief  Set HSE Prescalers for RTC Clock
  * @param prescaler parameter can be a value between 0 and 511 with 0 meaning no clock
  * @retval HAL_OK    HSE RTC and prescaler is set.
  * note   prescaler must be correctly set to ensure that the clock supplied to the
  *        RTC is lower than 1 MHz.
  */
void  HAL_RCC_RTC_SetHSEPrescaler(uint32_t prescaler)
{
  ASSERT_DBG_PARAM(IS_RCC_RTC_HSEDIV(prescaler));

  LL_RCC_SetRTC_HSEPrescaler(prescaler);
}

/**
  * @brief  Get the RTC HSE prescaler.
  * @retval uint32_t Prescaler value
  */
uint32_t HAL_RCC_RTC_GetHSEPrescaler(void)
{
  return LL_RCC_GetRTC_HSEPrescaler();
}

#endif /* HSE_VALUE */
/**
  * @brief   Configure the oscillator clock source for wakeup from Stop and CSS backup clock.
  * @param   wakeup_clk  Wakeup clock
  *          This parameter can be one of the following values:
  *            @arg @ref HAL_RCC_STOP_WAKEUPCLOCK_HSIS  HSI clock selection
  *            @arg @ref HAL_RCC_STOP_WAKEUPCLOCK_HSIDIV3  HSI/3 clock selection
  * @warning This function must not be called after the Clock Security System on HSE has been enabled.
  */
void HAL_RCC_SetClockAfterWakeFromStop(hal_rcc_stop_wakeup_clk_t wakeup_clk)
{
  ASSERT_DBG_PARAM(IS_RCC_STOP_WAKEUPCLOCK(wakeup_clk));

  LL_RCC_SetClkAfterWakeFromStop((uint32_t)wakeup_clk);
}

/**
  * @brief   Get the oscillator clock source for wakeup from Stop and CSS backup clock.
  * @retval  hal_rcc_stop_wakeup_clk_t  Wakeup clock source
  */
hal_rcc_stop_wakeup_clk_t HAL_RCC_GetClockAfterWakeFromStop(void)
{
  return (hal_rcc_stop_wakeup_clk_t)LL_RCC_GetClkAfterWakeFromStop();
}

#if defined(LSE_VALUE)
/**
  * @brief  Enable the LSE Clock Security System.
  * @note   Prior to enable the LSE Clock Security System, LSE oscillator is to be enabled
  *         with HAL_RCC_LSE_Enable() and the LSE oscillator clock is to be selected as RTC
  *         clock with HAL_RCC_RTC_SetKernelClkSource().
  */
void HAL_RCC_LSE_EnableCSS(void)
{
  LL_RCC_LSE_EnableCSS();
}

/**
  * @brief  Disable the LSE Clock Security System.
  * @note   LSE Clock Security System can only be disabled after a LSE failure detection.
  */
void HAL_RCC_LSE_DisableCSS(void)
{
  LL_RCC_LSE_DisableCSS();
}

/**
  * @brief  RCC LSE Clock Security System interrupt callback.
  */
__WEAK hal_status_t HAL_RCC_LSE_CSSCallback(void)
{
  /* NOTE : This function must not be modified, when the callback is needed,
            the @ref HAL_RCC_LSECSS_Callback must be implemented in the user file
   */
  /* Status to be updated to HAL_OK when the user callback managed the CSS error */
  return HAL_ERROR;
}

#endif /* LSE_VALUE */
/**
  * @brief   Select source clock to use on the Low Speed Clock Output (LSCO).
  * @param   source  specifies the Low Speed clock source to output.
  * @note    PWR and backup domain are to enabled before calling this function.
  * @retval  HAL_OK      LSCO activated
  * @retval  HAL_ERROR   Backup domain is not enabled
  */
hal_status_t HAL_RCC_EnableLSCO(hal_rcc_lsco_src_t source)
{
  ASSERT_DBG_PARAM(IS_RCC_LSCOSOURCE(source));

  if (LL_PWR_IsEnabledRTCDomainWriteProtection() != 0U)
  {
    return HAL_ERROR;
  }

  LL_RCC_ConfigLSCO((uint32_t)source);

  LL_RCC_LSCO_Enable();

  return HAL_OK;
}

/**
  * @brief  Disable the Low Speed Clock Output (LSCO).
  * @note   PWR and backup domain are to enabled before calling this function.
  * @retval HAL_OK      LSCO Deactivated
  * @retval HAL_ERROR   Backup domain is not enabled
  */
hal_status_t HAL_RCC_DisableLSCO(void)
{
  if (LL_PWR_IsEnabledRTCDomainWriteProtection() != 0U)
  {
    return HAL_ERROR;
  }

  LL_RCC_LSCO_Disable();

  return HAL_OK;
}

/**
  * @brief Enable RTC and TAMP kernel clock.
  * @note  PWR and backup domain are to enabled before calling this function.
  * @retval HAL_OK      RTC and TAMP kernel clock enabled
  * @retval HAL_ERROR   Backup domain is not enabled
  */
hal_status_t HAL_RCC_RTC_EnableKernelClock(void)
{
  if (LL_PWR_IsEnabledRTCDomainWriteProtection() != 0U)
  {
    return HAL_ERROR;
  }

  LL_RCC_EnableRTC();

  return HAL_OK;
}

/**
  * @brief Disable RTC and TAMP kernel clock.
  * @note  PWR and backup domain are to enabled before calling this function.
  * @retval HAL_OK      RTC and TAMP kernel clock disabled
  * @retval HAL_ERROR   Backup domain is not enabled
  */
hal_status_t HAL_RCC_RTC_DisableKernelClock(void)
{
  if (LL_PWR_IsEnabledRTCDomainWriteProtection() != 0U)
  {
    return HAL_ERROR;
  }

  LL_RCC_DisableRTC();

  return HAL_OK;
}
/**
  * @}
  */

/** @addtogroup RCC_Exported_Functions_Group3
  * @{
  */
/**
  * @brief  Set the USART1 clock source
  * @param  clk_src Clock source selection based on @ref hal_rcc_usart1_clk_src_t
  * @retval HAL_OK    Source clock has been selected
  */
hal_status_t HAL_RCC_USART1_SetKernelClkSource(hal_rcc_usart1_clk_src_t clk_src)
{
  ASSERT_DBG_PARAM(IS_RCC_USART1_CLK(clk_src));

  LL_RCC_SetUSARTClockSource((uint32_t)clk_src);
  return HAL_OK;
}

/**
  * @brief  Set the USART2 clock source
  * @param  clk_src Clock source selection based on @ref hal_rcc_usart2_clk_src_t
  * @retval HAL_OK    Source clock has been selected
  */
hal_status_t HAL_RCC_USART2_SetKernelClkSource(hal_rcc_usart2_clk_src_t clk_src)
{
  ASSERT_DBG_PARAM(IS_RCC_USART2_CLK(clk_src));

  LL_RCC_SetUSARTClockSource((uint32_t)clk_src);
  return HAL_OK;
}

#if defined(USART3)
/**
  * @brief  Set the USART3 clock source
  * @param  clk_src Clock source selection based on @ref hal_rcc_usart3_clk_src_t
  * @retval HAL_OK    Source clock has been selected
  */
hal_status_t HAL_RCC_USART3_SetKernelClkSource(hal_rcc_usart3_clk_src_t clk_src)
{
  ASSERT_DBG_PARAM(IS_RCC_USART3_CLK(clk_src));

  LL_RCC_SetUSARTClockSource((uint32_t)clk_src);
  return HAL_OK;
}

#endif /* USART3 */
/**
  * @brief  Set the UART4 clock source
  * @param  clk_src Clock source selection based on @ref hal_rcc_uart4_clk_src_t
  * @retval HAL_OK    Source clock has been selected
  */
hal_status_t HAL_RCC_UART4_SetKernelClkSource(hal_rcc_uart4_clk_src_t clk_src)
{
  ASSERT_DBG_PARAM(IS_RCC_UART4_CLK(clk_src));

  LL_RCC_SetUARTClockSource((uint32_t)clk_src);
  return HAL_OK;
}

/**
  * @brief  Set the UART5 clock source
  * @param  clk_src Clock source selection based on @ref hal_rcc_uart5_clk_src_t
  * @retval HAL_OK    Source clock has been selected
  */
hal_status_t HAL_RCC_UART5_SetKernelClkSource(hal_rcc_uart5_clk_src_t clk_src)
{
  ASSERT_DBG_PARAM(IS_RCC_UART5_CLK(clk_src));

  LL_RCC_SetUARTClockSource((uint32_t)clk_src);
  return HAL_OK;
}

#if defined(USART6)
/**
  * @brief  Set the USART6 clock source
  * @param  clk_src Clock source selection based on @ref hal_rcc_usart6_clk_src_t
  * @retval HAL_OK    Source clock has been selected
  */
hal_status_t HAL_RCC_USART6_SetKernelClkSource(hal_rcc_usart6_clk_src_t clk_src)
{
  ASSERT_DBG_PARAM(IS_RCC_USART6_CLK(clk_src));

  LL_RCC_SetUSARTClockSource((uint32_t)clk_src);
  return HAL_OK;
}

#endif /* USART6 */
#if defined(USART7)
/**
  * @brief  Set the USART7 clock source
  * @param  clk_src Clock source selection based on @ref hal_rcc_usart7_clk_src_t
  * @retval HAL_OK    Source clock has been selected
  */
hal_status_t HAL_RCC_USART7_SetKernelClkSource(hal_rcc_usart7_clk_src_t clk_src)
{
  ASSERT_DBG_PARAM(IS_RCC_USART7_CLK(clk_src));

  LL_RCC_SetUSARTClockSource((uint32_t)clk_src);
  return HAL_OK;
}

#endif /* USART7 */
/**
  * @brief  Set the LPUART1 clock source
  * @param  clk_src Clock source selection based on @ref hal_rcc_lpuart1_clk_src_t
  * @retval HAL_OK    Source clock has been selected
  */
hal_status_t HAL_RCC_LPUART1_SetKernelClkSource(hal_rcc_lpuart1_clk_src_t clk_src)
{
  ASSERT_DBG_PARAM(IS_RCC_LPUART1_CLK(clk_src));

  LL_RCC_SetLPUARTClockSource((uint32_t)clk_src);
  return HAL_OK;
}

/**
  * @brief  Set the SPI1 clock source
  * @param  clk_src Clock source selection based on @ref hal_rcc_spi1_clk_src_t
  * @retval HAL_OK    Source clock has been selected
  */
hal_status_t HAL_RCC_SPI1_SetKernelClkSource(hal_rcc_spi1_clk_src_t clk_src)
{
  ASSERT_DBG_PARAM(IS_RCC_SPI1_CLK(clk_src));

  LL_RCC_SetSPIClockSource((uint32_t)clk_src);
  return HAL_OK;
}

/**
  * @brief  Set the SPI2 clock source
  * @param  clk_src Clock source selection based on @ref hal_rcc_spi2_clk_src_t
  * @retval HAL_OK    Source clock has been selected
  */
hal_status_t HAL_RCC_SPI2_SetKernelClkSource(hal_rcc_spi2_clk_src_t clk_src)
{
  ASSERT_DBG_PARAM(IS_RCC_SPI2_CLK(clk_src));

  LL_RCC_SetSPIClockSource((uint32_t)clk_src);
  return HAL_OK;
}

#if defined(SPI3)
/**
  * @brief  Set the SPI3 clock source
  * @param  clk_src Clock source selection based on @ref hal_rcc_spi3_clk_src_t
  * @retval HAL_OK    Source clock has been selected
  */
hal_status_t HAL_RCC_SPI3_SetKernelClkSource(hal_rcc_spi3_clk_src_t clk_src)
{
  ASSERT_DBG_PARAM(IS_RCC_SPI3_CLK(clk_src));

  LL_RCC_SetSPIClockSource((uint32_t)clk_src);
  return HAL_OK;
}

#endif /* SPI3 */
#if defined(FDCAN1)

/**
  * @brief  Set the FDCAN clock source
  * @param  clk_src Clock source selection based on @ref hal_rcc_fdcan_clk_src_t
  * @retval HAL_OK    Source clock has been selected
  * @note   The FDCAN clock is common for all FDCAN instances
  */
hal_status_t HAL_RCC_FDCAN_SetKernelClkSource(hal_rcc_fdcan_clk_src_t clk_src)
{
  ASSERT_DBG_PARAM(IS_RCC_FDCAN_CLK(clk_src));

  LL_RCC_SetFDCANClockSource((uint32_t)clk_src);
  return HAL_OK;
}
#endif /* FDCAN1 */

/**
  * @brief  Set the I2C1 clock source
  * @param  clk_src Clock source selection based on @ref hal_rcc_i2c1_clk_src_t
  * @retval HAL_OK    Source clock has been selected
  */
hal_status_t HAL_RCC_I2C1_SetKernelClkSource(hal_rcc_i2c1_clk_src_t clk_src)
{
  ASSERT_DBG_PARAM(IS_RCC_I2C1_CLK(clk_src));

  LL_RCC_SetI2CClockSource((uint32_t)clk_src);
  return HAL_OK;
}

#if defined(I2C2)
/**
  * @brief  Set the I2C2 clock source
  * @param  clk_src Clock source selection based on @ref hal_rcc_i2c2_clk_src_t
  * @retval HAL_OK    Source clock has been selected
  */
hal_status_t HAL_RCC_I2C2_SetKernelClkSource(hal_rcc_i2c2_clk_src_t clk_src)
{
  ASSERT_DBG_PARAM(IS_RCC_I2C2_CLK(clk_src));

  LL_RCC_SetI2CClockSource((uint32_t)clk_src);
  return HAL_OK;
}

#endif /* I2C2 */
/**
  * @brief  Set the I3C1 clock source
  * @param  clk_src Clock source selection based on @ref hal_rcc_i3c1_clk_src_t
  * @retval HAL_OK    Source clock has been selected
  */
hal_status_t HAL_RCC_I3C1_SetKernelClkSource(hal_rcc_i3c1_clk_src_t clk_src)
{
  ASSERT_DBG_PARAM(IS_RCC_I3C1_CLK(clk_src));

  LL_RCC_SetI3CClockSource((uint32_t)clk_src);
  return HAL_OK;
}

/**
  * @brief  Set the ADCDAC clock source
  * @param  clk_src Clock source selection based on @ref hal_rcc_adcdac_clk_src_t
  * @retval HAL_OK    Source clock has been selected
  * @note This bit must not be changed when ADC or DAC enabled.
  */
hal_status_t HAL_RCC_ADCDAC_SetKernelClkSource(hal_rcc_adcdac_clk_src_t clk_src)
{
  ASSERT_DBG_PARAM(IS_RCC_ADCDAC_CLK(clk_src));

  LL_RCC_SetADCDACClockSource((uint32_t)clk_src);
  return HAL_OK;
}

/**
  * @brief  Set the DAC1 clock source
  * @param  clk_src Clock source selection based on @ref hal_rcc_dac1_sh_clk_src_t
  * @retval HAL_OK    Source clock has been selected
  */
hal_status_t HAL_RCC_DAC1_SetSampleAndHoldClkSource(hal_rcc_dac1_sh_clk_src_t clk_src)
{
  ASSERT_DBG_PARAM(IS_RCC_DAC1_CLK(clk_src));

  LL_RCC_SetDAC1ClockSource((uint32_t)clk_src);
  return HAL_OK;
}

/**
  * @brief  Set the LPTIM1 clock source
  * @param  clk_src Clock source selection based on @ref hal_rcc_lptim1_clk_src_t
  * @retval HAL_OK    Source clock has been selected
  */
hal_status_t HAL_RCC_LPTIM1_SetKernelClkSource(hal_rcc_lptim1_clk_src_t clk_src)
{
  ASSERT_DBG_PARAM(IS_RCC_LPTIM1_CLK(clk_src));

  LL_RCC_SetLPTIMClockSource((uint32_t)clk_src);
  return HAL_OK;
}

/**
  * @brief  Set the CK48 clock source
  * @param  clk_src Clock source selection based on @ref hal_rcc_ck48_clk_src_t
  * @retval HAL_OK    Source clock has been selected
  */
hal_status_t HAL_RCC_CK48_SetKernelClkSource(hal_rcc_ck48_clk_src_t clk_src)
{
  ASSERT_DBG_PARAM(IS_RCC_CK48_CLK(clk_src));

  LL_RCC_SetCKClockSource((uint32_t)clk_src);
  return HAL_OK;
}

#if defined(XSPI1)
/**
  * @brief  Set the XSPI1 clock source
  * @param  clk_src Clock source selection based on @ref hal_rcc_xspi1_clk_src_t
  * @retval HAL_OK    Source clock has been selected
  */
hal_status_t HAL_RCC_XSPI1_SetKernelClkSource(hal_rcc_xspi1_clk_src_t clk_src)
{
  ASSERT_DBG_PARAM(IS_RCC_XSPI1_CLK(clk_src));

  LL_RCC_SetXSPIClockSource((uint32_t)clk_src);
  return HAL_OK;
}

#endif /* XSPI1 */
#if defined(ETH)
/**
  * @brief  Set the ETHREF clock source
  * @param  clk_src Clock source selection based on @ref hal_rcc_ethref_clk_src_t
  * @retval HAL_OK    Source clock has been selected
  */
hal_status_t HAL_RCC_ETHREF_SetKernelClkSource(hal_rcc_ethref_clk_src_t clk_src)
{
  ASSERT_DBG_PARAM(IS_RCC_ETHREF_CLK(clk_src));

  LL_RCC_SetETHClockSource((uint32_t)clk_src);
  return HAL_OK;
}

/**
  * @brief  Set the ETH PTP clock source
  * @param  clk_src Clock source selection based on @ref hal_rcc_ethptp_clk_src_t
  * @retval HAL_OK    Source clock has been selected
  */
hal_status_t HAL_RCC_ETHPTP_SetKernelClkSource(hal_rcc_ethptp_clk_src_t clk_src)
{
  ASSERT_DBG_PARAM(IS_RCC_ETHPTP_CLK(clk_src));

  LL_RCC_SetETHClockSource((uint32_t)clk_src);
  return HAL_OK;
}

/**
  * @brief  Set the ETH clock source
  * @param  clk_src Clock source selection based on @ref hal_rcc_eth_clk_src_t
  * @retval HAL_OK    Source clock has been selected
  */
hal_status_t HAL_RCC_ETH_SetKernelClkSource(hal_rcc_eth_clk_src_t clk_src)
{
  ASSERT_DBG_PARAM(IS_RCC_ETH_CLK(clk_src));

  LL_RCC_SetETHClockSource((uint32_t)clk_src);
  return HAL_OK;
}

#endif /* ETH */
/**
  * @brief  Set the RTC clock source
  * @param  clk_src Clock source selection based on @ref hal_rcc_rtc_clk_src_t
  * @note   Access to Backup domain has to be enabled.
  * @retval HAL_OK    RTC source clock has been selected
  * @retval HAL_ERROR LSE activation failed after reset of Backup domain
  */
hal_status_t HAL_RCC_RTC_SetKernelClkSource(hal_rcc_rtc_clk_src_t clk_src)
{
  hal_status_t status = HAL_OK;

  ASSERT_DBG_PARAM(IS_RCC_RTC_CLK(clk_src));

  /* Reset the Backup domain only if the RTC Clock source selection is modified from default */
  uint32_t tmpregister = LL_RCC_GetRTCClockSource();

  if ((tmpregister != LL_RCC_RTC_CLKSOURCE_NONE) && (tmpregister != (uint32_t)clk_src))
  {
    /* Store the content of RTCCR register before the reset of Backup Domain */
    tmpregister = READ_BIT(RCC->RTCCR, ~(RCC_RTCCR_RTCSEL));
    /* RTC Clock selection can be changed only if the Backup Domain is reset */
    HAL_RCC_ResetRTCDomain();
    /* Restore the Content of RTCCR register */
    RCC->RTCCR = tmpregister;
  }

#if defined(LSE_VALUE)
  /* Wait for LSE reactivation if LSE was enable prior to Backup Domain reset */
  if (IS_BIT_SET(tmpregister, RCC_RTCCR_LSEON))
  {
    status = RCC_WaitForTimeout(LL_RCC_LSE_IsReady, RCC_LSE_TIMEOUT_VALUE, 1U);
  }

  if (status == HAL_OK)
#endif /* LSE_VALUE */
  {
    /* Apply new RTC clock source selection */
    LL_RCC_SetRTCClockSource((uint32_t)clk_src);
  }

  return status;
}

/**
  * @brief  Get the USART1 clock source
  * @retval clk_src Clock source based on @ref hal_rcc_usart1_clk_src_t
  */
hal_rcc_usart1_clk_src_t HAL_RCC_USART1_GetKernelClkSource(void)
{
  return (hal_rcc_usart1_clk_src_t)LL_RCC_GetUSARTClockSource(LL_RCC_USART1_CLKSOURCE);
}

/**
  * @brief  Get the USART2 clock source
  * @retval clk_src Clock source based on @ref hal_rcc_usart2_clk_src_t
  */
hal_rcc_usart2_clk_src_t HAL_RCC_USART2_GetKernelClkSource(void)
{
  return (hal_rcc_usart2_clk_src_t)LL_RCC_GetUSARTClockSource(LL_RCC_USART2_CLKSOURCE);
}

#if defined(USART3)
/**
  * @brief  Get the USART3 clock source
  * @retval clk_src Clock source based on @ref hal_rcc_usart3_clk_src_t
  */
hal_rcc_usart3_clk_src_t HAL_RCC_USART3_GetKernelClkSource(void)
{
  return (hal_rcc_usart3_clk_src_t)LL_RCC_GetUSARTClockSource(LL_RCC_USART3_CLKSOURCE);
}

#endif /* USART3 */
/**
  * @brief  Get the UART4 clock source
  * @retval clk_src Clock source based on @ref hal_rcc_uart4_clk_src_t
  */
hal_rcc_uart4_clk_src_t HAL_RCC_UART4_GetKernelClkSource(void)
{
  return (hal_rcc_uart4_clk_src_t)LL_RCC_GetUARTClockSource(LL_RCC_UART4_CLKSOURCE);
}

/**
  * @brief  Get the UART5 clock source
  * @retval clk_src Clock source based on @ref hal_rcc_uart5_clk_src_t
  */
hal_rcc_uart5_clk_src_t HAL_RCC_UART5_GetKernelClkSource(void)
{
  return (hal_rcc_uart5_clk_src_t)LL_RCC_GetUARTClockSource(LL_RCC_UART5_CLKSOURCE);
}

#if defined(USART6)
/**
  * @brief  Get the USART6 clock source
  * @retval clk_src Clock source based on @ref hal_rcc_usart6_clk_src_t
  */
hal_rcc_usart6_clk_src_t HAL_RCC_USART6_GetKernelClkSource(void)
{
  return (hal_rcc_usart6_clk_src_t)LL_RCC_GetUSARTClockSource(LL_RCC_USART6_CLKSOURCE);
}

#endif /* USART6 */
#if defined(UART7)
/**
  * @brief  Get the UART7 clock source
  * @retval clk_src Clock source based on @ref hal_rcc_uart7_clk_src_t
  */
hal_rcc_uart7_clk_src_t HAL_RCC_UART7_GetKernelClkSource(void)
{
  return (hal_rcc_uart7_clk_src_t)LL_RCC_GetUARTClockSource(LL_RCC_UART7_CLKSOURCE);
}

#endif /* UART7 */
/**
  * @brief  Get the LPUART1 clock source
  * @retval clk_src Clock source based on @ref hal_rcc_lpuart1_clk_src_t
  */
hal_rcc_lpuart1_clk_src_t HAL_RCC_LPUART1_GetKernelClkSource(void)
{
  return (hal_rcc_lpuart1_clk_src_t)LL_RCC_GetLPUARTClockSource(LL_RCC_LPUART1_CLKSOURCE);
}

/**
  * @brief  Get the SPI1 clock source
  * @retval clk_src Clock source based on @ref hal_rcc_spi1_clk_src_t
  */
hal_rcc_spi1_clk_src_t HAL_RCC_SPI1_GetKernelClkSource(void)
{
  return (hal_rcc_spi1_clk_src_t)LL_RCC_GetSPIClockSource(LL_RCC_SPI1_CLKSOURCE);
}

/**
  * @brief  Get the SPI2 clock source
  * @retval clk_src Clock source based on @ref hal_rcc_spi2_clk_src_t
  */
hal_rcc_spi2_clk_src_t HAL_RCC_SPI2_GetKernelClkSource(void)
{
  return (hal_rcc_spi2_clk_src_t)LL_RCC_GetSPIClockSource(LL_RCC_SPI2_CLKSOURCE);
}

#if defined(SPI3)
/**
  * @brief  Get the SPI3 clock source
  * @retval clk_src Clock source based on @ref hal_rcc_spi3_clk_src_t
  */
hal_rcc_spi3_clk_src_t HAL_RCC_SPI3_GetKernelClkSource(void)
{
  return (hal_rcc_spi3_clk_src_t)LL_RCC_GetSPIClockSource(LL_RCC_SPI3_CLKSOURCE);
}

#endif /* SPI3 */
#if defined(FDCAN1)

/**
  * @brief  Get the FDCAN clock source
  * @retval clk_src Clock source based on @ref hal_rcc_fdcan_clk_src_t
  * @note   The FDCAN clock is common for all FDCAN instances
  */
hal_rcc_fdcan_clk_src_t HAL_RCC_FDCAN_GetKernelClkSource(void)
{
  return (hal_rcc_fdcan_clk_src_t)LL_RCC_GetFDCANClockSource(LL_RCC_FDCAN_CLKSOURCE);
}
#endif /* FDCAN1 */

/**
  * @brief  Get the I2C1 clock source
  * @retval clk_src Clock source based on @ref hal_rcc_i2c1_clk_src_t
  */
hal_rcc_i2c1_clk_src_t HAL_RCC_I2C1_GetKernelClkSource(void)
{
  return (hal_rcc_i2c1_clk_src_t)LL_RCC_GetI2CClockSource(LL_RCC_I2C1_CLKSOURCE);
}

#if defined(I2C2)
/**
  * @brief  Get the I2C2 clock source
  * @retval clk_src Clock source based on @ref hal_rcc_i2c2_clk_src_t
  */
hal_rcc_i2c2_clk_src_t HAL_RCC_I2C2_GetKernelClkSource(void)
{
  return (hal_rcc_i2c2_clk_src_t)LL_RCC_GetI2CClockSource(LL_RCC_I2C2_CLKSOURCE);
}

#endif /* I2C2 */
/**
  * @brief  Get the I3C1 clock source
  * @retval clk_src Clock source based on @ref hal_rcc_i3c1_clk_src_t
  */
hal_rcc_i3c1_clk_src_t HAL_RCC_I3C1_GetKernelClkSource(void)
{
  return (hal_rcc_i3c1_clk_src_t)LL_RCC_GetI3CClockSource(LL_RCC_I3C1_CLKSOURCE);
}

/**
  * @brief  Get the ADCDAC clock source
  * @retval clk_src Clock source based on @ref hal_rcc_adcdac_clk_src_t
  */
hal_rcc_adcdac_clk_src_t HAL_RCC_ADCDAC_GetKernelClkSource(void)
{
  return (hal_rcc_adcdac_clk_src_t)LL_RCC_GetADCDACClockSource(LL_RCC_ADCDAC_CLKSOURCE);
}

/**
  * @brief  Get the DAC1 clock source
  * @retval clk_src Clock source based on @ref hal_rcc_dac1_sh_clk_src_t
  */
hal_rcc_dac1_sh_clk_src_t HAL_RCC_DAC1_GetSampleHoldClkSource(void)
{
  return (hal_rcc_dac1_sh_clk_src_t)LL_RCC_GetDAC1ClockSource(LL_RCC_DAC1_CLKSOURCE);
}

/**
  * @brief  Get the LPTIM1 clock source
  * @retval clk_src Clock source based on @ref hal_rcc_lptim1_clk_src_t
  */
hal_rcc_lptim1_clk_src_t HAL_RCC_LPTIM1_GetKernelClkSource(void)
{
  return (hal_rcc_lptim1_clk_src_t)LL_RCC_GetLPTIMClockSource(LL_RCC_LPTIM1_CLKSOURCE);
}

/**
  * @brief  Get the CK48 clock source
  * @retval clk_src Clock source based on @ref hal_rcc_ck48_clk_src_t
  */
hal_rcc_ck48_clk_src_t HAL_RCC_CK48_GetKernelClkSource(void)
{
  return (hal_rcc_ck48_clk_src_t)LL_RCC_GetCKClockSource(LL_RCC_CK48_CLKSOURCE);
}

#if defined(XSPI1)
/**
  * @brief  Get the XSPI1 clock source
  * @retval clk_src Clock source based on @ref hal_rcc_xspi1_clk_src_t
  */
hal_rcc_xspi1_clk_src_t HAL_RCC_XSPI1_GetKernelClkSource(void)
{
  return (hal_rcc_xspi1_clk_src_t)LL_RCC_GetXSPIClockSource(LL_RCC_XSPI1_CLKSOURCE);
}

#endif /* XSPI1 */
#if defined(ETH)
/**
  * @brief  Get the ETH REF clock source
  * @retval clk_src Clock source based on @ref hal_rcc_ethref_clk_src_t
  */
hal_rcc_ethref_clk_src_t HAL_RCC_ETHREF_GetKernelClkSource(void)
{
  return (hal_rcc_ethref_clk_src_t)LL_RCC_GetETHClockSource(LL_RCC_ETHREF_CLKSOURCE);
}

/**
  * @brief  Get the ETH PTP clock source
  * @retval clk_src Clock source based on @ref hal_rcc_ethptp_clk_src_t
  */
hal_rcc_ethptp_clk_src_t HAL_RCC_ETHPTP_GetKernelClkSource(void)
{
  return (hal_rcc_ethptp_clk_src_t)LL_RCC_GetETHClockSource(LL_RCC_ETHPTP_CLKSOURCE);
}

/**
  * @brief  Get the ETH clock source
  * @retval clk_src Clock source based on @ref hal_rcc_eth_clk_src_t
  */
hal_rcc_eth_clk_src_t HAL_RCC_ETH_GetKernelClkSource(void)
{
  return (hal_rcc_eth_clk_src_t)LL_RCC_GetETHClockSource(LL_RCC_ETH_CLKSOURCE);
}

#endif /* ETH */
/**
  * @brief  Get the RTC clock source
  * @retval clk_src Clock source based on @ref hal_rcc_rtc_clk_src_t
  */
hal_rcc_rtc_clk_src_t HAL_RCC_RTC_GetKernelClkSource(void)
{
  return (hal_rcc_rtc_clk_src_t)LL_RCC_GetRTCClockSource();
}

/**
  * @brief  Set the ADCDAC prescaler
  * @param  adcdac_pre Prescaler selection based on @ref hal_rcc_adcdac_prescaler_t
  * @retval HAL_OK     Prescaler has been selected
  * @note This bit must not be changed when ADC or DAC enabled.
  */
hal_status_t HAL_RCC_ADCDAC_SetKernelClkPrescaler(hal_rcc_adcdac_prescaler_t adcdac_pre)
{
  ASSERT_DBG_PARAM(IS_RCC_ADCDAC_PRESCALER(adcdac_pre));

  LL_RCC_SetADCDACPrescaler((uint32_t)adcdac_pre);
  return HAL_OK;
}

/**
  * @brief  Get the ADCDAC prescaler
  * @retval value based on @ref hal_rcc_adcdac_prescaler_t
  */
hal_rcc_adcdac_prescaler_t HAL_RCC_ADCDAC_GetKernelClkPrescaler(void)
{

  return (hal_rcc_adcdac_prescaler_t)LL_RCC_GetADCDACPrescaler(LL_RCC_ADCDAC_CLKSOURCE);
}

/**
  * @brief  Set the ADCDAC Clock source and prescaler
  * @note   Clock source and prescaler can be update only if ADCDAC is disabled
  * @param  clk_src Clock source selection based on @ref hal_rcc_adcdac_clk_src_t
  * @param  adcdac_pre Prescaler selection based on @ref hal_rcc_adcdac_prescaler_t
  * @retval HAL_OK     CLock source and prescaler has been selected
  *         HAL_ERROR  ADCDAC is enabled
  */
hal_status_t HAL_RCC_ADCDAC_SetConfigKernelClk(hal_rcc_adcdac_clk_src_t clk_src, hal_rcc_adcdac_prescaler_t adcdac_pre)
{
  ASSERT_DBG_PARAM(IS_RCC_ADCDAC_CLK(clk_src));
  ASSERT_DBG_PARAM(IS_RCC_ADCDAC_PRESCALER(adcdac_pre));

#if defined(ADC3)
  if ((LL_AHB2_GRP1_IsEnabledClock(LL_AHB2_GRP1_PERIPH_ADC12) == 1U)
      || (LL_AHB2_GRP1_IsEnabledClock(LL_AHB2_GRP1_PERIPH_ADC3) == 1U))
#else
  if (LL_AHB2_GRP1_IsEnabledClock(LL_AHB2_GRP1_PERIPH_ADC12) == 1U)
#endif /* ADC3 */
  {
    return HAL_ERROR;
  }
  else
  {
    LL_RCC_ConfigADCDAC((uint32_t)clk_src, (uint32_t)adcdac_pre);
  }
  return HAL_OK;
}

/**
  * @brief  Get the ADCDAC Clock source and prescaler
  * @param  p_clk_src Pointer on @ref hal_rcc_adcdac_clk_src_t
  * @param  p_prescaler Pointer on @ref hal_rcc_adcdac_prescaler_t
  */
void HAL_RCC_ADCDAC_GetConfigKernelClk(hal_rcc_adcdac_clk_src_t *p_clk_src, hal_rcc_adcdac_prescaler_t *p_prescaler)
{
  ASSERT_DBG_PARAM(p_clk_src != (void *)NULL);
  ASSERT_DBG_PARAM(p_prescaler != (void *)NULL);

  uint32_t clk_src;
  uint32_t prescaler;

  /* Get ADC clock source and prescaler */
  LL_RCC_GetConfigADCDAC(&clk_src, &prescaler);

  *p_clk_src = (hal_rcc_adcdac_clk_src_t)clk_src;
  *p_prescaler = (hal_rcc_adcdac_prescaler_t)prescaler;
}

#if defined(ETH)
/**
  * @brief  Set the ETH prescaler
  * @param  eth_div Prescaler selection based on @ref hal_rcc_eth_div_t
  * @retval HAL_OK     Prescaler has been selected
  */
hal_status_t HAL_RCC_ETH_SetKernelClkPrescaler(hal_rcc_eth_div_t eth_div)
{
  ASSERT_DBG_PARAM(IS_RCC_ETH_PRESCALER(eth_div));

  LL_RCC_SetETHPrescaler((uint32_t)eth_div);
  return HAL_OK;
}

/**
  * @brief  Get the ETH prescaler
  * @retval value based on @ref hal_rcc_eth_div_t
  */
hal_rcc_eth_div_t HAL_RCC_ETH_GetKernelClkPrescaler(void)
{

  return (hal_rcc_eth_div_t)LL_RCC_GetETHPrescaler();
}

/**
  * @brief  Set the ETH Clock source and prescaler
  * @note   Clock source and prescaler can be update only if ETH is disabled
  * @param  clk_src Clock source selection based on @ref hal_rcc_eth_clk_src_t
  * @param  eth_div Prescaler selection based on @ref hal_rcc_eth_div_t
  * @retval HAL_OK     CLock source and prescaler has been selected
  *         HAL_ERROR  ETH is enabled
  */
hal_status_t HAL_RCC_SetConfigETHKernelClk(hal_rcc_eth_clk_src_t clk_src, hal_rcc_eth_div_t eth_div)
{
  ASSERT_DBG_PARAM(IS_RCC_ETH_CLK(clk_src));
  ASSERT_DBG_PARAM(IS_RCC_ETH_PRESCALER(eth_div));

  LL_RCC_ConfigETH((uint32_t)clk_src, (uint32_t)eth_div);
  return HAL_OK;
}

/**
  * @brief  Get the ETH Clock source and prescaler
  * @param  p_clk_src Pointer on @ref hal_rcc_eth_clk_src_t
  * @param  p_prescaler Pointer on @ref hal_rcc_eth_div_t
  */
void HAL_RCC_GetConfigETHKernelClk(hal_rcc_eth_clk_src_t *p_clk_src, hal_rcc_eth_div_t *p_prescaler)
{
  ASSERT_DBG_PARAM(p_clk_src != (void *)NULL);
  ASSERT_DBG_PARAM(p_prescaler != (void *)NULL);

  uint32_t clk_src;
  uint32_t prescaler;

  /* Get ETH clock source and prescaler */
  LL_RCC_GetConfigETH(&clk_src, &prescaler);

  *p_clk_src = (hal_rcc_eth_clk_src_t)clk_src;
  *p_prescaler = (hal_rcc_eth_div_t)prescaler;
}

/**
  * @brief  Set the ETHPTP prescaler
  * @param  ethptp_div Prescaler selection based on @ref hal_rcc_ethptp_div_t
  * @retval HAL_OK     Prescaler has been selected
  * @note This bit must not be changed when ADC or DAC enabled.
  */
hal_status_t HAL_RCC_ETHPTP_SetKernelClkPrescaler(hal_rcc_ethptp_div_t ethptp_div)
{
  ASSERT_DBG_PARAM(IS_RCC_ETHPTP_PRESCALER(ethptp_div));

  LL_RCC_SetETHPTPPrescaler((uint32_t)ethptp_div);
  return HAL_OK;
}

/**
  * @brief  Get the ETHPTP prescaler
  * @retval value based on @ref hal_rcc_ethptp_div_t
  */
hal_rcc_ethptp_div_t HAL_RCC_ETHPTP_GetKernelClkPrescaler(void)
{

  return (hal_rcc_ethptp_div_t)LL_RCC_GetETHPTPPrescaler();
}

/**
  * @brief  Set the ethptp PTP Clock source and prescaler
  * @note   Clock source and prescaler can be update only if ethptp PTP is disabled
  * @param  clk_src Clock source selection based on @ref hal_rcc_ethptp_clk_src_t
  * @param  ethptp_div Prescaler selection based on @ref hal_rcc_ethptp_div_t
  * @retval HAL_OK     CLock source and prescaler has been selected
  *         HAL_ERROR  ethptp PTP is enabled
  */
hal_status_t HAL_RCC_SetConfigETHPTPKernelClk(hal_rcc_ethptp_clk_src_t clk_src, hal_rcc_ethptp_div_t ethptp_div)
{
  ASSERT_DBG_PARAM(IS_RCC_ETHPTP_CLK(clk_src));
  ASSERT_DBG_PARAM(IS_RCC_ETHPTP_PRESCALER(ethptp_div));

  LL_RCC_ConfigETHPTP((uint32_t)clk_src, (uint32_t)ethptp_div);
  return HAL_OK;
}

/**
  * @brief  Get the ETHPTP Clock source and prescaler
  * @param  p_clk_src Pointer on @ref hal_rcc_ethptp_clk_src_t
  * @param  p_prescaler Pointer on @ref hal_rcc_ethptp_div_t
  */
void HAL_RCC_GetConfigETHPTPKernelClk(hal_rcc_ethptp_clk_src_t *p_clk_src, hal_rcc_ethptp_div_t *p_prescaler)
{
  ASSERT_DBG_PARAM(p_clk_src != (void *)NULL);
  ASSERT_DBG_PARAM(p_prescaler != (void *)NULL);

  uint32_t clk_src;
  uint32_t prescaler;

  /* Get ETHPTP clock source and prescaler */
  LL_RCC_GetConfigETHPTP(&clk_src, &prescaler);

  *p_clk_src = (hal_rcc_ethptp_clk_src_t)clk_src;
  *p_prescaler = (hal_rcc_ethptp_div_t)prescaler;
}

#endif /* ETH */
/**
  * @brief  Return the peripheral clock frequency for UART/LPUART
  * @param  uartx UART instance
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator not ready)
  */
uint32_t HAL_RCC_UART_GetKernelClkFreq(const USART_TypeDef *uartx)
{
  uint32_t frequency;

  if (uartx == USART1)
  {
    frequency = HAL_RCC_USART1_GetKernelClkFreq();
  }
#if defined (USART2)
  else if (uartx == USART2)
  {
    frequency = HAL_RCC_USART2_GetKernelClkFreq();
  }
#endif /* USART2 */
#if defined(USART3)
  else if (uartx == USART3)
  {
    frequency = HAL_RCC_USART3_GetKernelClkFreq();
  }
#endif /* USART3 */
  else if (uartx == UART4)
  {
    frequency = HAL_RCC_UART4_GetKernelClkFreq();
  }
  else if (uartx == UART5)
  {
    frequency = HAL_RCC_UART5_GetKernelClkFreq();
  }
#if defined(UART7)
  else if (uartx == UART7)
  {
    frequency = HAL_RCC_UART7_GetKernelClkFreq();
  }
#endif /* UART7 */
  else if (uartx == LPUART1)
  {
    frequency = HAL_RCC_LPUART1_GetKernelClkFreq();
  }
  else
  {
    frequency = 0U;
  }

  return frequency;
}

/**
  * @brief  Return the peripheral clock frequency for USART1
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator not ready)
  */
uint32_t HAL_RCC_USART1_GetKernelClkFreq(void)
{
  uint32_t frequency = 0U;
  uint32_t srcclk = LL_RCC_GetUSARTClockSource(LL_RCC_USART1_CLKSOURCE);

  if (srcclk == LL_RCC_USART1_CLKSOURCE_PCLK2)
  {
    frequency = HAL_RCC_GetPCLK2Freq();
  }
  else if ((LL_RCC_PSIK_IsReady() != 0U) && (srcclk == LL_RCC_USART1_CLKSOURCE_PSIK))
  {
    frequency = (HAL_RCC_GetPSIClockFreq() * 10UL) / RCC_GetDividerValue(LL_RCC_PSIK_GetDivider());
  }
  else if ((LL_RCC_HSIK_IsReady() != 0U) && (srcclk == LL_RCC_USART1_CLKSOURCE_HSIK))
  {
    frequency = (HSI_VALUE * 10UL) /  RCC_GetDividerValue(LL_RCC_HSIK_GetDivider());
  }
#if defined(LSE_VALUE)
  else if ((LL_RCC_LSE_IsReady() != 0U) && (srcclk == LL_RCC_USART1_CLKSOURCE_LSE))
  {
    frequency = LSE_VALUE;
  }
#endif /* LSE_VALUE */

  return frequency;
}

/**
  * @brief  Return the peripheral clock frequency for USART2
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator not ready)
  */
uint32_t  HAL_RCC_USART2_GetKernelClkFreq(void)
{
  uint32_t frequency = 0U;
  uint32_t srcclk = LL_RCC_GetUSARTClockSource(LL_RCC_USART2_CLKSOURCE);

  if (srcclk == LL_RCC_USART2_CLKSOURCE_PCLK1)
  {
    frequency = HAL_RCC_GetPCLK1Freq();
  }
  else if ((LL_RCC_PSIK_IsReady() != 0U) && (srcclk == LL_RCC_USART2_CLKSOURCE_PSIK))
  {
    frequency = (HAL_RCC_GetPSIClockFreq() * 10UL) / RCC_GetDividerValue(LL_RCC_PSIK_GetDivider());
  }
  else if ((LL_RCC_HSIK_IsReady() != 0U) && (srcclk == LL_RCC_USART2_CLKSOURCE_HSIK))
  {
    frequency = (HSI_VALUE * 10UL) /  RCC_GetDividerValue(LL_RCC_HSIK_GetDivider());
  }
#if defined(LSE_VALUE)
  else if ((LL_RCC_LSE_IsReady() != 0U) && (srcclk == LL_RCC_USART2_CLKSOURCE_LSE))
  {
    frequency = LSE_VALUE;
  }
#endif /* LSE_VALUE */

  return frequency;
}

#if defined(USART3)
/**
  * @brief  Return the peripheral clock frequency for USART3
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator not ready)
  */
uint32_t HAL_RCC_USART3_GetKernelClkFreq(void)
{
  uint32_t frequency = 0U;
  uint32_t srcclk = LL_RCC_GetUARTClockSource(LL_RCC_USART3_CLKSOURCE);

  if (srcclk == LL_RCC_USART3_CLKSOURCE_PCLK1)
  {
    frequency = HAL_RCC_GetPCLK1Freq();
  }
  else if ((LL_RCC_PSIK_IsReady() != 0U) && (srcclk == LL_RCC_USART3_CLKSOURCE_PSIK))
  {
    frequency = (HAL_RCC_GetPSIClockFreq() * 10UL) / RCC_GetDividerValue(LL_RCC_PSIK_GetDivider());
  }
  else if ((LL_RCC_HSIK_IsReady() != 0U) && (srcclk == LL_RCC_USART3_CLKSOURCE_HSIK))
  {
    frequency = (HSI_VALUE * 10UL) /  RCC_GetDividerValue(LL_RCC_HSIK_GetDivider());
  }
#if defined(LSE_VALUE)
  else if ((LL_RCC_LSE_IsReady() != 0U) && (srcclk == LL_RCC_USART3_CLKSOURCE_LSE))
  {
    frequency = LSE_VALUE;
  }
#endif /* LSE_VALUE */
  return frequency;
}

#endif /* USART3 */
/**
  * @brief  Return the peripheral clock frequency for UART4
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator not ready)
  */
uint32_t HAL_RCC_UART4_GetKernelClkFreq(void)
{
  uint32_t frequency = 0U;
  uint32_t srcclk = LL_RCC_GetUARTClockSource(LL_RCC_UART4_CLKSOURCE);

  if (srcclk == LL_RCC_UART4_CLKSOURCE_PCLK1)
  {
    frequency = HAL_RCC_GetPCLK1Freq();
  }
  else if ((LL_RCC_PSIK_IsReady() != 0U) && (srcclk == LL_RCC_UART4_CLKSOURCE_PSIK))
  {
    frequency = (HAL_RCC_GetPSIClockFreq() * 10UL) / RCC_GetDividerValue(LL_RCC_PSIK_GetDivider());
  }
  else if ((LL_RCC_HSIK_IsReady() != 0U) && (srcclk == LL_RCC_UART4_CLKSOURCE_HSIK))
  {
    frequency = (HSI_VALUE * 10UL) /  RCC_GetDividerValue(LL_RCC_HSIK_GetDivider());
  }
#if defined(LSE_VALUE)
  else if ((LL_RCC_LSE_IsReady() != 0U) && (srcclk == LL_RCC_UART4_CLKSOURCE_LSE))
  {
    frequency = LSE_VALUE;
  }
#endif /* LSE_VALUE */

  return frequency;
}

/**
  * @brief  Return the peripheral clock frequency for UART5
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator not ready)
  */
uint32_t HAL_RCC_UART5_GetKernelClkFreq(void)
{
  uint32_t frequency = 0U;
  uint32_t srcclk = LL_RCC_GetUARTClockSource(LL_RCC_UART5_CLKSOURCE);

  if (srcclk == LL_RCC_UART5_CLKSOURCE_PCLK1)
  {
    frequency = HAL_RCC_GetPCLK1Freq();
  }
  else if ((LL_RCC_PSIK_IsReady() != 0U) && (srcclk == LL_RCC_UART5_CLKSOURCE_PSIK))
  {
    frequency = (HAL_RCC_GetPSIClockFreq() * 10UL) / RCC_GetDividerValue(LL_RCC_PSIK_GetDivider());
  }
  else if ((LL_RCC_HSIK_IsReady() != 0U) && (srcclk == LL_RCC_UART5_CLKSOURCE_HSIK))
  {
    frequency = (HSI_VALUE * 10UL) /  RCC_GetDividerValue(LL_RCC_HSIK_GetDivider());
  }
#if defined(LSE_VALUE)
  else if ((LL_RCC_LSE_IsReady() != 0U) && (srcclk == LL_RCC_UART5_CLKSOURCE_LSE))
  {
    frequency = LSE_VALUE;
  }
#endif /* LSE_VALUE */

  return frequency;
}

#if defined(USART6)
/**
  * @brief  Return the peripheral clock frequency for USART6
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator not ready)
  */
uint32_t HAL_RCC_USART6_GetKernelClkFreq(void)
{
  uint32_t frequency = 0U;
  uint32_t srcclk = LL_RCC_GetUARTClockSource(LL_RCC_USART6_CLKSOURCE);

  if (srcclk == LL_RCC_USART6_CLKSOURCE_PCLK1)
  {
    frequency = HAL_RCC_GetPCLK1Freq();
  }
  else if ((LL_RCC_PSIK_IsReady() != 0U) && (srcclk == LL_RCC_USART6_CLKSOURCE_PSIK))
  {
    frequency = (HAL_RCC_GetPSIClockFreq() * 10UL) / RCC_GetDividerValue(LL_RCC_PSIK_GetDivider());
  }
  else if ((LL_RCC_HSIK_IsReady() != 0U) && (srcclk == LL_RCC_USART6_CLKSOURCE_HSIK))
  {
    frequency = (HSI_VALUE * 10UL) /  RCC_GetDividerValue(LL_RCC_HSIK_GetDivider());
  }
#if defined(LSE_VALUE)
  else if ((LL_RCC_LSE_IsReady() != 0U) && (srcclk == LL_RCC_USART6_CLKSOURCE_LSE))
  {
    frequency = LSE_VALUE;
  }
#endif /* LSE_VALUE */
  return frequency;
}

#endif /* USART6 */
#if defined(UART7)
/**
  * @brief  Return the peripheral clock frequency for UART7
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator not ready)
  */
uint32_t HAL_RCC_UART7_GetKernelClkFreq(void)
{
  uint32_t frequency = 0U;
  uint32_t srcclk = LL_RCC_GetUARTClockSource(LL_RCC_UART7_CLKSOURCE);

  if (srcclk == LL_RCC_UART7_CLKSOURCE_PCLK1)
  {
    frequency = HAL_RCC_GetPCLK1Freq();
  }
  else if ((LL_RCC_PSIK_IsReady() != 0U) && (srcclk == LL_RCC_UART7_CLKSOURCE_PSIK))
  {
    frequency = (HAL_RCC_GetPSIClockFreq() * 10UL) / RCC_GetDividerValue(LL_RCC_PSIK_GetDivider());
  }
  else if ((LL_RCC_HSIK_IsReady() != 0U) && (srcclk == LL_RCC_UART7_CLKSOURCE_HSIK))
  {
    frequency = (HSI_VALUE * 10UL) /  RCC_GetDividerValue(LL_RCC_HSIK_GetDivider());
  }
#if defined(LSE_VALUE)
  else if ((LL_RCC_LSE_IsReady() != 0U) && (srcclk == LL_RCC_UART7_CLKSOURCE_LSE))
  {
    frequency = LSE_VALUE;
  }
#endif /* LSE_VALUE */

  return frequency;
}

#endif /* UART7 */
/**
  * @brief  Return the peripheral clock frequency for LPUART1
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator not ready)
  */
uint32_t HAL_RCC_LPUART1_GetKernelClkFreq(void)
{
  uint32_t frequency = 0U;
  uint32_t srcclk = LL_RCC_GetLPUARTClockSource(LL_RCC_LPUART1_CLKSOURCE);

  if (srcclk == LL_RCC_LPUART1_CLKSOURCE_PCLK3)
  {
    frequency = HAL_RCC_GetPCLK3Freq();
  }
  else if ((LL_RCC_HSIK_IsReady() != 0U) && (srcclk == LL_RCC_LPUART1_CLKSOURCE_HSIK))
  {
    frequency = (HSI_VALUE * 10UL) /  RCC_GetDividerValue(LL_RCC_HSIK_GetDivider());
  }
#if defined(LSE_VALUE)
  else if ((LL_RCC_LSE_IsReady() != 0U) && (srcclk == LL_RCC_LPUART1_CLKSOURCE_LSE))
  {
    frequency = LSE_VALUE;
  }
#endif /* LSE_VALUE */
  else if ((LL_RCC_LSI_IsReady() != 0U) && (srcclk == LL_RCC_LPUART1_CLKSOURCE_LSI))
  {
    frequency = LSI_VALUE;
  }

  return frequency;
}

/**
  * @brief  Return the peripheral clock frequency for USART/SMARTCARD
  * @param  usartx USART instance
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator not ready)
  */
uint32_t HAL_RCC_USART_GetKernelClkFreq(const USART_TypeDef *usartx)
{
  uint32_t frequency;

  if (usartx == USART1)
  {
    frequency = HAL_RCC_USART1_GetKernelClkFreq();
  }
#if defined (USART2)
  else if (usartx == USART2)
  {
    frequency = HAL_RCC_USART2_GetKernelClkFreq();
  }
#endif /* USART2 */
#if defined (USART3)
  else if (usartx == USART3)
  {
    frequency = HAL_RCC_USART3_GetKernelClkFreq();
  }
#endif /* USART3 */
#if defined (USART6)
  else if (usartx == USART6)
  {
    frequency = HAL_RCC_USART6_GetKernelClkFreq();
  }
#endif /* USART6 */
  else
  {
    frequency = 0U;
  }

  return frequency;
}

/**
  * @brief  Return the peripheral clock frequency for SPI
  * @param  spix SPI instance
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator not ready)
  */
uint32_t HAL_RCC_SPI_GetKernelClkFreq(const SPI_TypeDef *spix)
{
  uint32_t frequency;

  if (spix == SPI1)
  {
    frequency = HAL_RCC_SPI1_GetKernelClkFreq();
  }
  else if (spix == SPI2)
  {
    frequency = HAL_RCC_SPI2_GetKernelClkFreq();
  }
#if defined(SPI3)
  else if (spix == SPI3)
  {
    frequency = HAL_RCC_SPI3_GetKernelClkFreq();
  }
#endif /* SPI3 */
  else
  {
    frequency = 0U;
  }

  return frequency;
}

/**
  * @brief  Return the peripheral clock frequency for SPI1
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator not ready)
  */
uint32_t HAL_RCC_SPI1_GetKernelClkFreq(void)
{
  uint32_t frequency = 0U;
  uint32_t srcclk = LL_RCC_GetSPIClockSource(LL_RCC_SPI1_CLKSOURCE);

  if (srcclk == LL_RCC_SPI1_CLKSOURCE_PCLK2)
  {
    frequency = HAL_RCC_GetPCLK2Freq();
  }
  else if ((srcclk == LL_RCC_SPI1_CLKSOURCE_PSIK) && (LL_RCC_PSIK_IsReady() != 0U))
  {
    frequency = (HAL_RCC_GetPSIClockFreq() * 10UL) / RCC_GetDividerValue(LL_RCC_PSIK_GetDivider());
  }
  else if ((srcclk == LL_RCC_SPI1_CLKSOURCE_HSIK) && (LL_RCC_HSIK_IsReady() != 0U))
  {
    frequency = (HSI_VALUE * 10UL) /  RCC_GetDividerValue(LL_RCC_HSIK_GetDivider());
  }
#if defined(AUDIO_CLOCK_VALUE)
  else if (srcclk == LL_RCC_SPI1_CLKSOURCE_AUDIOCLK)
  {
    frequency = AUDIO_CLOCK_VALUE;
  }
#endif /* AUDIO_CLOCK_VALUE */
  else
  {
    frequency = 0U;
  }

  return frequency;
}

/**
  * @brief  Return the peripheral clock frequency for SPI2
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator not ready)
  */
uint32_t HAL_RCC_SPI2_GetKernelClkFreq(void)
{
  uint32_t frequency = 0U;
  uint32_t srcclk = LL_RCC_GetSPIClockSource(LL_RCC_SPI2_CLKSOURCE);
  if (srcclk == LL_RCC_SPI2_CLKSOURCE_PCLK1)
  {
    frequency = HAL_RCC_GetPCLK1Freq();
  }
  else if ((srcclk == LL_RCC_SPI2_CLKSOURCE_PSIK) && (LL_RCC_PSIK_IsReady() != 0U))
  {
    frequency = (HAL_RCC_GetPSIClockFreq() * 10UL) / RCC_GetDividerValue(LL_RCC_PSIK_GetDivider());
  }
  else if ((srcclk == LL_RCC_SPI2_CLKSOURCE_HSIK) && (LL_RCC_HSIK_IsReady() != 0U))
  {
    frequency = (HSI_VALUE * 10UL) /  RCC_GetDividerValue(LL_RCC_HSIK_GetDivider());
  }
#if defined(AUDIO_CLOCK_VALUE)
  else if (srcclk == LL_RCC_SPI2_CLKSOURCE_AUDIOCLK)
  {
    frequency = AUDIO_CLOCK_VALUE;
  }
#endif /* AUDIO_CLOCK_VALUE */
  else
  {
    frequency = 0U;
  }

  return frequency;
}

#if defined(SPI3)
/**
  * @brief  Return the peripheral clock frequency for SPI3
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator not ready)
  */
uint32_t HAL_RCC_SPI3_GetKernelClkFreq(void)
{
  uint32_t frequency = 0U;
  uint32_t srcclk = LL_RCC_GetSPIClockSource(LL_RCC_SPI3_CLKSOURCE);
  if (srcclk == LL_RCC_SPI3_CLKSOURCE_PCLK1)
  {
    frequency = HAL_RCC_GetPCLK1Freq();
  }
  else if ((srcclk == LL_RCC_SPI3_CLKSOURCE_PSIK) && (LL_RCC_PSIK_IsReady() != 0U))
  {
    frequency = (HAL_RCC_GetPSIClockFreq() * 10UL) / RCC_GetDividerValue(LL_RCC_PSIK_GetDivider());
  }
  else if ((srcclk == LL_RCC_SPI3_CLKSOURCE_HSIK) && (LL_RCC_HSIK_IsReady() != 0U))
  {
    frequency = (HSI_VALUE * 10UL) /  RCC_GetDividerValue(LL_RCC_HSIK_GetDivider());
  }
#if defined(AUDIO_CLOCK_VALUE)
  if (srcclk == LL_RCC_SPI3_CLKSOURCE_AUDIOCLK)
  {
    frequency = AUDIO_CLOCK_VALUE;
  }
#endif /* AUDIO_CLOCK_VALUE */
  else
  {
    frequency = 0U;
  }

  return frequency;
}

#endif /* SPI3 */
#if defined(FDCAN1)

/**
  * @brief  Return the peripheral clock frequency for FDCAN
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator not ready)
  * @note   The FDCAN clock is common for all FDCAN instances
  */
uint32_t HAL_RCC_FDCAN_GetKernelClkFreq(void)
{
  uint32_t frequency = 0U;
  uint32_t srcclk = LL_RCC_GetFDCANClockSource(LL_RCC_FDCAN_CLKSOURCE);

  if (srcclk == LL_RCC_FDCAN_CLKSOURCE_PCLK1)
  {
    frequency = HAL_RCC_GetPCLK1Freq();
  }
  else if ((LL_RCC_PSIS_IsReady() != 0U) && (srcclk == LL_RCC_FDCAN_CLKSOURCE_PSIS))
  {
    frequency = HAL_RCC_GetPSIClockFreq();
  }
  else if ((LL_RCC_PSIK_IsReady() != 0U) && (srcclk == LL_RCC_FDCAN_CLKSOURCE_PSIK))
  {
    frequency = (HAL_RCC_GetPSIClockFreq() * 10UL) / RCC_GetDividerValue(LL_RCC_PSIK_GetDivider());
  }
#if defined(HSE_VALUE)
  else if ((LL_RCC_HSE_IsReady() != 0U) && (srcclk == LL_RCC_FDCAN_CLKSOURCE_HSE))
  {
    frequency = HSE_VALUE;
  }
#endif /* HSE_VALUE */
  return frequency;
}
#endif /* FDCAN1 */

/**
  * @brief  Return the peripheral clock frequency for LPTIM.
  * @param  lptimx LPTIM instance
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator not ready)
  */
uint32_t HAL_RCC_LPTIM_GetKernelClkFreq(const LPTIM_TypeDef *lptimx)
{
  uint32_t frequency;

  if (lptimx == LPTIM1)
  {
    frequency = HAL_RCC_LPTIM1_GetKernelClkFreq();
  }
  else
  {
    frequency = 0U;
  }
  return frequency;
}

/** @brief  Return the peripheral clock frequency for TIM.
  * @param  timx TIM instance.
  * @retval uint32_t Frequency in Hz.
  * @retval 0        Frequency not calculated (Oscillator not ready)
  */
uint32_t  HAL_RCC_TIM_GetKernelClkFreq(const TIM_TypeDef *timx)
{
  uint32_t frequency;

  if ((IS_TIM_APB1_INSTANCE(timx) != 0U) || (IS_TIM_APB2_INSTANCE(timx) != 0U))
  {
    frequency = HAL_RCC_GetHCLKFreq();
  }
  else
  {
    frequency = 0U;
  }

  return frequency;
}

/**
  * @brief  Return the peripheral clock frequency for I2C/SMBUS.
  * @param  i2cx I2C instance
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator not ready)
  */
uint32_t HAL_RCC_I2C_GetKernelClkFreq(const I2C_TypeDef *i2cx)
{
  uint32_t frequency;

  if (i2cx == I2C1)
  {
    frequency = HAL_RCC_I2C1_GetKernelClkFreq();
  }
#if defined(I2C2)
  else if (i2cx == I2C2)
  {
    frequency = HAL_RCC_I2C2_GetKernelClkFreq();
  }
#endif /* I2C2 */
  else
  {
    frequency = 0U;
  }
  return frequency;
}

/**
  * @brief  Return the peripheral clock frequency for I2C1
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator not ready)
  */
uint32_t HAL_RCC_I2C1_GetKernelClkFreq(void)
{
  uint32_t frequency = 0U;
  uint32_t srcclk = LL_RCC_GetI2CClockSource(LL_RCC_I2C1_CLKSOURCE);

  if (srcclk == LL_RCC_I2C1_CLKSOURCE_PCLK1)
  {
    frequency = HAL_RCC_GetPCLK1Freq();
  }
  else if ((LL_RCC_PSIK_IsReady() != 0U) && (srcclk == LL_RCC_I2C1_CLKSOURCE_PSIK))
  {
    frequency = (HAL_RCC_GetPSIClockFreq() * 10UL) / RCC_GetDividerValue(LL_RCC_PSIK_GetDivider());
  }
  else if ((LL_RCC_HSIK_IsReady() != 0U) && (srcclk == LL_RCC_I2C1_CLKSOURCE_HSIK))
  {
    frequency = (HSI_VALUE * 10UL) /  RCC_GetDividerValue(LL_RCC_HSIK_GetDivider());
  }
  return frequency;
}

#if defined(I2C2)
/**
  * @brief  Return the peripheral clock frequency for I2C2
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator not ready)
  */
uint32_t HAL_RCC_I2C2_GetKernelClkFreq(void)
{
  uint32_t frequency = 0U;
  uint32_t srcclk = LL_RCC_GetI2CClockSource(LL_RCC_I2C2_CLKSOURCE);

  if (srcclk == LL_RCC_I2C2_CLKSOURCE_PCLK1)
  {
    frequency = HAL_RCC_GetPCLK1Freq();
  }
  else if ((LL_RCC_PSIK_IsReady() != 0U) && (srcclk == LL_RCC_I2C2_CLKSOURCE_PSIK))
  {
    frequency = (HAL_RCC_GetPSIClockFreq() * 10UL) / RCC_GetDividerValue(LL_RCC_PSIK_GetDivider());
  }
  else if ((LL_RCC_HSIK_IsReady() != 0U) && (srcclk == LL_RCC_I2C2_CLKSOURCE_HSIK))
  {
    frequency = (HSI_VALUE * 10UL) /  RCC_GetDividerValue(LL_RCC_HSIK_GetDivider());
  }

  return frequency;
}

#endif /* I2C2 */
/**
  * @brief  Return the peripheral clock frequency for I3C
  * @param  i3cx I3C instance
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator not ready)
  */
uint32_t  HAL_RCC_I3C_GetKernelClkFreq(const I3C_TypeDef *i3cx)
{
  uint32_t frequency;

  if (i3cx == I3C1)
  {
    frequency = HAL_RCC_I3C1_GetKernelClkFreq();
  }
  else
  {
    frequency = 0U;
  }

  return frequency;
}


/**
  * @brief  Return the peripheral clock frequency for I3C1
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator not ready)
  */
uint32_t HAL_RCC_I3C1_GetKernelClkFreq(void)
{
  uint32_t frequency = 0U;
  uint32_t srcclk = LL_RCC_GetI3CClockSource(LL_RCC_I3C1_CLKSOURCE);

  if (srcclk == LL_RCC_I3C1_CLKSOURCE_PCLK1)
  {
    frequency = HAL_RCC_GetPCLK1Freq();
  }
  else if ((LL_RCC_PSIK_IsReady() != 0U) && (srcclk == LL_RCC_I3C1_CLKSOURCE_PSIK))
  {
    frequency = (HAL_RCC_GetPSIClockFreq() * 10UL) / RCC_GetDividerValue(LL_RCC_PSIK_GetDivider());
  }
  else if ((LL_RCC_HSIK_IsReady() != 0U) && (srcclk == LL_RCC_I3C1_CLKSOURCE_HSIK))
  {
    frequency = (HSI_VALUE * 10UL) /  RCC_GetDividerValue(LL_RCC_HSIK_GetDivider());
  }
  return frequency;
}

/**
  * @brief  Return the peripheral clock frequency for ADCDAC
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator not ready)
  */
uint32_t HAL_RCC_ADCDAC_GetKernelClkFreq(void)
{
  uint32_t frequency = 0U;
  uint32_t srcclk = LL_RCC_GetADCDACClockSource(LL_RCC_ADCDAC_CLKSOURCE);

  if (srcclk == LL_RCC_ADCDAC_CLKSOURCE_HCLK)
  {
    frequency = HAL_RCC_GetHCLKFreq();
  }
  else if ((LL_RCC_PSIS_IsReady() != 0U) && (srcclk == LL_RCC_ADCDAC_CLKSOURCE_PSIS))
  {
    frequency = HAL_RCC_GetPSIClockFreq();
  }
  else if ((LL_RCC_PSIK_IsReady() != 0U) && (srcclk == LL_RCC_ADCDAC_CLKSOURCE_PSIK))
  {
    frequency = (HAL_RCC_GetPSIClockFreq() * 10UL) / RCC_GetDividerValue(LL_RCC_PSIK_GetDivider());
  }
  else if ((LL_RCC_HSIK_IsReady() != 0U) && (srcclk == LL_RCC_ADCDAC_CLKSOURCE_HSIK))
  {
    frequency = (HSI_VALUE * 10UL) /  RCC_GetDividerValue(LL_RCC_HSIK_GetDivider());
  }
  frequency = frequency / RCC_GET_ADC_DIVIDER();

  return frequency;
}

/**
  * @brief  Return the peripheral clock frequency for DAC
  * @param  dacx DAC instance
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator not ready)
  */
uint32_t HAL_RCC_DAC_GetKernelClkFreq(const DAC_TypeDef *dacx)
{
  STM32_UNUSED(dacx);

  return HAL_RCC_ADCDAC_GetKernelClkFreq();
}

/**
  * @brief  Return the peripheral clock frequency for ADC
  * @param  adcx ADC instance
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator not ready)
  */
uint32_t HAL_RCC_ADC_GetKernelClkFreq(const ADC_TypeDef *adcx)
{
  STM32_UNUSED(adcx);

  return HAL_RCC_ADCDAC_GetKernelClkFreq();
}

/**
  * @brief  Return the peripheral clock frequency for DAC1
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator not ready)
  */
uint32_t HAL_RCC_DAC1_GetSampleHoldClkFreq(void)
{
  uint32_t frequency = 0U;
  uint32_t srcclk = LL_RCC_GetDAC1ClockSource(LL_RCC_DAC1_CLKSOURCE);

  /* Check if LSI is ready and if DAC1 clock selection is LSI */
  if ((LL_RCC_LSI_IsReady() != 0U) && (srcclk == LL_RCC_DAC1SH_CLKSOURCE_LSI))
  {
    frequency = LSI_VALUE;
  }
#if defined(LSE_VALUE)
  /* Check if LSE is ready and if DAC1 clock selection is LSE */
  else
  {
    if ((LL_RCC_LSE_IsReady() != 0U) && (srcclk == LL_RCC_DAC1SH_CLKSOURCE_LSE))
    {
      frequency = LSE_VALUE;
    }
  }
#endif /* LSE_VALUE */

  return frequency;
}

/**
  * @brief  Return the peripheral clock frequency for LPTIM1
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator not ready)
  */
uint32_t HAL_RCC_LPTIM1_GetKernelClkFreq(void)
{
  uint32_t frequency = 0U;
  uint32_t srcclk = LL_RCC_GetLPTIMClockSource(LL_RCC_LPTIM1_CLKSOURCE);

  if (srcclk == LL_RCC_LPTIM1_CLKSOURCE_PCLK3)
  {
    frequency = HAL_RCC_GetPCLK3Freq();
  }
  else if ((LL_RCC_HSIK_IsReady() != 0U) && (srcclk == LL_RCC_LPTIM1_CLKSOURCE_HSIK))
  {
    frequency = (HSI_VALUE * 10UL) /  RCC_GetDividerValue(LL_RCC_HSIK_GetDivider());
  }
  else if ((LL_RCC_LSI_IsReady() != 0U) && (srcclk == LL_RCC_LPTIM1_CLKSOURCE_LSI))
  {
    frequency = LSI_VALUE;
  }
#if defined(LSE_VALUE)
  else if ((LL_RCC_LSE_IsReady() != 0U) && (srcclk == LL_RCC_LPTIM1_CLKSOURCE_LSE))
  {
    frequency = LSE_VALUE;
  }
#endif /* LSE_VALUE */

  return frequency;
}

#if defined(XSPI1)
/**
  * @brief  Return the peripheral clock frequency for XSPI.
  * @param  xspix XSPI instance
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator not ready)
  */
uint32_t HAL_RCC_XSPI_GetKernelClkFreq(const XSPI_TypeDef *xspix)
{
  uint32_t frequency;

  if (xspix == XSPI1)
  {
    frequency = HAL_RCC_XSPI1_GetKernelClkFreq();
  }
  else
  {
    frequency = 0U;
  }
  return frequency;
}

/**
  * @brief  Return the peripheral clock frequency for XSPI
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator not ready)
  */
uint32_t HAL_RCC_XSPI1_GetKernelClkFreq(void)
{
  uint32_t frequency = 0U;
  uint32_t srcclk = LL_RCC_GetXSPIClockSource(LL_RCC_XSPI1_CLKSOURCE);

  if (srcclk == LL_RCC_XSPI1_CLKSOURCE_HCLK)
  {
    frequency = HAL_RCC_GetHCLKFreq();
  }
  else if ((LL_RCC_PSIK_IsReady() != 0U) && (srcclk == LL_RCC_XSPI1_CLKSOURCE_PSIK))
  {
    frequency = (HAL_RCC_GetPSIClockFreq() * 10UL) / RCC_GetDividerValue(LL_RCC_PSIK_GetDivider());
  }
  else if ((LL_RCC_HSIK_IsReady() != 0U) && (srcclk == LL_RCC_XSPI1_CLKSOURCE_HSIK))
  {
    frequency = (HSI_VALUE * 10UL) /  RCC_GetDividerValue(LL_RCC_HSIK_GetDivider());
  }

  return frequency;
}

#endif /* XSPI1 */
#if defined(ETH)
/**
  * @brief  Return the peripheral clock frequency for ETH PTP
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator not ready)
  */
uint32_t HAL_RCC_ETHPTP_GetKernelClkFreq(void)
{
  uint32_t frequency = 0U;
  uint32_t srcclk = LL_RCC_GetETHClockSource(LL_RCC_ETHPTP_CLKSOURCE);

  if (srcclk == LL_RCC_ETHPTP_CLKSOURCE_HCLK)
  {
    frequency = HAL_RCC_GetHCLKFreq();
  }
  else if ((LL_RCC_PSIS_IsReady() != 0U) && (srcclk == LL_RCC_ETHPTP_CLKSOURCE_PSIS))
  {
    frequency = HAL_RCC_GetPSIClockFreq();
  }
  else if ((LL_RCC_PSIK_IsReady() != 0U) && (srcclk == LL_RCC_ETHPTP_CLKSOURCE_PSIK))
  {
    frequency = (HAL_RCC_GetPSIClockFreq() * 10UL) / RCC_GetDividerValue(LL_RCC_PSIK_GetDivider());
  }

  frequency = frequency / RCC_GET_ETHPTP_DIVIDER();

  return frequency;
}

/**
  * @brief  Return the peripheral clock frequency for ETH
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator not ready)
  */
uint32_t HAL_RCC_ETH_GetKernelClkFreq(void)
{
  uint32_t frequency = 0U;
  uint32_t srcclk = LL_RCC_GetETHClockSource(LL_RCC_ETH_CLKSOURCE);

  if ((LL_RCC_PSIS_IsReady() != 0U) && (srcclk == LL_RCC_ETH_CLKSOURCE_PSIS))
  {
    frequency = HAL_RCC_GetPSIClockFreq();
  }
  else if ((LL_RCC_PSIK_IsReady() != 0U) && (srcclk == LL_RCC_ETH_CLKSOURCE_PSIK))
  {
    frequency = (HAL_RCC_GetPSIClockFreq() * 10UL) / RCC_GetDividerValue(LL_RCC_PSIK_GetDivider());
  }
#if defined(HSE_VALUE)
  else if ((LL_RCC_HSE_IsReady() != 0U) && (srcclk == LL_RCC_ETH_CLKSOURCE_HSE))
  {
    frequency = HSE_VALUE;
  }
#endif /* HSE_VALUE */

  frequency = frequency / RCC_GET_ETH_DIVIDER();

  return frequency;
}
#endif /* ETH */

/**
  * @brief  Return the peripheral clock frequency for RTC
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator not ready)
  */
uint32_t HAL_RCC_RTC_GetKernelClkFreq(void)
{
  uint32_t frequency;
  uint32_t srcclk = LL_RCC_GetRTCClockSource();
  uint32_t rtccr_temp = LL_RCC_READ_REG(RTCCR);

  /* Check if LSI is ready and if RTC clock selection is LSI */
  if ((IS_BIT_SET(rtccr_temp, RCC_RTCCR_LSIRDY)) && (srcclk == LL_RCC_RTC_CLKSOURCE_LSI))
  {
    frequency = LSI_VALUE;
  }
#if defined(LSE_VALUE)
  /* Check if LSE is ready and if RTC clock selection is LSE */
  else if ((IS_BIT_SET(rtccr_temp, RCC_RTCCR_LSERDY)) && (srcclk == LL_RCC_RTC_CLKSOURCE_LSE))
  {
    frequency = LSE_VALUE;
  }
#endif /* LSE_VALUE */
#if defined(HSE_VALUE)
  /* Check if HSE is ready  and if RTC clock selection is HSE*/
  else if ((LL_RCC_HSE_IsReady() != 0U) && (srcclk == LL_RCC_RTC_CLKSOURCE_HSE))
  {
    uint32_t Prescaler = LL_RCC_GetRTC_HSEPrescaler();
    if (Prescaler >= LL_RCC_RTC_HSE_DIV_2)
    {
      frequency = HSE_VALUE / Prescaler;
    }
    else
    {
      frequency = 0U;
    }
  }
#endif /* HSE_VALUE */
  /* Clock not enabled for RTC*/
  else
  {
    frequency = 0U;
  }
  return frequency;
}

/**
  * @brief  Get the Systick external clock frequency
  * @retval uint32_t Frequency in Hz
  */
uint32_t HAL_RCC_GetSysTickExternalClkFreq(void)
{
  uint32_t frequency = 0;
  uint32_t srcclk = LL_RCC_GetSystickClockSource();

  switch (srcclk)
  {
    case LL_RCC_SYSTICK_CLKSOURCE_HCLKDIV8:
      frequency = (HAL_RCC_GetSYSCLKFreq() >> 3U);
      break;

    case LL_RCC_SYSTICK_CLKSOURCE_LSI:
      frequency = LSI_VALUE;
      break;

#if defined(LSE_VALUE)
    case LL_RCC_SYSTICK_CLKSOURCE_LSE:
      frequency = LSE_VALUE;
      break;
#endif /* LSE_VALUE */

    default:
      break;
  }

  return frequency;
}
/**
  * @}
  */

/**
  * @}
  */
/* Private function prototypes -----------------------------------------------*/
/** @addtogroup RCC_Private_Functions
  * @{
  */
/** @brief  Wait for clock timeout
  * @param  p_timeout_cb Callback on the timeout function
  * @param  timeout      Timeout value
  * @param  status       Status to be checked
  * @retval HAL_OK       Not timeout detected
  * @retval HAL_ERROR    Timeout detected during clock activation or deactivation
  */
static hal_status_t RCC_WaitForTimeout(const rcc_cb_timeout_t p_timeout_cb, uint32_t timeout, uint32_t status)
{
  uint32_t tickstart;
  hal_status_t hal_status = HAL_OK;
  tickstart = HAL_GetTick();

  while (p_timeout_cb() != status)
  {
    if ((HAL_GetTick() - tickstart) > timeout)
    {
      /* New check to avoid false timeout detection in case of preemption */
      if (p_timeout_cb() != status)
      {
        hal_status = HAL_ERROR;
        break;
      }
    }
  }

  return hal_status;
}

/** @brief  Get the value for a divider factor 10
  * @param  divider field
  * @retval divider value factor 10
  */
static uint32_t RCC_GetDividerValue(uint32_t divider)
{
  uint32_t value;

  if ((divider == LL_RCC_PSIK_DIV_1) || (divider == LL_RCC_HSIK_DIV_1))
  {
    value = 10UL;
  }
  else if ((divider == LL_RCC_PSIK_DIV_1_5) || (divider == LL_RCC_HSIK_DIV_1_5))
  {
    value = 15UL;
  }
  else if ((divider == LL_RCC_PSIK_DIV_2) || (divider == LL_RCC_HSIK_DIV_2))
  {
    value = 20UL;
  }
  else if ((divider == LL_RCC_PSIK_DIV_2_5) || (divider == LL_RCC_HSIK_DIV_2_5))
  {
    value = 25UL;
  }
  else if ((divider == LL_RCC_PSIK_DIV_3) || (divider == LL_RCC_HSIK_DIV_3))
  {
    value = 30UL;
  }
  else if ((divider == LL_RCC_PSIK_DIV_3_5) || (divider == LL_RCC_HSIK_DIV_3_5))
  {
    value = 35UL;
  }
  else if ((divider == LL_RCC_PSIK_DIV_4) || (divider == LL_RCC_HSIK_DIV_4))
  {
    value = 40UL;
  }
  else if ((divider == LL_RCC_PSIK_DIV_4_5) || (divider == LL_RCC_HSIK_DIV_4_5))
  {
    value = 45UL;
  }
  else if ((divider == LL_RCC_PSIK_DIV_5) || (divider == LL_RCC_HSIK_DIV_5))
  {
    value = 50UL;
  }
  else if ((divider == LL_RCC_PSIK_DIV_5_5) || (divider == LL_RCC_HSIK_DIV_5_5))
  {
    value = 55UL;
  }
  else if ((divider == LL_RCC_PSIK_DIV_6) || (divider == LL_RCC_HSIK_DIV_6))
  {
    value = 60UL;
  }
  else if ((divider == LL_RCC_PSIK_DIV_6_5) || (divider == LL_RCC_HSIK_DIV_6_5))
  {
    value = 65UL;
  }
  else if ((divider == LL_RCC_PSIK_DIV_7) || (divider == LL_RCC_HSIK_DIV_7))
  {
    value = 70UL;
  }
  else if ((divider == LL_RCC_PSIK_DIV_7_5) || (divider == LL_RCC_HSIK_DIV_7_5))
  {
    value = 75UL;
  }
  else
  {
    value = 80UL;
  }
  return value;
}
/**
  * @}
  */ /* RCC_Private_Functions */

#endif /* USE_HAL_RCC_MODULE */
/**
  * @}
  */ /* RCC */

/**
  * @}
  */ /* STM32C5XX_HAL_Driver */
