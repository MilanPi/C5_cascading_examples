/**
  **********************************************************************************************************************
  * @file    stm32c5xx_hal_flash_itf.h
  * @author  GPM Application Team
  * @brief   Header file of FLASH HAL module.
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

/* Define to prevent recursive inclusion -----------------------------------------------------------------------------*/
#ifndef STM32C5XX_HAL_ITF_H
#define STM32C5XX_HAL_ITF_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ----------------------------------------------------------------------------------------------------------*/
#include "stm32c5xx_hal_def.h"
#include "stm32c5xx_ll_flash.h"
#include "stm32c5xx_ll_sbs.h"

/** @addtogroup STM32C5xx_HAL_Driver
  * @{
  */

/* Exported Constants ------------------------------------------------------------------------------------------------*/
/** @defgroup FLASH_Exported_Constants FLASH Exported Constants
  * @{
  */
#define HAL_FLASH_ITF_OB_STOP_MODE     1U /*!< FLASH ITF option bytes stop mode     */
#define HAL_FLASH_ITF_OB_STANDBY_MODE  2U /*!< FLASH ITF option bytes standby mode  */

#define HAL_FLASH_ITF_OB_SRAM2         2U /*!< FLASH ITF option bytes SRAM2         */
#define HAL_FLASH_ITF_OB_SRAM1         8U /*!< FLASH ITF option bytes SRAM1         */


/** @defgroup HAL_FLASH_ITF_OB_Write_Protection_Pages FLASH OB Write Protection Pages
  * @{
  */
#if defined(STM32C5A3xx)
#define HAL_FLASH_ITF_OB_WRP_PAGE_0_1     LL_FLASH_OB_WRP_PAGE_0_1     /*!< Write protection of PAGE 0  and 1  */
#define HAL_FLASH_ITF_OB_WRP_PAGE_2_3     LL_FLASH_OB_WRP_PAGE_2_3     /*!< Write protection of PAGE 2  and 3  */
#define HAL_FLASH_ITF_OB_WRP_PAGE_4_5     LL_FLASH_OB_WRP_PAGE_4_5     /*!< Write protection of PAGE 4  and 5  */
#define HAL_FLASH_ITF_OB_WRP_PAGE_6_7     LL_FLASH_OB_WRP_PAGE_6_7     /*!< Write protection of PAGE 6  and 7  */
#define HAL_FLASH_ITF_OB_WRP_PAGE_8_9     LL_FLASH_OB_WRP_PAGE_8_9     /*!< Write protection of PAGE 8  and 9  */
#define HAL_FLASH_ITF_OB_WRP_PAGE_10_11   LL_FLASH_OB_WRP_PAGE_10_11   /*!< Write protection of PAGE 10 and 11 */
#define HAL_FLASH_ITF_OB_WRP_PAGE_12_13   LL_FLASH_OB_WRP_PAGE_12_13   /*!< Write protection of PAGE 12 and 13 */
#define HAL_FLASH_ITF_OB_WRP_PAGE_14_15   LL_FLASH_OB_WRP_PAGE_14_15   /*!< Write protection of PAGE 14 and 15 */
#define HAL_FLASH_ITF_OB_WRP_PAGE_16_17   LL_FLASH_OB_WRP_PAGE_16_17   /*!< Write protection of PAGE 16 and 17 */
#define HAL_FLASH_ITF_OB_WRP_PAGE_18_19   LL_FLASH_OB_WRP_PAGE_18_19   /*!< Write protection of PAGE 18 and 19 */
#define HAL_FLASH_ITF_OB_WRP_PAGE_20_21   LL_FLASH_OB_WRP_PAGE_20_21   /*!< Write protection of PAGE 20 and 21 */
#define HAL_FLASH_ITF_OB_WRP_PAGE_22_23   LL_FLASH_OB_WRP_PAGE_22_23   /*!< Write protection of PAGE 22 and 23 */
#define HAL_FLASH_ITF_OB_WRP_PAGE_24_25   LL_FLASH_OB_WRP_PAGE_24_25   /*!< Write protection of PAGE 24 and 25 */
#define HAL_FLASH_ITF_OB_WRP_PAGE_26_27   LL_FLASH_OB_WRP_PAGE_26_27   /*!< Write protection of PAGE 26 and 27 */
#define HAL_FLASH_ITF_OB_WRP_PAGE_28_29   LL_FLASH_OB_WRP_PAGE_28_29   /*!< Write protection of PAGE 28 and 29 */
#define HAL_FLASH_ITF_OB_WRP_PAGE_30_31   LL_FLASH_OB_WRP_PAGE_30_31   /*!< Write protection of PAGE 30 and 31 */
#define HAL_FLASH_ITF_OB_WRP_PAGE_32_33   LL_FLASH_OB_WRP_PAGE_32_33   /*!< Write protection of PAGE 32 and 33 */
#define HAL_FLASH_ITF_OB_WRP_PAGE_34_35   LL_FLASH_OB_WRP_PAGE_34_35   /*!< Write protection of PAGE 34 and 35 */
#define HAL_FLASH_ITF_OB_WRP_PAGE_36_37   LL_FLASH_OB_WRP_PAGE_36_37   /*!< Write protection of PAGE 36 and 37 */
#define HAL_FLASH_ITF_OB_WRP_PAGE_38_39   LL_FLASH_OB_WRP_PAGE_38_39   /*!< Write protection of PAGE 38 and 39 */
#define HAL_FLASH_ITF_OB_WRP_PAGE_40_41   LL_FLASH_OB_WRP_PAGE_40_41   /*!< Write protection of PAGE 40 and 41 */
#define HAL_FLASH_ITF_OB_WRP_PAGE_42_43   LL_FLASH_OB_WRP_PAGE_42_43   /*!< Write protection of PAGE 42 and 43 */
#define HAL_FLASH_ITF_OB_WRP_PAGE_44_45   LL_FLASH_OB_WRP_PAGE_44_45   /*!< Write protection of PAGE 44 and 45 */
#define HAL_FLASH_ITF_OB_WRP_PAGE_46_47   LL_FLASH_OB_WRP_PAGE_46_47   /*!< Write protection of PAGE 46 and 47 */
#define HAL_FLASH_ITF_OB_WRP_PAGE_48_49   LL_FLASH_OB_WRP_PAGE_48_49   /*!< Write protection of PAGE 48 and 49 */
#define HAL_FLASH_ITF_OB_WRP_PAGE_50_51   LL_FLASH_OB_WRP_PAGE_50_51   /*!< Write protection of PAGE 50 and 51 */
#define HAL_FLASH_ITF_OB_WRP_PAGE_52_53   LL_FLASH_OB_WRP_PAGE_52_53   /*!< Write protection of PAGE 52 and 53 */
#define HAL_FLASH_ITF_OB_WRP_PAGE_54_55   LL_FLASH_OB_WRP_PAGE_54_55   /*!< Write protection of PAGE 54 and 55 */
#define HAL_FLASH_ITF_OB_WRP_PAGE_56_57   LL_FLASH_OB_WRP_PAGE_56_57   /*!< Write protection of PAGE 56 and 57 */
#define HAL_FLASH_ITF_OB_WRP_PAGE_58_59   LL_FLASH_OB_WRP_PAGE_58_59   /*!< Write protection of PAGE 58 and 59 */
#define HAL_FLASH_ITF_OB_WRP_PAGE_60_61   LL_FLASH_OB_WRP_PAGE_60_61   /*!< Write protection of PAGE 60 and 61 */
#define HAL_FLASH_ITF_OB_WRP_PAGE_62_63   LL_FLASH_OB_WRP_PAGE_62_63   /*!< Write protection of PAGE 62 and 63 */
#define HAL_FLASH_ITF_OB_WRP_PAGE_ALL     LL_FLASH_OB_WRP_PAGE_ALL       /*!< Write protection of all PAGEs */
#else
#define HAL_FLASH_ITF_OB_WRP_PAGE_0      LL_FLASH_OB_WRP_PAGE_0        /*!< Write protection of PAGE0     */
#define HAL_FLASH_ITF_OB_WRP_PAGE_1      LL_FLASH_OB_WRP_PAGE_1        /*!< Write protection of PAGE1     */
#define HAL_FLASH_ITF_OB_WRP_PAGE_2      LL_FLASH_OB_WRP_PAGE_2        /*!< Write protection of PAGE2     */
#define HAL_FLASH_ITF_OB_WRP_PAGE_3      LL_FLASH_OB_WRP_PAGE_3        /*!< Write protection of PAGE3     */
#define HAL_FLASH_ITF_OB_WRP_PAGE_4      LL_FLASH_OB_WRP_PAGE_4        /*!< Write protection of PAGE4     */
#define HAL_FLASH_ITF_OB_WRP_PAGE_5      LL_FLASH_OB_WRP_PAGE_5        /*!< Write protection of PAGE5     */
#define HAL_FLASH_ITF_OB_WRP_PAGE_6      LL_FLASH_OB_WRP_PAGE_6        /*!< Write protection of PAGE6     */
#define HAL_FLASH_ITF_OB_WRP_PAGE_7      LL_FLASH_OB_WRP_PAGE_7        /*!< Write protection of PAGE7     */
#define HAL_FLASH_ITF_OB_WRP_PAGE_8      LL_FLASH_OB_WRP_PAGE_8        /*!< Write protection of PAGE8     */
#define HAL_FLASH_ITF_OB_WRP_PAGE_9      LL_FLASH_OB_WRP_PAGE_9        /*!< Write protection of PAGE9     */
#define HAL_FLASH_ITF_OB_WRP_PAGE_10     LL_FLASH_OB_WRP_PAGE_10       /*!< Write protection of PAGE10    */
#define HAL_FLASH_ITF_OB_WRP_PAGE_11     LL_FLASH_OB_WRP_PAGE_11       /*!< Write protection of PAGE11    */
#define HAL_FLASH_ITF_OB_WRP_PAGE_12     LL_FLASH_OB_WRP_PAGE_12       /*!< Write protection of PAGE12    */
#define HAL_FLASH_ITF_OB_WRP_PAGE_13     LL_FLASH_OB_WRP_PAGE_13       /*!< Write protection of PAGE13    */
#define HAL_FLASH_ITF_OB_WRP_PAGE_14     LL_FLASH_OB_WRP_PAGE_14       /*!< Write protection of PAGE14    */
#define HAL_FLASH_ITF_OB_WRP_PAGE_15     LL_FLASH_OB_WRP_PAGE_15       /*!< Write protection of PAGE15    */
#define HAL_FLASH_ITF_OB_WRP_PAGE_16     LL_FLASH_OB_WRP_PAGE_16       /*!< Write protection of PAGE16    */
#define HAL_FLASH_ITF_OB_WRP_PAGE_17     LL_FLASH_OB_WRP_PAGE_17       /*!< Write protection of PAGE17    */
#define HAL_FLASH_ITF_OB_WRP_PAGE_18     LL_FLASH_OB_WRP_PAGE_18       /*!< Write protection of PAGE18    */
#define HAL_FLASH_ITF_OB_WRP_PAGE_19     LL_FLASH_OB_WRP_PAGE_19       /*!< Write protection of PAGE19    */
#define HAL_FLASH_ITF_OB_WRP_PAGE_20     LL_FLASH_OB_WRP_PAGE_20       /*!< Write protection of PAGE20    */
#define HAL_FLASH_ITF_OB_WRP_PAGE_21     LL_FLASH_OB_WRP_PAGE_21       /*!< Write protection of PAGE21    */
#define HAL_FLASH_ITF_OB_WRP_PAGE_22     LL_FLASH_OB_WRP_PAGE_22       /*!< Write protection of PAGE22    */
#define HAL_FLASH_ITF_OB_WRP_PAGE_23     LL_FLASH_OB_WRP_PAGE_23       /*!< Write protection of PAGE23    */
#define HAL_FLASH_ITF_OB_WRP_PAGE_24     LL_FLASH_OB_WRP_PAGE_24       /*!< Write protection of PAGE24    */
#define HAL_FLASH_ITF_OB_WRP_PAGE_25     LL_FLASH_OB_WRP_PAGE_25       /*!< Write protection of PAGE25    */
#define HAL_FLASH_ITF_OB_WRP_PAGE_26     LL_FLASH_OB_WRP_PAGE_26       /*!< Write protection of PAGE26    */
#define HAL_FLASH_ITF_OB_WRP_PAGE_27     LL_FLASH_OB_WRP_PAGE_27       /*!< Write protection of PAGE27    */
#define HAL_FLASH_ITF_OB_WRP_PAGE_28     LL_FLASH_OB_WRP_PAGE_28       /*!< Write protection of PAGE28    */
#define HAL_FLASH_ITF_OB_WRP_PAGE_29     LL_FLASH_OB_WRP_PAGE_29       /*!< Write protection of PAGE29    */
#define HAL_FLASH_ITF_OB_WRP_PAGE_30     LL_FLASH_OB_WRP_PAGE_30       /*!< Write protection of PAGE30    */
#define HAL_FLASH_ITF_OB_WRP_PAGE_31     LL_FLASH_OB_WRP_PAGE_31       /*!< Write protection of PAGE31    */
#define HAL_FLASH_ITF_OB_WRP_PAGE_ALL    LL_FLASH_OB_WRP_PAGE_ALL      /*!< Write protection of all PAGEs */
#endif

/**
  * @}
  */

/** @defgroup HAL_FLASH_ITF_OB_OTP_Lock_Blocks FLASH OTP Lock Blocks
  * @{
  */
#define HAL_FLASH_ITF_OB_OTP_BLK_0        LL_FLASH_OB_OTP_BLK_0    /*!< OTP Lock Block0      */
#define HAL_FLASH_ITF_OB_OTP_BLK_1        LL_FLASH_OB_OTP_BLK_1    /*!< OTP Lock Block1      */
#define HAL_FLASH_ITF_OB_OTP_BLK_2        LL_FLASH_OB_OTP_BLK_2    /*!< OTP Lock Block2      */
#define HAL_FLASH_ITF_OB_OTP_BLK_3        LL_FLASH_OB_OTP_BLK_3    /*!< OTP Lock Block3      */
#define HAL_FLASH_ITF_OB_OTP_BLK_4        LL_FLASH_OB_OTP_BLK_4    /*!< OTP Lock Block4      */
#define HAL_FLASH_ITF_OB_OTP_BLK_5        LL_FLASH_OB_OTP_BLK_5    /*!< OTP Lock Block5      */
#define HAL_FLASH_ITF_OB_OTP_BLK_6        LL_FLASH_OB_OTP_BLK_6    /*!< OTP Lock Block6      */
#define HAL_FLASH_ITF_OB_OTP_BLK_7        LL_FLASH_OB_OTP_BLK_7    /*!< OTP Lock Block7      */
#define HAL_FLASH_ITF_OB_OTP_BLK_8        LL_FLASH_OB_OTP_BLK_8    /*!< OTP Lock Block8      */
#define HAL_FLASH_ITF_OB_OTP_BLK_9        LL_FLASH_OB_OTP_BLK_9    /*!< OTP Lock Block9      */
#define HAL_FLASH_ITF_OB_OTP_BLK_10       LL_FLASH_OB_OTP_BLK_10   /*!< OTP Lock Block10     */
#define HAL_FLASH_ITF_OB_OTP_BLK_11       LL_FLASH_OB_OTP_BLK_11   /*!< OTP Lock Block11     */
#define HAL_FLASH_ITF_OB_OTP_BLK_12       LL_FLASH_OB_OTP_BLK_12   /*!< OTP Lock Block12     */
#define HAL_FLASH_ITF_OB_OTP_BLK_13       LL_FLASH_OB_OTP_BLK_13   /*!< OTP Lock Block13     */
#define HAL_FLASH_ITF_OB_OTP_BLK_14       LL_FLASH_OB_OTP_BLK_14   /*!< OTP Lock Block14     */
#define HAL_FLASH_ITF_OB_OTP_BLK_15       LL_FLASH_OB_OTP_BLK_15   /*!< OTP Lock Block15     */
#define HAL_FLASH_ITF_OB_OTP_BLK_16       LL_FLASH_OB_OTP_BLK_16   /*!< OTP Lock Block16     */
#define HAL_FLASH_ITF_OB_OTP_BLK_17       LL_FLASH_OB_OTP_BLK_17   /*!< OTP Lock Block17     */
#define HAL_FLASH_ITF_OB_OTP_BLK_18       LL_FLASH_OB_OTP_BLK_18   /*!< OTP Lock Block18     */
#define HAL_FLASH_ITF_OB_OTP_BLK_19       LL_FLASH_OB_OTP_BLK_19   /*!< OTP Lock Block19     */
#define HAL_FLASH_ITF_OB_OTP_BLK_20       LL_FLASH_OB_OTP_BLK_20   /*!< OTP Lock Block20     */
#define HAL_FLASH_ITF_OB_OTP_BLK_21       LL_FLASH_OB_OTP_BLK_21   /*!< OTP Lock Block21     */
#define HAL_FLASH_ITF_OB_OTP_BLK_22       LL_FLASH_OB_OTP_BLK_22   /*!< OTP Lock Block22     */
#define HAL_FLASH_ITF_OB_OTP_BLK_23       LL_FLASH_OB_OTP_BLK_23   /*!< OTP Lock Block23     */
#define HAL_FLASH_ITF_OB_OTP_BLK_24       LL_FLASH_OB_OTP_BLK_24   /*!< OTP Lock Block24     */
#define HAL_FLASH_ITF_OB_OTP_BLK_25       LL_FLASH_OB_OTP_BLK_25   /*!< OTP Lock Block25     */
#define HAL_FLASH_ITF_OB_OTP_BLK_26       LL_FLASH_OB_OTP_BLK_26   /*!< OTP Lock Block26     */
#define HAL_FLASH_ITF_OB_OTP_BLK_27       LL_FLASH_OB_OTP_BLK_27   /*!< OTP Lock Block27     */
#define HAL_FLASH_ITF_OB_OTP_BLK_28       LL_FLASH_OB_OTP_BLK_28   /*!< OTP Lock Block28     */
#define HAL_FLASH_ITF_OB_OTP_BLK_29       LL_FLASH_OB_OTP_BLK_29   /*!< OTP Lock Block29     */
#define HAL_FLASH_ITF_OB_OTP_BLK_30       LL_FLASH_OB_OTP_BLK_30   /*!< OTP Lock Block30     */
#define HAL_FLASH_ITF_OB_OTP_BLK_31       LL_FLASH_OB_OTP_BLK_31   /*!< OTP Lock Block31     */
#define HAL_FLASH_ITF_OB_OTP_BLK_ALL      LL_FLASH_OB_OTP_BLK_ALL  /*!< OTP Lock All Blocks  */
/**
  * @}
  */

/** @defgroup FLASH_ITF FLASH_ITF
  * @{
  */

/* Exported types ----------------------------------------------------------------------------------------------------*/
/** @defgroup FLASH_ITF_Exported_Types FLASH_ITF Exported Types
  * @{
  */

/*! HAL FLASH ITF lock status enumeration definition */
typedef enum
{
  HAL_FLASH_ITF_UNLOCKED = 0U, /*!< FLASH unlocked */
  HAL_FLASH_ITF_LOCKED   = 1U  /*!< FLASH locked   */
} hal_flash_itf_lock_status_t;

/*! HAL FLASH ITF option-bytes bank enumeration definition */
typedef enum
{
  HAL_FLASH_ITF_BANK_1 = LL_FLASH_BANK_1, /*!< FLASH ITF option-bytes Bank 1 */
  HAL_FLASH_ITF_BANK_2 = LL_FLASH_BANK_2  /*!< FLASH ITF option-bytes Bank 1 */
} hal_flash_itf_bank_t;

/*! HAL FLASH latency enumeration definition */
typedef enum
{
  HAL_FLASH_ITF_LATENCY_0  = LL_FLASH_LATENCY_0WS,  /*!< FLASH zero wait state      */
  HAL_FLASH_ITF_LATENCY_1  = LL_FLASH_LATENCY_1WS,  /*!< FLASH one wait state       */
  HAL_FLASH_ITF_LATENCY_2  = LL_FLASH_LATENCY_2WS,  /*!< FLASH two wait states      */
  HAL_FLASH_ITF_LATENCY_3  = LL_FLASH_LATENCY_3WS,  /*!< FLASH three wait states    */
  HAL_FLASH_ITF_LATENCY_4  = LL_FLASH_LATENCY_4WS,  /*!< FLASH four wait states     */
  HAL_FLASH_ITF_LATENCY_5  = LL_FLASH_LATENCY_5WS,  /*!< FLASH five wait states     */
  HAL_FLASH_ITF_LATENCY_6  = LL_FLASH_LATENCY_6WS,  /*!< FLASH six wait states      */
  HAL_FLASH_ITF_LATENCY_7  = LL_FLASH_LATENCY_7WS,  /*!< FLASH seven wait states    */
  HAL_FLASH_ITF_LATENCY_8  = LL_FLASH_LATENCY_8WS,  /*!< FLASH eight wait states    */
  HAL_FLASH_ITF_LATENCY_9  = LL_FLASH_LATENCY_9WS,  /*!< FLASH nine wait states     */
  HAL_FLASH_ITF_LATENCY_10 = LL_FLASH_LATENCY_10WS, /*!< FLASH ten wait states      */
  HAL_FLASH_ITF_LATENCY_11 = LL_FLASH_LATENCY_11WS, /*!< FLASH eleven wait states   */
  HAL_FLASH_ITF_LATENCY_12 = LL_FLASH_LATENCY_12WS, /*!< FLASH twelve wait states   */
  HAL_FLASH_ITF_LATENCY_13 = LL_FLASH_LATENCY_13WS, /*!< FLASH thirteen wait states */
  HAL_FLASH_ITF_LATENCY_14 = LL_FLASH_LATENCY_14WS, /*!< FLASH fourteen wait states */
  HAL_FLASH_ITF_LATENCY_15 = LL_FLASH_LATENCY_15WS  /*!< FLASH fifteen wait states  */
} hal_flash_itf_latency_t;

/*! HAL FLASH programming delay enumeration definition */
typedef enum
{
  HAL_FLASH_ITF_PROGRAM_DELAY_0  = LL_FLASH_PROGRAM_DELAY_0,  /*!< FLASH 0 programming delay */
  HAL_FLASH_ITF_PROGRAM_DELAY_1  = LL_FLASH_PROGRAM_DELAY_1,  /*!< FLASH 1 programming delay */
  HAL_FLASH_ITF_PROGRAM_DELAY_2  = LL_FLASH_PROGRAM_DELAY_2,  /*!< FLASH 2 programming delay */
} hal_flash_itf_program_delay_t;

/*! HAL FLASH Prefetch enumeration definition */
typedef enum
{
  HAL_FLASH_ITF_PREFETCH_DISABLED  = 0x00U, /*!< FLASH prefetch disabled */
  HAL_FLASH_ITF_PREFETCH_ENABLED   = 0x01U  /*!< FLASH prefetch enabled  */
} hal_flash_itf_prefetch_status_t;

typedef enum
{
  HAL_FLASH_ITF_BOOT_LOCATION_PROGRAMMED  = LL_FLASH_BOOT_LOCATION_PROGRAMMED, /*!< FLASH boot location programmed */
  HAL_FLASH_ITF_BOOT_LOCATION_EMPTY       = LL_FLASH_BOOT_LOCATION_EMPTY       /*!< FLASH boot location empty      */
} hal_flash_itf_empty_boot_location_t;

/*! HAL FLASH ITF RDP key lock status enumeration definition */
typedef enum
{
  HAL_FLASH_ITF_RDP_KEY_UNLOCKED = 0U, /*!< FLASH ITF option bytes RDP key unlocked */
  HAL_FLASH_ITF_RDP_KEY_LOCKED   = 1U  /*!< FLASH ITF option bytes RDP key locked   */
} hal_flash_itf_rdp_key_lock_status_t;

/*! HAL FLASH ITF hide protection level value enumeration definition */
typedef enum
{
  HAL_FLASH_ITF_HDP_LEVEL_1 = LL_SBS_HDPL_VALUE_1,  /*!< Hide protection level 1 */
  HAL_FLASH_ITF_HDP_LEVEL_2 = LL_SBS_HDPL_VALUE_2,  /*!< Hide protection level 2 */
  HAL_FLASH_ITF_HDP_LEVEL_3 = LL_SBS_HDPL_VALUE_3,  /*!< Hide protection level 3 */
} hal_flash_itf_hdp_level_t;


/*! HAL FLASH ITF option-bytes lock status enumeration definition */
typedef enum
{
  HAL_FLASH_ITF_OB_UNLOCKED = 0U, /*!< FLASH ITF option-bytes unlocked */
  HAL_FLASH_ITF_OB_LOCKED   = 1U  /*!< FLASH ITF option-bytes locked   */
} hal_flash_itf_ob_lock_status_t;

/*! HAL FLASH ITF option-bytes OTP block lock status enumeration definition */
typedef enum
{
  HAL_FLASH_ITF_OB_OTP_BLK_UNLOCKED = 0U, /*!< FLASH ITF option bytes otp block unlocked */
  HAL_FLASH_ITF_OB_OTP_BLK_LOCKED   = 1U  /*!< FLASH ITF option bytes otp block locked   */
} hal_flash_itf_ob_otp_blk_lock_status_t;

/*! HAL FLASH ITF option-bytes WRP page status enumeration definition */
typedef enum
{
  HAL_FLASH_ITF_OB_WRP_PAGE_NOT_PROTECTED = 0U, /*!< FLASH ITF option bytes not write protected page */
  HAL_FLASH_ITF_OB_WRP_PAGE_PROTECTED     = 1U  /*!< FLASH ITF option bytes write protected page     */
} hal_flash_itf_ob_wrp_page_status_t;

/*! HAL FLASH ITF option-bytes EDATA area status enumeration definition */
typedef enum
{
  HAL_FLASH_ITF_OB_EDATA_AREA_DISABLED = 0U, /*!< FLASH ITF option-bytes EDATA area disabled */
  HAL_FLASH_ITF_OB_EDATA_AREA_ENABLED  = 1U  /*!< FLASH ITF option-bytes EDATA area enabled  */
} hal_flash_itf_ob_edata_area_status_t;

/*! HAL FLASH ITF option-bytes Read-out Protection level enumeration definition */
typedef enum
{
  HAL_FLASH_ITF_OB_RDP_LEVEL_0     = LL_FLASH_OB_RDP_LEVEL_0,     /*!< FLASH ITF OB RDP Level 0                    */
  HAL_FLASH_ITF_OB_RDP_LEVEL_2_WBS = LL_FLASH_OB_RDP_LEVEL_2_WBS, /*!< FLASH ITF OB RDP Level 2 with Boundary Scan */
  HAL_FLASH_ITF_OB_RDP_LEVEL_2     = LL_FLASH_OB_RDP_LEVEL_2,     /*!< FLASH ITF OB RDP Level 2                    */
} hal_flash_itf_ob_rdp_level_t;

/*! HAL FLASH ITF option bytes reset generation when enter in low power mode enumeration definition */
typedef enum
{
  HAL_FLASH_ITF_OB_RST_GENERATION    = 0U, /*!< FLASH ITF OB reset generation when enter in low power mode    */
  HAL_FLASH_ITF_OB_NO_RST_GENERATION = 1U  /*!< FLASH ITF OB no reset generation when enter in low power mode */
} hal_flash_itf_ob_rst_generation_status_t ;

/*! HAL FLASH ITF option bytes Erased sram when system reset enumeration definition */
typedef enum
{
  HAL_FLASH_ITF_OB_SYS_RST_SRAM_ERASE    = 0U, /*!< FLASH ITF option bytes Erased SRAM when system reset occurs    */
  HAL_FLASH_ITF_OB_SYS_RST_SRAM_NO_ERASE = 1U  /*!< FLASH ITF option bytes No erased SRAM when system reset occurs */
} hal_flash_itf_ob_sys_rst_sram_erase_t;

/*! HAL FLASH ITF option-bytes IWDG hardware/software mode enumeration definition */
typedef enum
{
  HAL_FLASH_ITF_OB_WDG_HARDWARE = 0U,  /*!< FLASH ITF option-bytes WDG hardware select */
  HAL_FLASH_ITF_OB_WDG_SOFTWARE = 1U   /*!< FLASH ITF option-bytes WDG software select */
} hal_flash_itf_ob_wdg_mode_t;

/*! HAL FLASH ITF option-bytes IWDG stop counter freeze enumeration definition */
typedef enum
{
  HAL_FLASH_ITF_OB_WDG_FROZEN   = 1U, /*!< FLASH ITF option-bytes IWDG counter low-power mode frozen  */
  HAL_FLASH_ITF_OB_WDG_UNFROZEN = 0U  /*!< FLASH ITF option-bytes IWDG counter low-power mode running */
} hal_flash_itf_ob_wdg_freeze_status_t;

/*! HAL FLASH ITF option bytes  BOOT0 source selection enumeration definition */
typedef enum
{
  HAL_FLASH_ITF_OB_BOOT_OPTION_BIT = LL_FLASH_OB_BOOT0_BOOT0,  /*!< FLASH ITF option bytes BOOT taken from option-bit */
  HAL_FLASH_ITF_OB_BOOT_PIN        = LL_FLASH_OB_BOOT0_BOOTPIN /*!< FLASH ITF option bytes BOOT taken from boot pin   */
} hal_flash_itf_ob_boot_selection_t;

/*! HAL FLASH ITF option bytes software BOOT0 enumeration definition */
typedef enum
{
  HAL_FLASH_ITF_OB_BOOT_LOW  = LL_FLASH_OB_BOOT0_DISABLED, /*!< FLASH ITF option bytes BOOT option-bit low state  */
  HAL_FLASH_ITF_OB_BOOT_HIGH = LL_FLASH_OB_BOOT0_ENABLED,  /*!< FLASH ITF option bytes BOOT option-bit high state */
} hal_flash_itf_ob_boot_state_t;


/*! HAL FLASH ITF option bytes Single/Dual bank enumeration definition */
typedef enum
{
  HAL_FLASH_ITF_OB_SINGLE_BANK = LL_FLASH_OB_SINGLE_BANK, /*!< FLASH ITF option bytes Single bank */
  HAL_FLASH_ITF_OB_DUAL_BANK   = LL_FLASH_OB_DUAL_BANK    /*!< FLASH ITF option bytes Dual bank   */
} hal_flash_itf_ob_topology_t;

/*! HAL FLASH ITF option-bytes Swapping bank enumeration definition */
typedef enum
{
  HAL_FLASH_ITF_OB_BANK_NO_SWAP = LL_FLASH_OB_BANK_NOT_SWAPPED, /*!< FLASH ITF option-bytes Bank not swapped */
  HAL_FLASH_ITF_OB_BANK_SWAP    = LL_FLASH_OB_BANK_SWAPPED      /*!< FLASH ITF option-bytes Bank swapped     */
} hal_flash_itf_ob_bank_swap_t;

/*! HAL FLASH ITF option bytes SRAM ECC enumeration definition */
typedef enum
{
  HAL_FLASH_ITF_OB_SRAM_ECC_DISABLED = 0U, /*!< FLASH ITF option bytes SRAM ECC disable */
  HAL_FLASH_ITF_OB_SRAM_ECC_ENABLED  = 1U  /*!< FLASH ITF option bytes SRAM ECC enable  */
} hal_flash_itf_ob_sram_ecc_status_t ;

/*! HAL FLASH ITF option-bytes boot lock status enumeration definition */
typedef enum
{
  HAL_FLASH_ITF_OB_BOOT_UNLOCKED = 0U, /*!< FLASH ITF option bytes boot unlocked */
  HAL_FLASH_ITF_OB_BOOT_LOCKED   = 1U  /*!< FLASH ITF option bytes boot locked   */
} hal_flash_itf_ob_boot_lock_status_t;

/*! HAL FLASH ITF option-bytes read-out protection OEM key structure definition */
typedef struct
{
  uint32_t key_w1; /*!< FLASH ITF RDP OEM key word 1 */
  uint32_t key_w2; /*!< FLASH ITF RDP OEM key word 2 */
  uint32_t key_w3; /*!< FLASH ITF RDP OEM key word 3 */
  uint32_t key_w4; /*!< FLASH ITF RDP OEM key word 4 */
} hal_flash_itf_ob_rdp_oem_key_t;

/*! HAL FLASH ITF option-bytes read-out protection BS key structure definition */
typedef struct
{
  uint32_t key_w1; /*!< FLASH ITF RDP BS key word 1 */
} hal_flash_itf_ob_rdp_bs_key_t;

/**
  * @}
  */

/* Exported functions ------------------------------------------------------------------------------------------------*/
/** @defgroup FLASH_OB_Exported_Functions FLASH OB Exported Functions
  * @{
  */

/** @defgroup FLASH_ITF_Exported_Functions_Group1 FLASH ITF Control and Lock/Unlock functions
  * @{
  */

hal_status_t HAL_FLASH_ITF_Lock(FLASH_TypeDef *flashx);
hal_status_t HAL_FLASH_ITF_Unlock(FLASH_TypeDef *flashx);
hal_flash_itf_lock_status_t HAL_FLASH_ITF_IsLocked(const FLASH_TypeDef *flashx);

hal_status_t HAL_FLASH_ITF_SetLatency(FLASH_TypeDef *flashx, hal_flash_itf_latency_t latency);
hal_flash_itf_latency_t HAL_FLASH_ITF_GetLatency(const FLASH_TypeDef *flashx);

hal_status_t HAL_FLASH_ITF_SetProgrammingDelay(FLASH_TypeDef *flashx, hal_flash_itf_program_delay_t prog_delay);
hal_flash_itf_program_delay_t HAL_FLASH_ITF_GetProgrammingDelay(const FLASH_TypeDef *flashx);

hal_status_t HAL_FLASH_ITF_EnablePrefetch(FLASH_TypeDef *flashx);
hal_status_t HAL_FLASH_ITF_DisablePrefetch(FLASH_TypeDef *flashx);
hal_flash_itf_prefetch_status_t HAL_FLASH_ITF_IsEnabledPrefetch(const FLASH_TypeDef *flashx);

hal_status_t HAL_FLASH_ITF_SetEmptyBootLocation(FLASH_TypeDef *flashx, hal_flash_itf_empty_boot_location_t empty_boot);
hal_flash_itf_empty_boot_location_t HAL_FLASH_ITF_GetEmptyBootLocation(const FLASH_TypeDef *flashx);

hal_status_t HAL_FLASH_ITF_SetHDPExtArea(FLASH_TypeDef *flashx, hal_flash_itf_bank_t bank, uint32_t page_nbr);
uint32_t HAL_FLASH_ITF_GetHDPExtArea(const FLASH_TypeDef *flashx, hal_flash_itf_bank_t bank);

hal_status_t HAL_FLASH_ITF_SetHDPLevel(const FLASH_TypeDef *flashx, hal_flash_itf_hdp_level_t hdp_level);
hal_flash_itf_hdp_level_t HAL_FLASH_ITF_GetHDPLevel(const FLASH_TypeDef *flashx);

hal_flash_itf_rdp_key_lock_status_t HAL_FLASH_ITF_IsLockedRDPOEMKey(const FLASH_TypeDef *flashx);
hal_flash_itf_rdp_key_lock_status_t HAL_FLASH_ITF_IsLockedRDPBSKey(const FLASH_TypeDef *flashx);

#if defined (USE_HAL_FLASH_ITF_ECC) && (USE_HAL_FLASH_ITF_ECC == 1U)
hal_status_t HAL_FLASH_ITF_ECC_EnableIT(FLASH_TypeDef *flashx);
hal_status_t HAL_FLASH_ITF_ECC_DisableIT(FLASH_TypeDef *flashx);
#endif /* USE_HAL_FLASH_ITF_ECC */

/**
  * @}
  */

/** @defgroup FLASH_ITF_Exported_Functions_Group2 FLASH ITF Option-bytes configuration functions
  * @{
  */
hal_status_t HAL_FLASH_ITF_OB_Lock(FLASH_TypeDef *flashx);
hal_status_t HAL_FLASH_ITF_OB_Unlock(FLASH_TypeDef *flashx);
hal_flash_itf_ob_lock_status_t HAL_FLASH_ITF_OB_IsLocked(const FLASH_TypeDef *flashx);

hal_status_t HAL_FLASH_ITF_OB_LockOTPBlock(FLASH_TypeDef *flashx, uint32_t blocks);
hal_flash_itf_ob_otp_blk_lock_status_t HAL_FLASH_ITF_OB_IsLockedOTPBlock(const FLASH_TypeDef *flashx, uint32_t block);

hal_status_t HAL_FLASH_ITF_OB_EnablePageWRP(FLASH_TypeDef *flashx, hal_flash_itf_bank_t bank, uint32_t pages);
hal_status_t HAL_FLASH_ITF_OB_DisablePageWRP(FLASH_TypeDef *flashx, hal_flash_itf_bank_t bank, uint32_t pages);
hal_flash_itf_ob_wrp_page_status_t HAL_FLASH_ITF_OB_IsEnabledPageWRP(const FLASH_TypeDef *flashx,
                                                                     hal_flash_itf_bank_t bank,
                                                                     uint32_t page);

hal_status_t HAL_FLASH_ITF_OB_SetHDPArea(FLASH_TypeDef *flashx,
                                         hal_flash_itf_bank_t bank,
                                         uint32_t start_page,
                                         uint32_t page_nbr);
void HAL_FLASH_ITF_OB_GetHDPArea(const FLASH_TypeDef *flashx,
                                 hal_flash_itf_bank_t bank,
                                 uint32_t *p_start_page,
                                 uint32_t *p_page_nbr);

hal_status_t HAL_FLASH_ITF_OB_EnableEDATAArea(FLASH_TypeDef *flashx);
hal_status_t HAL_FLASH_ITF_OB_DisableEDATAArea(FLASH_TypeDef *flashx);
hal_flash_itf_ob_edata_area_status_t HAL_FLASH_ITF_OB_IsEnabledEDATAArea(const FLASH_TypeDef *flashx);

hal_status_t HAL_FLASH_ITF_OB_SetRDPLevel(FLASH_TypeDef *flashx, hal_flash_itf_ob_rdp_level_t rdp_level);
hal_flash_itf_ob_rdp_level_t HAL_FLASH_ITF_OB_GetRDPLevel(const FLASH_TypeDef *flashx);

hal_status_t HAL_FLASH_ITF_OB_SetRDPOEMKey(FLASH_TypeDef *flashx, const hal_flash_itf_ob_rdp_oem_key_t *p_key);
hal_status_t HAL_FLASH_ITF_OB_SetRDPBSKey(FLASH_TypeDef *flashx, const hal_flash_itf_ob_rdp_bs_key_t *p_key);

hal_status_t HAL_FLASH_ITF_OB_SetEnterLowPWRModeRstGeneration(FLASH_TypeDef *flashx, uint32_t low_pwr_mode,
                                                              hal_flash_itf_ob_rst_generation_status_t rst_gen);
hal_flash_itf_ob_rst_generation_status_t HAL_FLASH_ITF_OB_GetEnterLowPWRModeRstGeneration(const FLASH_TypeDef *flashx,
    uint32_t low_pwr_mode);

hal_status_t HAL_FLASH_ITF_OB_SetSystemRstSRAMErase(FLASH_TypeDef *flashx,
                                                    uint32_t sram,
                                                    hal_flash_itf_ob_sys_rst_sram_erase_t sram_erase);
hal_flash_itf_ob_sys_rst_sram_erase_t HAL_FLASH_ITF_OB_GetSystemRstSRAMErase(const FLASH_TypeDef *flashx,
                                                                             uint32_t sram);

hal_status_t HAL_FLASH_ITF_OB_SetIWDGMode(FLASH_TypeDef *flashx, hal_flash_itf_ob_wdg_mode_t mode);
hal_flash_itf_ob_wdg_mode_t HAL_FLASH_ITF_OB_GetIWDGMode(const FLASH_TypeDef *flashx);

hal_status_t HAL_FLASH_ITF_OB_SetWWDGMode(FLASH_TypeDef *flashx, hal_flash_itf_ob_wdg_mode_t mode);
hal_flash_itf_ob_wdg_mode_t HAL_FLASH_ITF_OB_GetWWDGMode(const FLASH_TypeDef *flashx);

hal_status_t HAL_FLASH_ITF_OB_FreezeIWDGCounterLowPWRMode(FLASH_TypeDef *flashx, uint32_t mode);
hal_status_t HAL_FLASH_ITF_OB_UnfreezeIWDGCounterLowPWRMode(FLASH_TypeDef *flashx, uint32_t mode);
hal_flash_itf_ob_wdg_freeze_status_t HAL_FLASH_ITF_OB_IsFrozenIWDGCounterLowPWRMode(const FLASH_TypeDef *flashx,
    uint32_t mode);

hal_status_t HAL_FLASH_ITF_OB_SetBootSelection(FLASH_TypeDef *flashx, hal_flash_itf_ob_boot_selection_t boot_select);
hal_flash_itf_ob_boot_selection_t HAL_FLASH_ITF_OB_GetBootSelection(const FLASH_TypeDef *flashx);

hal_status_t HAL_FLASH_ITF_OB_SetBoot0(FLASH_TypeDef *flashx, hal_flash_itf_ob_boot_state_t boot0);
hal_flash_itf_ob_boot_state_t HAL_FLASH_ITF_OB_GetBoot0(const FLASH_TypeDef *flashx);

hal_status_t HAL_FLASH_ITF_OB_SetBankTopology(FLASH_TypeDef *flashx, hal_flash_itf_ob_topology_t bank_topology);
hal_flash_itf_ob_topology_t HAL_FLASH_ITF_OB_GetBankTopology(const FLASH_TypeDef *flashx);

hal_status_t HAL_FLASH_ITF_OB_SetBankSwap(FLASH_TypeDef *flashx, hal_flash_itf_ob_bank_swap_t bank_swap);
hal_flash_itf_ob_bank_swap_t HAL_FLASH_ITF_OB_GetBankSwap(const FLASH_TypeDef *flashx);

hal_status_t HAL_FLASH_ITF_OB_EnableSRAMECC(FLASH_TypeDef *flashx, uint32_t sram);
hal_status_t HAL_FLASH_ITF_OB_DisableSRAMECC(FLASH_TypeDef *flashx, uint32_t sram);
hal_flash_itf_ob_sram_ecc_status_t HAL_FLASH_ITF_OB_IsEnabledSRAMECC(const FLASH_TypeDef *flashx, uint32_t sram);

hal_status_t HAL_FLASH_ITF_OB_SetBootAddr(FLASH_TypeDef *flashx, uint32_t boot_addr);
uint32_t HAL_FLASH_ITF_OB_GetBootAddr(const FLASH_TypeDef *flashx);


hal_status_t HAL_FLASH_ITF_OB_LockBootConfig(FLASH_TypeDef *flashx);
hal_status_t HAL_FLASH_ITF_OB_UnlockBootConfig(FLASH_TypeDef *flashx);
hal_flash_itf_ob_boot_lock_status_t HAL_FLASH_ITF_OB_IsLockedBootConfig(const FLASH_TypeDef *flashx);

hal_status_t HAL_FLASH_ITF_OB_SetBootloaderInterfaceConfig(FLASH_TypeDef *flashx, uint32_t bootloader_config);
uint32_t HAL_FLASH_ITF_OB_GetBootloaderInterfaceConfig(const FLASH_TypeDef *flashx);
/**
  * @}
  */

/** @defgroup FLASH_ITF_Exported_Functions_Group3 FLASH ITF IRQHandler and callback functions
  * @{
  */
void HAL_FLASH_ITF_IRQHandler(FLASH_TypeDef *flashx);


void HAL_FLASH_ITF_OB_ProgramCpltCallback(FLASH_TypeDef *flashx);
void HAL_FLASH_ITF_OB_ErrorCallback(FLASH_TypeDef *flashx);
/**
  * @}
  */

/** @defgroup FLASH_ITF_Exported_Functions_Group4 FLASH ITF program option-bytes functions configuration
  * @{
  */
hal_status_t HAL_FLASH_ITF_OB_Program(FLASH_TypeDef *flashx);
/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* STM32C5XX_HAL_ITF_H */
