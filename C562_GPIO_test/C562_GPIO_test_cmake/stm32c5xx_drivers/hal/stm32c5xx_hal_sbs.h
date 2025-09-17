/**
  **********************************************************************************************************************
  * @file    stm32c5xx_hal_sbs.h
  * @author  GPM Application Team
  * @brief   Header file of SBS HAL module driver.
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
#ifndef STM32C5XX_HAL_SBS_H
#define STM32C5XX_HAL_SBS_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ----------------------------------------------------------------------------------------------------------*/
#include "stm32c5xx_hal_def.h"
#include "stm32c5xx_ll_sbs.h"

/** @addtogroup STM32C5xx_HAL_Driver
  * @{
  */

/** @defgroup SBS SBS
  * @{
  */

/* Exported types ----------------------------------------------------------------------------------------------------*/
/** @defgroup SBS_Exported_Types SBS Exported Types
  * @{
  */

/*! HAL SBS fast mode plus enumeration definition */
typedef enum
{
  HAL_SBS_FAST_MODE_PLUS_DISABLED = 0U, /*!< Fast mode plus is disabled */
  HAL_SBS_FAST_MODE_PLUS_ENABLED  = 1U  /*!< Fast mode plus is enabled  */
} hal_sbs_fast_mode_plus_status_t;

/*! HAL SBS floating point unit interrupts state enumeration definition */
typedef enum
{
  HAL_SBS_IT_FPU_DISABLED = 0U, /*!< Floating point interrupt is disabled */
  HAL_SBS_IT_FPU_ENABLED  = 1U  /*!< Floating point interrupt is enabled  */
} hal_sbs_it_fpu_status_t;

/*! HAL SBS TIM break inputs enumeration definition */
typedef enum
{
  HAL_SBS_TIM_BREAK_INPUT_DISABLED = 0U, /*!< TIM break input is disabled */
  HAL_SBS_TIM_BREAK_INPUT_ENABLED  = 1U  /*!< TIM break input is enabled  */
} hal_sbs_tim_break_input_status_t;

/*! HAL SBS compensation cell code source enumeration definition */
typedef enum
{
  HAL_SBS_CCELL_CODE_DEFAULT = 0U, /*!< Compensation cell code default value */
  HAL_SBS_CCELL_CODE_CUSTOM  = 1U  /*!< Compnsation cell code custom value   */
} hal_sbs_ccell_code_src_t;

/*! HAL SBS compensation cell state enumeration definition */
typedef enum
{
  HAL_SBS_CCELL_DISABLED = 0U, /*!< Compensationn cell is disabled */
  HAL_SBS_CCELL_ENABLED  = 1U  /*!< Compensation cell is enabled   */
} hal_sbs_ccell_status_t;

/*! HAL SBS Hide protection level enumeration definition */
typedef enum
{
  HAL_SBS_HDP_LEVEL_1 = LL_SBS_HDPL_VALUE_1,  /*!< Hide protection level 1 */
  HAL_SBS_HDP_LEVEL_2 = LL_SBS_HDPL_VALUE_2,  /*!< Hide protection level 2 */
  HAL_SBS_HDP_LEVEL_3 = LL_SBS_HDPL_VALUE_3,  /*!< Hide protection level 3 */
} hal_sbs_hdp_level_value_t;
#if defined(SBS_NEXTHDPLCR_NEXTHDPL)

/*! HAL SBS Next Hide Protection Level Selection enumeration definition */
typedef enum
{
  HAL_SBS_HDP_OBK_LEVEL_0 = LL_SBS_HDP_OBK_0,  /*!< Increment the current HDPL to point (through OBK-HDPL) to the next secure storage areas */
  HAL_SBS_HDP_OBK_LEVEL_1 = LL_SBS_HDP_OBK_1,  /*!< Increment the current HDPL to point (through OBK-HDPL) to the next secure storage areas */
  HAL_SBS_HDP_OBK_LEVEL_2 = LL_SBS_HDP_OBK_2,  /*!< Increment the current HDPL to point (through OBK-HDPL) to the next secure storage areas */
  HAL_SBS_HDP_OBK_LEVEL_3 = LL_SBS_HDP_OBK_3,  /*!< Increment the current HDPL to point (through OBK-HDPL) to the next secure storage areas */
} hal_sbs_hdp_obk_level_value_t;
#endif /* SBS_NEXTHDPLCR_NEXTHDPL */

/*! HAL SBS Core register lock status enumeration definition */
typedef enum
{
  HAL_SBS_CORE_REG_UNLOCKED = 0U, /*!< SBS Core register unlocked */
  HAL_SBS_CORE_REG_LOCKED   = 1U  /*!< SBS Core register locked   */
} hal_sbs_core_reg_lock_status_t;

#if defined(ETH_BASE)
/*! HAL SBS Ethernet interface selection enumeration definition */
typedef enum
{
  HAL_SBS_ETH_PHY_INT_GMII_MII = LL_SBS_ETH_SEL_PHY_GMII_MII, /*!< GMII or MII interface */
  HAL_SBS_ETH_PHY_INT_RMII     = LL_SBS_ETH_SEL_PHY_RMII,     /*!< RMII interface */
  HAL_SBS_ETH_PHY_INT_10BT1S   = LL_SBS_ETH_SEL_PHY_10BT1S   /*!< 10BT1S interface */
} hal_sbs_eth_interface_t;

/*! HAL SBS Ethernet polarity enumeration definition */
typedef enum
{
  HAL_SBS_ETH_INT_POL_HIGH  = LL_SBS_ETH_INTPOL_HIGH, /*!< Ethernet external PHY interrupt polarity configuration active high */
  HAL_SBS_ETH_INT_POL_LOW   = LL_SBS_ETH_INTPOL_LOW  /*!< Ethernet external PHY interrupt polarity configuration active low */
} hal_sbs_eth_polarity_t;

/*! HAL SBS Ethernet TXLPI status enumeration definition */
typedef enum
{
  HAL_SBS_ETH_TXLPI_DISABLED = 0U, /*!< Ethernet TXLPI mode disabled */
  HAL_SBS_ETH_TXLPI_ENABLED  = 1U  /*!< Ethernet TXLPI mode enabled  */
} hal_sbs_eth_txlpi_status_t;

/*! HAL SBS Ethernet power down acknowledge enumeration definition */
typedef enum
{
  HAL_SBS_ETH_PWR_DOWN_ACTIVE    = 0U, /*!< Ethernet power down sequence not completed */
  HAL_SBS_ETH_PWR_DOWN_COMPLETED = 1U  /*!< Ethernet power down sequence completed     */
} hal_sbs_eth_pwr_down_ack_t;
#endif /* ETH_BASE */

#if defined(SBS_PMCR_ADC1_IN2_REMAP)
/*! HAL SBS ADC channel pin remapping status enumeration definition */
typedef enum
{
  HAL_SBS_ADC_CHANNEL_PIN_NOT_REMAPPED = 0U, /*!< SBS ADC Channel pin not remapped */
  HAL_SBS_ADC_CHANNEL_PIN_REMAPPED     = 1U  /*!< SBS ADC Channel pin remapped     */
} hal_sbs_adc_channel_pin_remap_status_t;
#endif /* SBS_PMCR_ADC1_IN2_REMAP */
/**
  * @}
  */

/* Exported constants ------------------------------------------------------------------------------------------------*/
/** @defgroup SBS_Exported_Constants SBS Exported Constants
  * @{
  */

/** @defgroup SBS_FLOATING_POINT_UNIT_INTERRUPTS SBS Floating point unit interrupts
  * @{
  */
#define HAL_SBS_IT_FPU_IOC LL_SBS_IT_FPU_IOC /*!< Invalid operation interrupt        */
#define HAL_SBS_IT_FPU_DZC LL_SBS_IT_FPU_DZC /*!< Divide-by-zero interrupt           */
#define HAL_SBS_IT_FPU_UFC LL_SBS_IT_FPU_UFC /*!< underflow interrupt                */
#define HAL_SBS_IT_FPU_OFC LL_SBS_IT_FPU_OFC /*!< Overflow interrupt                 */
#define HAL_SBS_IT_FPU_IDC LL_SBS_IT_FPU_IDC /*!< Input abnormal interrupt           */
#define HAL_SBS_IT_FPU_IXC LL_SBS_IT_FPU_IXC /*!< Inexact interrupt                  */
#define HAL_SBS_IT_FPU_ALL LL_SBS_IT_FPU_ALL /*!< All floating point unit interrupts */
/**
  * @}
  */

/** @defgroup SBS_TIM_BREAK_INPUTS SBS TIM break inputs
  * @{
  */
#define HAL_SBS_FLASH_ECC_DOUBLE_ERROR LL_SBS_FLASH_ECC_DOUBLE_ERROR /*!< Flash ECC double error */
#define HAL_SBS_PVD                    LL_SBS_PVD                    /*!< PVD connection         */
#define HAL_SBS_SRAM_ECC_DOUBLE_ERROR  LL_SBS_SRAM_ECC_DOUBLE_ERROR  /*!< SRAM ECC double error  */
#define HAL_SBS_LOCKUP_OUT             LL_SBS_LOCKUP_OUT             /*!< Cortex-M33 LOCKUP      */
#define HAL_SBS_TIM_BREAK_INPUTS_ALL   LL_SBS_TIM_BREAK_INPUTS_ALL   /*!< All TIM break inputs   */
/**
  * @}
  */

/** @defgroup SBS_FAST_MODE_PLUS_DRIVE SBS Fast mode plus drive
  * @{
  */
#define HAL_SBS_DRIVE_PA11              LL_SBS_DRIVE_PA11              /*!< Fast mode plus driving capability activation on PA11 */
#define HAL_SBS_DRIVE_PA12              LL_SBS_DRIVE_PA12              /*!< Fast mode plus driving capability activation on PA12 */
#define HAL_SBS_DRIVE_PB3               LL_SBS_DRIVE_PB3               /*!< Fast mode plus driving capability activation on PB3 */
#define HAL_SBS_DRIVE_PB4               LL_SBS_DRIVE_PB4               /*!< Fast mode plus driving capability activation on PB4 */
#define HAL_SBS_DRIVE_PB6               LL_SBS_DRIVE_PB6               /*!< Fast mode plus driving capability activation on PB6 */
#define HAL_SBS_DRIVE_PB7               LL_SBS_DRIVE_PB7               /*!< Fast mode plus driving capability activation on PB7 */
#define HAL_SBS_DRIVE_PB8               LL_SBS_DRIVE_PB8               /*!< Fast mode plus driving capability activation on PB8 */
#define HAL_SBS_DRIVE_PB9               LL_SBS_DRIVE_PB9               /*!< Fast mode plus driving capability activation on PB9 */
#define HAL_SBS_DRIVE_ALL               LL_SBS_DRIVE_ALL               /*!< ALL Fast mode plus driving capability activation    */
/**
  * @}
  */

/** @defgroup SBS_COMPENSATION_CELL SBS Compensation cell
  * @{
  */
#define HAL_SBS_CCELL_VDDIO LL_SBS_CCELL_VDDIO /*!< VDD I/O compensation cell */
#define HAL_SBS_CCELL_ALL   LL_SBS_CCELL_ALL   /*!< All compensation cell     */
/**
  * @}
  */

/** @defgroup SBS_CORE_LOCK_REGISTERS SBS Core lock registers
  * @{
  */
#define HAL_SBS_CORE_VTOR_REG LL_SBS_CPU_LOCK_VTOR /*!< VTOR register */
#define HAL_SBS_CORE_MPU_REG  LL_SBS_CPU_LOCK_MPU  /*!< MPU register  */
#define HAL_SBS_CORE_ALL_REGS LL_SBS_CPU_LOCK_ALL  /*!< All registers */
/**
  * @}
  */

/** @defgroup SBS_ERASE_STATUS_FLAGS SBS Erase status Flags
  * @{
  */
#define HAL_SBS_FLAG_ICACHE   LL_SBS_FLAG_IPMEE /*!< ICACHE erase status flag */
#define HAL_SBS_FLAG_MEMORIES LL_SBS_FLAG_MCLR  /*!< SRAM2 and ICACHE flag    */
/**
  * @}
  */

#if defined(SBS_PMCR_ADC1_IN2_REMAP)
/** @defgroup SBS_ADC_CHANNEL_PIN_REMAP SBS ADC channel pin remap
  * @{
  */
#define HAL_SBS_REMAP_ADC_IN7_TO_PB1 LL_SBS_REMAP_ADC_IN7_TO_PB1 /*!< Remap ADC IN7 to PB1 */
#define HAL_SBS_REMAP_ADC_IN6_TO_PB0 LL_SBS_REMAP_ADC_IN6_TO_PB0 /*!< Remap ADC IN6 to PB0 */
#define HAL_SBS_REMAP_ADC_IN5_TO_PC5 LL_SBS_REMAP_ADC_IN5_TO_PC5 /*!< Remap ADC IN5 to PC5 */
#define HAL_SBS_REMAP_ADC_IN2_TO_PC4 LL_SBS_REMAP_ADC_IN2_TO_PC4 /*!< Remap ADC IN2 to PC4 */
#define HAL_SBS_REMAP_ADC_IN_ALL     LL_SBS_REMAP_ADC_IN_ALL     /*!< Remap ALL ADC IN     */
/**
  * @}
  */
#endif /* SBS_PMCR_ADC1_IN2_REMAP */
/**
  * @}
  */

/* Exported functions ------------------------------------------------------------------------------------------------*/
/** @defgroup SBS_Exported_Functions SBS Exported Functions
  * @{
  */

/** @defgroup SBS_Exported_Functions_Group1 Fast mode plus functions
  * @{
  */
void HAL_SBS_EnableFastModePlus(uint32_t fast_mode_plus);
void HAL_SBS_DisableFastModePlus(uint32_t fast_mode_plus);
hal_sbs_fast_mode_plus_status_t HAL_SBS_IsEnabledFastModePlus(uint32_t fast_mode_plus);
/**
  * @}
  */

/** @defgroup SBS_Exported_Functions_Group2 Floating point unit interrupts management functions
  * @{
  */
void HAL_SBS_EnableFPUIT(uint32_t floating_point);
void HAL_SBS_DisableFPUIT(uint32_t floating_point);
hal_sbs_it_fpu_status_t HAL_SBS_IsEnabledFPUIT(uint32_t floating_point);
/**
  * @}
  */

/** @defgroup SBS_Exported_Functions_Group3 TIM break inputs management functions
  * @{
  */
void HAL_SBS_EnableTIMBreakInputs(uint32_t break_input);
void HAL_SBS_DisableTIMBreakInputs(uint32_t break_input);
hal_sbs_tim_break_input_status_t HAL_SBS_IsEnabledTIMBreakInputs(uint32_t break_input);
/**
  * @}
  */

/** @defgroup SBS_Exported_Functions_Group4 Compensation cell control functions
  * @{
  */
void HAL_SBS_SetCompensationCellCodeSrc(uint32_t comp_cell, hal_sbs_ccell_code_src_t code_select);
hal_sbs_ccell_code_src_t HAL_SBS_GetCompensationCellCodeSrc(uint32_t comp_cell);

hal_status_t HAL_SBS_EnableCompensationCell(uint32_t comp_cell);
void HAL_SBS_DisableCompensationCell(uint32_t comp_cell);
hal_sbs_ccell_status_t HAL_SBS_IsEnabledCompensationCell(uint32_t comp_cell);
/**
  * @}
  */

/** @defgroup SBS_Exported_Functions_Group5 Compensation cell code management functions
  * @{
  */
uint32_t HAL_SBS_GetPMOSCompensationCellValue(uint32_t comp_cell);
uint32_t HAL_SBS_GetNMOSCompensationCellValue(uint32_t comp_cell);

void HAL_SBS_SetConfigxMOSCompensationCellCode(uint32_t comp_cell, uint32_t pmos_code, uint32_t nmos_code);
void HAL_SBS_GetConfigxMOSCompensationCellCode(uint32_t comp_cell, uint32_t *p_pmos_code, uint32_t *p_nmos_code);
/**
  * @}
  */

/** @defgroup SBS_Exported_Functions_Group6 NMI double ECC error in FLASH Interface functions
  * @{
  */
void HAL_SBS_FLASH_EnableECCNMI(void);
void HAL_SBS_FLASH_DisableECCNMI(void);
uint32_t HAL_SBS_FLASH_IsEnabledECCNMI(void);
/**
  * @}
  */

/** @defgroup SBS_Exported_Functions_Group7 Hide Protection Level management functions
  * @{
  */
hal_status_t HAL_SBS_SetHDPLevelValue(hal_sbs_hdp_level_value_t value);
hal_sbs_hdp_level_value_t HAL_SBS_GetHDPLevelValue(void);
#if defined(SBS_NEXTHDPLCR_NEXTHDPL)

void HAL_SBS_SetHDPOBKLevelValue(hal_sbs_hdp_obk_level_value_t value);
hal_sbs_hdp_obk_level_value_t HAL_SBS_GetHDPOBKLevelValue(void);
#endif /* SBS_NEXTHDPLCR_NEXTHDPL */
/**
  * @}
  */

/** @defgroup SBS_Exported_Functions_Group8 Core lock registers functions
  * @{
  */
void HAL_SBS_LockCoreRegisters(uint32_t core_regs);
hal_sbs_core_reg_lock_status_t HAL_SBS_IsLockedCoreRegisters(uint32_t core_regs);
/**
  * @}
  */

/** @defgroup SBS_Exported_Functions_Group9 Flag management functions
  * @{
  This section provides functions allowing to management the Memories erase status feature :
  - Call HAL_SBS_IsActiveFlag() to check the memories erase status flags.
  - Call HAL_SBS_ClearFlag() to get clear the memories erase status pending flags.
  */

/**
  * @brief Check if the SBS memories erase status flags is active or not
  * @param flag This parameter can be one of the following values:
  *        @arg @ref HAL_SBS_FLAG_ICACHE
  *        @arg @ref HAL_SBS_FLAG_MEMORIES
  * @retval retrieve the state of the selected memory flag (1U or 0U).
  */
__STATIC_INLINE uint32_t HAL_SBS_IsActiveFlag(uint32_t flag)
{
  return ((READ_BIT(SBS->MESR, flag) == flag) ? 1UL : 0UL);
}

/**
  * @brief Clear the SBS memories erase status pending flags
  * @param flag This parameter can be one or a combination of the following values:
  *        @arg @ref HAL_SBS_FLAG_ICACHE
  *        @arg @ref HAL_SBS_FLAG_MEMORIES
  */
__STATIC_INLINE void HAL_SBS_ClearFlag(uint32_t flag)
{
  SET_BIT(SBS->MESR, flag);
}
/**
  * @}
  */

#if defined(ETH_BASE)
/** @defgroup SBS_Exported_Functions_Group10 Ethernet functions
  * @{
  */
void HAL_SBS_ETH_SetPolarity(hal_sbs_eth_polarity_t polarity);
hal_sbs_eth_polarity_t HAL_SBS_ETH_GetPolarity(void);

void HAL_SBS_ETH_SetInterface(hal_sbs_eth_interface_t phy_int);
hal_sbs_eth_interface_t HAL_SBS_ETH_GetInterface(void);

hal_sbs_eth_txlpi_status_t HAL_SBS_ETH_GetTxLPIStatus(void);
hal_sbs_eth_pwr_down_ack_t HAL_SBS_ETH_GetPwrDownAck(void);
/**
  * @}
  */
#endif /* ETH_BASE */

#if defined(SBS_PMCR_ADC1_IN2_REMAP)
/** @defgroup SBS_Exported_Functions_Group11 Channel Pin Remap functions
  * @{
  */
void HAL_SBS_ADC_EnableChannelPinRemap(uint32_t channel_pin_remap);
void HAL_SBS_ADC_DisableChannelPinRemap(uint32_t channel_pin_remap);
hal_sbs_adc_channel_pin_remap_status_t HAL_SBS_ADC_IsEnabledChannelPinRemap(uint32_t channel_pin_remap);
/**
  * @}
  */
#endif /* SBS_PMCR_ADC1_IN2_REMAP */

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

#endif /* STM32C5XX_HAL_SBS_H */
