/**
  **********************************************************************************************************************
  * @file    stm32c5xx_hal_pwr.c
  * @author  GPM Application Team
  * @brief   PWR HAL module driver.
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

/* Includes ----------------------------------------------------------------------------------------------------------*/
#include "stm32_hal.h"

/** @addtogroup STM32C5xx_HAL_Driver
  * @{
  */

/** @addtogroup PWR
  * @{

# PWR peripheral overview

The power control peripheral (PWR) provides an overview of the supply architecture for the different power domains
and of the supply configuration controller.

This file provides firmware functions to manage the following functionalities :
   - Wakeup pins management functions.
   - RTC domain write protection management functions.
   - Low power mode management functions.
   - Voltage monitoring management functions.
   - Items retention management functions.
   - I/O pull management functions.

# How to use the PWR HAL module driver

This module provides 7 different sets of APIs that allows to :

1. Manage the wakeup pin :
   A wakeup pin is used to wakeup the system from low power modes.
   - Configure the wakeup pin polarity and pull, without enabling it :
     - This functionality is ensured by HAL_PWR_LP_SetConfigWakeupPin() function. The p_config pointer allows to
       configure wakeup polarity and pull.
       - When p_config is null, this function returns an HAL_INVALID_PARAM.
   - Get the wakeup pin polarity and pull configuration:
     - This functionality is ensured by HAL_PWR_LP_GetConfigWakeupPin() function.
   - Enable, disable and check the wakeup pin :
     - These functionalities are ensured respectively by HAL_PWR_LP_EnableWakeupPin(), HAL_PWR_LP_DisableWakeupPin() and
       HAL_PWR_LP_IsEnabledWakeupPin().

2. Manage RTC domain write protection :
   After a system reset, the RTC domain is protected against possible unwanted write accesses.
   - Enable, disable and check the write protection to RTC domain :
     - These functionalities are ensured respectively by HAL_PWR_EnableRTCDomainWriteProtection(),
       HAL_PWR_DisableRTCDomainWriteProtection() and HAL_PWR_IsEnabledRTCDomainWriteProtection().

3. Manage low power mode:
   Several power modes are available and can be used to reduce power consumption.
   - Clear Core pending event to clear internal cortex event before entering sleep or stop x mode:
     - This functionality is ensured by HAL_PWR_ClearCorePendingEvent() function.
   - Enter the MCU to low power modes:
     - Enter the MCU to sleep mode through WFE or WFI request:
       - This functionality is ensured by HAL_PWR_EnterSleepMode() function.
     - Enter the MCU to stop x mode through WFE or WFI request:
       - This functionality is ensured by HAL_PWR_EnterStopMode() function.
     - Enter the MCU to standby mode:
       - This functionality is ensured by HAL_PWR_EnterStandbyMode() function.
   - Configure the core deep sleep mode:
     - This functionality is ensured by HAL_PWR_SetCoreSleepMode() function.
   - Get the core deep sleep mode configuration:
     - This functionality is ensured by HAL_PWR_GetCoreSleepMode() function.
   - Enable, disable and check the core sleep on exit. This feature allows the core to enter sleep mode immediately
      after interrupt handling complete without returning to the main program.
     - These functionalities are ensured respectively by HAL_PWR_EnableCoreSleepOnExit(),
        HAL_PWR_DisableCoreSleepOnExit() and HAL_PWR_IsEnabledCoreSleepOnExit().
   - Enable, disable and check the core send event on pending. This feature allows the cortex to generate an event
      signal whenever there is a pending interrupt or exception. This event signal can be used to wake up the processor
      from a low-power state, ensuring that the system responds promptly to interrupts.
     - these functionalities are ensured respectively by HAL_PWR_EnableCoreSendEventOnPending(),
         HAL_PWR_DisableCoreSendEventOnPending() and HAL_PWR_IsEnabledCoreSendEventOnPending() functions.

4. Manage monitoring:
   The monitor can be used to manage the power supplies and supply domains.
   - Enable, disable and check the the programmable voltage detector:
     - These functionalities are ensured respectively by HAL_PWR_EnableProgrammableVoltageDetector(),
       HAL_PWR_DisableProgrammableVoltageDetector() and HAL_PWR_IsEnabledProgrammableVoltageDetector() functions.

5. Manage memory retention:
   After entering low power mode, the volatile memories (SRAM) content can be retained or not according application
    needs.
   - Enable, disable and check the memory retention:
     - These functionalities are ensured by HAL_PWR_LP_EnableMemoryRetention(), HAL_PWR_LP_DisableMemoryRetention() and
       HAL_PWR_LP_IsEnabledMemoryRetention() functions.
   - Enable, disable and check the memory retention per pages:
     - These functionalities are ensured by HAL_PWR_LP_EnableMemoryPageRetention(),
       HAL_PWR_LP_DisableMemoryPageRetention() and HAL_PWR_LP_IsEnabledMemoryPageRetention() functions.

6. Manage memory power modes:
   The flash memory can be configured to enter low power mode when the MCU enter low power mode.
   - Enable, disable and check the flash low power mode in stop modes:
     - These functionalities are ensured by HAL_PWR_LP_EnableFlashLowPWRMode(), HAL_PWR_LP_DisableFlashLowPWRMode() and
       HAL_PWR_LP_IsEnabledFlashLowPWRMode() functions.

7. Manage the I/O retention :
   The I/O retention feature allows to maintain the state I/Os during low-power modes. Several API are available to
    retain or release the output of IOs.
   - Enable, disable and check IOs retention:
     - These functionalities are ensured by HAL_PWR_LP_EnableIORetention(), HAL_PWR_LP_DisableIORetention() and
       HAL_PWR_LP_IsEnabledIORetention() functions.

## Configuration inside the HAL PWR driver

Config defines       | Description        | Default value | Note
---------------------| ---------------    | ------------- | ------------------------------------------------------------
PRODUCT              | from IDE           | NA            | The selected device
USE_HAL_PWR_MODULE   | from hal_conf.h    | 1U            | When set, HAL PWR module is enabled.
USE_ASSERT_DBG_PARAM | from IDE           | None          | When defined, enable the params assert.
USE_HAL_CHECK_PARAM  | from hal_conf.h    | 0U            | When set, parameters are checked in runtime.
  */

#if defined(USE_HAL_PWR_MODULE) && (USE_HAL_PWR_MODULE == 1)

/* Private typedef ---------------------------------------------------------------------------------------------------*/
/* Private defines ---------------------------------------------------------------------------------------------------*/
/** @defgroup PWR_Private_Constants PWR Private Constants
  * @{
  */
/* Memory retention pages number */
#define PWR_SRAM1_RETENTION_PAGES_MAX 0x01UL /*!< SRAM1 max pages number       */
#define PWR_SRAM2_RETENTION_PAGES_MAX 0x02UL /*!< SRAM2 max pages number       */
/**
  * @}
  */

/* Private variables -------------------------------------------------------------------------------------------------*/
/** @defgroup PWR_Private_Variables PWR Private Variables
  * @{
  */
/*! Memory retention mapping table */
static const uint32_t PWR_MemoryFullRetentionMap[] =
{
  LL_PWR_SRAM1_STOP_RETENTION,
  LL_PWR_SRAM2_STOP_RETENTION
};

#if defined(USE_ASSERT_DBG_PARAM)
/*! Memory max pages retention mapping table */
static const uint32_t PWR_MemoryMaxPagesRetentionMap[] =
{
  PWR_SRAM1_RETENTION_PAGES_MAX,
  PWR_SRAM2_RETENTION_PAGES_MAX
};

/*! Number of SRAM banks */
static const uint32_t PWR_SRAM_BANKS = (uint32_t)(sizeof(PWR_MemoryMaxPagesRetentionMap) / sizeof(uint32_t));
#endif /* USE_ASSERT_DBG_PARAM */
/**
  * @}
  */

/* Private macros ----------------------------------------------------------------------------------------------------*/
/** @defgroup PWR_Private_Macros PWR Private Macros
  * @{
  */

/*! Set wakeup pins check macro */
#define IS_PWR_SET_WAKEUP_PIN(pin) \
  ((((pin) & (HAL_PWR_WAKEUP_PIN_ALL)) != 0U) && (((pin) & (~HAL_PWR_WAKEUP_PIN_ALL)) == 0U))

/*! Wakeup pin polarity check macro */
#define IS_PWR_WAKEUP_PIN_POLARITY(polarity) \
  (((polarity) == HAL_PWR_WAKEUP_PIN_POLARITY_HIGH) || ((polarity) == HAL_PWR_WAKEUP_PIN_POLARITY_LOW))

/*! Wakeup pin pull check macro */
#define IS_PWR_WAKEUP_PIN_PULL(pull)                                                \
  (((pull) == HAL_PWR_WAKEUP_PIN_PULL_NO) || ((pull) == HAL_PWR_WAKEUP_PIN_PULL_UP) \
   || ((pull) == HAL_PWR_WAKEUP_PIN_PULL_DOWN))

/*! Get wakeup pins check macro */
#define IS_PWR_GET_WAKEUP_PIN(pin)    \
  (((pin) == HAL_PWR_WAKEUP_PIN_1)    \
   || ((pin) == HAL_PWR_WAKEUP_PIN_2) \
   || ((pin) == HAL_PWR_WAKEUP_PIN_3) \
   || ((pin) == HAL_PWR_WAKEUP_PIN_4) \
   || ((pin) == HAL_PWR_WAKEUP_PIN_5) \
   || ((pin) == HAL_PWR_WAKEUP_PIN_6) \
   || ((pin) == HAL_PWR_WAKEUP_PIN_7))

/*! Low power mode entry check macro */
#define IS_PWR_LP_MODE_ENTRY(entry) \
  (((entry) == (uint32_t)HAL_PWR_LOW_PWR_MODE_WFE) || ((entry) == (uint32_t)HAL_PWR_LOW_PWR_MODE_WFI))

/*! Stop mode check macro */
#define IS_PWR_STOP_MODE(mode)       \
  (((mode) == (uint32_t)HAL_PWR_STOP0_MODE)    \
   || (((mode) == (uint32_t)HAL_PWR_STOP1_MODE)))

/*! Core sleep mode check macro */
#define IS_PWR_CORE_SLEEP_MODE(mode) \
  (((mode) == ((uint32_t)HAL_PWR_CORE_SLEEP)) || ((mode) == ((uint32_t)HAL_PWR_CORE_DEEP_SLEEP)))

/*! Memory retention check macro */
#define IS_PWR_MEMORY_RETENTION(memory)                 \
  (((memory) == ((uint32_t)HAL_PWR_MEMORY_RETENTION_SRAM1_STOP))    \
   || ((memory) == ((uint32_t)HAL_PWR_MEMORY_RETENTION_SRAM2_STOP)))


/*! Memory page retention check macro */
#define IS_PWR_MEMORY_PAGES_RETENTION(memory, page_idx, page_nbr)                   \
  (((memory) < PWR_SRAM_BANKS)                                                        \
   && ((((page_idx) - 1U) + (page_nbr)) <= (PWR_MemoryMaxPagesRetentionMap[memory]))  \
   && ((((PWR_MemoryMaxPagesRetentionMap[memory]) > 1U)))                              \
   && ((((page_idx) - 1U) + (page_nbr)) > 0U))

/*! I/O selection retention check macro */
#define IS_PWR_SET_IO_RETENTION(io)                                     \
  (((((io) & (uint32_t)HAL_PWR_IO_RETENTION_JTAGIO) == (uint32_t)HAL_PWR_IO_RETENTION_JTAGIO) \
    || (((io) & (uint32_t)HAL_PWR_IO_RETENTION_GPIO) == (uint32_t)HAL_PWR_IO_RETENTION_GPIO)) \
   && ((io) <= (uint32_t)HAL_PWR_IO_RETENTION_ALL))

/*! I/O selection retention enabled check macro */
#define IS_PWR_GET_IO_RETENTION(io)         \
  (((io) == (uint32_t)HAL_PWR_IO_RETENTION_JTAGIO)    \
   || ((io) == (uint32_t)HAL_PWR_IO_RETENTION_GPIO))
/**
  * @}
  */

/* Exported functions ------------------------------------------------------------------------------------------------*/
/** @addtogroup PWR_Exported_Functions PWR Exported Functions
  * @{
  */

/** @addtogroup PWR_Exported_Functions_Group1 Wakeup pins management functions
  * @{
  This section provides functions allowing to manage the wakeup pins
  - Call HAL_PWR_LP_SetConfigWakeupPin() function to configure wakeup pin.
  - Call HAL_PWR_LP_GetConfigWakeupPin() function to get wakeup pin configuration.
  - Call HAL_PWR_LP_EnableWakeupPin() function to enable wakeup pin.
  - Call HAL_PWR_LP_DisableWakeupPin() function to disable wakeup pin.
  - Call HAL_PWR_LP_IsEnabledWakeupPin() function to check whether the wakeup pin is enabled or not.
  */

/**
  * @brief  Set wakeup pin configuration.
  * @param  wakeup_pin        This parameter can be a combination of HAL_PWR_WAKEUP_PIN_x where x can be (1..7).
  * @param  p_config          Pointer to a @ref hal_pwr_wakeup_pin_config_t structure.
  * @retval HAL_INVALID_PARAM p_config pointer is NULL.
  * @retval HAL_OK            Wakeup pin has been correctly configured.
  */
hal_status_t HAL_PWR_LP_SetConfigWakeupPin(uint32_t wakeup_pin, const hal_pwr_wakeup_pin_config_t *p_config)
{
  uint32_t temp_pin = wakeup_pin;
  __IO uint32_t register_value = LL_PWR_READ_REG(WUCR);
  uint32_t position;
  uint32_t current_pin;

  ASSERT_DBG_PARAM(p_config != NULL);
  ASSERT_DBG_PARAM(IS_PWR_SET_WAKEUP_PIN(wakeup_pin));
  ASSERT_DBG_PARAM(IS_PWR_WAKEUP_PIN_POLARITY(p_config->polarity));
  ASSERT_DBG_PARAM(IS_PWR_WAKEUP_PIN_PULL(p_config->pull));

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_config == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  /* Get wakeup pin information */
  position    = POSITION_VAL(temp_pin);
  current_pin = 1UL << position;

  while (temp_pin != 0U)
  {
    /* Mask values which will be modified */
    register_value &= ~(uint32_t)((LL_PWR_WAKEUP_PIN_REF << position) \
                                  + (LL_PWR_WAKEUP_PIN_PULL_REF << (position * LL_PWR_WAKEUP_PINS_PULL_SHIFT_OFFSET)));

    /* Compute new value */
    register_value |= (uint32_t)(((uint32_t)(p_config->polarity) << (LL_PWR_WAKEUP_PIN_REF_POS + position))
                                 + ((uint32_t)(p_config->pull) << (LL_PWR_WAKEUP_PIN_PULL_REF_POS \
                                                                   + (position \
                                                                      * LL_PWR_WAKEUP_PINS_PULL_SHIFT_OFFSET))));

    /* Update wakeup pin information */
    temp_pin    &= (~current_pin);
    position    = POSITION_VAL(temp_pin);
    current_pin = 1UL << position;
  }

  /* Set new value in one register access */
  LL_PWR_WRITE_REG(WUCR, register_value);

  return HAL_OK;
}

/**
  * @brief  Get wakeup pin configuration.
  * @param  wakeup_pin This parameter can be one of HAL_PWR_WAKEUP_PIN_x where x can be (1..7).
  * @param  p_config   Pointer to a @ref hal_pwr_wakeup_pin_config_t structure.
  */
void HAL_PWR_LP_GetConfigWakeupPin(uint32_t wakeup_pin, hal_pwr_wakeup_pin_config_t *p_config)
{
  ASSERT_DBG_PARAM(p_config != NULL);
  ASSERT_DBG_PARAM(IS_PWR_GET_WAKEUP_PIN(wakeup_pin));

  p_config->polarity = (hal_pwr_wakeup_pin_polarity_t)LL_PWR_GetWakeUpPinPolarity(wakeup_pin);
  p_config->pull = (hal_pwr_wakeup_pin_pull_t)LL_PWR_GetWakeUpPinPull(wakeup_pin);
}

/**
  * @brief  Enable the wakeup pin configuration.
  * @param  wakeup_pin This parameter can be one or a combination of HAL_PWR_WAKEUP_PIN_x where x can be (1..7).
  * @note   Wakeup pins are used to wake up the system from Standby mode.
  */
void HAL_PWR_LP_EnableWakeupPin(uint32_t wakeup_pin)
{
  ASSERT_DBG_PARAM(IS_PWR_SET_WAKEUP_PIN(wakeup_pin));

  LL_PWR_EnableWakeUpPin(wakeup_pin);
}

/**
  * @brief  Disable the wakeup pin configuration.
  * @param  wakeup_pin This parameter can be one or a combination of HAL_PWR_WAKEUP_PIN_x where x can be (1..7).
  * @note   Wakeup pins are used to wake up the system from Standby mode.
  */
void HAL_PWR_LP_DisableWakeupPin(uint32_t wakeup_pin)
{
  ASSERT_DBG_PARAM(IS_PWR_SET_WAKEUP_PIN(wakeup_pin));

  LL_PWR_DisableWakeUpPin(wakeup_pin);
}

/**
  * @brief  Check whether wakeup pin is enabled or not.
  * @param  wakeup_pin                  This parameter can be one of HAL_PWR_WAKEUP_PIN_x where x can be (1..7).
  * @retval HAL_PWR_WAKEUP_PIN_DISABLED Wakeup pin disabled
  * @retval HAL_PWR_WAKEUP_PIN_ENABLED  Wakeup pin enabled
  */
hal_pwr_wakeup_pin_status_t HAL_PWR_LP_IsEnabledWakeupPin(uint32_t wakeup_pin)
{
  ASSERT_DBG_PARAM(IS_PWR_GET_WAKEUP_PIN(wakeup_pin));

  return ((hal_pwr_wakeup_pin_status_t)LL_PWR_IsEnabledWakeUpPin(wakeup_pin));
}
/**
  * @}
  */

/** @addtogroup PWR_Exported_Functions_Group2 RTC domain write protection management functions
  * @{
  This section provides functions allowing to manage RTC domain write protection:
  - Call HAL_PWR_EnableRTCDomainWriteProtection() to enable RTC domain write protection.
  - Call HAL_PWR_DisableRTCDomainWriteProtection() to disable RTC domain write protection.
  - Call HAL_PWR_IsEnabledRTCDomainWriteProtection() to check whether the RTC domain write protection is enabled or not.
  */

/**
  * @brief  Enable the RTC domain write protection (RCC RTC domain control register RCC_BDCR, RTC registers,
  *         TAMP registers, backup registers and backup SRAM).
  * @note   After a system reset, the RTC domain is protected against possible unwanted write accesses.
  */
void HAL_PWR_EnableRTCDomainWriteProtection(void)
{
  LL_PWR_EnableRTCDomainWriteProtection();
}

/**
  * @brief  Disable the RTC domain write protection (RCC RTC domain control register RCC_BDCR, RTC registers,
  *         TAMP registers, backup registers and backup SRAM).
  */
void HAL_PWR_DisableRTCDomainWriteProtection(void)
{
  LL_PWR_DisableRTCDomainWriteProtection();
}

/**
  * @brief  Check that RTC domain write protection is enabled.
  * @retval HAL_PWR_RTC_DOMAIN_WRP_DISABLED RTC domain write protection disabled.
  * @retval HAL_PWR_RTC_DOMAIN_WRP_ENABLED  RTC domain write protection enabled.
  */
hal_pwr_rtc_domain_wrp_status_t HAL_PWR_IsEnabledRTCDomainWriteProtection(void)
{
  return ((hal_pwr_rtc_domain_wrp_status_t)LL_PWR_IsEnabledRTCDomainWriteProtection());
}
/**
  * @}
  */

/** @addtogroup PWR_Exported_Functions_Group3 Low power mode management functions
  * @{
  This section provides functions allowing to manage low power modes:
  - Call HAL_PWR_ClearCorePendingEvent() function to clear the internal cortex event before entering low power mode
    using WFE.
  - Call HAL_PWR_EnterSleepMode() function to enter the core in sleep mode.
  - Call HAL_PWR_EnterStopMode() function to enter the MCU in stop x mode
  - Call HAL_PWR_EnterStandbyMode() function to enter the MCU in standby mode.
  - Call HAL_PWR_SetCoreSleepMode() function to configure the core in sleep or deep sleep mode.
  - Call HAL_PWR_GetCoreSleepMode() function to get core sleep mode configuration.
  - Call HAL_PWR_EnableCoreSleepOnExit() function to enable core to re-entry in sleep mode after an interrupt is over.
  - Call HAL_PWR_DisableCoreSleepOnExit() function to disable core to re-entry in sleep mode after an interrupt is over.
  - Call HAL_PWR_IsEnabledCoreSleepOnExit() function to check whether core send event on pending is enabled or not.
  - Call HAL_PWR_EnableCoreSendEventOnPending() function to enable core to wakeup after any pending event/ interrupt.
  - Call HAL_PWR_DisableCoreSendEventOnPending() function to disable core to wakeup after any pending event/ interrupt.
  - Call HAL_PWR_IsEnabledCoreSendEventOnPending() function to check whether core send event on pending is enabled or
    not.
  */

/**
  * @brief   Clear core pending event.
  * @note    This API clears the pending event in order to enter a given core to Sleep or stop mode with WFE entry.
  * @warning It must be called just before APIs performing enter Sleep and stop mode using Wait For Event request
  */
void HAL_PWR_ClearCorePendingEvent(void)
{
  __SEV();
  __WFE();
}

/**
  * @brief  Enter the core in Sleep mode.
  * @param  sleep_entry Parameter to @ref hal_pwr_low_pwr_mode_entry_t enumeration.
  */
void HAL_PWR_EnterSleepMode(hal_pwr_low_pwr_mode_entry_t sleep_entry)
{
  ASSERT_DBG_PARAM(IS_PWR_LP_MODE_ENTRY((uint32_t)sleep_entry));

  /* Clear SLEEPDEEP bit of Cortex System Control Register */
  CLEAR_BIT(SCB->SCR, SCB_SCR_SLEEPDEEP_Msk);

  if (sleep_entry == HAL_PWR_LOW_PWR_MODE_WFE)
  {
    /* Wait For Event Request */
    __WFE();
  }
  else
  {
    /* Wait For Interrupt Request */
    __WFI();
  }
}

/**
  * @brief  Enter the MCU in stop mode.
  * @param  stop_entry This parameter is an element of @ref hal_pwr_low_pwr_mode_entry_t enumeration.
  * @param  stop_mode  This parameter is an element of @ref hal_pwr_stop_mode_t enumeration.
  */
void HAL_PWR_EnterStopMode(hal_pwr_low_pwr_mode_entry_t stop_entry, hal_pwr_stop_mode_t stop_mode)
{
  ASSERT_DBG_PARAM(IS_PWR_LP_MODE_ENTRY((uint32_t)stop_entry));
  ASSERT_DBG_PARAM(IS_PWR_STOP_MODE((uint32_t)stop_mode));

  /* Set SLEEPDEEP bit of Cortex System Control Register */
  SET_BIT(SCB->SCR, SCB_SCR_SLEEPDEEP_Msk);

  LL_PWR_SetPowerMode((uint32_t)stop_mode);

  if (stop_entry == HAL_PWR_LOW_PWR_MODE_WFE)
  {
    /* Wait For Event Request */
    __WFE();
  }
  else
  {
    /* Wait For Interrupt Request */
    __WFI();
  }
}

/**
  * @brief  Enter the MCU in Standby mode.
  */
void HAL_PWR_EnterStandbyMode(void)
{
  /* Set SLEEPDEEP bit of Cortex System Control Register */
  SET_BIT(SCB->SCR, ((uint32_t)SCB_SCR_SLEEPDEEP_Msk));

  LL_PWR_SetPowerMode(LL_PWR_STANDBY_MODE);

  /* Wait For Interrupt Request */
  __WFI();
}

/**
  * @brief  Set the core sleep mode configuration.
  * @param  sleep_mode This parameter is an element of @ref hal_pwr_core_sleep_mode_t enumeration.
  */
void HAL_PWR_SetCoreSleepMode(hal_pwr_core_sleep_mode_t sleep_mode)
{
  ASSERT_DBG_PARAM(IS_PWR_CORE_SLEEP_MODE((uint32_t)sleep_mode));

  MODIFY_REG(SCB->SCR, SCB_SCR_SLEEPDEEP_Msk, (uint32_t)sleep_mode);
}

/**
  * @brief  Get the core sleep mode configuration.
  * @retval HAL_PWR_CORE_SLEEP      Core sleep mode.
  * @retval HAL_PWR_CORE_DEEP_SLEEP Core deep sleep mode.
  */
hal_pwr_core_sleep_mode_t HAL_PWR_GetCoreSleepMode(void)
{
  return ((hal_pwr_core_sleep_mode_t)((uint32_t)READ_BIT(SCB->SCR, SCB_SCR_SLEEPDEEP_Msk)));
}

/**
  * @brief  Enable SLEEP-ON-EXIT feature when returning from handler mode to thread mode.
  */
void HAL_PWR_EnableCoreSleepOnExit(void)
{
  SET_BIT(SCB->SCR, SCB_SCR_SLEEPONEXIT_Msk);
}

/**
  * @brief  Disable SLEEP-ON-EXIT feature when returning from handler mode to thread mode.
  */
void HAL_PWR_DisableCoreSleepOnExit(void)
{
  CLEAR_BIT(SCB->SCR, SCB_SCR_SLEEPONEXIT_Msk);
}

/**
  * @brief  Check if the Core SLEEP-ON-EXIT is enabled or disabled.
  * @retval hal_pwr_core_sleep_on_exit_status_t Core send event on pending status.
  */
hal_pwr_core_sleep_on_exit_status_t HAL_PWR_IsEnabledCoreSleepOnExit(void)
{
  uint32_t dummy = READ_BIT(SCB->SCR, SCB_SCR_SLEEPONEXIT_Msk) >> SCB_SCR_SLEEPONEXIT_Pos;

  return ((hal_pwr_core_sleep_on_exit_status_t)(dummy));
}

/**
  * @brief  Enable core Send Event On Pending feature.
  */
void HAL_PWR_EnableCoreSendEventOnPending(void)
{
  SET_BIT(SCB->SCR, SCB_SCR_SEVONPEND_Msk);
}

/**
  * @brief  Disable core Send Event On Pending.
  */
void HAL_PWR_DisableCoreSendEventOnPending(void)
{
  CLEAR_BIT(SCB->SCR, SCB_SCR_SEVONPEND_Msk);
}

/**
  * @brief  Get core Send Event On Pending.
  * @retval HAL_PWR_CORE_SEV_ON_PENDING_DISABLED Core send event on pending disabled.
  * @retval HAL_PWR_CORE_SEV_ON_PENDING_ENABLED  Core send event on pending enabled.
  */
hal_pwr_core_sev_on_pending_status_t HAL_PWR_IsEnabledCoreSendEventOnPending(void)
{
  uint32_t dummy = READ_BIT(SCB->SCR, SCB_SCR_SEVONPEND_Msk) >> SCB_SCR_SEVONPEND_Pos;

  return ((hal_pwr_core_sev_on_pending_status_t)(dummy));
}
/**
  * @}
  */

/** @addtogroup PWR_Exported_Functions_Group4 Voltage monitoring management functions
  * @{
  This section provides functions allowing to manage voltage monitoring.
  - Call HAL_PWR_EnableProgrammableVoltageDetector() function to enable the programmable voltage detector.
  - Call HAL_PWR_DisableProgrammableVoltageDetector() function to disable the programmable voltage detector.
  - Call HAL_PWR_IsEnabledProgrammableVoltageDetector() function to check whether the programmable voltage detector is
    enabled or not.
  */

/**
  * @brief  Enable the voltage threshold detection by the programmable voltage detector (PVD).
  */
void HAL_PWR_EnableProgrammableVoltageDetector(void)
{
  LL_PWR_EnablePVD();
}

/**
  * @brief  Disable the voltage threshold detection by the programmable voltage detector (PVD).
  */
void HAL_PWR_DisableProgrammableVoltageDetector(void)
{
  LL_PWR_DisablePVD();
}

/**
  * @brief  Check if the programmable voltage detection is enabled.
  * @retval HAL_PWR_PVD_DISABLED Programmable voltage detection disabled.
  * @retval HAL_PWR_PVD_ENABLED  Programmable voltage detection enabled.
  */
hal_pwr_pvd_status_t HAL_PWR_IsEnabledProgrammableVoltageDetector(void)
{
  return ((hal_pwr_pvd_status_t)LL_PWR_IsEnabledPVD());
}
/**
  * @}
  */

/** @addtogroup PWR_Exported_Functions_Group5 Memory retention management functions
  * @{
 This section provides functions allowing to manage memory content retention.
 - Call HAL_PWR_LP_EnableMemoryRetention() function to enable memory retention.
 - Call HAL_PWR_LP_DisableMemoryRetention() function to disable memory retention.
 - Call HAL_PWR_LP_IsEnabledMemoryRetention() to check whether selected memory retention is enabled or not.
 - Call HAL_PWR_LP_EnableMemoryPageRetention() function to enable memory retention for selected pages.
 - Call HAL_PWR_LP_DisableMemoryPageRetention() function to disable memory retention for selected pages.
 - Call HAL_PWR_LP_IsEnabledMemoryPageRetention() to check whether selected memory page retention is enabled or not.
  */

/**
  * @brief  Enable memory retention in stop mode.
  * @param  memory This parameter is an element of @ref hal_pwr_memory_retention_t enumeration.
  */
void HAL_PWR_LP_EnableMemoryRetention(hal_pwr_memory_retention_t memory)
{
  ASSERT_DBG_PARAM(IS_PWR_MEMORY_RETENTION((uint32_t)memory));

  LL_PWR_EnableMemoryStopRetention(PWR_MemoryFullRetentionMap[memory]);
}

/**
  * @brief  Disable memory retention in stop mode.
  * @param  memory  This parameter is an element of @ref hal_pwr_memory_retention_t enumeration.
  */
void HAL_PWR_LP_DisableMemoryRetention(hal_pwr_memory_retention_t memory)
{
  ASSERT_DBG_PARAM(IS_PWR_MEMORY_RETENTION((uint32_t)memory));

  LL_PWR_DisableMemoryStopRetention(PWR_MemoryFullRetentionMap[memory]);
}

/**
  * @brief  Get memory retention status.
  * @param  memory  This parameter is an element of @ref hal_pwr_memory_retention_t enumeration.
  * @retval HAL_PWR_MEMORY_RETENTION_DISABLED if the selected memory is not retained in stop mode.
  * @retval HAL_PWR_MEMORY_RETENTION_ENABLED  if the selected memory is retained in stop mode.
  */
hal_pwr_memory_retention_status_t HAL_PWR_LP_IsEnabledMemoryRetention(hal_pwr_memory_retention_t memory)
{
  ASSERT_DBG_PARAM(IS_PWR_MEMORY_RETENTION((uint32_t)memory));

  return ((hal_pwr_memory_retention_status_t)LL_PWR_IsEnabledMemoryStopRetention(PWR_MemoryFullRetentionMap[memory]));
}

/**
  * @brief  Enable memory page retention in stop mode.
  * @param  memory  This parameter is an element of @ref hal_pwr_memory_retention_t enumeration.
  * @param  page_idx  the index of memory page.
  * @param  page_nbr  The memory pages number.
  */
void HAL_PWR_LP_EnableMemoryPageRetention(hal_pwr_memory_retention_t memory, uint32_t page_idx, uint32_t page_nbr)
{
  uint32_t pages;
  uint32_t pageshift;

  ASSERT_DBG_PARAM(IS_PWR_MEMORY_PAGES_RETENTION((uint32_t)memory, page_idx, page_nbr));

  STM32_UNUSED(memory);

  /* Pages mask creation */
  pageshift = (page_idx + 1UL) % 2UL;
  pages = (page_idx + page_nbr) >> pageshift;
  pages = pages << LL_PWR_SRAM2_STOP_RETENTION_POS;
  pages &= LL_PWR_SRAM2_STOP_RETENTION;

  /* Pages stop retention enabling */
  LL_PWR_EnableSRAM2PagesStopRetention(pages);
}

/**
  * @brief  Disable memory page retention in stop mode.
  * @param  memory  This parameter is an element of @ref hal_pwr_memory_retention_t enumeration.
  * @param  page_idx  the index of memory page.
  * @param  page_nbr  The memory pages number.
  */
void HAL_PWR_LP_DisableMemoryPageRetention(hal_pwr_memory_retention_t memory, uint32_t page_idx, uint32_t page_nbr)
{
  uint32_t pages;
  uint32_t pageshift;

  ASSERT_DBG_PARAM(IS_PWR_MEMORY_PAGES_RETENTION((uint32_t)memory, page_idx, page_nbr));

  STM32_UNUSED(memory);

  /* Pages mask creation */
  pageshift = (page_idx + 1UL) % 2UL;
  pages = (page_idx + page_nbr) >> pageshift;
  pages = pages << LL_PWR_SRAM2_STOP_RETENTION_POS;
  pages &= LL_PWR_SRAM2_STOP_RETENTION;

  /* Pages stop retention disabling */
  LL_PWR_DisableSRAM2PagesStopRetention(pages);
}

/**
  * @brief  Check the selected memory page retention in stop mode status.
  * @param  memory  This parameter is an element of @ref hal_pwr_memory_retention_t enumeration.
  * @param  page_idx  the index of memory page.
  * @retval HAL_PWR_MEMORY_PAGE_RETENTION_DISABLED if the selected memory page is not retained in stop mode.
  * @retval HAL_PWR_MEMORY_PAGE_RETENTION_ENABLED  if the selected memory page is retained in stop mode.
  */
hal_pwr_memory_page_retention_status_t HAL_PWR_LP_IsEnabledMemoryPageRetention(hal_pwr_memory_retention_t memory,
                                                                               uint32_t page_idx)
{
  hal_pwr_memory_page_retention_status_t status;
  uint32_t page;
  uint32_t pageshift;

  ASSERT_DBG_PARAM(IS_PWR_MEMORY_PAGES_RETENTION((uint32_t)memory, page_idx, 1U));

  STM32_UNUSED(memory);

  /* Pages mask creation */
  pageshift = (page_idx + 1UL) % 2UL;
  page = (page_idx + 1UL) >> pageshift;
  page = page << LL_PWR_SRAM2_STOP_RETENTION_POS;
  page &= LL_PWR_SRAM2_STOP_RETENTION;

  /* Get memory page retention status */
  if (LL_PWR_IsEnabledSRAM2PagesStopRetention(page) != 0UL)
  {
    status = HAL_PWR_MEMORY_PAGE_RETENTION_ENABLED;
  }
  else
  {
    status = HAL_PWR_MEMORY_PAGE_RETENTION_DISABLED;
  }

  return status;
}
/**
  * @}
  */

/** @addtogroup PWR_Exported_Functions_Group6 Memory management functions
  * @{
 This section provides functions allowing to manage flash memory low power modes.
 - Call HAL_PWR_LP_EnableFlashLowPWRMode() function to enable flash memory power down in stop 0/1 mode.
 - Call HAL_PWR_LP_DisableFlashLowPWRMode() function to disable flash memory power down in stop 0/1 mode.
 - Call HAL_PWR_LP_IsEnabledFlashLowPWRMode() function to check the flash memory power down in stop 0/1 mode status.
  */
/**
  * @brief  Enable the flash low power mode.
  */
void HAL_PWR_LP_EnableFlashLowPWRMode(void)
{
  LL_PWR_EnableFlashLowPWRMode();
}

/**
  * @brief  Disable the flash low power mode.
  */
void HAL_PWR_LP_DisableFlashLowPWRMode(void)
{
  LL_PWR_DisableFlashLowPWRMode();
}

/**
  * @brief  Check if the flash low power mode is enabled or disabled.
  * @retval hal_pwr_Flash_low_pwr_mode_status_t flash low power mode status.
  */
hal_pwr_flash_low_pwr_mode_status_t HAL_PWR_LP_IsEnabledFlashLowPWRMode(void)
{
  return (hal_pwr_flash_low_pwr_mode_status_t)LL_PWR_IsEnabledFlashLowPWRMode();
}
/**
  * @}
  */

/** @addtogroup PWR_Exported_Functions_Group7 I/O retention management functions
  * @{
  This section provides functions allowing to manage IO retention in low power mode.
  - Call HAL_PWR_LP_EnableIORetention() function to enable the IO (GPIO and/or JTAGIO) retention in Standby mode.
  - Call HAL_PWR_LP_DisableIORetention() function to disable the IO (GPIO and/or JTAGIO) retention in Standby mode.
  - Call HAL_PWR_LP_IsEnabledIORetention() function to check if the IO (GPIO or JTAGIO) retention in Standby mode
    is enabled or disabled.
  */

/**
  * @brief  Enable the IO retention in Standby mode.
  * @note   The output is sampled, and apply to the output IO during the Standby mode.
  * @param  io This parameter is an element or combination of elements of \ref hal_pwr_io_retention_t enumeration.
  *            HAL_PWR_IO_RETENTION_JTAGIO IO retention mode is enabled for JTAG I/Os (PA13, PA14, PA15, and PB4).
  *            HAL_PWR_IO_RETENTION_GPIO   IO retention mode is enabled for all I/Os except the I/Os supporting
  *            the Standby functionality and JTAG I/Os.
  *            HAL_PWR_IO_RETENTION_ALL    IO retention mode is enabled for all I/Os.
  */
void HAL_PWR_LP_EnableIORetention(hal_pwr_io_retention_t io)
{
  ASSERT_DBG_PARAM(IS_PWR_SET_IO_RETENTION(((uint32_t)io)));

  if (((uint32_t)io & (uint32_t)HAL_PWR_IO_RETENTION_JTAGIO) == (uint32_t)HAL_PWR_IO_RETENTION_JTAGIO)
  {
    LL_PWR_EnableJTAGIORetentionStandbyMode();
  }

  if (((uint32_t)io & (uint32_t)HAL_PWR_IO_RETENTION_GPIO) == (uint32_t)HAL_PWR_IO_RETENTION_GPIO)
  {
    LL_PWR_EnableIORetentionStandbyMode();
  }
}

/**
  * @brief  Disable the IO retention in Standby mode.
  * @param  io This parameter is an element of \ref hal_pwr_io_retention_t enumeration.
  *            HAL_PWR_IO_RETENTION_JTAGIO IO retention mode is enabled for JTAG I/Os (PA13, PA14, PA15, and PB4).
  *            HAL_PWR_IO_RETENTION_GPIO   IO retention mode is enabled for all I/Os except the I/Os supporting
  *            the Standby functionality and JTAG I/Os.
  *            HAL_PWR_IO_RETENTION_ALL    IO retention mode is enabled for all I/Os.
  */
void HAL_PWR_LP_DisableIORetention(hal_pwr_io_retention_t io)
{
  ASSERT_DBG_PARAM(IS_PWR_SET_IO_RETENTION(((uint32_t)io)));

  if (((uint32_t)io & (uint32_t)HAL_PWR_IO_RETENTION_JTAGIO) == (uint32_t)HAL_PWR_IO_RETENTION_JTAGIO)
  {
    LL_PWR_DisableJTAGIORetentionStandbyMode();
  }

  if (((uint32_t)io & (uint32_t)HAL_PWR_IO_RETENTION_GPIO) == (uint32_t)HAL_PWR_IO_RETENTION_GPIO)
  {
    LL_PWR_DisableIORetentionStandbyMode();
  }
}

/**
  * @brief  Check if the IO retention in Standby mode is enabled or disabled.
  * @param  io This parameter is an element of \ref hal_pwr_io_retention_t enumeration.
  *            HAL_PWR_IO_RETENTION_JTAGIO IO retention mode is enabled for JTAG I/Os (PA13, PA14, PA15, and PB4).
  *            HAL_PWR_IO_RETENTION_GPIO   IO retention mode is enabled for all I/Os except the I/Os supporting
  *            the Standby functionality and JTAG I/Os.
  * @retval hal_pwr_io_retention_status_t The IO retention status.
  */
hal_pwr_io_retention_status_t HAL_PWR_LP_IsEnabledIORetention(hal_pwr_io_retention_t io)
{
  hal_pwr_io_retention_status_t status = HAL_PWR_IO_RETENTION_DISABLED;

  ASSERT_DBG_PARAM(IS_PWR_GET_IO_RETENTION((uint32_t)io));

  if (io == HAL_PWR_IO_RETENTION_JTAGIO)
  {
    status = (hal_pwr_io_retention_status_t)LL_PWR_IsEnabledJTAGIORetentionStandbyMode();
  }

  if (io == HAL_PWR_IO_RETENTION_GPIO)
  {
    status = (hal_pwr_io_retention_status_t)LL_PWR_IsEnabledIORetentionStandbyMode();
  }

  return status;
}
/**
  * @}
  */

/**
  * @}
  */

#endif /* USE_HAL_PWR_MODULE */

/**
  * @}
  */

/**
  * @}
  */
