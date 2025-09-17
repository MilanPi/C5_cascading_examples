/**
  ******************************************************************************
  * @file    stm32c5xx.h
  * @author  GPM Application Team
  * @brief   CMSIS STM32C5xx Device Peripheral Access Layer Header File.
  *
  *          The file is the unique include file that the application programmer
  *          is using in the C source code, usually in main.c.
  *          This file allows to select the STM32C5xx device used in the target
  *          application.
  *
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

/** @addtogroup CMSIS
  * @{
  */

/** @addtogroup stm32c5xx
  * @{
  */

#ifndef STM32C5XX_H
#define STM32C5XX_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#if defined(USE_EXTERNAL_ENV)
#include "stm32_external_env.h"
#endif /* USE_EXTERNAL_ENV */

/** @addtogroup Library_configuration_section
  * @{
  */

/**
  * @brief STM32 Family
  */
#if !defined (STM32C5)
#define STM32C5
#endif /* STM32C5 */

/**
  * @brief STM32C5xx CMSIS Device version number 2.0.0
  */
#define STM32C5_CMSIS_VERSION_MAIN   (2) /*!< [31:24] main version */
#define STM32C5_CMSIS_VERSION_SUB1   (0) /*!< [23:16] sub1 version */
#define STM32C5_CMSIS_VERSION_SUB2   (0) /*!< [15:8]  sub2 version */
#define STM32C5_CMSIS_VERSION_RC     (0) /*!< [7:0]  release candidate */
#define STM32C5_CMSIS_VERSION        ((STM32C5_CMSIS_VERSION_MAIN << 24U)\
                                        |(STM32C5_CMSIS_VERSION_SUB1 << 16U)\
                                        |(STM32C5_CMSIS_VERSION_SUB2 << 8U )\
                                        |(STM32C5_CMSIS_VERSION_RC))

/**
  * @}
  */

/** @addtogroup Device_Included
  * @{
  */

#if defined(STM32C531xx)
#include "stm32c531xx.h"
#elif defined(STM32C532xx)
#include "stm32c532xx.h"
#elif defined(STM32C542xx)
#include "stm32c542xx.h"
#elif defined(STM32C551xx)
#include "stm32c551xx.h"
#elif defined(STM32C552xx)
#include "stm32c552xx.h"
#elif defined(STM32C562xx)
#include "stm32c562xx.h"
#elif defined(STM32C591xx)
#include "stm32c591xx.h"
#elif defined(STM32C593xx)
#include "stm32c593xx.h"
#elif defined(STM32C5A3xx)
#include "stm32c5a3xx.h"
#else
#error "Please select first the target STM32C5xx device used in your application"
#endif

/**
  * @}
  */

/** @addtogroup Exported_types
  * @{
  */

/* Legacy enumerations */

typedef enum
{
  RESET = 0,
  SET = !RESET
} FlagStatus, ITStatus;

typedef enum
{
  DISABLE = 0,
  ENABLE = !DISABLE
} FunctionalState;
#define IS_FUNCTIONAL_STATE(STATE) (((STATE) == DISABLE) || ((STATE) == ENABLE))

typedef enum
{
  SUCCESS = 0,
  ERROR = !SUCCESS
} ErrorStatus;

/**
  * @}
  */

/** @addtogroup Exported_macros
  * @{
  */

#define STM32_POSITION_VAL(VAL)     (__CLZ(__RBIT(VAL)))

#define STM32_UNUSED(x) ((void)(x))

#define STM32_SET_BIT(REG, BIT)     ((REG) |= (BIT))

#define STM32_CLEAR_BIT(REG, BIT)   ((REG) &= ~(BIT))

#define STM32_READ_BIT(REG, BIT)    ((REG) & (BIT))

#define STM32_CLEAR_REG(REG)        ((REG) = (0x0))

#define STM32_WRITE_REG(REG, VAL)   ((REG) = (VAL))

#define STM32_READ_REG(REG)         ((REG))

#define STM32_MODIFY_REG(REG, CLEARMASK, SETMASK)  WRITE_REG((REG), (((READ_REG(REG)) & (~(CLEARMASK))) | (SETMASK)))

#define STM32_IS_BIT_SET(REG, BIT)  (((REG) & (BIT)) == (BIT))

#define STM32_IS_BIT_CLR(REG, BIT)  (((REG) & (BIT)) == 0U)

/* Use of CMSIS compiler intrinsics for register exclusive access */

/* Atomic 32-bit register access macro to set one or several bits */
#define STM32_ATOMIC_SET_BIT_32(REG, BIT)                    \
  do {                                                       \
    uint32_t val;                                            \
    do {                                                     \
      val = __LDREXW((__IO uint32_t *)&(REG)) | (BIT);       \
    } while ((__STREXW(val,(__IO uint32_t *)&(REG))) != 0U); \
  } while(0)

/* Atomic 32-bit register access macro to clear one or several bits */
#define STM32_ATOMIC_CLEAR_BIT_32(REG, BIT)                  \
  do {                                                       \
    uint32_t val;                                            \
    do {                                                     \
      val = __LDREXW((__IO uint32_t *)&(REG)) & ~(BIT);      \
    } while ((__STREXW(val,(__IO uint32_t *)&(REG))) != 0U); \
  } while(0)

/* Atomic 32-bit register access macro to clear and set one or several bits */
#define STM32_ATOMIC_MODIFY_REG_32(REG, CLEARMSK, SETMASK)                 \
  do {                                                                     \
    uint32_t val;                                                          \
    do {                                                                   \
      val = (__LDREXW((__IO uint32_t *)&(REG)) & ~(CLEARMSK)) | (SETMASK); \
    } while ((__STREXW(val,(__IO uint32_t *)&(REG))) != 0U);               \
  } while(0)

/* Atomic 16-bit register access macro to set one or several bits */
#define STM32_ATOMIC_SET_BIT_16(REG, BIT)                    \
  do {                                                       \
    uint16_t val;                                            \
    do {                                                     \
      val = __LDREXH((__IO uint16_t *)&(REG)) | (BIT);       \
    } while ((__STREXH(val,(__IO uint16_t *)&(REG))) != 0U); \
  } while(0)

/* Atomic 16-bit register access macro to clear one or several bits */
#define STM32_ATOMIC_CLEAR_BIT_16(REG, BIT)                  \
  do {                                                       \
    uint16_t val;                                            \
    do {                                                     \
      val = __LDREXH((__IO uint16_t *)&(REG)) & ~(BIT);      \
    } while ((__STREXH(val,(__IO uint16_t *)&(REG))) != 0U); \
  } while(0)

/* Atomic 16-bit register access macro to clear and set one or several bits */
#define STM32_ATOMIC_MODIFY_REG_16(REG, CLEARMSK, SETMASK)                 \
  do {                                                                     \
    uint16_t val;                                                          \
    do {                                                                   \
      val = (__LDREXH((__IO uint16_t *)&(REG)) & ~(CLEARMSK)) | (SETMASK); \
    } while ((__STREXH(val,(__IO uint16_t *)&(REG))) != 0U);               \
  } while(0)

/* Atomic 8-bit register access macro to set one or several bits */
#define STM32_ATOMIC_SET_BIT_8(REG, BIT)                    \
  do {                                                      \
    uint8_t val;                                            \
    do {                                                    \
      val = __LDREXB((__IO uint8_t *)&(REG)) | (BIT);       \
    } while ((__STREXB(val,(__IO uint8_t *)&(REG))) != 0U); \
  } while(0)

/* Atomic 8-bit register access macro to clear one or several bits */
#define STM32_ATOMIC_CLEAR_BIT_8(REG, BIT)                  \
  do {                                                      \
    uint8_t val;                                            \
    do {                                                    \
      val = __LDREXB((__IO uint8_t *)&(REG)) & ~(BIT);      \
    } while ((__STREXB(val,(__IO uint8_t *)&(REG))) != 0U); \
  } while(0)

/* Atomic 8-bit register access macro to clear and set one or several bits */
#define STM32_ATOMIC_MODIFY_REG_8(REG, CLEARMSK, SETMASK)                 \
  do {                                                                    \
    uint8_t val;                                                          \
    do {                                                                  \
      val = (__LDREXB((__IO uint8_t *)&(REG)) & ~(CLEARMSK)) | (SETMASK); \
    } while ((__STREXB(val,(__IO uint8_t *)&(REG))) != 0U);               \
  } while(0)

/* Legacy aliasing */
#define POSITION_VAL       STM32_POSITION_VAL
#define SET_BIT            STM32_SET_BIT
#define CLEAR_BIT          STM32_CLEAR_BIT
#define READ_BIT           STM32_READ_BIT
#define CLEAR_REG          STM32_CLEAR_REG
#define WRITE_REG          STM32_WRITE_REG
#define READ_REG           STM32_READ_REG
#define MODIFY_REG         STM32_MODIFY_REG
#define IS_BIT_SET         STM32_IS_BIT_SET
#define IS_BIT_CLR         STM32_IS_BIT_CLR
#define ATOMIC_SET_BIT     STM32_ATOMIC_SET_BIT_32
#define ATOMIC_CLEAR_BIT   STM32_ATOMIC_CLEAR_BIT_32
#define ATOMIC_MODIFY_REG  STM32_ATOMIC_MODIFY_REG_32
#define ATOMIC_SETH_BIT    STM32_ATOMIC_SET_BIT_16
#define ATOMIC_CLEARH_BIT  STM32_ATOMIC_CLEAR_BIT_16
#define ATOMIC_MODIFYH_REG STM32_ATOMIC_MODIFY_REG_16
#define ATOMIC_SETB_BIT    STM32_ATOMIC_SET_BIT_8
#define ATOMIC_CLEARB_BIT  STM32_ATOMIC_CLEAR_BIT_8
#define ATOMIC_MODIFYB_REG STM32_ATOMIC_MODIFY_REG_8

/**
  * @}
  */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* STM32C5XX_H */
/**
  * @}
  */

/**
  * @}
  */
