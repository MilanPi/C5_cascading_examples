/**
  ******************************************************************************
  * @file    stm32g5xx_ll_rcc.h
  * @author  GPM Application Team
  * @brief   Header file of RCC LL module.
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
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef STM32C5XX_LL_RCC_H
#define STM32C5XX_LL_RCC_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32c5xx.h"

/** @addtogroup STM32C5xx_LL_Driver
  * @{
  */

#if defined(RCC)

/** @defgroup RCC_LL RCC
  * @{
  */

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/** @defgroup RCC_LL_Private_Constants RCC Private Constants
  * @{
  */
/* Constants for LL_CLKSOURCE_xxx() macros
   31           24            16           8             0
   --------------------------------------------------------
   | Register    | Bit         |  Bit       | ClkSource   |
   | Offset      | Position    | Mask       | Config      |
   --------------------------------------------------------*/

/* Clock source register offset Vs CCIPR1 register */
#define RCC_OFFSET_CCIPR1       0x00U
#define RCC_OFFSET_CCIPR2       0x04U
#define RCC_OFFSET_CCIPR3       0x08U

#define LL_RCC_CONFIG_SHIFT 0U
#define LL_RCC_MASK_SHIFT   8U
#define LL_RCC_POS_SHIFT    16U
#define LL_RCC_REG_SHIFT    24U

/**
  * @}
  */ /* End of RCC_LL_Private_Constants */

/* Private macros ------------------------------------------------------------*/
/** @defgroup RCC_LL_Private_Macros RCC Private Macros
  * @{
  */
#if !defined(UNUSED)
#define UNUSED(x) ((void)(x))
#endif /* UNUSED */

#define LL_CLKSOURCE_POS(__CLKSOURCE__)     (((__CLKSOURCE__) >> LL_RCC_POS_SHIFT) & 0x1FUL)
#define LL_CLKSOURCE_MASK(__CLKSOURCE__)    ((((__CLKSOURCE__) >> LL_RCC_MASK_SHIFT) & 0xFFUL) << \
                                             LL_CLKSOURCE_POS(__CLKSOURCE__))
#define LL_CLKSOURCE_CONFIG(__CLKSOURCE__)  ((((__CLKSOURCE__) >> LL_RCC_CONFIG_SHIFT) & 0xFFUL) << \
                                             LL_CLKSOURCE_POS(__CLKSOURCE__))
#define LL_CLKSOURCE_REG(__CLKSOURCE__)     (((__CLKSOURCE__) >> LL_RCC_REG_SHIFT) & 0xFFUL)

#define LL_CLKSOURCE(__REG__, __POS__, __MSK__, __CLK__) ((uint32_t)((((__MSK__) >> (__POS__)) << LL_RCC_MASK_SHIFT) | \
                                                                     (( __POS__              ) << LL_RCC_POS_SHIFT)  | \
                                                                     (( __REG__              ) << LL_RCC_REG_SHIFT)  | \
                                                                     (((__CLK__) >> (__POS__)) << LL_RCC_CONFIG_SHIFT)))
/**
  * @}
  */ /* RCC_LL_Private_Macros */

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/** @defgroup RCC_LL_Exported_Constants RCC Exported Constants
  * @{
  */

/** @defgroup RCC_LL_EC_LSE LSE oscillator driving capability
  * @{
  */
#define LL_RCC_LSEDRIVE_LOW               0U                       /*!< Xtal mode lower driving capability */
#define LL_RCC_LSEDRIVE_MEDIUMLOW         RCC_RTCCR_LSEDRV_0       /*!< Xtal mode medium low driving capability */
#define LL_RCC_LSEDRIVE_MEDIUMHIGH        RCC_RTCCR_LSEDRV_1       /*!< Xtal mode medium high driving capability */
#define LL_RCC_LSEDRIVE_HIGH              RCC_RTCCR_LSEDRV         /*!< Xtal mode higher driving capability */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_LSE LSE oscillator driving capability
  * @{
  */
#define LL_RCC_LSE_ANALOG_MODE            0U                       /*!< ANALOG  clock used as LSE external clock source  */
#define LL_RCC_LSE_DIGITAL_MODE           RCC_RTCCR_LSEEXT         /*!< DIGITAL clock used as LSE external clock source */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_HSEEXT  EXTERNAL HSE Mode
  * @{
  */
#define LL_RCC_HSE_ANALOG_MODE            0U                       /*!< HSE clock used as ANALOG clock source */
#define LL_RCC_HSE_DIGITAL_MODE           RCC_CR1_HSEEXT           /*!< HSE clock used as DIGITAL clock source */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_LSCO_CLKSOURCE  LSCO Selection
  * @{
  */
#define LL_RCC_LSCO_CLKSOURCE_LSI         0U                       /*!< LSI selection for low speed clock  */
#define LL_RCC_LSCO_CLKSOURCE_LSE         RCC_RTCCR_LSCOSEL        /*!< LSE selection for low speed clock  */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_HSIK HSI kernel clock out divider factor
  * @{
  */
#define LL_RCC_HSIK_DIV_1                 RCC_CR2_HSIKDIV_0                                           /*!< HSI kernel clock divided by 1 */
#define LL_RCC_HSIK_DIV_1_5               RCC_CR2_HSIKDIV_1                                           /*!< HSI kernel clock divided by 1.5 */
#define LL_RCC_HSIK_DIV_2                 (RCC_CR2_HSIKDIV_1 | RCC_CR2_HSIKDIV_0)                     /*!< HSI kernel clock divided by 2 */
#define LL_RCC_HSIK_DIV_2_5               RCC_CR2_HSIKDIV_2                                           /*!< HSI kernel clock divided by 2.5 */
#define LL_RCC_HSIK_DIV_3                 (RCC_CR2_HSIKDIV_2 | RCC_CR2_HSIKDIV_0)                     /*!< HSI kernel clock divided by 3 */
#define LL_RCC_HSIK_DIV_3_5               (RCC_CR2_HSIKDIV_2 | RCC_CR2_HSIKDIV_1)                     /*!< HSI kernel clock divided by 3.5 */
#define LL_RCC_HSIK_DIV_4                 (RCC_CR2_HSIKDIV_2 | RCC_CR2_HSIKDIV_1 | RCC_CR2_HSIKDIV_0) /*!< HSI kernel clock divided by 4 */
#define LL_RCC_HSIK_DIV_4_5               RCC_CR2_HSIKDIV_3                                           /*!< HSI kernel clock divided by 4.5 */
#define LL_RCC_HSIK_DIV_5                 (RCC_CR2_HSIKDIV_3 | RCC_CR2_HSIKDIV_0)                     /*!< HSI kernel clock divided by 5 */
#define LL_RCC_HSIK_DIV_5_5               (RCC_CR2_HSIKDIV_3 | RCC_CR2_HSIKDIV_1)                     /*!< HSI kernel clock divided by 5.5 */
#define LL_RCC_HSIK_DIV_6                 (RCC_CR2_HSIKDIV_3 | RCC_CR2_HSIKDIV_1 | RCC_CR2_HSIKDIV_0) /*!< HSI kernel clock divided by 6 */
#define LL_RCC_HSIK_DIV_6_5               (RCC_CR2_HSIKDIV_3 | RCC_CR2_HSIKDIV_2)                     /*!< HSI kernel clock divided by 6.5 */
#define LL_RCC_HSIK_DIV_7                 (RCC_CR2_HSIKDIV_3 | RCC_CR2_HSIKDIV_2 | RCC_CR2_HSIKDIV_0) /*!< HSI kernel clock divided by 7 */
#define LL_RCC_HSIK_DIV_7_5               (RCC_CR2_HSIKDIV_3 | RCC_CR2_HSIKDIV_2 | RCC_CR2_HSIKDIV_1) /*!< HSI kernel clock divided by 7.5 */
#define LL_RCC_HSIK_DIV_8                 RCC_CR2_HSIKDIV                                             /*!< HSI kernel clock divided by 8 */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_PSIK PSI kernel clock out divider factor
  * @{
  */
#define LL_RCC_PSIK_DIV_1                 RCC_CR2_PSIKDIV_0                                           /*!< PSI kernel clock divided by 1 */
#define LL_RCC_PSIK_DIV_1_5               RCC_CR2_PSIKDIV_1                                           /*!< PSI kernel clock divided by 1.5 */
#define LL_RCC_PSIK_DIV_2                 (RCC_CR2_PSIKDIV_1 | RCC_CR2_PSIKDIV_0)                     /*!< PSI kernel clock divided by 2 */
#define LL_RCC_PSIK_DIV_2_5               RCC_CR2_PSIKDIV_2                                           /*!< PSI kernel clock divided by 2.5 */
#define LL_RCC_PSIK_DIV_3                 (RCC_CR2_PSIKDIV_2 | RCC_CR2_PSIKDIV_0)                     /*!< PSI kernel clock divided by 3 */
#define LL_RCC_PSIK_DIV_3_5               (RCC_CR2_PSIKDIV_2 | RCC_CR2_PSIKDIV_1)                     /*!< PSI kernel clock divided by 3.5 */
#define LL_RCC_PSIK_DIV_4                 (RCC_CR2_PSIKDIV_2 | RCC_CR2_PSIKDIV_1 | RCC_CR2_PSIKDIV_0) /*!< PSI kernel clock divided by 4 */
#define LL_RCC_PSIK_DIV_4_5               RCC_CR2_PSIKDIV_3                                           /*!< PSI kernel clock divided by 4.5 */
#define LL_RCC_PSIK_DIV_5                 (RCC_CR2_PSIKDIV_3 | RCC_CR2_PSIKDIV_0)                     /*!< PSI kernel clock divided by 5 */
#define LL_RCC_PSIK_DIV_5_5               (RCC_CR2_PSIKDIV_3 | RCC_CR2_PSIKDIV_1)                     /*!< PSI kernel clock divided by 5.5 */
#define LL_RCC_PSIK_DIV_6                 (RCC_CR2_PSIKDIV_3 | RCC_CR2_PSIKDIV_1 | RCC_CR2_PSIKDIV_0) /*!< PSI kernel clock divided by 6 */
#define LL_RCC_PSIK_DIV_6_5               (RCC_CR2_PSIKDIV_3 | RCC_CR2_PSIKDIV_2)                     /*!< PSI kernel clock divided by 6.5 */
#define LL_RCC_PSIK_DIV_7                 (RCC_CR2_PSIKDIV_3 | RCC_CR2_PSIKDIV_2 | RCC_CR2_PSIKDIV_0) /*!< PSI kernel clock divided by 7 */
#define LL_RCC_PSIK_DIV_7_5               (RCC_CR2_PSIKDIV_3 | RCC_CR2_PSIKDIV_2 | RCC_CR2_PSIKDIV_1) /*!< PSI kernel clock divided by 7.5 */
#define LL_RCC_PSIK_DIV_8                 RCC_CR2_PSIKDIV                                             /*!< PSI kernel clock divided by 8 */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_PSIFREQ PSI target frequency configuration
  * @{
  */
#define LL_RCC_PSIFREQ_100                0U                       /*!< PSI output frequency is 100 MHz */
#define LL_RCC_PSIFREQ_144                RCC_CR2_PSIFREQ_0        /*!< PSI output frequency is 144 MHz */
#define LL_RCC_PSIFREQ_160                RCC_CR2_PSIFREQ_1        /*!< PSI output frequency is 160 MHz */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_PSIREF PSI ref clock frequency selection
  * @{
  */
#define LL_RCC_PSIREF_32K768              0U                                      /*!< PSI reference clock input is 32768 Hz */
#define LL_RCC_PSIREF_8M                  RCC_CR2_PSIREF_0                        /*!< PSI reference clock input is 8 MHz */
#define LL_RCC_PSIREF_16M                 RCC_CR2_PSIREF_1                        /*!< PSI reference clock input is 16 MHz */
#define LL_RCC_PSIREF_24M                 (RCC_CR2_PSIREF_1 | RCC_CR2_PSIREF_0)   /*!< PSI reference clock input is 24 MHz */
#define LL_RCC_PSIREF_25M                 RCC_CR2_PSIREF_2                        /*!< PSI reference clock input is 25 MHz */
#define LL_RCC_PSIREF_32M                 (RCC_CR2_PSIREF_2 | RCC_CR2_PSIREF_0)   /*!< PSI reference clock input is 32 MHz */
#define LL_RCC_PSIREF_48M                 (RCC_CR2_PSIREF_2  | RCC_CR2_PSIREF_1)  /*!< PSI reference clock input is 48 MHz */
#define LL_RCC_PSIREF_50M                 RCC_CR2_PSIREF                          /*!< PSI reference clock input is 50 MHz */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_PSIREFSRC PSI ref clock source selection
  * @{
  */
#define LL_RCC_PSISOURCE_HSE              0U                       /*!< PSI source is HSE */
#define LL_RCC_PSISOURCE_LSE              RCC_CR2_PSIREFSRC_0      /*!< PSI source is LSE */
#define LL_RCC_PSISOURCE_HSIDIV18         RCC_CR2_PSIREFSRC_1      /*!< PSI source is HSI divided by 18 */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_SYS_CLKSOURCE  System clock switch
  * @{
  */
#define LL_RCC_SYS_CLKSOURCE_HSIDIV3      0U                       /*!< HSI DIV3 clock selection as system clock */
#define LL_RCC_SYS_CLKSOURCE_HSIS         RCC_CFGR1_SW_0           /*!< HSIS clock selection as system clock */
#define LL_RCC_SYS_CLKSOURCE_HSE          RCC_CFGR1_SW_1           /*!< HSE oscillator selection as system clock */
#define LL_RCC_SYS_CLKSOURCE_PSIS         RCC_CFGR1_SW             /*!< PSIS clock selection as system clock */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_SYS_CLKSOURCE_STATUS  System clock switch status
  * @{
  */
#define LL_RCC_SYS_CLKSOURCE_STATUS_HSIDIV3 0U                     /*!< HSI DIV3 clock used as system clock */
#define LL_RCC_SYS_CLKSOURCE_STATUS_HSIS    RCC_CFGR1_SWS_0        /*!< HSIS clock used as system clock */
#define LL_RCC_SYS_CLKSOURCE_STATUS_HSE     RCC_CFGR1_SWS_1        /*!< HSE oscillator used as system clock */
#define LL_RCC_SYS_CLKSOURCE_STATUS_PSIS    RCC_CFGR1_SWS          /*!< PSIS clock used as system clock */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_SYSCLK_DIV  AHB prescaler
  * @{
  */
#define LL_RCC_HCLK_PRESCALER_1       0U                                                           /*!< SYSCLK not divided */
#define LL_RCC_HCLK_PRESCALER_2       RCC_CFGR2_HPRE_3                                             /*!< SYSCLK divided by 2 */
#define LL_RCC_HCLK_PRESCALER_4       (RCC_CFGR2_HPRE_3 | RCC_CFGR2_HPRE_0)                        /*!< SYSCLK divided by 4 */
#define LL_RCC_HCLK_PRESCALER_8       (RCC_CFGR2_HPRE_3 | RCC_CFGR2_HPRE_1)                        /*!< SYSCLK divided by 8 */
#define LL_RCC_HCLK_PRESCALER_16      (RCC_CFGR2_HPRE_3 | RCC_CFGR2_HPRE_1 | RCC_CFGR2_HPRE_0)     /*!< SYSCLK divided by 16 */
#define LL_RCC_HCLK_PRESCALER_64      (RCC_CFGR2_HPRE_3 | RCC_CFGR2_HPRE_2)                        /*!< SYSCLK divided by 64 */
#define LL_RCC_HCLK_PRESCALER_128     (RCC_CFGR2_HPRE_3 | RCC_CFGR2_HPRE_2 | RCC_CFGR2_HPRE_0)     /*!< SYSCLK divided by 128 */
#define LL_RCC_HCLK_PRESCALER_256     (RCC_CFGR2_HPRE_3 | RCC_CFGR2_HPRE_2 | RCC_CFGR2_HPRE_1)     /*!< SYSCLK divided by 256 */
#define LL_RCC_HCLK_PRESCALER_512     RCC_CFGR2_HPRE                                               /*!< SYSCLK divided by 512 */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_SYSTICK_CLKSOURCE  SYSTICK clock source selection
  * @{
  */
#define LL_RCC_SYSTICK_CLKSOURCE_HCLKDIV8    0U                       /*!< HCLKDIV8 clock used as SYSTICK clock source */
#define LL_RCC_SYSTICK_CLKSOURCE_LSI         RCC_CCIPR2_SYSTICKSEL_0  /*!< LSI clock used as SYSTICK clock source */
#define LL_RCC_SYSTICK_CLKSOURCE_LSE         RCC_CCIPR2_SYSTICKSEL_1  /*!< LSE clock used as SYSTICK clock source */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_APB1_DIV  APB low-speed prescaler (APB1)
  * @{
  */
#define LL_RCC_APB1_PRESCALER_1            0U                                                          /*!< HCLK not divided */
#define LL_RCC_APB1_PRESCALER_2            RCC_CFGR2_PPRE1_2                                           /*!< HCLK divided by 2 */
#define LL_RCC_APB1_PRESCALER_4            (RCC_CFGR2_PPRE1_2 | RCC_CFGR2_PPRE1_0)                     /*!< HCLK divided by 4 */
#define LL_RCC_APB1_PRESCALER_8            (RCC_CFGR2_PPRE1_2 | RCC_CFGR2_PPRE1_1)                     /*!< HCLK divided by 8 */
#define LL_RCC_APB1_PRESCALER_16           (RCC_CFGR2_PPRE1_2 | RCC_CFGR2_PPRE1_1 | RCC_CFGR2_PPRE1_0) /*!< HCLK divided by 16 */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_APB2_DIV  APB high-speed prescaler (APB2)
  * @{
  */
#define LL_RCC_APB2_PRESCALER_1            0U                                                          /*!< HCLK not divided */
#define LL_RCC_APB2_PRESCALER_2            RCC_CFGR2_PPRE2_2                                           /*!< HCLK divided by 2 */
#define LL_RCC_APB2_PRESCALER_4            (RCC_CFGR2_PPRE2_2 | RCC_CFGR2_PPRE2_0)                     /*!< HCLK divided by 4 */
#define LL_RCC_APB2_PRESCALER_8            (RCC_CFGR2_PPRE2_2 | RCC_CFGR2_PPRE2_1)                     /*!< HCLK divided by 8 */
#define LL_RCC_APB2_PRESCALER_16           (RCC_CFGR2_PPRE2_2 | RCC_CFGR2_PPRE2_1 | RCC_CFGR2_PPRE2_0) /*!< HCLK divided by 16 */
/**
  * @}
  */


/** @defgroup RCC_LL_EC_APB3_DIV  APB high-speed prescaler (APB3)
  * @{
  */
#define LL_RCC_APB3_PRESCALER_1            0U                                                          /*!< HCLK not divided */
#define LL_RCC_APB3_PRESCALER_2            RCC_CFGR2_PPRE3_2                                           /*!< HCLK divided by 2 */
#define LL_RCC_APB3_PRESCALER_4            (RCC_CFGR2_PPRE3_2 | RCC_CFGR2_PPRE3_0)                     /*!< HCLK divided by 4 */
#define LL_RCC_APB3_PRESCALER_8            (RCC_CFGR2_PPRE3_2 | RCC_CFGR2_PPRE3_1)                     /*!< HCLK divided by 8 */
#define LL_RCC_APB3_PRESCALER_16           (RCC_CFGR2_PPRE3_2 | RCC_CFGR2_PPRE3_1 | RCC_CFGR2_PPRE3_0) /*!< HCLK divided by 16 */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_STOP_WAKEUPCLOCK  System clock selection after a wakeup from system Stop
  * @{
  */
#define LL_RCC_STOP_WAKEUPCLOCK_HSIDIV3      0U                      /*!< HSIDIV3 selection after wake-up from STOP */
#define LL_RCC_STOP_WAKEUPCLOCK_HSIS         RCC_CFGR1_STOPWUCK      /*!< HSIS selection after wake-up from STOP */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_MCO1SOURCE  MCO1 SOURCE selection
  * @{
  */
#define LL_RCC_MCO1SOURCE_SYSCLK             (uint32_t)((RCC_CFGR1_MCO1SEL>>16U) | 0x00000000U)                                                       /*!< SYSCLK selection as MCO1 source */
#define LL_RCC_MCO1SOURCE_HSE                (uint32_t)((RCC_CFGR1_MCO1SEL>>16U) | RCC_CFGR1_MCO1SEL_0)                                               /*!< HSE selection as MCO1 source */
#define LL_RCC_MCO1SOURCE_LSE                (uint32_t)((RCC_CFGR1_MCO1SEL>>16U) | RCC_CFGR1_MCO1SEL_1)                                               /*!< LSE selection as MCO1 source */
#define LL_RCC_MCO1SOURCE_LSI                (uint32_t)((RCC_CFGR1_MCO1SEL>>16U) | RCC_CFGR1_MCO1SEL_1 | RCC_CFGR1_MCO1SEL_0)                         /*!< LSI selection as MCO1 source */
#define LL_RCC_MCO1SOURCE_PSIK               (uint32_t)((RCC_CFGR1_MCO1SEL>>16U) | RCC_CFGR1_MCO1SEL_2)                                               /*!< PSI kernel clock selection as MCO1 source */
#define LL_RCC_MCO1SOURCE_HSIK               (uint32_t)((RCC_CFGR1_MCO1SEL>>16U) | RCC_CFGR1_MCO1SEL_2 | RCC_CFGR1_MCO1SEL_0)                         /*!< HSI kernel clock selection as MCO1 source */
#define LL_RCC_MCO1SOURCE_PSIS               (uint32_t)((RCC_CFGR1_MCO1SEL>>16U) | RCC_CFGR1_MCO1SEL_2| RCC_CFGR1_MCO1SEL_1)                          /*!< PSIS selection as MCO1 source */
#define LL_RCC_MCO1SOURCE_HSIS               (uint32_t)((RCC_CFGR1_MCO1SEL>>16U) | RCC_CFGR1_MCO1SEL_2 | RCC_CFGR1_MCO1SEL_1 | RCC_CFGR1_MCO1SEL_0 )  /*!< HSIS selection as MCO1 source */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_MCO2SOURCE  MCO2 SOURCE selection
  * @{
  */
#define LL_RCC_MCO2SOURCE_SYSCLK             (uint32_t)((RCC_CFGR1_MCO2SEL>>16U) | 0x00000000U)                                                       /*!< SYSCLK selection as MCO2 source */
#define LL_RCC_MCO2SOURCE_HSE                (uint32_t)((RCC_CFGR1_MCO2SEL>>16U) | RCC_CFGR1_MCO2SEL_0)                                               /*!< HSE selection as MCO2 source */
#define LL_RCC_MCO2SOURCE_LSE                (uint32_t)((RCC_CFGR1_MCO2SEL>>16U) | RCC_CFGR1_MCO2SEL_1)                                               /*!< LSE selection as MCO2 source */
#define LL_RCC_MCO2SOURCE_LSI                (uint32_t)((RCC_CFGR1_MCO2SEL>>16U) | RCC_CFGR1_MCO2SEL_1| RCC_CFGR1_MCO2SEL_0)                          /*!< LSI selection as MCO2 source */
#define LL_RCC_MCO2SOURCE_PSIK               (uint32_t)((RCC_CFGR1_MCO2SEL>>16U) | RCC_CFGR1_MCO2SEL_2)                                               /*!< PSI kernel clock selection as MCO2 source */
#define LL_RCC_MCO2SOURCE_HSIK               (uint32_t)((RCC_CFGR1_MCO2SEL>>16U) | RCC_CFGR1_MCO2SEL_2 | RCC_CFGR1_MCO2SEL_0)                         /*!< HSI kernel clock selection as MCO2 source */
#define LL_RCC_MCO2SOURCE_PSIDIV3            (uint32_t)((RCC_CFGR1_MCO2SEL>>16U) | RCC_CFGR1_MCO2SEL_2 | RCC_CFGR1_MCO2SEL_1)                         /*!< PSI DIV 3 selection as MCO2 source */
#define LL_RCC_MCO2SOURCE_HSIDIV3            (uint32_t)((RCC_CFGR1_MCO2SEL>>16U) | RCC_CFGR1_MCO2SEL_2 | RCC_CFGR1_MCO2SEL_1 | RCC_CFGR1_MCO2SEL_0 )  /*!< HSI DIV 3 selection as MCO2 source */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_MCO1_DIV  MCO1 prescaler
  * @{
  */
#define LL_RCC_MCO1_NO_CLK                   (uint32_t)((RCC_CFGR1_MCO1PRE>>16U) | 0x00000000U)                                                       /*!< MCO1 output disabled, no clock on MCO1 */
#define LL_RCC_MCO1_PRESCALER_1                    (uint32_t)((RCC_CFGR1_MCO1PRE>>16U) | RCC_CFGR1_MCO1PRE_0)                                               /*!< MCO1 not divided */
#define LL_RCC_MCO1_PRESCALER_2                    (uint32_t)((RCC_CFGR1_MCO1PRE>>16U) | RCC_CFGR1_MCO1PRE_1)                                               /*!< MCO1 divided by 2 */
#define LL_RCC_MCO1_PRESCALER_3                    (uint32_t)((RCC_CFGR1_MCO1PRE>>16U) | RCC_CFGR1_MCO1PRE_0 | RCC_CFGR1_MCO1PRE_1)                         /*!< MCO1 divided by 3 */
#define LL_RCC_MCO1_PRESCALER_4                    (uint32_t)((RCC_CFGR1_MCO1PRE>>16U) | RCC_CFGR1_MCO1PRE_2)                                               /*!< MCO1 divided by 4 */
#define LL_RCC_MCO1_PRESCALER_5                    (uint32_t)((RCC_CFGR1_MCO1PRE>>16U) | RCC_CFGR1_MCO1PRE_2 | RCC_CFGR1_MCO1PRE_0)                         /*!< MCO1 divided by 5 */
#define LL_RCC_MCO1_PRESCALER_6                    (uint32_t)((RCC_CFGR1_MCO1PRE>>16U) | RCC_CFGR1_MCO1PRE_2 | RCC_CFGR1_MCO1PRE_1)                         /*!< MCO1 divided by 6 */
#define LL_RCC_MCO1_PRESCALER_7                    (uint32_t)((RCC_CFGR1_MCO1PRE>>16U) | RCC_CFGR1_MCO1PRE_2 | RCC_CFGR1_MCO1PRE_1 | RCC_CFGR1_MCO1PRE_0)   /*!< MCO1 divided by 7 */
#define LL_RCC_MCO1_PRESCALER_8                    (uint32_t)((RCC_CFGR1_MCO1PRE>>16U) | RCC_CFGR1_MCO1PRE_3)                                               /*!< MCO1 divided by 8 */
#define LL_RCC_MCO1_PRESCALER_9                    (uint32_t)((RCC_CFGR1_MCO1PRE>>16U) | RCC_CFGR1_MCO1PRE_3 | RCC_CFGR1_MCO1PRE_0)                         /*!< MCO1 divided by 9 */
#define LL_RCC_MCO1_PRESCALER_10                   (uint32_t)((RCC_CFGR1_MCO1PRE>>16U) | RCC_CFGR1_MCO1PRE_3 | RCC_CFGR1_MCO1PRE_1)                         /*!< MCO1 divided by 10 */
#define LL_RCC_MCO1_PRESCALER_11                   (uint32_t)((RCC_CFGR1_MCO1PRE>>16U) | RCC_CFGR1_MCO1PRE_3 | RCC_CFGR1_MCO1PRE_1 | RCC_CFGR1_MCO1PRE_0)   /*!< MCO1 divided by 11 */
#define LL_RCC_MCO1_PRESCALER_12                   (uint32_t)((RCC_CFGR1_MCO1PRE>>16U) | RCC_CFGR1_MCO1PRE_3 | RCC_CFGR1_MCO1PRE_2)                         /*!< MCO1 divided by 12 */
#define LL_RCC_MCO1_PRESCALER_13                   (uint32_t)((RCC_CFGR1_MCO1PRE>>16U) | RCC_CFGR1_MCO1PRE_3 | RCC_CFGR1_MCO1PRE_2 | RCC_CFGR1_MCO1PRE_0)   /*!< MCO1 divided by 13 */
#define LL_RCC_MCO1_PRESCALER_14                   (uint32_t)((RCC_CFGR1_MCO1PRE>>16U) | RCC_CFGR1_MCO1PRE_3 | RCC_CFGR1_MCO1PRE_2 | RCC_CFGR1_MCO1PRE_1)   /*!< MCO1 divided by 14 */
#define LL_RCC_MCO1_PRESCALER_15                   (uint32_t)((RCC_CFGR1_MCO1PRE>>16U) | RCC_CFGR1_MCO1PRE)                                                 /*!< MCO1 divided by 15 */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_MCO2_DIV  MCO2 prescaler
  * @{
  */
#define LL_RCC_MCO2_NO_CLK                   (uint32_t)((RCC_CFGR1_MCO2PRE>>16U) | 0x00000000U)                                                       /*!< MCO2 output disabled, no clock on MCO2 */
#define LL_RCC_MCO2_PRESCALER_1                    (uint32_t)((RCC_CFGR1_MCO2PRE>>16U) | RCC_CFGR1_MCO2PRE_0)                                               /*!< MCO2 not divided */
#define LL_RCC_MCO2_PRESCALER_2                    (uint32_t)((RCC_CFGR1_MCO2PRE>>16U) | RCC_CFGR1_MCO2PRE_1)                                               /*!< MCO2 divided by 2 */
#define LL_RCC_MCO2_PRESCALER_3                    (uint32_t)((RCC_CFGR1_MCO2PRE>>16U) | RCC_CFGR1_MCO2PRE_0 | RCC_CFGR1_MCO2PRE_1)                         /*!< MCO2 divided by 3 */
#define LL_RCC_MCO2_PRESCALER_4                    (uint32_t)((RCC_CFGR1_MCO2PRE>>16U) | RCC_CFGR1_MCO2PRE_2)                                               /*!< MCO2 divided by 4 */
#define LL_RCC_MCO2_PRESCALER_5                    (uint32_t)((RCC_CFGR1_MCO2PRE>>16U) | RCC_CFGR1_MCO2PRE_2 | RCC_CFGR1_MCO2PRE_0)                         /*!< MCO2 divided by 5 */
#define LL_RCC_MCO2_PRESCALER_6                    (uint32_t)((RCC_CFGR1_MCO2PRE>>16U) | RCC_CFGR1_MCO2PRE_2 | RCC_CFGR1_MCO2PRE_1)                         /*!< MCO2 divided by 6 */
#define LL_RCC_MCO2_PRESCALER_7                    (uint32_t)((RCC_CFGR1_MCO2PRE>>16U) | RCC_CFGR1_MCO2PRE_2 | RCC_CFGR1_MCO2PRE_1 | RCC_CFGR1_MCO2PRE_0)   /*!< MCO2 divided by 7 */
#define LL_RCC_MCO2_PRESCALER_8                    (uint32_t)((RCC_CFGR1_MCO2PRE>>16U) | RCC_CFGR1_MCO2PRE_3)                                               /*!< MCO2 divided by 8 */
#define LL_RCC_MCO2_PRESCALER_9                    (uint32_t)((RCC_CFGR1_MCO2PRE>>16U) | RCC_CFGR1_MCO2PRE_3 | RCC_CFGR1_MCO2PRE_0)                         /*!< MCO2 divided by 9 */
#define LL_RCC_MCO2_PRESCALER_10                   (uint32_t)((RCC_CFGR1_MCO2PRE>>16U) | RCC_CFGR1_MCO2PRE_3 | RCC_CFGR1_MCO2PRE_1)                         /*!< MCO2 divided by 10 */
#define LL_RCC_MCO2_PRESCALER_11                   (uint32_t)((RCC_CFGR1_MCO2PRE>>16U) | RCC_CFGR1_MCO2PRE_3 | RCC_CFGR1_MCO2PRE_1 | RCC_CFGR1_MCO2PRE_0)   /*!< MCO2 divided by 11 */
#define LL_RCC_MCO2_PRESCALER_12                   (uint32_t)((RCC_CFGR1_MCO2PRE>>16U) | RCC_CFGR1_MCO2PRE_3 | RCC_CFGR1_MCO2PRE_2)                         /*!< MCO2 divided by 12 */
#define LL_RCC_MCO2_PRESCALER_13                   (uint32_t)((RCC_CFGR1_MCO2PRE>>16U) | RCC_CFGR1_MCO2PRE_3 | RCC_CFGR1_MCO2PRE_2 | RCC_CFGR1_MCO2PRE_0)   /*!< MCO2 divided by 13 */
#define LL_RCC_MCO2_PRESCALER_14                   (uint32_t)((RCC_CFGR1_MCO2PRE>>16U) | RCC_CFGR1_MCO2PRE_3 | RCC_CFGR1_MCO2PRE_2 | RCC_CFGR1_MCO2PRE_1)   /*!< MCO2 divided by 14 */
#define LL_RCC_MCO2_PRESCALER_15                   (uint32_t)((RCC_CFGR1_MCO2PRE>>16U) | RCC_CFGR1_MCO2PRE)                                                 /*!< MCO2 divided by 15 */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_RTC_CLKSOURCE  RTC clock source selection
  * @{
  */
#define LL_RCC_RTC_CLKSOURCE_NONE            0U                     /*!< No clock used as RTC clock */
#define LL_RCC_RTC_CLKSOURCE_LSE             RCC_RTCCR_RTCSEL_0     /*!< LSE oscillator clock used as RTC clock */
#define LL_RCC_RTC_CLKSOURCE_LSI             RCC_RTCCR_RTCSEL_1     /*!< LSI oscillator clock used as RTC clock */
#define LL_RCC_RTC_CLKSOURCE_HSE             RCC_RTCCR_RTCSEL       /*!< HSE oscillator clock divided by RTCPRE used as RTC clock */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_RTC_HSE_DIV  RTC clock prescaler
  * @{
  */
#define LL_RCC_RTC_HSE_DIV_DIS RCC_CFGR1_RTCPRE_0
#define LL_RCC_RTC_HSE_DIV_2   RCC_CFGR1_RTCPRE_1
#define LL_RCC_RTC_HSE_DIV_3   (RCC_CFGR1_RTCPRE_1 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_4   RCC_CFGR1_RTCPRE_2
#define LL_RCC_RTC_HSE_DIV_5   (RCC_CFGR1_RTCPRE_2 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_6   (RCC_CFGR1_RTCPRE_2 | RCC_CFGR1_RTCPRE_1)
#define LL_RCC_RTC_HSE_DIV_7   (RCC_CFGR1_RTCPRE_2 | RCC_CFGR1_RTCPRE_1 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_8   RCC_CFGR1_RTCPRE_3
#define LL_RCC_RTC_HSE_DIV_9   (RCC_CFGR1_RTCPRE_3 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_10  (RCC_CFGR1_RTCPRE_3 | RCC_CFGR1_RTCPRE_1)
#define LL_RCC_RTC_HSE_DIV_11  (RCC_CFGR1_RTCPRE_3 | RCC_CFGR1_RTCPRE_1 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_12  (RCC_CFGR1_RTCPRE_3 | RCC_CFGR1_RTCPRE_2)
#define LL_RCC_RTC_HSE_DIV_13  (RCC_CFGR1_RTCPRE_3 | RCC_CFGR1_RTCPRE_2 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_14  (RCC_CFGR1_RTCPRE_3 | RCC_CFGR1_RTCPRE_2 | RCC_CFGR1_RTCPRE_1)
#define LL_RCC_RTC_HSE_DIV_15  (RCC_CFGR1_RTCPRE_3 | RCC_CFGR1_RTCPRE_2 | RCC_CFGR1_RTCPRE_1 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_16  RCC_CFGR1_RTCPRE_4
#define LL_RCC_RTC_HSE_DIV_17  (RCC_CFGR1_RTCPRE_4 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_18  (RCC_CFGR1_RTCPRE_4 | RCC_CFGR1_RTCPRE_1)
#define LL_RCC_RTC_HSE_DIV_19  (RCC_CFGR1_RTCPRE_4 | RCC_CFGR1_RTCPRE_1 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_20  (RCC_CFGR1_RTCPRE_4 | RCC_CFGR1_RTCPRE_2)
#define LL_RCC_RTC_HSE_DIV_21  (RCC_CFGR1_RTCPRE_4 | RCC_CFGR1_RTCPRE_2 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_22  (RCC_CFGR1_RTCPRE_4 | RCC_CFGR1_RTCPRE_2 | RCC_CFGR1_RTCPRE_1)
#define LL_RCC_RTC_HSE_DIV_23  (RCC_CFGR1_RTCPRE_4 | RCC_CFGR1_RTCPRE_2 | RCC_CFGR1_RTCPRE_1 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_24  (RCC_CFGR1_RTCPRE_4 | RCC_CFGR1_RTCPRE_3)
#define LL_RCC_RTC_HSE_DIV_25  (RCC_CFGR1_RTCPRE_4 | RCC_CFGR1_RTCPRE_3 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_26  (RCC_CFGR1_RTCPRE_4 | RCC_CFGR1_RTCPRE_3 | RCC_CFGR1_RTCPRE_1)
#define LL_RCC_RTC_HSE_DIV_27  (RCC_CFGR1_RTCPRE_4 | RCC_CFGR1_RTCPRE_3 | RCC_CFGR1_RTCPRE_1 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_28  (RCC_CFGR1_RTCPRE_4 | RCC_CFGR1_RTCPRE_3 | RCC_CFGR1_RTCPRE_2)
#define LL_RCC_RTC_HSE_DIV_29  (RCC_CFGR1_RTCPRE_4 | RCC_CFGR1_RTCPRE_3 | RCC_CFGR1_RTCPRE_2 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_30  (RCC_CFGR1_RTCPRE_4 | RCC_CFGR1_RTCPRE_3 | RCC_CFGR1_RTCPRE_2 | RCC_CFGR1_RTCPRE_1)
#define LL_RCC_RTC_HSE_DIV_31  (RCC_CFGR1_RTCPRE_4 | RCC_CFGR1_RTCPRE_3 | RCC_CFGR1_RTCPRE_2 | RCC_CFGR1_RTCPRE_1 | \
                                RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_32  RCC_CFGR1_RTCPRE_5
#define LL_RCC_RTC_HSE_DIV_33  (RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_34  (RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_1)
#define LL_RCC_RTC_HSE_DIV_35  (RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_1 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_36  (RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_2)
#define LL_RCC_RTC_HSE_DIV_37  (RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_2 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_38  (RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_2 | RCC_CFGR1_RTCPRE_1)
#define LL_RCC_RTC_HSE_DIV_39  (RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_2 | RCC_CFGR1_RTCPRE_1 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_40  (RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_3)
#define LL_RCC_RTC_HSE_DIV_41  (RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_3 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_42  (RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_3 | RCC_CFGR1_RTCPRE_1)
#define LL_RCC_RTC_HSE_DIV_43  (RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_3 | RCC_CFGR1_RTCPRE_1 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_44  (RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_3 | RCC_CFGR1_RTCPRE_2)
#define LL_RCC_RTC_HSE_DIV_45  (RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_3 | RCC_CFGR1_RTCPRE_2 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_46  (RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_3 | RCC_CFGR1_RTCPRE_2 | RCC_CFGR1_RTCPRE_1)
#define LL_RCC_RTC_HSE_DIV_47  (RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_3 | RCC_CFGR1_RTCPRE_2 | RCC_CFGR1_RTCPRE_1 | \
                                RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_48  (RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_4)
#define LL_RCC_RTC_HSE_DIV_49  (RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_4 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_50  (RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_4 | RCC_CFGR1_RTCPRE_1)
#define LL_RCC_RTC_HSE_DIV_51  (RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_4 | RCC_CFGR1_RTCPRE_1 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_52  (RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_4 | RCC_CFGR1_RTCPRE_2)
#define LL_RCC_RTC_HSE_DIV_53  (RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_4 | RCC_CFGR1_RTCPRE_2 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_54  (RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_4 | RCC_CFGR1_RTCPRE_2 | RCC_CFGR1_RTCPRE_1)
#define LL_RCC_RTC_HSE_DIV_55  (RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_4 | RCC_CFGR1_RTCPRE_2 | RCC_CFGR1_RTCPRE_1 | \
                                RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_56  (RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_4 | RCC_CFGR1_RTCPRE_3)
#define LL_RCC_RTC_HSE_DIV_57  (RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_4 | RCC_CFGR1_RTCPRE_3 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_58  (RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_4 | RCC_CFGR1_RTCPRE_3 | RCC_CFGR1_RTCPRE_1)
#define LL_RCC_RTC_HSE_DIV_59  (RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_4 | RCC_CFGR1_RTCPRE_3 | RCC_CFGR1_RTCPRE_1 | \
                                RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_60  (RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_4 | RCC_CFGR1_RTCPRE_3 | RCC_CFGR1_RTCPRE_2)
#define LL_RCC_RTC_HSE_DIV_61  (RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_4 | RCC_CFGR1_RTCPRE_3 | RCC_CFGR1_RTCPRE_2 | \
                                RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_62  (RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_4 | RCC_CFGR1_RTCPRE_3 | RCC_CFGR1_RTCPRE_2 | \
                                RCC_CFGR1_RTCPRE_1)
#define LL_RCC_RTC_HSE_DIV_63  (RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_4 | RCC_CFGR1_RTCPRE_3 | RCC_CFGR1_RTCPRE_2 | \
                                RCC_CFGR1_RTCPRE_1 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_64  RCC_CFGR1_RTCPRE_6
#define LL_RCC_RTC_HSE_DIV_65  (RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_66  (RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_1)
#define LL_RCC_RTC_HSE_DIV_67  (RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_1 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_68  (RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_2)
#define LL_RCC_RTC_HSE_DIV_69  (RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_2 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_70  (RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_2 | RCC_CFGR1_RTCPRE_1)
#define LL_RCC_RTC_HSE_DIV_71  (RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_2 | RCC_CFGR1_RTCPRE_1 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_72  (RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_3)
#define LL_RCC_RTC_HSE_DIV_73  (RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_3 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_74  (RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_3 | RCC_CFGR1_RTCPRE_1)
#define LL_RCC_RTC_HSE_DIV_75  (RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_3 | RCC_CFGR1_RTCPRE_1 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_76  (RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_3 | RCC_CFGR1_RTCPRE_2)
#define LL_RCC_RTC_HSE_DIV_77  (RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_3 | RCC_CFGR1_RTCPRE_2 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_78  (RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_3 | RCC_CFGR1_RTCPRE_2 | RCC_CFGR1_RTCPRE_1)
#define LL_RCC_RTC_HSE_DIV_79  (RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_3 | RCC_CFGR1_RTCPRE_2 | RCC_CFGR1_RTCPRE_1 | \
                                RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_80  (RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_4)
#define LL_RCC_RTC_HSE_DIV_81  (RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_4 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_82  (RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_4 | RCC_CFGR1_RTCPRE_1)
#define LL_RCC_RTC_HSE_DIV_83  (RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_4 | RCC_CFGR1_RTCPRE_1 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_84  (RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_4 | RCC_CFGR1_RTCPRE_2)
#define LL_RCC_RTC_HSE_DIV_85  (RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_4 | RCC_CFGR1_RTCPRE_2 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_86  (RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_4 | RCC_CFGR1_RTCPRE_2 | RCC_CFGR1_RTCPRE_1)
#define LL_RCC_RTC_HSE_DIV_87  (RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_4 | RCC_CFGR1_RTCPRE_2 | RCC_CFGR1_RTCPRE_1 | \
                                RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_88  (RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_4 | RCC_CFGR1_RTCPRE_3)
#define LL_RCC_RTC_HSE_DIV_89  (RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_4 | RCC_CFGR1_RTCPRE_3 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_90  (RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_4 | RCC_CFGR1_RTCPRE_3 | RCC_CFGR1_RTCPRE_1)
#define LL_RCC_RTC_HSE_DIV_91  (RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_4 | RCC_CFGR1_RTCPRE_3 | RCC_CFGR1_RTCPRE_1 | \
                                RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_92  (RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_4 | RCC_CFGR1_RTCPRE_3 | RCC_CFGR1_RTCPRE_2)
#define LL_RCC_RTC_HSE_DIV_93  (RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_4 | RCC_CFGR1_RTCPRE_3 | RCC_CFGR1_RTCPRE_2 | \
                                RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_94  (RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_4 | RCC_CFGR1_RTCPRE_3 | RCC_CFGR1_RTCPRE_2 | \
                                RCC_CFGR1_RTCPRE_1)
#define LL_RCC_RTC_HSE_DIV_95  (RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_4 | RCC_CFGR1_RTCPRE_3 | RCC_CFGR1_RTCPRE_2 | \
                                RCC_CFGR1_RTCPRE_1 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_96  (RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_5)
#define LL_RCC_RTC_HSE_DIV_97  (RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_98  (RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_1)
#define LL_RCC_RTC_HSE_DIV_99  (RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_1 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_100 (RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_2)
#define LL_RCC_RTC_HSE_DIV_101 (RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_2 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_102 (RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_2 | RCC_CFGR1_RTCPRE_1)
#define LL_RCC_RTC_HSE_DIV_103 (RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_2 | RCC_CFGR1_RTCPRE_1 | \
                                RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_104 (RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_3)
#define LL_RCC_RTC_HSE_DIV_105 (RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_3 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_106 (RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_3 | RCC_CFGR1_RTCPRE_1)
#define LL_RCC_RTC_HSE_DIV_107 (RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_3 | RCC_CFGR1_RTCPRE_1 | \
                                RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_108 (RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_3 | RCC_CFGR1_RTCPRE_2)
#define LL_RCC_RTC_HSE_DIV_109 (RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_3 | RCC_CFGR1_RTCPRE_2 | \
                                RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_110 (RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_3 | RCC_CFGR1_RTCPRE_2 | \
                                RCC_CFGR1_RTCPRE_1)
#define LL_RCC_RTC_HSE_DIV_111 (RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_3 | RCC_CFGR1_RTCPRE_2 | \
                                RCC_CFGR1_RTCPRE_1 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_112 (RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_4)
#define LL_RCC_RTC_HSE_DIV_113 (RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_4 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_114 (RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_4 | RCC_CFGR1_RTCPRE_1)
#define LL_RCC_RTC_HSE_DIV_115 (RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_4 | RCC_CFGR1_RTCPRE_1 | \
                                RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_116 (RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_4 | RCC_CFGR1_RTCPRE_2)
#define LL_RCC_RTC_HSE_DIV_117 (RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_4 | RCC_CFGR1_RTCPRE_2 | \
                                RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_118 (RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_4 | RCC_CFGR1_RTCPRE_2 | \
                                RCC_CFGR1_RTCPRE_1)
#define LL_RCC_RTC_HSE_DIV_119 (RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_4 | RCC_CFGR1_RTCPRE_2 | \
                                RCC_CFGR1_RTCPRE_1 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_120 (RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_4 | RCC_CFGR1_RTCPRE_3)
#define LL_RCC_RTC_HSE_DIV_121 (RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_4 | RCC_CFGR1_RTCPRE_3 | \
                                RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_122 (RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_4 | RCC_CFGR1_RTCPRE_3 | \
                                RCC_CFGR1_RTCPRE_1)
#define LL_RCC_RTC_HSE_DIV_123 (RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_4 | RCC_CFGR1_RTCPRE_3 | \
                                RCC_CFGR1_RTCPRE_1 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_124 (RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_4 | RCC_CFGR1_RTCPRE_3 | \
                                RCC_CFGR1_RTCPRE_2)
#define LL_RCC_RTC_HSE_DIV_125 (RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_4 | RCC_CFGR1_RTCPRE_3 | \
                                RCC_CFGR1_RTCPRE_2 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_126 (RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_4 | RCC_CFGR1_RTCPRE_3 | \
                                RCC_CFGR1_RTCPRE_2 | RCC_CFGR1_RTCPRE_1)
#define LL_RCC_RTC_HSE_DIV_127 (RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_4 | RCC_CFGR1_RTCPRE_3 | \
                                RCC_CFGR1_RTCPRE_2 | RCC_CFGR1_RTCPRE_1 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_128 RCC_CFGR1_RTCPRE_7
#define LL_RCC_RTC_HSE_DIV_129 (RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_130 (RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_1)
#define LL_RCC_RTC_HSE_DIV_131 (RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_1 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_132 (RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_2)
#define LL_RCC_RTC_HSE_DIV_133 (RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_2 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_134 (RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_2 | RCC_CFGR1_RTCPRE_1)
#define LL_RCC_RTC_HSE_DIV_135 (RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_2 | RCC_CFGR1_RTCPRE_1 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_136 (RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_3)
#define LL_RCC_RTC_HSE_DIV_137 (RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_3 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_138 (RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_3 | RCC_CFGR1_RTCPRE_1)
#define LL_RCC_RTC_HSE_DIV_139 (RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_3 | RCC_CFGR1_RTCPRE_1 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_140 (RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_3 | RCC_CFGR1_RTCPRE_2)
#define LL_RCC_RTC_HSE_DIV_141 (RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_3 | RCC_CFGR1_RTCPRE_2 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_142 (RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_3 | RCC_CFGR1_RTCPRE_2 | RCC_CFGR1_RTCPRE_1)
#define LL_RCC_RTC_HSE_DIV_143 (RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_3 | RCC_CFGR1_RTCPRE_2 | RCC_CFGR1_RTCPRE_1 | \
                                RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_144 (RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_4)
#define LL_RCC_RTC_HSE_DIV_145 (RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_4 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_146 (RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_4 | RCC_CFGR1_RTCPRE_1)
#define LL_RCC_RTC_HSE_DIV_147 (RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_4 | RCC_CFGR1_RTCPRE_1 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_148 (RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_4 | RCC_CFGR1_RTCPRE_2)
#define LL_RCC_RTC_HSE_DIV_149 (RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_4 | RCC_CFGR1_RTCPRE_2 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_150 (RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_4 | RCC_CFGR1_RTCPRE_2 | RCC_CFGR1_RTCPRE_1)
#define LL_RCC_RTC_HSE_DIV_151 (RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_4 | RCC_CFGR1_RTCPRE_2 | RCC_CFGR1_RTCPRE_1 | \
                                RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_152 (RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_4 | RCC_CFGR1_RTCPRE_3)
#define LL_RCC_RTC_HSE_DIV_153 (RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_4 | RCC_CFGR1_RTCPRE_3 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_154 (RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_4 | RCC_CFGR1_RTCPRE_3 | RCC_CFGR1_RTCPRE_1)
#define LL_RCC_RTC_HSE_DIV_155 (RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_4 | RCC_CFGR1_RTCPRE_3 | RCC_CFGR1_RTCPRE_1 | \
                                RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_156 (RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_4 | RCC_CFGR1_RTCPRE_3 | RCC_CFGR1_RTCPRE_2)
#define LL_RCC_RTC_HSE_DIV_157 (RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_4 | RCC_CFGR1_RTCPRE_3 | RCC_CFGR1_RTCPRE_2 | \
                                RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_158 (RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_4 | RCC_CFGR1_RTCPRE_3 | RCC_CFGR1_RTCPRE_2 | \
                                RCC_CFGR1_RTCPRE_1)
#define LL_RCC_RTC_HSE_DIV_159 (RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_4 | RCC_CFGR1_RTCPRE_3 | RCC_CFGR1_RTCPRE_2 | \
                                RCC_CFGR1_RTCPRE_1 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_160 (RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_5)
#define LL_RCC_RTC_HSE_DIV_161 (RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_162 (RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_1)
#define LL_RCC_RTC_HSE_DIV_163 (RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_1 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_164 (RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_2)
#define LL_RCC_RTC_HSE_DIV_165 (RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_2 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_166 (RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_2 | RCC_CFGR1_RTCPRE_1)
#define LL_RCC_RTC_HSE_DIV_167 (RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_2 | RCC_CFGR1_RTCPRE_1 | \
                                RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_168 (RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_3)
#define LL_RCC_RTC_HSE_DIV_169 (RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_3 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_170 (RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_3 | RCC_CFGR1_RTCPRE_1)
#define LL_RCC_RTC_HSE_DIV_171 (RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_3 | RCC_CFGR1_RTCPRE_1 | \
                                RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_172 (RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_3 | RCC_CFGR1_RTCPRE_2)
#define LL_RCC_RTC_HSE_DIV_173 (RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_3 | RCC_CFGR1_RTCPRE_2 | \
                                RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_174 (RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_3 | RCC_CFGR1_RTCPRE_2 | \
                                RCC_CFGR1_RTCPRE_1)
#define LL_RCC_RTC_HSE_DIV_175 (RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_3 | RCC_CFGR1_RTCPRE_2 | \
                                RCC_CFGR1_RTCPRE_1 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_176 (RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_4)
#define LL_RCC_RTC_HSE_DIV_177 (RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_4 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_178 (RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_4 | RCC_CFGR1_RTCPRE_1)
#define LL_RCC_RTC_HSE_DIV_179 (RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_4 | RCC_CFGR1_RTCPRE_1 | \
                                RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_180 (RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_4 | RCC_CFGR1_RTCPRE_2)
#define LL_RCC_RTC_HSE_DIV_181 (RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_4 | RCC_CFGR1_RTCPRE_2 | \
                                RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_182 (RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_4 | RCC_CFGR1_RTCPRE_2 | \
                                RCC_CFGR1_RTCPRE_1)
#define LL_RCC_RTC_HSE_DIV_183 (RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_4 | RCC_CFGR1_RTCPRE_2 | \
                                RCC_CFGR1_RTCPRE_1 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_184 (RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_4 | RCC_CFGR1_RTCPRE_3)
#define LL_RCC_RTC_HSE_DIV_185 (RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_4 | RCC_CFGR1_RTCPRE_3 | \
                                RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_186 (RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_4 | RCC_CFGR1_RTCPRE_3 | \
                                RCC_CFGR1_RTCPRE_1)
#define LL_RCC_RTC_HSE_DIV_187 (RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_4 | RCC_CFGR1_RTCPRE_3 | \
                                RCC_CFGR1_RTCPRE_1 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_188 (RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_4 | RCC_CFGR1_RTCPRE_3 | \
                                RCC_CFGR1_RTCPRE_2)
#define LL_RCC_RTC_HSE_DIV_189 (RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_4 | RCC_CFGR1_RTCPRE_3 | \
                                RCC_CFGR1_RTCPRE_2 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_190 (RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_4 | RCC_CFGR1_RTCPRE_3 | \
                                RCC_CFGR1_RTCPRE_2 | RCC_CFGR1_RTCPRE_1)
#define LL_RCC_RTC_HSE_DIV_191 (RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_4 | RCC_CFGR1_RTCPRE_3 | \
                                RCC_CFGR1_RTCPRE_2 | RCC_CFGR1_RTCPRE_1 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_192 (RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_6)
#define LL_RCC_RTC_HSE_DIV_193 (RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_194 (RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_1)
#define LL_RCC_RTC_HSE_DIV_195 (RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_1 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_196 (RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_2)
#define LL_RCC_RTC_HSE_DIV_197 (RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_2 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_198 (RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_2 | RCC_CFGR1_RTCPRE_1)
#define LL_RCC_RTC_HSE_DIV_199 (RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_2 | RCC_CFGR1_RTCPRE_1 | \
                                RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_200 (RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_3)
#define LL_RCC_RTC_HSE_DIV_201 (RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_3 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_202 (RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_3 | RCC_CFGR1_RTCPRE_1)
#define LL_RCC_RTC_HSE_DIV_203 (RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_3 | RCC_CFGR1_RTCPRE_1 | \
                                RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_204 (RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_3 | RCC_CFGR1_RTCPRE_2)
#define LL_RCC_RTC_HSE_DIV_205 (RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_3 | RCC_CFGR1_RTCPRE_2 | \
                                RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_206 (RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_3 | RCC_CFGR1_RTCPRE_2 | \
                                RCC_CFGR1_RTCPRE_1)
#define LL_RCC_RTC_HSE_DIV_207 (RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_3 | RCC_CFGR1_RTCPRE_2 | \
                                RCC_CFGR1_RTCPRE_1 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_208 (RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_4)
#define LL_RCC_RTC_HSE_DIV_209 (RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_4 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_210 (RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_4 | RCC_CFGR1_RTCPRE_1)
#define LL_RCC_RTC_HSE_DIV_211 (RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_4 | RCC_CFGR1_RTCPRE_1 | \
                                RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_212 (RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_4 | RCC_CFGR1_RTCPRE_2)
#define LL_RCC_RTC_HSE_DIV_213 (RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_4 | RCC_CFGR1_RTCPRE_2 | \
                                RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_214 (RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_4 | RCC_CFGR1_RTCPRE_2 | \
                                RCC_CFGR1_RTCPRE_1)
#define LL_RCC_RTC_HSE_DIV_215 (RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_4 | RCC_CFGR1_RTCPRE_2 | \
                                RCC_CFGR1_RTCPRE_1 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_216 (RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_4 | RCC_CFGR1_RTCPRE_3)
#define LL_RCC_RTC_HSE_DIV_217 (RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_4 | RCC_CFGR1_RTCPRE_3 | \
                                RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_218 (RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_4 | RCC_CFGR1_RTCPRE_3 | \
                                RCC_CFGR1_RTCPRE_1)
#define LL_RCC_RTC_HSE_DIV_219 (RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_4 | RCC_CFGR1_RTCPRE_3 | \
                                RCC_CFGR1_RTCPRE_1 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_220 (RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_4 | RCC_CFGR1_RTCPRE_3 | \
                                RCC_CFGR1_RTCPRE_2)
#define LL_RCC_RTC_HSE_DIV_221 (RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_4 | RCC_CFGR1_RTCPRE_3 | \
                                RCC_CFGR1_RTCPRE_2 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_222 (RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_4 | RCC_CFGR1_RTCPRE_3 | \
                                RCC_CFGR1_RTCPRE_2 | RCC_CFGR1_RTCPRE_1)
#define LL_RCC_RTC_HSE_DIV_223 (RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_4 | RCC_CFGR1_RTCPRE_3 | \
                                RCC_CFGR1_RTCPRE_2 | RCC_CFGR1_RTCPRE_1 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_224 (RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_5)
#define LL_RCC_RTC_HSE_DIV_225 (RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_226 (RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_1)
#define LL_RCC_RTC_HSE_DIV_227 (RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_1 | \
                                RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_228 (RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_2)
#define LL_RCC_RTC_HSE_DIV_229 (RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_2 | \
                                RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_230 (RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_2 | \
                                RCC_CFGR1_RTCPRE_1)
#define LL_RCC_RTC_HSE_DIV_231 (RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_2 | \
                                RCC_CFGR1_RTCPRE_1 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_232 (RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_3)
#define LL_RCC_RTC_HSE_DIV_233 (RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_3 | \
                                RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_234 (RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_3 | \
                                RCC_CFGR1_RTCPRE_1)
#define LL_RCC_RTC_HSE_DIV_235 (RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_3 | \
                                RCC_CFGR1_RTCPRE_1 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_236 (RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_3 | \
                                RCC_CFGR1_RTCPRE_2)
#define LL_RCC_RTC_HSE_DIV_237 (RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_3 | \
                                RCC_CFGR1_RTCPRE_2 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_238 (RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_3 | \
                                RCC_CFGR1_RTCPRE_2 | RCC_CFGR1_RTCPRE_1)
#define LL_RCC_RTC_HSE_DIV_239 (RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_3 | \
                                RCC_CFGR1_RTCPRE_2 | RCC_CFGR1_RTCPRE_1 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_240 (RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_4)
#define LL_RCC_RTC_HSE_DIV_241 (RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_4 | \
                                RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_242 (RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_4 | \
                                RCC_CFGR1_RTCPRE_1)
#define LL_RCC_RTC_HSE_DIV_243 (RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_4 | \
                                RCC_CFGR1_RTCPRE_1 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_244 (RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_4 | \
                                RCC_CFGR1_RTCPRE_2)
#define LL_RCC_RTC_HSE_DIV_245 (RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_4 | \
                                RCC_CFGR1_RTCPRE_2 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_246 (RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_4 | \
                                RCC_CFGR1_RTCPRE_2 | RCC_CFGR1_RTCPRE_1)
#define LL_RCC_RTC_HSE_DIV_247 (RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_4 | \
                                RCC_CFGR1_RTCPRE_2 | RCC_CFGR1_RTCPRE_1 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_248 (RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_4 | \
                                RCC_CFGR1_RTCPRE_3)
#define LL_RCC_RTC_HSE_DIV_249 (RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_4 | \
                                RCC_CFGR1_RTCPRE_3 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_250 (RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_4 | \
                                RCC_CFGR1_RTCPRE_3 | RCC_CFGR1_RTCPRE_1)
#define LL_RCC_RTC_HSE_DIV_251 (RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_4 | \
                                RCC_CFGR1_RTCPRE_3 | RCC_CFGR1_RTCPRE_1 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_252 (RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_4 | \
                                RCC_CFGR1_RTCPRE_3 | RCC_CFGR1_RTCPRE_2)
#define LL_RCC_RTC_HSE_DIV_253 (RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_4 | \
                                RCC_CFGR1_RTCPRE_3 | RCC_CFGR1_RTCPRE_2 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_254 (RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_4 | \
                                RCC_CFGR1_RTCPRE_3 | RCC_CFGR1_RTCPRE_2 | RCC_CFGR1_RTCPRE_1)
#define LL_RCC_RTC_HSE_DIV_255 (RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_4 | \
                                RCC_CFGR1_RTCPRE_3 | RCC_CFGR1_RTCPRE_2 | RCC_CFGR1_RTCPRE_1 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_256 RCC_CFGR1_RTCPRE_8
#define LL_RCC_RTC_HSE_DIV_257 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_258 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_1)
#define LL_RCC_RTC_HSE_DIV_259 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_1 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_260 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_2)
#define LL_RCC_RTC_HSE_DIV_261 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_2 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_262 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_2 | RCC_CFGR1_RTCPRE_1)
#define LL_RCC_RTC_HSE_DIV_263 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_2 | RCC_CFGR1_RTCPRE_1 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_264 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_3)
#define LL_RCC_RTC_HSE_DIV_265 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_3 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_266 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_3 | RCC_CFGR1_RTCPRE_1)
#define LL_RCC_RTC_HSE_DIV_267 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_3 | RCC_CFGR1_RTCPRE_1 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_268 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_3 | RCC_CFGR1_RTCPRE_2)
#define LL_RCC_RTC_HSE_DIV_269 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_3 | RCC_CFGR1_RTCPRE_2 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_270 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_3 | RCC_CFGR1_RTCPRE_2 | RCC_CFGR1_RTCPRE_1)
#define LL_RCC_RTC_HSE_DIV_271 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_3 | RCC_CFGR1_RTCPRE_2 | RCC_CFGR1_RTCPRE_1 | \
                                RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_272 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_4)
#define LL_RCC_RTC_HSE_DIV_273 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_4 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_274 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_4 | RCC_CFGR1_RTCPRE_1)
#define LL_RCC_RTC_HSE_DIV_275 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_4 | RCC_CFGR1_RTCPRE_1 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_276 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_4 | RCC_CFGR1_RTCPRE_2)
#define LL_RCC_RTC_HSE_DIV_277 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_4 | RCC_CFGR1_RTCPRE_2 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_278 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_4 | RCC_CFGR1_RTCPRE_2 | RCC_CFGR1_RTCPRE_1)
#define LL_RCC_RTC_HSE_DIV_279 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_4 | RCC_CFGR1_RTCPRE_2 | RCC_CFGR1_RTCPRE_1 | \
                                RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_280 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_4 | RCC_CFGR1_RTCPRE_3)
#define LL_RCC_RTC_HSE_DIV_281 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_4 | RCC_CFGR1_RTCPRE_3 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_282 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_4 | RCC_CFGR1_RTCPRE_3 | RCC_CFGR1_RTCPRE_1)
#define LL_RCC_RTC_HSE_DIV_283 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_4 | RCC_CFGR1_RTCPRE_3 | RCC_CFGR1_RTCPRE_1 | \
                                RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_284 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_4 | RCC_CFGR1_RTCPRE_3 | RCC_CFGR1_RTCPRE_2)
#define LL_RCC_RTC_HSE_DIV_285 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_4 | RCC_CFGR1_RTCPRE_3 | RCC_CFGR1_RTCPRE_2 | \
                                RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_286 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_4 | RCC_CFGR1_RTCPRE_3 | RCC_CFGR1_RTCPRE_2 | \
                                RCC_CFGR1_RTCPRE_1)
#define LL_RCC_RTC_HSE_DIV_287 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_4 | RCC_CFGR1_RTCPRE_3 | RCC_CFGR1_RTCPRE_2 | \
                                RCC_CFGR1_RTCPRE_1 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_288 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_5)
#define LL_RCC_RTC_HSE_DIV_289 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_290 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_1)
#define LL_RCC_RTC_HSE_DIV_291 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_1 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_292 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_2)
#define LL_RCC_RTC_HSE_DIV_293 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_2 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_294 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_2 | RCC_CFGR1_RTCPRE_1)
#define LL_RCC_RTC_HSE_DIV_295 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_2 | RCC_CFGR1_RTCPRE_1 | \
                                RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_296 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_3)
#define LL_RCC_RTC_HSE_DIV_297 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_3 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_298 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_3 | RCC_CFGR1_RTCPRE_1)
#define LL_RCC_RTC_HSE_DIV_299 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_3 | RCC_CFGR1_RTCPRE_1 | \
                                RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_300 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_3 | RCC_CFGR1_RTCPRE_2)
#define LL_RCC_RTC_HSE_DIV_301 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_3 | RCC_CFGR1_RTCPRE_2 | \
                                RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_302 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_3 | RCC_CFGR1_RTCPRE_2 | \
                                RCC_CFGR1_RTCPRE_1)
#define LL_RCC_RTC_HSE_DIV_303 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_3 | RCC_CFGR1_RTCPRE_2 | \
                                RCC_CFGR1_RTCPRE_1 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_304 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_4)
#define LL_RCC_RTC_HSE_DIV_305 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_4 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_306 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_4 | RCC_CFGR1_RTCPRE_1)
#define LL_RCC_RTC_HSE_DIV_307 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_4 | RCC_CFGR1_RTCPRE_1 | \
                                RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_308 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_4 | RCC_CFGR1_RTCPRE_2)
#define LL_RCC_RTC_HSE_DIV_309 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_4 | RCC_CFGR1_RTCPRE_2 | \
                                RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_310 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_4 | RCC_CFGR1_RTCPRE_2 | \
                                RCC_CFGR1_RTCPRE_1)
#define LL_RCC_RTC_HSE_DIV_311 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_4 | RCC_CFGR1_RTCPRE_2 | \
                                RCC_CFGR1_RTCPRE_1 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_312 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_4 | RCC_CFGR1_RTCPRE_3)
#define LL_RCC_RTC_HSE_DIV_313 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_4 | RCC_CFGR1_RTCPRE_3 | \
                                RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_314 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_4 | RCC_CFGR1_RTCPRE_3 | \
                                RCC_CFGR1_RTCPRE_1)
#define LL_RCC_RTC_HSE_DIV_315 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_4 | RCC_CFGR1_RTCPRE_3 | \
                                RCC_CFGR1_RTCPRE_1 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_316 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_4 | RCC_CFGR1_RTCPRE_3 | \
                                RCC_CFGR1_RTCPRE_2)
#define LL_RCC_RTC_HSE_DIV_317 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_4 | RCC_CFGR1_RTCPRE_3 | \
                                RCC_CFGR1_RTCPRE_2 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_318 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_4 | RCC_CFGR1_RTCPRE_3 | \
                                RCC_CFGR1_RTCPRE_2 | RCC_CFGR1_RTCPRE_1)
#define LL_RCC_RTC_HSE_DIV_319 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_4 | RCC_CFGR1_RTCPRE_3 | \
                                RCC_CFGR1_RTCPRE_2 | RCC_CFGR1_RTCPRE_1 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_320 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_6)
#define LL_RCC_RTC_HSE_DIV_321 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_322 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_1)
#define LL_RCC_RTC_HSE_DIV_323 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_1 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_324 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_2)
#define LL_RCC_RTC_HSE_DIV_325 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_2 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_326 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_2 | RCC_CFGR1_RTCPRE_1)
#define LL_RCC_RTC_HSE_DIV_327 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_2 | RCC_CFGR1_RTCPRE_1 | \
                                RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_328 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_3)
#define LL_RCC_RTC_HSE_DIV_329 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_3 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_330 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_3 | RCC_CFGR1_RTCPRE_1)
#define LL_RCC_RTC_HSE_DIV_331 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_3 | RCC_CFGR1_RTCPRE_1 | \
                                RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_332 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_3 | RCC_CFGR1_RTCPRE_2)
#define LL_RCC_RTC_HSE_DIV_333 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_3 | RCC_CFGR1_RTCPRE_2 | \
                                RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_334 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_3 | RCC_CFGR1_RTCPRE_2 | \
                                RCC_CFGR1_RTCPRE_1)
#define LL_RCC_RTC_HSE_DIV_335 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_3 | RCC_CFGR1_RTCPRE_2 | \
                                RCC_CFGR1_RTCPRE_1 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_336 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_4)
#define LL_RCC_RTC_HSE_DIV_337 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_4 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_338 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_4 | RCC_CFGR1_RTCPRE_1)
#define LL_RCC_RTC_HSE_DIV_339 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_4 | RCC_CFGR1_RTCPRE_1 | \
                                RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_340 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_4 | RCC_CFGR1_RTCPRE_2)
#define LL_RCC_RTC_HSE_DIV_341 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_4 | RCC_CFGR1_RTCPRE_2 | \
                                RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_342 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_4 | RCC_CFGR1_RTCPRE_2 | \
                                RCC_CFGR1_RTCPRE_1)
#define LL_RCC_RTC_HSE_DIV_343 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_4 | RCC_CFGR1_RTCPRE_2 | \
                                RCC_CFGR1_RTCPRE_1 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_344 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_4 | RCC_CFGR1_RTCPRE_3)
#define LL_RCC_RTC_HSE_DIV_345 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_4 | RCC_CFGR1_RTCPRE_3 | \
                                RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_346 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_4 | RCC_CFGR1_RTCPRE_3 | \
                                RCC_CFGR1_RTCPRE_1)
#define LL_RCC_RTC_HSE_DIV_347 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_4 | RCC_CFGR1_RTCPRE_3 | \
                                RCC_CFGR1_RTCPRE_1 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_348 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_4 | RCC_CFGR1_RTCPRE_3 | \
                                RCC_CFGR1_RTCPRE_2)
#define LL_RCC_RTC_HSE_DIV_349 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_4 | RCC_CFGR1_RTCPRE_3 | \
                                RCC_CFGR1_RTCPRE_2 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_350 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_4 | RCC_CFGR1_RTCPRE_3 | \
                                RCC_CFGR1_RTCPRE_2 | RCC_CFGR1_RTCPRE_1)
#define LL_RCC_RTC_HSE_DIV_351 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_4 | RCC_CFGR1_RTCPRE_3 | \
                                RCC_CFGR1_RTCPRE_2 | RCC_CFGR1_RTCPRE_1 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_352 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_5)
#define LL_RCC_RTC_HSE_DIV_353 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_354 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_1)
#define LL_RCC_RTC_HSE_DIV_355 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_1 | \
                                RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_356 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_2)
#define LL_RCC_RTC_HSE_DIV_357 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_2 | \
                                RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_358 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_2 | \
                                RCC_CFGR1_RTCPRE_1)
#define LL_RCC_RTC_HSE_DIV_359 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_2 | \
                                RCC_CFGR1_RTCPRE_1 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_360 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_3)
#define LL_RCC_RTC_HSE_DIV_361 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_3 | \
                                RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_362 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_3 | \
                                RCC_CFGR1_RTCPRE_1)
#define LL_RCC_RTC_HSE_DIV_363 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_3 | \
                                RCC_CFGR1_RTCPRE_1 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_364 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_3 | \
                                RCC_CFGR1_RTCPRE_2)
#define LL_RCC_RTC_HSE_DIV_365 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_3 | \
                                RCC_CFGR1_RTCPRE_2 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_366 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_3 | \
                                RCC_CFGR1_RTCPRE_2 | RCC_CFGR1_RTCPRE_1)
#define LL_RCC_RTC_HSE_DIV_367 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_3 | \
                                RCC_CFGR1_RTCPRE_2 | RCC_CFGR1_RTCPRE_1 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_368 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_4)
#define LL_RCC_RTC_HSE_DIV_369 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_4 | \
                                RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_370 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_4 | \
                                RCC_CFGR1_RTCPRE_1)
#define LL_RCC_RTC_HSE_DIV_371 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_4 | \
                                RCC_CFGR1_RTCPRE_1 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_372 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_4 | \
                                RCC_CFGR1_RTCPRE_2)
#define LL_RCC_RTC_HSE_DIV_373 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_4 | \
                                RCC_CFGR1_RTCPRE_2 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_374 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_4 | \
                                RCC_CFGR1_RTCPRE_2 | RCC_CFGR1_RTCPRE_1)
#define LL_RCC_RTC_HSE_DIV_375 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_4 | \
                                RCC_CFGR1_RTCPRE_2 | RCC_CFGR1_RTCPRE_1 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_376 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_4 | \
                                RCC_CFGR1_RTCPRE_3)
#define LL_RCC_RTC_HSE_DIV_377 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_4 | \
                                RCC_CFGR1_RTCPRE_3 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_378 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_4 | \
                                RCC_CFGR1_RTCPRE_3 | RCC_CFGR1_RTCPRE_1)
#define LL_RCC_RTC_HSE_DIV_379 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_4 | \
                                RCC_CFGR1_RTCPRE_3 | RCC_CFGR1_RTCPRE_1 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_380 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_4 | \
                                RCC_CFGR1_RTCPRE_3 | RCC_CFGR1_RTCPRE_2)
#define LL_RCC_RTC_HSE_DIV_381 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_4 | \
                                RCC_CFGR1_RTCPRE_3 | RCC_CFGR1_RTCPRE_2 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_382 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_4 | \
                                RCC_CFGR1_RTCPRE_3 | RCC_CFGR1_RTCPRE_2 | RCC_CFGR1_RTCPRE_1)
#define LL_RCC_RTC_HSE_DIV_383 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_4 | \
                                RCC_CFGR1_RTCPRE_3 | RCC_CFGR1_RTCPRE_2 | RCC_CFGR1_RTCPRE_1 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_384 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_7)
#define LL_RCC_RTC_HSE_DIV_385 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_386 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_1)
#define LL_RCC_RTC_HSE_DIV_387 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_1 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_388 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_2)
#define LL_RCC_RTC_HSE_DIV_389 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_2 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_390 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_2 | RCC_CFGR1_RTCPRE_1)
#define LL_RCC_RTC_HSE_DIV_391 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_2 | RCC_CFGR1_RTCPRE_1 | \
                                RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_392 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_3)
#define LL_RCC_RTC_HSE_DIV_393 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_3 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_394 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_3 | RCC_CFGR1_RTCPRE_1)
#define LL_RCC_RTC_HSE_DIV_395 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_3 | RCC_CFGR1_RTCPRE_1 | \
                                RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_396 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_3 | RCC_CFGR1_RTCPRE_2)
#define LL_RCC_RTC_HSE_DIV_397 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_3 | RCC_CFGR1_RTCPRE_2 | \
                                RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_398 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_3 | RCC_CFGR1_RTCPRE_2 | \
                                RCC_CFGR1_RTCPRE_1)
#define LL_RCC_RTC_HSE_DIV_399 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_3 | RCC_CFGR1_RTCPRE_2 | \
                                RCC_CFGR1_RTCPRE_1 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_400 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_4)
#define LL_RCC_RTC_HSE_DIV_401 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_4 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_402 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_4 | RCC_CFGR1_RTCPRE_1)
#define LL_RCC_RTC_HSE_DIV_403 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_4 | RCC_CFGR1_RTCPRE_1 | \
                                RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_404 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_4 | RCC_CFGR1_RTCPRE_2)
#define LL_RCC_RTC_HSE_DIV_405 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_4 | RCC_CFGR1_RTCPRE_2 | \
                                RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_406 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_4 | RCC_CFGR1_RTCPRE_2 | \
                                RCC_CFGR1_RTCPRE_1)
#define LL_RCC_RTC_HSE_DIV_407 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_4 | RCC_CFGR1_RTCPRE_2 | \
                                RCC_CFGR1_RTCPRE_1 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_408 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_4 | RCC_CFGR1_RTCPRE_3)
#define LL_RCC_RTC_HSE_DIV_409 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_4 | RCC_CFGR1_RTCPRE_3 | \
                                RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_410 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_4 | RCC_CFGR1_RTCPRE_3 | \
                                RCC_CFGR1_RTCPRE_1)
#define LL_RCC_RTC_HSE_DIV_411 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_4 | RCC_CFGR1_RTCPRE_3 | \
                                RCC_CFGR1_RTCPRE_1 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_412 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_4 | RCC_CFGR1_RTCPRE_3 | \
                                RCC_CFGR1_RTCPRE_2)
#define LL_RCC_RTC_HSE_DIV_413 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_4 | RCC_CFGR1_RTCPRE_3 | \
                                RCC_CFGR1_RTCPRE_2 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_414 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_4 | RCC_CFGR1_RTCPRE_3 | \
                                RCC_CFGR1_RTCPRE_2 | RCC_CFGR1_RTCPRE_1)
#define LL_RCC_RTC_HSE_DIV_415 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_4 | RCC_CFGR1_RTCPRE_3 | \
                                RCC_CFGR1_RTCPRE_2 | RCC_CFGR1_RTCPRE_1 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_416 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_5)
#define LL_RCC_RTC_HSE_DIV_417 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_418 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_1)
#define LL_RCC_RTC_HSE_DIV_419 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_1 | \
                                RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_420 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_2)
#define LL_RCC_RTC_HSE_DIV_421 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_2 | \
                                RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_422 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_2 | \
                                RCC_CFGR1_RTCPRE_1)
#define LL_RCC_RTC_HSE_DIV_423 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_2 | \
                                RCC_CFGR1_RTCPRE_1 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_424 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_3)
#define LL_RCC_RTC_HSE_DIV_425 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_3 | \
                                RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_426 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_3 | \
                                RCC_CFGR1_RTCPRE_1)
#define LL_RCC_RTC_HSE_DIV_427 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_3 | \
                                RCC_CFGR1_RTCPRE_1 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_428 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_3 | \
                                RCC_CFGR1_RTCPRE_2)
#define LL_RCC_RTC_HSE_DIV_429 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_3 | \
                                RCC_CFGR1_RTCPRE_2 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_430 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_3 | \
                                RCC_CFGR1_RTCPRE_2 | RCC_CFGR1_RTCPRE_1)
#define LL_RCC_RTC_HSE_DIV_431 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_3 | \
                                RCC_CFGR1_RTCPRE_2 | RCC_CFGR1_RTCPRE_1 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_432 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_4)
#define LL_RCC_RTC_HSE_DIV_433 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_4 | \
                                RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_434 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_4 | \
                                RCC_CFGR1_RTCPRE_1)
#define LL_RCC_RTC_HSE_DIV_435 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_4 | \
                                RCC_CFGR1_RTCPRE_1 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_436 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_4 | \
                                RCC_CFGR1_RTCPRE_2)
#define LL_RCC_RTC_HSE_DIV_437 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_4 | \
                                RCC_CFGR1_RTCPRE_2 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_438 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_4 | \
                                RCC_CFGR1_RTCPRE_2 | RCC_CFGR1_RTCPRE_1)
#define LL_RCC_RTC_HSE_DIV_439 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_4 | \
                                RCC_CFGR1_RTCPRE_2 | RCC_CFGR1_RTCPRE_1 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_440 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_4 | \
                                RCC_CFGR1_RTCPRE_3)
#define LL_RCC_RTC_HSE_DIV_441 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_4 | \
                                RCC_CFGR1_RTCPRE_3 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_442 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_4 | \
                                RCC_CFGR1_RTCPRE_3 | RCC_CFGR1_RTCPRE_1)
#define LL_RCC_RTC_HSE_DIV_443 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_4 | \
                                RCC_CFGR1_RTCPRE_3 | RCC_CFGR1_RTCPRE_1 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_444 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_4 | \
                                RCC_CFGR1_RTCPRE_3 | RCC_CFGR1_RTCPRE_2)
#define LL_RCC_RTC_HSE_DIV_445 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_4 | \
                                RCC_CFGR1_RTCPRE_3 | RCC_CFGR1_RTCPRE_2 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_446 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_4 | \
                                RCC_CFGR1_RTCPRE_3 | RCC_CFGR1_RTCPRE_2 | RCC_CFGR1_RTCPRE_1)
#define LL_RCC_RTC_HSE_DIV_447 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_5 | RCC_CFGR1_RTCPRE_4 | \
                                RCC_CFGR1_RTCPRE_3 | RCC_CFGR1_RTCPRE_2 | RCC_CFGR1_RTCPRE_1 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_448 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_6)
#define LL_RCC_RTC_HSE_DIV_449 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_450 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_1)
#define LL_RCC_RTC_HSE_DIV_451 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_1 | \
                                RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_452 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_2)
#define LL_RCC_RTC_HSE_DIV_453 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_2 | \
                                RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_454 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_2 | \
                                RCC_CFGR1_RTCPRE_1)
#define LL_RCC_RTC_HSE_DIV_455 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_2 | \
                                RCC_CFGR1_RTCPRE_1 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_456 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_3)
#define LL_RCC_RTC_HSE_DIV_457 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_3 | \
                                RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_458 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_3 | \
                                RCC_CFGR1_RTCPRE_1)
#define LL_RCC_RTC_HSE_DIV_459 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_3 | \
                                RCC_CFGR1_RTCPRE_1 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_460 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_3 | \
                                RCC_CFGR1_RTCPRE_2)
#define LL_RCC_RTC_HSE_DIV_461 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_3 | \
                                RCC_CFGR1_RTCPRE_2 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_462 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_3 | \
                                RCC_CFGR1_RTCPRE_2 | RCC_CFGR1_RTCPRE_1)
#define LL_RCC_RTC_HSE_DIV_463 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_3 | \
                                RCC_CFGR1_RTCPRE_2 | RCC_CFGR1_RTCPRE_1 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_464 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_4)
#define LL_RCC_RTC_HSE_DIV_465 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_4 | \
                                RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_466 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_4 | \
                                RCC_CFGR1_RTCPRE_1)
#define LL_RCC_RTC_HSE_DIV_467 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_4 | \
                                RCC_CFGR1_RTCPRE_1 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_468 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_4 | \
                                RCC_CFGR1_RTCPRE_2)
#define LL_RCC_RTC_HSE_DIV_469 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_4 | \
                                RCC_CFGR1_RTCPRE_2 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_470 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_4 | \
                                RCC_CFGR1_RTCPRE_2 | RCC_CFGR1_RTCPRE_1)
#define LL_RCC_RTC_HSE_DIV_471 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_4 | \
                                RCC_CFGR1_RTCPRE_2 | RCC_CFGR1_RTCPRE_1 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_472 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_4 | \
                                RCC_CFGR1_RTCPRE_3)
#define LL_RCC_RTC_HSE_DIV_473 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_4 | \
                                RCC_CFGR1_RTCPRE_3 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_474 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_4 | \
                                RCC_CFGR1_RTCPRE_3 | RCC_CFGR1_RTCPRE_1)
#define LL_RCC_RTC_HSE_DIV_475 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_4 | \
                                RCC_CFGR1_RTCPRE_3 | RCC_CFGR1_RTCPRE_1 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_476 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_4 | \
                                RCC_CFGR1_RTCPRE_3 | RCC_CFGR1_RTCPRE_2)
#define LL_RCC_RTC_HSE_DIV_477 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_4 | \
                                RCC_CFGR1_RTCPRE_3 | RCC_CFGR1_RTCPRE_2 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_478 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_4 | \
                                RCC_CFGR1_RTCPRE_3 | RCC_CFGR1_RTCPRE_2 | RCC_CFGR1_RTCPRE_1)
#define LL_RCC_RTC_HSE_DIV_479 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_4 | \
                                RCC_CFGR1_RTCPRE_3 | RCC_CFGR1_RTCPRE_2 | RCC_CFGR1_RTCPRE_1 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_480 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_5)
#define LL_RCC_RTC_HSE_DIV_481 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_5 | \
                                RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_482 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_5 | \
                                RCC_CFGR1_RTCPRE_1)
#define LL_RCC_RTC_HSE_DIV_483 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_5 | \
                                RCC_CFGR1_RTCPRE_1 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_484 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_5 | \
                                RCC_CFGR1_RTCPRE_2)
#define LL_RCC_RTC_HSE_DIV_485 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_5 | \
                                RCC_CFGR1_RTCPRE_2 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_486 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_5 | \
                                RCC_CFGR1_RTCPRE_2 | RCC_CFGR1_RTCPRE_1)
#define LL_RCC_RTC_HSE_DIV_487 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_5 | \
                                RCC_CFGR1_RTCPRE_2 | RCC_CFGR1_RTCPRE_1 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_488 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_5 | \
                                RCC_CFGR1_RTCPRE_3)
#define LL_RCC_RTC_HSE_DIV_489 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_5 | \
                                RCC_CFGR1_RTCPRE_3 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_490 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_5 | \
                                RCC_CFGR1_RTCPRE_3 | RCC_CFGR1_RTCPRE_1)
#define LL_RCC_RTC_HSE_DIV_491 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_5 | \
                                RCC_CFGR1_RTCPRE_3 | RCC_CFGR1_RTCPRE_1 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_492 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_5 | \
                                RCC_CFGR1_RTCPRE_3 | RCC_CFGR1_RTCPRE_2)
#define LL_RCC_RTC_HSE_DIV_493 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_5 | \
                                RCC_CFGR1_RTCPRE_3 | RCC_CFGR1_RTCPRE_2 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_494 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_5 | \
                                RCC_CFGR1_RTCPRE_3 | RCC_CFGR1_RTCPRE_2 | RCC_CFGR1_RTCPRE_1)
#define LL_RCC_RTC_HSE_DIV_495 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_5 | \
                                RCC_CFGR1_RTCPRE_3 | RCC_CFGR1_RTCPRE_2 | RCC_CFGR1_RTCPRE_1 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_496 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_5 | \
                                RCC_CFGR1_RTCPRE_4)
#define LL_RCC_RTC_HSE_DIV_497 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_5 | \
                                RCC_CFGR1_RTCPRE_4 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_498 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_5 | \
                                RCC_CFGR1_RTCPRE_4 | RCC_CFGR1_RTCPRE_1)
#define LL_RCC_RTC_HSE_DIV_499 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_5 | \
                                RCC_CFGR1_RTCPRE_4 | RCC_CFGR1_RTCPRE_1 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_500 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_5 | \
                                RCC_CFGR1_RTCPRE_4 | RCC_CFGR1_RTCPRE_2)
#define LL_RCC_RTC_HSE_DIV_501 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_5 | \
                                RCC_CFGR1_RTCPRE_4 | RCC_CFGR1_RTCPRE_2 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_502 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_5 | \
                                RCC_CFGR1_RTCPRE_4 | RCC_CFGR1_RTCPRE_2 | RCC_CFGR1_RTCPRE_1)
#define LL_RCC_RTC_HSE_DIV_503 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_5 | \
                                RCC_CFGR1_RTCPRE_4 | RCC_CFGR1_RTCPRE_2 | RCC_CFGR1_RTCPRE_1 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_504 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_5 | \
                                RCC_CFGR1_RTCPRE_4 | RCC_CFGR1_RTCPRE_3)
#define LL_RCC_RTC_HSE_DIV_505 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_5 | \
                                RCC_CFGR1_RTCPRE_4 | RCC_CFGR1_RTCPRE_3 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_506 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_5 | \
                                RCC_CFGR1_RTCPRE_4 | RCC_CFGR1_RTCPRE_3 | RCC_CFGR1_RTCPRE_1)
#define LL_RCC_RTC_HSE_DIV_507 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_5 | \
                                RCC_CFGR1_RTCPRE_4 | RCC_CFGR1_RTCPRE_3 | RCC_CFGR1_RTCPRE_1 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_508 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_5 | \
                                RCC_CFGR1_RTCPRE_4 | RCC_CFGR1_RTCPRE_3 | RCC_CFGR1_RTCPRE_2)
#define LL_RCC_RTC_HSE_DIV_509 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_5 | \
                                RCC_CFGR1_RTCPRE_4 | RCC_CFGR1_RTCPRE_3 | RCC_CFGR1_RTCPRE_2 | RCC_CFGR1_RTCPRE_0)
#define LL_RCC_RTC_HSE_DIV_510 (RCC_CFGR1_RTCPRE_8 | RCC_CFGR1_RTCPRE_7 | RCC_CFGR1_RTCPRE_6 | RCC_CFGR1_RTCPRE_5 | \
                                RCC_CFGR1_RTCPRE_4 | RCC_CFGR1_RTCPRE_3 | RCC_CFGR1_RTCPRE_2 | RCC_CFGR1_RTCPRE_1)
#define LL_RCC_RTC_HSE_DIV_511 RCC_CFGR1_RTCPRE
/**
  * @}
  */

/** @defgroup RCC_LL_EC_USARTx_CLKSOURCE  Peripheral USARTx clock source selection
  * @{
  */
#define LL_RCC_USART1_CLKSOURCE_PCLK2        LL_CLKSOURCE(RCC_OFFSET_CCIPR1, RCC_CCIPR1_USART1SEL_Pos, RCC_CCIPR1_USART1SEL, 0U)                     /*!< PCLK2 clock used as USART1 clock source */
#define LL_RCC_USART1_CLKSOURCE_PSIK         LL_CLKSOURCE(RCC_OFFSET_CCIPR1, RCC_CCIPR1_USART1SEL_Pos, RCC_CCIPR1_USART1SEL, RCC_CCIPR1_USART1SEL_0) /*!< PSIK clock used as USART1 clock source */
#define LL_RCC_USART1_CLKSOURCE_HSIK         LL_CLKSOURCE(RCC_OFFSET_CCIPR1, RCC_CCIPR1_USART1SEL_Pos, RCC_CCIPR1_USART1SEL, RCC_CCIPR1_USART1SEL_1) /*!< HSIK clock used as USART1 clock source */
#define LL_RCC_USART1_CLKSOURCE_LSE          LL_CLKSOURCE(RCC_OFFSET_CCIPR1, RCC_CCIPR1_USART1SEL_Pos, RCC_CCIPR1_USART1SEL, RCC_CCIPR1_USART1SEL)   /*!< LSE clock used as USART1 clock source */

#define LL_RCC_USART2_CLKSOURCE_PCLK1        LL_CLKSOURCE(RCC_OFFSET_CCIPR1, RCC_CCIPR1_USART2SEL_Pos, RCC_CCIPR1_USART2SEL, 0U)                     /*!< PCLK1 clock used as USART2 clock source */
#define LL_RCC_USART2_CLKSOURCE_PSIK         LL_CLKSOURCE(RCC_OFFSET_CCIPR1, RCC_CCIPR1_USART2SEL_Pos, RCC_CCIPR1_USART2SEL, RCC_CCIPR1_USART2SEL_0) /*!< PSIK clock used as USART2 clock source */
#define LL_RCC_USART2_CLKSOURCE_HSIK         LL_CLKSOURCE(RCC_OFFSET_CCIPR1, RCC_CCIPR1_USART2SEL_Pos, RCC_CCIPR1_USART2SEL, RCC_CCIPR1_USART2SEL_1) /*!< HSIK clock used as USART2 clock source */
#define LL_RCC_USART2_CLKSOURCE_LSE          LL_CLKSOURCE(RCC_OFFSET_CCIPR1, RCC_CCIPR1_USART2SEL_Pos, RCC_CCIPR1_USART2SEL, RCC_CCIPR1_USART2SEL)   /*!< LSE clock used as USART2 clock source */

#if defined(USART3)
#define LL_RCC_USART3_CLKSOURCE_PCLK1        LL_CLKSOURCE(RCC_OFFSET_CCIPR1, RCC_CCIPR1_USART3SEL_Pos, RCC_CCIPR1_USART3SEL, 0U)                        /*!< PCLK1 clock used as USART3 clock source */
#define LL_RCC_USART3_CLKSOURCE_PSIK         LL_CLKSOURCE(RCC_OFFSET_CCIPR1, RCC_CCIPR1_USART3SEL_Pos, RCC_CCIPR1_USART3SEL, RCC_CCIPR1_USART3SEL_0)    /*!< PSIK clock used as USART3 clock source */
#define LL_RCC_USART3_CLKSOURCE_HSIK         LL_CLKSOURCE(RCC_OFFSET_CCIPR1, RCC_CCIPR1_USART3SEL_Pos, RCC_CCIPR1_USART3SEL, RCC_CCIPR1_USART3SEL_1)    /*!< HSIK clock used as USART3 clock source */
#define LL_RCC_USART3_CLKSOURCE_LSE          LL_CLKSOURCE(RCC_OFFSET_CCIPR1, RCC_CCIPR1_USART3SEL_Pos, RCC_CCIPR1_USART3SEL, RCC_CCIPR1_USART3SEL)      /*!< LSE clock used as USART3 clock source */

#endif /* USART3 */
#if defined(USART6)
#define LL_RCC_USART6_CLKSOURCE_PCLK1        LL_CLKSOURCE(RCC_OFFSET_CCIPR1, RCC_CCIPR1_USART6SEL_Pos, RCC_CCIPR1_USART6SEL, 0U)                        /*!< PCLK1 clock used as USART6 clock source */
#define LL_RCC_USART6_CLKSOURCE_PSIK         LL_CLKSOURCE(RCC_OFFSET_CCIPR1, RCC_CCIPR1_USART6SEL_Pos, RCC_CCIPR1_USART6SEL, RCC_CCIPR1_USART6SEL_0)    /*!< PSIK clock used as USART6 clock source */
#define LL_RCC_USART6_CLKSOURCE_HSIK         LL_CLKSOURCE(RCC_OFFSET_CCIPR1, RCC_CCIPR1_USART6SEL_Pos, RCC_CCIPR1_USART6SEL, RCC_CCIPR1_USART6SEL_1)    /*!< HSIK clock used as USART6 clock source */
#define LL_RCC_USART6_CLKSOURCE_LSE          LL_CLKSOURCE(RCC_OFFSET_CCIPR1, RCC_CCIPR1_USART6SEL_Pos, RCC_CCIPR1_USART6SEL, RCC_CCIPR1_USART6SEL)      /*!< LSE clock used as USART6 clock source */

#endif /* USART6 */
/**
  * @}
  */ /* End of RCC_LL_EC_USART_CLKSOURCE */

/** @defgroup RCC_LL_EC_UARTx_CLKSOURCE  Peripheral UARTx clock source selection
  * @{
  */
#define LL_RCC_UART4_CLKSOURCE_PCLK1         LL_CLKSOURCE(RCC_OFFSET_CCIPR1, RCC_CCIPR1_UART4SEL_Pos, RCC_CCIPR1_UART4SEL, 0U)                        /*!< PCLK1 clock used as UART4 clock source */
#define LL_RCC_UART4_CLKSOURCE_PSIK          LL_CLKSOURCE(RCC_OFFSET_CCIPR1, RCC_CCIPR1_UART4SEL_Pos, RCC_CCIPR1_UART4SEL, RCC_CCIPR1_UART4SEL_0)     /*!< PSIK clock used as UART4 clock source */
#define LL_RCC_UART4_CLKSOURCE_HSIK          LL_CLKSOURCE(RCC_OFFSET_CCIPR1, RCC_CCIPR1_UART4SEL_Pos, RCC_CCIPR1_UART4SEL, RCC_CCIPR1_UART4SEL_1)     /*!< HSIK clock used as UART4 clock source */
#define LL_RCC_UART4_CLKSOURCE_LSE           LL_CLKSOURCE(RCC_OFFSET_CCIPR1, RCC_CCIPR1_UART4SEL_Pos, RCC_CCIPR1_UART4SEL, RCC_CCIPR1_UART4SEL)       /*!< LSE clock used as UART4 clock source */

#define LL_RCC_UART5_CLKSOURCE_PCLK1         LL_CLKSOURCE(RCC_OFFSET_CCIPR1, RCC_CCIPR1_UART5SEL_Pos, RCC_CCIPR1_UART5SEL, 0U)                        /*!< PCLK1 clock used as UART5 clock source */
#define LL_RCC_UART5_CLKSOURCE_PSIK          LL_CLKSOURCE(RCC_OFFSET_CCIPR1, RCC_CCIPR1_UART5SEL_Pos, RCC_CCIPR1_UART5SEL, RCC_CCIPR1_UART5SEL_0)     /*!< PSIK clock used as UART5 clock source */
#define LL_RCC_UART5_CLKSOURCE_HSIK          LL_CLKSOURCE(RCC_OFFSET_CCIPR1, RCC_CCIPR1_UART5SEL_Pos, RCC_CCIPR1_UART5SEL, RCC_CCIPR1_UART5SEL_1)     /*!< HSIK clock used as UART5 clock source */
#define LL_RCC_UART5_CLKSOURCE_LSE           LL_CLKSOURCE(RCC_OFFSET_CCIPR1, RCC_CCIPR1_UART5SEL_Pos, RCC_CCIPR1_UART5SEL, RCC_CCIPR1_UART5SEL)       /*!< LSE clock used as UART5 clock source */
#if defined(UART7)
#define LL_RCC_UART7_CLKSOURCE_PCLK1         LL_CLKSOURCE(RCC_OFFSET_CCIPR1, RCC_CCIPR1_UART7SEL_Pos, RCC_CCIPR1_UART7SEL, 0U)                        /*!< PCLK1 clock used as UART7 clock source */
#define LL_RCC_UART7_CLKSOURCE_PSIK          LL_CLKSOURCE(RCC_OFFSET_CCIPR1, RCC_CCIPR1_UART7SEL_Pos, RCC_CCIPR1_UART7SEL, RCC_CCIPR1_UART7SEL_0)     /*!< PSIK clock used as UART7 clock source */
#define LL_RCC_UART7_CLKSOURCE_HSIK          LL_CLKSOURCE(RCC_OFFSET_CCIPR1, RCC_CCIPR1_UART7SEL_Pos, RCC_CCIPR1_UART7SEL, RCC_CCIPR1_UART7SEL_1)     /*!< HSIK clock used as UART7 clock source */
#define LL_RCC_UART7_CLKSOURCE_LSE           LL_CLKSOURCE(RCC_OFFSET_CCIPR1, RCC_CCIPR1_UART7SEL_Pos, RCC_CCIPR1_UART7SEL, RCC_CCIPR1_UART7SEL)       /*!< LSE clock used as UART7 clock source */

#endif /* UART7 */
/**
  * @}
  */ /* End of RCC_LL_EC_UART_CLKSOURCE */

/** @defgroup RCC_LL_EC_LPUART_CLKSOURCE  Peripheral LPUART clock source selection
  * @{
  */
#define LL_RCC_LPUART1_CLKSOURCE_PCLK3       0U                      /*!< PCLK3 clock used as LPUART1 clock source */
#define LL_RCC_LPUART1_CLKSOURCE_HSIK        RCC_CCIPR1_LPUART1SEL_0 /*!< HSIK clock used as LPUART1 clock source */
#define LL_RCC_LPUART1_CLKSOURCE_LSE         RCC_CCIPR1_LPUART1SEL_1 /*!< LSE clock used as LPUART1 clock source */
#define LL_RCC_LPUART1_CLKSOURCE_LSI         RCC_CCIPR1_LPUART1SEL   /*!< LSI clock used as LPUART1 clock source */
/**
  * @}
  */ /* End of RCC_LL_EC_LPUART_CLKSOURCE */

/** @defgroup RCC_LL_EC_SPIx_CLKSOURCE  Peripheral SPIx clock source selection
  * @{
  */
#define LL_RCC_SPI1_CLKSOURCE_PCLK2          LL_CLKSOURCE(RCC_OFFSET_CCIPR1, RCC_CCIPR1_SPI1SEL_Pos, RCC_CCIPR1_SPI1SEL, 0U)                    /*!< PCLK2 clock used as SPI1 clock source */
#define LL_RCC_SPI1_CLKSOURCE_PSIK           LL_CLKSOURCE(RCC_OFFSET_CCIPR1, RCC_CCIPR1_SPI1SEL_Pos, RCC_CCIPR1_SPI1SEL, RCC_CCIPR1_SPI1SEL_0)  /*!< PSIK clock used as SPI1 clock source */
#define LL_RCC_SPI1_CLKSOURCE_HSIK           LL_CLKSOURCE(RCC_OFFSET_CCIPR1, RCC_CCIPR1_SPI1SEL_Pos, RCC_CCIPR1_SPI1SEL, RCC_CCIPR1_SPI1SEL_1)  /*!< HSIK clock used as SPI1 clock source */
#define LL_RCC_SPI1_CLKSOURCE_AUDIOCLK       LL_CLKSOURCE(RCC_OFFSET_CCIPR1, RCC_CCIPR1_SPI1SEL_Pos, RCC_CCIPR1_SPI1SEL, RCC_CCIPR1_SPI1SEL)    /*!< AUDIOCLK clock used as SPI1 clock source */

#define LL_RCC_SPI2_CLKSOURCE_PCLK1          LL_CLKSOURCE(RCC_OFFSET_CCIPR1, RCC_CCIPR1_SPI2SEL_Pos, RCC_CCIPR1_SPI2SEL, 0U)                    /*!< PCLK1 clock used as SPI2 clock source */
#define LL_RCC_SPI2_CLKSOURCE_PSIK           LL_CLKSOURCE(RCC_OFFSET_CCIPR1, RCC_CCIPR1_SPI2SEL_Pos, RCC_CCIPR1_SPI2SEL, RCC_CCIPR1_SPI2SEL_0)  /*!< PSIK clock used as SPI2 clock source */
#define LL_RCC_SPI2_CLKSOURCE_HSIK           LL_CLKSOURCE(RCC_OFFSET_CCIPR1, RCC_CCIPR1_SPI2SEL_Pos, RCC_CCIPR1_SPI2SEL, RCC_CCIPR1_SPI2SEL_1)  /*!< HSIK clock used as SPI2 clock source */
#define LL_RCC_SPI2_CLKSOURCE_AUDIOCLK       LL_CLKSOURCE(RCC_OFFSET_CCIPR1, RCC_CCIPR1_SPI2SEL_Pos, RCC_CCIPR1_SPI2SEL, RCC_CCIPR1_SPI2SEL)    /*!< AUDIOCLK clock used as SPI2 clock source */
#if defined(SPI3)
#define LL_RCC_SPI3_CLKSOURCE_PCLK1          LL_CLKSOURCE(RCC_OFFSET_CCIPR1, RCC_CCIPR1_SPI3SEL_Pos, RCC_CCIPR1_SPI3SEL, 0U)                    /*!< PCLK1 clock used as SPI3 clock source */
#define LL_RCC_SPI3_CLKSOURCE_PSIK           LL_CLKSOURCE(RCC_OFFSET_CCIPR1, RCC_CCIPR1_SPI3SEL_Pos, RCC_CCIPR1_SPI3SEL, RCC_CCIPR1_SPI3SEL_0)  /*!< PSIK clock used as SPI3 clock source */
#define LL_RCC_SPI3_CLKSOURCE_HSIK           LL_CLKSOURCE(RCC_OFFSET_CCIPR1, RCC_CCIPR1_SPI3SEL_Pos, RCC_CCIPR1_SPI3SEL, RCC_CCIPR1_SPI3SEL_1)  /*!< HSIK clock used as SPI3 clock source */
#define LL_RCC_SPI3_CLKSOURCE_AUDIOCLK       LL_CLKSOURCE(RCC_OFFSET_CCIPR1, RCC_CCIPR1_SPI3SEL_Pos, RCC_CCIPR1_SPI3SEL, RCC_CCIPR1_SPI3SEL)    /*!< AUDIOCLK clock used as SPI3 clock source */

#endif /* SPI3 */
/**
  * @}
  */ /* End of RCC_LL_EC_SPI_CLKSOURCE */

#if defined(FDCAN1)
/** @defgroup RCC_LL_EC_FDCAN_CLKSOURCE  Peripheral FDCAN clock source selection
  * @{
  */
#define LL_RCC_FDCAN_CLKSOURCE_PCLK1        0U                     /*!< PCLK1 clock used as FDCAN clock source */
#define LL_RCC_FDCAN_CLKSOURCE_PSIS         RCC_CCIPR1_FDCANSEL_0  /*!< PSIS clock used as FDCAN clock source */
#define LL_RCC_FDCAN_CLKSOURCE_PSIK         RCC_CCIPR1_FDCANSEL_1  /*!< PSIK clock used as FDCAN clock source */
#define LL_RCC_FDCAN_CLKSOURCE_HSE          RCC_CCIPR1_FDCANSEL    /*!< HSE clock used as FDCAN clock source */
/**
  * @}
  */ /* End of RCC_LL_EC_FDCAN_CLKSOURCE */

#endif /* FDCAN1 */
/** @defgroup RCC_LL_EC_I2Cx_CLKSOURCE  Peripheral I2Cx clock source selection
  * @{
  */
#define LL_RCC_I2C1_CLKSOURCE_PCLK1          LL_CLKSOURCE(RCC_OFFSET_CCIPR2, RCC_CCIPR2_I2C1SEL_Pos, RCC_CCIPR2_I2C1SEL, 0U)                   /*!< PCLK1 clock used as I2C1 clock source */
#define LL_RCC_I2C1_CLKSOURCE_PSIK           LL_CLKSOURCE(RCC_OFFSET_CCIPR2, RCC_CCIPR2_I2C1SEL_Pos, RCC_CCIPR2_I2C1SEL, RCC_CCIPR2_I2C1SEL_0) /*!< PSIK clock used as I2C1 clock source */
#define LL_RCC_I2C1_CLKSOURCE_HSIK           LL_CLKSOURCE(RCC_OFFSET_CCIPR2, RCC_CCIPR2_I2C1SEL_Pos, RCC_CCIPR2_I2C1SEL, RCC_CCIPR2_I2C1SEL_1) /*!< HSIK clock used as I2C1 clock source */
#if defined(I2C2)
#define LL_RCC_I2C2_CLKSOURCE_PCLK1          LL_CLKSOURCE(RCC_OFFSET_CCIPR2, RCC_CCIPR2_I2C2SEL_Pos, RCC_CCIPR2_I2C2SEL, 0U)                    /*!< PCLK1 clock used as I2C2 clock source */
#define LL_RCC_I2C2_CLKSOURCE_PSIK           LL_CLKSOURCE(RCC_OFFSET_CCIPR2, RCC_CCIPR2_I2C2SEL_Pos, RCC_CCIPR2_I2C2SEL,  RCC_CCIPR2_I2C2SEL_0) /*!< PSIK clock used as I2C2 clock source */
#define LL_RCC_I2C2_CLKSOURCE_HSIK           LL_CLKSOURCE(RCC_OFFSET_CCIPR2, RCC_CCIPR2_I2C2SEL_Pos, RCC_CCIPR2_I2C2SEL,  RCC_CCIPR2_I2C2SEL_1) /*!< HSIK clock used as I2C2 clock source */

#endif /* I2C2 */
/**
  * @}
  */ /* End of RCC_LL_EC_I2C_CLKSOURCE */

/** @defgroup RCC_LL_EC_I3C_CLKSOURCE  Peripheral I3C clock source selection
  * @{
  */
#define LL_RCC_I3C1_CLKSOURCE_PCLK1          0U                   /*!< PCLK1 clock used as I3C1 clock source */
#define LL_RCC_I3C1_CLKSOURCE_PSIK           RCC_CCIPR2_I3C1SEL_0 /*!< PSIK clock used as I3C1 clock source */
#define LL_RCC_I3C1_CLKSOURCE_HSIK           RCC_CCIPR2_I3C1SEL_1 /*!< HSIK clock used as I3C1 clock source */
/**
  * @}
  */ /* End of RCC_LL_EC_I3C_CLKSOURCE */

/** @defgroup RCC_LL_EC_ADCDAC_CLKSOURCE  Peripheral ADCDAC clock source selection
  * @{
  */
#define LL_RCC_ADCDAC_CLKSOURCE_HCLK         0U                     /*!< HCLK clock used as ADCDAC clock source */
#define LL_RCC_ADCDAC_CLKSOURCE_PSIS         RCC_CCIPR2_ADCDACSEL_0 /*!< PSIS clock used as ADCDAC clock source */
#define LL_RCC_ADCDAC_CLKSOURCE_PSIK         RCC_CCIPR2_ADCDACSEL_1 /*!< PSIK clock used as ADCDAC clock source */
#define LL_RCC_ADCDAC_CLKSOURCE_HSIK         RCC_CCIPR2_ADCDACSEL   /*!< HSIK clock used as ADCDAC clock source */
/**
  * @}
  */ /* End of RCC_LL_EC_ADCDAC_CLKSOURCE */


/** @defgroup RCC_LL_EC_ADCDAC_PRESCALER  ADCDAC prescaler
  * @{
  */
#define LL_RCC_ADCDAC_PRESCALER_1               0U                                                                              /*!< ADC and DAC kernel clock not divided */
#define LL_RCC_ADCDAC_PRESCALER_2               RCC_CCIPR2_ADCDACPRE_0                                                          /*!< ADC and DAC kernel clock divided by 2 */
#define LL_RCC_ADCDAC_PRESCALER_4               RCC_CCIPR2_ADCDACPRE_1                                                          /*!< ADC and DAC kernel clock divided by 4 */
#define LL_RCC_ADCDAC_PRESCALER_8               (RCC_CCIPR2_ADCDACPRE_1 | RCC_CCIPR2_ADCDACPRE_0)                               /*!< ADC and DAC kernel clock divided by 8 */
#define LL_RCC_ADCDAC_PRESCALER_16              (RCC_CCIPR2_ADCDACPRE_2)                                                        /*!< ADC and DAC kernel clock divided by 16 */
#define LL_RCC_ADCDAC_PRESCALER_32              (RCC_CCIPR2_ADCDACPRE_2 | RCC_CCIPR2_ADCDACPRE_0)                               /*!< ADC and DAC kernel clock divided by 32 */
#define LL_RCC_ADCDAC_PRESCALER_64              (RCC_CCIPR2_ADCDACPRE_2 | RCC_CCIPR2_ADCDACPRE_1)                               /*!< ADC and DAC kernel clock divided by 64 */
#define LL_RCC_ADCDAC_PRESCALER_128             (RCC_CCIPR2_ADCDACPRE_2 | RCC_CCIPR2_ADCDACPRE_1 | RCC_CCIPR2_ADCDACPRE_0)      /*!< ADC and DAC kernel clock divided by 128 */
/**
  * @}
  */ /* End of RCC_LL_EC_ADCDAC_PRESCALER */

/** @defgroup RCC_LL_EC_DAC1_CLKSOURCE  Peripheral DAC1 clock source selection
  * @{
  */
#define LL_RCC_DAC1SH_CLKSOURCE_LSE           0U                     /*!< LSE clock used as DAC1 clock source */
#define LL_RCC_DAC1SH_CLKSOURCE_LSI           RCC_CCIPR2_DACSEL      /*!< LSI clock used as DAC1 clock source */
/**
  * @}
  */ /* End of RCC_LL_EC_DAC1_CLKSOURCE */

/** @defgroup RCC_LL_EC_LPTIM_CLKSOURCE  Peripheral LPTIM clock source selection
  * @{
  */
#define LL_RCC_LPTIM1_CLKSOURCE_PCLK3        0U                     /*!< PCLK3 clock used as LPTIM1 clock source */
#define LL_RCC_LPTIM1_CLKSOURCE_HSIK         RCC_CCIPR2_LPTIM1SEL_0 /*!< HSIK clock used as LPTIM1 clock source */
#define LL_RCC_LPTIM1_CLKSOURCE_LSE          RCC_CCIPR2_LPTIM1SEL_1 /*!< LSE clock used as LPTIM1 clock source */
#define LL_RCC_LPTIM1_CLKSOURCE_LSI          RCC_CCIPR2_LPTIM1SEL   /*!< LSI clock used as LPTIM1 clock source */
/**
  * @}
  */ /* End of RCC_LL_EC_LPTIM_CLKSOURCE */

/** @defgroup RCC_LL_EC_CK_CLKSOURCE  Peripheral CK clock source selection
  * @{
  */
#define LL_RCC_CK48_NONE                     0U                     /*!< CK48 clock source disable */
#define LL_RCC_CK48_CLKSOURCE_PSI_DIV_3      RCC_CCIPR2_CK48SEL_0   /*!< PSI_DIV_3 clock used as CK48 clock source */
#define LL_RCC_CK48_CLKSOURCE_HSI_DIV_3      RCC_CCIPR2_CK48SEL_1   /*!< HSI_DIV_3 clock used as CK48 clock source */
#define LL_RCC_CK48_CLKSOURCE_HSE            RCC_CCIPR2_CK48SEL     /*!< HSE clock used as CK48 clock source */
/**
  * @}
  */ /* End of RCC_LL_EC_CK_CLKSOURCE */
#if defined(XSPI1)
/** @defgroup RCC_LL_EC_XSPI_CLKSOURCE  Peripheral XSPI clock source selection
  * @{
  */
#define LL_RCC_XSPI1_CLKSOURCE_HCLK        0U                        /*!< HCLK clock used as XSPI1 clock source */
#define LL_RCC_XSPI1_CLKSOURCE_PSIK        RCC_CCIPR3_XSPI1SEL_0     /*!< PSIK clock used as XSPI1 clock source */
#define LL_RCC_XSPI1_CLKSOURCE_HSIK        RCC_CCIPR3_XSPI1SEL_1     /*!< HSIK clock used as XSPI1 clock source */
/**
  * @}
  */ /* End of RCC_LL_EC_XSPI_CLKSOURCE */

#endif /* XSPI*/
#if defined(ETH)
/** @defgroup RCC_LL_EC_ETH_CLKSOURCE  Peripheral ETH clock source selection
  * @{
  */
#define LL_RCC_ETHREF_CLKSOURCE_RMII        LL_CLKSOURCE(RCC_OFFSET_CCIPR3, RCC_CCIPR3_ETHREFCLKSEL_Pos, RCC_CCIPR3_ETHREFCLKSEL, 0U)                          /*!< PHY clock used as ETH REF clock source */
#define LL_RCC_ETHREF_CLKSOURCE_FB          LL_CLKSOURCE(RCC_OFFSET_CCIPR3, RCC_CCIPR3_ETHREFCLKSEL_Pos, RCC_CCIPR3_ETHREFCLKSEL, RCC_CCIPR3_ETHREFCLKSEL)     /*!< Feedback clock used as ETH REF clock source */

#define LL_RCC_ETHPTP_CLKSOURCE_NONE        LL_CLKSOURCE(RCC_OFFSET_CCIPR3, RCC_CCIPR3_ETHPTPCLKSEL_Pos, RCC_CCIPR3_ETHPTPCLKSEL, 0U)                          /*!< ETH PTP clock source disable */
#define LL_RCC_ETHPTP_CLKSOURCE_HCLK        LL_CLKSOURCE(RCC_OFFSET_CCIPR3, RCC_CCIPR3_ETHPTPCLKSEL_Pos, RCC_CCIPR3_ETHPTPCLKSEL, RCC_CCIPR3_ETHPTPCLKSEL_0)   /*!< HCLK clock used as ETH PTP clock source */
#define LL_RCC_ETHPTP_CLKSOURCE_PSIS        LL_CLKSOURCE(RCC_OFFSET_CCIPR3, RCC_CCIPR3_ETHPTPCLKSEL_Pos, RCC_CCIPR3_ETHPTPCLKSEL, RCC_CCIPR3_ETHPTPCLKSEL_1)   /*!< PSIS clock used as ETH PTP clock source */
#define LL_RCC_ETHPTP_CLKSOURCE_PSIK        LL_CLKSOURCE(RCC_OFFSET_CCIPR3, RCC_CCIPR3_ETHPTPCLKSEL_Pos, RCC_CCIPR3_ETHPTPCLKSEL, RCC_CCIPR3_ETHPTPCLKSEL)     /*!< PSIK clock used as ETH PTP clock source */

#define LL_RCC_ETH_CLKSOURCE_NONE           LL_CLKSOURCE(RCC_OFFSET_CCIPR3, RCC_CCIPR3_ETHCLKSEL_Pos, RCC_CCIPR3_ETHCLKSEL, 0U)                                /*!< ETH clock source disable */
#define LL_RCC_ETH_CLKSOURCE_PSIS           LL_CLKSOURCE(RCC_OFFSET_CCIPR3, RCC_CCIPR3_ETHCLKSEL_Pos, RCC_CCIPR3_ETHCLKSEL, RCC_CCIPR3_ETHCLKSEL_0)            /*!< PSIS clock used as ETH clock source */
#define LL_RCC_ETH_CLKSOURCE_PSIK           LL_CLKSOURCE(RCC_OFFSET_CCIPR3, RCC_CCIPR3_ETHCLKSEL_Pos, RCC_CCIPR3_ETHCLKSEL, RCC_CCIPR3_ETHCLKSEL_1)            /*!< PSIK clock used as ETH clock source */
#define LL_RCC_ETH_CLKSOURCE_HSE            LL_CLKSOURCE(RCC_OFFSET_CCIPR3, RCC_CCIPR3_ETHCLKSEL_Pos, RCC_CCIPR3_ETHCLKSEL, RCC_CCIPR3_ETHCLKSEL)              /*!< HSE clock used as ETH clock source */
/**
  * @}
  */ /* End of RCC_LL_EC_ETH_CLKSOURCE */

/** @defgroup RCC_LL_EC_ETH_DIV  ETH prescaler
  * @{
  */
#define LL_RCC_ETH_DIV_1               0U                                  /*!< ETH clock not divided  */
#define LL_RCC_ETH_DIV_2               RCC_CCIPR3_ETHCLKDIVSEL_0           /*!< ETH clock divided by 2 */
#define LL_RCC_ETH_DIV_4               RCC_CCIPR3_ETHCLKDIVSEL_1           /*!< ETH clock divided by 4 */
/**
  * @}
  */ /* End of RCC_LL_EC_ETH_DIV */

/** @defgroup RCC_LL_EC_ETHPTP_DIV  ETHPTP prescaler
  * @{
  */
#define LL_RCC_ETHPTP_DIV_1             0U                                                                                                              /*!< ETH PTP clock not divided  */
#define LL_RCC_ETHPTP_DIV_2             RCC_CCIPR3_ETHPTPDIVSEL_0                                                                                       /*!< ETH PTP clock divided by 2 */
#define LL_RCC_ETHPTP_DIV_3             RCC_CCIPR3_ETHPTPDIVSEL_1                                                                                       /*!< ETH PTP clock divided by 3 */
#define LL_RCC_ETHPTP_DIV_4             (RCC_CCIPR3_ETHPTPDIVSEL_1 | RCC_CCIPR3_ETHPTPDIVSEL_0)                                                         /*!< ETH PTP clock divided by 4 */
#define LL_RCC_ETHPTP_DIV_5             (RCC_CCIPR3_ETHPTPDIVSEL_2)                                                                                     /*!< ETH PTP clock divided by 5 */
#define LL_RCC_ETHPTP_DIV_6             (RCC_CCIPR3_ETHPTPDIVSEL_2 | RCC_CCIPR3_ETHPTPDIVSEL_0)                                                         /*!< ETH PTP clock divided by 6 */
#define LL_RCC_ETHPTP_DIV_7             (RCC_CCIPR3_ETHPTPDIVSEL_2 | RCC_CCIPR3_ETHPTPDIVSEL_1)                                                         /*!< ETH PTP clock divided by 7 */
#define LL_RCC_ETHPTP_DIV_8             (RCC_CCIPR3_ETHPTPDIVSEL_2 | RCC_CCIPR3_ETHPTPDIVSEL_1 | RCC_CCIPR3_ETHPTPDIVSEL_0)                             /*!< ETH PTP clock divided by 8 */
#define LL_RCC_ETHPTP_DIV_9             (RCC_CCIPR3_ETHPTPDIVSEL_3)                                                                                     /*!< ETH PTP clock divided by 9 */
#define LL_RCC_ETHPTP_DIV_10            (RCC_CCIPR3_ETHPTPDIVSEL_3 | RCC_CCIPR3_ETHPTPDIVSEL_0)                                                         /*!< ETH PTP clock divided by 10 */
#define LL_RCC_ETHPTP_DIV_11            (RCC_CCIPR3_ETHPTPDIVSEL_3 | RCC_CCIPR3_ETHPTPDIVSEL_1)                                                         /*!< ETH PTP clock divided by 11 */
#define LL_RCC_ETHPTP_DIV_12            (RCC_CCIPR3_ETHPTPDIVSEL_3 | RCC_CCIPR3_ETHPTPDIVSEL_1 | RCC_CCIPR3_ETHPTPDIVSEL_0)                             /*!< ETH PTP clock divided by 12 */
#define LL_RCC_ETHPTP_DIV_13            (RCC_CCIPR3_ETHPTPDIVSEL_3 | RCC_CCIPR3_ETHPTPDIVSEL_2)                                                         /*!< ETH PTP clock divided by 13 */
#define LL_RCC_ETHPTP_DIV_14            (RCC_CCIPR3_ETHPTPDIVSEL_3 | RCC_CCIPR3_ETHPTPDIVSEL_2| RCC_CCIPR3_ETHPTPDIVSEL_0)                              /*!< ETH PTP clock divided by 14 */
#define LL_RCC_ETHPTP_DIV_15            (RCC_CCIPR3_ETHPTPDIVSEL_3 | RCC_CCIPR3_ETHPTPDIVSEL_2 | RCC_CCIPR3_ETHPTPDIVSEL_1)                             /*!< ETH PTP clock divided by 15 */
#define LL_RCC_ETHPTP_DIV_16            (RCC_CCIPR3_ETHPTPDIVSEL_3 | RCC_CCIPR3_ETHPTPDIVSEL_2 | RCC_CCIPR3_ETHPTPDIVSEL_1| RCC_CCIPR3_ETHPTPDIVSEL_0)  /*!< ETH PTP clock divided by 16 */
/**
  * @}
  */ /* End of RCC_LL_EC_ETHPTP_DIV */

#endif /* ETH */
/** @defgroup RCC_LL_EC_USARTx  Peripheral USARTx get clock source
  * @{
  */
#define LL_RCC_USART1_CLKSOURCE              LL_CLKSOURCE(RCC_OFFSET_CCIPR1, RCC_CCIPR1_USART1SEL_Pos, RCC_CCIPR1_USART1SEL, 0U) /*!< USART1 Clock source selection */
#define LL_RCC_USART2_CLKSOURCE              LL_CLKSOURCE(RCC_OFFSET_CCIPR1, RCC_CCIPR1_USART2SEL_Pos, RCC_CCIPR1_USART2SEL, 0U) /*!< USART2 Clock source selection */
#if defined(USART3)
#define LL_RCC_USART3_CLKSOURCE              LL_CLKSOURCE(RCC_OFFSET_CCIPR1, RCC_CCIPR1_USART3SEL_Pos, RCC_CCIPR1_USART3SEL, 0U) /*!< USART3 Clock source selection */
#endif /* USART3 */
#if defined(USART6)
#define LL_RCC_USART6_CLKSOURCE              LL_CLKSOURCE(RCC_OFFSET_CCIPR1, RCC_CCIPR1_USART6SEL_Pos, RCC_CCIPR1_USART6SEL, 0U) /*!< USART6 Clock source selection */
#endif /* USART6 */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_UARTx  Peripheral UARTx get clock source
  * @{
  */
#define LL_RCC_UART4_CLKSOURCE               LL_CLKSOURCE(RCC_OFFSET_CCIPR1, RCC_CCIPR1_UART4SEL_Pos, RCC_CCIPR1_UART4SEL, 0U) /*!< UART4 Clock source selection */
#define LL_RCC_UART5_CLKSOURCE               LL_CLKSOURCE(RCC_OFFSET_CCIPR1, RCC_CCIPR1_UART5SEL_Pos, RCC_CCIPR1_UART5SEL, 0U) /*!< UART5 Clock source selection */
#if defined(UART7)
#define LL_RCC_UART7_CLKSOURCE               LL_CLKSOURCE(RCC_OFFSET_CCIPR1, RCC_CCIPR1_UART7SEL_Pos, RCC_CCIPR1_UART7SEL, 0U) /*!< UART7 Clock source selection */
#endif /* UART7 */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_LPUART  Peripheral LPUART get clock source
  * @{
  */
#define LL_RCC_LPUART1_CLKSOURCE             RCC_CCIPR1_LPUART1SEL /*!< LPUART1 Clock source selection */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_SPIx  Peripheral SPIx get clock source
  * @{
  */
#define LL_RCC_SPI1_CLKSOURCE                LL_CLKSOURCE(RCC_OFFSET_CCIPR1, RCC_CCIPR1_SPI1SEL_Pos, RCC_CCIPR1_SPI1SEL, 0U) /*!< SPI1 Clock source selection */
#define LL_RCC_SPI2_CLKSOURCE                LL_CLKSOURCE(RCC_OFFSET_CCIPR1, RCC_CCIPR1_SPI2SEL_Pos, RCC_CCIPR1_SPI2SEL, 0U) /*!< SPI2 Clock source selection */
#if defined(SPI3)
#define LL_RCC_SPI3_CLKSOURCE                LL_CLKSOURCE(RCC_OFFSET_CCIPR1, RCC_CCIPR1_SPI3SEL_Pos, RCC_CCIPR1_SPI3SEL, 0U) /*!< SPI3 Clock source selection */
#endif /* SPI3 */
/**
  * @}
  */
#if defined(FDCAN1)

/** @defgroup RCC_LL_EC_FDCAN  Peripheral FDCAN get clock source
  * @{
  */
#define LL_RCC_FDCAN_CLKSOURCE              RCC_CCIPR1_FDCANSEL /*!< FDCAN Clock source selection */
/**
  * @}
  */

#endif /* FDCAN1 */
/** @defgroup RCC_LL_EC_I2Cx  Peripheral I2Cx get clock source
  * @{
  */
#define LL_RCC_I2C1_CLKSOURCE                LL_CLKSOURCE(RCC_OFFSET_CCIPR2, RCC_CCIPR2_I2C1SEL_Pos, RCC_CCIPR2_I2C1SEL, 0U) /*!< I2C1 Clock source selection */
#if defined(I2C2)
#define LL_RCC_I2C2_CLKSOURCE                LL_CLKSOURCE(RCC_OFFSET_CCIPR2, RCC_CCIPR2_I2C2SEL_Pos, RCC_CCIPR2_I2C2SEL, 0U) /*!< I2C2 Clock source selection */
#endif /* I2C2 */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_I3C  Peripheral I3C get clock source
  * @{
  */
#define LL_RCC_I3C1_CLKSOURCE                RCC_CCIPR2_I3C1SEL /*!< I3C1 Clock source selection */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_ADCDAC  Peripheral ADCDAC get clock source
  * @{
  */
#define LL_RCC_ADCDAC_CLKSOURCE              RCC_CCIPR2_ADCDACSEL /*!< ADCDAC Clock source selection */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_DAC1  Peripheral DAC1 get clock source
  * @{
  */
#define LL_RCC_DAC1_CLKSOURCE                 RCC_CCIPR2_DACSEL /*!< DAC1 Clock source selection */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_LPTIM  Peripheral LPTIM get clock source
  * @{
  */
#define LL_RCC_LPTIM1_CLKSOURCE              RCC_CCIPR2_LPTIM1SEL /*!< LPTIM1 Clock source selection */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_CK  Peripheral CK get clock source
  * @{
  */
#define LL_RCC_CK48_CLKSOURCE                RCC_CCIPR2_CK48SEL /*!< CK48 Clock source selection */
/**
  * @}
  */
#if defined(XSPI1)
/** @defgroup RCC_LL_EC_XSPI  Peripheral CK get clock source
  * @{
  */
#define LL_RCC_XSPI1_CLKSOURCE                RCC_CCIPR3_XSPI1SEL /*!< XSPI1 Clock source selection */
/**
  * @}
  */

#endif /* XSPI1 */
#if defined(ETH)
/** @defgroup RCC_LL_EC_ETH  Peripheral CK get clock source
  * @{
  */
#define LL_RCC_ETHREF_CLKSOURCE                LL_CLKSOURCE(RCC_OFFSET_CCIPR3, RCC_CCIPR3_ETHREFCLKSEL_Pos, RCC_CCIPR3_ETHREFCLKSEL, 0U) /*!< ETHREF Clock source selection */
#define LL_RCC_ETHPTP_CLKSOURCE                LL_CLKSOURCE(RCC_OFFSET_CCIPR3, RCC_CCIPR3_ETHPTPCLKSEL_Pos, RCC_CCIPR3_ETHPTPCLKSEL, 0U) /*!< ETHPTP Clock source selection */
#define LL_RCC_ETH_CLKSOURCE                   LL_CLKSOURCE(RCC_OFFSET_CCIPR3, RCC_CCIPR3_ETHCLKSEL_Pos, RCC_CCIPR3_ETHCLKSEL, 0U)       /*!< ETH Clock source selection */
/**
  * @}
  */

#endif /* ETH */
/** @defgroup RCC_LL_FLAGS RCC Flags
  * @{
  */
#define LL_RCC_IT_LSIRDY     RCC_CIFR_LSIRDYF      /*!< LSI ready interrupt flag */
#define LL_RCC_IT_LSERDY     RCC_CIFR_LSERDYF      /*!< LSE ready interrupt flag */
#define LL_RCC_IT_HSIRDY     RCC_CIFR_HSISRDYF     /*!< HSIS ready interrupt flag */
#define LL_RCC_IT_HSIDIV3RDY RCC_CIFR_HSIDIV3RDYF  /*!< HSIDIV3 ready interrupt flag */
#define LL_RCC_IT_HSIKRDY    RCC_CIFR_HSIKRDYF     /*!< HSIK ready interrupt flag */
#define LL_RCC_IT_PSIRDY     RCC_CIFR_PSISRDYF     /*!< PSIS ready interrupt flag */
#define LL_RCC_IT_PSIDIV3RDY RCC_CIFR_PSIDIV3RDYF  /*!< PSIDIV3 ready interrupt flag */
#define LL_RCC_IT_PSIKRDY    RCC_CIFR_PSIKRDYF     /*!< PSIK ready interrupt flag */
#define LL_RCC_IT_HSERDY     RCC_CIFR_HSERDYF      /*!< HSE ready interrupt flag */
#define LL_RCC_IT_HSECSS     RCC_CIFR_HSECSSF      /*!< HSE clock security system interrupt flag */
#define LL_RCC_IT_LSECSS     RCC_CIFR_LSECSSF      /*!< LSE clock security system interrupt flag */
/**
  * @}
  */

/**
  * @}
  */ /* End of RCC_LL_Exported_Constants */

/* Exported macro ------------------------------------------------------------*/
/** @defgroup RCC_LL_Exported_Macros RCC Exported Macros
  * @{
  */

/** @defgroup RCC_LL_EM_WRITE_READ Common Write and read registers Macros
  * @{
  */

/**
  * @brief  Write a value in RCC register
  * @param  reg Register to be written
  * @param  value Value to be written in the register
  */
#define LL_RCC_WRITE_REG(reg, value) WRITE_REG(RCC->reg, (value))

/**
  * @brief  Read a value in RCC register
  * @param  reg Register to be read
  * @retval Register value
  */
#define LL_RCC_READ_REG(reg) READ_REG(RCC->reg)
/**
  * @}
  */ /* End of RCC_LL_EM_WRITE_READ */

/** @defgroup RCC_LL_EM_CALC_FREQ Calculate frequencies
  * @{
  */

/**
  * @brief  Helper macro to calculate the HCLK frequency
  * @param  sysclk_freq SYSCLK frequency (based on HSIS/HSIDIV3/HSE/PSIS)
  * @param  ahb_prescaler This parameter can be one of the following values:
  *         @arg @ref LL_RCC_HCLK_PRESCALER_1
  *         @arg @ref LL_RCC_HCLK_PRESCALER_2
  *         @arg @ref LL_RCC_HCLK_PRESCALER_4
  *         @arg @ref LL_RCC_HCLK_PRESCALER_8
  *         @arg @ref LL_RCC_HCLK_PRESCALER_16
  *         @arg @ref LL_RCC_HCLK_PRESCALER_64
  *         @arg @ref LL_RCC_HCLK_PRESCALER_128
  *         @arg @ref LL_RCC_HCLK_PRESCALER_256
  *         @arg @ref LL_RCC_HCLK_PRESCALER_512
  * @retval HCLK clock frequency (in Hz)
  */
#define LL_RCC_CALC_HCLK_FREQ(sysclk_freq, ahb_prescaler) ((sysclk_freq) >> \
                                                           AHBPrescTable[((ahb_prescaler)& RCC_CFGR2_HPRE) \
                                                                         >>  RCC_CFGR2_HPRE_Pos])

/**
  * @brief  Helper macro to calculate the PCLK1 frequency (ABP1)
  * @param  hclk_freq HCLK frequency
  * @param  apb1_prescaler This parameter can be one of the following values:
  *         @arg @ref LL_RCC_APB1_PRESCALER_1
  *         @arg @ref LL_RCC_APB1_PRESCALER_2
  *         @arg @ref LL_RCC_APB1_PRESCALER_4
  *         @arg @ref LL_RCC_APB1_PRESCALER_8
  *         @arg @ref LL_RCC_APB1_PRESCALER_16
  * @retval PCLK1 clock frequency (in Hz)
  */
#define LL_RCC_CALC_PCLK1_FREQ(hclk_freq, apb1_prescaler) ((hclk_freq) >> \
                                                           (APBPrescTable[((apb1_prescaler)& \
                                                                           RCC_CFGR2_PPRE1) >>  RCC_CFGR2_PPRE1_Pos]))

/**
  * @brief  Helper macro to calculate the PCLK2 frequency (ABP2)
  * @param  hclk_freq HCLK frequency
  * @param  apb2_prescaler This parameter can be one of the following values:
  *         @arg @ref LL_RCC_APB2_PRESCALER_1
  *         @arg @ref LL_RCC_APB2_PRESCALER_2
  *         @arg @ref LL_RCC_APB2_PRESCALER_4
  *         @arg @ref LL_RCC_APB2_PRESCALER_8
  *         @arg @ref LL_RCC_APB2_PRESCALER_16
  * @retval PCLK2 clock frequency (in Hz)
  */
#define LL_RCC_CALC_PCLK2_FREQ(hclk_freq, apb2_prescaler) ((hclk_freq) >> \
                                                           (APBPrescTable[((apb2_prescaler)& \
                                                                           RCC_CFGR2_PPRE2) >>  RCC_CFGR2_PPRE2_Pos]))

/**
  * @brief  Helper macro to calculate the PCLK3 frequency (ABP3)
  * @param  hclk_freq HCLK frequency
  * @param  apb3_prescaler This parameter can be one of the following values:
  *         @arg @ref LL_RCC_APB3_PRESCALER_1
  *         @arg @ref LL_RCC_APB3_PRESCALER_2
  *         @arg @ref LL_RCC_APB3_PRESCALER_4
  *         @arg @ref LL_RCC_APB3_PRESCALER_8
  *         @arg @ref LL_RCC_APB3_PRESCALER_16
  * @retval PCLK3 clock frequency (in Hz)
  */
#define LL_RCC_CALC_PCLK3_FREQ(hclk_freq, apb3_prescaler) ((hclk_freq) >> \
                                                           (APBPrescTable[((apb3_prescaler)& \
                                                                           RCC_CFGR2_PPRE3) >>  RCC_CFGR2_PPRE3_Pos]))

/**
  * @}
  */ /* End of RCC_LL_EM_CALC_FREQ */

/**
  * @}
  */ /* End of RCC_LL_Exported_Macros */

/* Exported functions --------------------------------------------------------*/
/** @defgroup RCC_LL_Exported_Functions RCC Exported Functions
  * @{
  */

/** @defgroup RCC_LL_EF_LSI LSI
  * @{
  */

/**
  * @brief  Enable LSI oscillator (LSI ON)
  * @rmtoll
  *  RTCCR         LSION        LL_RCC_LSI_Enable
  */
__STATIC_INLINE void LL_RCC_LSI_Enable(void)
{
  SET_BIT(RCC->RTCCR, RCC_RTCCR_LSION);
}

/**
  * @brief  Disable LSI oscillator (LSI ON)
  * @rmtoll
  *  RTCCR         LSION        LL_RCC_LSI_Disable
  */
__STATIC_INLINE void LL_RCC_LSI_Disable(void)
{
  CLEAR_BIT(RCC->RTCCR, RCC_RTCCR_LSION);
}

/**
  * @brief  Check if LSI oscillator is ready
  * @rmtoll
  *  RTCCR         LSIRDY         LL_RCC_LSI_IsReady
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_LSI_IsReady(void)
{
  return ((READ_BIT(RCC->RTCCR, RCC_RTCCR_LSIRDY) == RCC_RTCCR_LSIRDY) ? 1UL : 0UL);
}

/**
  * @brief  Check if LSI oscillator is enabled
  * @rmtoll
  *  RTCCR         LSION         LL_RCC_LSI_IsEnabled
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_LSI_IsEnabled(void)
{
  return ((READ_BIT(RCC->RTCCR, RCC_RTCCR_LSION) == RCC_RTCCR_LSION) ? 1UL : 0UL);
}

/**
  * @}
  */ /* End of RCC_LL_EF_LSI */

/** @defgroup RCC_LL_EF_LSE LSE
  * @{
  */

/**
  * @brief  Enable LSE oscillatord (LSE ON)
  * @rmtoll
  *  RTCCR         LSEON        LL_RCC_LSE_Enable
  */
__STATIC_INLINE void LL_RCC_LSE_Enable(void)
{
  SET_BIT(RCC->RTCCR, RCC_RTCCR_LSEON);
}

/**
  * @brief  Disable LSE oscillatord (LSE ON)
  * @rmtoll
  *  RTCCR         LSEON        LL_RCC_LSE_Disable
  */
__STATIC_INLINE void LL_RCC_LSE_Disable(void)
{
  CLEAR_BIT(RCC->RTCCR, RCC_RTCCR_LSEON);
}

/**
  * @brief  Check if LSE oscillator is ready
  * @rmtoll
  *  RTCCR         LSERDY         LL_RCC_LSE_IsReady
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_LSE_IsReady(void)
{
  return ((READ_BIT(RCC->RTCCR, RCC_RTCCR_LSERDY) == RCC_RTCCR_LSERDY) ? 1UL : 0UL);
}

/**
  * @brief  Check if LSE oscillator is enabled
  * @rmtoll
  *  RTCCR         LSEON         LL_RCC_LSE_IsEnabled
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_LSE_IsEnabled(void)
{
  return ((READ_BIT(RCC->RTCCR, RCC_RTCCR_LSEON) == RCC_RTCCR_LSEON) ? 1UL : 0UL);
}

/**
  * @brief  Enable external clock source (LSE bypass).
  * @rmtoll
  *  RTCCR         LSEBYP        LL_RCC_LSE_EnableBypass
  */
__STATIC_INLINE void LL_RCC_LSE_EnableBypass(void)
{
  SET_BIT(RCC->RTCCR, RCC_RTCCR_LSEBYP);
}

/**
  * @brief  Configure LSE external oscillator in bypass
  * @rmtoll
  *  RTCCR         LSEBYP        LL_RCC_LSE_ConfigBypass \n
  *  RTCCR         LSEEXT        LL_RCC_LSE_ConfigBypass
  * @param  lse_mode This parameter can be one of the following values:
  *         @arg @ref LL_RCC_LSE_ANALOG_MODE
  *         @arg @ref LL_RCC_LSE_DIGITAL_MODE
  */
__STATIC_INLINE void LL_RCC_LSE_ConfigBypass(uint32_t lse_mode)
{
  MODIFY_REG(RCC->RTCCR, RCC_RTCCR_LSEBYP | RCC_RTCCR_LSEEXT, RCC_RTCCR_LSEBYP | lse_mode);
}

/**
  * @brief  Disable external clock source (LSE bypass).
  * @rmtoll
  *  RTCCR         LSEBYP        LL_RCC_LSE_DisableBypass
  */
__STATIC_INLINE void LL_RCC_LSE_DisableBypass(void)
{
  CLEAR_BIT(RCC->RTCCR, RCC_RTCCR_LSEBYP);
}

/**
  * @brief  Check if LSE oscillator is bypassed
  * @rmtoll
  *  RTCCR         LSEBYP        LL_RCC_LSE_IsBypassed
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_LSE_IsBypassed(void)
{
  return ((READ_BIT(RCC->RTCCR, RCC_RTCCR_LSEBYP) == RCC_RTCCR_LSEBYP) ? 1UL : 0UL);
}

/**
  * @brief  Set external LSE clock mode
  * @rmtoll
  *  RTCCR         LSEEXT        LL_RCC_LSE_SetClockMode
  * @param  lse_mode This parameter can be one of the following values:
  *         @arg @ref LL_RCC_LSE_ANALOG_MODE
  *         @arg @ref LL_RCC_LSE_DIGITAL_MODE
  * @note This bit can be written only if the LSE oscillator is disabled.
  */
__STATIC_INLINE void LL_RCC_LSE_SetClockMode(uint32_t lse_mode)
{
  MODIFY_REG(RCC->RTCCR, RCC_RTCCR_LSEEXT, lse_mode);
}

/**
  * @brief  Get External LSE clock mode
  * @rmtoll
  *  RTCCR         LSEEXT        LL_RCC_LSE_GetClockMode
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_LSE_ANALOG_MODE
  *         @arg @ref LL_RCC_LSE_DIGITAL_MODE
  */
__STATIC_INLINE uint32_t LL_RCC_LSE_GetClockMode(void)
{
  return (uint32_t)(READ_BIT(RCC->RTCCR, RCC_RTCCR_LSEEXT));
}

/**
  * @brief  Set LSE oscillator drive capability
  * @rmtoll
  *  RTCCR         LSEDRV        LL_RCC_LSE_SetDriveCapability
  * @param  lse_drive This parameter can be one of the following values:
  *         @arg @ref LL_RCC_LSEDRIVE_LOW
  *         @arg @ref LL_RCC_LSEDRIVE_MEDIUMLOW
  *         @arg @ref LL_RCC_LSEDRIVE_MEDIUMHIGH
  *         @arg @ref LL_RCC_LSEDRIVE_HIGH
  * @note The oscillator is in Xtal mode when it is not in bypass mode.
  */
__STATIC_INLINE void LL_RCC_LSE_SetDriveCapability(uint32_t lse_drive)
{
  MODIFY_REG(RCC->RTCCR, RCC_RTCCR_LSEDRV, lse_drive);
}

/**
  * @brief  Get LSE oscillator drive capability
  * @rmtoll
  *  RTCCR         LSEDRV        LL_RCC_LSE_GetDriveCapability
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_LSEDRIVE_LOW
  *         @arg @ref LL_RCC_LSEDRIVE_MEDIUMLOW
  *         @arg @ref LL_RCC_LSEDRIVE_MEDIUMHIGH
  *         @arg @ref LL_RCC_LSEDRIVE_HIGH
  */
__STATIC_INLINE uint32_t LL_RCC_LSE_GetDriveCapability(void)
{
  return (uint32_t)(READ_BIT(RCC->RTCCR, RCC_RTCCR_LSEDRV));
}

/**
  * @brief  Enable LSE clock security system (LSE CSSON)
  * @rmtoll
  *  RTCCR         LSECSSON        LL_RCC_LSE_EnableCSS
  */
__STATIC_INLINE void LL_RCC_LSE_EnableCSS(void)
{
  SET_BIT(RCC->RTCCR, RCC_RTCCR_LSECSSON);
}

/**
  * @brief  Disable LSE clock security system (LSE CSSON)
  * @rmtoll
  *  RTCCR         LSECSSON        LL_RCC_LSE_DisableCSS
  */
__STATIC_INLINE void LL_RCC_LSE_DisableCSS(void)
{
  CLEAR_BIT(RCC->RTCCR, RCC_RTCCR_LSECSSON);
}

/**
  * @brief  Check if CSS on LSE failure Detection
  * @rmtoll
  *  RTCCR         LSECSSD       LL_RCC_LSE_IsCSSDetected
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_LSE_IsCSSDetected(void)
{
  return ((READ_BIT(RCC->RTCCR, RCC_RTCCR_LSECSSD) == RCC_RTCCR_LSECSSD) ? 1UL : 0UL);
}

/**
  * @}
  */ /* End of RCC_LL_EF_LSE */

/** @defgroup RCC_LL_EF_HSI HSI
  * @{
  */
/**
  * @brief  Enable HSIS clock (HSIS ON)
  * @rmtoll
  *  CR1           HSISON        LL_RCC_HSI_Enable
  */
__STATIC_INLINE void LL_RCC_HSIS_Enable(void)
{
  SET_BIT(RCC->CR1, RCC_CR1_HSISON);
}

/**
  * @brief  Disable HSIS clock (HSIS ON)
  * @rmtoll
  *  CR1           HSISON        LL_RCC_HSI_Disable
  */
__STATIC_INLINE void LL_RCC_HSIS_Disable(void)
{
  CLEAR_BIT(RCC->CR1, RCC_CR1_HSISON);
}

/**
  * @brief  Check if HSIS oscillator is enabled
  * @rmtoll
  *  CR            HSISON        LL_RCC_HSIS_IsEnabled
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_HSIS_IsEnabled(void)
{
  return ((READ_BIT(RCC->CR1, RCC_CR1_HSISON) == RCC_CR1_HSISON) ? 1UL : 0UL);
}

/**
  * @brief  Enable HSIDIV3 clock (HSIDIV3 ON)
  * @rmtoll
  *  CR1           HSIDIV3ON        LL_RCC_HSIDIV3_Enable
  */
__STATIC_INLINE void LL_RCC_HSIDIV3_Enable(void)
{
  SET_BIT(RCC->CR1, RCC_CR1_HSIDIV3ON);
}

/**
  * @brief  Disable HSIDIV3 clock (HSIDIV3 ON)
  * @rmtoll
  *  CR1           HSIDIV3ON        LL_RCC_HSIDIV3_Disable
  */
__STATIC_INLINE void LL_RCC_HSIDIV3_Disable(void)
{
  CLEAR_BIT(RCC->CR1, RCC_CR1_HSIDIV3ON);
}

/**
  * @brief  Check if HSIDIV3 oscillator is enabled
  * @rmtoll
  *  CR            HSIDIV3ON        LL_RCC_HSIDIV3_IsEnabled
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_HSIDIV3_IsEnabled(void)
{
  return ((READ_BIT(RCC->CR1, RCC_CR1_HSIDIV3ON) == RCC_CR1_HSIDIV3ON) ? 1UL : 0UL);
}

/**
  * @brief  Enable HSIK clock (HSIK ON)
  * @rmtoll
  *  CR1           HSIKON        LL_RCC_HSIK_Enable
  */
__STATIC_INLINE void LL_RCC_HSIK_Enable(void)
{
  SET_BIT(RCC->CR1, RCC_CR1_HSIKON);
}

/**
  * @brief  Disable HSIK clock (HSIK ON)
  * @rmtoll
  *  CR1           HSIKON        LL_RCC_HSIK_Disable
  */
__STATIC_INLINE void LL_RCC_HSIK_Disable(void)
{
  CLEAR_BIT(RCC->CR1, RCC_CR1_HSIKON);
}

/**
  * @brief  Check if HSIK oscillator is enabled
  * @rmtoll
  *  CR            HSIK        LL_RCC_HSIK_IsEnabled
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_HSIK_IsEnabled(void)
{
  return ((READ_BIT(RCC->CR1, RCC_CR1_HSIKON) == RCC_CR1_HSIKON) ? 1UL : 0UL);
}

/**
  * @brief  Enable HSI clock used as kernel clock for peripheral in Stop mode
  * @rmtoll
  *  CR1           HSIKERON        LL_RCC_HSI_EnableInStopMode
  */
__STATIC_INLINE void LL_RCC_HSI_EnableInStopMode(void)
{
  SET_BIT(RCC->CR1, RCC_CR1_HSIKERON);
}

/**
  * @brief  Disable HSI clock used as kernel clock for peripheral in Stop mode
  * @rmtoll
  *  CR1           HSIKERON        LL_RCC_HSI_DisableInStopMode
  */
__STATIC_INLINE void LL_RCC_HSI_DisableInStopMode(void)
{
  CLEAR_BIT(RCC->CR1, RCC_CR1_HSIKERON);
}

/**
  * @brief  Check if HSI clock used as kernel clock for peripheral is enabled in stop mode
  * @rmtoll
  *  CR1          HSIKERON        LL_RCC_HSI_IsEnabledInStopMode
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_HSI_IsEnabledInStopMode(void)
{
  return ((READ_BIT(RCC->CR1, RCC_CR1_HSIKERON) == RCC_CR1_HSIKERON) ? 1UL : 0UL);
}

/**
  * @brief  Check if HSIS clock is ready
  * @rmtoll
  *  CR1         HSISRDY         LL_RCC_HSIS_IsReady
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_HSIS_IsReady(void)
{
  return ((READ_BIT(RCC->CR1, RCC_CR1_HSISRDY) == RCC_CR1_HSISRDY) ? 1UL : 0UL);
}

/**
  * @brief  Check if HSIDIV3 clock is ready
  * @rmtoll
  *  CR1         HSIDIV3RDY         LL_RCC_HSIDIV3_IsReady
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_HSIDIV3_IsReady(void)
{
  return ((READ_BIT(RCC->CR1, RCC_CR1_HSIDIV3RDY) == RCC_CR1_HSIDIV3RDY) ? 1UL : 0UL);
}

/**
  * @brief  Check if HSIK clock is ready
  * @rmtoll
  *  CR1         HSIKRDY         LL_RCC_HSIK_IsReady
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_HSIK_IsReady(void)
{
  return ((READ_BIT(RCC->CR1, RCC_CR1_HSIKRDY) == RCC_CR1_HSIKRDY) ? 1UL : 0UL);
}

/**
  * @brief  Set HSIK clock out divider factor (HSIK DIV)
  * @rmtoll
  *  CR2         HSIKDIV         LL_RCC_HSIK_SetDivider
  * @param  value This parameter can be one of the following values:
  *         @arg @ref LL_RCC_HSIK_DIV_1
  *         @arg @ref LL_RCC_HSIK_DIV_1_5
  *         @arg @ref LL_RCC_HSIK_DIV_2
  *         @arg @ref LL_RCC_HSIK_DIV_2_5
  *         @arg @ref LL_RCC_HSIK_DIV_3
  *         @arg @ref LL_RCC_HSIK_DIV_3_5
  *         @arg @ref LL_RCC_HSIK_DIV_4
  *         @arg @ref LL_RCC_HSIK_DIV_4_5
  *         @arg @ref LL_RCC_HSIK_DIV_5
  *         @arg @ref LL_RCC_HSIK_DIV_5_5
  *         @arg @ref LL_RCC_HSIK_DIV_6
  *         @arg @ref LL_RCC_HSIK_DIV_6_5
  *         @arg @ref LL_RCC_HSIK_DIV_7
  *         @arg @ref LL_RCC_HSIK_DIV_7_5
  *         @arg @ref LL_RCC_HSIK_DIV_8
  */
__STATIC_INLINE void LL_RCC_HSIK_SetDivider(uint32_t value)
{
  MODIFY_REG(RCC->CR2, RCC_CR2_HSIKDIV, value);
}

/**
  * @brief  Get HSIK clock out divider factor (HSIK DIV)
  * @rmtoll
  *  CR2         HSIKDIV         LL_RCC_HSIK_GetDivider
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_HSIK_DIV_1
  *         @arg @ref LL_RCC_HSIK_DIV_1_5
  *         @arg @ref LL_RCC_HSIK_DIV_2
  *         @arg @ref LL_RCC_HSIK_DIV_2_5
  *         @arg @ref LL_RCC_HSIK_DIV_3
  *         @arg @ref LL_RCC_HSIK_DIV_3_5
  *         @arg @ref LL_RCC_HSIK_DIV_4
  *         @arg @ref LL_RCC_HSIK_DIV_4_5
  *         @arg @ref LL_RCC_HSIK_DIV_5
  *         @arg @ref LL_RCC_HSIK_DIV_5_5
  *         @arg @ref LL_RCC_HSIK_DIV_6
  *         @arg @ref LL_RCC_HSIK_DIV_6_5
  *         @arg @ref LL_RCC_HSIK_DIV_7
  *         @arg @ref LL_RCC_HSIK_DIV_7_5
  *         @arg @ref LL_RCC_HSIK_DIV_8
   */
__STATIC_INLINE uint32_t LL_RCC_HSIK_GetDivider(void)
{
  return (READ_BIT(RCC->CR2, RCC_CR2_HSIKDIV));
}

/**
  * @}
  */ /* End of RCC_LL_EF_HSI */

/** @defgroup RCC_LL_EF_PSI PSI
  * @{
  */
/**
  * @brief  Enable PSIS clock (PSIS ON)
  * @rmtoll
  *  CR1           PSISON        LL_RCC_PSI_Enable
  */
__STATIC_INLINE void LL_RCC_PSIS_Enable(void)
{
  SET_BIT(RCC->CR1, RCC_CR1_PSISON);
}

/**
  * @brief  Disable PSIS clock (PSIS ON)
  * @rmtoll
  *  CR1           PSISON        LL_RCC_PSI_Disable
  */
__STATIC_INLINE void LL_RCC_PSIS_Disable(void)
{
  CLEAR_BIT(RCC->CR1, RCC_CR1_PSISON);
}

/**
  * @brief  Check if PSIS oscillator is enabled
  * @rmtoll
  *  CR            PSISON        LL_RCC_PSIS_IsEnabled
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_PSIS_IsEnabled(void)
{
  return ((READ_BIT(RCC->CR1, RCC_CR1_PSISON) == RCC_CR1_PSISON) ? 1UL : 0UL);
}

/**
  * @brief  Enable PSIDIV3 clock (PSIDIV3 ON)
  * @rmtoll
  *  CR1           PSIDIV3ON        LL_RCC_PSIDIV3_Enable
  */
__STATIC_INLINE void LL_RCC_PSIDIV3_Enable(void)
{
  SET_BIT(RCC->CR1, RCC_CR1_PSIDIV3ON);
}

/**
  * @brief  Disable PSIDIV3 clock (PSIDIV3 ON)
  * @rmtoll
  *  CR1           PSIDIV3ON        LL_RCC_PSIDIV3_Disable
  */
__STATIC_INLINE void LL_RCC_PSIDIV3_Disable(void)
{
  CLEAR_BIT(RCC->CR1, RCC_CR1_PSIDIV3ON);
}

/**
  * @brief  Check if PSIDIV3ON oscillator is enabled
  * @rmtoll
  *  CR            PSIDIV3ON        LL_RCC_PSIDIV3_IsEnabled
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_PSIDIV3_IsEnabled(void)
{
  return ((READ_BIT(RCC->CR1, RCC_CR1_PSIDIV3ON) == RCC_CR1_PSIDIV3ON) ? 1UL : 0UL);
}

/**
  * @brief  Enable PSIK clock (PSIK ON)
  * @rmtoll
  *  CR1           PSIKON        LL_RCC_PSIK_Enable
  */
__STATIC_INLINE void LL_RCC_PSIK_Enable(void)
{
  SET_BIT(RCC->CR1, RCC_CR1_PSIKON);
}

/**
  * @brief  Disable PSIK clock (PSIK ON)
  * @rmtoll
  *  CR1           PSIKON        LL_RCC_PSIK_Disable
  */
__STATIC_INLINE void LL_RCC_PSIK_Disable(void)
{
  CLEAR_BIT(RCC->CR1, RCC_CR1_PSIKON);
}

/**
  * @brief  Check if PSIKON oscillator is enabled
  * @rmtoll
  *  CR            PSIKON        LL_RCC_PSIK_IsEnabled
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_PSIK_IsEnabled(void)
{
  return ((READ_BIT(RCC->CR1, RCC_CR1_PSIKON) == RCC_CR1_PSIKON) ? 1UL : 0UL);
}

/**
  * @brief  Enable PSI clock in Stop mode
  * @rmtoll
  *  CR1           PSIKERON        LL_RCC_PSI_EnableInStopMode
  */
__STATIC_INLINE void LL_RCC_PSI_EnableInStopMode(void)
{
  SET_BIT(RCC->CR1, RCC_CR1_PSIKERON);
}

/**
  * @brief  Disable PSI clock in Stop mode
  * @rmtoll
  *  CR1           PSIKERON        LL_RCC_PSI_DisableInStopMode
  */
__STATIC_INLINE void LL_RCC_PSI_DisableInStopMode(void)
{
  CLEAR_BIT(RCC->CR1, RCC_CR1_PSIKERON);
}

/**
  * @brief  Check if PSI is enabled in stop mode
  * @rmtoll
  *  CR1           PSIKERON        LL_RCC_PSI_IsEnabledInStopMode
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_PSI_IsEnabledInStopMode(void)
{
  return ((READ_BIT(RCC->CR1, RCC_CR1_PSIKERON) == RCC_CR1_PSIKERON) ? 1UL : 0UL);
}

/**
  * @brief  Check if PSIS clock is ready
  * @rmtoll
  *  CR1         PSISRDY         LL_RCC_PSIS_IsReady
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_PSIS_IsReady(void)
{
  return ((READ_BIT(RCC->CR1, RCC_CR1_PSISRDY) == RCC_CR1_PSISRDY) ? 1UL : 0UL);
}

/**
  * @brief  Check if PSIDIV3 clock is ready
  * @rmtoll
  *  CR1         PSIDIV3RDY         LL_RCC_PSIDIV3_IsReady
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_PSIDIV3_IsReady(void)
{
  return ((READ_BIT(RCC->CR1, RCC_CR1_PSIDIV3RDY) == RCC_CR1_PSIDIV3RDY) ? 1UL : 0UL);
}

/**
  * @brief  Check if PSIK clock is ready
  * @rmtoll
  *  CR1         PSIKRDY         LL_RCC_PSIK_IsReady
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_PSIK_IsReady(void)
{
  return ((READ_BIT(RCC->CR1, RCC_CR1_PSIKRDY) == RCC_CR1_PSIKRDY) ? 1UL : 0UL);
}

/**
  * @brief  Set PSIK clock out divider factor (PSIK DIV)
  * @rmtoll
  *  CR2         PSIKDIV         LL_RCC_PSIK_SetDivider
  * @param  value This parameter can be one of the following values:
  *         @arg @ref LL_RCC_PSIK_DIV_1
  *         @arg @ref LL_RCC_PSIK_DIV_1_5
  *         @arg @ref LL_RCC_PSIK_DIV_2
  *         @arg @ref LL_RCC_PSIK_DIV_2_5
  *         @arg @ref LL_RCC_PSIK_DIV_3
  *         @arg @ref LL_RCC_PSIK_DIV_3_5
  *         @arg @ref LL_RCC_PSIK_DIV_4
  *         @arg @ref LL_RCC_PSIK_DIV_4_5
  *         @arg @ref LL_RCC_PSIK_DIV_5
  *         @arg @ref LL_RCC_PSIK_DIV_5_5
  *         @arg @ref LL_RCC_PSIK_DIV_6
  *         @arg @ref LL_RCC_PSIK_DIV_6_5
  *         @arg @ref LL_RCC_PSIK_DIV_7
  *         @arg @ref LL_RCC_PSIK_DIV_7_5
  *         @arg @ref LL_RCC_PSIK_DIV_8
  */
__STATIC_INLINE void LL_RCC_PSIK_SetDivider(uint32_t value)
{
  MODIFY_REG(RCC->CR2, RCC_CR2_PSIKDIV, value);
}

/**
  * @brief  Get PSIK clock out divider factor (PSIK DIV)
  * @rmtoll
  *  CR2         PSIKDIV         LL_RCC_PSIK_GetDivider
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_PSIK_DIV_1
  *         @arg @ref LL_RCC_PSIK_DIV_1_5
  *         @arg @ref LL_RCC_PSIK_DIV_2
  *         @arg @ref LL_RCC_PSIK_DIV_2_5
  *         @arg @ref LL_RCC_PSIK_DIV_3
  *         @arg @ref LL_RCC_PSIK_DIV_3_5
  *         @arg @ref LL_RCC_PSIK_DIV_4
  *         @arg @ref LL_RCC_PSIK_DIV_4_5
  *         @arg @ref LL_RCC_PSIK_DIV_5
  *         @arg @ref LL_RCC_PSIK_DIV_5_5
  *         @arg @ref LL_RCC_PSIK_DIV_6
  *         @arg @ref LL_RCC_PSIK_DIV_6_5
  *         @arg @ref LL_RCC_PSIK_DIV_7
  *         @arg @ref LL_RCC_PSIK_DIV_7_5
  *         @arg @ref LL_RCC_PSIK_DIV_8
   */
__STATIC_INLINE uint32_t LL_RCC_PSIK_GetDivider(void)
{
  return (READ_BIT(RCC->CR2, RCC_CR2_PSIKDIV));
}

/**
  * @brief  Configure the PSI target frequency output
  * @rmtoll
  *  CR2         PSIFREQ         LL_RCC_SetPSIFreqOutput
  * @param  freq This parameter can be one of the following values:
  *         @arg @ref LL_RCC_PSIFREQ_100
  *         @arg @ref LL_RCC_PSIFREQ_144
  *         @arg @ref LL_RCC_PSIFREQ_160
  */
__STATIC_INLINE void LL_RCC_SetPSIFreqOutput(uint32_t freq)
{
  MODIFY_REG(RCC->CR2, RCC_CR2_PSIFREQ, freq);
}

/**
  * @brief  Get the PSI target frequency output
  * @rmtoll
  *  CR2         PSIFREQ         LL_RCC_GetPSIFreqOutput
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_PSIFREQ_100
  *         @arg @ref LL_RCC_PSIFREQ_144
  *         @arg @ref LL_RCC_PSIFREQ_160
  */
__STATIC_INLINE uint32_t LL_RCC_GetPSIFreqOutput(void)
{
  return (uint32_t)(READ_BIT(RCC->CR2, RCC_CR2_PSIFREQ));
}

/**
  * @brief  Configure the PSI ref clock frequency selection
  * @rmtoll
  *  CR2         PSIREF         LL_RCC_SetPSIRef
  * @param  source This parameter can be one of the following values:
  *         @arg @ref LL_RCC_PSIREF_32K768
  *         @arg @ref LL_RCC_PSIREF_8M
  *         @arg @ref LL_RCC_PSIREF_16M
  *         @arg @ref LL_RCC_PSIREF_24M
  *         @arg @ref LL_RCC_PSIREF_25M
  *         @arg @ref LL_RCC_PSIREF_32M
  *         @arg @ref LL_RCC_PSIREF_48M
  *         @arg @ref LL_RCC_PSIREF_50M
  */
__STATIC_INLINE void LL_RCC_SetPSIRef(uint32_t source)
{
  MODIFY_REG(RCC->CR2, RCC_CR2_PSIREF, source);
}

/**
  * @brief  Get the PSI ref clock frequency selection
  * @rmtoll
  *  CR2         PSIREF         LL_RCC_GetPSIRef
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_PSIREF_32K768
  *         @arg @ref LL_RCC_PSIREF_8M
  *         @arg @ref LL_RCC_PSIREF_16M
  *         @arg @ref LL_RCC_PSIREF_24M
  *         @arg @ref LL_RCC_PSIREF_25M
  *         @arg @ref LL_RCC_PSIREF_32M
  *         @arg @ref LL_RCC_PSIREF_48M
  *         @arg @ref LL_RCC_PSIREF_50M
  */
__STATIC_INLINE uint32_t LL_RCC_GetPSIRef(void)
{
  return (uint32_t)(READ_BIT(RCC->CR2, RCC_CR2_PSIREF));
}

/**
  * @brief  Configure the PSI clock source
  * @rmtoll
  *  CR2         PSIREFSRC         LL_RCC_SetPSIClkSource
  * @param  ref This parameter can be one of the following values:
  *         @arg @ref LL_RCC_PSISOURCE_HSE
  *         @arg @ref LL_RCC_PSISOURCE_LSE
  *         @arg @ref LL_RCC_PSISOURCE_HSIDIV18
  */
__STATIC_INLINE void LL_RCC_SetPSIClkSource(uint32_t ref)
{
  MODIFY_REG(RCC->CR2, RCC_CR2_PSIREFSRC, ref);
}

/**
  * @brief  Get the PSI clock source
  * @rmtoll
  *  CR2         PSIREFSRC         LL_RCC_GetPSIClkSource
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_PSISOURCE_HSE
  *         @arg @ref LL_RCC_PSISOURCE_LSE
  *         @arg @ref LL_RCC_PSISOURCE_HSIDIV18
  */
__STATIC_INLINE uint32_t LL_RCC_GetPSIClkSource(void)
{
  return (uint32_t)(READ_BIT(RCC->CR2, RCC_CR2_PSIREFSRC));
}

/**
  * @brief  Configure the PSI clock
  * @rmtoll
  *  CR2         PSIFREQ           LL_RCC_ConfigPSI
  *  CR2         PSIREF            LL_RCC_ConfigPSI
  *  CR2         PSIREFSRC         LL_RCC_ConfigPSI
  * @param  freq This parameter can be one of the following values:
  *         @arg @ref LL_RCC_PSIFREQ_100
  *         @arg @ref LL_RCC_PSIFREQ_144
  *         @arg @ref LL_RCC_PSIFREQ_160
  * @param  source This parameter can be one of the following values:
  *         @arg @ref LL_RCC_PSIREF_32K768
  *         @arg @ref LL_RCC_PSIREF_8M
  *         @arg @ref LL_RCC_PSIREF_16M
  *         @arg @ref LL_RCC_PSIREF_24M
  *         @arg @ref LL_RCC_PSIREF_25M
  *         @arg @ref LL_RCC_PSIREF_32M
  *         @arg @ref LL_RCC_PSIREF_48M
  *         @arg @ref LL_RCC_PSIREF_50M
  * @param  ref This parameter can be one of the following values:
  *         @arg @ref LL_RCC_PSISOURCE_HSE
  *         @arg @ref LL_RCC_PSISOURCE_LSE
  *         @arg @ref LL_RCC_PSISOURCE_HSIDIV18
  */
__STATIC_INLINE void LL_RCC_ConfigPSI(uint32_t freq, uint32_t ref, uint32_t source)
{
  MODIFY_REG(RCC->CR2, (RCC_CR2_PSIFREQ | RCC_CR2_PSIREF | RCC_CR2_PSIREFSRC), (freq | ref | source));
}

/**
  * @brief  Get PSI configuration
  * @rmtoll
  *  CR2         PSIFREQ           LL_RCC_GetConfigPSI
  *  CR2         PSIREF            LL_RCC_GetConfigPSI
  *  CR2         PSIREFSRC         LL_RCC_GetConfigPSI
  * @param  p_freq Pointer on LL_RCC_PSIFREQ
  * @param  p_ref Pointer on LL_RCC_PSIREF
  * @param  p_source Pointer on LL_RCC_PSISOURCE
  */
__STATIC_INLINE void LL_RCC_GetConfigPSI(uint32_t *p_freq, uint32_t *p_ref, uint32_t *p_source)
{
  const volatile uint32_t Reg = READ_REG(RCC->CR2);

  *p_freq = (uint32_t)(Reg & RCC_CR2_PSIFREQ);
  *p_ref = (uint32_t)(Reg & RCC_CR2_PSIREF);
  *p_source = (uint32_t)(Reg & RCC_CR2_PSIREFSRC);
}

/**
  * @}
  */ /* End of RCC_LL_EF_PSI */

/** @defgroup RCC_LL_EF_HSE HSE
  * @{
  */

/**
  * @brief  Enable HSE clock (HSE ON)
  * @rmtoll
  *  CR1           HSEON        LL_RCC_HSE_Enable
  */
__STATIC_INLINE void LL_RCC_HSE_Enable(void)
{
  SET_BIT(RCC->CR1, RCC_CR1_HSEON);
}

/**
  * @brief  Disable HSE clock (HSE ON)
  * @rmtoll
  *  CR1           HSEON        LL_RCC_HSE_Disable
  */
__STATIC_INLINE void LL_RCC_HSE_Disable(void)
{
  CLEAR_BIT(RCC->CR1, RCC_CR1_HSEON);
}

/**
  * @brief  Check if HSE oscillator is enabled
  * @rmtoll
  *  CR            HSEON        LL_RCC_HSE_IsEnabled
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_HSE_IsEnabled(void)
{
  return ((READ_BIT(RCC->CR1, RCC_CR1_HSEON) == RCC_CR1_HSEON) ? 1UL : 0UL);
}

/**
  * @brief  Check if HSE clock is ready
  * @rmtoll
  *  CR1         HSERDY         LL_RCC_HSE_IsReady
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_HSE_IsReady(void)
{
  return ((READ_BIT(RCC->CR1, RCC_CR1_HSERDY) == RCC_CR1_HSERDY) ? 1UL : 0UL);
}

/**
  * @brief  Set external HSE clock mode
  * @rmtoll
  *  CR1        HSEEXT        LL_RCC_HSE_SetClockMode
  * @param  hse_mode This parameter can be one of the following values:
  *         @arg @ref LL_RCC_HSE_ANALOG_MODE
  *         @arg @ref LL_RCC_HSE_DIGITAL_MODE
  * @note This bit can be written only if the HSE oscillator is disabled.
  */
__STATIC_INLINE void LL_RCC_HSE_SetClockMode(uint32_t hse_mode)
{
  MODIFY_REG(RCC->CR1, RCC_CR1_HSEEXT, hse_mode);
}

/**
  * @brief  Get External HSE clock mode
  * @rmtoll
  *  CR1        HSEEXT        LL_RCC_HSE_GetClockMode
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_HSE_ANALOG_MODE
  *         @arg @ref LL_RCC_HSE_DIGITAL_MODE
  */
__STATIC_INLINE uint32_t LL_RCC_HSE_GetClockMode(void)
{
  return (uint32_t)(READ_BIT(RCC->CR1, RCC_CR1_HSEEXT));
}

/**
  * @brief  Enable HSE external oscillator (HSE Bypass)
  * @rmtoll
  *  CR1          HSEBYP        LL_RCC_HSE_EnableBypass
  */
__STATIC_INLINE void LL_RCC_HSE_EnableBypass(void)
{
  SET_BIT(RCC->CR1, RCC_CR1_HSEBYP);
}

/**
  * @brief  Configure HSE external oscillator in bypass
  * @rmtoll
  *  CR1        HSEBYP        LL_RCC_HSE_ConfigBypass \n
  *  CR1        HSEEXT        LL_RCC_HSE_ConfigBypass
  * @param  hse_mode This parameter can be one of the following values:
  *         @arg @ref LL_RCC_HSE_ANALOG_MODE
  *         @arg @ref LL_RCC_HSE_DIGITAL_MODE
  */
__STATIC_INLINE void LL_RCC_HSE_ConfigBypass(uint32_t hse_mode)
{
  MODIFY_REG(RCC->CR1, RCC_CR1_HSEBYP | RCC_CR1_HSEEXT, RCC_CR1_HSEBYP | hse_mode);
}

/**
  * @brief  Disable HSE external oscillator (HSE Bypass)
  * @rmtoll
  *  CR1          HSEBYP        LL_RCC_HSE_DisableBypass
  */
__STATIC_INLINE void LL_RCC_HSE_DisableBypass(void)
{
  CLEAR_BIT(RCC->CR1, RCC_CR1_HSEBYP);
}

/**
  * @brief  Check if HSE is bypassed
  * @rmtoll
  *  CR1          HSEBYP        LL_RCC_HSE_IsBypassed
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_HSE_IsBypassed(void)
{
  return ((READ_BIT(RCC->CR1, RCC_CR1_HSEBYP) == RCC_CR1_HSEBYP) ? 1UL : 0UL);
}

/**
  * @brief  Select the Analog HSE external clock type in Bypass mode
  * @rmtoll
  *  CR1           HSEEXT        LL_RCC_HSE_SelectAnalogClock
  */
__STATIC_INLINE void LL_RCC_HSE_SelectAnalogClock(void)
{
  CLEAR_BIT(RCC->CR1, RCC_CR1_HSEEXT);
}

/**
  * @brief  Select the Digital HSE external clock type in Bypass mode
  * @rmtoll
  *  CR1           HSEEXT        LL_RCC_HSE_SelectDigitalClock
  */
__STATIC_INLINE void LL_RCC_HSE_SelectDigitalClock(void)
{
  SET_BIT(RCC->CR1, RCC_CR1_HSEEXT);
}

/**
  * @brief  Enable HSE clock security system
  * @rmtoll
  *  CR1           HSECSSON        LL_RCC_HSE_EnableCSS
  */
__STATIC_INLINE void LL_RCC_HSE_EnableCSS(void)
{
  SET_BIT(RCC->CR1, RCC_CR1_HSECSSON);
}

/**
  * @}
  */ /* End of RCC_LL_EF_HSE */


/** @defgroup RCC_LL_EF_LSCO LSCO
  * @{
  */

/**
  * @brief  Enable Low speed clock
  * @rmtoll
  *  RTCCR         LSCOEN        LL_RCC_LSCO_Enable
  */
__STATIC_INLINE void LL_RCC_LSCO_Enable(void)
{
  SET_BIT(RCC->RTCCR, RCC_RTCCR_LSCOEN);
}

/**
  * @brief  Disable Low speed clock
  * @rmtoll
  *  RTCCR         LSCOEN        LL_RCC_LSCO_Disable
  */
__STATIC_INLINE void LL_RCC_LSCO_Disable(void)
{
  CLEAR_BIT(RCC->RTCCR, RCC_RTCCR_LSCOEN);
}

/**
  * @brief  Configure Low speed clock selection
  * @rmtoll
  *  RTCCR         LSCOSEL       LL_RCC_LSCO_SetSource
  * @param  source This parameter can be one of the following values:
  *         @arg @ref LL_RCC_LSCO_CLKSOURCE_LSI
  *         @arg @ref LL_RCC_LSCO_CLKSOURCE_LSE
  */
__STATIC_INLINE void LL_RCC_LSCO_SetSource(uint32_t source)
{
  MODIFY_REG(RCC->RTCCR, RCC_RTCCR_LSCOSEL, source);
}

/**
  * @brief  Get Low speed clock selection
  * @rmtoll
  *  RTCCR         LSCOSEL       LL_RCC_LSCO_GetSource
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_LSCO_CLKSOURCE_LSI
  *         @arg @ref LL_RCC_LSCO_CLKSOURCE_LSE
  */
__STATIC_INLINE uint32_t LL_RCC_LSCO_GetSource(void)
{
  return (uint32_t)(READ_BIT(RCC->RTCCR, RCC_RTCCR_LSCOSEL));
}

/**
  * @brief  Configure Low speed clock
  * @rmtoll
  *  RTCCR         LSCOSEL       LL_RCC_ConfigLSCO \n
  *  RTCCR         LSCOEN        LL_RCC_ConfigLSCO
  * @param  source This parameter can be one of the following values:
  *         @arg @ref LL_RCC_LSCO_CLKSOURCE_LSI
  *         @arg @ref LL_RCC_LSCO_CLKSOURCE_LSE
  * @note  PWR and backup domain must be previously enabled.
  */
__STATIC_INLINE void LL_RCC_ConfigLSCO(uint32_t source)
{
  MODIFY_REG(RCC->RTCCR, RCC_RTCCR_LSCOSEL | RCC_RTCCR_LSCOEN, source | RCC_RTCCR_LSCOEN);
}

/**
  * @}
  */

/** @defgroup RCC_LL_EF_System System
  * @{
  */

/**
  * @brief  Configure the system clock source
  * @rmtoll
  *  CFGR1         SW         LL_RCC_SetSysClkSource
  * @param  source This parameter can be one of the following values:
  *         @arg @ref LL_RCC_SYS_CLKSOURCE_HSIDIV3
  *         @arg @ref LL_RCC_SYS_CLKSOURCE_HSIS
  *         @arg @ref LL_RCC_SYS_CLKSOURCE_HSE
  *         @arg @ref LL_RCC_SYS_CLKSOURCE_PSIS
  */
__STATIC_INLINE void LL_RCC_SetSysClkSource(uint32_t source)
{
  MODIFY_REG(RCC->CFGR1, RCC_CFGR1_SW, source);
}

/**
  * @brief  Get the system clock source
  * @rmtoll
  *  CFGR1         SWS         LL_RCC_GetSysClkSource
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_SYS_CLKSOURCE_STATUS_HSIDIV3
  *         @arg @ref LL_RCC_SYS_CLKSOURCE_STATUS_HSIS
  *         @arg @ref LL_RCC_SYS_CLKSOURCE_STATUS_HSE
  *         @arg @ref LL_RCC_SYS_CLKSOURCE_STATUS_PSIS
  */
__STATIC_INLINE uint32_t LL_RCC_GetSysClkSource(void)
{
  return (uint32_t)(READ_BIT(RCC->CFGR1, RCC_CFGR1_SWS));
}

/**
  * @brief  Set AHB prescaler
  * @rmtoll
  *  CFGR2         HPRE         LL_RCC_SetAHBPrescaler
  * @param  prescaler This parameter can be one of the following values:
  *         @arg @ref LL_RCC_HCLK_PRESCALER_1
  *         @arg @ref LL_RCC_HCLK_PRESCALER_2
  *         @arg @ref LL_RCC_HCLK_PRESCALER_4
  *         @arg @ref LL_RCC_HCLK_PRESCALER_8
  *         @arg @ref LL_RCC_HCLK_PRESCALER_16
  *         @arg @ref LL_RCC_HCLK_PRESCALER_64
  *         @arg @ref LL_RCC_HCLK_PRESCALER_128
  *         @arg @ref LL_RCC_HCLK_PRESCALER_256
  *         @arg @ref LL_RCC_HCLK_PRESCALER_512
  */
__STATIC_INLINE void LL_RCC_SetAHBPrescaler(uint32_t prescaler)
{
  MODIFY_REG(RCC->CFGR2, RCC_CFGR2_HPRE, prescaler);
}

/**
  * @brief  Get AHB prescaler
  * @rmtoll
  *  CFGR2         HPRE         LL_RCC_GetAHBPrescaler
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_HCLK_PRESCALER_1
  *         @arg @ref LL_RCC_HCLK_PRESCALER_2
  *         @arg @ref LL_RCC_HCLK_PRESCALER_4
  *         @arg @ref LL_RCC_HCLK_PRESCALER_8
  *         @arg @ref LL_RCC_HCLK_PRESCALER_16
  *         @arg @ref LL_RCC_HCLK_PRESCALER_64
  *         @arg @ref LL_RCC_HCLK_PRESCALER_128
  *         @arg @ref LL_RCC_HCLK_PRESCALER_256
  *         @arg @ref LL_RCC_HCLK_PRESCALER_512
  */
__STATIC_INLINE uint32_t LL_RCC_GetAHBPrescaler(void)
{
  return (uint32_t)(READ_BIT(RCC->CFGR2, RCC_CFGR2_HPRE));
}

/**
  * @brief  Set Systick clock source
  * @rmtoll
  *  CCIPR2         SYSTICKSEL         LL_RCC_SetSystickClockSource
  * @param  SystickSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_SYSTICK_CLKSOURCE_HCLKDIV8
  *         @arg @ref LL_RCC_SYSTICK_CLKSOURCE_LSI
  *         @arg @ref LL_RCC_SYSTICK_CLKSOURCE_LSE
  */
__STATIC_INLINE void LL_RCC_SetSystickClockSource(uint32_t SystickSource)
{
  MODIFY_REG(RCC->CCIPR2, RCC_CCIPR2_SYSTICKSEL, SystickSource);
}

/**
  * @brief  Get Sysctick clock source
  * @rmtoll
  *  CCIPR2         SYSTICKSEL         LL_RCC_GetSystickClockSource
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_SYSTICK_CLKSOURCE_HCLKDIV8
  *         @arg @ref LL_RCC_SYSTICK_CLKSOURCE_LSI
  *         @arg @ref LL_RCC_SYSTICK_CLKSOURCE_LSE
  */
__STATIC_INLINE uint32_t LL_RCC_GetSystickClockSource(void)
{
  return (uint32_t)(READ_BIT(RCC->CCIPR2, RCC_CCIPR2_SYSTICKSEL));
}

/**
  * @brief  Set APB1 prescaler
  * @rmtoll
  *  CFGR2         PPRE1         LL_RCC_SetAPB1Prescaler
  * @param  prescaler This parameter can be one of the following values:
  *         @arg @ref LL_RCC_APB1_PRESCALER_1
  *         @arg @ref LL_RCC_APB1_PRESCALER_2
  *         @arg @ref LL_RCC_APB1_PRESCALER_4
  *         @arg @ref LL_RCC_APB1_PRESCALER_8
  *         @arg @ref LL_RCC_APB1_PRESCALER_16
  */
__STATIC_INLINE void LL_RCC_SetAPB1Prescaler(uint32_t prescaler)
{
  MODIFY_REG(RCC->CFGR2, RCC_CFGR2_PPRE1, prescaler);
}

/**
  * @brief  Get APB1 prescaler
  * @rmtoll
  *  CFGR2         PPRE1         LL_RCC_GetAPB1Prescaler
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_APB1_PRESCALER_1
  *         @arg @ref LL_RCC_APB1_PRESCALER_2
  *         @arg @ref LL_RCC_APB1_PRESCALER_4
  *         @arg @ref LL_RCC_APB1_PRESCALER_8
  *         @arg @ref LL_RCC_APB1_PRESCALER_16
  */
__STATIC_INLINE uint32_t LL_RCC_GetAPB1Prescaler(void)
{
  return (uint32_t)(READ_BIT(RCC->CFGR2, RCC_CFGR2_PPRE1));
}

/**
  * @brief  Set APB2 prescaler
  * @rmtoll
  *  CFGR2         PPRE2         LL_RCC_SetAPB2Prescaler
  * @param  prescaler This parameter can be one of the following values:
  *         @arg @ref LL_RCC_APB2_PRESCALER_1
  *         @arg @ref LL_RCC_APB2_PRESCALER_2
  *         @arg @ref LL_RCC_APB2_PRESCALER_4
  *         @arg @ref LL_RCC_APB2_PRESCALER_8
  *         @arg @ref LL_RCC_APB2_PRESCALER_16
  */
__STATIC_INLINE void LL_RCC_SetAPB2Prescaler(uint32_t prescaler)
{
  MODIFY_REG(RCC->CFGR2, RCC_CFGR2_PPRE2, prescaler);
}

/**
  * @brief  Get APB2 prescaler
  * @rmtoll
  *  CFGR2         PPRE2         LL_RCC_GetAPB2Prescaler
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_APB2_PRESCALER_1
  *         @arg @ref LL_RCC_APB2_PRESCALER_2
  *         @arg @ref LL_RCC_APB2_PRESCALER_4
  *         @arg @ref LL_RCC_APB2_PRESCALER_8
  *         @arg @ref LL_RCC_APB2_PRESCALER_16
  */
__STATIC_INLINE uint32_t LL_RCC_GetAPB2Prescaler(void)
{
  return (uint32_t)(READ_BIT(RCC->CFGR2, RCC_CFGR2_PPRE2));
}

/**
  * @brief  Set APB3 prescaler
  * @rmtoll
  *  CFGR2         PPRE3         LL_RCC_SetAPB3Prescaler
  * @param  prescaler This parameter can be one of the following values:
  *         @arg @ref LL_RCC_APB3_PRESCALER_1
  *         @arg @ref LL_RCC_APB3_PRESCALER_2
  *         @arg @ref LL_RCC_APB3_PRESCALER_4
  *         @arg @ref LL_RCC_APB3_PRESCALER_8
  *         @arg @ref LL_RCC_APB3_PRESCALER_16
  */
__STATIC_INLINE void LL_RCC_SetAPB3Prescaler(uint32_t prescaler)
{
  MODIFY_REG(RCC->CFGR2, RCC_CFGR2_PPRE3, prescaler);
}

/**
  * @brief  Get APB3 prescaler
  * @rmtoll
  *  CFGR2         PPRE3         LL_RCC_GetAPB3Prescaler
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_APB3_PRESCALER_1
  *         @arg @ref LL_RCC_APB3_PRESCALER_2
  *         @arg @ref LL_RCC_APB3_PRESCALER_4
  *         @arg @ref LL_RCC_APB3_PRESCALER_8
  *         @arg @ref LL_RCC_APB3_PRESCALER_16
  */
__STATIC_INLINE uint32_t LL_RCC_GetAPB3Prescaler(void)
{
  return (uint32_t)(READ_BIT(RCC->CFGR2, RCC_CFGR2_PPRE3));
}

/**
  * @brief  Configure buses prescalers (AHB, APB1, APB2, APB3)
  * @rmtoll
  *  CFGR2         HPRE         LL_RCC_ConfigBusClock \n
  *  CFGR2         PPRE1        LL_RCC_ConfigBusClock \n
  *  CFGR2         PPRE2        LL_RCC_ConfigBusClock \n
  *  CFGR2         PPRE3        LL_RCC_ConfigBusClock
  * @param  ahb_apb1_apb2_apb3pres Bus Prescalers values of AHB, ABP1 , ABP2 and ABP3
  *         This parameter can be one or a combination of the following values:
  *         @arg @ref LL_RCC_HCLK_PRESCALER_1
  *         @arg @ref LL_RCC_HCLK_PRESCALER_2
  *         @arg @ref LL_RCC_HCLK_PRESCALER_4
  *         @arg @ref LL_RCC_HCLK_PRESCALER_8
  *         @arg @ref LL_RCC_HCLK_PRESCALER_16
  *         @arg @ref LL_RCC_HCLK_PRESCALER_64
  *         @arg @ref LL_RCC_HCLK_PRESCALER_128
  *         @arg @ref LL_RCC_HCLK_PRESCALER_256
  *         @arg @ref LL_RCC_HCLK_PRESCALER_512
  *         @arg @ref LL_RCC_APB1_PRESCALER_1
  *         @arg @ref LL_RCC_APB1_PRESCALER_2
  *         @arg @ref LL_RCC_APB1_PRESCALER_4
  *         @arg @ref LL_RCC_APB1_PRESCALER_8
  *         @arg @ref LL_RCC_APB1_PRESCALER_16
  *         @arg @ref LL_RCC_APB2_PRESCALER_1
  *         @arg @ref LL_RCC_APB2_PRESCALER_2
  *         @arg @ref LL_RCC_APB2_PRESCALER_4
  *         @arg @ref LL_RCC_APB2_PRESCALER_8
  *         @arg @ref LL_RCC_APB2_PRESCALER_16
  *         @arg @ref LL_RCC_APB3_PRESCALER_1
  *         @arg @ref LL_RCC_APB3_PRESCALER_2
  *         @arg @ref LL_RCC_APB3_PRESCALER_4
  *         @arg @ref LL_RCC_APB3_PRESCALER_8
  *         @arg @ref LL_RCC_APB3_PRESCALER_16
  */
__STATIC_INLINE void LL_RCC_ConfigBusClock(uint32_t ahb_apb1_apb2_apb3pres)
{
  MODIFY_REG(RCC->CFGR2, (RCC_CFGR2_HPRE | RCC_CFGR2_PPRE1 | RCC_CFGR2_PPRE2 | RCC_CFGR2_PPRE3), \
             ahb_apb1_apb2_apb3pres);
}

/**
  * @brief  Set Clock After Wake-Up From Stop mode
  * @rmtoll
  *  CFGR1       STOPWUCK      LL_RCC_SetClkAfterWakeFromStop
  * @param  clock This parameter can be one of the following values:
  *         @arg @ref LL_RCC_STOP_WAKEUPCLOCK_HSIDIV3
  *         @arg @ref LL_RCC_STOP_WAKEUPCLOCK_HSIS
  */
__STATIC_INLINE void LL_RCC_SetClkAfterWakeFromStop(uint32_t clock)
{
  MODIFY_REG(RCC->CFGR1, RCC_CFGR1_STOPWUCK, clock);
}

/**
  * @brief  Get Clock After Wake-Up From Stop mode
  * @rmtoll
  *  CFGR1         STOPWUCK      LL_RCC_GetClkAfterWakeFromStop
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_STOP_WAKEUPCLOCK_HSIDIV3
  *         @arg @ref LL_RCC_STOP_WAKEUPCLOCK_HSIS
  */
__STATIC_INLINE uint32_t LL_RCC_GetClkAfterWakeFromStop(void)
{
  return (uint32_t)(READ_BIT(RCC->CFGR1, RCC_CFGR1_STOPWUCK));
}

/**
  * @}
  */ /* RCC_LL_EF_System */

/** @defgroup RCC_LL_EF_MCO MCO
  * @{
  */
/**
  * @brief  Configure MCOx
  * @note   The clock provided to the MCOx outputs must not exceed the maximum IO speed,
  *         refer to the product datasheet for information about the supported IO speed.
  * @rmtoll
  *  CFGR1         MCO1SEL         LL_RCC_ConfigMCO \n
  *  CFGR1         MCO2SEL         LL_RCC_ConfigMCO \n
  *  CFGR1         MCO1PRE         LL_RCC_ConfigMCO \n
  *  CFGR1         MCO2PRE         LL_RCC_ConfigMCO
  * @param  mcox_source This parameter can be one of the following values:
  *         @arg @ref LL_RCC_MCO1SOURCE_SYSCLK
  *         @arg @ref LL_RCC_MCO1SOURCE_HSE
  *         @arg @ref LL_RCC_MCO1SOURCE_LSE
  *         @arg @ref LL_RCC_MCO1SOURCE_LSI
  *         @arg @ref LL_RCC_MCO1SOURCE_PSIK
  *         @arg @ref LL_RCC_MCO1SOURCE_HSIK
  *         @arg @ref LL_RCC_MCO1SOURCE_PSIS
  *         @arg @ref LL_RCC_MCO1SOURCE_HSIS
  *         @arg @ref LL_RCC_MCO2SOURCE_SYSCLK
  *         @arg @ref LL_RCC_MCO2SOURCE_HSE
  *         @arg @ref LL_RCC_MCO2SOURCE_LSE
  *         @arg @ref LL_RCC_MCO2SOURCE_LSI
  *         @arg @ref LL_RCC_MCO2SOURCE_PSIK
  *         @arg @ref LL_RCC_MCO2SOURCE_HSIK
  *         @arg @ref LL_RCC_MCO2SOURCE_PSIDIV3
  *         @arg @ref LL_RCC_MCO2SOURCE_HSIDIV3
  * @param  mcox_prescaler This parameter can be one of the following values:
  *         @arg @ref LL_RCC_MCO1_NO_CLK
  *         @arg @ref LL_RCC_MCO1_PRESCALER_1
  *         @arg @ref LL_RCC_MCO1_PRESCALER_2
  *         @arg @ref LL_RCC_MCO1_PRESCALER_3
  *         @arg @ref LL_RCC_MCO1_PRESCALER_4
  *         @arg @ref LL_RCC_MCO1_PRESCALER_5
  *         @arg @ref LL_RCC_MCO1_PRESCALER_6
  *         @arg @ref LL_RCC_MCO1_PRESCALER_7
  *         @arg @ref LL_RCC_MCO1_PRESCALER_8
  *         @arg @ref LL_RCC_MCO1_PRESCALER_9
  *         @arg @ref LL_RCC_MCO1_PRESCALER_10
  *         @arg @ref LL_RCC_MCO1_PRESCALER_11
  *         @arg @ref LL_RCC_MCO1_PRESCALER_12
  *         @arg @ref LL_RCC_MCO1_PRESCALER_13
  *         @arg @ref LL_RCC_MCO1_PRESCALER_14
  *         @arg @ref LL_RCC_MCO1_PRESCALER_15
  *         @arg @ref LL_RCC_MCO2_NO_CLK
  *         @arg @ref LL_RCC_MCO2_PRESCALER_1
  *         @arg @ref LL_RCC_MCO2_PRESCALER_2
  *         @arg @ref LL_RCC_MCO2_PRESCALER_3
  *         @arg @ref LL_RCC_MCO2_PRESCALER_4
  *         @arg @ref LL_RCC_MCO2_PRESCALER_5
  *         @arg @ref LL_RCC_MCO2_PRESCALER_6
  *         @arg @ref LL_RCC_MCO2_PRESCALER_7
  *         @arg @ref LL_RCC_MCO2_PRESCALER_8
  *         @arg @ref LL_RCC_MCO2_PRESCALER_9
  *         @arg @ref LL_RCC_MCO2_PRESCALER_10
  *         @arg @ref LL_RCC_MCO2_PRESCALER_11
  *         @arg @ref LL_RCC_MCO2_PRESCALER_12
  *         @arg @ref LL_RCC_MCO2_PRESCALER_13
  *         @arg @ref LL_RCC_MCO2_PRESCALER_14
  *         @arg @ref LL_RCC_MCO2_PRESCALER_15
  */
__STATIC_INLINE void LL_RCC_ConfigMCO(uint32_t mcox_source, uint32_t mcox_prescaler)
{
  MODIFY_REG(RCC->CFGR1, (mcox_source << 16U) | (mcox_prescaler << 16U), \
             (mcox_source & 0xFFFF0000U) | (mcox_prescaler & 0xFFFF0000U));
}
/**
  * @}
  */ /* End of RCC_LL_EF_MCO */

/** @defgroup RCC_LL_EF_Peripheral_Clock_Source Peripheral Clock Source
  * @{
  */

/**
  * @brief  Configure peripheral clock source
  * @rmtoll
  *  CCIPR1         *         LL_RCC_SetClockSource \n
  *  CCIPR2         *         LL_RCC_SetClockSource \n
  *  CCIPR3         *         LL_RCC_SetClockSource
  * @param  ClkSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_USART1_CLKSOURCE_PCLK2
  *         @arg @ref LL_RCC_USART1_CLKSOURCE_PSIK
  *         @arg @ref LL_RCC_USART1_CLKSOURCE_HSIK
  *         @arg @ref LL_RCC_USART1_CLKSOURCE_LSE
  *         @arg @ref LL_RCC_USART2_CLKSOURCE_PCLK1
  *         @arg @ref LL_RCC_USART2_CLKSOURCE_PSIK
  *         @arg @ref LL_RCC_USART2_CLKSOURCE_HSIK
  *         @arg @ref LL_RCC_USART2_CLKSOURCE_LSE
  * @if USART3
  *         @arg @ref LL_RCC_USART3_CLKSOURCE_PCLK1 (*)
  *         @arg @ref LL_RCC_USART3_CLKSOURCE_PSIK (*)
  *         @arg @ref LL_RCC_USART3_CLKSOURCE_HSIK (*)
  *         @arg @ref LL_RCC_USART3_CLKSOURCE_LSE (*)
  * @endif
  * @if USART6
  *         @arg @ref LL_RCC_USART6_CLKSOURCE_PCLK1 (*)
  *         @arg @ref LL_RCC_USART6_CLKSOURCE_PSIK  (*)
  *         @arg @ref LL_RCC_USART6_CLKSOURCE_HSIK  (*)
  *         @arg @ref LL_RCC_USART6_CLKSOURCE_LSE   (*)
  * @endif
  *         @arg @ref LL_RCC_UART4_CLKSOURCE_PCLK1
  *         @arg @ref LL_RCC_UART4_CLKSOURCE_PSIK
  *         @arg @ref LL_RCC_UART4_CLKSOURCE_HSIK
  *         @arg @ref LL_RCC_UART4_CLKSOURCE_LSE
  *         @arg @ref LL_RCC_UART5_CLKSOURCE_PCLK1
  *         @arg @ref LL_RCC_UART5_CLKSOURCE_PSIK
  *         @arg @ref LL_RCC_UART5_CLKSOURCE_HSIK
  *         @arg @ref LL_RCC_UART5_CLKSOURCE_LSE
  * @if UART7
  *         @arg @ref LL_RCC_UART7_CLKSOURCE_PCLK1  (*)
  *         @arg @ref LL_RCC_UART7_CLKSOURCE_PSIK   (*)
  *         @arg @ref LL_RCC_UART7_CLKSOURCE_HSIK   (*)
  *         @arg @ref LL_RCC_UART7_CLKSOURCE_LSE    (*)
  * @endif
  *         @arg @ref LL_RCC_SPI1_CLKSOURCE_PCLK2
  *         @arg @ref LL_RCC_SPI1_CLKSOURCE_PSIK
  *         @arg @ref LL_RCC_SPI1_CLKSOURCE_HSIK
  *         @arg @ref LL_RCC_SPI1_CLKSOURCE_AUDIOCLK
  *         @arg @ref LL_RCC_SPI2_CLKSOURCE_PCLK1
  *         @arg @ref LL_RCC_SPI2_CLKSOURCE_PSIK
  *         @arg @ref LL_RCC_SPI2_CLKSOURCE_HSIK
  *         @arg @ref LL_RCC_SPI2_CLKSOURCE_AUDIOCLK
  * @if SPI3
  *         @arg @ref LL_RCC_SPI3_CLKSOURCE_PCLK1    (*)
  *         @arg @ref LL_RCC_SPI3_CLKSOURCE_PSIK     (*)
  *         @arg @ref LL_RCC_SPI3_CLKSOURCE_HSIK     (*)
  *         @arg @ref LL_RCC_SPI3_CLKSOURCE_AUDIOCLK (*)
  * @endif
  *         @arg @ref LL_RCC_I2C1_CLKSOURCE_PCLK1
  *         @arg @ref LL_RCC_I2C1_CLKSOURCE_PSIK
  *         @arg @ref LL_RCC_I2C1_CLKSOURCE_HSIK
  * @if I2C2
  *         @arg @ref LL_RCC_I2C2_CLKSOURCE_PCLK1   (*)
  *         @arg @ref LL_RCC_I2C2_CLKSOURCE_PSIK    (*)
  *         @arg @ref LL_RCC_I2C2_CLKSOURCE_HSIK    (*)
  * @endif
  * @if ETH
  *         @arg @ref LL_RCC_ETHREF_CLKSOURCE_RMII  (*)
  *         @arg @ref LL_RCC_ETHREF_CLKSOURCE_FB    (*)
  *         @arg @ref LL_RCC_ETHPTP_CLKSOURCE_HCLK  (*)
  *         @arg @ref LL_RCC_ETHPTP_CLKSOURCE_PSIS  (*)
  *         @arg @ref LL_RCC_ETHPTP_CLKSOURCE_PSIK  (*)
  *         @arg @ref LL_RCC_ETH_CLKSOURCE_NONE     (*)
  *         @arg @ref LL_RCC_ETH_CLKSOURCE_PSIS     (*)
  *         @arg @ref LL_RCC_ETH_CLKSOURCE_PSIK     (*)
  *         @arg @ref LL_RCC_ETH_CLKSOURCE_HSE      (*)
  * @endif
  *
  *         (*) value not defined in all devices.
  */
__STATIC_INLINE void LL_RCC_SetClockSource(uint32_t ClkSource)
{
  volatile uint32_t *pReg = (uint32_t *)((uint32_t)&RCC->CCIPR1 + LL_CLKSOURCE_REG(ClkSource));
  MODIFY_REG(*pReg, LL_CLKSOURCE_MASK(ClkSource), LL_CLKSOURCE_CONFIG(ClkSource));
}
/**
  * @brief  Configure USARTx clock source
  * @rmtoll
  *  CCIPR1         USART1SEL         LL_RCC_SetUSARTClockSource \n
  *  CCIPR1         USART2SEL         LL_RCC_SetUSARTClockSource \n
  *  CCIPR1         USART3SEL         LL_RCC_SetUSARTClockSource \n
  *  CCIPR1         USART6SEL         LL_RCC_SetUSARTClockSource
  * @param  ClkSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_USART1_CLKSOURCE_PCLK2
  *         @arg @ref LL_RCC_USART1_CLKSOURCE_PSIK
  *         @arg @ref LL_RCC_USART1_CLKSOURCE_HSIK
  *         @arg @ref LL_RCC_USART1_CLKSOURCE_LSE
  *         @arg @ref LL_RCC_USART2_CLKSOURCE_PCLK1
  *         @arg @ref LL_RCC_USART2_CLKSOURCE_PSIK
  *         @arg @ref LL_RCC_USART2_CLKSOURCE_HSIK
  *         @arg @ref LL_RCC_USART2_CLKSOURCE_LSE
  * @if USART3
  *         @arg @ref LL_RCC_USART3_CLKSOURCE_PCLK1 (*)
  *         @arg @ref LL_RCC_USART3_CLKSOURCE_PSIK  (*)
  *         @arg @ref LL_RCC_USART3_CLKSOURCE_HSIK  (*)
  *         @arg @ref LL_RCC_USART3_CLKSOURCE_LSE   (*)
  * @endif
  * @if USART6
  *         @arg @ref LL_RCC_USART6_CLKSOURCE_PCLK1 (*)
  *         @arg @ref LL_RCC_USART6_CLKSOURCE_PSIK  (*)
  *         @arg @ref LL_RCC_USART6_CLKSOURCE_HSIK  (*)
  *         @arg @ref LL_RCC_USART6_CLKSOURCE_LSE   (*)
  * @endif
  */
__STATIC_INLINE void LL_RCC_SetUSARTClockSource(uint32_t ClkSource)
{
  LL_RCC_SetClockSource(ClkSource);
}
/**
  * @brief  Configure UARTx clock source
  * @rmtoll
  *  CCIPR1         UART4SEL         LL_RCC_SetUARTClockSource \n
  *  CCIPR1         UART5SEL         LL_RCC_SetUARTClockSource \n
  *  CCIPR1         UART7SEL         LL_RCC_SetUARTClockSource
  * @param  ClkSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_UART4_CLKSOURCE_PCLK1
  *         @arg @ref LL_RCC_UART4_CLKSOURCE_PSIK
  *         @arg @ref LL_RCC_UART4_CLKSOURCE_HSIK
  *         @arg @ref LL_RCC_UART4_CLKSOURCE_LSE
  *         @arg @ref LL_RCC_UART5_CLKSOURCE_PCLK1
  *         @arg @ref LL_RCC_UART5_CLKSOURCE_PSIK
  *         @arg @ref LL_RCC_UART5_CLKSOURCE_HSIK
  *         @arg @ref LL_RCC_UART5_CLKSOURCE_LSE
  * @if UART7
  *         @arg @ref LL_RCC_UART7_CLKSOURCE_PCLK1  (*)
  *         @arg @ref LL_RCC_UART7_CLKSOURCE_PSIK   (*)
  *         @arg @ref LL_RCC_UART7_CLKSOURCE_HSIK   (*)
  *         @arg @ref LL_RCC_UART7_CLKSOURCE_LSE    (*)
  * @endif
  */
__STATIC_INLINE void LL_RCC_SetUARTClockSource(uint32_t ClkSource)
{
  LL_RCC_SetClockSource(ClkSource);
}
/**
  * @brief  Configure LPUARTx clock source
  * @rmtoll
  *  CCIPR1         LPUART1SEL         LL_RCC_SetLPUARTClockSource
  * @param  ClkSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_LPUART1_CLKSOURCE_PCLK3
  *         @arg @ref LL_RCC_LPUART1_CLKSOURCE_HSIK
  *         @arg @ref LL_RCC_LPUART1_CLKSOURCE_LSE
  *         @arg @ref LL_RCC_LPUART1_CLKSOURCE_LSI
  */
__STATIC_INLINE void LL_RCC_SetLPUARTClockSource(uint32_t ClkSource)
{
  MODIFY_REG(RCC->CCIPR1, RCC_CCIPR1_LPUART1SEL, ClkSource);
}
/**
  * @brief  Configure SPIx clock source
  * @rmtoll
  *  CCIPR1         SPI1SEL         LL_RCC_SetSPIClockSource \n
  *  CCIPR1         SPI2SEL         LL_RCC_SetSPIClockSource \n
  *  CCIPR1         SPI3SEL         LL_RCC_SetSPIClockSource
  * @param  ClkSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_SPI1_CLKSOURCE_PCLK2
  *         @arg @ref LL_RCC_SPI1_CLKSOURCE_PSIK
  *         @arg @ref LL_RCC_SPI1_CLKSOURCE_HSIK
  *         @arg @ref LL_RCC_SPI1_CLKSOURCE_AUDIOCLK
  *         @arg @ref LL_RCC_SPI2_CLKSOURCE_PCLK1
  *         @arg @ref LL_RCC_SPI2_CLKSOURCE_PSIK
  *         @arg @ref LL_RCC_SPI2_CLKSOURCE_HSIK
  *         @arg @ref LL_RCC_SPI2_CLKSOURCE_AUDIOCLK
  * @if SPI3
  *         @arg @ref LL_RCC_SPI3_CLKSOURCE_PCLK1     (*)
  *         @arg @ref LL_RCC_SPI3_CLKSOURCE_PSIK      (*)
  *         @arg @ref LL_RCC_SPI3_CLKSOURCE_HSIK      (*)
  *         @arg @ref LL_RCC_SPI3_CLKSOURCE_AUDIOCLK  (*)
  * @endif
  */
__STATIC_INLINE void LL_RCC_SetSPIClockSource(uint32_t ClkSource)
{
  LL_RCC_SetClockSource(ClkSource);
}
#if defined(FDCAN1)

/**
  * @brief  Configure FDCANx clock source
  * @rmtoll
  *  CCIPR1         FDCANSEL         LL_RCC_SetFDCANClockSource
  * @param  ClkSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_FDCAN_CLKSOURCE_PCLK1
  *         @arg @ref LL_RCC_FDCAN_CLKSOURCE_PSIS
  *         @arg @ref LL_RCC_FDCAN_CLKSOURCE_PSIK
  *         @arg @ref LL_RCC_FDCAN_CLKSOURCE_HSE
  */
__STATIC_INLINE void LL_RCC_SetFDCANClockSource(uint32_t ClkSource)
{
  MODIFY_REG(RCC->CCIPR1, RCC_CCIPR1_FDCANSEL, ClkSource);
}
#endif /* FDCAN1 */

/**
  * @brief  Configure I2Cx clock source
  * @rmtoll
  *  CCIPR2         I2C1SEL         LL_RCC_SetI2CClockSource \n
  *  CCIPR2         I2C2SEL         LL_RCC_SetI2CClockSource
  * @param  ClkSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_I2C1_CLKSOURCE_PCLK1
  *         @arg @ref LL_RCC_I2C1_CLKSOURCE_PSIK
  *         @arg @ref LL_RCC_I2C1_CLKSOURCE_HSIK
  * @if I2C2
  *         @arg @ref LL_RCC_I2C2_CLKSOURCE_PCLK1 (*)
  *         @arg @ref LL_RCC_I2C2_CLKSOURCE_PSIK  (*)
  *         @arg @ref LL_RCC_I2C2_CLKSOURCE_HSIK  (*)
  * @endif
  */
__STATIC_INLINE void LL_RCC_SetI2CClockSource(uint32_t ClkSource)
{
  LL_RCC_SetClockSource(ClkSource);
}

/**
  * @brief  Configure I3Cx clock source
  * @rmtoll
  *  CCIPR2         I3C1SEL         LL_RCC_SetI3CClockSource
  * @param  ClkSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_I3C1_CLKSOURCE_PCLK1
  *         @arg @ref LL_RCC_I3C1_CLKSOURCE_PSIK
  *         @arg @ref LL_RCC_I3C1_CLKSOURCE_HSIK
  */
__STATIC_INLINE void LL_RCC_SetI3CClockSource(uint32_t ClkSource)
{
  MODIFY_REG(RCC->CCIPR2, RCC_CCIPR2_I3C1SEL, ClkSource);
}
/**
  * @brief  Configure ADCDACx clock source
  * @rmtoll
  *  CCIPR2         ADCDACSEL         LL_RCC_SetADCDACClockSource
  * @param  ClkSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_ADCDAC_CLKSOURCE_HCLK
  *         @arg @ref LL_RCC_ADCDAC_CLKSOURCE_PSIS
  *         @arg @ref LL_RCC_ADCDAC_CLKSOURCE_PSIK
  *         @arg @ref LL_RCC_ADCDAC_CLKSOURCE_HSIK
  * @note This bit must not be changed when ADC or DAC enabled.
  */
__STATIC_INLINE void LL_RCC_SetADCDACClockSource(uint32_t ClkSource)
{
  MODIFY_REG(RCC->CCIPR2, RCC_CCIPR2_ADCDACSEL, ClkSource);
}

/**
  * @brief  Configure ADCDACx clock prescaler
  * @rmtoll
  *  CCIPR2         ADCDACPRE         LL_RCC_SetADCDACPrescaler
  * @param  Prescaler This parameter can be one of the following values:
  *         @arg @ref LL_RCC_ADCDAC_PRESCALER_1
  *         @arg @ref LL_RCC_ADCDAC_PRESCALER_2
  *         @arg @ref LL_RCC_ADCDAC_PRESCALER_4
  *         @arg @ref LL_RCC_ADCDAC_PRESCALER_8
  *         @arg @ref LL_RCC_ADCDAC_PRESCALER_16
  *         @arg @ref LL_RCC_ADCDAC_PRESCALER_32
  *         @arg @ref LL_RCC_ADCDAC_PRESCALER_64
  *         @arg @ref LL_RCC_ADCDAC_PRESCALER_128
  * @note This bit must not be changed when ADC or DAC enabled.
  */
__STATIC_INLINE void LL_RCC_SetADCDACPrescaler(uint32_t Prescaler)
{
  MODIFY_REG(RCC->CCIPR2, RCC_CCIPR2_ADCDACPRE, Prescaler);
}

/**
  * @brief  Configure DAC1 clock source
  * @rmtoll
  *  CCIPR2         DACSEL         LL_RCC_SetDAC1ClockSource
  * @param  ClkSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_DAC1SH_CLKSOURCE_LSE
  *         @arg @ref LL_RCC_DAC1SH_CLKSOURCE_LSI
  */
__STATIC_INLINE void LL_RCC_SetDAC1ClockSource(uint32_t ClkSource)
{
  MODIFY_REG(RCC->CCIPR2, RCC_CCIPR2_DACSEL, ClkSource);
}

/**
  * @brief  Configure LPTIMx clock source
  * @rmtoll
  *  CCIPR2         LPTIM1SEL         LL_RCC_SetLPTIMClockSource
  * @param  ClkSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_LPTIM1_CLKSOURCE_PCLK3
  *         @arg @ref LL_RCC_LPTIM1_CLKSOURCE_HSIK
  *         @arg @ref LL_RCC_LPTIM1_CLKSOURCE_LSE
  *         @arg @ref LL_RCC_LPTIM1_CLKSOURCE_LSI
  */
__STATIC_INLINE void LL_RCC_SetLPTIMClockSource(uint32_t ClkSource)
{
  MODIFY_REG(RCC->CCIPR2, RCC_CCIPR2_LPTIM1SEL, ClkSource);
}

/**
  * @brief  Configure CKx clock source
  * @rmtoll
  *  CCIPR2         CK48SEL         LL_RCC_SetCKClockSource
  * @param  ClkSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_CK48_CLKSOURCE_PSI_DIV_3
  *         @arg @ref LL_RCC_CK48_CLKSOURCE_HSI_DIV_3
  *         @arg @ref LL_RCC_CK48_CLKSOURCE_HSE
  */
__STATIC_INLINE void LL_RCC_SetCKClockSource(uint32_t ClkSource)
{
  MODIFY_REG(RCC->CCIPR2, RCC_CCIPR2_CK48SEL, ClkSource);
}

#if defined(XSPI1)
/* @brief  Configure XSPIx clock source
  * @rmtoll
  *  CCIPR3         XSPI1SEL         LL_RCC_SetXSPIClockSource
  * @param  clk_source This parameter can be one of the following values:
  *         @arg @ref LL_RCC_XSPI1_CLKSOURCE_HCLK
  *         @arg @ref LL_RCC_XSPI1_CLKSOURCE_PSIK
  *         @arg @ref LL_RCC_XSPI1_CLKSOURCE_HSIK
  */
__STATIC_INLINE void LL_RCC_SetXSPIClockSource(uint32_t clk_source)
{
  MODIFY_REG(RCC->CCIPR3, RCC_CCIPR3_XSPI1SEL, clk_source);
}

#endif /* XSPI1 */
#if defined(ETH)
/**
  * @brief  Configure ETHx clock source
  * @rmtoll
  *  CCIPR3         ETHREFCLKSEL        LL_RCC_SetETHClockSource \n
  *  CCIPR3         ETHPTPCLKSEL        LL_RCC_SetETHClockSource \n
  *  CCIPR3         ETHCLKSEL           LL_RCC_SetETHClockSource
  * @param  ClkSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_ETHREF_CLKSOURCE_RMII
  *         @arg @ref LL_RCC_ETHREF_CLKSOURCE_FB
  *         @arg @ref LL_RCC_ETHPTP_CLKSOURCE_NONE
  *         @arg @ref LL_RCC_ETHPTP_CLKSOURCE_HCLK
  *         @arg @ref LL_RCC_ETHPTP_CLKSOURCE_PSIS
  *         @arg @ref LL_RCC_ETHPTP_CLKSOURCE_PSIK
  *         @arg @ref LL_RCC_ETH_CLKSOURCE_NONE
  *         @arg @ref LL_RCC_ETH_CLKSOURCE_PSIS
  *         @arg @ref LL_RCC_ETH_CLKSOURCE_PSIK
  *         @arg @ref LL_RCC_ETH_CLKSOURCE_HSE
  */
__STATIC_INLINE void LL_RCC_SetETHClockSource(uint32_t ClkSource)
{
  LL_RCC_SetClockSource(ClkSource);
}

/**
  * @brief  Configure ETH clock prescaler
  * @rmtoll
  *  CCIPR3         ETHCLKDIVSEL         LL_RCC_SetETHPrescaler
  * @param  Prescaler This parameter can be one of the following values:
  *         @arg @ref LL_RCC_ETH_DIV_1
  *         @arg @ref LL_RCC_ETH_DIV_2
  *         @arg @ref LL_RCC_ETH_DIV_4
  */
__STATIC_INLINE void LL_RCC_SetETHPrescaler(uint32_t Prescaler)
{
  MODIFY_REG(RCC->CCIPR3, RCC_CCIPR3_ETHCLKDIVSEL, Prescaler);
}

/**
  * @brief  Configure ETHPTP clock prescaler
  * @rmtoll
  *  CCIPR3         ETHPTPDIVSEL         LL_RCC_SetETHPTPPrescaler
  * @param  Prescaler This parameter can be one of the following values:
  *         @arg @ref LL_RCC_ETHPTP_DIV_1
  *         @arg @ref LL_RCC_ETHPTP_DIV_2
  *         @arg @ref LL_RCC_ETHPTP_DIV_3
  *         @arg @ref LL_RCC_ETHPTP_DIV_4
  *         @arg @ref LL_RCC_ETHPTP_DIV_5
  *         @arg @ref LL_RCC_ETHPTP_DIV_6
  *         @arg @ref LL_RCC_ETHPTP_DIV_7
  *         @arg @ref LL_RCC_ETHPTP_DIV_8
  */
__STATIC_INLINE void LL_RCC_SetETHPTPPrescaler(uint32_t Prescaler)
{
  MODIFY_REG(RCC->CCIPR3, RCC_CCIPR3_ETHPTPDIVSEL, Prescaler);
}

#endif /* ETH */
/**
  * @brief  Configure ADCDACx
  * @rmtoll
  *  CCIPR2         ADCDACSEL        LL_RCC_ConfigADCDAC \n
  *  CCIPR2         ADCDACPRE        LL_RCC_ConfigADCDAC
  * @param  adcdacx_source This parameter can be one of the following values:
  *         @arg @ref LL_RCC_ADCDAC_CLKSOURCE_HCLK
  *         @arg @ref LL_RCC_ADCDAC_CLKSOURCE_PSIS
  *         @arg @ref LL_RCC_ADCDAC_CLKSOURCE_PSIK
  *         @arg @ref LL_RCC_ADCDAC_CLKSOURCE_HSIK
  * @param  adcdacx_prescaler This parameter can be one of the following values:
  *         @arg @ref LL_RCC_ADCDAC_PRESCALER_1
  *         @arg @ref LL_RCC_ADCDAC_PRESCALER_2
  *         @arg @ref LL_RCC_ADCDAC_PRESCALER_4
  *         @arg @ref LL_RCC_ADCDAC_PRESCALER_8
  *         @arg @ref LL_RCC_ADCDAC_PRESCALER_16
  *         @arg @ref LL_RCC_ADCDAC_PRESCALER_32
  *         @arg @ref LL_RCC_ADCDAC_PRESCALER_64
  *         @arg @ref LL_RCC_ADCDAC_PRESCALER_128
  * @note These bits can be written only if the ADCDAC clock is disabled.
  */
__STATIC_INLINE void LL_RCC_ConfigADCDAC(uint32_t adcdacx_source, uint32_t adcdacx_prescaler)
{
  MODIFY_REG(RCC->CCIPR2, RCC_CCIPR2_ADCDACSEL | RCC_CCIPR2_ADCDACPRE, adcdacx_source | adcdacx_prescaler);
}

/**
  * @brief  Get ADCDACx configuration
  * @rmtoll
  *  CCIPR2         ADCDACSEL        LL_RCC_GetConfigADCDAC \n
  *  CCIPR2         ADCDACPRE        LL_RCC_GetConfigADCDAC
  * @param  p_adcdacx_source Pointer on LL_RCC_ADCDAC_CLKSOURCE
  * @param  p_adcdacx_prescaler Pointer on LL_RCC_ADCDAC_PRESCALER
  */
__STATIC_INLINE void LL_RCC_GetConfigADCDAC(uint32_t *p_adcdacx_source, uint32_t *p_adcdacx_prescaler)
{
  const volatile uint32_t Reg = READ_REG(RCC->CCIPR2);

  *p_adcdacx_source = (uint32_t)(Reg & RCC_CCIPR2_ADCDACSEL);
  *p_adcdacx_prescaler = (uint32_t)(Reg & RCC_CCIPR2_ADCDACPRE);
}

#if defined(ETH)
/**
  * @brief  Configure ETH
  * @rmtoll
  *  CCIPR3         ETHCLKSEL        LL_RCC_ConfigETH \n
  *  CCIPR3         ETHCLKDIVSEL     LL_RCC_ConfigETH
  * @param  eth_source This parameter can be one of the following values:
  *         @arg @ref LL_RCC_ETH_CLKSOURCE_NONE
  *         @arg @ref LL_RCC_ETH_CLKSOURCE_PSIS
  *         @arg @ref LL_RCC_ETH_CLKSOURCE_PSIK
  *         @arg @ref LL_RCC_ETH_CLKSOURCE_HSE
  * @param  eth_prescaler This parameter can be one of the following values:
  *         @arg @ref LL_RCC_ETH_DIV_1
  *         @arg @ref LL_RCC_ETH_DIV_2
  *         @arg @ref LL_RCC_ETH_DIV_4
  * @note These bits can be written only if the ADCDAC clock is disabled.
  */
__STATIC_INLINE void LL_RCC_ConfigETH(uint32_t eth_source, uint32_t eth_prescaler)
{
  MODIFY_REG(RCC->CCIPR3, RCC_CCIPR3_ETHCLKSEL | RCC_CCIPR3_ETHCLKDIVSEL, eth_source | eth_prescaler);
}

/**
  * @brief  Get ETH configuration
  * @rmtoll
  *  CCIPR3         ETHCLKSEL        LL_RCC_GetConfigETH \n
  *  CCIPR3         ETHCLKDIVSEL     LL_RCC_GetConfigETH
  * @param  p_adcdacx_source Pointer on LL_RCC_ETH_CLKSOURCE
  * @param  p_adcdacx_prescaler Pointer on LL_RCC_ETH_DIV
  */
__STATIC_INLINE void LL_RCC_GetConfigETH(uint32_t *p_adcdacx_source, uint32_t *p_adcdacx_prescaler)
{
  const volatile uint32_t Reg = READ_REG(RCC->CCIPR3);

  *p_adcdacx_source = (uint32_t)(Reg & RCC_CCIPR3_ETHCLKSEL);
  *p_adcdacx_prescaler = (uint32_t)(Reg & RCC_CCIPR3_ETHCLKDIVSEL);
}

/**
  * @brief  Configure ETHPTP
  * @rmtoll
  *  CCIPR3         ETHPTPCLKSEL        LL_RCC_ConfigETHPTP \n
  *  CCIPR3         ETHPTPDIVSEL        LL_RCC_ConfigETHPTP
  * @param  ethptp_source This parameter can be one of the following values:
  *         @arg @ref LL_RCC_ETHPTP_CLKSOURCE_NONE
  *         @arg @ref LL_RCC_ETHPTP_CLKSOURCE_HCLK
  *         @arg @ref LL_RCC_ETHPTP_CLKSOURCE_PSIS
  *         @arg @ref LL_RCC_ETHPTP_CLKSOURCE_PSIK
  * @param  ethptp_prescaler This parameter can be one of the following values:
  *         @arg @ref LL_RCC_ETHPTP_DIV_1
  *         @arg @ref LL_RCC_ETHPTP_DIV_2
  *         @arg @ref LL_RCC_ETHPTP_DIV_3
  *         @arg @ref LL_RCC_ETHPTP_DIV_4
  *         @arg @ref LL_RCC_ETHPTP_DIV_5
  *         @arg @ref LL_RCC_ETHPTP_DIV_6
  *         @arg @ref LL_RCC_ETHPTP_DIV_7
  *         @arg @ref LL_RCC_ETHPTP_DIV_8
  */
__STATIC_INLINE void LL_RCC_ConfigETHPTP(uint32_t ethptp_source, uint32_t ethptp_prescaler)
{
  MODIFY_REG(RCC->CCIPR3, RCC_CCIPR3_ETHPTPCLKSEL | RCC_CCIPR3_ETHPTPDIVSEL, ethptp_source | ethptp_prescaler);
}

/**
  * @brief  Get ETH PTPconfiguration
  * @rmtoll
  *  CCIPR3         ETHPTPCLKSEL        LL_RCC_GetConfigETHPTP \n
  *  CCIPR3         ETHPTPDIVSEL        LL_RCC_GetConfigETHPTP
  * @param  p_adcdacx_source Pointer on LL_RCC_ETHPTP_CLKSOURCE
  * @param  p_adcdacx_prescaler Pointer on LL_RCC_ETHPTP_DIV
  */
__STATIC_INLINE void LL_RCC_GetConfigETHPTP(uint32_t *p_adcdacx_source, uint32_t *p_adcdacx_prescaler)
{
  const volatile uint32_t Reg = READ_REG(RCC->CCIPR3);

  *p_adcdacx_source = (uint32_t)(Reg & RCC_CCIPR3_ETHPTPCLKSEL);
  *p_adcdacx_prescaler = (uint32_t)(Reg & RCC_CCIPR3_ETHPTPDIVSEL);
}

#endif /* ETH */
/**
  * @brief  Get periph clock source
  * @rmtoll
  *  CCIPR1         *         LL_RCC_GetClockSource \n
  *  CCIPR2         *         LL_RCC_GetClockSource \n
  *  CCIPR3         *         LL_RCC_GetClockSource
  * @param  Periph This parameter can be one of the following values:
  *         @arg @ref LL_RCC_USART1_CLKSOURCE
  *         @arg @ref LL_RCC_USART2_CLKSOURCE
  * @if USART3
  *         @arg @ref LL_RCC_USART3_CLKSOURCE       (*)
  * @endif
  * @if USART6
  *         @arg @ref LL_RCC_USART6_CLKSOURCE       (*)
  * @endif
  *         @arg @ref LL_RCC_UART4_CLKSOURCE
  *         @arg @ref LL_RCC_UART5_CLKSOURCE
  * @if UART7
  *         @arg @ref LL_RCC_UART7_CLKSOURCE        (*)
  * @endif
  *         @arg @ref LL_RCC_SPI1_CLKSOURCE
  *         @arg @ref LL_RCC_SPI2_CLKSOURCE
  * @if SPI3
  *         @arg @ref LL_RCC_SPI3_CLKSOURCE         (*)
  * @endif
  *         @arg @ref LL_RCC_I2C1_CLKSOURCE
  * @if I2C2
  *         @arg @ref LL_RCC_I2C2_CLKSOURCE         (*)
  * @endif
  * @if XSPI1
  *         @arg @ref LL_RCC_XSPI1_CLKSOURCE        (*)
  * @endif
  * @if ETH
  *         @arg @ref LL_RCC_ETHREF_CLKSOURCE       (*)
  *         @arg @ref LL_RCC_ETHPTP_CLKSOURCE       (*)
  *         @arg @ref LL_RCC_ETH_CLKSOURCE          (*)
  * @endif
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_USART1_CLKSOURCE_PCLK2
  *         @arg @ref LL_RCC_USART1_CLKSOURCE_PSIK
  *         @arg @ref LL_RCC_USART1_CLKSOURCE_HSIK
  *         @arg @ref LL_RCC_USART1_CLKSOURCE_LSE
  *         @arg @ref LL_RCC_USART2_CLKSOURCE_PCLK1
  *         @arg @ref LL_RCC_USART2_CLKSOURCE_PSIK
  *         @arg @ref LL_RCC_USART2_CLKSOURCE_HSIK
  *         @arg @ref LL_RCC_USART2_CLKSOURCE_LSE
  * @if USART3
  *         @arg @ref LL_RCC_USART3_CLKSOURCE_PCLK1 (*)
  *         @arg @ref LL_RCC_USART3_CLKSOURCE_PSIK  (*)
  *         @arg @ref LL_RCC_USART3_CLKSOURCE_HSIK  (*)
  *         @arg @ref LL_RCC_USART3_CLKSOURCE_LSE   (*)
  * @endif
  * @if USART6
  *         @arg @ref LL_RCC_USART6_CLKSOURCE_PCLK1 (*)
  *         @arg @ref LL_RCC_USART6_CLKSOURCE_PSIK  (*)
  *         @arg @ref LL_RCC_USART6_CLKSOURCE_HSIK  (*)
  *         @arg @ref LL_RCC_USART6_CLKSOURCE_LSE   (*)
  * @endif
  *         @arg @ref LL_RCC_UART4_CLKSOURCE_PCLK1
  *         @arg @ref LL_RCC_UART4_CLKSOURCE_PSIK
  *         @arg @ref LL_RCC_UART4_CLKSOURCE_HSIK
  *         @arg @ref LL_RCC_UART4_CLKSOURCE_LSE
  *         @arg @ref LL_RCC_UART5_CLKSOURCE_PCLK1
  *         @arg @ref LL_RCC_UART5_CLKSOURCE_PSIK
  *         @arg @ref LL_RCC_UART5_CLKSOURCE_HSIK
  *         @arg @ref LL_RCC_UART5_CLKSOURCE_LSE
  * @if UART7
  *         @arg @ref LL_RCC_UART7_CLKSOURCE_PCLK1  (*)
  *         @arg @ref LL_RCC_UART7_CLKSOURCE_PSIK   (*)
  *         @arg @ref LL_RCC_UART7_CLKSOURCE_HSIK   (*)
  *         @arg @ref LL_RCC_UART7_CLKSOURCE_LSE    (*)
  * @endif
  *         @arg @ref LL_RCC_SPI1_CLKSOURCE_PCLK2
  *         @arg @ref LL_RCC_SPI1_CLKSOURCE_PSIK
  *         @arg @ref LL_RCC_SPI1_CLKSOURCE_HSIK
  *         @arg @ref LL_RCC_SPI1_CLKSOURCE_AUDIOCLK
  *         @arg @ref LL_RCC_SPI2_CLKSOURCE_PCLK1
  *         @arg @ref LL_RCC_SPI2_CLKSOURCE_PSIK
  *         @arg @ref LL_RCC_SPI2_CLKSOURCE_HSIK
  *         @arg @ref LL_RCC_SPI2_CLKSOURCE_AUDIOCLK
  * @if SPI3
  *         @arg @ref LL_RCC_SPI3_CLKSOURCE_PCLK1     (*)
  *         @arg @ref LL_RCC_SPI3_CLKSOURCE_PSIK     (*)
  *         @arg @ref LL_RCC_SPI3_CLKSOURCE_HSIK     (*)
  *         @arg @ref LL_RCC_SPI3_CLKSOURCE_AUDIOCLK (*)
  * @endif
  *         @arg @ref LL_RCC_I2C1_CLKSOURCE_PCLK1
  *         @arg @ref LL_RCC_I2C1_CLKSOURCE_PSIK
  *         @arg @ref LL_RCC_I2C1_CLKSOURCE_HSIK
  * @if I2C2
  *         @arg @ref LL_RCC_I2C2_CLKSOURCE_PCLK1 (*)
  *         @arg @ref LL_RCC_I2C2_CLKSOURCE_PSIK  (*)
  *         @arg @ref LL_RCC_I2C2_CLKSOURCE_HSIK  (*)
  * @endif
  * @if ETH
  *         @arg @ref LL_RCC_ETHREF_CLKSOURCE_RMII  (*)
  *         @arg @ref LL_RCC_ETHREF_CLKSOURCE_FB    (*)
  *         @arg @ref LL_RCC_ETHPTP_CLKSOURCE_HCLK  (*)
  *         @arg @ref LL_RCC_ETHPTP_CLKSOURCE_PSIS  (*)
  *         @arg @ref LL_RCC_ETHPTP_CLKSOURCE_PSIK  (*)
  *         @arg @ref LL_RCC_ETH_CLKSOURCE_NONE     (*)
  *         @arg @ref LL_RCC_ETH_CLKSOURCE_PSIS     (*)
  *         @arg @ref LL_RCC_ETH_CLKSOURCE_PSIK     (*)
  *         @arg @ref LL_RCC_ETH_CLKSOURCE_HSE      (*)
  * @endif
  *
  *         (*) value not defined in all devices.
  */
__STATIC_INLINE uint32_t LL_RCC_GetClockSource(uint32_t Periph)
{
  const volatile uint32_t *pReg = (uint32_t *)((uint32_t)((uint32_t)(&RCC->CCIPR1) + LL_CLKSOURCE_REG(Periph)));
  return (uint32_t)(Periph | (((READ_BIT(*pReg, LL_CLKSOURCE_MASK(Periph))) >> LL_CLKSOURCE_POS(Periph)) \
                              << LL_RCC_CONFIG_SHIFT));
}
/**
  * @brief  Get USARTx clock source
  * @rmtoll
  *  CCIPR1         USART1SEL         LL_RCC_GetUSARTClockSource \n
  *  CCIPR1         USART2SEL         LL_RCC_GetUSARTClockSource \n
  *  CCIPR1         USART3SEL         LL_RCC_GetUSARTClockSource \n
  *  CCIPR1         USART6SEL         LL_RCC_GetUSARTClockSource
  * @param  Periph This parameter can be one of the following values:
  *         @arg @ref LL_RCC_USART1_CLKSOURCE
  *         @arg @ref LL_RCC_USART2_CLKSOURCE
  * @if USART3
  *         @arg @ref LL_RCC_USART3_CLKSOURCE (*)
  * @endif
  * @if USART6
  *         @arg @ref LL_RCC_USART6_CLKSOURCE (*)
  * @endif
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_USART1_CLKSOURCE_PCLK2
  *         @arg @ref LL_RCC_USART1_CLKSOURCE_PSIK
  *         @arg @ref LL_RCC_USART1_CLKSOURCE_HSIK
  *         @arg @ref LL_RCC_USART1_CLKSOURCE_LSE
  *         @arg @ref LL_RCC_USART2_CLKSOURCE_PCLK1
  *         @arg @ref LL_RCC_USART2_CLKSOURCE_PSIK
  *         @arg @ref LL_RCC_USART2_CLKSOURCE_HSIK
  *         @arg @ref LL_RCC_USART2_CLKSOURCE_LSE
  * @if USART3
  *         @arg @ref LL_RCC_USART3_CLKSOURCE_PCLK1 (*)
  *         @arg @ref LL_RCC_USART3_CLKSOURCE_PSIK  (*)
  *         @arg @ref LL_RCC_USART3_CLKSOURCE_HSIK  (*)
  *         @arg @ref LL_RCC_USART3_CLKSOURCE_LSE   (*)
  * @endif
  * @if USART6
  *         @arg @ref LL_RCC_USART6_CLKSOURCE_PCLK1 (*)
  *         @arg @ref LL_RCC_USART6_CLKSOURCE_PSIK  (*)
  *         @arg @ref LL_RCC_USART6_CLKSOURCE_HSIK  (*)
  *         @arg @ref LL_RCC_USART6_CLKSOURCE_LSE   (*)
  * @endif
  *
  *         (*) value not defined in all devices.
  */
__STATIC_INLINE uint32_t LL_RCC_GetUSARTClockSource(uint32_t Periph)
{
  return LL_RCC_GetClockSource(Periph);
}
/**
  * @brief  Get UARTx clock source
  * @rmtoll
  *  CCIPR1         UART4SEL         LL_RCC_GetUARTClockSource \n
  *  CCIPR1         UART5SEL         LL_RCC_GetUARTClockSource \n
  *  CCIPR1         UART7SEL         LL_RCC_GetUARTClockSource
  * @param  Periph This parameter can be one of the following values:
  *         @arg @ref LL_RCC_UART4_CLKSOURCE
  *         @arg @ref LL_RCC_UART5_CLKSOURCE
  * @if UART7
  *         @arg @ref LL_RCC_UART7_CLKSOURCE (*)
  * @endif
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_UART4_CLKSOURCE_PCLK1
  *         @arg @ref LL_RCC_UART4_CLKSOURCE_PSIK
  *         @arg @ref LL_RCC_UART4_CLKSOURCE_HSIK
  *         @arg @ref LL_RCC_UART4_CLKSOURCE_LSE
  *         @arg @ref LL_RCC_UART5_CLKSOURCE_PCLK1
  *         @arg @ref LL_RCC_UART5_CLKSOURCE_PSIK
  *         @arg @ref LL_RCC_UART5_CLKSOURCE_HSIK
  *         @arg @ref LL_RCC_UART5_CLKSOURCE_LSE
  * @if UART7
  *         @arg @ref LL_RCC_UART7_CLKSOURCE_PCLK1  (*)
  *         @arg @ref LL_RCC_UART7_CLKSOURCE_PSIK   (*)
  *         @arg @ref LL_RCC_UART7_CLKSOURCE_HSIK   (*)
  *         @arg @ref LL_RCC_UART7_CLKSOURCE_LSE    (*)
  * @endif
  *
  *         (*) value not defined in all devices.
  */
__STATIC_INLINE uint32_t LL_RCC_GetUARTClockSource(uint32_t Periph)
{
  return LL_RCC_GetClockSource(Periph);
}
/**
  * @brief  Get LPUARTx clock source
  * @rmtoll
  *  CCIPR1         LPUART1SEL         LL_RCC_GetLPUARTClockSource
  * @param  Periph This parameter can be one of the following values:
  *         @arg @ref LL_RCC_LPUART1_CLKSOURCE
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_LPUART1_CLKSOURCE_PCLK3
  *         @arg @ref LL_RCC_LPUART1_CLKSOURCE_HSIK
  *         @arg @ref LL_RCC_LPUART1_CLKSOURCE_LSE
  *         @arg @ref LL_RCC_LPUART1_CLKSOURCE_LSI
  */
__STATIC_INLINE uint32_t LL_RCC_GetLPUARTClockSource(uint32_t Periph)
{
  UNUSED(Periph);
  return (uint32_t)(READ_BIT(RCC->CCIPR1, RCC_CCIPR1_LPUART1SEL));
}
/**
  * @brief  Get SPIx clock source
  * @rmtoll
  *  CCIPR1         SPI1SEL         LL_RCC_GetSPIClockSource \n
  *  CCIPR1         SPI2SEL         LL_RCC_GetSPIClockSource \n
  *  CCIPR1         SPI3SEL         LL_RCC_GetSPIClockSource
  * @param  Periph This parameter can be one of the following values:
  *         @arg @ref LL_RCC_SPI1_CLKSOURCE
  *         @arg @ref LL_RCC_SPI2_CLKSOURCE
  *         @arg @ref LL_RCC_SPI3_CLKSOURCE
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_SPI1_CLKSOURCE_PCLK2
  *         @arg @ref LL_RCC_SPI1_CLKSOURCE_PSIK
  *         @arg @ref LL_RCC_SPI1_CLKSOURCE_HSIK
  *         @arg @ref LL_RCC_SPI1_CLKSOURCE_AUDIOCLK
  *         @arg @ref LL_RCC_SPI2_CLKSOURCE_PCLK1
  *         @arg @ref LL_RCC_SPI2_CLKSOURCE_PSIK
  *         @arg @ref LL_RCC_SPI2_CLKSOURCE_HSIK
  *         @arg @ref LL_RCC_SPI2_CLKSOURCE_AUDIOCLK
  * @if SPI3
  *         @arg @ref LL_RCC_SPI3_CLKSOURCE_PCLK1     (*)
  *         @arg @ref LL_RCC_SPI3_CLKSOURCE_PSIK      (*)
  *         @arg @ref LL_RCC_SPI3_CLKSOURCE_HSIK      (*)
  *         @arg @ref LL_RCC_SPI3_CLKSOURCE_AUDIOCLK  (*)
  * @endif
  */
__STATIC_INLINE uint32_t LL_RCC_GetSPIClockSource(uint32_t Periph)
{
  return LL_RCC_GetClockSource(Periph);
}
#if defined(FDCAN1)

/**
  * @brief  Get FDCANx clock source
  * @rmtoll
  *  CCIPR1         FDCANSEL         LL_RCC_GetFDCANClockSource
  * @param  Periph This parameter can be one of the following values:
  *         @arg @ref LL_RCC_FDCAN_CLKSOURCE
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_FDCAN_CLKSOURCE_PCLK1
  *         @arg @ref LL_RCC_FDCAN_CLKSOURCE_PSIS
  *         @arg @ref LL_RCC_FDCAN_CLKSOURCE_PSIK
  *         @arg @ref LL_RCC_FDCAN_CLKSOURCE_HSE
  */
__STATIC_INLINE uint32_t LL_RCC_GetFDCANClockSource(uint32_t Periph)
{
  UNUSED(Periph);
  return (uint32_t)(READ_BIT(RCC->CCIPR1, RCC_CCIPR1_FDCANSEL));
}

#endif /* FDCAN1 */
/**
  * @brief  Get I2Cx clock source
  * @rmtoll
  *  CCIPR2         I2C1SEL         LL_RCC_GetI2CClockSource \n
  *  CCIPR2         I2C2SEL         LL_RCC_GetI2CClockSource
  * @param  Periph This parameter can be one of the following values:
  *         @arg @ref LL_RCC_I2C1_CLKSOURCE
  *         @arg @ref LL_RCC_I2C2_CLKSOURCE
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_I2C1_CLKSOURCE_PCLK1
  *         @arg @ref LL_RCC_I2C1_CLKSOURCE_PSIK
  *         @arg @ref LL_RCC_I2C1_CLKSOURCE_HSIK
  * @if I2C2
  *         @arg @ref LL_RCC_I2C2_CLKSOURCE_PCLK1  (*)
  *         @arg @ref LL_RCC_I2C2_CLKSOURCE_PSIK   (*)
  *         @arg @ref LL_RCC_I2C2_CLKSOURCE_HSIK   (*)
  * @endif
  */
__STATIC_INLINE uint32_t LL_RCC_GetI2CClockSource(uint32_t Periph)
{
  return LL_RCC_GetClockSource(Periph);
}
/**
  * @brief  Get I3Cx clock source
  * @rmtoll
  *  CCIPR2         I3C1SEL         LL_RCC_GetI3CClockSource
  * @param  Periph This parameter can be one of the following values:
  *         @arg @ref LL_RCC_I3C1_CLKSOURCE
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_I3C1_CLKSOURCE_PCLK1
  *         @arg @ref LL_RCC_I3C1_CLKSOURCE_PSIK
  *         @arg @ref LL_RCC_I3C1_CLKSOURCE_HSIK
  */
__STATIC_INLINE uint32_t LL_RCC_GetI3CClockSource(uint32_t Periph)
{
  UNUSED(Periph);
  return (uint32_t)(READ_BIT(RCC->CCIPR2, RCC_CCIPR2_I3C1SEL));
}
/**
  * @brief  Get ADCDACx clock source
  * @rmtoll
  *  CCIPR2         ADCDACSEL         LL_RCC_GetADCDACClockSource
  * @param  Periph This parameter can be one of the following values:
  *         @arg @ref LL_RCC_ADCDAC_CLKSOURCE
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_ADCDAC_CLKSOURCE_HCLK
  *         @arg @ref LL_RCC_ADCDAC_CLKSOURCE_PSIS
  *         @arg @ref LL_RCC_ADCDAC_CLKSOURCE_PSIK
  *         @arg @ref LL_RCC_ADCDAC_CLKSOURCE_HSIK
  */
__STATIC_INLINE uint32_t LL_RCC_GetADCDACClockSource(uint32_t Periph)
{
  UNUSED(Periph);
  return (uint32_t)(READ_BIT(RCC->CCIPR2, RCC_CCIPR2_ADCDACSEL));
}
/**
  * @brief  Get ADCDACx clock prescaler
  * @rmtoll
  *  CCIPR2         ADCDACSEL         LL_RCC_GetADCDACPrescaler
  * @param  Periph This parameter can be one of the following values:
  *         @arg @ref LL_RCC_ADCDAC_CLKSOURCE
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_ADCDAC_PRESCALER_1
  *         @arg @ref LL_RCC_ADCDAC_PRESCALER_2
  *         @arg @ref LL_RCC_ADCDAC_PRESCALER_4
  *         @arg @ref LL_RCC_ADCDAC_PRESCALER_8
  *         @arg @ref LL_RCC_ADCDAC_PRESCALER_16
  *         @arg @ref LL_RCC_ADCDAC_PRESCALER_32
  *         @arg @ref LL_RCC_ADCDAC_PRESCALER_64
  *         @arg @ref LL_RCC_ADCDAC_PRESCALER_128
  */
__STATIC_INLINE uint32_t LL_RCC_GetADCDACPrescaler(uint32_t Periph)
{
  UNUSED(Periph);
  return (uint32_t)(READ_BIT(RCC->CCIPR2, RCC_CCIPR2_ADCDACPRE));
}
/**
  * @brief  Get DAC1 clock source
  * @rmtoll
  *  CCIPR2         DACSEL         LL_RCC_GetDACClockSource
  * @param  Periph This parameter can be one of the following values:
  *         @arg @ref LL_RCC_DAC1_CLKSOURCE
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_DAC1SH_CLKSOURCE_LSE
  *         @arg @ref LL_RCC_DAC1SH_CLKSOURCE_LSI
  */
__STATIC_INLINE uint32_t LL_RCC_GetDAC1ClockSource(uint32_t Periph)
{
  UNUSED(Periph);
  return (uint32_t)(READ_BIT(RCC->CCIPR2, RCC_CCIPR2_DACSEL));
}
/**
  * @brief  Get LPTIMx clock source
  * @rmtoll
  *  CCIPR2         LPTIM1SEL         LL_RCC_GetLPTIMClockSource
  * @param  Periph This parameter can be one of the following values:
  *         @arg @ref LL_RCC_LPTIM1_CLKSOURCE
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_LPTIM1_CLKSOURCE_PCLK3
  *         @arg @ref LL_RCC_LPTIM1_CLKSOURCE_HSIK
  *         @arg @ref LL_RCC_LPTIM1_CLKSOURCE_LSE
  *         @arg @ref LL_RCC_LPTIM1_CLKSOURCE_LSI
  */
__STATIC_INLINE uint32_t LL_RCC_GetLPTIMClockSource(uint32_t Periph)
{
  UNUSED(Periph);
  return (uint32_t)(READ_BIT(RCC->CCIPR2, RCC_CCIPR2_LPTIM1SEL));
}
/**
  * @brief  Get CKx clock source
  * @rmtoll
  *  CCIPR2         CK48SEL         LL_RCC_GetCKClockSource
  * @param  Periph This parameter can be one of the following values:
  *         @arg @ref LL_RCC_CK48_CLKSOURCE
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_CK48_CLKSOURCE_PSI_DIV_3
  *         @arg @ref LL_RCC_CK48_CLKSOURCE_HSI_DIV_3
  *         @arg @ref LL_RCC_CK48_CLKSOURCE_HSE
  */
__STATIC_INLINE uint32_t LL_RCC_GetCKClockSource(uint32_t Periph)
{
  UNUSED(Periph);
  return (uint32_t)(READ_BIT(RCC->CCIPR2, RCC_CCIPR2_CK48SEL));
}

#if defined(XSPI1)
/**
  * @brief  Get XSPIx clock source
  * @rmtoll
  *  CCIPR3         XSPI1SEL         LL_RCC_GetXSPIClockSource
  * @param  Periph This parameter can be one of the following values:
  *         @arg @ref LL_RCC_XSPI1_CLKSOURCE
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_XSPI1_CLKSOURCE_HCLK
  *         @arg @ref LL_RCC_XSPI1_CLKSOURCE_PSIK
  *         @arg @ref LL_RCC_XSPI1_CLKSOURCE_HSIK
  */
__STATIC_INLINE uint32_t LL_RCC_GetXSPIClockSource(uint32_t Periph)
{
  UNUSED(Periph);
  return (uint32_t)(READ_BIT(RCC->CCIPR3, RCC_CCIPR3_XSPI1SEL));
}

#endif /* XSPI1 */
#if defined(ETH)
/**
  * @brief  Get UARTx clock source
  * @rmtoll
  *  CCIPR3         ETHREFCLKSEL         LL_RCC_GetETHClockSource \n
  *  CCIPR3         ETHPTPCLKSEL         LL_RCC_GetETHClockSource \n
  *  CCIPR3         ETHCLKSEL            LL_RCC_GetETHClockSource
  * @param  Periph This parameter can be one of the following values:
  *         @arg @ref LL_RCC_ETHREF_CLKSOURCE
  *         @arg @ref LL_RCC_ETHPTP_CLKSOURCE
  *         @arg @ref LL_RCC_ETH_CLKSOURCE
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_ETHREF_CLKSOURCE_RMII
  *         @arg @ref LL_RCC_ETHREF_CLKSOURCE_FB
  *         @arg @ref LL_RCC_ETHPTP_CLKSOURCE_HCLK
  *         @arg @ref LL_RCC_ETHPTP_CLKSOURCE_PSIS
  *         @arg @ref LL_RCC_ETHPTP_CLKSOURCE_PSIK
  *         @arg @ref LL_RCC_ETH_CLKSOURCE_PSIS
  *         @arg @ref LL_RCC_ETH_CLKSOURCE_PSIK
  *         @arg @ref LL_RCC_ETH_CLKSOURCE_HSE
  */
__STATIC_INLINE uint32_t LL_RCC_GetETHClockSource(uint32_t Periph)
{
  return LL_RCC_GetClockSource(Periph);
}

/**
  * @brief  Get ETH clock prescaler
  * @rmtoll
  *  CCIPR3         ETHCLKDIVSEL         LL_RCC_GetETHPrescaler
  * @param  Periph This parameter can be one of the following values:
  *         @arg @ref LL_RCC_ETH_CLKSOURCE
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_ETH_DIV_1
  *         @arg @ref LL_RCC_ETH_DIV_2
  *         @arg @ref LL_RCC_ETH_DIV_4
  */
__STATIC_INLINE uint32_t LL_RCC_GetETHPrescaler(void)
{
  return (uint32_t)(READ_BIT(RCC->CCIPR3, RCC_CCIPR3_ETHCLKDIVSEL));
}

/**
  * @brief  Get ETHPTP clock prescaler
  * @rmtoll
  *  CCIPR3         ETHPTPDIVSEL         LL_RCC_GetETHPTPPrescaler
  * @if ETH
  * @param  Periph This parameter can be one of the following values:
  *         @arg @ref LL_RCC_ETHPTP_CLKSOURCE
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_ETHPTP_DIV_1
  *         @arg @ref LL_RCC_ETHPTP_DIV_2
  *         @arg @ref LL_RCC_ETHPTP_DIV_3
  *         @arg @ref LL_RCC_ETHPTP_DIV_4
  *         @arg @ref LL_RCC_ETHPTP_DIV_5
  *         @arg @ref LL_RCC_ETHPTP_DIV_6
  *         @arg @ref LL_RCC_ETHPTP_DIV_7
  *         @arg @ref LL_RCC_ETHPTP_DIV_8
  * @endif
  */
__STATIC_INLINE uint32_t LL_RCC_GetETHPTPPrescaler(void)
{
  return (uint32_t)(READ_BIT(RCC->CCIPR3, RCC_CCIPR3_ETHPTPDIVSEL));
}

#endif /* ETH */
/**
  * @}
  */ /* End of RCC_LL_EF_Peripheral_Clock_Source */

/** @defgroup RCC_LL_EF_RTC RTC
  * @{
  */

/**
  * @brief  Set RTC Clock Source
  * @note   Once the RTC clock source has been selected, it cannot be changed anymore unless
  *         the Backup domain is reset, or unless a failure is detected on LSE (LSECSSD is
  *         set). The VSWRST bit can be used to reset them.
  * @rmtoll
  *  RTCCR         RTCSEL         LL_RCC_SetRTCClockSource
  * @param  Source This parameter can be one of the following values:
  *         @arg @ref LL_RCC_RTC_CLKSOURCE_NONE
  *         @arg @ref LL_RCC_RTC_CLKSOURCE_LSE
  *         @arg @ref LL_RCC_RTC_CLKSOURCE_LSI
  *         @arg @ref LL_RCC_RTC_CLKSOURCE_HSE
  */
__STATIC_INLINE void LL_RCC_SetRTCClockSource(uint32_t Source)
{
  MODIFY_REG(RCC->RTCCR, RCC_RTCCR_RTCSEL, Source);
}

/**
  * @brief  Get RTC Clock Source
  * @rmtoll
  *  RTCCR         RTCSEL         LL_RCC_GetRTCClockSource
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_RTC_CLKSOURCE_NONE
  *         @arg @ref LL_RCC_RTC_CLKSOURCE_LSE
  *         @arg @ref LL_RCC_RTC_CLKSOURCE_LSI
  *         @arg @ref LL_RCC_RTC_CLKSOURCE_HSE
  */
__STATIC_INLINE uint32_t LL_RCC_GetRTCClockSource(void)
{
  return (uint32_t)(READ_BIT(RCC->RTCCR, RCC_RTCCR_RTCSEL));
}

/**
  * @brief  Enable RTC
  * @rmtoll
  *  RTCCR         RTCEN         LL_RCC_EnableRTC
  */
__STATIC_INLINE void LL_RCC_EnableRTC(void)
{
  SET_BIT(RCC->RTCCR, RCC_RTCCR_RTCEN);
}

/**
  * @brief  Disable RTC
  * @rmtoll
  *  RTCCR         RTCEN         LL_RCC_DisableRTC
  */
__STATIC_INLINE void LL_RCC_DisableRTC(void)
{
  CLEAR_BIT(RCC->RTCCR, RCC_RTCCR_RTCEN);
}

/**
  * @brief  Check if RTC has been enabled or not
  * @rmtoll
  *  RTCCR         RTCEN         LL_RCC_IsEnabledRTC
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsEnabledRTC(void)
{
  return ((READ_BIT(RCC->RTCCR, RCC_RTCCR_RTCEN) == (RCC_RTCCR_RTCEN)) ? 1UL : 0UL);
}

/**
  * @brief  Force the Backup domain reset
  * @rmtoll
  *  RTCCR         RTCDRST         LL_RCC_ForceRTCDomainReset
  */
__STATIC_INLINE void LL_RCC_ForceRTCDomainReset(void)
{
  SET_BIT(RCC->RTCCR, RCC_RTCCR_RTCDRST);
}

/**
  * @brief  Release the Backup domain reset
  * @rmtoll
  *  RTCCR         RTCDRST         LL_RCC_ReleaseRTCDomainReset
  */
__STATIC_INLINE void LL_RCC_ReleaseRTCDomainReset(void)
{
  CLEAR_BIT(RCC->RTCCR, RCC_RTCCR_RTCDRST);
}

/**
  * @brief  Get HSE Prescaler for RTC Clock
  * @rmtoll
  *  CFGR1         RTCPRE         LL_RCC_GetRTC_HSEPrescaler
  * @retval  Prescaler This parameter can be one of the following values:
  *         @arg @ref LL_RCC_RTC_HSE_DIV_DIS
  *         @arg /ref LL_RCC_RTC_HSE_DIV_xxx
  * note : x value between 1 and 511
  */
__STATIC_INLINE uint32_t LL_RCC_GetRTC_HSEPrescaler(void)
{
  return READ_BIT(RCC->CFGR1, RCC_CFGR1_RTCPRE);
}

/**
  * @brief  Set HSE Prescaler for RTC Clock
  * @rmtoll
  *  CFGR1         RTCPRE         LL_RCC_SetRTC_HSEPrescaler
  * @param  Prescaler This parameter can be one of the following values:
  *         @arg @ref LL_RCC_RTC_HSE_DIV_DIS
  *         @arg /ref LL_RCC_RTC_HSE_DIV_xxx
  *
  * note : x value between 1 and 511
  */
__STATIC_INLINE void LL_RCC_SetRTC_HSEPrescaler(uint32_t Prescaler)
{
  MODIFY_REG(RCC->CFGR1, RCC_CFGR1_RTCPRE, Prescaler);
}

/**
  * @}
  */ /* End of RCC_LL_EF_RTC */

/**
  * @brief  Set ADC Clock Prescaler
  * @rmtoll CCIPR2          ADCDACPRE      LL_RCC_SetADCPrescaler
  * @param  prescaler This parameter can be one of the following values:
  *         @arg @ref LL_RCC_ADCDAC_PRESCALER_1
  *         @arg @ref LL_RCC_ADCDAC_PRESCALER_2
  *         @arg @ref LL_RCC_ADCDAC_PRESCALER_4
  *         @arg @ref LL_RCC_ADCDAC_PRESCALER_8
  *         @arg @ref LL_RCC_ADCDAC_PRESCALER_16
  *         @arg @ref LL_RCC_ADCDAC_PRESCALER_32
  *         @arg @ref LL_RCC_ADCDAC_PRESCALER_64
  *         @arg @ref LL_RCC_ADCDAC_PRESCALER_128
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SetADCPrescaler(uint32_t prescaler)
{
  MODIFY_REG(RCC->CCIPR2, RCC_CCIPR2_ADCDACPRE, prescaler);
}

/**
  * @brief  Get ADC Clock Prescaler
  * @rmtoll CCIPR2          ADCDACPRE      LL_RCC_GetADCPrescaler
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_ADCDAC_PRESCALER_1
  *         @arg @ref LL_RCC_ADCDAC_PRESCALER_2
  *         @arg @ref LL_RCC_ADCDAC_PRESCALER_4
  *         @arg @ref LL_RCC_ADCDAC_PRESCALER_8
  *         @arg @ref LL_RCC_ADCDAC_PRESCALER_16
  *         @arg @ref LL_RCC_ADCDAC_PRESCALER_32
  *         @arg @ref LL_RCC_ADCDAC_PRESCALER_64
  *         @arg @ref LL_RCC_ADCDAC_PRESCALER_128
  */
__STATIC_INLINE uint32_t LL_RCC_GetADCPrescaler(void)
{
  return (uint32_t)(READ_BIT(RCC->CCIPR2, RCC_CCIPR2_ADCDACPRE));
}


/** @defgroup RCC_LL_EF_PRIV Privileged mode
  * @{
  */

/**
  * @brief  Enable privileged mode
  * @rmtoll
  *  PRIVCFGR         PRIV          LL_RCC_EnablePrivilegedMode
  *         This API is kept for legacy purpose only.
  */
__STATIC_INLINE void LL_RCC_EnablePrivilegedMode(void)
{
  SET_BIT(RCC->PRIVCFGR, RCC_PRIVCFGR_PRIV);
}

/**
  * @brief  Disable Privileged mode
  * @rmtoll
  *  PRIVCFGR         PRIV          LL_RCC_DisablePrivilegedMode
  *         This API is kept for legacy purpose only.
  */
__STATIC_INLINE void LL_RCC_DisablePrivilegedMode(void)
{
  CLEAR_BIT(RCC->PRIVCFGR, RCC_PRIVCFGR_PRIV);
}

/**
  * @brief  Check if Privileged mode has been enabled or not
  * @rmtoll
  *  PRIVCFGR         PRIV          LL_RCC_IsEnabledPrivilegedMode
  *         This API is kept for legacy purpose only.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsEnabledPrivilegedMode(void)
{
  return ((READ_BIT(RCC->PRIVCFGR, RCC_PRIVCFGR_PRIV) == RCC_PRIVCFGR_PRIV) ? 1UL : 0UL);
}

/**
  * @}
  */ /* End of RCC_LL_EF_PRIV */

/** @defgroup RCC_LL_EF_FLAG_Management FLAG Management
  * @{
  */
/**
  * @brief  Clear RCC interrupt flags
  * @rmtoll
  *  CICR         LSIRDYC             LL_RCC_ClearFlag \n
  *  CICR         LSERDYC             LL_RCC_ClearFlag \n
  *  CICR         HSIRDYC             LL_RCC_ClearFlag \n
  *  CICR         HSIDIV3RDYC         LL_RCC_ClearFlag \n
  *  CICR         HSIKRDYC            LL_RCC_ClearFlag \n
  *  CICR         PSIRDYC             LL_RCC_ClearFlag \n
  *  CICR         PSIDIV3RDYC         LL_RCC_ClearFlag \n
  *  CICR         PSIKRDYC            LL_RCC_ClearFlag \n
  *  CICR         HSERDYC             LL_RCC_ClearFlag \n
  *  CICR         HSECSSC             LL_RCC_ClearFlag \n
  *  CICR         LSECSSC             LL_RCC_ClearFlag
  * @param  mask specifies the RCC flags to be cleared.
  *         This parameter can be any combination of the following values:
  *            @arg @ref LL_RCC_IT_LSIRDY
  *            @arg @ref LL_RCC_IT_LSERDY
  *            @arg @ref LL_RCC_IT_HSIRDY
  *            @arg @ref LL_RCC_IT_HSIDIV3RDY
  *            @arg @ref LL_RCC_IT_HSIKRDY
  *            @arg @ref LL_RCC_IT_PSIRDY
  *            @arg @ref LL_RCC_IT_PSIDIV3RDY
  *            @arg @ref LL_RCC_IT_PSIKRDY
  *            @arg @ref LL_RCC_IT_HSERDY
  *            @arg @ref LL_RCC_IT_HSECSS
  *            @arg @ref LL_RCC_IT_LSECSS
  */
__STATIC_INLINE void LL_RCC_ClearFlag(uint32_t mask)
{
  WRITE_REG(RCC->CICR, mask);
}
/**
  * @brief  Clear LSIRDY ready interrupt flag
  * @rmtoll
  *  CICR         LSIRDYC         LL_RCC_ClearFlag_LSIRDY
  */
__STATIC_INLINE void LL_RCC_ClearFlag_LSIRDY(void)
{
  SET_BIT(RCC->CICR, RCC_CICR_LSIRDYC);
}
/**
  * @brief  Clear LSERDY ready interrupt flag
  * @rmtoll
  *  CICR         LSERDYC         LL_RCC_ClearFlag_LSERDY
  */
__STATIC_INLINE void LL_RCC_ClearFlag_LSERDY(void)
{
  SET_BIT(RCC->CICR, RCC_CICR_LSERDYC);
}
/**
  * @brief  Clear HSIRDY ready interrupt flag
  * @rmtoll
  *  CICR         HSIRDYC         LL_RCC_ClearFlag_HSIRDY
  */
__STATIC_INLINE void LL_RCC_ClearFlag_HSIRDY(void)
{
  SET_BIT(RCC->CICR, RCC_CICR_HSISRDYC);
}
/**
  * @brief  Clear HSIDIV3RDY ready interrupt flag
  * @rmtoll
  *  CICR         HSIDIV3RDYC         LL_RCC_ClearFlag_HSIDIV3RDY
  */
__STATIC_INLINE void LL_RCC_ClearFlag_HSIDIV3RDY(void)
{
  SET_BIT(RCC->CICR, RCC_CICR_HSIDIV3RDYC);
}
/**
  * @brief  Clear HSIKRDY ready interrupt flag
  * @rmtoll
  *  CICR         HSIKRDYC         LL_RCC_ClearFlag_HSIKRDY
  */
__STATIC_INLINE void LL_RCC_ClearFlag_HSIKRDY(void)
{
  SET_BIT(RCC->CICR, RCC_CICR_HSIKRDYC);
}
/**
  * @brief  Clear PSIRDY ready interrupt flag
  * @rmtoll
  *  CICR         PSIRDYC         LL_RCC_ClearFlag_PSIRDY
  */
__STATIC_INLINE void LL_RCC_ClearFlag_PSIRDY(void)
{
  SET_BIT(RCC->CICR, RCC_CICR_PSISRDYC);
}
/**
  * @brief  Clear PSIDIV3RDY ready interrupt flag
  * @rmtoll
  *  CICR         PSIDIV3RDYC         LL_RCC_ClearFlag_PSIDIV3RDY
  */
__STATIC_INLINE void LL_RCC_ClearFlag_PSIDIV3RDY(void)
{
  SET_BIT(RCC->CICR, RCC_CICR_PSIDIV3RDYC);
}
/**
  * @brief  Clear PSIKRDY ready interrupt flag
  * @rmtoll
  *  CICR         PSIKRDYC         LL_RCC_ClearFlag_PSIKRDY
  */
__STATIC_INLINE void LL_RCC_ClearFlag_PSIKRDY(void)
{
  SET_BIT(RCC->CICR, RCC_CICR_PSIKRDYC);
}
/**
  * @brief  Clear HSERDY ready interrupt flag
  * @rmtoll
  *  CICR         HSERDYC         LL_RCC_ClearFlag_HSERDY
  */
__STATIC_INLINE void LL_RCC_ClearFlag_HSERDY(void)
{
  SET_BIT(RCC->CICR, RCC_CICR_HSERDYC);
}
/**
  * @brief  Clear HSECSS ready interrupt flag
  * @rmtoll
  *  CICR         HSECSSC         LL_RCC_ClearFlag_HSECSS
  */
__STATIC_INLINE void LL_RCC_ClearFlag_HSECSS(void)
{
  SET_BIT(RCC->CICR, RCC_CICR_HSECSSC);
}

/**
  * @brief  Clear LSECSS ready interrupt flag
  * @rmtoll
  *  CICR         LSECSSC         LL_RCC_ClearFlag_LSECSS
  */
__STATIC_INLINE void LL_RCC_ClearFlag_LSECSS(void)
{
  SET_BIT(RCC->CICR, RCC_CICR_LSECSSC);
}


/**
  * @brief  Check if RCC ready interrupt occurred or not
  * @rmtoll
  *  CIFR         LSIRDYF             LL_RCC_IsActiveFlag \n
  *  CIFR         LSERDYF             LL_RCC_IsActiveFlag \n
  *  CIFR         HSIRDYF             LL_RCC_IsActiveFlag \n
  *  CIFR         HSIDIV3RDYF         LL_RCC_IsActiveFlag \n
  *  CIFR         HSIKRDYF            LL_RCC_IsActiveFlag \n
  *  CIFR         PSIRDYF             LL_RCC_IsActiveFlag \n
  *  CIFR         PSIDIV3RDYF         LL_RCC_IsActiveFlag \n
  *  CIFR         PSIKRDYF            LL_RCC_IsActiveFlag \n
  *  CIFR         HSERDYF             LL_RCC_IsActiveFlag \n
  *  CIFR         HSECSSF             LL_RCC_IsActiveFlag \n
  *  CIFR         LSECSSF             LL_RCC_IsActiveFlag
  * @param  mask specifies the RCC flags to be cleared.
  *         This parameter can be any combination of the following values:
  *            @arg @ref LL_RCC_IT_LSIRDY
  *            @arg @ref LL_RCC_IT_LSERDY
  *            @arg @ref LL_RCC_IT_HSIRDY
  *            @arg @ref LL_RCC_IT_HSIDIV3RDY
  *            @arg @ref LL_RCC_IT_HSIKRDY
  *            @arg @ref LL_RCC_IT_PSIRDY
  *            @arg @ref LL_RCC_IT_PSIDIV3RDY
  *            @arg @ref LL_RCC_IT_PSIKRDY
  *            @arg @ref LL_RCC_IT_HSERDY
  *            @arg @ref LL_RCC_IT_HSECSS
  *            @arg @ref LL_RCC_IT_LSECSS
  * @retval State of flags (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag(uint32_t mask)
{
  return ((READ_BIT(RCC->CIFR, mask) == mask) ? 1UL : 0UL);
}

/**
  * @brief  Check if LSIRDY ready interrupt occurred or not
  * @rmtoll
  *  CIFR         LSIRDYF         LL_RCC_IsActiveFlag_LSIRDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_LSIRDY(void)
{
  return ((READ_BIT(RCC->CIFR, RCC_CIFR_LSIRDYF) == RCC_CIFR_LSIRDYF) ? 1UL : 0UL);
}

/**
  * @brief  Check if LSERDY ready interrupt occurred or not
  * @rmtoll
  *  CIFR         LSERDYF         LL_RCC_IsActiveFlag_LSERDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_LSERDY(void)
{
  return ((READ_BIT(RCC->CIFR, RCC_CIFR_LSERDYF) == RCC_CIFR_LSERDYF) ? 1UL : 0UL);
}

/**
  * @brief  Check if HSIRDY ready interrupt occurred or not
  * @rmtoll
  *  CIFR         HSIRDYF         LL_RCC_IsActiveFlag_HSIRDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_HSIRDY(void)
{
  return ((READ_BIT(RCC->CIFR, RCC_CIFR_HSISRDYF) == RCC_CIFR_HSISRDYF) ? 1UL : 0UL);
}

/**
  * @brief  Check if HSIDIV3RDY ready interrupt occurred or not
  * @rmtoll
  *  CIFR         HSIDIV3RDYF         LL_RCC_IsActiveFlag_HSIDIV3RDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_HSIDIV3RDY(void)
{
  return ((READ_BIT(RCC->CIFR, RCC_CIFR_HSIDIV3RDYF) == RCC_CIFR_HSIDIV3RDYF) ? 1UL : 0UL);
}

/**
  * @brief  Check if HSIKRDY ready interrupt occurred or not
  * @rmtoll
  *  CIFR         HSIKRDYF         LL_RCC_IsActiveFlag_HSIKRDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_HSIKRDY(void)
{
  return ((READ_BIT(RCC->CIFR, RCC_CIFR_HSIKRDYF) == RCC_CIFR_HSIKRDYF) ? 1UL : 0UL);
}

/**
  * @brief  Check if PSIRDY ready interrupt occurred or not
  * @rmtoll
  *  CIFR         PSIRDYF         LL_RCC_IsActiveFlag_PSIRDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_PSIRDY(void)
{
  return ((READ_BIT(RCC->CIFR, RCC_CIFR_PSISRDYF) == RCC_CIFR_PSISRDYF) ? 1UL : 0UL);
}

/**
  * @brief  Check if PSIDIV3RDY ready interrupt occurred or not
  * @rmtoll
  *  CIFR         PSIDIV3RDYF         LL_RCC_IsActiveFlag_PSIDIV3RDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_PSIDIV3RDY(void)
{
  return ((READ_BIT(RCC->CIFR, RCC_CIFR_PSIDIV3RDYF) == RCC_CIFR_PSIDIV3RDYF) ? 1UL : 0UL);
}

/**
  * @brief  Check if PSIKRDY ready interrupt occurred or not
  * @rmtoll
  *  CIFR         PSIKRDYF         LL_RCC_IsActiveFlag_PSIKRDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_PSIKRDY(void)
{
  return ((READ_BIT(RCC->CIFR, RCC_CIFR_PSIKRDYF) == RCC_CIFR_PSIKRDYF) ? 1UL : 0UL);
}

/**
  * @brief  Check if HSERDY ready interrupt occurred or not
  * @rmtoll
  *  CIFR         HSERDYF         LL_RCC_IsActiveFlag_HSERDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_HSERDY(void)
{
  return ((READ_BIT(RCC->CIFR, RCC_CIFR_HSERDYF) == RCC_CIFR_HSERDYF) ? 1UL : 0UL);
}

/**
  * @brief  Check if HSECSS ready interrupt occurred or not
  * @rmtoll
  *  CIFR         HSECSSF         LL_RCC_IsActiveFlag_HSECSS
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_HSECSS(void)
{
  return ((READ_BIT(RCC->CIFR, RCC_CIFR_HSECSSF) == RCC_CIFR_HSECSSF) ? 1UL : 0UL);
}

/**
  * @brief  Check if LSECSS ready interrupt occurred or not
  * @rmtoll
  *  CIFR         LSECSSF         LL_RCC_IsActiveFlag_LSECSS
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_LSECSS(void)
{
  return ((READ_BIT(RCC->CIFR, RCC_CIFR_LSECSSF) == RCC_CIFR_LSECSSF) ? 1UL : 0UL);
}

/**
  * @brief  Set RMVF bit to clear the reset flags.
  * @rmtoll
  *  RSR          RMVF          LL_RCC_ClearResetFlags
  */
__STATIC_INLINE void LL_RCC_ClearResetFlags(void)
{
  SET_BIT(RCC->RSR, RCC_RSR_RMVF);
}

/**
  * @brief  Check if RCC pin reset flag (NRST) is set or not.
  * @rmtoll
  *  RSR         PINRSTF         LL_RCC_IsActiveFlag_PINRST
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_PINRST(void)
{
  return ((READ_BIT(RCC->RSR, RCC_RSR_PINRSTF) == RCC_RSR_PINRSTF) ? 1UL : 0UL);
}

/**
  * @brief  Check if RCC POR reset flag is set or not.
  * @rmtoll
  *  RSR         BORRSTF         LL_RCC_IsActiveFlag_BORRST
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_BORRST(void)
{
  return ((READ_BIT(RCC->RSR, RCC_RSR_BORRSTF) == RCC_RSR_BORRSTF) ? 1UL : 0UL);
}

/**
  * @brief  Check if RCC system reset from CPU reset flag is set or not.
  * @rmtoll
  *  RSR         SFTRSTF         LL_RCC_IsActiveFlag_SFTRST
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_SFTRST(void)
{
  return ((READ_BIT(RCC->RSR, RCC_RSR_SFTRSTF) == RCC_RSR_SFTRSTF) ? 1UL : 0UL);
}

/**
  * @brief  Check if RCC independent watchdog reset flag is set or not.
  * @rmtoll
  *  RSR         IWDGRSTF         LL_RCC_IsActiveFlag_IWDGRST
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_IWDGRST(void)
{
  return ((READ_BIT(RCC->RSR, RCC_RSR_IWDGRSTF) == RCC_RSR_IWDGRSTF) ? 1UL : 0UL);
}

/**
  * @brief  Check if RCC window watchdog reset flag is set or not.
  * @rmtoll
  *  RSR         WWDGRSTF         LL_RCC_IsActiveFlag_WWDGRST
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_WWDGRST(void)
{
  return ((READ_BIT(RCC->RSR, RCC_RSR_WWDGRSTF) == RCC_RSR_WWDGRSTF) ? 1UL : 0UL);
}

/**
  * @brief  Check if RCC Low-power reset flag is set or not.
  * @rmtoll
  *  RSR         LPWRRSTF         LL_RCC_IsActiveFlag_LPWRRST
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_LPWRRST(void)
{
  return ((READ_BIT(RCC->RSR, RCC_RSR_LPWRRSTF) == RCC_RSR_LPWRRSTF) ? 1UL : 0UL);
}

/**
  * @}
  */ /* End of RCC_LL_EF_FLAG_Management */

/** @defgroup RCC_LL_EF_IT_Management IT Management
  * @{
  */

/**
  * @brief  Enable RCC interrupts
  * @rmtoll
  *  CIER         LSIRDYIE             LL_RCC_EnableIT \n
  *  CIER         LSERDYIE             LL_RCC_EnableIT \n
  *  CIER         HSIRDYIE             LL_RCC_EnableIT \n
  *  CIER         HSIDIV3RDYIE         LL_RCC_EnableIT \n
  *  CIER         HSIKRDYIE            LL_RCC_EnableIT \n
  *  CIER         PSIRDYIE             LL_RCC_EnableIT \n
  *  CIER         PSIDIV3RDYIE         LL_RCC_EnableIT \n
  *  CIER         PSIKRDYIE            LL_RCC_EnableIT \n
  *  CIER         HSERDYIE             LL_RCC_EnableIT
  * @param  mask specifies the RCC IT to be enabled.
  *         This parameter can be any combination of the following values:
  *            @arg @ref LL_RCC_IT_LSIRDY
  *            @arg @ref LL_RCC_IT_LSERDY
  *            @arg @ref LL_RCC_IT_HSIRDY
  *            @arg @ref LL_RCC_IT_HSIDIV3RDY
  *            @arg @ref LL_RCC_IT_HSIKRDY
  *            @arg @ref LL_RCC_IT_PSIRDY
  *            @arg @ref LL_RCC_IT_PSIDIV3RDY
  *            @arg @ref LL_RCC_IT_PSIKRDY
  *            @arg @ref LL_RCC_IT_HSERDY
  */
__STATIC_INLINE void LL_RCC_EnableIT(uint32_t mask)
{
  SET_BIT(RCC->CIER, mask);
}

/**
  * @brief  Enable LSI ready interrupt
  * @rmtoll
  *  CIER         LSIRDYIE         LL_RCC_EnableIT_LSIRDY
  */
__STATIC_INLINE void LL_RCC_EnableIT_LSIRDY(void)
{
  SET_BIT(RCC->CIER, RCC_CIER_LSIRDYIE);
}

/**
  * @brief  Enable LSI ready interrupt
  * @rmtoll
  *  CIER         LSERDYIE         LL_RCC_EnableIT_LSERDY
  */
__STATIC_INLINE void LL_RCC_EnableIT_LSERDY(void)
{
  SET_BIT(RCC->CIER, RCC_CIER_LSERDYIE);
}

/**
  * @brief  Enable LSI ready interrupt
  * @rmtoll
  *  CIER         HSIRDYIE         LL_RCC_EnableIT_HSIRDY
  */
__STATIC_INLINE void LL_RCC_EnableIT_HSIRDY(void)
{
  SET_BIT(RCC->CIER, RCC_CIER_HSISRDYIE);
}

/**
  * @brief  Enable LSI ready interrupt
  * @rmtoll
  *  CIER         HSIDIV3RDYIE         LL_RCC_EnableIT_HSIDIV3RDY
  */
__STATIC_INLINE void LL_RCC_EnableIT_HSIDIV3RDY(void)
{
  SET_BIT(RCC->CIER, RCC_CIER_HSIDIV3RDYIE);
}

/**
  * @brief  Enable LSI ready interrupt
  * @rmtoll
  *  CIER         HSIKRDYIE         LL_RCC_EnableIT_HSIKRDY
  */
__STATIC_INLINE void LL_RCC_EnableIT_HSIKRDY(void)
{
  SET_BIT(RCC->CIER, RCC_CIER_HSIKRDYIE);
}

/**
  * @brief  Enable LSI ready interrupt
  * @rmtoll
  *  CIER         PSIRDYIE         LL_RCC_EnableIT_PSIRDY
  */
__STATIC_INLINE void LL_RCC_EnableIT_PSIRDY(void)
{
  SET_BIT(RCC->CIER, RCC_CIER_PSISRDYIE);
}

/**
  * @brief  Enable LSI ready interrupt
  * @rmtoll
  *  CIER         PSIDIV3RDYIE         LL_RCC_EnableIT_PSIDIV3RDY
  */
__STATIC_INLINE void LL_RCC_EnableIT_PSIDIV3RDY(void)
{
  SET_BIT(RCC->CIER, RCC_CIER_PSIDIV3RDYIE);
}

/**
  * @brief  Enable LSI ready interrupt
  * @rmtoll
  *  CIER         PSIKRDYIE         LL_RCC_EnableIT_PSIKRDY
  */
__STATIC_INLINE void LL_RCC_EnableIT_PSIKRDY(void)
{
  SET_BIT(RCC->CIER, RCC_CIER_PSIKRDYIE);
}

/**
  * @brief  Enable LSI ready interrupt
  * @rmtoll
  *  CIER         HSERDYIE         LL_RCC_EnableIT_HSERDY
  */
__STATIC_INLINE void LL_RCC_EnableIT_HSERDY(void)
{
  SET_BIT(RCC->CIER, RCC_CIER_HSERDYIE);
}


/**
  * @brief  Disable RCC interrupts
  * @rmtoll
  *  CIER         LSIRDYIE             LL_RCC_DisableIT \n
  *  CIER         LSERDYIE             LL_RCC_DisableIT \n
  *  CIER         HSIRDYIE             LL_RCC_DisableIT \n
  *  CIER         HSIDIV3RDYIE         LL_RCC_DisableIT \n
  *  CIER         HSIKRDYIE            LL_RCC_DisableIT \n
  *  CIER         PSIRDYIE             LL_RCC_DisableIT \n
  *  CIER         PSIDIV3RDYIE         LL_RCC_DisableIT \n
  *  CIER         PSIKRDYIE            LL_RCC_DisableIT \n
  *  CIER         HSERDYIE             LL_RCC_DisableIT
  * @param  mask specifies the RCC IT to be disabled.
  *         This parameter can be any combination of the following values:
  *            @arg @ref LL_RCC_IT_LSIRDY
  *            @arg @ref LL_RCC_IT_LSERDY
  *            @arg @ref LL_RCC_IT_HSIRDY
  *            @arg @ref LL_RCC_IT_HSIDIV3RDY
  *            @arg @ref LL_RCC_IT_HSIKRDY
  *            @arg @ref LL_RCC_IT_PSIRDY
  *            @arg @ref LL_RCC_IT_PSIDIV3RDY
  *            @arg @ref LL_RCC_IT_PSIKRDY
  *            @arg @ref LL_RCC_IT_HSERDY
  */
__STATIC_INLINE void LL_RCC_DisableIT(uint32_t mask)
{
  CLEAR_BIT(RCC->CIER, mask);
}

/**
  * @brief  Disable LSI ready interrupt
  * @rmtoll
  *  CIER         LSIRDYIE         LL_RCC_DisableIT_LSIRDY
  */
__STATIC_INLINE void LL_RCC_DisableIT_LSIRDY(void)
{
  CLEAR_BIT(RCC->CIER, RCC_CIER_LSIRDYIE);
}

/**
  * @brief  Disable LSI ready interrupt
  * @rmtoll
  *  CIER         LSERDYIE         LL_RCC_DisableIT_LSERDY
  */
__STATIC_INLINE void LL_RCC_DisableIT_LSERDY(void)
{
  CLEAR_BIT(RCC->CIER, RCC_CIER_LSERDYIE);
}

/**
  * @brief  Disable LSI ready interrupt
  * @rmtoll
  *  CIER         HSIRDYIE         LL_RCC_DisableIT_HSIRDY
  */
__STATIC_INLINE void LL_RCC_DisableIT_HSIRDY(void)
{
  CLEAR_BIT(RCC->CIER, RCC_CIER_HSISRDYIE);
}

/**
  * @brief  Disable LSI ready interrupt
  * @rmtoll
  *  CIER         HSIDIV3RDYIE         LL_RCC_DisableIT_HSIDIV3RDY
  */
__STATIC_INLINE void LL_RCC_DisableIT_HSIDIV3RDY(void)
{
  CLEAR_BIT(RCC->CIER, RCC_CIER_HSIDIV3RDYIE);
}

/**
  * @brief  Disable LSI ready interrupt
  * @rmtoll
  *  CIER         HSIKRDYIE         LL_RCC_DisableIT_HSIKRDY
  */
__STATIC_INLINE void LL_RCC_DisableIT_HSIKRDY(void)
{
  CLEAR_BIT(RCC->CIER, RCC_CIER_HSIKRDYIE);
}

/**
  * @brief  Disable LSI ready interrupt
  * @rmtoll
  *  CIER         PSIRDYIE         LL_RCC_DisableIT_PSIRDY
  */
__STATIC_INLINE void LL_RCC_DisableIT_PSIRDY(void)
{
  CLEAR_BIT(RCC->CIER, RCC_CIER_PSISRDYIE);
}

/**
  * @brief  Disable LSI ready interrupt
  * @rmtoll
  *  CIER         PSIDIV3RDYIE         LL_RCC_DisableIT_PSIDIV3RDY
  */
__STATIC_INLINE void LL_RCC_DisableIT_PSIDIV3RDY(void)
{
  CLEAR_BIT(RCC->CIER, RCC_CIER_PSIDIV3RDYIE);
}

/**
  * @brief  Disable LSI ready interrupt
  * @rmtoll
  *  CIER         PSIKRDYIE         LL_RCC_DisableIT_PSIKRDY
  */
__STATIC_INLINE void LL_RCC_DisableIT_PSIKRDY(void)
{
  CLEAR_BIT(RCC->CIER, RCC_CIER_PSIKRDYIE);
}

/**
  * @brief  Disable LSI ready interrupt
  * @rmtoll
  *  CIER         HSERDYIE         LL_RCC_DisableIT_HSERDY
  */
__STATIC_INLINE void LL_RCC_DisableIT_HSERDY(void)
{
  CLEAR_BIT(RCC->CIER, RCC_CIER_HSERDYIE);
}

/**
  * @brief  Check if LSI ready interrupt source is enabled or disabled.
  * @rmtoll
  *  CIER         LSIRDYIE         LL_RCC_IsEnabledIT_LSIRDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsEnabledIT_LSIRDY(void)
{
  return ((READ_BIT(RCC->CIER, RCC_CIER_LSIRDYIE) == RCC_CIER_LSIRDYIE) ? 1UL : 0UL);
}

/**
  * @brief  Check if LSI ready interrupt source is enabled or disabled.
  * @rmtoll
  *  CIER         LSERDYIE         LL_RCC_IsEnabledIT_LSERDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsEnabledIT_LSERDY(void)
{
  return ((READ_BIT(RCC->CIER, RCC_CIER_LSERDYIE) == RCC_CIER_LSERDYIE) ? 1UL : 0UL);
}

/**
  * @brief  Check if LSI ready interrupt source is enabled or disabled.
  * @rmtoll
  *  CIER         HSIRDYIE         LL_RCC_IsEnabledIT_HSIRDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsEnabledIT_HSIRDY(void)
{
  return ((READ_BIT(RCC->CIER, RCC_CIER_HSISRDYIE) == RCC_CIER_HSISRDYIE) ? 1UL : 0UL);
}

/**
  * @brief  Check if LSI ready interrupt source is enabled or disabled.
  * @rmtoll
  *  CIER         HSIDIV3RDYIE         LL_RCC_IsEnabledIT_HSIDIV3RDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsEnabledIT_HSIDIV3RDY(void)
{
  return ((READ_BIT(RCC->CIER, RCC_CIER_HSIDIV3RDYIE) == RCC_CIER_HSIDIV3RDYIE) ? 1UL : 0UL);
}

/**
  * @brief  Check if LSI ready interrupt source is enabled or disabled.
  * @rmtoll
  *  CIER         HSIKRDYIE         LL_RCC_IsEnabledIT_HSIKRDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsEnabledIT_HSIKRDY(void)
{
  return ((READ_BIT(RCC->CIER, RCC_CIER_HSIKRDYIE) == RCC_CIER_HSIKRDYIE) ? 1UL : 0UL);
}

/**
  * @brief  Check if LSI ready interrupt source is enabled or disabled.
  * @rmtoll
  *  CIER         PSIRDYIE         LL_RCC_IsEnabledIT_PSIRDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsEnabledIT_PSIRDY(void)
{
  return ((READ_BIT(RCC->CIER, RCC_CIER_PSISRDYIE) == RCC_CIER_PSISRDYIE) ? 1UL : 0UL);
}

/**
  * @brief  Check if LSI ready interrupt source is enabled or disabled.
  * @rmtoll
  *  CIER         PSIDIV3RDYIE         LL_RCC_IsEnabledIT_PSIDIV3RDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsEnabledIT_PSIDIV3RDY(void)
{
  return ((READ_BIT(RCC->CIER, RCC_CIER_PSIDIV3RDYIE) == RCC_CIER_PSIDIV3RDYIE) ? 1UL : 0UL);
}

/**
  * @brief  Check if LSI ready interrupt source is enabled or disabled.
  * @rmtoll
  *  CIER         PSIKRDYIE         LL_RCC_IsEnabledIT_PSIKRDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsEnabledIT_PSIKRDY(void)
{
  return ((READ_BIT(RCC->CIER, RCC_CIER_PSIKRDYIE) == RCC_CIER_PSIKRDYIE) ? 1UL : 0UL);
}

/**
  * @brief  Check if LSI ready interrupt source is enabled or disabled.
  * @rmtoll
  *  CIER         HSERDYIE         LL_RCC_IsEnabledIT_HSERDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsEnabledIT_HSERDY(void)
{
  return ((READ_BIT(RCC->CIER, RCC_CIER_HSERDYIE) == RCC_CIER_HSERDYIE) ? 1UL : 0UL);
}

/**
  * @}
  */ /* End of RCC_LL_EF_IT_Management */

/**
  * @}
  */ /* RCC_LL_Exported_Functions */

/**
  * @}
  */ /* End of RCC_LL */

#endif /* RCC */

/**
  * @}
  */ /* End of STM32C5XX_LL_Driver */

#ifdef __cplusplus
}
#endif

#endif /* STM32C5XX_LL_RCC_H */
