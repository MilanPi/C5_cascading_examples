/**
  **********************************************************************************************************************
  * @file    stm32c5xx_hal_flash_itf.c
  * @author  GPM Application Team
  * @brief   This file provides FLASH peripheral services.
  **********************************************************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  **********************************************************************************************************************
  */

/* Includes ----------------------------------------------------------------------------------------------------------*/
#include "stm32_hal.h"


/** @addtogroup STM32C5xx_HAL_Driver
  * @{
  */

/** @addtogroup FLASH_ITF
  * @{
This file provides firmware functions to manage the following functionalities of FLASH option bytes peripheral:

- Lock and Unlock functions
- Configuration functions
- Launch functions

# FLASH option bytes main features

- The Flash Option Bytes, often referred to as "Option Bytes" or "OB" in the context of microcontrollers, are a set of
  configuration settings that can be programmed to customize the Behaviour of the flash memory and other features of a
  microcontroller. These Option Bytes are typically stored in a special area of the flash memory and are used to control
  various aspects of the device's operation.

## Lock mechanism :

  - After reset, the FLASH option bytes are write-protected.
    The Unlock sequence is necessary to run any operation on the FLASH option bytes.

## Option bytes :

  - Write protection area : The user area in flash memory can be protected against unwanted write operations.
                            Each block of up to 2 pages can be individually write-protected.

  - Read-out protection : The read-out protection protects the flash main memory, the option bytes, the backup
                          registers, the backup RAM and the SRAM. To reach the highest level of security.
                          - 3 levels (L0, L2_wBS and L2) of protection available.
                          - It is recommended to set a password for the L2_wBS and L2.

  - Hide protection area : A part of the main flash memory area.

  - Boot lock : Several option bytes cannot be modified when the boot lock mechanism enabled.

  - Boot address : The boot address option bytes are used to program any boot memory address. However, the allowed
                   address space depends on flash memory read protection RDP level.

  - User option bytes : There are option bytes that must include additional options to customize the behavior.
                        - Reset generation in low power mode, erase memories upon system reset, watchdog selection,
                          Independent watchdog counter freeze, Bank swapping, Single/Dual bank, Memories ECC, Boot0,
                          EDATA area, Bootloader Interface.

# How to use the FLASH_ITF HAL module driver

## Lock and unlock functions :

- Use the HAL_FLASH_ITF_Lock() and HAL_FLASH_ITF_Unlock() functions to lock and unlock the access to the FLASH control
  register.
- Use the HAL_FLASH_ITF_IsLocked() function to check the lock access state to the FLASH control register.

## Configuration functions :

- Use the HAL_FLASH_ITF_SetLatency() function to set the FLASH latency.
- Use the HAL_FLASH_ITF_GetLatency() function to get the FLASH latency.
- Use the HAL_FLASH_ITF_SetProgrammingDelay() function to set the FLASH programming delay.
- Use the HAL_FLASH_ITF_GetProgrammingDelay() function to get the FLASH programming delay.
- Use the HAL_FLASH_ITF_EnablePrefetch() function to enable the FLASH prefetch.
- Use the HAL_FLASH_ITF_DisablePrefetch() function to disable the FLASH prefetch.
- Use the HAL_FLASH_ITF_IsEnabledPrefetch() function to check if the FLASH prefetch is enabled or disabled.
- Use the HAL_FLASH_ITF_SetEmptyBootLocation() function to set the FLASh empty boot location information.
- Use the HAL_FLASH_ITF_GetEmptyBootLocation() function to get the FLASh empty boot location information.
- Use the HAL_FLASH_ITF_SetHDPExtArea() function to set the set the HDP extended area.
- Use the HAL_FLASH_ITF_GetHDPExtArea() function to get the get the HDP extended area.
- Use the HAL_FLASH_ITF_SetHDPLevel() function to set the HDP level value.
- Use the HAL_FLASH_ITF_GetHDPLevel() function to get the HDP level value.
- Use the HAL_FLASH_ITF_IsLockedRDPOEMKey() function to check if the RDP OEM key is locked or unlocked.
- Use the HAL_FLASH_ITF_IsLockedRDPBSKey() function to check if the RDP BS key is locked or unlocked.
- Use the HAL_FLASH_ITF_ECC_EnableIT() function to enable the FLASH ECC interruption.
- Use the HAL_FLASH_ITF_ECC_DisableIT() function to disable the FLASH ECC interruption.

## Option bytes lock and unlock functions :

- Use the HAL_FLASH_ITF_OB_Lock() function to lock the access to the FLASH option bytes registers.
- Use the HAL_FLASH_ITF_OB_Unlock() function to unlock the access to the FLASH option bytes registers.
- Use the HAL_FLASH_ITF_OB_IsLocked() function to check the lock state of the access to the FLASH option bytes
  registers.

## EDATA Area configuration :
- Use the HAL_FLASH_ITF_OB_EnableEDATAArea() function to enable the EDATA area.
- Use the HAL_FLASH_ITF_OB_DisableEDATAArea() function to disable the EDATA area.
- Use the HAL_FLASH_ITF_OB_IsEnabledEDATAArea() function to check if the EDATA area is enabled or disabled.

## Write protection area configuration :

- Use the HAL_FLASH_ITF_OB_EnablePageWRP() function to enable the FLASH ITF OB pagewise write protection area
  configuration.
- Use the HAL_FLASH_ITF_OB_DisablePageWRP() function to disable the FLASH ITF OB pagewise write protection area
  configuration.
- Use the HAL_FLASH_ITF_OB_IsEnabledPageWRP() function to check if the FLASH ITF OB pagewisewrite protection area
  configuration.
enabled or disabled.

## Read out protection configuration :

- Use the HAL_FLASH_ITF_OB_SetRDPLevel() function to set the FLASH ITF OB read-out protection level.
- Use the HAL_FLASH_ITF_OB_GetRDPLevel() function to get the FLASH ITF OB read-out protection level.
- Use the HAL_FLASH_ITF_OB_SetRDPOEMKey() function to set the FLASH ITF OB read-out protection OEM keys.
- Use the HAL_FLASH_ITF_OB_SetRDPBSKey() function to set the FLASH ITF OB read-out portection BS keys

## Enter low power modes by reset generation configuration :

- Use the HAL_FLASH_ITF_OB_SetEnterLowPWRModeRstGeneration() function to set the FLASH ITF OB enter stop mode,
  or standby mode reset generation configuration.
- Use the HAL_FLASH_ITF_OB_GetEnterLowPWRModeRstGeneration() function to get the FLASH ITF OB enter stop mode,
  or standby mode reset generation configuration.

## SRAM System reset erase configuration :

- Use the HAL_FLASH_ITF_OB_SetSystemRstSRAMErase() function to set the FLASH ITF OB system reset SRAM1 and SRAM2 erase
  configuration.
- Use the HAL_FLASH_ITF_OB_GetSystemRstSRAMErase() function to get the FLASH ITF OB system reset SRAM1 and SRAM2 erase
  configuration.

## WDG Mode configuration :

- Use the HAL_FLASH_ITF_OB_SetIWDGMode() function to set the FLASH ITF OB IWDG mode configuration.
- Use the HAL_FLASH_ITF_OB_GetIWDGMode() function to get the FLASH ITF OB IWDG mode configuration.
- Use the HAL_FLASH_ITF_OB_SetWWDGMode() function to set the FLASH ITF OB WWDG mode configuration.
- Use the HAL_FLASH_ITF_OB_GetWWDGMode() function to get the FLASH ITF OB WWDG mode configuration.

## WDG counter freeze configuration :

- Use the HAL_FLASH_ITF_OB_FreezeIWDGCounterLowPWRMode() function to freeze the FLASH ITF OB IWDG for stop and standby
  counter configuration.
- Use the HAL_FLASH_ITF_OB_UnfreezeIWDGCounterLowPWRMode() function to unfreeze the FLASH ITF OB IWDG stop and standby
  counter configuration.
- Use the HAL_FLASH_ITF_OB_IsFrozenIWDGCounterLowPWRMode() function to check the FLASH ITF OB IWDG stop and standby
  counter configuration is enabled.

## Bank swapping configuration :

- Use the HAL_FLASH_ITF_OB_SetBankSwap() function to set the FLASH ITF OB swap bank configuration.
- Use the HAL_FLASH_ITF_OB_GetBankSwap() function to get the FLASH ITF OB swap bank configuration.

## Bank configuration :

- Use the HAL_FLASH_ITF_OB_SetBankTopology() function to set the FLASH ITF OB single dual bank configuration.
- Use the HAL_FLASH_ITF_OB_GetBankTopology() function to get the FLASH ITF OB single dual bank configuration.

## SRAM ECC configuration :

- Use the HAL_FLASH_ITF_OB_EnableSRAMECC() function to enable the FLASH ITF OB for SRAM2 ECC configuration.
- Use the HAL_FLASH_ITF_OB_DisableSRAMECC() function to disable the FLASH ITF OB for SRAM2 ECC configuration.
- Use the HAL_FLASH_ITF_OB_IsEnabledSRAMECC() function to check the FLASH ITF OB for SRAM2 ECC configuration is enabled.

## Boot0 configuration :

- Use the HAL_FLASH_ITF_OB_SetBoot0() function to set the FLASH ITF OB boot0 configuration.
- Use the HAL_FLASH_ITF_OB_GetBoot0() function to get the FLASH ITF OB boot0 configuration.

## Hide protection configuration :

- Use the HAL_FLASH_ITF_OB_SetHDPArea() function to set the FLASH ITF OB hide protection area configuration.
- Use the HAL_FLASH_ITF_OB_GetHDPArea() function to get the FLASH ITF OB hide protection area configuration.

## Boot address configuration :

- Use the HAL_FLASH_ITF_OB_SetBootAddr() function to set the FLASH OB boot address configuration.
- Use the HAL_FLASH_ITF_OB_GetBootAddr() function to get the FLASH OB boot address configuration.
- Use the HAL_FLASH_ITF_OB_LockBootConfig() function to lock the FLASH option bytes boot configuration.
- Use the HAL_FLASH_ITF_OB_UnlockBootConfig() function to unlock the FLASH option bytes boot configuration.
- Use the HAL_FLASH_ITF_OB_IsLockedBootConfig() function to Check if the FLASH ITF OB boot configuration
  is locked or unlocked.

## Bootloader interface configuration :

- Use the HAL_FLASH_ITF_OB_SetBootloaderInterfaceConfig() function to set the bootloader interface configuration.
- Use the HAL_FLASH_ITF_OB_GetBootloaderInterfaceConfig() function to get the bootloader interface configuration.

## Option-bytes programming function :

- Use the FLASH_ITF_OB_Program() function to program the option-bytes.

## IRQHandler and Callback functions :

- Use the HAL_FLASH_ITF_IRQHandler() function to handle OB write/error operations.
- Use the HAL_FLASH_ITF_OB_ProgramCpltCallback() function to be redefined within application for the OB complete write
  operations callback.
- Use the HAL_FLASH_ITF_OB_ErrorCallback() function to be redefined within application for the OB write operation error
  callback.

# Configuration inside the FLASH ITF driver

Configuration defines        | Description     | Default value   | Note                                              |
-----------------------------|-----------------|-----------------|---------------------------------------------------|
PRODUCT                      | from IDE        |        NA       | The selected device (ex STM32U575xx).             |
USE_HAL_FLASH_ITF_MODULE     | from hal_conf.h |        1        | Allows to use HAL FLASH ITF module.               |
USE_ASSERT_DBG_PARAM         | from IDE        |      None       | Allows to use the assert check parameters.        |
  */

#if defined (USE_HAL_FLASH_ITF_MODULE) && (USE_HAL_FLASH_ITF_MODULE == 1)

/* Private Constants -------------------------------------------------------------------------------------------------*/
/** @defgroup FLASH_ITF_Private_Constants FLASH ITF Private Constants
  * @{
  */
#define FLASH_ITF_OB_TIMEOUT        1000U                                              /*!< FLASH default OB timeout */
#define FLASH_ITF_OB_LOW_PWR_MSK    (HAL_FLASH_ITF_OB_STOP_MODE      \
                                     | HAL_FLASH_ITF_OB_STANDBY_MODE)                  /*!< FLASH low power mask     */
#define FLASH_ITF_OB_SRAM_ERASE_MSK (HAL_FLASH_ITF_OB_SRAM2 | HAL_FLASH_ITF_OB_SRAM1)  /*!< FLASH sram erase mask    */
#define FLASH_ITF_OB_SRAM_ECC_MSK   (HAL_FLASH_ITF_OB_SRAM2)                           /*!< FLASH sram ecc mask      */
/**
  * @}
  */

/* Private macros ----------------------------------------------------------------------------------------------------*/
/** @defgroup FLASH_ITF_Private_Macros FLASH ITF Private Macros
  * @{
  */

/*! Macro to check FLASH memory bank */
#define IS_FLASH_ITF_BANK(value) (((value) == HAL_FLASH_ITF_BANK_1) || ((value) == HAL_FLASH_ITF_BANK_2))

/*! Macro to check FLASH memory latency */
#define IS_FLASH_ITF_LATENCY(value) (((value) == HAL_FLASH_ITF_LATENCY_0)  \
                                     || ((value) == HAL_FLASH_ITF_LATENCY_1)  \
                                     || ((value) == HAL_FLASH_ITF_LATENCY_2)  \
                                     || ((value) == HAL_FLASH_ITF_LATENCY_3)  \
                                     || ((value) == HAL_FLASH_ITF_LATENCY_4)  \
                                     || ((value) == HAL_FLASH_ITF_LATENCY_5)  \
                                     || ((value) == HAL_FLASH_ITF_LATENCY_6)  \
                                     || ((value) == HAL_FLASH_ITF_LATENCY_7)  \
                                     || ((value) == HAL_FLASH_ITF_LATENCY_8)  \
                                     || ((value) == HAL_FLASH_ITF_LATENCY_9)  \
                                     || ((value) == HAL_FLASH_ITF_LATENCY_10) \
                                     || ((value) == HAL_FLASH_ITF_LATENCY_11) \
                                     || ((value) == HAL_FLASH_ITF_LATENCY_12) \
                                     || ((value) == HAL_FLASH_ITF_LATENCY_13) \
                                     || ((value) == HAL_FLASH_ITF_LATENCY_14) \
                                     || ((value) == HAL_FLASH_ITF_LATENCY_15))

/*! Macro to check FLASH memory programming delay */
#define IS_FLASH_ITF_PROGRAMMING_DELAY(value) (((value) == HAL_FLASH_ITF_PROGRAM_DELAY_0)  \
                                               || ((value) == HAL_FLASH_ITF_PROGRAM_DELAY_1)  \
                                               || ((value) == HAL_FLASH_ITF_PROGRAM_DELAY_2))

/*! Macro to check FLASH empty boot location status */
#define IS_FLASH_ITF_EMPTY_BOOT_LOCATION(value) (((value) == HAL_FLASH_ITF_BOOT_LOCATION_PROGRAMMED) \
                                                 || ((value) == HAL_FLASH_ITF_BOOT_LOCATION_EMPTY))

/*! Macro to get the FLASH HDPExt bank */
#define FLASH_GET_HDPEXT_BANK(bank) (((bank) == HAL_FLASH_ITF_BANK_1) ? LL_FLASH_HDPEXT_BANK_1 : \
                                     (((bank) == HAL_FLASH_ITF_BANK_2) ? LL_FLASH_HDPEXT_BANK_2 : \
                                      0U))


#define IS_FLASH_ITF_HDPL_VALUE(value) (((value) == HAL_FLASH_ITF_HDP_LEVEL_1)  \
                                        || ((value) == HAL_FLASH_ITF_HDP_LEVEL_2)  \
                                        || ((value) == HAL_FLASH_ITF_HDP_LEVEL_3))

/*! Macro to check FLASH product state */
#define IS_FLASH_ITF_OB_RDP_LEVEL(value) (((value) == HAL_FLASH_ITF_OB_RDP_LEVEL_0)      \
                                          || ((value) == HAL_FLASH_ITF_OB_RDP_LEVEL_2_WBS) \
                                          || ((value) == HAL_FLASH_ITF_OB_RDP_LEVEL_2))

/*! Macro to check FLASH ITF OB low power mode */
#define IS_FLASH_ITF_OB_LOW_PWR_MODE(value) (((value) == HAL_FLASH_ITF_OB_STOP_MODE)    \
                                             || ((value) == HAL_FLASH_ITF_OB_STANDBY_MODE))

/*! Macro to check FLASH ITF OB low power reset generation */
#define IS_FLASH_ITF_OB_RST_GENERATION(value)(((value) == HAL_FLASH_ITF_OB_RST_GENERATION) \
                                              || ((value) == HAL_FLASH_ITF_OB_NO_RST_GENERATION))

/*! Macro to check FLASH ITF OB sram erase*/
#define IS_FLASH_ITF_OB_SRAM_ERASE(value) (((value) == HAL_FLASH_ITF_OB_SRAM2) \
                                           || ((value) == HAL_FLASH_ITF_OB_SRAM1))

/*! Macro to check FLASH ITF OB sram ecc*/
#define IS_FLASH_ITF_OB_SRAM_ECC(value) (((value) == HAL_FLASH_ITF_OB_SRAM2))

/*! Macro to check FLASH ITF OB system reset sram erase */
#define IS_FLASH_ITF_OB_SYSTEM_RST_SRAM_ERASE(value) (((value) == HAL_FLASH_ITF_OB_SYS_RST_SRAM_ERASE) \
                                                      || ((value) == HAL_FLASH_ITF_OB_SYS_RST_SRAM_NO_ERASE))


/*! Macro to check FLASH ITF OB wdg hardware/software mode */
#define IS_FLASH_ITF_OB_WDG_HW_SW_MODE(value) (((value) == HAL_FLASH_ITF_OB_WDG_HARDWARE) \
                                               || ((value) == HAL_FLASH_ITF_OB_WDG_SOFTWARE))

/*! Macro to check FLASH memory swap bank */
#define IS_FLASH_ITF_OB_SINGLE_DUAL_BANK(value) (((value) == HAL_FLASH_ITF_OB_SINGLE_BANK) \
                                                 || ((value) == HAL_FLASH_ITF_OB_DUAL_BANK))

/*! Macro to check FLASH memory swap bank */
#define IS_FLASH_ITF_OB_SWAP_BANK(value) (((value) == HAL_FLASH_ITF_OB_BANK_NO_SWAP) \
                                          || ((value) == HAL_FLASH_ITF_OB_BANK_SWAP))

/*! Macro to check FLASH memory boot0 source selection value */
#define IS_FLASH_ITF_OB_BOOT_SELECT(value) (((value) == HAL_FLASH_ITF_OB_BOOT_OPTION_BIT) \
                                            || ((value) == HAL_FLASH_ITF_OB_BOOT_PIN))

/*! Macro to check FLASH memory boot0 option-bit value */
#define IS_FLASH_ITF_OB_BOOT_STATE(value) (((value) == HAL_FLASH_ITF_OB_BOOT_LOW) \
                                           || ((value) == HAL_FLASH_ITF_OB_BOOT_HIGH))


/**
  * @}
  */

/* Private Functions Prototypes --------------------------------------------------------------------------------------*/
/** @defgroup FLASH_Private_Functions FLASH Private Functions
  * @{
  */
static hal_status_t FLASH_ITF_IsValidHDPLTransition(hal_flash_itf_hdp_level_t current_hdpl,
                                                    hal_flash_itf_hdp_level_t hdpl);
static hal_flash_itf_hdp_level_t FLASH_ITF_GetNextHDPL(hal_flash_itf_hdp_level_t current_hdpl);
static hal_status_t FLASH_ITF_OB_WaitForLastOperation(FLASH_TypeDef *flashx);
/**
  * @}
  */

/* Exported functions ------------------------------------------------------------------------------------------------*/
/** @addtogroup FLASH_OB_Exported_Functions
  * @{
  */

/** @addtogroup FLASH_OB_Exported_Functions_Group1
  * @{
This subsection provides a set of functions allowing to lock/unlock and configure the FLASH ITF peripheral:

- Call the HAL_FLASH_ITF_Lock() functions to lock the access to the FLASH control register.

- Call the HAL_FLASH_ITF_Unlock() functions to unlock the access to the FLASH control register.

- Call the HAL_FLASH_ITF_IsLocked() function to check the lock access state to the FLASH control register.

- Call the HAL_FLASH_ITF_SetLatency() function to set the FLASH latency.

- Call the HAL_FLASH_ITF_GetLatency() function to get the FLASH latency.

- Call the HAL_FLASH_ITF_SetProgrammingDelay() function to set the FLASH programming delay.

- Call the HAL_FLASH_ITF_GetProgrammingDelay() function to get the FLASH programming delay.

- Call the HAL_FLASH_ITF_EnablePrefetch() function to enable the FLASH prefetch.

- Call the HAL_FLASH_ITF_DisablePrefetch() function to disable the FLASH prefetch.

- Call the HAL_FLASH_ITF_IsEnabledPrefetch() function to check if the FLASH prefetch is enabled or disabled.

- Call the HAL_FLASH_ITF_SetEmptyBootLocation() function to set the FLASh empty boot location information.

- Call the HAL_FLASH_ITF_GetEmptyBootLocation() function to get the FLASh empty boot location information.

- Call the HAL_FLASH_ITF_SetHDPExtArea() function to set the HDP extended area.

- Call the HAL_FLASH_ITF_GetHDPExtArea() function to get the HDP extended area.

- Call the HAL_FLASH_ITF_SetHDPLevel() function to set the HDP level value.

- Call the HAL_FLASH_ITF_GetHDPLevel() function to get the HDP level value.

- Call the HAL_FLASH_ITF_IsLockedRDPOEMKey() function to check if the RDP OEM key is locked or unlocked.

- Call the HAL_FLASH_ITF_IsLockedRDPBSKey() function to check if the RDP BS key is locked or unlocked.

- Call the HAL_FLASH_ITF_ECC_EnableIT() function to enable the FLASH ECC interruption.

- Call the HAL_FLASH_ITF_ECC_DisableIT() function to disable the FLASH ECC interruption.
 */

/**
  * @brief  Lock the FLASH control register access.
  * @retval HAL_OK The FLASH registers access locked.
  */
hal_status_t HAL_FLASH_ITF_Lock(FLASH_TypeDef *flashx)
{
  ASSERT_DBG_PARAM(flashx != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(flashx));

  LL_FLASH_Lock(flashx);

  return HAL_OK;
}

/**
  * @brief  Unlock the FLASH control register access.
  * @retval HAL_OK The FLASH registers access unlocked.
  */
hal_status_t HAL_FLASH_ITF_Unlock(FLASH_TypeDef *flashx)
{
  ASSERT_DBG_PARAM(flashx != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(flashx));

  if (LL_FLASH_IsLocked(flashx) != 0U)
  {
    LL_FLASH_SetUnlockKey(flashx, LL_FLASH_KEY1);
    LL_FLASH_SetUnlockKey(flashx, LL_FLASH_KEY2);
  }

  return HAL_OK;
}

/**
  * @brief  Check if the FLASH control register access is locked or unlocked.
  * @retval Returned value can be one element of \ref hal_flash_itf_lock_status_t enumeration.
  */
hal_flash_itf_lock_status_t HAL_FLASH_ITF_IsLocked(const FLASH_TypeDef *flashx)
{
  ASSERT_DBG_PARAM(flashx != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(flashx));

  return ((hal_flash_itf_lock_status_t)LL_FLASH_IsLocked(flashx));
}

/**
  * @brief  Set the FLASH latency configuration.
  * @param  latency This parameter is one element of \ref hal_flash_itf_latency_t enumeration.
  * @retval HAL_OK  Latency is successfully configured.
  */
hal_status_t HAL_FLASH_ITF_SetLatency(FLASH_TypeDef *flashx, hal_flash_itf_latency_t latency)
{
  ASSERT_DBG_PARAM(flashx != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(flashx));
  ASSERT_DBG_PARAM(IS_FLASH_ITF_LATENCY(latency));

  LL_FLASH_SetLatency(flashx, (uint32_t)latency);

  return HAL_OK;
}

/**
  * @brief  Get the FLASH latency configuration.
  * @retval hal_flash_itf_latency_t Latency value.
  */
hal_flash_itf_latency_t HAL_FLASH_ITF_GetLatency(const FLASH_TypeDef *flashx)
{
  ASSERT_DBG_PARAM(flashx != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(flashx));

  return ((hal_flash_itf_latency_t)LL_FLASH_GetLatency(flashx));
}

/**
  * @brief  Set the FLASH programming delay configuration.
  * @param  prog_delay This parameter is one element of \ref hal_flash_itf_program_delay_t enumeration.
  * @retval HAL_OK  Programming Delay is successfully configured.
  */
hal_status_t HAL_FLASH_ITF_SetProgrammingDelay(FLASH_TypeDef *flashx, hal_flash_itf_program_delay_t prog_delay)
{
  ASSERT_DBG_PARAM(flashx != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(flashx));
  ASSERT_DBG_PARAM(IS_FLASH_ITF_PROGRAMMING_DELAY(prog_delay));

  LL_FLASH_SetProgrammingDelay(flashx, (uint32_t)prog_delay);

  return HAL_OK;
}

/**
  * @brief  Get the FLASH programming delay configuration.
  * @retval hal_flash_itf_program_delay_t programming delay value.
  */
hal_flash_itf_program_delay_t HAL_FLASH_ITF_GetProgrammingDelay(const FLASH_TypeDef *flashx)
{
  ASSERT_DBG_PARAM(flashx != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(flashx));

  return ((hal_flash_itf_program_delay_t)LL_FLASH_GetProgrammingDelay(flashx));
}

/**
  * @brief  Enable the FLASH prefetch.
  * @retval HAL_OK Prefetch enabled.
  */
hal_status_t HAL_FLASH_ITF_EnablePrefetch(FLASH_TypeDef *flashx)
{
  ASSERT_DBG_PARAM(flashx != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(flashx));


  LL_FLASH_EnablePrefetch(flashx);

  return HAL_OK;
}

/**
  * @brief  Disable the FLASH prefetch.
  * @retval HAL_OK Prefetch disabled.
  */
hal_status_t HAL_FLASH_ITF_DisablePrefetch(FLASH_TypeDef *flashx)
{
  ASSERT_DBG_PARAM(flashx != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(flashx));

  LL_FLASH_DisablePrefetch(flashx);

  return HAL_OK;
}

/**
  * @brief  Check if the FLASH prefetch is enabled or disabled.
  * @retval hal_flash_itf_prefetch_status_t Prefetch status.
  */
hal_flash_itf_prefetch_status_t HAL_FLASH_ITF_IsEnabledPrefetch(const FLASH_TypeDef *flashx)
{
  ASSERT_DBG_PARAM(flashx != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(flashx));

  return ((hal_flash_itf_prefetch_status_t)LL_FLASH_IsEnabledPrefetch(flashx));
}

/**
  * @brief  Set the FLASH empty boot location status.
  * @param  empty_boot This parameter is one element of \ref hal_flash_itf_empty_boot_location_t enumeration.
  * @retval HAL_OK  Programming Delay is successfully configured.
  */
hal_status_t HAL_FLASH_ITF_SetEmptyBootLocation(FLASH_TypeDef *flashx, hal_flash_itf_empty_boot_location_t empty_boot)
{
  ASSERT_DBG_PARAM(flashx != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(flashx));
  ASSERT_DBG_PARAM(IS_FLASH_ITF_EMPTY_BOOT_LOCATION(empty_boot));

  LL_FLASH_SetEmptyBootLocation(flashx, (uint32_t)empty_boot);

  return HAL_OK;
}

/**
  * @brief  Get the FLASH empty boot location status.
  * @retval hal_flash_itf_empty_boot_location_t programming delay value.
  */
hal_flash_itf_empty_boot_location_t HAL_FLASH_ITF_GetEmptyBootLocation(const FLASH_TypeDef *flashx)
{
  ASSERT_DBG_PARAM(flashx != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(flashx));

  return ((hal_flash_itf_empty_boot_location_t)LL_FLASH_GetEmptyBootLocation(flashx));
}

/**
  * @brief Set the HDP Extended area end page.
  *
  * @param  bank This parameter can be one element of \ref hal_flash_itf_bank_t enumeration.
  * @param  page_nbr This parameter can be any value between 0 and the maximum number of pages per bank.
  * @retval HAL_OK HDP Extended area number of pages set.
  */
hal_status_t HAL_FLASH_ITF_SetHDPExtArea(FLASH_TypeDef *flashx, hal_flash_itf_bank_t bank, uint32_t page_nbr)
{
  ASSERT_DBG_PARAM(flashx != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(flashx));
  ASSERT_DBG_PARAM(IS_FLASH_ITF_BANK(bank));
  ASSERT_DBG_PARAM(page_nbr < FLASH_PAGE_NB);

  LL_FLASH_BANK_SetHDPExtArea(flashx, FLASH_GET_HDPEXT_BANK(bank), page_nbr);

  return HAL_OK;
}

/**
  * @brief Get the HDP Extended area number of pages.
  *
  * @param  bank   This parameter can be one element of \ref hal_flash_itf_bank_t enumeration.
  * @retval uint32_t HDP Extended area number of pages value, between 0 and the maximum number of pages per bank.
  */
uint32_t HAL_FLASH_ITF_GetHDPExtArea(const FLASH_TypeDef *flashx, hal_flash_itf_bank_t bank)
{
  ASSERT_DBG_PARAM(flashx != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(flashx));
  ASSERT_DBG_PARAM(IS_FLASH_ITF_BANK(bank));

  return LL_FLASH_BANK_GetHDPExtArea(flashx, FLASH_GET_HDPEXT_BANK(bank));
}

hal_status_t HAL_FLASH_ITF_SetHDPLevel(const FLASH_TypeDef *flashx, hal_flash_itf_hdp_level_t hdp_level)
{
  ASSERT_DBG_PARAM(flashx != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(flashx));
  ASSERT_DBG_PARAM(IS_FLASH_ITF_HDPL_VALUE(hdp_level));

  STM32_UNUSED(flashx);

  hal_flash_itf_hdp_level_t current_hdpl = (hal_flash_itf_hdp_level_t) LL_SBS_GetHDPLevel();
  hal_flash_itf_hdp_level_t next_hdpl = current_hdpl;

  hal_status_t status = FLASH_ITF_IsValidHDPLTransition(current_hdpl, hdp_level);

  while ((status == HAL_OK) && (next_hdpl != hdp_level))
  {
    next_hdpl = FLASH_ITF_GetNextHDPL(next_hdpl);
    LL_SBS_IncrementHDPLevel();
    while (((hal_flash_itf_hdp_level_t)LL_SBS_GetHDPLevel()) != next_hdpl)
    {
    }
  }

  return status;
}

hal_flash_itf_hdp_level_t HAL_FLASH_ITF_GetHDPLevel(const FLASH_TypeDef *flashx)
{
  ASSERT_DBG_PARAM(flashx != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(flashx));

  STM32_UNUSED(flashx);

  return (hal_flash_itf_hdp_level_t)LL_SBS_GetHDPLevel();
}

/**
  * @brief  Check if the FLASH Readout Protection OEM key is locked or unlocked.
  * @retval hal_flash_itf_rdp_key_lock_status_t Readout Protection OEM key lock status.
  */
hal_flash_itf_rdp_key_lock_status_t HAL_FLASH_ITF_IsLockedRDPOEMKey(const FLASH_TypeDef *flashx)
{
  ASSERT_DBG_PARAM(flashx != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(flashx));

  return ((hal_flash_itf_rdp_key_lock_status_t)LL_FLASH_IsActiveFlag_OEMLOCK(flashx));
}

/**
  * @brief  Check if the FLASH Readout Protection BS key is locked or unlocked.
  * @retval hal_flash_itf_rdp_key_lock_status_t Readout Protection BS key lock status.
  */
hal_flash_itf_rdp_key_lock_status_t HAL_FLASH_ITF_IsLockedRDPBSKey(const FLASH_TypeDef *flashx)
{
  ASSERT_DBG_PARAM(flashx != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(flashx));

  return ((hal_flash_itf_rdp_key_lock_status_t)LL_FLASH_IsActiveFlag_BSLOCK(flashx));
}


#if defined (USE_HAL_FLASH_ITF_ECC) && (USE_HAL_FLASH_ITF_ECC == 1U)
/**
  * @brief  Enable the FLASH ECC interruption.
  * @retval HAL_OK ECC interruption enabled.
  */
hal_status_t HAL_FLASH_ITF_ECC_EnableIT(FLASH_TypeDef *flashx)
{
  ASSERT_DBG_PARAM(flashx != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(flashx));

  LL_FLASH_EnableIT_ECCC(flashx);

  return HAL_OK;
}

/**
  * @brief  Disable the FLASH ECC interruption.
  * @retval HAL_OK ECC interruption disabled.
  */
hal_status_t HAL_FLASH_ITF_ECC_DisableIT(FLASH_TypeDef *flashx)
{
  ASSERT_DBG_PARAM(flashx != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(flashx));

  LL_FLASH_DisableIT_ECCC(flashx);

  return HAL_OK;
}
#endif /* USE_HAL_FLASH_ITF_ECC */
/**
  * @}
  */
/** @addtogroup FLASH_OB_Exported_Functions_Group2
  * @{
This subsection provides a set of functions allowing to configure the FLASH peripheral option bytes:


- Call the HAL_FLASH_ITF_OB_Lock() function to lock the access to the FLASH option bytes registers.

- Call the HAL_FLASH_ITF_OB_Unlock() function to unlock the access to the FLASH option bytes registers.

- Call the HAL_FLASH_ITF_OB_IsLocked() function to check the lock state of the access to the FLASH option bytes

- Call the HAL_FLASH_ITF_OB_EnableEDATAArea() function to enable the EDATA area.

- Call the HAL_FLASH_ITF_OB_DisableEDATAArea() function to disable the EDATA area.

- Call the HAL_FLASH_ITF_OB_IsEnabledEDATAArea() function to check if the EDATA area is enabled or disabled.

- Call the HAL_FLASH_ITF_OB_EnablePageWRP() function to enable the FLASH ITF OB pagewise write protection area
  configuration.

- Call the HAL_FLASH_ITF_OB_DisablePageWRP() function to disable the FLASH ITF OB pagewise write protection area
  configuration.

- Call the HAL_FLASH_ITF_OB_IsEnabledPageWRP() function to check if the FLASH ITF OB pagewise write protection area
  configuration.
enabled or disabled.

- Call the HAL_FLASH_ITF_OB_SetRDPLevel() function to set the FLASH ITF OB read-out protection level.

- Call the HAL_FLASH_ITF_OB_GetRDPLevel() function to get the FLASH ITF OB read-out protection level.

- Call the HAL_FLASH_ITF_OB_SetRDPKey() function to set the FLASH ITF OB read-out protection keys.

- Call the HAL_FLASH_ITF_OB_SetEnterLowPWRModeRstGeneration() function to set the FLASH ITF OB enter stop mode,
  or standby mode reset generation configuration.

- Call the HAL_FLASH_ITF_OB_GetEnterLowPWRModeRstGeneration() function to get the FLASH ITF OB enter stop mode,
  or standby mode reset generation configuration.

- Call the HAL_FLASH_ITF_OB_SetSystemRstSRAMErase() function to set the FLASH ITF OB system reset SRAM1 and SRAM2 erase
  configuration.

- Call the HAL_FLASH_ITF_OB_GetSystemRstSRAMErase() function to get the FLASH ITF OB system reset SRAM1 and SRAM2 erase
  configuration.

- Call the HAL_FLASH_ITF_OB_SetIWDGMode() function to set the FLASH ITF OB IWDG mode configuration.

- Call the HAL_FLASH_ITF_OB_GetIWDGMode() function to get the FLASH ITF OB IWDG mode configuration.

- Call the HAL_FLASH_ITF_OB_SetWWDGMode() function to set the FLASH ITF OB WWDG mode configuration.

- Call the HAL_FLASH_ITF_OB_GetWWDGMode() function to get the FLASH ITF OB WWDG mode configuration.

- Call the HAL_FLASH_ITF_OB_FreezeIWDGCounterLowPWRMode() function to freeze the FLASH ITF OB IWDG for stop and standby
  counter configuration.

- Call the HAL_FLASH_ITF_OB_UnfreezeIWDGCounterLowPWRMode() function to unfreeze the FLASH ITF OB IWDG stop and standby
  counter configuration.

- Call the HAL_FLASH_ITF_OB_IsFrozenIWDGCounterLowPWRMode() function to check the FLASH ITF OB IWDG stop and standby
  counter configuration is enabled.

- Call the HAL_FLASH_ITF_OB_SetBankSwap() function to set the FLASH ITF OB swap bank configuration.

- Call the HAL_FLASH_ITF_OB_GetBankSwap() function to get the FLASH ITF OB swap bank configuration.

- Call the HAL_FLASH_ITF_OB_SetBankTopology() function to set the FLASH ITF OB single dual bank configuration.

- Call the HAL_FLASH_ITF_OB_GetBankTopology() function to get the FLASH ITF OB single dual bank configuration.

- Call the HAL_FLASH_ITF_OB_EnableSRAMECC() function to enable the FLASH ITF OB for SRAM2 ECC configuration.

- Call the HAL_FLASH_ITF_OB_DisableSRAMECC() function to disable the FLASH ITF OB for SRAM2 ECC configuration.

- Call the HAL_FLASH_ITF_OB_IsEnabledSRAMECC() function to check the FLASH ITF OB for SRAM2 ECC configuration
  is enabled.

- Call the HAL_FLASH_ITF_OB_SetBoot0() function to set the FLASH ITF OB boot0 configuration.

- Call the HAL_FLASH_ITF_OB_GetBoot0() function to get the FLASH ITF OB boot0 configuration.

- Call the HAL_FLASH_ITF_OB_SetHDPArea() function to set the FLASH ITF OB hide protection area configuration.

- Call the HAL_FLASH_ITF_OB_GetHDPArea() function to get the FLASH ITF OB hide protection area configuration.

- Call the HAL_FLASH_ITF_OB_SetBootAddr() function to set the FLASH OB boot address configuration.

- Call the HAL_FLASH_ITF_OB_GetBootAddr() function to get the FLASH OB boot address configuration.

- Call the HAL_FLASH_ITF_OB_LockBootConfig() function to lock the FLASH option bytes boot configuration.

- Call the HAL_FLASH_ITF_OB_UnlockBootConfig() function to unlock the FLASH option bytes boot configuration.

- Call the HAL_FLASH_ITF_OB_IsLockedBootConfig() function to Check if the FLASH ITF OB boot configuration
  is locked or unlocked.

- Call the HAL_FLASH_ITF_OB_SetBootloaderInterfaceConfig() function to set the bootloader interface configuration.

- Call the HAL_FLASH_ITF_OB_GetBootloaderInterfaceConfig() function to get the bootloader interface configuration.
  */

/**
  * @brief  Lock the FLASH OB control register access.
  * @retval HAL_OK   FLASH OB is successfully locked.
  */
hal_status_t HAL_FLASH_ITF_OB_Lock(FLASH_TypeDef *flashx)
{
  ASSERT_DBG_PARAM(flashx != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(flashx));

  LL_FLASH_OB_Lock(flashx);

  LL_FLASH_Lock(flashx);

  /* Verify that the Option-Bytes are locked */
  if (LL_FLASH_IsLocked(flashx) == 0U)
  {
    return HAL_ERROR;
  }

  return HAL_OK;
}

/**
  * @brief  Unlock the FLASH OB control register access.
  * @retval HAL_OK   FLASH OB is successfully unlocked.
  */
hal_status_t HAL_FLASH_ITF_OB_Unlock(FLASH_TypeDef *flashx)
{
  ASSERT_DBG_PARAM(flashx != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(flashx));

  if (LL_FLASH_IsLocked(flashx) == 1U)
  {
    LL_FLASH_SetUnlockKey(flashx, LL_FLASH_KEY1);
    LL_FLASH_SetUnlockKey(flashx, LL_FLASH_KEY2);
  }

  if (LL_FLASH_OB_IsLocked(flashx) == 1U)
  {
    LL_FLASH_OB_SetUnlockKey(flashx, LL_FLASH_OB_OPTKEY1);
    LL_FLASH_OB_SetUnlockKey(flashx, LL_FLASH_OB_OPTKEY2);
  }

  /* Verify that the Option-Bytes are unlocked */
  if (LL_FLASH_IsLocked(flashx) == 1U)
  {
    return HAL_ERROR;
  }

  return HAL_OK;
}

/**
  * @brief  Check if the FLASH OB control register access is locked or unlocked.
  * @retval Return value can be one element of \ref hal_flash_itf_ob_lock_status_t enumeration.
  */
hal_flash_itf_ob_lock_status_t HAL_FLASH_ITF_OB_IsLocked(const FLASH_TypeDef *flashx)
{
  ASSERT_DBG_PARAM(flashx != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(flashx));

  return ((hal_flash_itf_ob_lock_status_t)LL_FLASH_OB_IsLocked(flashx));
}

/**
  * @brief  Lock the selected blocks of the OTP flash area.
  *
  * @note   To configure the locked OTP blocks, the option lock bit OPTLOCK must be
  *         cleared with the call of the HAL_FLASH_ITF_OB_Unlock() function.
  *
  * @param  blocks     This parameter can be any combinations of @ref HAL_FLASH_ITF_OB_OTP_Lock_Blocks values.
  * @retval HAL_OK     FLASH OB OTP blocks are successfully locked.
  * @retval HAL_ERROR  FLASH OB write error generated.
  */
hal_status_t HAL_FLASH_ITF_OB_LockOTPBlock(FLASH_TypeDef *flashx, uint32_t blocks)
{
  ASSERT_DBG_PARAM(flashx != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(flashx));
  ASSERT_DBG_PARAM(blocks < HAL_FLASH_ITF_OB_OTP_BLK_ALL);

  if (FLASH_ITF_OB_WaitForLastOperation(flashx) != HAL_OK)
  {
    return HAL_ERROR;
  }

  LL_FLASH_OB_LockOTPBlock(flashx, blocks);

  return HAL_OK;
}

/**
  * @brief  Check if the selected OTP blocks are locked.
  * @param  block  This parameter can take any value of @ref HAL_FLASH_ITF_OB_OTP_Lock_Blocks.
  * @retval Return value can be one element of \ref hal_flash_itf_ob_otp_blk_lock_status_t enumeration.
  */
hal_flash_itf_ob_otp_blk_lock_status_t HAL_FLASH_ITF_OB_IsLockedOTPBlock(const FLASH_TypeDef *flashx, uint32_t block)
{
  ASSERT_DBG_PARAM(flashx != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(flashx));

  return (hal_flash_itf_ob_otp_blk_lock_status_t)LL_FLASH_OB_IsLockedOTPBlock(flashx, block);
}


/**
  * @brief  Enable the write protection feature on the selected pages of the given bank.
  *
  * @note   To configure the write protected pages, the option lock bit OPTLOCK must be
  *         cleared with the call of the HAL_FLASH_ITF_OB_Unlock() function.
  *
  * @param  bank       This parameter can be one element of \ref hal_flash_itf_bank_t enumeration.
  * @param  pages      This parameter can be any combinations of @ref HAL_FLASH_ITF_OB_Write_Protection_Pages values.
  * @retval HAL_OK     FLASH OB write protection area is successfully configured.
  * @retval HAL_ERROR  FLASH OB write error generated.
  */
hal_status_t HAL_FLASH_ITF_OB_EnablePageWRP(FLASH_TypeDef *flashx, hal_flash_itf_bank_t bank, uint32_t pages)
{
  ASSERT_DBG_PARAM(flashx != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(flashx));
  ASSERT_DBG_PARAM(IS_FLASH_ITF_BANK(bank));

  if (FLASH_ITF_OB_WaitForLastOperation(flashx) != HAL_OK)
  {
    return HAL_ERROR;
  }

  LL_FLASH_OB_BANK_EnablePageWRP(flashx, (uint32_t)bank, pages);
  return HAL_OK;
}

/**
  * @brief  Disable the write protection feature on the selected pages of the given bank.
  *
  * @note   To configure the write protected pages, the option lock bit OPTLOCK must be
  *         cleared with the call of the HAL_FLASH_ITF_OB_Unlock() function.
  *
  * @param  bank       This parameter can be one element of \ref hal_flash_itf_bank_t enumeration.
  * @param  pages      This parameter can be any combinations @ref HAL_FLASH_ITF_OB_Write_Protection_Pages.
  * @retval HAL_OK     FLASH OB write protection area is successfully configured.
  * @retval HAL_ERROR  FLASH OB write error generated.
  */
hal_status_t HAL_FLASH_ITF_OB_DisablePageWRP(FLASH_TypeDef *flashx, hal_flash_itf_bank_t bank, uint32_t pages)
{
  ASSERT_DBG_PARAM(flashx != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(flashx));
  ASSERT_DBG_PARAM(IS_FLASH_ITF_BANK(bank));

  if (FLASH_ITF_OB_WaitForLastOperation(flashx) != HAL_OK)
  {
    return HAL_ERROR;
  }

  LL_FLASH_OB_BANK_DisablePageWRP(flashx, (uint32_t)bank, pages);
  return HAL_OK;
}

/**
  * @brief  Get the state  of page write protection configuration for the selected pages of the given bank.
  * @param  bank  This parameter can be one element of \ref hal_flash_itf_bank_t enumeration.
  * @param  page  This parameter can be any value of @ref HAL_FLASH_ITF_OB_Write_Protection_Pages.
  * @retval Return value can be one element of \ref hal_flash_itf_ob_wrp_page_status_t enumeration.
  */
hal_flash_itf_ob_wrp_page_status_t HAL_FLASH_ITF_OB_IsEnabledPageWRP(const FLASH_TypeDef *flashx,
                                                                     hal_flash_itf_bank_t bank,
                                                                     uint32_t page)
{
  ASSERT_DBG_PARAM(flashx != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(flashx));
  ASSERT_DBG_PARAM(IS_FLASH_ITF_BANK(bank));

  return (hal_flash_itf_ob_wrp_page_status_t)LL_FLASH_OB_BANK_IsEnabledPageWRP(flashx, (uint32_t)bank, page);
}

/**
  * @brief  Enable the data flash area.
  *
  * @note   Before enabling the data flash area, the option lock bit OPTLOCK must
  *         be previously cleared with the call of the HAL_FLASH_ITF_OB_Unlock() function.
  *
  * @retval HAL_OK     FLASH OB data FLASH is successfully enabled.
  * @retval HAL_ERROR  FLASH OB write error generated.
  */
hal_status_t HAL_FLASH_ITF_OB_EnableEDATAArea(FLASH_TypeDef *flashx)
{
  ASSERT_DBG_PARAM(flashx != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(flashx));

  if (FLASH_ITF_OB_WaitForLastOperation(flashx) != HAL_OK)
  {
    return HAL_ERROR;
  }

  LL_FLASH_OB_EnableEDATAArea(flashx);
  return HAL_OK;
}

/**
  * @brief  Disable the data flash area.
  *
  * @note   To disable the data flash area, the option lock bit OPTLOCK mustbe cleared
  *         with the call of the HAL_FLASH_ITF_OB_Unlock() function.
  *
  * @retval HAL_OK     FLASH OB data FLASH is successfully disabled.
  * @retval HAL_ERROR  FLASH OB write error generated.
  */
hal_status_t HAL_FLASH_ITF_OB_DisableEDATAArea(FLASH_TypeDef *flashx)
{
  ASSERT_DBG_PARAM(flashx != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(flashx));

  if (FLASH_ITF_OB_WaitForLastOperation(flashx) != HAL_OK)
  {
    return HAL_ERROR;
  }

  LL_FLASH_OB_DisableEDATAArea(flashx);
  return HAL_OK;
}

/**
  * @brief  Check if the data flash area of the selected bank is enabled or not.
  * @retval Return value can be one element of \ref hal_flash_itf_ob_edata_area_status_t enumeration.
  */
hal_flash_itf_ob_edata_area_status_t HAL_FLASH_ITF_OB_IsEnabledEDATAArea(const FLASH_TypeDef *flashx)
{
  ASSERT_DBG_PARAM(flashx != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(flashx));

  return (hal_flash_itf_ob_edata_area_status_t)LL_FLASH_OB_IsEnabledEDATAArea(flashx);
}

/**
  * @brief  Set the HDP area start page.
  *
  * @note   To configure the HDP area start page, the option lock bit OPTLOCK must be
  *         cleared with the call of the HAL_FLASH_ITF_OB_Unlock() function.
  *
  * @param  bank        This parameter can be one element of \ref hal_flash_itf_bank_t enumeration.
  * @param  start_page  This parameter can take any value between 0 and the maximum number of pages.
  * @param  page_nbr    Number of page of the hide protection area.
  * @retval HAL_OK      FLASH OB HDP area start page is successfully configured.
  * @retval HAL_ERROR   FLASH OB write error generated.
  */
hal_status_t HAL_FLASH_ITF_OB_SetHDPArea(FLASH_TypeDef *flashx,
                                         hal_flash_itf_bank_t bank,
                                         uint32_t start_page,
                                         uint32_t page_nbr)
{
  ASSERT_DBG_PARAM(flashx != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(flashx));
  ASSERT_DBG_PARAM(IS_FLASH_ITF_BANK(bank));
  ASSERT_DBG_PARAM(start_page < FLASH_PAGE_NB);

  if (FLASH_ITF_OB_WaitForLastOperation(flashx) != HAL_OK)
  {
    return HAL_ERROR;
  }

  LL_FLASH_OB_BANK_ConfigHDPArea(flashx, (uint32_t)bank, start_page, start_page + page_nbr - 1U);
  return HAL_OK;
}

/**
  * @brief  Get the hide protection area configuration.
  * @param  bank This parameter can be one element of \ref hal_flash_itf_bank_t enumeration.
  * @param  p_start_page Pointer to start page of the hide protection area.
  * @param  p_page_nbr   Pointer to number of page of the hide protection area.
  */
void HAL_FLASH_ITF_OB_GetHDPArea(const FLASH_TypeDef *flashx, hal_flash_itf_bank_t bank,
                                 uint32_t *p_start_page, uint32_t *p_page_nbr)
{
  ASSERT_DBG_PARAM(IS_FLASH_ITF_BANK(bank));
  ASSERT_DBG_PARAM(p_start_page != NULL);
  ASSERT_DBG_PARAM(p_page_nbr != NULL);

  *p_start_page = LL_FLASH_OB_BANK_GetHDPAreaStartPage(flashx, (uint32_t)bank);
  *p_page_nbr   = (LL_FLASH_OB_BANK_GetHDPAreaEndPage(flashx, (uint32_t)bank) - *p_start_page + 1U);
}

/**
  * @brief  Set the RDP level.
  *
  * @note   To configure the RDP level, the option lock bit OPTLOCK must be
  *         cleared with the call of the HAL_FLASH_ITF_OB_Unlock() function.
  *
  * @param  rdp_level Element from the \ref hal_flash_itf_ob_rdp_level_t enumeration.
  *
  * @retval HAL_OK    FLASH OB RDP level is successfully configured.
  * @retval HAL_ERROR FLASH OB write error generated.
  */
hal_status_t HAL_FLASH_ITF_OB_SetRDPLevel(FLASH_TypeDef *flashx, hal_flash_itf_ob_rdp_level_t rdp_level)
{
  ASSERT_DBG_PARAM(flashx != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(flashx));
  ASSERT_DBG_PARAM(IS_FLASH_ITF_OB_RDP_LEVEL(rdp_level));

  if (FLASH_ITF_OB_WaitForLastOperation(flashx) != HAL_OK)
  {
    return HAL_ERROR;
  }

  LL_FLASH_OB_SetRDPLevel(flashx, (uint32_t)rdp_level);
  return HAL_OK;
}

/**
  * @brief  Get the FLASH OB RDP level configuration.
  * @retval Return value can be one element of \ref hal_flash_itf_ob_rdp_level_t enumeration.
  */
hal_flash_itf_ob_rdp_level_t HAL_FLASH_ITF_OB_GetRDPLevel(const FLASH_TypeDef *flashx)
{
  ASSERT_DBG_PARAM(flashx != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(flashx));

  return (hal_flash_itf_ob_rdp_level_t)LL_FLASH_OB_GetRDPLevel(flashx);
}

/**
  * @brief  Set the FLASH OB OEM key configuration.
  *
  * @note   To configure the OEM key, the option lock bit OPTLOCK must be
  *         cleared with the call of the HAL_FLASH_ITF_OB_Unlock() function.
  *
  * @warning This function assumes that the value pointed by the pointer passed as parameter is of the specified RDP
  *          key size, e.g. 128 bits for OEM key and 32 bits for BS key.
  *          Since this key definition is unique and irreversible, make sure that the value has a correct size to
  *          ensure its future use for RDP regression.
  *
  * @param  p_key     Pointer to the key value.
  * @retval HAL_OK    FLASH OB OEM key is successfully configured.
  * @retval HAL_ERROR FLASH OB write error generated.
  */
hal_status_t HAL_FLASH_ITF_OB_SetRDPOEMKey(FLASH_TypeDef *flashx, const hal_flash_itf_ob_rdp_oem_key_t *p_key)
{
  ASSERT_DBG_PARAM(flashx != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(flashx));

  if (FLASH_ITF_OB_WaitForLastOperation(flashx) != HAL_OK)
  {
    return HAL_ERROR;
  }

  if (LL_FLASH_IsActiveFlag_OEMLOCK(flashx) != 0U)
  {
    return HAL_ERROR;
  }
  LL_FLASH_OB_SetOEMKeyWord1(flashx, p_key->key_w1);
  LL_FLASH_OB_SetOEMKeyWord2(flashx, p_key->key_w2);
  LL_FLASH_OB_SetOEMKeyWord3(flashx, p_key->key_w3);
  LL_FLASH_OB_SetOEMKeyWord4(flashx, p_key->key_w4);

  return HAL_OK;
}

/**
  * @brief  Set the FLASH OB BS key configuration.
  *
  * @note   To configure the BS key, the option lock bit OPTLOCK must be
  *         cleared with the call of the HAL_FLASH_ITF_OB_Unlock() function.
  *
  * @param  p_key         Pointer to the key value.
  * @retval HAL_OK        FLASH OB BS key is successfully configured.
  * @retval HAL_ERROR     FLASH OB write error generated.
  */
hal_status_t HAL_FLASH_ITF_OB_SetRDPBSKey(FLASH_TypeDef *flashx, const hal_flash_itf_ob_rdp_bs_key_t *p_key)
{
  ASSERT_DBG_PARAM(flashx != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(flashx));

  if (FLASH_ITF_OB_WaitForLastOperation(flashx) != HAL_OK)
  {
    return HAL_ERROR;
  }

  if (LL_FLASH_IsActiveFlag_BSLOCK(flashx) != 0U)
  {
    return HAL_ERROR;
  }

  LL_FLASH_OB_SetBSKey(flashx, p_key->key_w1);

  return HAL_OK;
}


/**
  * @brief  Set the FLASH OB enter stop mode reset generation configuration.
  *
  * @note   To configure the reset generation upon entering stop mode, the option lock bit OPTLOCK must be
  *         cleared with the call of the HAL_FLASH_ITF_OB_Unlock() function.
  *
  * @param  low_pwr_mode
  *         This parameter can take one of the following values:
  *         @arg @ref HAL_FLASH_ITF_OB_STOP_MODE
  *         @arg @ref HAL_FLASH_ITF_OB_STANDBY_MODE
  * @param  rst_gen   Element from the \ref hal_flash_itf_ob_rst_generation_status_t enumeration.
  * @retval HAL_OK    FLASH OB enter low-power mode reset generation is successfully configured.
  * @retval HAL_ERROR FLASH OB write error generated.
  */
hal_status_t HAL_FLASH_ITF_OB_SetEnterLowPWRModeRstGeneration(FLASH_TypeDef *flashx, uint32_t low_pwr_mode,
                                                              hal_flash_itf_ob_rst_generation_status_t rst_gen)
{
  ASSERT_DBG_PARAM((low_pwr_mode & FLASH_ITF_OB_LOW_PWR_MSK) == low_pwr_mode);
  ASSERT_DBG_PARAM(IS_FLASH_ITF_OB_RST_GENERATION(rst_gen));

  if (FLASH_ITF_OB_WaitForLastOperation(flashx) != HAL_OK)
  {
    return HAL_ERROR;
  }

  if ((low_pwr_mode & HAL_FLASH_ITF_OB_STOP_MODE) == HAL_FLASH_ITF_OB_STOP_MODE)
  {
    LL_FLASH_OB_SetNRSTStopMode(flashx, (uint32_t)rst_gen * LL_FLASH_OB_NO_RST_STOP_MODE);
  }

  if ((low_pwr_mode & HAL_FLASH_ITF_OB_STANDBY_MODE) == HAL_FLASH_ITF_OB_STANDBY_MODE)
  {
    LL_FLASH_OB_SetNRSTStandbyMode(flashx, (uint32_t)rst_gen * LL_FLASH_OB_NO_RST_STDBY_MODE);
  }

  return HAL_OK;
}

/**
  * @brief  Get the FLASH OB enter stop mode reset generation configuration.
  * @param  low_pwr_mode
  *         This parameter can take one of the following values:
  *         @arg @ref HAL_FLASH_ITF_OB_STOP_MODE
  *         @arg @ref HAL_FLASH_ITF_OB_STANDBY_MODE
  * @retval Return value can be one element of \ref hal_flash_itf_ob_rst_generation_status_t enumeration.
  */
hal_flash_itf_ob_rst_generation_status_t HAL_FLASH_ITF_OB_GetEnterLowPWRModeRstGeneration(const FLASH_TypeDef *flashx,
    uint32_t low_pwr_mode)
{
  ASSERT_DBG_PARAM(flashx != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(flashx));
  ASSERT_DBG_PARAM(IS_FLASH_ITF_OB_LOW_PWR_MODE(low_pwr_mode));

  if (low_pwr_mode == HAL_FLASH_ITF_OB_STOP_MODE)
  {
    return (hal_flash_itf_ob_rst_generation_status_t)
           ((uint32_t)(LL_FLASH_OB_GetNRSTStopMode(flashx) >> FLASH_OPTSR_PRG_NRST_STOP_Pos));
  }
  else
  {
    return (hal_flash_itf_ob_rst_generation_status_t)
           ((uint32_t)(LL_FLASH_OB_GetNRSTStandbyMode(flashx) >> FLASH_OPTSR_PRG_NRST_STDBY_Pos));
  }
}

/**
  * @brief  Set the FLASH OB system reset SRAM1 erase configuration.
  *
  * @note   To configure the SRAM1 erase upon system reset, the option lock bit OPTLOCK must be
  *         cleared with the call of the HAL_FLASH_ITF_OB_Unlock() function.
  *
  * @param  sram
  *         This parameter can take one of the following values:
  *         @arg @ref HAL_FLASH_ITF_OB_SRAM2
  *         @arg @ref HAL_FLASH_ITF_OB_SRAM1
  * @param  sram_erase Element from the \ref hal_flash_itf_ob_sys_rst_sram_erase_t enumeration.
  * @retval HAL_OK     FLASH OB erase sram on system reset is successfully configured.
  * @retval HAL_ERROR  FLASH OB write error generated.
  */
hal_status_t HAL_FLASH_ITF_OB_SetSystemRstSRAMErase(FLASH_TypeDef *flashx,
                                                    uint32_t sram,
                                                    hal_flash_itf_ob_sys_rst_sram_erase_t sram_erase)
{
  ASSERT_DBG_PARAM(flashx != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(flashx));
  ASSERT_DBG_PARAM((sram & FLASH_ITF_OB_SRAM_ERASE_MSK) == sram);
  ASSERT_DBG_PARAM(IS_FLASH_ITF_OB_SYSTEM_RST_SRAM_ERASE(sram_erase));

  if (FLASH_ITF_OB_WaitForLastOperation(flashx) != HAL_OK)
  {
    return HAL_ERROR;
  }

  if ((sram & HAL_FLASH_ITF_OB_SRAM2) == HAL_FLASH_ITF_OB_SRAM2)
  {
    LL_FLASH_OB_SetSystemResetSRAM2Erase(flashx, (uint32_t)sram_erase * LL_FLASH_OB_NOT_ERASED_SRAM2_SYS_RST);
  }

  if ((sram & HAL_FLASH_ITF_OB_SRAM1) == HAL_FLASH_ITF_OB_SRAM1)
  {
    LL_FLASH_OB_SetSystemResetSRAM1Erase(flashx, (uint32_t)sram_erase * LL_FLASH_OB_NOT_ERASED_SRAM1_SYS_RST);
  }

  return HAL_OK;
}

/**
  * @brief  Get the FLASH OB system reset SRAM erase configuration.
  * @param  sram
  *         This parameter can take one of the following values:
  *         @arg @ref HAL_FLASH_ITF_OB_SRAM2
  *         @arg @ref HAL_FLASH_ITF_OB_SRAM1
  * @retval Return value can be one element of \ref hal_flash_itf_ob_sys_rst_sram_erase_t enumeration.
  */
hal_flash_itf_ob_sys_rst_sram_erase_t HAL_FLASH_ITF_OB_GetSystemRstSRAMErase(const FLASH_TypeDef *flashx, uint32_t sram)
{
  ASSERT_DBG_PARAM(flashx != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(flashx));
  ASSERT_DBG_PARAM(IS_FLASH_ITF_OB_SRAM_ERASE(sram));

  if (sram == HAL_FLASH_ITF_OB_SRAM2)
  {
    return (hal_flash_itf_ob_sys_rst_sram_erase_t)
           ((uint32_t)(LL_FLASH_OB_GetSystemResetSRAM2Erase(flashx) >> FLASH_OPTSR2_PRG_SRAM2_RST_Pos));
  }
  else
  {
    return (hal_flash_itf_ob_sys_rst_sram_erase_t)
           ((uint32_t)(LL_FLASH_OB_GetSystemResetSRAM1Erase(flashx) >> FLASH_OPTSR2_PRG_SRAM1_RST_Pos));
  }
}

/**
  * @brief  Set the FLASH OB IWDG mode configuration.
  *
  * @note   To configure the IWDG control mode, the option lock bit OPTLOCK must be
  *         cleared with the call of the HAL_FLASH_ITF_OB_Unlock() function.
  *
  * @param  mode      Element from the \ref hal_flash_itf_ob_wdg_mode_t enumeration.
  * @retval HAL_OK    FLASH OB IWDG mode is successfully configured.
  * @retval HAL_ERROR FLASH OB write error generated.
  */
hal_status_t HAL_FLASH_ITF_OB_SetIWDGMode(FLASH_TypeDef *flashx, hal_flash_itf_ob_wdg_mode_t mode)
{
  ASSERT_DBG_PARAM(flashx != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(flashx));
  ASSERT_DBG_PARAM(IS_FLASH_ITF_OB_WDG_HW_SW_MODE(mode));

  if (FLASH_ITF_OB_WaitForLastOperation(flashx) != HAL_OK)
  {
    return HAL_ERROR;
  }

  LL_FLASH_OB_SetIWDGSelection(flashx, (uint32_t)mode * LL_FLASH_OB_IWDG_SW);

  return HAL_OK;
}

/**
  * @brief  Get the FLASH OB IWDG mode configuration.
  * @retval Return value can be one element of \ref hal_flash_itf_ob_wdg_mode_t enumeration.
  */
hal_flash_itf_ob_wdg_mode_t HAL_FLASH_ITF_OB_GetIWDGMode(const FLASH_TypeDef *flashx)
{
  ASSERT_DBG_PARAM(flashx != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(flashx));

  return (hal_flash_itf_ob_wdg_mode_t)((uint32_t)(LL_FLASH_OB_GetIWDGSelection(flashx) >> FLASH_OPTSR_PRG_IWDG_SW_Pos));
}

/**
  * @brief  Set the FLASH OB WWDG mode configuration.
  *
  * @note   To configure the WWDG control mode, the option lock bit OPTLOCK must be
  *         cleared with the call of the HAL_FLASH_ITF_OB_Unlock() function.
  *
  * @param  mode      Element from the \ref hal_flash_itf_ob_wdg_mode_t enumeration.
  * @retval HAL_OK    FLASH OB WWDG mode is successfully configured.
  * @retval HAL_ERROR FLASH OB write error generated.
  */
hal_status_t HAL_FLASH_ITF_OB_SetWWDGMode(FLASH_TypeDef *flashx, hal_flash_itf_ob_wdg_mode_t mode)
{
  ASSERT_DBG_PARAM(flashx != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(flashx));
  ASSERT_DBG_PARAM(IS_FLASH_ITF_OB_WDG_HW_SW_MODE(mode));

  if (FLASH_ITF_OB_WaitForLastOperation(flashx) != HAL_OK)
  {
    return HAL_ERROR;
  }

  LL_FLASH_OB_SetWWDGSelection(flashx, (uint32_t)mode * LL_FLASH_OB_WWDG_SW);

  return HAL_OK;
}

/**
  * @brief  Get the FLASH OB WWDG mode configuration.
  * @retval Return value can be one element of \ref hal_flash_itf_ob_wdg_mode_t enumeration.
  */
hal_flash_itf_ob_wdg_mode_t HAL_FLASH_ITF_OB_GetWWDGMode(const FLASH_TypeDef *flashx)
{
  ASSERT_DBG_PARAM(flashx != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(flashx));

  return (hal_flash_itf_ob_wdg_mode_t)((uint32_t)(LL_FLASH_OB_GetWWDGSelection(flashx) >> FLASH_OPTSR_PRG_WWDG_SW_Pos));
}

/**
  * @brief  Freeze the FLASH OB IWDG counter in low power mode configuration.
  *
  * @note   To configure the IWDG freeze in low-power mode, the option lock bit OPTLOCK must be
  *         cleared with the call of the HAL_FLASH_ITF_OB_Unlock() function.
  *
  * @param  mode
  *         This parameter can take one of the following values:
  *         @arg @ref HAL_FLASH_ITF_OB_STOP_MODE
  *         @arg @ref HAL_FLASH_ITF_OB_STANDBY_MODE
  * @retval HAL_OK    FLASH OB IWDG counter is frozen in specified low-power mode.
  * @retval HAL_ERROR FLASH OB write error generated.
  */
hal_status_t HAL_FLASH_ITF_OB_FreezeIWDGCounterLowPWRMode(FLASH_TypeDef *flashx, uint32_t mode)
{
  ASSERT_DBG_PARAM(flashx != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(flashx));
  ASSERT_DBG_PARAM((mode & FLASH_ITF_OB_LOW_PWR_MSK) == mode);

  if (FLASH_ITF_OB_WaitForLastOperation(flashx) != HAL_OK)
  {
    return HAL_ERROR;
  }

  if ((mode & HAL_FLASH_ITF_OB_STOP_MODE) == HAL_FLASH_ITF_OB_STOP_MODE)
  {
    LL_FLASH_OB_FreezeIWDGStopMode(flashx);
  }

  if ((mode & HAL_FLASH_ITF_OB_STANDBY_MODE) == HAL_FLASH_ITF_OB_STANDBY_MODE)
  {
    LL_FLASH_OB_FreezeIWDGStandbyMode(flashx);
  }

  return HAL_OK;
}

/**
  * @brief  Unfreeze the FLASH OB IWDG counter in low-power mode configuration.
  *
  * @note   To configure the IWDG freeze in low-power mode, the option lock bit OPTLOCK must be
  *         cleared with the call of the HAL_FLASH_ITF_OB_Unlock() function.
  *
  * @param  mode
  *         This parameter can take one of the following values:
  *         @arg @ref HAL_FLASH_ITF_OB_STOP_MODE
  *         @arg @ref HAL_FLASH_ITF_OB_STANDBY_MODE
  * @retval HAL_OK    FLASH OB IWDG counter is not frozen in specified low-power mode.
  * @retval HAL_ERROR FLASH OB write error generated.
  */
hal_status_t HAL_FLASH_ITF_OB_UnfreezeIWDGCounterLowPWRMode(FLASH_TypeDef *flashx, uint32_t mode)
{
  ASSERT_DBG_PARAM(flashx != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(flashx));
  ASSERT_DBG_PARAM((mode & FLASH_ITF_OB_LOW_PWR_MSK) == mode);

  if (FLASH_ITF_OB_WaitForLastOperation(flashx) != HAL_OK)
  {
    return HAL_ERROR;
  }

  if ((mode & HAL_FLASH_ITF_OB_STOP_MODE) == HAL_FLASH_ITF_OB_STOP_MODE)
  {
    LL_FLASH_OB_UnfreezeIWDGStopMode(flashx);
  }

  if ((mode & HAL_FLASH_ITF_OB_STANDBY_MODE) == HAL_FLASH_ITF_OB_STANDBY_MODE)
  {
    LL_FLASH_OB_UnfreezeIWDGStandbyMode(flashx);
  }

  return HAL_OK;
}

/**
  * @brief  Check the FLASH OB freeze IWDG counter in low-power mode configuration.
  *
  * @param  mode
  *         This parameter can take one of the following values:
  *         @arg @ref HAL_FLASH_ITF_OB_STOP_MODE
  *         @arg @ref HAL_FLASH_ITF_OB_STANDBY_MODE
  * @retval Return value can be one element of \ref hal_flash_itf_ob_wdg_freeze_status_t enumeration.
  */
hal_flash_itf_ob_wdg_freeze_status_t HAL_FLASH_ITF_OB_IsFrozenIWDGCounterLowPWRMode(const FLASH_TypeDef *flashx,
    uint32_t mode)
{
  ASSERT_DBG_PARAM(flashx != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(flashx));
  ASSERT_DBG_PARAM(IS_FLASH_ITF_OB_LOW_PWR_MODE(mode));

  if (mode == HAL_FLASH_ITF_OB_STOP_MODE)
  {
    return (hal_flash_itf_ob_wdg_freeze_status_t)LL_FLASH_OB_IsFrozenIWDGStopMode(flashx);
  }
  else
  {
    return (hal_flash_itf_ob_wdg_freeze_status_t)LL_FLASH_OB_IsFrozenIWDGStandbyMode(flashx);
  }
}

/**
  * @brief  Set the FLASH ITF OB boot0 configuration.
  * @param  boot_select Element from \ref hal_flash_itf_ob_boot_selection_t enumeration.
  * @retval HAL_OK          FLASH ITF OB boot0 is successfully configured.
  * @retval HAL_ERROR       FLASH ITF OB write error generated.
  */
hal_status_t HAL_FLASH_ITF_OB_SetBootSelection(FLASH_TypeDef *flashx, hal_flash_itf_ob_boot_selection_t boot_select)
{
  ASSERT_DBG_PARAM(flashx != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(flashx));
  ASSERT_DBG_PARAM(IS_FLASH_ITF_OB_BOOT_SELECT(boot_select));

  if (FLASH_ITF_OB_WaitForLastOperation(flashx) != HAL_OK)
  {
    return HAL_ERROR;
  }

  LL_FLASH_OB_SetBoot0SourceSelection(flashx, (uint32_t)boot_select);
  return HAL_OK;
}

/**
  * @brief  Get the FLASH ITF OB boot0 source selection configuration.
  * @retval hal_flash_itf_ob_boot_selection_t FLASH ITF OB boot0 source selected.
  */
hal_flash_itf_ob_boot_selection_t HAL_FLASH_ITF_OB_GetBootSelection(const FLASH_TypeDef *flashx)
{
  ASSERT_DBG_PARAM(flashx != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(flashx));

  return (hal_flash_itf_ob_boot_selection_t)LL_FLASH_OB_GetBoot0SourceSelection(flashx);
}

/**
  * @brief  Set the FLASH ITF OB boot0 option-bit state configuration.
  * @param  boot0     Element from \ref hal_flash_itf_ob_boot_state_t enumeration.
  * @retval HAL_OK    FLASH ITF OB boot0 is successfully configured.
  * @retval HAL_ERROR FLASH ITF OB write error generated.
  */
hal_status_t HAL_FLASH_ITF_OB_SetBoot0(FLASH_TypeDef *flashx, hal_flash_itf_ob_boot_state_t boot0)
{
  ASSERT_DBG_PARAM(flashx != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(flashx));
  ASSERT_DBG_PARAM(IS_FLASH_ITF_OB_BOOT_STATE(boot0));

  if (FLASH_ITF_OB_WaitForLastOperation(flashx) != HAL_OK)
  {
    return HAL_ERROR;
  }

  LL_FLASH_OB_SetBoot0(flashx, (uint32_t)boot0);
  return HAL_OK;
}

/**
  * @brief  Get the FLASH ITF OB boot0 option-bit state configuration.
  * @retval hal_flash_itf_ob_boot_selection_t FLASH ITF OB boot0 option-bit state configuration.
  */
hal_flash_itf_ob_boot_state_t HAL_FLASH_ITF_OB_GetBoot0(const FLASH_TypeDef *flashx)
{
  ASSERT_DBG_PARAM(flashx != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(flashx));

  return (hal_flash_itf_ob_boot_state_t)LL_FLASH_OB_GetBoot0(flashx);
}

/**
  * @brief  Set the FLASH ITF OB single/dual bank configuration for products with less user memory.
  * @note   Before setting the bank topology, the option lock bit OPTLOCK must
  *         be previously cleared with the call of the HAL_FLASH_ITF_OB_Unlock() function.
  * @param bank_topology This parameter is one element of \ref hal_flash_itf_ob_topology_t  enumeration.
  * @retval HAL_OK    FLASH OB single-bank option-bit value is successfully enabled.
  * @retval HAL_ERROR FLASH OB write error generated.
  */
hal_status_t HAL_FLASH_ITF_OB_SetBankTopology(FLASH_TypeDef *flashx, hal_flash_itf_ob_topology_t bank_topology)
{
  ASSERT_DBG_PARAM(flashx != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(flashx));
  ASSERT_DBG_PARAM(IS_FLASH_ITF_OB_SINGLE_DUAL_BANK(bank_topology));

  if (FLASH_ITF_OB_WaitForLastOperation(flashx) != HAL_OK)
  {
    return HAL_ERROR;
  }

  LL_FLASH_OB_SetBank(flashx, (uint32_t)bank_topology);
  return HAL_OK;
}

/**
  * @brief  Get the FLASH ITF OB single/dual bank configuration.
  * @retval hal_flash_itf_ob_topology_t FLASH ITF OB single/dual bank configuration.
  */
hal_flash_itf_ob_topology_t HAL_FLASH_ITF_OB_GetBankTopology(const FLASH_TypeDef *flashx)
{
  ASSERT_DBG_PARAM(flashx != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(flashx));

  return (hal_flash_itf_ob_topology_t)LL_FLASH_OB_GetBank(flashx);
}

/**
  * @brief  Set the FLASH OB bank swapping configuration.
  *
  * @note   To configure the bank swapping, the option lock bit OPTLOCK must be
  *         cleared with the call of the HAL_FLASH_ITF_OB_Unlock() function.
  *
  * @param  bank_swap This parameter is one element of \ref hal_flash_itf_ob_bank_swap_t enumeration.
  * @retval HAL_OK    FLASH OB bank swapping is successfully configured.
  * @retval HAL_ERROR FLASH OB write error generated.
  */
hal_status_t HAL_FLASH_ITF_OB_SetBankSwap(FLASH_TypeDef *flashx, hal_flash_itf_ob_bank_swap_t bank_swap)
{
  ASSERT_DBG_PARAM(flashx != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(flashx));
  ASSERT_DBG_PARAM(IS_FLASH_ITF_OB_SWAP_BANK(bank_swap));

  if (FLASH_ITF_OB_WaitForLastOperation(flashx) != HAL_OK)
  {
    return HAL_ERROR;
  }

  LL_FLASH_OB_SetSwapBank(flashx, (uint32_t)bank_swap);
  return HAL_OK;
}

/**
  * @brief  Get the FLASH OB bank swapping configuration.
  * @retval Return value can be one element of \ref hal_flash_itf_ob_bank_swap_t enumeration.
  */
hal_flash_itf_ob_bank_swap_t HAL_FLASH_ITF_OB_GetBankSwap(const FLASH_TypeDef *flashx)
{
  ASSERT_DBG_PARAM(flashx != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(flashx));

  return ((hal_flash_itf_ob_bank_swap_t)LL_FLASH_OB_GetSwapBank(flashx));
}

/**
  * @brief  Enable the FLASH OB SRAM ECC configuration.
  *
  * @note   To configure the SRAM ECC feature, the option lock bit OPTLOCK must be
  *         cleared with the call of the HAL_FLASH_ITF_OB_Unlock() function.
  *
  * @param  sram
  *         This parameter can take one of the following values:
  *         @arg @ref HAL_FLASH_ITF_OB_SRAM2
  * @retval HAL_OK    FLASH OB SRAM ECC is successfully configured.
  * @retval HAL_ERROR FLASH OB write error generated.
  */
hal_status_t HAL_FLASH_ITF_OB_EnableSRAMECC(FLASH_TypeDef *flashx, uint32_t sram)
{
  ASSERT_DBG_PARAM(flashx != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(flashx));
  ASSERT_DBG_PARAM((sram & FLASH_ITF_OB_SRAM_ECC_MSK) == sram);

  if (FLASH_ITF_OB_WaitForLastOperation(flashx) != HAL_OK)
  {
    return HAL_ERROR;
  }

  if ((sram & HAL_FLASH_ITF_OB_SRAM2) == HAL_FLASH_ITF_OB_SRAM2)
  {
    LL_FLASH_OB_EnableECCSRAM2(flashx);
  }

  return HAL_OK;
}

/**
  * @brief  Disable the FLASH OB SRAM ECC configuration.
  *
  * @note   To configure the SRAM ECC feature, the option lock bit OPTLOCK must be
  *         cleared with the call of the HAL_FLASH_ITF_OB_Unlock() function.
  *
  * @param  sram
  *         This parameter can take one of the following values:
  *         @arg @ref HAL_FLASH_ITF_OB_SRAM2
  * @retval HAL_OK    FLASH OB SRAM ECC is successfully configured.
  * @retval HAL_ERROR FLASH OB write error generated.
  */
hal_status_t HAL_FLASH_ITF_OB_DisableSRAMECC(FLASH_TypeDef *flashx, uint32_t sram)
{
  ASSERT_DBG_PARAM(flashx != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(flashx));
  ASSERT_DBG_PARAM((sram & FLASH_ITF_OB_SRAM_ECC_MSK) == sram);

  if (FLASH_ITF_OB_WaitForLastOperation(flashx) != HAL_OK)
  {
    return HAL_ERROR;
  }

  if ((sram & HAL_FLASH_ITF_OB_SRAM2) == HAL_FLASH_ITF_OB_SRAM2)
  {
    LL_FLASH_OB_DisableECCSRAM2(flashx);
  }

  return HAL_OK;
}

/**
  * @brief  Check the FLASH OB SRAM2 ECC configuration is enabled or disabled.
  * @param  sram
  *         This parameter can take one of the following values:
  *         @arg @ref HAL_FLASH_ITF_OB_SRAM2
  * @retval Return value can be one element of \ref hal_flash_itf_ob_sram_ecc_status_t enumeration.
  */
hal_flash_itf_ob_sram_ecc_status_t HAL_FLASH_ITF_OB_IsEnabledSRAMECC(const FLASH_TypeDef *flashx, uint32_t sram)
{
  ASSERT_DBG_PARAM(flashx != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(flashx));
  ASSERT_DBG_PARAM(IS_FLASH_ITF_OB_SRAM_ECC(sram));
  STM32_UNUSED(sram);
  return (hal_flash_itf_ob_sram_ecc_status_t)LL_FLASH_OB_IsEnabledECCSRAM2(flashx);
}

/**
  * @brief  Set the FLASH OB unique boot address configuration.
  *
  * @note   To configure the boot address, the option lock bit OPTLOCK must be
  *         cleared with the call of the HAL_FLASH_ITF_OB_Unlock() function.
  *
  * @param  boot_addr Boot address to be configured.
  * @retval HAL_OK    FLASH OB boot address is successfully configured.
  * @retval HAL_ERROR FLASH OB write error generated.
  */
hal_status_t HAL_FLASH_ITF_OB_SetBootAddr(FLASH_TypeDef *flashx, uint32_t boot_addr)
{
  ASSERT_DBG_PARAM(flashx != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(flashx));

  if (FLASH_ITF_OB_WaitForLastOperation(flashx) != HAL_OK)
  {
    return HAL_ERROR;
  }

  LL_FLASH_OB_SetBootAddr(flashx, boot_addr);
  return HAL_OK;
}

/**
  * @brief  Get the FLASH OB unique boot address 0 configuration.
  * @retval Return the configured boot address.
  */
uint32_t HAL_FLASH_ITF_OB_GetBootAddr(const FLASH_TypeDef *flashx)
{
  ASSERT_DBG_PARAM(flashx != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(flashx));

  return LL_FLASH_OB_GetBootAddr(flashx);
}

/**
  * @brief  Lock FLASH OB unique boot address.
  *
  * @note   To configure the boot address lock, the option lock bit OPTLOCK must be
  *         cleared with the call of the HAL_FLASH_ITF_OB_Unlock() function.
  *
  * @retval HAL_OK    FLASH OB boot address is successfully locked.
  * @retval HAL_ERROR FLASH OB write error generated.
  */
hal_status_t HAL_FLASH_ITF_OB_LockBootConfig(FLASH_TypeDef *flashx)
{
  ASSERT_DBG_PARAM(flashx != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(flashx));

  if (FLASH_ITF_OB_WaitForLastOperation(flashx) != HAL_OK)
  {
    return HAL_ERROR;
  }

  LL_FLASH_OB_LockBootConfig(flashx);
  return HAL_OK;
}

/**
  * @brief  Unlock FLASH OB unique boot address.
  *
  * @note   To configure the boot address lock, the option lock bit OPTLOCK must be
  *         cleared with the call of the HAL_FLASH_ITF_OB_Unlock() function.
  *
  * @retval HAL_OK    FLASH OB boot address is successfully unlocked.
  * @retval HAL_ERROR FLASH OB write error generated.
  */
hal_status_t HAL_FLASH_ITF_OB_UnlockBootConfig(FLASH_TypeDef *flashx)
{
  ASSERT_DBG_PARAM(flashx != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(flashx));

  if (FLASH_ITF_OB_WaitForLastOperation(flashx) != HAL_OK)
  {
    return HAL_ERROR;
  }

  LL_FLASH_OB_UnlockBootConfig(flashx);
  return HAL_OK;
}

/**
  * @brief  Check if the FLASH OB unique boot address is locked or not.
  *
  * @retval Return value can be one element of \ref hal_flash_itf_ob_boot_lock_status_t enumeration.
  */
hal_flash_itf_ob_boot_lock_status_t HAL_FLASH_ITF_OB_IsLockedBootConfig(const FLASH_TypeDef *flashx)
{
  ASSERT_DBG_PARAM(flashx != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(flashx));

  return (hal_flash_itf_ob_boot_lock_status_t)LL_FLASH_OB_IsLockedBootConfig(flashx);
}

/**
  * @brief  Set the bootloader interface configuration to the specified value.
  *
  * @note   To configure the bootloader interface, the option lock bit OPTLOCK must be
  *         cleared with the call of the HAL_FLASH_ITF_OB_Unlock() function.
  *
  * @param  bootloader_config  This parameter can be any value between 0x00000000 and 0xFFFFFFFF.
  * @retval HAL_OK             FLASH OB bootloader configuration is successfully configured.
  * @retval HAL_ERROR          FLASH OB write error generated.
  */
hal_status_t HAL_FLASH_ITF_OB_SetBootloaderInterfaceConfig(FLASH_TypeDef *flashx, uint32_t bootloader_config)
{
  ASSERT_DBG_PARAM(flashx != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(flashx));

  if (FLASH_ITF_OB_WaitForLastOperation(flashx) != HAL_OK)
  {
    return HAL_ERROR;
  }

  LL_FLASH_OB_SetBootloaderInterfaceConfig(flashx, bootloader_config);
  return HAL_OK;
}

/**
  * @brief  Get the bootloader interface configuration.
  * @retval Returned value can be any value between 0x00000000 and 0xFFFFFFFF.
  */
uint32_t HAL_FLASH_ITF_OB_GetBootloaderInterfaceConfig(const FLASH_TypeDef *flashx)
{
  ASSERT_DBG_PARAM(flashx != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(flashx));

  return  LL_FLASH_OB_GetBootloaderInterfaceConfig(flashx);
}

/**
  * @}
  */

/** @addtogroup FLASH_ITF_Exported_Functions_Group3
  * @{
This subsection provides a set of functions allowing to handle the FLASH ITF ECC interrupt subroutines:

- Call the function HAL_FLASH_ITF_IRQHandler() to handle Flash ECC error correction and OB write operations.

- Call the function HAL_FLASH_ITF_NMI_IRQHandler() to handle the ECC detection interrupt under NMI_IRQHandler interrupt
  subroutine.

- Call the function HAL_FLASH_ITF_ECC_IRQHandler() to handle any enabled interrupt and call its corresponding callback.

- Call the function HAL_FLASH_ITF_NMI_ECC_IRQHandler() to Handle the FLASH ECC detection interrupt request.

- Call the function HAL_FLASH_ITF_ECC_ErrorCallback() to be redefined within application for the ECC callback.

- Call the function HAL_FLASH_ITF_OB_ProgramCpltCallback() to be redefined within application for the OB complete write
  operation callback.

- Call the function HAL_FLASH_ITF_OB_ErrorCallback() to be redefined within application the OB write error operation
  callback.
  */

/**
  * @brief  Handle the FLASH ITF interrupt request.
  */
void HAL_FLASH_ITF_IRQHandler(FLASH_TypeDef *flashx)
{
  ASSERT_DBG_PARAM(flashx != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(flashx));

  uint32_t flags = LL_FLASH_READ_REG(flashx, SR);

  if (READ_BIT(flags, LL_FLASH_FLAG_EOP) != 0U)
  {
    LL_FLASH_ClearFlag(flashx, LL_FLASH_FLAG_EOP);
    HAL_FLASH_ITF_OB_ProgramCpltCallback(flashx);
  }

  if (READ_BIT(flags, LL_FLASH_FLAG_OPTCHANGEERR) != 0U)
  {
    LL_FLASH_ClearFlag(flashx, LL_FLASH_FLAG_OPTCHANGEERR);
    HAL_FLASH_ITF_OB_ErrorCallback(flashx);
  }
}

/**
  * @brief  FLASH ITF option bytes write complete callback.
  */
__WEAK void HAL_FLASH_ITF_OB_ProgramCpltCallback(FLASH_TypeDef *flashx)
{
  ASSERT_DBG_PARAM(flashx != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(flashx));

  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(flashx);

  /*! <b>WARNING:</b> This function must not be modified, when the callback is needed, the
                      HAL_FLASH_ITF_OB_ProgramCpltCallback() could be implemented in the user file */
}

/**
  * @brief  FLASH ITF option bytes write error callback.
  */
__WEAK void HAL_FLASH_ITF_OB_ErrorCallback(FLASH_TypeDef *flashx)
{
  ASSERT_DBG_PARAM(flashx != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(flashx));

  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(flashx);

  /*! <b>WARNING:</b> This function must not be modified, when the callback is needed, the
                      HAL_FLASH_ITF_OB_ErrorCallback() could be implemented in the user file */
}

/**
  * @}
  */

/** @addtogroup FLASH_ITF_Exported_Functions_Group4
  * @{
This subsection provides a set of functions allowing to program the option-bytes functions configuration:

- Call the function FLASH_ITF_OB_Program() to program the FLASH option-bytes.
  */

/**
  * @brief  Program the FLASH ITF option-bytes.
  * @retval HAL_ERROR Generated when an error occurred.
  * @retval HAL_OK    No error occurred.
  */
hal_status_t HAL_FLASH_ITF_OB_Program(FLASH_TypeDef *flashx)
{
  ASSERT_DBG_PARAM(flashx != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(flashx));

  uint32_t tick_start;

  LL_FLASH_OB_StartModification(flashx);

  tick_start = HAL_GetTick();

  /* Wait for BSY flag to be cleared */
  while (LL_FLASH_IsActiveFlag_BSY(flashx) != 0U)
  {
    if ((HAL_GetTick() - tick_start) > FLASH_ITF_OB_TIMEOUT)
    {
      /* Timeout occurred while waiting for end of operation */
      return HAL_TIMEOUT;
    }
  }

  if (LL_FLASH_ReadFlag(flashx, LL_FLASH_FLAG_ERRORS_ALL) != 0U)
  {
    LL_FLASH_ClearFlag_OPTCHANGEERR(flashx);
    return HAL_ERROR;
  }

  return HAL_OK;
}

/**
  * @}
  */

/**
  * @}
  */

/** @addtogroup FLASH_Private_Functions FLASH Private Functions
  * @{
  */

static hal_status_t FLASH_ITF_IsValidHDPLTransition(hal_flash_itf_hdp_level_t current_hdpl,
                                                    hal_flash_itf_hdp_level_t hdpl)
{
  ASSERT_DBG_PARAM(IS_FLASH_ITF_HDPL_VALUE(current_hdpl));
  ASSERT_DBG_PARAM(IS_FLASH_ITF_HDPL_VALUE(hdpl));

  hal_status_t status = HAL_INVALID_PARAM;

  switch (current_hdpl)
  {
    case HAL_FLASH_ITF_HDP_LEVEL_1:
      if ((hdpl == HAL_FLASH_ITF_HDP_LEVEL_2) || (hdpl == HAL_FLASH_ITF_HDP_LEVEL_3))
      {
        status = HAL_OK;
      }
      break;

    case HAL_FLASH_ITF_HDP_LEVEL_2:
      if (hdpl == HAL_FLASH_ITF_HDP_LEVEL_3)
      {
        status = HAL_OK;
      }
      break;

    default:
      break;
  }

  return status;
}

static hal_flash_itf_hdp_level_t FLASH_ITF_GetNextHDPL(hal_flash_itf_hdp_level_t current_hdpl)
{
  ASSERT_DBG_PARAM(IS_FLASH_ITF_HDPL_VALUE(current_hdpl));
  ASSERT_DBG_PARAM(current_hdpl != HAL_FLASH_ITF_HDP_LEVEL_3);
  hal_flash_itf_hdp_level_t next_hdpl = HAL_FLASH_ITF_HDP_LEVEL_1;

  switch (current_hdpl)
  {
    case HAL_FLASH_ITF_HDP_LEVEL_1:
      next_hdpl = HAL_FLASH_ITF_HDP_LEVEL_2;
      break;

    case HAL_FLASH_ITF_HDP_LEVEL_2:
      next_hdpl = HAL_FLASH_ITF_HDP_LEVEL_3;
      break;

    default:
      break;
  }

  return next_hdpl;
}

/**
  * @brief  Wait for a FLASH operation to complete.
  * @retval HAL_ERROR    Timeout.
  * @retval HAL_OK       No operation to be waiting.
  */
static hal_status_t FLASH_ITF_OB_WaitForLastOperation(FLASH_TypeDef *flashx)
{
  uint32_t tick_start;

  tick_start = HAL_GetTick();

  /* Wait for BSY flag to be cleared and write/data buffers to be empty */
  while (LL_FLASH_IsActiveFlag(flashx, LL_FLASH_FLAG_STATUS_ALL) != 0U)
  {
    if ((HAL_GetTick() - tick_start) > FLASH_ITF_OB_TIMEOUT)
    {
      return HAL_ERROR;
    }
  }

  /* Clear all error flags */
  LL_FLASH_ClearFlag(flashx, LL_FLASH_FLAG_ERRORS_ALL);

  return HAL_OK;
}

/**
  * @}
  */

#endif /* USE_HAL_FLASH_ITF_MODULE */

/**
  * @}
  */

/**
  * @}
  */
