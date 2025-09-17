/**
  **********************************************************************************************************************
  * @file    stm32c5xx_ll_system.h
  * @author  GPAM Application Team
  * @brief   Header file of LL system module.
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
#ifndef STM32C5XX_LL_SYSTEM_H
#define STM32C5XX_LL_SYSTEM_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ----------------------------------------------------------------------------------------------------------*/
#include "stm32c5xx.h"

/** @addtogroup STM32C5xx_LL_Driver
  * @{
  */

/** @defgroup LL_SYSTEM LL system
  * @{
  */

/* Private constants -------------------------------------------------------------------------------------------------*/
/* Exported constants ------------------------------------------------------------------------------------------------*/

/** @defgroup SYSTEM_LL_Exported_Constants SYSTEM Exported Constants
  * @{
  */

/** @defgroup DEVICE_ID_PACKAGE Device package identification
  * @{
  */
#define LL_ID_PACKAGE_LQFP64           0x00000000U /*!< Package LQFP64   */
#define LL_ID_PACKAGE_LQFP100          0x00000002U /*!< Package LQFP100  */
#define LL_ID_PACKAGE_LQFP48           0x00000005U /*!< Package LQFP48   */
#define LL_ID_PACKAGE_UFQFPN32         0x00000009U /*!< Package UFQFPN32 */
#define LL_ID_PACKAGE_UFQFPN48         0x00000010U /*!< Package UFQFPN48 */
#define LL_ID_PACKAGE_LQFP80           0x00000012U /*!< Package LQFP80   */
#define LL_ID_PACKAGE_LQFP32           0x00000016U /*!< Package LQFP32   */
/**
  * @}
  */

/** @defgroup PACKAGE_MASK package data mask
  * @{
  */
#define LL_SYSTEM_PACKAGE_MASK 0x1FU /*!< Mask to get package data */
/**
  * @}
  */


/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

/** @defgroup LL_System_Exported_Functions LL system exported functions
  * @{
  */

/** @defgroup LL_System_Device_Identification Device identification (electronic signature)
  * @{
  */

/**
  * @brief  Get Word0 of the device unique identifier (UID based on 96 bits)
  * @retval UID[31:0]: X and Y coordinates on the wafer expressed in BCD format
  */
__STATIC_INLINE uint32_t LL_GetUID_Word0(void)
{
  return (uint32_t)(READ_REG(*((uint32_t *)UID_BASE)));
}

/**
  * @brief  Get Word1 of the device unique identifier (UID based on 96 bits)
  * @retval UID[63:32]: Wafer number (UID[39:32]) & LOT_NUM[23:0] (UID[63:40])
  */
__STATIC_INLINE uint32_t LL_GetUID_Word1(void)
{
  return (uint32_t)(READ_REG(*((uint32_t *)(UID_BASE + 4U))));
}

/**
  * @brief  Get Word2 of the device unique identifier (UID based on 96 bits)
  * @retval UID[95:64]: Lot number (ASCII encoded) - LOT_NUM[55:24]
  */
__STATIC_INLINE uint32_t LL_GetUID_Word2(void)
{
  return (uint32_t)(READ_REG(*((uint32_t *)(UID_BASE + 8U))));
}

/**
  * @brief  Get Package type
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ID_PACKAGE_QFN32
  *         @arg @ref LL_ID_PACKAGE_QFN48
  *         @arg @ref LL_ID_PACKAGE_LQFP32
  *         @arg @ref LL_ID_PACKAGE_LQFP48
  *         @arg @ref LL_ID_PACKAGE_LQFP64
  *         @arg @ref LL_ID_PACKAGE_LQFP80
  *         @arg @ref LL_ID_PACKAGE_LQFP100
  *         @arg @ref LL_ID_PACKAGE_VFQFPN68
  */
__STATIC_INLINE uint32_t LL_GetPackageType(void)
{
  return (uint32_t)(READ_REG(*((volatile uint16_t *)PACKAGE_BASE)) & LL_SYSTEM_PACKAGE_MASK);
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

#endif /* STM32C5XX_LL_SYSTEM_H */
