/**
  **********************************************************************************************************************
  * @file    stm32c5xx_ll_pwr.h
  * @author  GPM Application Team
  * @brief   Header file of PWR LL module.
  **********************************************************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file in the root directory of this software
  * component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  **********************************************************************************************************************
  */

/* Define to prevent recursive inclusion -----------------------------------------------------------------------------*/
#ifndef STM32C5xx_LL_PWR_H
#define STM32C5xx_LL_PWR_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ----------------------------------------------------------------------------------------------------------*/
#include "stm32c5xx.h"

/** @addtogroup STM32C5xx_LL_Driver
  * @{
  */

#if defined (PWR)

/** @defgroup PWR_LL PWR
  * @{
  */

/* Private constants -------------------------------------------------------------------------------------------------*/
/** @defgroup PWR_LL_Private_Constants PWR Private Constants
  * @{
  */

/** @defgroup PWR_LL_WAKEUP_PIN_OFFSET Wake-Up Pins register offsets Defines
  * @brief    Flags defines which can be used with LL_PWR_WriteReg function
  * @{
  */
/* Wake-Up Pins PWR register offsets */
#define LL_PWR_WAKEUP_PINS_PULL_SHIFT_OFFSET    2UL
#define LL_PWR_WAKEUP_PINS_MAX_SHIFT_MASK       0x7FU
#define LL_PWR_WAKEUP_PIN_REF                   PWR_WUCR_WUPP1
#define LL_PWR_WAKEUP_PIN_REF_POS               PWR_WUCR_WUPP1_Pos
#define LL_PWR_WAKEUP_PIN_PULL_REF              PWR_WUCR_WUPPUPD1
#define LL_PWR_WAKEUP_PIN_PULL_REF_POS          PWR_WUCR_WUPPUPD1_Pos
/**
  * @}
  */

/** @defgroup PWR_LL_SRAM2_STOP_RETENTION_POSITION SRAM2 stop retention bits position
  * @brief    Position define which can be used in HAL_PWR_LP_EnableMemoryPageRetention /
  *           HAL_PWR_LP_EnableMemoryPageRetention functions.
  * @{
  */
#define LL_PWR_SRAM2_STOP_RETENTION_POS     PWR_PMCR_SRAM2_1_SO_Pos /*!< SRAM2 Page 1 retention in stop mode position */
/**
  * @}
  */

/**
  * @}
  */
/* Exported constants ------------------------------------------------------------------------------------------------*/

/** @defgroup PWR_LL_Exported_Constants PWR Exported Constants
  * @{
  */

/** @defgroup PWR_LL_EC_CLEAR_FLAG Clear Flags Defines
  * @brief    Flags defines which can be used with LL_PWR_WriteReg function
  * @{
  */
#define LL_PWR_PMCR_CSSF       PWR_PMCR_CSSF      /*!< Clear STOP and STANDBY flags */
#define LL_PWR_WUSCR_CWUF1     PWR_WUSCR_CWUF1    /*!< Clear Wakeup flag 1          */
#define LL_PWR_WUSCR_CWUF2     PWR_WUSCR_CWUF2    /*!< Clear Wakeup flag 2          */
#define LL_PWR_WUSCR_CWUF3     PWR_WUSCR_CWUF3    /*!< Clear Wakeup flag 3          */
#define LL_PWR_WUSCR_CWUF4     PWR_WUSCR_CWUF4    /*!< Clear Wakeup flag 4          */
#define LL_PWR_WUSCR_CWUF5     PWR_WUSCR_CWUF5    /*!< Clear Wakeup flag 5          */
#define LL_PWR_WUSCR_CWUF6     PWR_WUSCR_CWUF6    /*!< Clear Wakeup flag 6          */
#define LL_PWR_WUSCR_CWUF7     PWR_WUSCR_CWUF7    /*!< Clear Wakeup flag 7          */
#define LL_PWR_WUSCR_CWUF_ALL  PWR_WUSCR_CWUF     /*!< Clear all Wakeup flags       */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_GET_FLAG Get Flags Defines
  * @brief    Flags defines which can be used with LL_PWR_ReadReg function
  * @{
  */
#define LL_PWR_FLAG_STOPF     PWR_PMSR_STOPF      /*!< STOP flag                               */
#define LL_PWR_FLAG_SBF       PWR_PMSR_SBF        /*!< STANDBY flag                            */
#define LL_PWR_FLAG_PVDO      PWR_VMSR_PVDO       /*!< Programmable voltage detect output flag */
#define LL_PWR_FLAG_USB33RDY  PWR_VMSR_USB33RDY   /*!< VDDUSB ready flag                       */


#define LL_PWR_WAKEUP_FLAG1   PWR_WUSR_WUF1       /*!< Wakeup flag 1 */
#define LL_PWR_WAKEUP_FLAG2   PWR_WUSR_WUF2       /*!< Wakeup flag 2 */
#define LL_PWR_WAKEUP_FLAG3   PWR_WUSR_WUF3       /*!< Wakeup flag 3 */
#define LL_PWR_WAKEUP_FLAG4   PWR_WUSR_WUF4       /*!< Wakeup flag 4 */
#define LL_PWR_WAKEUP_FLAG5   PWR_WUSR_WUF5       /*!< Wakeup flag 5 */
#define LL_PWR_WAKEUP_FLAG6   PWR_WUSR_WUF6       /*!< Wakeup flag 6 */
#define LL_PWR_WAKEUP_FLAG7   PWR_WUSR_WUF7       /*!< Wakeup flag 7 */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_LOW_POWER_MODE_SELECTION  Low Power Mode Selection
  * @{
  */
#define LL_PWR_STOP0_MODE     (0U)                /*!< STOP0 mode    */
#define LL_PWR_STOP1_MODE     PWR_PMCR_LPMS_0     /*!< STOP1 mode    */
#define LL_PWR_STANDBY_MODE   PWR_PMCR_LPMS_1     /*!< STANDBY mode  */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_CORE_SLEEP_MODE  Core sleep mode
  * @{
  */
#define LL_PWR_CORE_SLEEP       0U                    /*!< Core sleep mode      */
#define LL_PWR_CORE_DEEP_SLEEP  SCB_SCR_SLEEPDEEP_Msk /*!< Core deep sleep mode */
/**
  * @}
  */


/** @defgroup PWR_LL_EC_SRAM1_STOP_CONTENTS_RETENTION PWR SRAM1 Content retention in stop mode
  * @{
  */
#define LL_PWR_SRAM1_STOP_RETENTION    PWR_PMCR_SRAM1SO  /*!< SRAM1 retention in stop mode  */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_SRAM2_STOP_CONTENTS_RETENTION PWR SRAM2 Content retention in stop mode
  * @{
  */
#define LL_PWR_SRAM2_PAGE1_STOP_RETENTION   PWR_PMCR_SRAM2_1_SO     /*!< SRAM2 Page 1 retention in stop mode          */
#define LL_PWR_SRAM2_PAGE2_STOP_RETENTION   PWR_PMCR_SRAM2_2_SO     /*!< SRAM2 Page 2 retention in stop mode          */
#define LL_PWR_SRAM2_STOP_RETENTION         (PWR_PMCR_SRAM2_2_SO | PWR_PMCR_SRAM2_1_SO)  /*!< SRAM2 retention
                                                                                              in stop mode            */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_WAKEUP_PIN PWR Wake Up Pin
  * @{
  */
#define LL_PWR_WAKEUP_PIN_1   PWR_WUCR_WUPEN1  /*!< Wakeup pin 1 enable */
#define LL_PWR_WAKEUP_PIN_2   PWR_WUCR_WUPEN2  /*!< Wakeup pin 2 enable */
#define LL_PWR_WAKEUP_PIN_3   PWR_WUCR_WUPEN3  /*!< Wakeup pin 3 enable */
#define LL_PWR_WAKEUP_PIN_4   PWR_WUCR_WUPEN4  /*!< Wakeup pin 4 enable */
#define LL_PWR_WAKEUP_PIN_5   PWR_WUCR_WUPEN5  /*!< Wakeup pin 5 enable */
#define LL_PWR_WAKEUP_PIN_6   PWR_WUCR_WUPEN6  /*!< Wakeup pin 6 enable */
#define LL_PWR_WAKEUP_PIN_7   PWR_WUCR_WUPEN7  /*!< Wakeup pin 7 enable */
#define LL_PWR_WAKEUP_PIN_ALL (0x7FU)          /*!< Wakeup all pin enable */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_WAKEUP_PIN_PULL  Wakeup Pins pull configuration
  * @{
  */
#define LL_PWR_WAKEUP_PIN_PULL_NO     0x00000000UL   /*!< Configure Wake-Up pin in no pull   */
#define LL_PWR_WAKEUP_PIN_PULL_UP     0x00000001UL   /*!< Configure Wake-Up pin in pull Up   */
#define LL_PWR_WAKEUP_PIN_PULL_DOWN   0x00000002UL   /*!< Configure Wake-Up pin in pull Down */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_WAKEUP_PIN_POLARITY  Wakeup Pins polarity
  * @{
 */
#define LL_PWR_WAKEUP_PIN_POLARITY_HIGH     0x00000000UL   /*!< Wakeup pin polarity high  */
#define LL_PWR_WAKEUP_PIN_POLARITY_LOW      0x00000001UL   /*!< Wakeup pin polarity low   */
/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ----------------------------------------------------------------------------------------------------*/

/** @defgroup PWR_LL_Exported_Macros PWR Exported Macros
  * @{
  */

/** @defgroup PWR_LL_EM_WRITE_READ Common Write and Read Registers Macros
  * @{
  */

/**
  * @brief  Write a value in PWR register.
  * @param  reg      Register to be written.
  * @param  value    Value to be written in the register.
  *
  */
#define LL_PWR_WRITE_REG(reg, value) WRITE_REG((PWR)->reg, (value))

/**
  * @brief  Read a value in PWR register.
  * @param  reg      Register to be read.
  * @retval Register value
  */
#define LL_PWR_READ_REG(reg) READ_REG((PWR)->reg)
/**
  * @}
  */

/**
  * @}
  */

/* Exported functions ------------------------------------------------------------------------------------------------*/

/** @defgroup PWR_LL_Exported_Functions PWR Exported Functions
  * @{
  */

/** @defgroup PWR_LL_EF_CONFIGURATION PWR Configuration
  * @{
  */

/**
  * @brief  Set system power mode.
  * @rmtoll
  *  PMCR              LPMS          LL_PWR_SetPowerMode
  * @param  mode : This parameter can be one of the following values:
  *         @arg @ref LL_PWR_STOP0_MODE
  *         @arg @ref LL_PWR_STOP1_MODE
  *         @arg @ref LL_PWR_STANDBY_MODE
  */
__STATIC_INLINE void LL_PWR_SetPowerMode(uint32_t mode)
{
  MODIFY_REG(PWR->PMCR, PWR_PMCR_LPMS, mode);
}

/**
  * @brief  Get system power mode.
  * @rmtoll
  *  PMCR             LPMS          LL_PWR_GetPowerMode
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_PWR_STOP0_MODE
  *         @arg @ref LL_PWR_STOP1_MODE
  *         @arg @ref LL_PWR_STANDBY_MODE
  */
__STATIC_INLINE uint32_t LL_PWR_GetPowerMode(void)
{
  return (READ_BIT(PWR->PMCR, PWR_PMCR_LPMS));
}

/**
  * @brief  Enable the flash power down in stop mode
  * @rmtoll
  *  PMCR    FLPS       LL_PWR_EnableFlashLowPWRMode
  */
__STATIC_INLINE void LL_PWR_EnableFlashLowPWRMode(void)
{
  SET_BIT(PWR->PMCR, PWR_PMCR_FLPS);
}

/**
  * @brief  Disable the flash power down in stop mode
  * @rmtoll
  *  PMCR    FLPS       LL_PWR_DisableFlashLowPWRMode
  */
__STATIC_INLINE void LL_PWR_DisableFlashLowPWRMode(void)
{
  CLEAR_BIT(PWR->PMCR, PWR_PMCR_FLPS);
}

/**
  * @brief  Check if the flash power down in stop mode is enabled
  * @rmtoll
  *  PMCR    FLPS       LL_PWR_IsEnabledFlashLowPWRMode
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledFlashLowPWRMode(void)
{
  return ((READ_BIT(PWR->PMCR, PWR_PMCR_FLPS) == (PWR_PMCR_FLPS)) ? 1UL : 0UL);
}

/**
  * @brief  Enable memory content stop retention.
  * @rmtoll
  *  PMCR              SRAM1SO       LL_PWR_EnableMemoryStopRetention \n
  *  PMCR              SRAM2_48SO    LL_PWR_EnableMemoryStopRetention \n
  *  PMCR              SRAM2_16SO    LL_PWR_EnableMemoryStopRetention
  * @param  memory This parameter can be one of the following values:
  *         @arg @ref LL_PWR_SRAM1_STOP_RETENTION
  *         @arg @ref LL_PWR_SRAM2_STOP_RETENTION
  * @note   (*) value not defined in all devices
  */
__STATIC_INLINE void LL_PWR_EnableMemoryStopRetention(uint32_t memory)
{
  CLEAR_BIT(PWR->PMCR, memory);
}

/**
  * @brief  Disable memory content stop retention.
  * @rmtoll
  *  PMCR              SRAM1SO       LL_PWR_DisableMemoryStopRetention \n
  *  PMCR              SRAM2_48SO    LL_PWR_DisableMemoryStopRetention \n
  *  PMCR              SRAM2_16SO    LL_PWR_DisableMemoryStopRetention
  * @param  memory This parameter can be one of the following values:
  *         @arg @ref LL_PWR_SRAM1_STOP_RETENTION
  *         @arg @ref LL_PWR_SRAM2_STOP_RETENTION
  * @note   (*) value not defined in all devices
  */
__STATIC_INLINE void LL_PWR_DisableMemoryStopRetention(uint32_t memory)
{
  SET_BIT(PWR->PMCR, memory);
}

/**
  * @brief  Get memory content stop retention.
  * @rmtoll
  *  PMCR              SRAM1SO       LL_PWR_IsEnabledMemoryStopRetention \n
  *  PMCR              SRAM2_48SO    LL_PWR_IsEnabledMemoryStopRetention \n
  *  PMCR              SRAM2_16SO    LL_PWR_IsEnabledMemoryStopRetention
  * @param  memory This parameter can be one of the following values:
  *         @arg @ref LL_PWR_SRAM1_STOP_RETENTION
  *         @arg @ref LL_PWR_SRAM2_STOP_RETENTION
  * @note   (*) value not defined in all devices
  * @retval 1 if disabled, 0 if enabled
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledMemoryStopRetention(uint32_t memory)
{
  return ((READ_BIT(PWR->PMCR, memory) == (memory)) ? 0UL : 1UL);
}

/**
  * @brief  Enable SRAM2 page(s) content stop retention.
  * @rmtoll
  *  PMCR              SRAM2_48SO   LL_PWR_EnableSRAM2PagesStopRetention \n
  *  PMCR              SRAM2_16SO   LL_PWR_EnableSRAM2PagesStopRetention
  * @param  pages This parameter is a bitfield representing each page of the SRAM2
  */
__STATIC_INLINE void LL_PWR_EnableSRAM2PagesStopRetention(uint32_t pages)
{
  CLEAR_BIT(PWR->PMCR, (pages & LL_PWR_SRAM2_STOP_RETENTION));
}

/**
  * @brief  Disable SRAM2 page(s) content stop retention.
  * @rmtoll
  *  PMCR              SRAM2_48SO   LL_PWR_DisableSRAM2PagesStopRetention \n
  *  PMCR              SRAM2_16SO   LL_PWR_DisableSRAM2PagesStopRetention
  * @param  pages This parameter is a bitfield representing each page of the SRAM2
  */
__STATIC_INLINE void LL_PWR_DisableSRAM2PagesStopRetention(uint32_t pages)
{
  SET_BIT(PWR->PMCR, (pages & LL_PWR_SRAM2_STOP_RETENTION));
}

/**
  * @brief  Check SRAM2 page content stop retention.
  * @rmtoll
  *  PMCR              SRAM2_48SO   LL_PWR_DisableSRAM2PagesStopRetention \n
  *  PMCR              SRAM2_16SO   LL_PWR_DisableSRAM2PagesStopRetention
  * @param  page This parameter is a bitfield representing each page of the SRAM2
  * @retval 1 if the memory page is retained, 0 otherwise.
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledSRAM2PagesStopRetention(uint32_t page)
{
  return ((READ_BIT(PWR->PMCR, page) == (page)) ? 0UL : 1UL);
}

/**
  * @brief  Enable RTC domain write protection
  * @rmtoll
  *  RTCCR    DRTCP       LL_PWR_EnableRTCDomainWriteProtection
  */
__STATIC_INLINE void LL_PWR_EnableRTCDomainWriteProtection(void)
{
  CLEAR_BIT(PWR->RTCCR, PWR_RTCCR_DRTCP);
}

/**
  * @brief  Disable RTC domain write protection
  * @rmtoll
  *  RTCCR    DRTCP       LL_PWR_DisableRTCDomainWriteProtection
  */
__STATIC_INLINE void LL_PWR_DisableRTCDomainWriteProtection(void)
{
  SET_BIT(PWR->RTCCR, PWR_RTCCR_DRTCP);
}

/**
  * @brief  Check if the RTC domain write protection is enabled
  * @rmtoll
  *  RTCCR    DRTCP       LL_PWR_IsEnabledRTCDomainWriteProtection
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledRTCDomainWriteProtection(void)
{
  return ((READ_BIT(PWR->RTCCR, PWR_RTCCR_DRTCP) == (PWR_RTCCR_DRTCP)) ? 0UL : 1UL);
}

/**
  * @brief  Enable Power Voltage Detector.
  * @rmtoll
  *  VMCR    PVDEN       LL_PWR_EnablePVD
  */
__STATIC_INLINE void LL_PWR_EnablePVD(void)
{
  SET_BIT(PWR->VMCR, PWR_VMCR_PVDE);
}

/**
  * @brief  Disable Power Voltage Detector.
  * @rmtoll
  *  VMCR    PVDEN       LL_PWR_DisablePVD
  */
__STATIC_INLINE void LL_PWR_DisablePVD(void)
{
  CLEAR_BIT(PWR->VMCR, PWR_VMCR_PVDE);
}

/**
  * @brief  Check if Power Voltage Detector is enabled.
  * @rmtoll
  *  VMCR    PVDEN       LL_PWR_IsEnabledPVD
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledPVD(void)
{
  return ((READ_BIT(PWR->VMCR, PWR_VMCR_PVDE) == (PWR_VMCR_PVDE)) ? 1UL : 0UL);
}

/**
  * @brief  Enable the wake up pin_x.
  * @rmtoll
  *  WUCR    WUPENx       LL_PWR_EnableWakeUpPin
  * @param  wakeup_pin This parameter can be a combination of the following values:
  *         @arg @ref LL_PWR_WAKEUP_PIN_1
  *         @arg @ref LL_PWR_WAKEUP_PIN_2
  *         @arg @ref LL_PWR_WAKEUP_PIN_3
  *         @arg @ref LL_PWR_WAKEUP_PIN_4
  *         @arg @ref LL_PWR_WAKEUP_PIN_5
  *         @arg @ref LL_PWR_WAKEUP_PIN_6
  *         @arg @ref LL_PWR_WAKEUP_PIN_7
  *         @arg @ref LL_PWR_WAKEUP_PIN_ALL
  */
__STATIC_INLINE void LL_PWR_EnableWakeUpPin(uint32_t wakeup_pin)
{
  SET_BIT(PWR->WUCR, wakeup_pin);
}

/**
  * @brief  Disable the wake up pin_x.
  * @rmtoll
  *  WUCR    WUPENx       LL_PWR_DisableWakeUpPin
  * @param  wakeup_pin This parameter can be a combination of the following values:
  *         @arg @ref LL_PWR_WAKEUP_PIN_1
  *         @arg @ref LL_PWR_WAKEUP_PIN_2
  *         @arg @ref LL_PWR_WAKEUP_PIN_3
  *         @arg @ref LL_PWR_WAKEUP_PIN_4
  *         @arg @ref LL_PWR_WAKEUP_PIN_5
  *         @arg @ref LL_PWR_WAKEUP_PIN_6
  *         @arg @ref LL_PWR_WAKEUP_PIN_7
  *         @arg @ref LL_PWR_WAKEUP_PIN_ALL
  */
__STATIC_INLINE void LL_PWR_DisableWakeUpPin(uint32_t wakeup_pin)
{
  CLEAR_BIT(PWR->WUCR, wakeup_pin);
}

/**
  * @brief  Check if the wake up pin_x is enabled.
  * @rmtoll
  *  WUCR    WUPPx       LL_PWR_IsEnabledWakeUpPin
  * @param  wakeup_pin This parameter can be one of the following values:
  *         @arg @ref LL_PWR_WAKEUP_PIN_1
  *         @arg @ref LL_PWR_WAKEUP_PIN_2
  *         @arg @ref LL_PWR_WAKEUP_PIN_3
  *         @arg @ref LL_PWR_WAKEUP_PIN_4
  *         @arg @ref LL_PWR_WAKEUP_PIN_5
  *         @arg @ref LL_PWR_WAKEUP_PIN_6
  *         @arg @ref LL_PWR_WAKEUP_PIN_7
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledWakeUpPin(uint32_t wakeup_pin)
{
  return ((READ_BIT(PWR->WUCR, wakeup_pin) == (wakeup_pin)) ? 1UL : 0UL);
}

/**
  * @brief  Set the wake up pin polarity low for the event detection.
  * @rmtoll
  *  WUCR          WUPPx       LL_PWR_SetWakeUpPinPolarityLow
  * @param  wakeup_pin This parameter can be a combination of the following values:
  *         @arg @ref LL_PWR_WAKEUP_PIN_1
  *         @arg @ref LL_PWR_WAKEUP_PIN_2
  *         @arg @ref LL_PWR_WAKEUP_PIN_3
  *         @arg @ref LL_PWR_WAKEUP_PIN_4
  *         @arg @ref LL_PWR_WAKEUP_PIN_5
  *         @arg @ref LL_PWR_WAKEUP_PIN_6
  *         @arg @ref LL_PWR_WAKEUP_PIN_7
  *         @arg @ref LL_PWR_WAKEUP_PIN_ALL
  */
__STATIC_INLINE void LL_PWR_SetWakeUpPinPolarityLow(uint32_t wakeup_pin)
{
  SET_BIT(PWR->WUCR, (uint32_t)(wakeup_pin << PWR_WUCR_WUPP1_Pos));
}

/**
  * @brief  Set the wake up pin polarity high for the event detection.
  * @rmtoll
  *  WUCR          WUPPx       LL_PWR_SetWakeUpPinPolarityHigh
  * @param  wakeup_pin This parameter can be a combination of the following values:
  *         @arg @ref LL_PWR_WAKEUP_PIN_1
  *         @arg @ref LL_PWR_WAKEUP_PIN_2
  *         @arg @ref LL_PWR_WAKEUP_PIN_3
  *         @arg @ref LL_PWR_WAKEUP_PIN_4
  *         @arg @ref LL_PWR_WAKEUP_PIN_5
  *         @arg @ref LL_PWR_WAKEUP_PIN_6
  *         @arg @ref LL_PWR_WAKEUP_PIN_7
  *         @arg @ref LL_PWR_WAKEUP_PIN_ALL
  */
__STATIC_INLINE void LL_PWR_SetWakeUpPinPolarityHigh(uint32_t wakeup_pin)
{
  CLEAR_BIT(PWR->WUCR, (uint32_t)(wakeup_pin << PWR_WUCR_WUPP1_Pos));
}

/**
  * @brief  Set the wake up pin polarity low for the event detection.
  * @rmtoll
  *  WUCR          WUPPx       LL_PWR_SetWakeupPinPolarity
  * @param  wakeup_pin This parameter can be one of the following values:
  *         @arg @ref LL_PWR_WAKEUP_PIN_1
  *         @arg @ref LL_PWR_WAKEUP_PIN_2
  *         @arg @ref LL_PWR_WAKEUP_PIN_3
  *         @arg @ref LL_PWR_WAKEUP_PIN_4
  *         @arg @ref LL_PWR_WAKEUP_PIN_5
  *         @arg @ref LL_PWR_WAKEUP_PIN_6
  *         @arg @ref LL_PWR_WAKEUP_PIN_7
  * @param  polarity This parameter can be one of the following values:
  *         @arg @ref LL_PWR_WAKEUP_PIN_POLARITY_HIGH
  *         @arg @ref LL_PWR_WAKEUP_PIN_POLARITY_LOW
  */
__STATIC_INLINE void LL_PWR_SetWakeUpPinPolarity(uint32_t wakeup_pin, uint32_t polarity)
{
  MODIFY_REG(PWR->WUCR, (uint32_t)(PWR_WUCR_WUPP1 << POSITION_VAL(wakeup_pin)), \
             (uint32_t)(polarity << (PWR_WUCR_WUPP1_Pos + POSITION_VAL(wakeup_pin))));
}

/**
  * @brief  Get the wake up pin polarity for the event detection.
  * @rmtoll
  *  WUCR          WUPPx       LL_PWR_GetWakeUpPinPolarity
  * @param  wakeup_pin This parameter can be one of the following values:
  *         @arg @ref LL_PWR_WAKEUP_PIN_1
  *         @arg @ref LL_PWR_WAKEUP_PIN_2
  *         @arg @ref LL_PWR_WAKEUP_PIN_3
  *         @arg @ref LL_PWR_WAKEUP_PIN_4
  *         @arg @ref LL_PWR_WAKEUP_PIN_5
  *         @arg @ref LL_PWR_WAKEUP_PIN_6
  *         @arg @ref LL_PWR_WAKEUP_PIN_7
  * @retval State of bit (1 : polarity low or 0 : polarity high).
  */
__STATIC_INLINE uint32_t LL_PWR_GetWakeUpPinPolarity(uint32_t wakeup_pin)
{
  return (((READ_BIT(PWR->WUCR, (uint32_t)(PWR_WUCR_WUPP1 << POSITION_VAL(wakeup_pin)))) != 0U) ? 1UL : 0UL);
}

/**
  * @brief  Set the Wake-Up pin Pull None.
  * @rmtoll
  *  WUCR   WUPPUPDx       LL_PWR_SetWakeUpPinPullNone
  * @param  wakeup_pin This parameter can be one of the following values:
  *         @arg @ref LL_PWR_WAKEUP_PIN_1
  *         @arg @ref LL_PWR_WAKEUP_PIN_2
  *         @arg @ref LL_PWR_WAKEUP_PIN_3
  *         @arg @ref LL_PWR_WAKEUP_PIN_4
  *         @arg @ref LL_PWR_WAKEUP_PIN_5
  *         @arg @ref LL_PWR_WAKEUP_PIN_6
  *         @arg @ref LL_PWR_WAKEUP_PIN_7
  */
__STATIC_INLINE void LL_PWR_SetWakeUpPinPullNone(uint32_t wakeup_pin)
{
  MODIFY_REG(PWR->WUCR,
             (PWR_WUCR_WUPPUPD1 << ((LL_PWR_WAKEUP_PINS_PULL_SHIFT_OFFSET * (POSITION_VAL(wakeup_pin) & 0xFU)) & \
                                    LL_PWR_WAKEUP_PINS_MAX_SHIFT_MASK)),
             (LL_PWR_WAKEUP_PIN_PULL_NO << ((PWR_WUCR_WUPPUPD1_Pos + ((LL_PWR_WAKEUP_PINS_PULL_SHIFT_OFFSET * \
                                                                       POSITION_VAL(wakeup_pin)) & 0xFU)) & \
                                            LL_PWR_WAKEUP_PINS_MAX_SHIFT_MASK)));
}

/**
  * @brief  Set the Wake-Up pin Pull Up.
  * @rmtoll
  *  WUCR   WUPPUPDx       LL_PWR_SetWakeUpPinPullUp
  * @param  wakeup_pin This parameter can be one of the following values:
  *         @arg @ref LL_PWR_WAKEUP_PIN_1
  *         @arg @ref LL_PWR_WAKEUP_PIN_2
  *         @arg @ref LL_PWR_WAKEUP_PIN_3
  *         @arg @ref LL_PWR_WAKEUP_PIN_4
  *         @arg @ref LL_PWR_WAKEUP_PIN_5
  *         @arg @ref LL_PWR_WAKEUP_PIN_6
  *         @arg @ref LL_PWR_WAKEUP_PIN_7
  */
__STATIC_INLINE void LL_PWR_SetWakeUpPinPullUp(uint32_t wakeup_pin)
{
  MODIFY_REG(PWR->WUCR,
             (PWR_WUCR_WUPPUPD1 << ((LL_PWR_WAKEUP_PINS_PULL_SHIFT_OFFSET * (POSITION_VAL(wakeup_pin) & 0xFU)) & \
                                    LL_PWR_WAKEUP_PINS_MAX_SHIFT_MASK)),
             (LL_PWR_WAKEUP_PIN_PULL_UP << ((PWR_WUCR_WUPPUPD1_Pos + ((LL_PWR_WAKEUP_PINS_PULL_SHIFT_OFFSET * \
                                                                       POSITION_VAL(wakeup_pin)) & 0xFU)) & \
                                            LL_PWR_WAKEUP_PINS_MAX_SHIFT_MASK)));
}

/**
  * @brief  Set the Wake-Up pin Pull Down.
  * @rmtoll
  *  WUCR   WUPPUPDx       LL_PWR_SetWakeUpPinPullDown
  * @param  wakeup_pin This parameter can be one of the following values:
  *         @arg @ref LL_PWR_WAKEUP_PIN_1
  *         @arg @ref LL_PWR_WAKEUP_PIN_2
  *         @arg @ref LL_PWR_WAKEUP_PIN_3
  *         @arg @ref LL_PWR_WAKEUP_PIN_4
  *         @arg @ref LL_PWR_WAKEUP_PIN_5
  *         @arg @ref LL_PWR_WAKEUP_PIN_6
  *         @arg @ref LL_PWR_WAKEUP_PIN_7
  */
__STATIC_INLINE void LL_PWR_SetWakeUpPinPullDown(uint32_t wakeup_pin)
{
  MODIFY_REG(PWR->WUCR,
             (PWR_WUCR_WUPPUPD1 << ((LL_PWR_WAKEUP_PINS_PULL_SHIFT_OFFSET * (POSITION_VAL(wakeup_pin) & 0xFU)) & \
                                    LL_PWR_WAKEUP_PINS_MAX_SHIFT_MASK)),
             (LL_PWR_WAKEUP_PIN_PULL_DOWN << ((PWR_WUCR_WUPPUPD1_Pos + ((LL_PWR_WAKEUP_PINS_PULL_SHIFT_OFFSET * \
                                                                         POSITION_VAL(wakeup_pin)) & 0xFU)) & \
                                              LL_PWR_WAKEUP_PINS_MAX_SHIFT_MASK)));
}

/**
  * @brief  Set the Wake-Up pin pull.
  * @rmtoll
  *  WUCR   WUPPUPDx       LL_PWR_GetWakeUpPinPull
  * @param  wakeup_pin This parameter can be one of the following values:
  *         @arg @ref LL_PWR_WAKEUP_PIN_1
  *         @arg @ref LL_PWR_WAKEUP_PIN_2
  *         @arg @ref LL_PWR_WAKEUP_PIN_3
  *         @arg @ref LL_PWR_WAKEUP_PIN_4
  *         @arg @ref LL_PWR_WAKEUP_PIN_5
  *         @arg @ref LL_PWR_WAKEUP_PIN_6
  *         @arg @ref LL_PWR_WAKEUP_PIN_7
  * @param  pull This parameter can be one of the following values:
  *         @arg @ref LL_PWR_WAKEUP_PIN_PULL_NO
  *         @arg @ref LL_PWR_WAKEUP_PIN_PULL_UP
  *         @arg @ref LL_PWR_WAKEUP_PIN_PULL_DOWN
  */
__STATIC_INLINE void LL_PWR_SetWakeUpPinPull(uint32_t wakeup_pin, uint32_t pull)
{
  MODIFY_REG(PWR->WUCR, (PWR_WUCR_WUPPUPD1 << (LL_PWR_WAKEUP_PINS_PULL_SHIFT_OFFSET * (POSITION_VAL(wakeup_pin)))), \
             pull << (PWR_WUCR_WUPPUPD1_Pos + \
                      (LL_PWR_WAKEUP_PINS_PULL_SHIFT_OFFSET * (POSITION_VAL(wakeup_pin)))));
}

/**
  * @brief  Get the Wake-Up pin pull.
  * @rmtoll
  *  WUCR   WUPPUPDx       LL_PWR_GetWakeUpPinPull
  * @param  wakeup_pin This parameter can be one of the following values:
  *         @arg @ref LL_PWR_WAKEUP_PIN_1
  *         @arg @ref LL_PWR_WAKEUP_PIN_2
  *         @arg @ref LL_PWR_WAKEUP_PIN_3
  *         @arg @ref LL_PWR_WAKEUP_PIN_4
  *         @arg @ref LL_PWR_WAKEUP_PIN_5
  *         @arg @ref LL_PWR_WAKEUP_PIN_6
  *         @arg @ref LL_PWR_WAKEUP_PIN_7
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_PWR_WAKEUP_PIN_PULL_NO
  *         @arg @ref LL_PWR_WAKEUP_PIN_PULL_UP
  *         @arg @ref LL_PWR_WAKEUP_PIN_PULL_DOWN
  */
__STATIC_INLINE uint32_t LL_PWR_GetWakeUpPinPull(uint32_t wakeup_pin)
{
  uint32_t regValue = READ_BIT(PWR->WUCR, (PWR_WUCR_WUPPUPD1 << ((LL_PWR_WAKEUP_PINS_PULL_SHIFT_OFFSET * \
                                                                  (POSITION_VAL(wakeup_pin) & 0xFU)) & \
                                                                 LL_PWR_WAKEUP_PINS_MAX_SHIFT_MASK)));

  return (uint32_t)(regValue >> ((PWR_WUCR_WUPPUPD1_Pos + ((LL_PWR_WAKEUP_PINS_PULL_SHIFT_OFFSET * \
                                                            POSITION_VAL(wakeup_pin)) & 0xFU)) & \
                                 LL_PWR_WAKEUP_PINS_MAX_SHIFT_MASK));
}

/**
  * @brief  Enable IO retention.
  * @rmtoll
  *  IORETR        IORETEN           LL_PWR_EnableIORetention
  */
__STATIC_INLINE void LL_PWR_EnableIORetentionStandbyMode(void)
{
  SET_BIT(PWR->IORETR, PWR_IORETR_IORETEN);
}

/**
  * @brief  Disable IO retention.
  * @rmtoll
  *  IORETR        IORETEN           LL_PWR_DisableIORetention
  */
__STATIC_INLINE void LL_PWR_DisableIORetentionStandbyMode(void)
{
  CLEAR_BIT(PWR->IORETR, PWR_IORETR_IORETEN);
}

/**
  * @brief  Check if IO retention is enabled.
  * @rmtoll
  *  IORETR        IORETEN           LL_PWR_IsEnabledIORetention
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledIORetentionStandbyMode(void)
{
  return ((READ_BIT(PWR->IORETR, PWR_IORETR_IORETEN) == (PWR_IORETR_IORETEN)) ? 1UL : 0UL);
}

/**
  * @brief  Enable JTAGIO retention.
  * @rmtoll
  *  JTAGIORETR    JTAGIORETEN       LL_PWR_EnableJTAGIORetention
  */
__STATIC_INLINE void LL_PWR_EnableJTAGIORetentionStandbyMode(void)
{
  SET_BIT(PWR->IORETR, PWR_IORETR_JTAGIORETEN);
}

/**
  * @brief  Disable JTAGIO retention.
  * @rmtoll
  *  JTAGIORETR     JTAGIORETEN      LL_PWR_DisableJTAGIORetention
  */
__STATIC_INLINE void LL_PWR_DisableJTAGIORetentionStandbyMode(void)
{
  CLEAR_BIT(PWR->IORETR, PWR_IORETR_JTAGIORETEN);
}

/**
  * @brief  Check if JTAGIO retention is enabled.
  * @rmtoll
  *  IORETR     JTAGIORETEN          LL_PWR_IsEnabledJTAGIORetention
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledJTAGIORetentionStandbyMode(void)
{
  return ((READ_BIT(PWR->IORETR, PWR_IORETR_JTAGIORETEN) == (PWR_IORETR_JTAGIORETEN)) ? 1UL : 0UL);
}
/**
  * @}
  */

/** @defgroup PWR_LL_EF_FLAG_MANAGEMENT PWR FLAG Management
  * @{
  */

/**
  * @brief  Indicate whether the system was in standby mode or not.
  * @rmtoll
  *  PMSR          SBF          LL_PWR_IsActiveFlag_SB
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_SB(void)
{
  return ((READ_BIT(PWR->PMSR, PWR_PMSR_SBF) == (PWR_PMSR_SBF)) ? 1UL : 0UL);
}

/**
  * @brief  Indicate whether the system was in stop mode or not.
  * @rmtoll
  *  PMSR          STOPF          LL_PWR_IsActiveFlag_STOP
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_STOP(void)
{
  return ((READ_BIT(PWR->PMSR, PWR_PMSR_STOPF) == (PWR_PMSR_STOPF)) ? 1UL : 0UL);
}

/**
  * @brief  Indicate whether the VDD voltage is below the threshold or not.
  * @rmtoll
  *  VMSR          PVDO          LL_PWR_IsActiveFlag_PVDO
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_PVDO(void)
{
  return ((READ_BIT(PWR->VMSR, PWR_VMSR_PVDO) == (PWR_VMSR_PVDO)) ? 1UL : 0UL);
}

/**
  * @brief  Indicate whether a wakeup event is detected on wake up pin 1.
  * @rmtoll
  *  WUSR          WUF1          LL_PWR_IsActiveFlag_WU1
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_WU1(void)
{
  return ((READ_BIT(PWR->WUSR, PWR_WUSR_WUF1) == (PWR_WUSR_WUF1)) ? 1UL : 0UL);
}

/**
  * @brief  Indicate whether a wakeup event is detected on wake up pin 2.
  * @rmtoll
  *  WUSR          WUF2          LL_PWR_IsActiveFlag_WU2
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_WU2(void)
{
  return ((READ_BIT(PWR->WUSR, PWR_WUSR_WUF2) == (PWR_WUSR_WUF2)) ? 1UL : 0UL);
}

/**
  * @brief  Indicate whether a wakeup event is detected on wake up pin 3.
  * @rmtoll
  *  WUSR          WUF3          LL_PWR_IsActiveFlag_WU3
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_WU3(void)
{
  return ((READ_BIT(PWR->WUSR, PWR_WUSR_WUF3) == (PWR_WUSR_WUF3)) ? 1UL : 0UL);
}

/**
  * @brief  Indicate whether a wakeup event is detected on wake up pin 4.
  * @rmtoll
  *  WUSR          WUF4          LL_PWR_IsActiveFlag_WU4
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_WU4(void)
{
  return ((READ_BIT(PWR->WUSR, PWR_WUSR_WUF4) == (PWR_WUSR_WUF4)) ? 1UL : 0UL);
}

/**
  * @brief  Indicate whether a wakeup event is detected on wake up pin 5.
  * @rmtoll
  *  WUSR          WUF5          LL_PWR_IsActiveFlag_WU5
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_WU5(void)
{
  return ((READ_BIT(PWR->WUSR, PWR_WUSR_WUF5) == (PWR_WUSR_WUF5)) ? 1UL : 0UL);
}

#if defined (PWR_WUSR_WUF6)
/**
  * @brief  Indicate whether a wakeup event is detected on wake up pin 6.
  * @rmtoll
  *  WUSR          WUF6          LL_PWR_IsActiveFlag_WU6
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_WU6(void)
{
  return ((READ_BIT(PWR->WUSR, PWR_WUSR_WUF6) == (PWR_WUSR_WUF6)) ? 1UL : 0UL);
}
#endif /* PWR_WUSR_WUF6 */

#if defined (PWR_WUSR_WUF7)
/**
  * @brief  Indicate whether a wakeup event is detected on wake up pin 7.
  * @rmtoll
  *  WUSR          WUF7          LL_PWR_IsActiveFlag_WU7
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_WU7(void)
{
  return ((READ_BIT(PWR->WUSR, PWR_WUSR_WUF7) == (PWR_WUSR_WUF7)) ? 1UL : 0UL);
}
#endif /* PWR_WUSR_WUF7 */

/**
  * @brief  Clear stop flag.
  * @rmtoll
  *  PMCR          CSSF          LL_PWR_ClearFlag_STOP
  */
__STATIC_INLINE void LL_PWR_ClearFlag_STOP(void)
{
  WRITE_REG(PWR->PMCR, PWR_PMCR_CSSF);
}

/**
  * @brief  Clear standby flag.
  * @rmtoll
  *  PMCR          CSSF          LL_PWR_ClearFlag_SB
  */
__STATIC_INLINE void LL_PWR_ClearFlag_SB(void)
{
  WRITE_REG(PWR->PMCR, PWR_PMCR_CSSF);
}

/**
  * @brief  Clear wake up flag 1.
  * @rmtoll
  *  WUSCR          CWUF1         LL_PWR_ClearFlag_WU1
  */
__STATIC_INLINE void LL_PWR_ClearFlag_WU1(void)
{
  WRITE_REG(PWR->WUSCR, PWR_WUSCR_CWUF1);
}

/**
  * @brief  Clear wake up flag 2.
  * @rmtoll
  *  WUSCR          CWUF2         LL_PWR_ClearFlag_WU2
  */
__STATIC_INLINE void LL_PWR_ClearFlag_WU2(void)
{
  WRITE_REG(PWR->WUSCR, PWR_WUSCR_CWUF2);
}

/**
  * @brief  Clear wake up flag 3.
  * @rmtoll
  *  WUSCR          CWUF3         LL_PWR_ClearFlag_WU3
  */
__STATIC_INLINE void LL_PWR_ClearFlag_WU3(void)
{
  WRITE_REG(PWR->WUSCR, PWR_WUSCR_CWUF3);
}

/**
  * @brief  Clear wake up flag 4.
  * @rmtoll
  *  WUSCR          CWUF4         LL_PWR_ClearFlag_WU4
  */
__STATIC_INLINE void LL_PWR_ClearFlag_WU4(void)
{
  WRITE_REG(PWR->WUSCR, PWR_WUSCR_CWUF4);
}

/**
  * @brief  Clear wake up flag 5.
  * @rmtoll
  *  WUSCR          CWUF5         LL_PWR_ClearFlag_WU5
  */
__STATIC_INLINE void LL_PWR_ClearFlag_WU5(void)
{
  WRITE_REG(PWR->WUSCR, PWR_WUSCR_CWUF5);
}

#if defined (PWR_WUSCR_CWUF6)
/**
  * @brief  Clear wake up flag 6.
  * @rmtoll
  *  WUSCR          CWUF6         LL_PWR_ClearFlag_WU6
  */
__STATIC_INLINE void LL_PWR_ClearFlag_WU6(void)
{
  WRITE_REG(PWR->WUSCR, PWR_WUSCR_CWUF6);
}
#endif /* PWR_WUSCR_CWUF6 */

#if defined (PWR_WUSCR_CWUF7)
/**
  * @brief  Clear wake up flag 7.
  * @rmtoll
  *  WUSCR          CWUF7         LL_PWR_ClearFlag_WU7
  */
__STATIC_INLINE void LL_PWR_ClearFlag_WU7(void)
{
  WRITE_REG(PWR->WUSCR, PWR_WUSCR_CWUF7);
}
#endif /* PWR_WUSCR_CWUF7 */

/**
  * @brief  Clear wakeup pin flags.
  * @rmtoll
  *  WKUPSCR           WKUPCx           LL_PWR_ClearFlag_WU
  * @param  wakeup_pin
  *         This parameter can be one or a combination of the following values:
  *         @arg @ref LL_PWR_WAKEUP_PIN_1
  *         @arg @ref LL_PWR_WAKEUP_PIN_2
  *         @arg @ref LL_PWR_WAKEUP_PIN_3
  *         @arg @ref LL_PWR_WAKEUP_PIN_4
  *         @arg @ref LL_PWR_WAKEUP_PIN_5
  *         @arg @ref LL_PWR_WAKEUP_PIN_6
  *         @arg @ref LL_PWR_WAKEUP_PIN_7
  *         @arg @ref LL_PWR_WAKEUP_PIN_ALL
  */
__STATIC_INLINE void LL_PWR_ClearFlag_WU(uint32_t wakeup_pin)
{
  WRITE_REG(PWR->WUSCR, wakeup_pin);
}
/**
  * @}
  */

/** @defgroup PWR_LL_EF_ATTRIBUTE_MANAGEMENT PWR Attribute Management
  * @{
  */
#if defined(PWR_PRIVCFGR_PRIV)
/**
  * @brief  Enable privileged mode.
  * @rmtoll
  *  PRIVCFGR     PRIV        LL_PWR_EnablePrivilege
  */
__STATIC_INLINE void LL_PWR_EnablePrivilege(void)
{
  SET_BIT(PWR->PRIVCFGR, PWR_PRIVCFGR_PRIV);
}

/**
  * @brief  Disable privileged mode.
  * @rmtoll
  *  PRIVCFGR     PRIV          LL_PWR_DisablePrivilege
  */
__STATIC_INLINE void LL_PWR_DisablePrivilege(void)
{
  CLEAR_BIT(PWR->PRIVCFGR, PWR_PRIVCFGR_PRIV);
}

/**
  * @brief  Check if privileged mode is enabled.
  * @rmtoll
  *  PRIVCFGR     PRIV          LL_PWR_IsEnabledPrivilege
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledPrivilege(void)
{
  return ((READ_BIT(PWR->PRIVCFGR, PWR_PRIVCFGR_PRIV) == PWR_PRIVCFGR_PRIV) ? 1UL : 0UL);
}
#endif /* PWR_PRIVCFGR_PRIV */
/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#endif /* defined (PWR) */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* STM32C5xx_LL_PWR_H */
