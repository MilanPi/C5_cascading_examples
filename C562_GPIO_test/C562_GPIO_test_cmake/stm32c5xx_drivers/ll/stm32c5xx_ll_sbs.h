/**
  **********************************************************************************************************************
  * @file    stm32c5xx_ll_sbs.h
  * @author  GPAM Application Team
  * @brief   Header file of LL SBS module.
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
#ifndef STM32C5XX_LL_SBS_H
#define STM32C5XX_LL_SBS_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ----------------------------------------------------------------------------------------------------------*/
#include "stm32c5xx.h"

/** @addtogroup STM32C5xx_LL_Driver
  * @{
  */

/** @defgroup LL_SBS LL SBS
  * @{
  */

/* Private constants -------------------------------------------------------------------------------------------------*/
/** @defgroup SBS_LL_Private_Constants LL SBS private constants
  * @{
  */
#define LL_SBS_HDPL_INCREMENT_VALUE 0x6AU /*!< Define used for the HDPL increment */
/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/** @defgroup SBS_LL_Exported_Constants SBS Exported Constants
  * @{
  */

/** @defgroup LL_SBS_HDPL_Value  HDPL Value
  * @{
  */
#define LL_SBS_HDPL_VALUE_1 0x00000051U /*!< Hide protection level 1 */
#define LL_SBS_HDPL_VALUE_2 0x0000008AU /*!< Hide protection level 2 */
#define LL_SBS_HDPL_VALUE_3 0x0000006FU /*!< Hide protection level 3 */
/**
  * @}
  */

#if defined(SBS_NEXTHDPLCR_NEXTHDPL)
/** @defgroup LL_SBS_Next_HDP_Level_Selection  SBS Next HDP Level Selection
  * @{
  */
#define LL_SBS_HDP_OBK_0 0x00000000U               /*!< Index to add to the current HDPL to point (through OBK-HDPL) to the next secure storage areas */
#define LL_SBS_HDP_OBK_1 SBS_NEXTHDPLCR_NEXTHDPL_0 /*!< Index to add to the current HDPL to point (through OBK-HDPL) to the next secure storage areas */
#define LL_SBS_HDP_OBK_2 SBS_NEXTHDPLCR_NEXTHDPL_1 /*!< Index to add to the current HDPL to point (through OBK-HDPL) to the next secure storage areas */
#define LL_SBS_HDP_OBK_3 SBS_NEXTHDPLCR_NEXTHDPL   /*!< Index to add to the current HDPL to point (through OBK-HDPL) to the next secure storage areas */
/**
  * @}
  */
#endif /* SBS_NEXTHDPLCR_NEXTHDPL */

/** @defgroup LL_SBS_EC_DRIVE SBS FASTMODEPLUS
  * @{
  */
#define LL_SBS_DRIVE_PA11 SBS_PMCR_PA11_FMP                     /*!< Enable Fast Mode Plus on PA11 */
#define LL_SBS_DRIVE_PA12 SBS_PMCR_PA12_FMP                     /*!< Enable Fast Mode Plus on PA12 */
#define LL_SBS_DRIVE_PB3  SBS_PMCR_PB3_FMP                      /*!< Enable Fast Mode Plus on PB3 */
#define LL_SBS_DRIVE_PB4  SBS_PMCR_PB4_FMP                      /*!< Enable Fast Mode Plus on PB4 */
#define LL_SBS_DRIVE_PB6  SBS_PMCR_PB6_FMP                      /*!< Enable Fast Mode Plus on PB6 */
#define LL_SBS_DRIVE_PB7  SBS_PMCR_PB7_FMP                      /*!< Enable Fast Mode Plus on PB7 */
#define LL_SBS_DRIVE_PB8  SBS_PMCR_PB8_FMP                      /*!< Enable Fast Mode Plus on PB8 */
#define LL_SBS_DRIVE_PB9  SBS_PMCR_PB9_FMP                      /*!< Enable Fast Mode Plus on PB9 */
#define LL_SBS_DRIVE_ALL  (SBS_PMCR_PA11_FMP | SBS_PMCR_PA12_FMP | \
                           SBS_PMCR_PB3_FMP | SBS_PMCR_PB4_FMP |   \
                           SBS_PMCR_PB6_FMP | SBS_PMCR_PB7_FMP |   \
                           SBS_PMCR_PB8_FMP | SBS_PMCR_PB9_FMP) /*!< Enables all Fast mode plus driving capability */
/**
  * @}
  */

#if defined(ETH_BASE)
/** @defgroup SBS_LL_EC_ETHINTPOL SBS Ethernet external PHY interrupt polarity configuration
  * @{
  */
#define LL_SBS_ETH_INTPOL_HIGH         0U                  /*!< Ethernet external PHY interrupt polarity configuration active high */
#define LL_SBS_ETH_INTPOL_LOW          SBS_PMCR_ETHINTPOL  /*!< Ethernet external PHY interrupt polarity configuration active low */
/**
  * @}
  */

/** @defgroup SBS_LL_EC_SBS_ETH_PHYSEL SBS Ethernet PHY interface selection
  * @{
  */
#define LL_SBS_ETH_SEL_PHY_GMII_MII    0U                     /*!< GMII or MII interface */
#define LL_SBS_ETH_SEL_PHY_RMII        SBS_PMCR_ETH_SEL_PHY_2 /*!< RMII interface */
#define LL_SBS_ETH_SEL_PHY_10BT1S      SBS_PMCR_ETH_SEL_PHY_3 /*!< 10BT1S interface */
/**
  * @}
  */
#endif /* ETH_BASE */

/** @defgroup SBS_LL_EC_FLOATING_POINT_UNIT_INTERRUPTs SBS floating point unit interrupts
  * @{
  */
#define LL_SBS_IT_FPU_IOC SBS_FPUIMR_FPU_IE_0                         /*!< Invalid operation interrupt */
#define LL_SBS_IT_FPU_DZC SBS_FPUIMR_FPU_IE_1                         /*!< Divide-by-zero interrupt    */
#define LL_SBS_IT_FPU_UFC SBS_FPUIMR_FPU_IE_2                         /*!< underflow interrupt         */
#define LL_SBS_IT_FPU_OFC SBS_FPUIMR_FPU_IE_3                         /*!< Overflow interrupt          */
#define LL_SBS_IT_FPU_IDC SBS_FPUIMR_FPU_IE_4                         /*!< Input abnormal interrupt    */
#define LL_SBS_IT_FPU_IXC SBS_FPUIMR_FPU_IE_5                         /*!< Inexact interrupt           */
#define LL_SBS_IT_FPU_ALL (SBS_FPUIMR_FPU_IE_0 | SBS_FPUIMR_FPU_IE_1 | \
                           SBS_FPUIMR_FPU_IE_2 | SBS_FPUIMR_FPU_IE_3 | \
                           SBS_FPUIMR_FPU_IE_4 | SBS_FPUIMR_FPU_IE_5) /*!< All floating point unit interrupts interrupt   */
/**
  * @}
  */

/** @defgroup LL_SBS_Erase_Status_Flags SBS Erase status Flags
  * @{
  */
#define LL_SBS_FLAG_IPMEE SBS_MESR_IPMEE /*!< ICACHE erase status flag                */
#define LL_SBS_FLAG_MCLR  SBS_MESR_MCLR  /*!< SRAM2, ICACHE, DCACHE erase status flag */
/**
  * @}
  */

/** @defgroup SBS_LL_EC_CCELL_CODE SBS compensation cell Code source
  * @{
  */
#define LL_SBS_CCELL_VDDIO SBS_CCCSR_EN1   /*!< Compensation cell selection for VDDIO */
#define LL_SBS_CCELL_ALL   (SBS_CCCSR_EN1) /*!< Compensation cell selection for ALL   */

#define LL_SBS_CCELL_CODE_DEFAULT 0U /*!< I/Os code from the cell (available in the SBS_CCVALR)               */
#define LL_SBS_CCELL_CODE_CUSTOM  1U /*!< I/Os code from the SBS compensation cell software code register (SBS_CCSWCR) */
/**
  * @}
  */

/** @defgroup SBS_LL_EC_CS1 SBS Vdd compensation cell Code selection
  * @{
  */
#define LL_SBS_CCELL_VDDIO_DEFAULT_CODE 0U           /*!< VDD I/Os code from the cell (available in the SBS_CCVALR)               */
#define LL_SBS_CCELL_VDDIO_CUSTOM_CODE  SBS_CCCSR_CS1 /*!< VDD I/Os code from the SBS compensation cell code register (SBS_CCSWCR) */
/**
  * @}
  */

/** @defgroup LL_SBS_EC_TIMBREAK SBS TIMER BREAK
  * @{
  */
#define LL_SBS_FLASH_ECC_DOUBLE_ERROR SBS_CFGR2_ECCL /*!< Enables and locks the Flash ECC double error signal with Break Input of TIM1/8/15/16/17 */
#define LL_SBS_PVD                    SBS_CFGR2_PVDL /*!< Enables and locks the PVD connection with TIM1/8/15/16/17 Break Input */
#define LL_SBS_SRAM_ECC_DOUBLE_ERROR  SBS_CFGR2_SEL  /*!< Enables and locks the SRAM ECC double error signal with Break Input of TIM1/8/15/16/17 */
#define LL_SBS_LOCKUP_OUT             SBS_CFGR2_CLL  /*!< Enables and locks the LOCKUP (Hardfault) output of Cortex-M33 with Break Input of TIM1/8/15/16/17 */
#define LL_SBS_TIM_BREAK_INPUTS_ALL   (SBS_CFGR2_ECCL | SBS_CFGR2_PVDL | \
                                       SBS_CFGR2_SEL | SBS_CFGR2_CLL) /*!< Enables and locks the all with Break Input */
/**
  * @}
  */

/** @defgroup LL_SBS_Lock_Core_Register SBS Lock Core Register
  * @{
  */
#define LL_SBS_CPU_LOCK_VTOR SBS_CLCKR_LOCKMPU                        /*!< VTOR register lock */
#define LL_SBS_CPU_LOCK_MPU  SBS_CLCKR_LOCKVTOR                       /*!< MPU register lock  */
#define LL_SBS_CPU_LOCK_ALL  (SBS_CLCKR_LOCKMPU | SBS_CLCKR_LOCKVTOR) /*!< All secure registers lock */
/**
  * @}
  */

/**
  * @}
  */
/* Exported macro ------------------------------------------------------------*/
/** @defgroup SBS_LL_Exported_Macros SBS Exported Macros
  * @{
  */

/** @defgroup SBS_LL_EM_WRITE_READ Common Write and read registers Macros
  * @{
  */

/**
  * @brief  Write a value in SBS register
  * @param  reg Register to be written
  * @param  value Value to be written in the register
  */
#define LL_SBS_WRITE_REG(reg, value) WRITE_REG(SBS->reg, (value))

/**
  * @brief  Read a value in SBS register
  * @param  reg Register to be read
  * @retval Register value
  */
#define LL_SBS_READ_REG(reg) READ_REG(SBS->reg)
/**
  * @}
  */

/**
  * @}
  */
/* Exported functions --------------------------------------------------------*/

/** @defgroup SBS_LL_Exported_Functions LL SBS exported functions
  * @{
  */

/** @defgroup LL_SBS_EF_HDPL_Management HDPL Management
  * @{
  */

/**
  * @brief  Increment by 1 the HDPL value
  * @rmtoll
  *  HDPLCR     HDPL_INCR      LL_SBS_IncrementHDPLevel
  */
__STATIC_INLINE void LL_SBS_IncrementHDPLevel(void)
{
  MODIFY_REG(SBS->HDPLCR, SBS_HDPLCR_INCR_HDPL, LL_SBS_HDPL_INCREMENT_VALUE);
}

/**
  * @brief  Get the HDPL Value.
  * @rmtoll
  *  HDPLSR     HDPL      LL_SBS_GetHDPLevel
  * @retval  Returns the HDPL value
  *          This return value can be one of the following values:
  *           @arg @ref LL_SBS_HDPL_VALUE_1 : HDPL1
  *           @arg @ref LL_SBS_HDPL_VALUE_2 : HDPL2
  *           @arg @ref LL_SBS_HDPL_VALUE_3 : HDPL3
  */
__STATIC_INLINE uint32_t LL_SBS_GetHDPLevel(void)
{
  return (uint32_t)(READ_BIT(SBS->HDPLSR, SBS_HDPLSR_HDPL));
}

#if defined(SBS_NEXTHDPLCR_NEXTHDPL)
/**
  * @brief  Set the OBK-HDPL Value.
  * @rmtoll
  *  NEXTHDPLCR     NEXTHDPL      LL_SBS_SetOBKHDPLevel
  * @param  value Value of increment to add to HDPL value to generate the OBK-HDPL.
  *         This parameter can be one of the following values:
  *         @arg @ref LL_SBS_HDP_OBK_0 : HDPL
  *         @arg @ref LL_SBS_HDP_OBK_1 : HDPL + 1
  *         @arg @ref LL_SBS_HDP_OBK_2 : HDPL + 2
  *         @arg @ref LL_SBS_HDP_OBK_3 : HDPL + 3
  */
__STATIC_INLINE void LL_SBS_SetOBKHDPLevel(uint32_t value)
{
  MODIFY_REG(SBS->NEXTHDPLCR, SBS_NEXTHDPLCR_NEXTHDPL, (uint32_t)(value));
}

/**
  * @brief  Get the OBK-HDPL Value.
  * @rmtoll
  *  NEXTHDPLCR     NEXTHDPL      LL_SBS_GetOBKHDPLevel
  * @retval  Returns the incremement to add to HDPL value to generate OBK-HDPL
  *          This return value can be one of the following values:
  *          @arg @ref LL_SBS_HDP_OBK_0 : HDPL
  *          @arg @ref LL_SBS_HDP_OBK_1 : HDPL + 1
  *          @arg @ref LL_SBS_HDP_OBK_2 : HDPL + 2
  *          @arg @ref LL_SBS_HDP_OBK_3 : HDPL + 3
  */
__STATIC_INLINE  uint32_t LL_SBS_GetOBKHDPLevel(void)
{
  return (uint32_t)(READ_BIT(SBS->NEXTHDPLCR, SBS_NEXTHDPLCR_NEXTHDPL));
}
#endif /* SBS_NEXTHDPLCR_NEXTHDPL */

/**
  * @}
  */

/** @defgroup LL_SBS_EF_FPM_Management FPM Management
  * @{
  */

/**
  * @brief  Enable the fast mode plus driving capability.
  * @rmtoll
  *  SBS_PMCR     PBx_FMP   LL_SBS_EnableFastModePlus
  * @param  fast_mode_plus This parameter can be one or a combination of the following values:
  *         @arg @ref LL_SBS_DRIVE_PA11
  *         @arg @ref LL_SBS_DRIVE_PA12
  *         @arg @ref LL_SBS_DRIVE_PB3
  *         @arg @ref LL_SBS_DRIVE_PB4
  *         @arg @ref LL_SBS_DRIVE_PB6
  *         @arg @ref LL_SBS_DRIVE_PB7
  *         @arg @ref LL_SBS_DRIVE_PB8
  *         @arg @ref LL_SBS_DRIVE_PB9
  *         @arg @ref LL_SBS_DRIVE_ALL
  */
__STATIC_INLINE void LL_SBS_EnableFastModePlus(uint32_t fast_mode_plus)
{
  SET_BIT(SBS->PMCR, fast_mode_plus);
}

/**
  * @brief  Disable the fast mode plus driving capability.
  * @rmtoll
  *  SBS_PMCR     PBx_FMP   LL_SBS_DisableFastModePlus
  * @param  fast_mode_plus This parameter can be one or a combination of the following values:
  *         @arg @ref LL_SBS_DRIVE_PA11
  *         @arg @ref LL_SBS_DRIVE_PA12
  *         @arg @ref LL_SBS_DRIVE_PB3
  *         @arg @ref LL_SBS_DRIVE_PB4
  *         @arg @ref LL_SBS_DRIVE_PB6
  *         @arg @ref LL_SBS_DRIVE_PB7
  *         @arg @ref LL_SBS_DRIVE_PB8
  *         @arg @ref LL_SBS_DRIVE_PB9
  *         @arg @ref LL_SBS_DRIVE_ALL
  */
__STATIC_INLINE void LL_SBS_DisableFastModePlus(uint32_t fast_mode_plus)
{
  CLEAR_BIT(SBS->PMCR, fast_mode_plus);
}

/**
  * @brief  Check if fast mode plus is enabled or disabled.
  * @rmtoll
  *  SBS_PMCR   PBx_FMP   LL_SBS_IsEnabledFastModePlus
  * @param  fast_mode_plus This parameter can be one or a combination of the following values:
  *         @arg @ref LL_SBS_DRIVE_PA11
  *         @arg @ref LL_SBS_DRIVE_PA12
  *         @arg @ref LL_SBS_DRIVE_PB3
  *         @arg @ref LL_SBS_DRIVE_PB4
  *         @arg @ref LL_SBS_DRIVE_PB6
  *         @arg @ref LL_SBS_DRIVE_PB7
  *         @arg @ref LL_SBS_DRIVE_PB8
  *         @arg @ref LL_SBS_DRIVE_PB9
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SBS_IsEnabledFastModePlus(uint32_t fast_mode_plus)
{
  return ((READ_BIT(SBS->PMCR, fast_mode_plus) == fast_mode_plus) ? 1UL : 0UL);
}

/**
  * @}
  */

#if defined(ETH_BASE)
/** @defgroup LL_SBS_EF_ETHERNET_Management ETHERNET Management
  * @{
  */

/**
  * @brief  Check if the MAC has entered Tx LPI mode.
  * @rmtoll
  *  SBS_PMCR   ETHTXLPI   LL_SBS_IsEnabledTxLPIMode
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SBS_IsEnabledTxLPIMode(void)
{
  return ((READ_BIT(SBS->PMCR, SBS_PMCR_ETHTXLPI) == SBS_PMCR_ETHTXLPI) ? 1UL : 0UL);
}

/**
  * @brief  Check if the Ethernet controller has complete its power-down sequence.
  * @rmtoll
  *  SBS_PMCR   ETHPDACK   LL_SBS_IsPowerDownSeqCompleted
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SBS_IsPowerDownSeqCompleted(void)
{
  return ((READ_BIT(SBS->PMCR, SBS_PMCR_ETHPDACK) == SBS_PMCR_ETHPDACK) ? 1UL : 0UL);
}

/**
  * @brief  Set the ethernet polarity.
  * @rmtoll
  *  SBS_PMCR     ETHINTPOL   LL_SBS_SetEthernetPolarity
  * @param  level This parameter can be one of the following values:
  *         @arg @ref LL_SBS_ETH_INTPOL_HIGH
  *         @arg @ref LL_SBS_ETH_INTPOL_LOW
  */
__STATIC_INLINE void LL_SBS_SetEthernetPolarity(uint32_t level)
{
  MODIFY_REG(SBS->PMCR, SBS_PMCR_ETHINTPOL, level);
}

/**
  * @brief  Get the ethernet polarity.
  * @rmtoll
  *  SBS_PMCR     ETHINTPOL   LL_SBS_GetEthernetPolarity
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_SBS_ETH_INTPOL_HIGH
  *         @arg @ref LL_SBS_ETH_INTPOL_LOW
  */
__STATIC_INLINE uint32_t LL_SBS_GetEthernetPolarity(void)
{
  return (uint32_t)(READ_BIT(SBS->PMCR, SBS_PMCR_ETHINTPOL));
}

/**
  * @brief  Select the ethernet interface.
  * @rmtoll
  *  SBS_PMCR     ETH_SEL_PHYx   LL_SBS_SetEthernetInterface
  * @param  interface This parameter can be one of the following values:
  *         @arg @ref LL_SBS_ETH_SEL_PHY_GMII_MII
  *         @arg @ref LL_SBS_ETH_SEL_PHY_RMII
  *         @arg @ref LL_SBS_ETH_SEL_PHY_10BT1S
  */
__STATIC_INLINE void LL_SBS_SetEthernetInterface(uint32_t interface)
{
  MODIFY_REG(SBS->PMCR, SBS_PMCR_ETH_SEL_PHY, interface);
}

/**
  * @brief  Get the ethernet interface.
  * @rmtoll
  *  SBS_PMCR     ETH_SEL_PHYx   LL_SBS_GetEthernetInterface
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_SBS_ETH_SEL_PHY_GMII_MII
  *         @arg @ref LL_SBS_ETH_SEL_PHY_RMII
  *         @arg @ref LL_SBS_ETH_SEL_PHY_10BT1S
  */
__STATIC_INLINE uint32_t LL_SBS_GetEthernetInterface(void)
{
  return (uint32_t)(READ_BIT(SBS->PMCR, SBS_PMCR_ETH_SEL_PHY));
}

/**
  * @}
  */
#endif /* ETH_BASE */

/** @defgroup LL_SBS_EF_FPUIT_Management FPUIT Management
  * @{
  */

/**
  * @brief  Enable floating point unit interrupts bits.
  * @rmtoll
  *  SBS_FPUIMR FPU_IE_0   LL_SBS_EnableFPUIT \n
  *  SBS_FPUIMR FPU_IE_1   LL_SBS_EnableFPUIT \n
  *  SBS_FPUIMR FPU_IE_2   LL_SBS_EnableFPUIT \n
  *  SBS_FPUIMR FPU_IE_3   LL_SBS_EnableFPUIT \n
  *  SBS_FPUIMR FPU_IE_4   LL_SBS_EnableFPUIT \n
  *  SBS_FPUIMR FPU_IE_5   LL_SBS_EnableFPUIT
  * @param  floating_point This parameter can be one or a combination of the following values:
  *         @arg @ref LL_SBS_IT_FPU_IOC
  *         @arg @ref LL_SBS_IT_FPU_DZC
  *         @arg @ref LL_SBS_IT_FPU_UFC
  *         @arg @ref LL_SBS_IT_FPU_OFC
  *         @arg @ref LL_SBS_IT_FPU_IDC
  *         @arg @ref LL_SBS_IT_FPU_IXC
  *         @arg @ref LL_SBS_IT_FPU_ALL
  */
__STATIC_INLINE void LL_SBS_EnableFPUIT(uint32_t floating_point)
{
  SET_BIT(SBS->FPUIMR, floating_point);
}

/**
  * @brief  Disable floating point unit interrupts bits.
  * @rmtoll
  *  SBS_FPUIMR FPU_IE_0   LL_SBS_DisableFPUIT \n
  *  SBS_FPUIMR FPU_IE_1   LL_SBS_DisableFPUIT \n
  *  SBS_FPUIMR FPU_IE_2   LL_SBS_DisableFPUIT \n
  *  SBS_FPUIMR FPU_IE_3   LL_SBS_DisableFPUIT \n
  *  SBS_FPUIMR FPU_IE_4   LL_SBS_DisableFPUIT \n
  *  SBS_FPUIMR FPU_IE_5   LL_SBS_DisableFPUIT
  * @param  floating_point This parameter can be one or a combination of the following values:
  *         @arg @ref LL_SBS_IT_FPU_IOC
  *         @arg @ref LL_SBS_IT_FPU_DZC
  *         @arg @ref LL_SBS_IT_FPU_UFC
  *         @arg @ref LL_SBS_IT_FPU_OFC
  *         @arg @ref LL_SBS_IT_FPU_IDC
  *         @arg @ref LL_SBS_IT_FPU_IXC
  *         @arg @ref LL_SBS_IT_FPU_ALL
  */
__STATIC_INLINE void LL_SBS_DisableFPUIT(uint32_t floating_point)
{
  CLEAR_BIT(SBS->FPUIMR, floating_point);
}

/**
  * @brief  Check if floating point unit interrupts bits is enabled.
  * @rmtoll
  *  SBS_FPUIMR FPU_IE_0   LL_SBS_IsEnabledFPUIT \n
  *  SBS_FPUIMR FPU_IE_1   LL_SBS_IsEnabledFPUIT \n
  *  SBS_FPUIMR FPU_IE_2   LL_SBS_IsEnabledFPUIT \n
  *  SBS_FPUIMR FPU_IE_3   LL_SBS_IsEnabledFPUIT \n
  *  SBS_FPUIMR FPU_IE_4   LL_SBS_IsEnabledFPUIT \n
  *  SBS_FPUIMR FPU_IE_5   LL_SBS_IsEnabledFPUIT
  * @param  floating_point This parameter can be one of the following values:
  *         @arg @ref LL_SBS_IT_FPU_IOC
  *         @arg @ref LL_SBS_IT_FPU_DZC
  *         @arg @ref LL_SBS_IT_FPU_UFC
  *         @arg @ref LL_SBS_IT_FPU_OFC
  *         @arg @ref LL_SBS_IT_FPU_IDC
  *         @arg @ref LL_SBS_IT_FPU_IXC
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SBS_IsEnabledFPUIT(uint32_t floating_point)
{
  return ((READ_BIT(SBS->FPUIMR, floating_point) == floating_point) ? 1UL : 0UL);
}

/**
  * @brief  Enable Floating Point Unit Invalid operation Interrupt
  * @rmtoll
  *  FPUIMR     FPU_IE_0      LL_SBS_EnableIT_FPU_IOC
  */
__STATIC_INLINE void LL_SBS_EnableIT_FPU_IOC(void)
{
  SET_BIT(SBS->FPUIMR, SBS_FPUIMR_FPU_IE_0);
}

/**
  * @brief  Enable Floating Point Unit Divide-by-zero Interrupt
  * @rmtoll
  *  FPUIMR     FPU_IE_1      LL_SBS_EnableIT_FPU_DZC
  */
__STATIC_INLINE void LL_SBS_EnableIT_FPU_DZC(void)
{
  SET_BIT(SBS->FPUIMR, SBS_FPUIMR_FPU_IE_1);
}

/**
  * @brief  Enable Floating Point Unit Underflow Interrupt
  * @rmtoll
  *  FPUIMR     FPU_IE_2      LL_SBS_EnableIT_FPU_UFC
  */
__STATIC_INLINE void LL_SBS_EnableIT_FPU_UFC(void)
{
  SET_BIT(SBS->FPUIMR, SBS_FPUIMR_FPU_IE_2);
}

/**
  * @brief  Enable Floating Point Unit Overflow Interrupt
  * @rmtoll
  *  FPUIMR     FPU_IE_3      LL_SBS_EnableIT_FPU_OFC
  */
__STATIC_INLINE void LL_SBS_EnableIT_FPU_OFC(void)
{
  SET_BIT(SBS->FPUIMR, SBS_FPUIMR_FPU_IE_3);
}

/**
  * @brief  Enable Floating Point Unit Input denormal Interrupt
  * @rmtoll
  *  FPUIMR     FPU_IE_4      LL_SBS_EnableIT_FPU_IDC
  */
__STATIC_INLINE void LL_SBS_EnableIT_FPU_IDC(void)
{
  SET_BIT(SBS->FPUIMR, SBS_FPUIMR_FPU_IE_4);
}

/**
  * @brief  Enable Floating Point Unit Inexact Interrupt
  * @rmtoll
  *  FPUIMR     FPU_IE_5      LL_SBS_EnableIT_FPU_IXC
  */
__STATIC_INLINE void LL_SBS_EnableIT_FPU_IXC(void)
{
  SET_BIT(SBS->FPUIMR, SBS_FPUIMR_FPU_IE_5);
}

/**
  * @brief  Disable Floating Point Unit Invalid operation Interrupt
  * @rmtoll
  *  FPUIMR     FPU_IE_0      LL_SBS_DisableIT_FPU_IOC
  */
__STATIC_INLINE void LL_SBS_DisableIT_FPU_IOC(void)
{
  CLEAR_BIT(SBS->FPUIMR, SBS_FPUIMR_FPU_IE_0);
}

/**
  * @brief  Disable Floating Point Unit Divide-by-zero Interrupt
  * @rmtoll
  *  FPUIMR      FPU_IE_1      LL_SBS_DisableIT_FPU_DZC
  */
__STATIC_INLINE void LL_SBS_DisableIT_FPU_DZC(void)
{
  CLEAR_BIT(SBS->FPUIMR, SBS_FPUIMR_FPU_IE_1);
}

/**
  * @brief  Disable Floating Point Unit Underflow Interrupt
  * @rmtoll
  *  FPUIMR     FPU_IE_2      LL_SBS_DisableIT_FPU_UFC
  */
__STATIC_INLINE void LL_SBS_DisableIT_FPU_UFC(void)
{
  CLEAR_BIT(SBS->FPUIMR, SBS_FPUIMR_FPU_IE_2);
}

/**
  * @brief  Disable Floating Point Unit Overflow Interrupt
  * @rmtoll
  *  FPUIMR     FPU_IE_3      LL_SBS_DisableIT_FPU_OFC
  */
__STATIC_INLINE void LL_SBS_DisableIT_FPU_OFC(void)
{
  CLEAR_BIT(SBS->FPUIMR, SBS_FPUIMR_FPU_IE_3);
}

/**
  * @brief  Disable Floating Point Unit Input denormal Interrupt
  * @rmtoll
  *  FPUIMR     FPU_IE_4      LL_SBS_DisableIT_FPU_IDC
  */
__STATIC_INLINE void LL_SBS_DisableIT_FPU_IDC(void)
{
  CLEAR_BIT(SBS->FPUIMR, SBS_FPUIMR_FPU_IE_4);
}

/**
  * @brief  Disable Floating Point Unit Inexact Interrupt
  * @rmtoll
  *  FPUIMR     FPU_IE_5      LL_SBS_DisableIT_FPU_IXC
  */
__STATIC_INLINE void LL_SBS_DisableIT_FPU_IXC(void)
{
  CLEAR_BIT(SBS->FPUIMR, SBS_FPUIMR_FPU_IE_5);
}

/**
  * @brief  Check if Floating Point Unit Invalid operation Interrupt source is enabled or disabled.
  * @rmtoll
  *  FPUIMR     FPU_IE_0      LL_SBS_IsEnabledIT_FPU_IOC
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SBS_IsEnabledIT_FPU_IOC(void)
{
  return ((READ_BIT(SBS->FPUIMR, SBS_FPUIMR_FPU_IE_0) == SBS_FPUIMR_FPU_IE_0) ? 1UL : 0UL);
}

/**
  * @brief  Check if Floating Point Unit Divide-by-zero Interrupt source is enabled or disabled.
  * @rmtoll
  *  FPUIMR     FPU_IE_1      LL_SBS_IsEnabledIT_FPU_DZC
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SBS_IsEnabledIT_FPU_DZC(void)
{
  return ((READ_BIT(SBS->FPUIMR, SBS_FPUIMR_FPU_IE_1) == SBS_FPUIMR_FPU_IE_1) ? 1UL : 0UL);
}

/**
  * @brief  Check if Floating Point Unit Underflow Interrupt source is enabled or disabled.
  * @rmtoll
  *  FPUIMR     FPU_IE_2      LL_SBS_IsEnabledIT_FPU_UFC
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SBS_IsEnabledIT_FPU_UFC(void)
{
  return ((READ_BIT(SBS->FPUIMR, SBS_FPUIMR_FPU_IE_2) == SBS_FPUIMR_FPU_IE_2) ? 1UL : 0UL);
}

/**
  * @brief  Check if Floating Point Unit Overflow Interrupt source is enabled or disabled.
  * @rmtoll
  *  FPUIMR     FPU_IE_3      LL_SBS_IsEnabledIT_FPU_OFC
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SBS_IsEnabledIT_FPU_OFC(void)
{
  return ((READ_BIT(SBS->FPUIMR, SBS_FPUIMR_FPU_IE_3) == SBS_FPUIMR_FPU_IE_3) ? 1UL : 0UL);
}

/**
  * @brief  Check if Floating Point Unit Input denormal Interrupt source is enabled or disabled.
  * @rmtoll
  *  FPUIMR FPU_IE_4      LL_SBS_IsEnabledIT_FPU_IDC
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SBS_IsEnabledIT_FPU_IDC(void)
{
  return ((READ_BIT(SBS->FPUIMR, SBS_FPUIMR_FPU_IE_4) == SBS_FPUIMR_FPU_IE_4) ? 1UL : 0UL);
}

/**
  * @brief  Check if Floating Point Unit Inexact Interrupt source is enabled or disabled.
  * @rmtoll
  *  FPUIMR FPU_IE_5      LL_SBS_IsEnabledIT_FPU_IXC
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SBS_IsEnabledIT_FPU_IXC(void)
{
  return ((READ_BIT(SBS->FPUIMR, SBS_FPUIMR_FPU_IE_5) == SBS_FPUIMR_FPU_IE_5) ? 1UL : 0UL);
}

/**
  * @}
  */

/** @defgroup SBS_LL_EF_ERASE_MEMORIE_STATUS SBS ERASE MEMORIES STATUS
  * @{
  */

/**
  * @brief  Clear Status of End of Erase for ICACHE RAMs
  * @rmtoll
  *  MESR   IPMEE    LL_SBS_ClearFlag_IPMEE
  */
__STATIC_INLINE void LL_SBS_ClearFlag_IPMEE(void)
{
  SET_BIT(SBS->MESR, SBS_MESR_IPMEE);
}

/**
  * @brief  Get Status of End of Erase for ICACHE RAM
  * @rmtoll
  *  MESR   IPMEE    LL_SBS_IsActiveFlag_IPEE
  * @retval retrieve the state of the IPMEE flag (1U or 0U).
  */
__STATIC_INLINE uint32_t LL_SBS_IsActiveFlag_IPMEE(void)
{
  return ((READ_BIT(SBS->MESR, SBS_MESR_IPMEE) == SBS_MESR_IPMEE) ? 1UL : 0UL);
}

/**
  * @brief  Clear Status of End of Erase after reset for SRAM2 and ICACHE RAMs
  * @rmtoll
  *  MESR   MCLR    LL_SBS_ClearFlag_MCLR
  */
__STATIC_INLINE void LL_SBS_ClearFlag_MCLR(void)
{
  SET_BIT(SBS->MESR, SBS_MESR_MCLR);
}

/**
  * @brief  Get Status of End of Erase after reset for SRAM2 and ICACHE RAMs
  * @rmtoll
  *  MESR   MCLR    LL_SBS_IsActiveFlag_MCLR
  * @retval retrieve the state of the MCLR flag (1U or 0U).
  */
__STATIC_INLINE uint32_t LL_SBS_IsActiveFlag_MCLR(void)
{
  return ((READ_BIT(SBS->MESR, SBS_MESR_MCLR) == SBS_MESR_MCLR) ? 1UL : 0UL);
}

/**
  * @}
  */

/** @defgroup LL_SBS_EF_COMPENSATION Compensation Cell Control
  * @{
  */

/**
  * @brief  Set the compensation cell code.
  * @rmtoll
  *  CCCSR    CSx x= [1]  LL_SBS_SetCompensationCellCodeSrc
  * @param  comp_cell This parameter can be the following values:
  *         @arg @ref LL_SBS_CCELL_VDDIO
  * @param  code_source: This parameter can be one of the following values:
  *         @arg @ref LL_SBS_CCELL_CODE_DEFAULT
  *         @arg @ref LL_SBS_CCELL_CODE_CUSTOM
  */
__STATIC_INLINE void LL_SBS_SetCompensationCellCodeSrc(uint32_t comp_cell, uint32_t code_source)
{
  ATOMIC_MODIFY_REG(SBS->CCCSR, (comp_cell << 1U), (code_source * (comp_cell << 1U)));
}

/**
  * @brief  Get the compensation cell code.
  * @rmtoll
  *  SBS_CCCSR    CSx x= [1]    LL_SBS_GetCompensationCellCodeSrc
  * @param  comp_cell This parameter can be the following values:
  *         @arg @ref LL_SBS_CCELL_VDDIO
  * @retval Returned value can be one of the following values:
  *   @arg LL_SBS_CCELL_CODE_DEFAULT : Selected Code is from the cell (available in the SBS_CCVALR)
  *   @arg LL_SBS_CCELL_CODE_CUSTOM  : Selected Code is from the SBS compensation
  *                                           cell software code register (SBS_CCSWCR)
  */
__STATIC_INLINE uint32_t LL_SBS_GetCompensationCellCodeSrc(uint32_t comp_cell)
{
  return (READ_BIT(SBS->CCCSR, (SBS_CCCSR_CS1 << POSITION_VAL(comp_cell))) >> POSITION_VAL(comp_cell << 1U));
}

/**
  * @brief  Set the compensation cell code selection of GPIO supplied by VDD
  * @rmtoll
  *  CCCSR   CS1    LL_SBS_SetVddIOCompensationCellCodeSource
  * @param  code_source: Select the code to be applied for the Vdd compensation cell
  *   This parameter can be one of the following values:
  *   @arg LL_SBS_CCELL_VDDIO_DEFAULT_CODE : Select Code from the cell (available in the SBS_CCVALR)
  *   @arg LL_SBS_CCELL_VDDIO_CUSTOM_CODE  : Select Code from the SBS compensation cell
  *                                                  software code register (SBS_CCSWCR)
  */
__STATIC_INLINE void LL_SBS_SetVddIOCompensationCellCodeSource(uint32_t code_source)
{
  ATOMIC_MODIFY_REG(SBS->CCCSR, SBS_CCCSR_CS1, code_source);
}

/**
  * @brief  Get the compensation cell code selection of GPIO supplied by VDD
  * @rmtoll
  *  CCCSR   CS1    LL_SBS_GetVddIOCompensationCellCodeSource
  * @retval Returned value can be one of the following values:
  *   @arg LL_SBS_CCELL_VDDIO_DEFAULT_CODE : Selected Code is from the cell (available in the SBS_CCVALR)
  *   @arg LL_SBS_CCELL_VDDIO_CUSTOM_CODE: Selected Code is from the SBS compensation cell
  *                                            software code register (SBS_CCSWCR)
  */
__STATIC_INLINE uint32_t LL_SBS_GetVddIOCompensationCellCodeSource(void)
{
  return (uint32_t)(READ_BIT(SBS->CCCSR, SBS_CCCSR_CS1));
}

/**
  * @brief  Enable the Compensation Cell.
  * @rmtoll
  *  CCCSR   ENX   X[1]    LL_SBS_EnableCompensationCell
  * @param  comp_cell This parameter can be one or a combination of the following values:
  *         @arg @ref LL_SBS_CCELL_VDDIO
  */
__STATIC_INLINE void LL_SBS_EnableCompensationCell(uint32_t comp_cell)
{
  ATOMIC_SET_BIT(SBS->CCCSR, comp_cell);
}

/**
  * @brief  Disable the Compensation Cell.
  * @rmtoll
  *  CCCSR   ENX   X[1]    LL_SBS_DisableCompensationCell
  * @param  comp_cell This parameter can be one or a combination of the following values:
  *         @arg @ref LL_SBS_CCELL_VDDIO
  */
__STATIC_INLINE void LL_SBS_DisableCompensationCell(uint32_t comp_cell)
{
  ATOMIC_CLEAR_BIT(SBS->CCCSR, comp_cell);
}

/**
  * @brief  Check if the Compensation Cell is enable
  * @rmtoll
  *  CCCSR   ENx x=[1]    LL_SBS_IsEnabledCompensationCell
  * @param  comp_cell This parameter can be one of the following values:
  *         @arg @ref LL_SBS_CCELL_VDDIO
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SBS_IsEnabledCompensationCell(uint32_t comp_cell)
{
  return ((READ_BIT(SBS->CCCSR, comp_cell) == comp_cell) ? 1U : 0U);
}

/**
  * @brief  Enable the Compensation Cell of GPIO supplied by VDD
  * @rmtoll
  *  CCCSR   EN1    LL_SBS_EnableVddIOCompensationCell
  */
__STATIC_INLINE void LL_SBS_EnableVddIOCompensationCell(void)
{
  ATOMIC_SET_BIT(SBS->CCCSR, SBS_CCCSR_EN1);
}

/**
  * @brief  Disable the Compensation Cell of GPIO supplied by VDD
  * @rmtoll
  *  CCCSR   EN1    LL_SBS_DisableVddIOCompensationCell
  */
__STATIC_INLINE void LL_SBS_DisableVddIOCompensationCell(void)
{
  ATOMIC_CLEAR_BIT(SBS->CCCSR, SBS_CCCSR_EN1);
}

/**
  * @brief  Check if the Compensation Cell of GPIO supplied by VDD is enable
  * @rmtoll
  *  CCCSR   EN1    LL_SBS_IsEnabledVddIOCompensationCell
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SBS_IsEnabledVddIOCompensationCell(void)
{
  return ((READ_BIT(SBS->CCCSR, SBS_CCCSR_EN1) == SBS_CCCSR_EN1) ? 1UL : 0UL);
}

/**
  * @brief  Get the PMOS transistor of the compensation cell value
  * @rmtoll
  *  CCVALR  APSRCx x=[1]   LL_SBS_GetPMOSCompensationCellValue
  * @param  comp_cell This parameter can be one of the following values:
  *         @arg @ref LL_SBS_CCELL_VDDIO
  * @retval Returned value of the PMOS compensation cell
  */
__STATIC_INLINE uint32_t LL_SBS_GetPMOSCompensationCellValue(uint32_t comp_cell)
{
  return (uint32_t)(READ_BIT(SBS->CCVALR, ((SBS_CCVALR_APSRC1 << (POSITION_VAL(comp_cell << 1U) * 4U))))
                    >> (POSITION_VAL(comp_cell << 1U) * 4U));
}

/**
  * @brief  Get the NMOS transistor of the compensation cell value
  * @rmtoll
  *  CCVALR    ANSRC1x x=[1]   LL_SBS_GetNMOSCompensationCellValue
  * @param  comp_cell This parameter can be one of the following values:
  *         @arg @ref LL_SBS_CCELL_VDDIO
  * @retval Returned value of the NMOS compensation cell
  */
__STATIC_INLINE uint32_t LL_SBS_GetNMOSCompensationCellValue(uint32_t comp_cell)
{
  return (uint32_t)(READ_BIT(SBS->CCVALR, ((SBS_CCVALR_ANSRC1 << (POSITION_VAL(comp_cell) * 4U))))
                    >> (POSITION_VAL(comp_cell) * 4U));
}

/**
  * @brief  Get the compensation cell value of the GPIO PMOS transistor supplied by VDD
  * @rmtoll
  *  CCVALR    APSRC1   LL_SBS_GetPMOSVddIOCompensationCellValue
  * @retval Returned value is the PMOS compensation cell
  */
__STATIC_INLINE uint32_t LL_SBS_GetPMOSVddIOCompensationCellValue(void)
{
  return (uint32_t)(READ_BIT(SBS->CCVALR, SBS_CCVALR_APSRC1));
}

/**
  * @brief  Get the compensation cell value of the GPIO NMOS transistor supplied by VDD
  * @rmtoll
  *  CCVALR    ANSRC1   LL_SBS_GetNMOSVddIOCompensationCellValue
  * @retval Returned value is the NMOS compensation cell
  */
__STATIC_INLINE uint32_t LL_SBS_GetNMOSVddIOCompensationCellValue(void)
{
  return (uint32_t)(READ_BIT(SBS->CCVALR, SBS_CCVALR_ANSRC1));
}

/**
  * @brief  Set the compensation cell code of PMOS transistor
  * @note   This code is applied to the PMOS compensation cell when the CSx x=[1] bits of the SBS_CCCSR is set
  * @rmtoll
  *  CCSWCR    APSRC1   LL_SBS_SetPMOSCompensationCellCode
  * @param  comp_cell This parameter can be one of the following values:
  *         @arg @ref LL_SBS_CCELL_VDDIO
  * @param  pmos_code PMOS compensation code
  */
__STATIC_INLINE void LL_SBS_SetPMOSCompensationCellCode(uint32_t comp_cell, uint32_t pmos_code)
{
  ATOMIC_MODIFY_REG(SBS->CCSWCR, (SBS_CCSWCR_SW_APSRC1 << (POSITION_VAL(comp_cell << 1U) * 4U)),
                    (pmos_code << (POSITION_VAL(comp_cell << 1U) * 4U)));
}

/**
  * @brief  Get the compensation cell code of PMOS transistor
  * @note   This code is applied to the PMOS compensation cell when the CSx x=[1] bits of the SBS_CCCSR is set
  * @rmtoll
  *  CCSWCR    APSRC1   LL_SBS_GetPMOSCompensationCellCode
  * @param  comp_cell This parameter can be one of the following values:
  *         @arg @ref LL_SBS_CCELL_VDDIO
  * @retval Returned value of the PMOS compensation cell
  */
__STATIC_INLINE uint32_t LL_SBS_GetPMOSCompensationCellCode(uint32_t comp_cell)
{
  return (READ_BIT(SBS->CCSWCR, (SBS_CCSWCR_SW_APSRC1 << (POSITION_VAL(comp_cell << 1U) * 4U))));
}

/**
  * @brief  Set the compensation cell code of NMOS transistor
  * @note   This code is applied to the PMOS compensation cell when the CSx x=[1] bits of the SBS_CCCSR is set
  * @rmtoll
  *  CCSWCR    ANSRC1   LL_SBS_SetNMOSCompensationCellCode
  * @param  comp_cell This parameter can be one of the following values:
  *         @arg @ref LL_SBS_CCELL_VDDIO
  * @param  nmos_code PMOS compensation code
  */
__STATIC_INLINE void LL_SBS_SetNMOSCompensationCellCode(uint32_t comp_cell, uint32_t nmos_code)
{
  ATOMIC_MODIFY_REG(SBS->CCSWCR, (SBS_CCSWCR_SW_ANSRC1 << (POSITION_VAL(comp_cell) * 4U)),
                    (nmos_code << (POSITION_VAL(comp_cell) * 4U)));
}

/**
  * @brief  Get the NMOS transistor of the compensation cell value
  * @note   This code is applied to the NMOS compensation cell when the CSx x=[1] bits of the SBS_CCCSR is set
  * @rmtoll
  *  CCSWCR    ANSRC1   LL_SBS_GetNMOSCompensationCellCode
  * @param  comp_cell This parameter can be one of the following values:
  *         @arg @ref LL_SBS_CCELL_VDDIO
  * @retval Returned value of the NMOS compensation cell
  */
__STATIC_INLINE uint32_t LL_SBS_GetNMOSCompensationCellCode(uint32_t comp_cell)
{
  return (READ_BIT(SBS->CCSWCR, (SBS_CCSWCR_SW_ANSRC1 << (POSITION_VAL(comp_cell) * 4U))));
}

/**
  * @brief  Set the compensation cell code of the GPIO PMOS and NMOS transistor supplied by VDD
  * @rmtoll
  *  CCSWCR    ANSRC1  LL_SBS_SetxMOSVddIOCompensationCellCode \n
  *  CCSWCR    APSRC1  LL_SBS_SetxMOSVddIOCompensationCellCode
  * @param  pmos_code PMOS compensation code
  *         This code is applied to the PMOS compensation cell when the CS1 bit of the
  *         SBS_CCCSR is set
  * @param  nmos_code NMOS compensation code
  *         This code is applied to the NMOS compensation cell when the CS1 bit of the
  *         SBS_CCCSR is set
  */
__STATIC_INLINE void LL_SBS_SetxMOSVddIOCompensationCellCode(uint32_t pmos_code, uint32_t nmos_code)
{
  MODIFY_REG(SBS->CCSWCR, (SBS_CCSWCR_SW_APSRC1 | SBS_CCSWCR_SW_ANSRC1), ((pmos_code << SBS_CCSWCR_SW_APSRC1_Pos) | \
                                                                          (nmos_code << SBS_CCSWCR_SW_ANSRC1_Pos)));
}

/**
  * @brief  Set the compensation cell code of the GPIO PMOS transistor supplied by VDD
  * @rmtoll
  *  CCSWCR    APSRC1  LL_SBS_SetPMOSVddIOCompensationCellCode
  * @param  pmos_code PMOS compensation code
  *         This code is applied to the PMOS compensation cell when the CS1 bit of the
  *         SBS_CCCSR is set
  */
__STATIC_INLINE void LL_SBS_SetPMOSVddIOCompensationCellCode(uint32_t pmos_code)
{
  MODIFY_REG(SBS->CCSWCR, SBS_CCSWCR_SW_APSRC1, pmos_code << SBS_CCSWCR_SW_APSRC1_Pos);
}

/**
  * @brief  Get the compensation cell code of the GPIO PMOS transistor supplied by VDD
  * @rmtoll
  *  CCSWCR    APSRC1   LL_SBS_GetPMOSVddIOCompensationCellCode
  * @retval Returned value is the PMOS compensation cell
  */
__STATIC_INLINE uint32_t LL_SBS_GetPMOSVddIOCompensationCellCode(void)
{
  return (uint32_t)(READ_BIT(SBS->CCSWCR, SBS_CCSWCR_SW_APSRC1));
}

/**
  * @brief  Set the compensation cell code of the GPIO NMOS transistor supplied by VDD
  * @rmtoll
  *  CCSWCR    APSRC1  LL_SBS_SetNMOSVddIOCompensationCellCode
  * @param  nmos_code NMOS compensation code
  *         This code is applied to the NMOS compensation cell when the CS1 bit of the
  *         SBS_CCCSR is set
  */
__STATIC_INLINE void LL_SBS_SetNMOSVddIOCompensationCellCode(uint32_t nmos_code)
{
  MODIFY_REG(SBS->CCSWCR, SBS_CCSWCR_SW_ANSRC1, nmos_code << SBS_CCSWCR_SW_ANSRC1_Pos);
}

/**
  * @brief  Get the compensation cell code of the GPIO NMOS transistor supplied by VDD
  * @rmtoll
  *  CCSWCR    ANSRC1   LL_SBS_GetNMOSVddIOCompensationCellCode
  * @retval Returned value is the Vdd compensation cell code for NMOS transistors
  */
__STATIC_INLINE uint32_t LL_SBS_GetNMOSVddIOCompensationCellCode(void)
{
  return (uint32_t)(READ_BIT(SBS->CCSWCR, SBS_CCSWCR_SW_ANSRC1));
}

/**
  * @brief  Get Compensation Cell ready Flag of GPIO supplied by VDD
  * @rmtoll
  *  CCCSR   RDY1   LL_SBS_IsActiveFlag_RDY1
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SBS_IsActiveFlag_RDY1(void)
{
  return ((READ_BIT(SBS->CCCSR, SBS_CCCSR_RDY1) == (SBS_CCCSR_RDY1)) ? 1UL : 0UL);
}

/**
  * @}
  */

/** @defgroup LL_SBS_EF_TIM_Break_Management TIM Break Management
  * @{
  */

/**
  * @brief  Set connections to TIM1/8/15/16/17 break inputs.
  * @rmtoll
  *  SBS_CFGR2 CLL          LL_SBS_EnableTIMBreakInputs \n
  *  SBS_CFGR2 SEL          LL_SBS_EnableTIMBreakInputs \n
  *  SBS_CFGR2 PVDL         LL_SBS_EnableTIMBreakInputs \n
  *  SBS_CFGR2 ECCL         LL_SBS_EnableTIMBreakInputs
  * @param  break_input This parameter can be one or a combination of the following values:
  *         @arg @ref LL_SBS_FLASH_ECC_DOUBLE_ERROR
  *         @arg @ref LL_SBS_PVD
  *         @arg @ref LL_SBS_SRAM_ECC_DOUBLE_ERROR
  *         @arg @ref LL_SBS_LOCKUP_OUT
  */
__STATIC_INLINE void LL_SBS_EnableTIMBreakInputs(uint32_t break_input)
{
  SET_BIT(SBS->CFGR2, break_input);
}

/**
  * @brief  Clear connections to TIM1/8/15/16/17 break inputs.
  * @rmtoll
  *  SBS_CFGR2   ECCL    LL_SBS_DisableTIMBreakInputs
  * @param  break_input This parameter can be one or a combination of the following values:
  *         @arg @ref LL_SBS_SRAM_ECC_DOUBLE_ERROR
  */
__STATIC_INLINE void LL_SBS_DisableTIMBreakInputs(uint32_t break_input)
{
  CLEAR_BIT(SBS->CFGR2, break_input);
}

/**
  * @brief  Get connections to TIM1/8/15/16/17 break inputs.
  * @rmtoll
  *  SBS_CFGR2   CLL     LL_SBS_IsEnabledTIMBreakInputs \n
  *  SBS_CFGR2   SPL     LL_SBS_IsEnabledTIMBreakInputs \n
  *  SBS_CFGR2   PVDL    LL_SBS_IsEnabledTIMBreakInputs \n
  *  SBS_CFGR2   ECCL    LL_SBS_IsEnabledTIMBreakInputs
  * @param  break_input This parameter can be one of the following values:
  *         @arg @ref LL_SBS_FLASH_ECC_DOUBLE_ERROR
  *         @arg @ref LL_SBS_PVD
  *         @arg @ref LL_SBS_SRAM_ECC_DOUBLE_ERROR
  *         @arg @ref LL_SBS_LOCKUP_OUT
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SBS_IsEnabledTIMBreakInputs(uint32_t break_input)
{
  return ((READ_BIT(SBS->CFGR2, break_input) == (break_input)) ? 1UL : 0UL);
}

/**
  * @}
  */

/** @defgroup LL_SBS_EF_Lock_Management Lock Management
  * @{
  */

/**
  * @brief  Lock of SBS CPU registers.
  *         Lock(s) cleared only at system reset
  * @rmtoll CLCKR       LOCKVTOR     LL_SBS_CPU_LockRegisters\n
  *         CLCKR       LOCKMPU      LL_SBS_CPU_LockRegisters
  * @param  core_regs
  *         This parameter can be one of the following values :
  *          @arg @ref LL_SBS_CPU_LOCK_VTOR
  *          @arg @ref LL_SBS_CPU_LOCK_MPU
  *          @arg @ref LL_SBS_CPU_LOCK_ALL
  * @retval None
  */
__STATIC_INLINE void LL_SBS_CPU_LockRegisters(uint32_t core_regs)
{
  SBS->CLCKR = core_regs;
}

/**
  * @brief  Check if the SBS CPU register is locked.
  * @rmtoll CLCKR     LOCKVTOR     LL_SBS_CPU_IsLockedRegisters\n
  *         CLCKR     LOCKMPU      LL_SBS_CPU_IsLockedRegisters
  * @retval the return value can be one of the following values :
  *          @arg @ref LL_SBS_CPU_LOCK_VTOR
  *          @arg @ref LL_SBS_CPU_LOCK_MPU
  */
__STATIC_INLINE uint32_t LL_SBS_CPU_IsLockedRegisters(uint32_t core_regs)
{
  return ((READ_BIT(SBS->CLCKR, core_regs) == (core_regs)) ? 1UL : 0UL);
}

/**
  * @}
  */

/** @defgroup LL_SBS_EF_FLASH_Management FLASH Management
  * @{
  */

/**
  * @brief  Disable the NMI in case of double ECC error in FLASH Interface.
  * @rmtoll
  *  ECCNMIR     SBS_ECCNMIR_ECCNMI_MASK_EN      LL_SBS_FLASH_DisableECCNMI
  */
__STATIC_INLINE  void LL_SBS_FLASH_DisableECCNMI(void)
{
  SET_BIT(SBS->ECCNMIR, SBS_ECCNMIR_ECCNMI_MASK_EN);
}

/**
  * @brief  Enable the NMI in case of double ECC error in FLASH Interface.
  * @rmtoll
  *  ECCNMIR     SBS_ECCNMIR_ECCNMI_MASK_EN      LL_SBS_FLASH_EnableECCNMI
  */
__STATIC_INLINE  void LL_SBS_FLASH_EnableECCNMI(void)
{
  CLEAR_BIT(SBS->ECCNMIR, SBS_ECCNMIR_ECCNMI_MASK_EN);
}

/**
  * @brief  Check if the NMI is Disabled in case of double ECC error in FLASH Interface.
  * @rmtoll
  *  ECCNMIR     SBS_ECCNMIR_ECCNMI_MASK_EN      LL_SBS_FLASH_IsEnabledECCNMI
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE  uint32_t LL_SBS_FLASH_IsEnabledECCNMI(void)
{
  return ((READ_BIT(SBS->ECCNMIR, SBS_ECCNMIR_ECCNMI_MASK_EN) == SBS_ECCNMIR_ECCNMI_MASK_EN) ? 0UL : 1UL);
}

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

#endif /* STM32C5XX_LL_SBS_H */
