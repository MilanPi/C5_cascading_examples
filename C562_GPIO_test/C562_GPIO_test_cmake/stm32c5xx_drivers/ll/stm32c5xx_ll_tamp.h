/**
  ******************************************************************************
  * @file    stm32c5xx_ll_tamp.h
  * @author  GPM Application Team
  * @brief   Header file of TAMP LL module.
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
#ifndef STM32C5XX_LL_TAMP_H
#define STM32C5XX_LL_TAMP_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32c5xx.h"

/** @addtogroup STM32C5xx_LL_Driver
  * @{
  */

#if defined(TAMP)

/** @defgroup TAMP_LL TAMP
  * @{
  */

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
#define LL_POSITION_FIRST_ITAMP        TAMP_CR1_ITAMP3E_Pos
#define LL_POSITION_OFFSET_REG_ITAMP   16U
#define TAMP_CR2_CFG_MSK               (LL_TAMP_NOERASE_TAMPER_ALL \
                                        | LL_TAMP_ACTIVELEVEL_TAMP_ALL | LL_TAMP_MASK_TAMPER_ALL)

/* Private macros ------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
#define LL_TAMP_NUMBER_TAMPERS         3U /*!< Number of tampers */
#define LL_TAMP_POSITION_FIRST_MASKED  TAMP_CR2_TAMP1MSK_Pos /*!< Tamper first masked */
#define LL_TAMP_BACKUP_NB              TAMP_BACKUP_NB /*!< Backup registers number */

/** @defgroup TAMP_LL_EC_TAMPER  TAMPER
  * @{
  */
#define LL_TAMP_1                    TAMP_CR1_TAMP1E /*!< Tamper 1 input detection */
#define LL_TAMP_2                    TAMP_CR1_TAMP2E /*!< Tamper 2 input detection */
#define LL_TAMP_3                    TAMP_CR1_TAMP3E /*!< Tamper 3 input detection */
#define LL_TAMP_ALL                  (TAMP_CR1_TAMP1E | TAMP_CR1_TAMP2E | TAMP_CR1_TAMP3E) /*!< All tampers input selection */
/**
  * @}
  */

/** @defgroup TAMP_LL_EC_TAMPER_MASK  TAMPER MASK
  * @{
  */
#define LL_TAMP_MASK_NONE            0U
#define LL_TAMP_MASK_TAMPER          TAMP_CR2_TAMP1MSK /*!< Tamper 1 event generates a trigger event. TAMP1F is masked and internally cleared by hardware.The backup registers are not erased */
#define LL_TAMP_MASK_TAMPER1         TAMP_CR2_TAMP1MSK /*!< Tamper 1 event generates a trigger event. TAMP1F is masked and internally cleared by hardware.The backup registers are not erased */
#define LL_TAMP_MASK_TAMPER2         TAMP_CR2_TAMP2MSK /*!< Tamper 2 event generates a trigger event. TAMP2F is masked and internally cleared by hardware. The backup registers are not erased. */
#define LL_TAMP_MASK_TAMPER3         TAMP_CR2_TAMP3MSK /*!< Tamper 3 event generates a trigger event. TAMP3F is masked and internally cleared by hardware. The backup registers are not erased. */
#define LL_TAMP_MASK_TAMPER_ALL      (TAMP_CR2_TAMP1MSK | TAMP_CR2_TAMP2MSK | TAMP_CR2_TAMP3MSK) /*!< Tamper 1-2-3 event generates a trigger event. TAMP1F-2F-3F are masked and internally cleared by hardware.The backup registers are not erased */
/**
  * @}
  */

/** @defgroup TAMP_LL_EC_TAMPER_NOERASE  TAMPER NO ERASE
  * @{
  */
#define LL_TAMP_ERASE_ACTIVATE_ALL   0U
#define LL_TAMP_NOERASE_TAMPER       TAMP_CR2_TAMP1POM /*!< Tamper 1 event does not erase the backup registers. */
#define LL_TAMP_NOERASE_TAMPER1      TAMP_CR2_TAMP1POM /*!< Tamper 1 event does not erase the backup registers. */
#define LL_TAMP_NOERASE_TAMPER2      TAMP_CR2_TAMP2POM /*!< Tamper 2 event does not erase the backup registers. */
#define LL_TAMP_NOERASE_TAMPER3      TAMP_CR2_TAMP3POM /*!< Tamper 3 event does not erase the backup registers. */
#define LL_TAMP_NOERASE_TAMPER_ALL   (TAMP_CR2_TAMP1POM | TAMP_CR2_TAMP2POM | TAMP_CR2_TAMP3POM)
/*!< All tampers events do not erase the backup registers. */
/**
  * @}
  */

/** @defgroup TAMP_LL_EC_BACKUP_BLOCK BACKUP BLOCKED
  * @{
  */

#define LL_TAMP_BACKUP_BLOCK_DISABLE   0U                /*!< Tamper backup block is disabled */
#define LL_TAMP_BACKUP_BLOCK_ENABLE    TAMP_CR2_BKBLOCK  /*!< Tamper backup block is enabled */

/**
  * @}
  */


/** @defgroup TAMP_LL_EC_TAMPER_DURATION  TAMPER DURATION
  * @{
  */
#define LL_TAMP_DURATION_1RTCCLK     0U                     /*!< Tamper pins are pre-charged before sampling during 1 RTCCLK cycle  */
#define LL_TAMP_DURATION_2RTCCLK     TAMP_FLTCR_TAMPPRCH_0  /*!< Tamper pins are pre-charged before sampling during 2 RTCCLK cycles */
#define LL_TAMP_DURATION_4RTCCLK     TAMP_FLTCR_TAMPPRCH_1  /*!< Tamper pins are pre-charged before sampling during 4 RTCCLK cycles */
#define LL_TAMP_DURATION_8RTCCLK     TAMP_FLTCR_TAMPPRCH    /*!< Tamper pins are pre-charged before sampling during 8 RTCCLK cycles */
/**
  * @}
  */

/** @defgroup TAMP_LL_EC_TAMPER_FILTER  TAMPER FILTER
  * @{
  */
#define LL_TAMP_FILTER_DISABLE       0U                      /*!< Tamper filter is disabled */
#define LL_TAMP_FILTER_2SAMPLES      TAMP_FLTCR_TAMPFLT_0    /*!< Tamper is activated after 2 consecutive samples at the active level */
#define LL_TAMP_FILTER_4SAMPLES      TAMP_FLTCR_TAMPFLT_1    /*!< Tamper is activated after 4 consecutive samples at the active level */
#define LL_TAMP_FILTER_8SAMPLES      TAMP_FLTCR_TAMPFLT      /*!< Tamper is activated after 8 consecutive samples at the active level. */
/**
  * @}
  */

/** @defgroup TAMP_LL_EC_TAMPER_SAMPLFREQDIV  TAMPER SAMPLING FREQUENCY DIVIDER
  * @{
  */
#define LL_TAMP_SAMPLFREQDIV_32768   0U                                              /*!< Each of the tamper inputs are sampled with a frequency =  RTCCLK / 32768 */
#define LL_TAMP_SAMPLFREQDIV_16384   TAMP_FLTCR_TAMPFREQ_0                           /*!< Each of the tamper inputs are sampled with a frequency =  RTCCLK / 16384 */
#define LL_TAMP_SAMPLFREQDIV_8192    TAMP_FLTCR_TAMPFREQ_1                           /*!< Each of the tamper inputs are sampled with a frequency =  RTCCLK / 8192 */
#define LL_TAMP_SAMPLFREQDIV_4096    (TAMP_FLTCR_TAMPFREQ_1 | TAMP_FLTCR_TAMPFREQ_0) /*!< Each of the tamper inputs are sampled with a frequency =  RTCCLK / 4096 */
#define LL_TAMP_SAMPLFREQDIV_2048    TAMP_FLTCR_TAMPFREQ_2                           /*!< Each of the tamper inputs are sampled with a frequency =  RTCCLK / 2048 */
#define LL_TAMP_SAMPLFREQDIV_1024    (TAMP_FLTCR_TAMPFREQ_2 | TAMP_FLTCR_TAMPFREQ_0) /*!< Each of the tamper inputs are sampled with a frequency =  RTCCLK / 1024 */
#define LL_TAMP_SAMPLFREQDIV_512     (TAMP_FLTCR_TAMPFREQ_2 | TAMP_FLTCR_TAMPFREQ_1) /*!< Each of the tamper inputs are sampled with a frequency =  RTCCLK / 512 */
#define LL_TAMP_SAMPLFREQDIV_256     TAMP_FLTCR_TAMPFREQ                             /*!< Each of the tamper inputs are sampled with a frequency =  RTCCLK / 256 */
/**
  * @}
  */

/** @defgroup TAMP_LL_EC_TAMPER_PULL_UP TAMPER PULL UP
  * @{
  */
#define LL_TAMP_PULL_UP_ENABLE        0U                    /*!< Precharge TAMP_INx pins before sampling (enable internal pull-up) */
#define LL_TAMP_PULL_UP_DISABLE       TAMP_FLTCR_TAMPPUDIS  /*!< Disable precharge of TAMP_INx pins                                */
/**
  * @}
  */

/** @defgroup TAMP_LL_EC_TAMPER_ACTIVELEVEL  TAMPER ACTIVE LEVEL
  * @{
  */
#define LL_TAMP_ACTIVELEVEL_DEACTIVATE_ALL  0U
#define LL_TAMP_ACTIVELEVEL_TAMP            TAMP_CR2_TAMP1TRG /*!< Tamper 1 input falling edge (if TAMPFLT = 00) or staying high (if TAMPFLT != 00) triggers a tamper detection event */
#define LL_TAMP_ACTIVELEVEL_TAMP1    TAMP_CR2_TAMP1TRG /*!< Tamper 1 input falling edge (if TAMPFLT = 00) or staying high (if TAMPFLT != 00) triggers a tamper detection event */
#define LL_TAMP_ACTIVELEVEL_TAMP2    TAMP_CR2_TAMP2TRG /*!< Tamper 2 input falling edge (if TAMPFLT = 00) or staying high (if TAMPFLT != 00) triggers a tamper detection event */
#define LL_TAMP_ACTIVELEVEL_TAMP3    TAMP_CR2_TAMP3TRG /*!< Tamper 2 input falling edge (if TAMPFLT = 00) or staying high (if TAMPFLT != 00) triggers a tamper detection event */
#define LL_TAMP_ACTIVELEVEL_TAMP_ALL (TAMP_CR2_TAMP1TRG | TAMP_CR2_TAMP2TRG | TAMP_CR2_TAMP3TRG)
/*!< All tamper input falling edge (if TAMPFLT = 00) or staying high (if TAMPFLT != 00) triggers a tamper detection event */
/**
  * @}
  */


/** @defgroup TAMP_LL_EC_INTERNAL  INTERNAL TAMPER
  * @{
  */
#define LL_TAMP_ITAMP3                TAMP_CR1_ITAMP3E  /*!< Internal tamper 3: LSE monitoring */
#define LL_TAMP_ITAMP4                TAMP_CR1_ITAMP4E  /*!< Internal tamper 4: HSE monitoring */
#define LL_TAMP_ITAMP5                TAMP_CR1_ITAMP5E  /*!< Internal tamper 5: RTC calendar overflow */
#define LL_TAMP_ITAMP6                TAMP_CR1_ITAMP6E  /*!< Internal tamper 6: Unexpected debug activation */
#define LL_TAMP_ITAMP9                TAMP_CR1_ITAMP9E  /*!< Internal tamper 9: TRNG fault */
#define LL_TAMP_ITAMP11               TAMP_CR1_ITAMP11E /*!< Internal tamper 11: IWDG reset when tamper flag is set */
#define LL_TAMP_ITAMP_ALL             (TAMP_CR1_ITAMP3E  | TAMP_CR1_ITAMP4E  | TAMP_CR1_ITAMP5E \
                                       | TAMP_CR1_ITAMP6E  | TAMP_CR1_ITAMP9E  | TAMP_CR1_ITAMP11E) /*!< All internal tampers */
/**
  * @}
  */

/**
  * @defgroup TAMP_LL_EC_INTERNAL_MODE INTERNAL TAMPER MODE
  * @{
  */
#define LL_TAMP_ITAMP_ERASE_ACTIVE_ALL    0U
#define LL_TAMP_ITAMP_NOERASE_TAMPER      TAMP_CR3_ITAMP3POM  /*!< Internal tamper 3 potential mode */
#define LL_TAMP_ITAMP_NOERASE_TAMPER3     TAMP_CR3_ITAMP3POM  /*!< Internal tamper 3 potential mode */
#define LL_TAMP_ITAMP_NOERASE_TAMPER4     TAMP_CR3_ITAMP4POM  /*!< Internal tamper 4 potential mode */
#define LL_TAMP_ITAMP_NOERASE_TAMPER5     TAMP_CR3_ITAMP5POM  /*!< Internal tamper 5 potential mode */
#define LL_TAMP_ITAMP_NOERASE_TAMPER6     TAMP_CR3_ITAMP6POM  /*!< Internal tamper 6 potential mode */
#define LL_TAMP_ITAMP_NOERASE_TAMPER9     TAMP_CR3_ITAMP9POM  /*!< Internal tamper 9 potential mode */
#define LL_TAMP_ITAMP_NOERASE_TAMPER11    TAMP_CR3_ITAMP11POM /*!< Internal tamper 11 potential mode */
#define LL_TAMP_ITAMP_NOERASE_TAMPER_ALL  (TAMP_CR3_ITAMP3POM | TAMP_CR3_ITAMP4POM | TAMP_CR3_ITAMP5POM \
                                           | TAMP_CR3_ITAMP6POM | TAMP_CR3_ITAMP9POM | TAMP_CR3_ITAMP11POM)
/*!< All internal tampers events do not erase the device secrets. */

/**
  * @}
  */


/** @defgroup TAMP_LL_EC_TAMPER_IT TAMPER IT
  * @{
  */
#define LL_TAMP_IT_NONE         0U
#define LL_TAMP_IT_TAMPER_1          TAMP_IER_TAMP1IE  /*!< Tamper 1 interrupt enable */
#define LL_TAMP_IT_TAMPER_2          TAMP_IER_TAMP2IE  /*!< Tamper 2 interrupt enable */
#define LL_TAMP_IT_TAMPER_3          TAMP_IER_TAMP3IE  /*!< Tamper 3 interrupt enable */
#define LL_TAMP_IT_ALL               (TAMP_IER_TAMP1IE | TAMP_IER_TAMP2IE | TAMP_IER_TAMP3IE)
/**
  * @}
  */

/** @defgroup TAMP_LL_EC_INTERNAL_TAMPER_IT INTERNAL TAMPER IT
  * @{
  */
#define LL_TAMP_INTERNAL_IT_NONE         0U
#define LL_TAMP_INTERNAL_IT_TAMPER_3    TAMP_IER_ITAMP3IE  /*!< Internal tamper 3 interrupt enable */
#define LL_TAMP_INTERNAL_IT_TAMPER_4    TAMP_IER_ITAMP4IE  /*!< Internal tamper 4 interrupt enable */
#define LL_TAMP_INTERNAL_IT_TAMPER_5    TAMP_IER_ITAMP5IE  /*!< Internal tamper 5 interrupt enable */
#define LL_TAMP_INTERNAL_IT_TAMPER_6    TAMP_IER_ITAMP6IE  /*!< Internal tamper 6 interrupt enable */
#define LL_TAMP_INTERNAL_IT_TAMPER_9    TAMP_IER_ITAMP9IE  /*!< Internal tamper 9 interrupt enable */
#define LL_TAMP_INTERNAL_IT_TAMPER_11   TAMP_IER_ITAMP11IE /*!< Internal tamper 11 interrupt enable */
#define LL_TAMP_INTERNAL_IT_ALL         (TAMP_IER_ITAMP3IE | TAMP_IER_ITAMP4IE | TAMP_IER_ITAMP5IE \
                                         | TAMP_IER_ITAMP6IE | TAMP_IER_ITAMP9IE | TAMP_IER_ITAMP11IE)
/**
  * @}
  */


/** @defgroup TAMP_LL_EC_TAMPER_REMAP TAMPER REMAP
  * @{
  */
#define LL_TAMP_RMP_TAMP_IN2_PA0_TO_PC1     TAMP_OR_IN2_RMP
#define LL_TAMP_RMP_TAMP_IN3_PA1_TO_PA2     TAMP_OR_IN3_RMP
/**
  * @}
  */

/** @defgroup TAMP_LL_EC_BKP  BACKUP REGISTER
  * @{
  */
#define LL_TAMP_BKP_NUMBER                  TAMP_BACKUP_NB /*!< TAMP backup registers number */
#define LL_TAMP_BKP_DR0                     0U /*!< TAMP backup registers 0 */
#define LL_TAMP_BKP_DR1                     1U /*!< TAMP backup registers 1 */
#define LL_TAMP_BKP_DR2                     2U /*!< TAMP backup registers 2 */
#define LL_TAMP_BKP_DR3                     3U /*!< TAMP backup registers 3 */
#define LL_TAMP_BKP_DR4                     4U /*!< TAMP backup registers 4 */
#define LL_TAMP_BKP_DR5                     5U /*!< TAMP backup registers 5 */
#define LL_TAMP_BKP_DR6                     6U /*!< TAMP backup registers 6 */
#define LL_TAMP_BKP_DR7                     7U /*!< TAMP backup registers 7 */
#define LL_TAMP_BKP_DR8                     8U   /*!< TAMP backup registers 8 */
#define LL_TAMP_BKP_DR9                     9U   /*!< TAMP backup registers 9 */
#define LL_TAMP_BKP_DR10                    10U  /*!< TAMP backup registers 10 */
#define LL_TAMP_BKP_DR11                    11U  /*!< TAMP backup registers 11 */
#define LL_TAMP_BKP_DR12                    12U  /*!< TAMP backup registers 12 */
#define LL_TAMP_BKP_DR13                    13U  /*!< TAMP backup registers 13 */
#define LL_TAMP_BKP_DR14                    14U  /*!< TAMP backup registers 14 */
#define LL_TAMP_BKP_DR15                    15U  /*!< TAMP backup registers 15 */
#define LL_TAMP_BKP_DR16                    16U  /*!< TAMP backup registers 16 */
#define LL_TAMP_BKP_DR17                    17U  /*!< TAMP backup registers 17 */
#define LL_TAMP_BKP_DR18                    18U  /*!< TAMP backup registers 18 */
#define LL_TAMP_BKP_DR19                    19U  /*!< TAMP backup registers 19 */
#define LL_TAMP_BKP_DR20                    20U  /*!< TAMP backup registers 20 */
#define LL_TAMP_BKP_DR21                    21U  /*!< TAMP backup registers 21 */
#define LL_TAMP_BKP_DR22                    22U  /*!< TAMP backup registers 22 */
#define LL_TAMP_BKP_DR23                    23U  /*!< TAMP backup registers 23 */
#define LL_TAMP_BKP_DR24                    24U  /*!< TAMP backup registers 24 */
#define LL_TAMP_BKP_DR25                    25U  /*!< TAMP backup registers 25 */
#define LL_TAMP_BKP_DR26                    26U  /*!< TAMP backup registers 26 */
#define LL_TAMP_BKP_DR27                    27U  /*!< TAMP backup registers 27 */
#define LL_TAMP_BKP_DR28                    28U  /*!< TAMP backup registers 28 */
#define LL_TAMP_BKP_DR29                    29U  /*!< TAMP backup registers 29 */
#define LL_TAMP_BKP_DR30                    30U  /*!< TAMP backup registers 30 */
#define LL_TAMP_BKP_DR31                    31U  /*!< TAMP backup registers 31 */
/**
  * @}
  */


/** @defgroup TAMP_LL_EC_PRIVILEGE_TAMP_FULL  Privilege full tamp
  * @{
  */
#define LL_TAMP_PRIVILEGE_FULL_YES         TAMP_PRIVCFGR_TAMPPRIV /*!< TAMP full privilege */
#define LL_TAMP_PRIVILEGE_FULL_NO          0U                     /*!< TAMP is not privilege */
/**
  * @}
  */


/** @defgroup TAMP_LL_EC_PRIVILEGE_BACKUP_REG_ZONE  Privilege Backup register privilege zone
  * @{
  */
#define LL_TAMP_PRIVILEGE_BKUP_ZONE_NONE    0U /*!< Backup registers no privilege protection */
#define LL_TAMP_PRIVILEGE_BKUP_ZONE_1       TAMP_PRIVCFGR_BKPRWPRIV /*!< Backup registers zone 1 privilege protection */
#define LL_TAMP_PRIVILEGE_BKUP_ZONE_2       TAMP_PRIVCFGR_BKPWPRIV  /*!< Backup registers zone 2 privilege protection */
#define LL_TAMP_PRIVILEGE_BKUP_ZONE_ALL     (LL_TAMP_PRIVILEGE_BKUP_ZONE_1 |  LL_TAMP_PRIVILEGE_BKUP_ZONE_2)
/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/** @defgroup TAMP_LL_Exported_Macros TAMP Exported Macros
  * @{
  */

/** @defgroup TAMP_LL_EM_WRITE_READ Common Write and read registers Macros
  * @{
  */


/**
  * @brief  Write a value in TAMP register
  * @param  __REG__ Register to be written
  * @param  __VALUE__ Value to be written in the register
  */
#define LL_TAMP_WRITE_REG(__REG__, __VALUE__) WRITE_REG(TAMP->__REG__, (__VALUE__))

/**
  * @brief  Read a value in TAMP register

  * @param  __REG__ Register to be read
  * @retval Register value
  */
#define LL_TAMP_READ_REG(__REG__) READ_REG(TAMP->__REG__)
/**
  * @}
  */

/** @defgroup TAMP_LL_EM_helper Helper macros
  * @{
  */

/**
  * @brief Helper macro to retrieve pull_up precharge configuration
  * @param tamp_config_value Value returned by @ref LL_TAMP_GetConfig
  * @retval Return value can be one of the following values:
  *        @arg @ref LL_TAMP_PULL_UP_ENABLE
  *        @arg @ref LL_TAMP_PULL_UP_DISABLE
  */
#define LL_TAMP_GET_PULL_UP(tamp_config_value) ((tamp_config_value) & TAMP_FLTCR_TAMPPUDIS)

/**
  * @brief Helper macro to retrieve pull_up precharge duration configuration
  * @param tamp_config_value Value returned by @ref LL_TAMP_GetConfig
  * @retval Return value can be one of the following values:
  *        @arg @ref LL_TAMP_DURATION_1RTCCLK
  *        @arg @ref LL_TAMP_DURATION_2RTCCLK
  *        @arg @ref LL_TAMP_DURATION_4RTCCLK
  *        @arg @ref LL_TAMP_DURATION_8RTCCLK
  */
#define LL_TAMP_GET_PRECHARGE_DURATION(tamp_config_value) ((tamp_config_value) & TAMP_FLTCR_TAMPPRCH)

/**
  * @brief Helper macro to retrieve pull_up precharge configuration
  * @param tamp_config_value Value returned by @ref LL_TAMP_GetConfig
  * @retval Return value can be one of the following values:
  *        @arg @ref LL_TAMP_FILTER_DISABLE
  *        @arg @ref LL_TAMP_FILTER_2SAMPLES
  *        @arg @ref LL_TAMP_FILTER_4SAMPLES
  *        @arg @ref LL_TAMP_FILTER_8SAMPLES
  */
#define LL_TAMP_GET_FILTER_SAMPLE(tamp_config_value) ((tamp_config_value) & TAMP_FLTCR_TAMPFLT)

/**
  * @brief Helper macro to retrieve pull_up precharge configuration
  * @param tamp_config_value Value returned by @ref LL_TAMP_GetConfig
  * @retval Return value can be one of the following values:
  *        @arg @ref LL_TAMP_SAMPLFREQDIV_32768
  *        @arg @ref LL_TAMP_SAMPLFREQDIV_16384
  *        @arg @ref LL_TAMP_SAMPLFREQDIV_8192
  *        @arg @ref LL_TAMP_SAMPLFREQDIV_4096
  *        @arg @ref LL_TAMP_SAMPLFREQDIV_2048
  *        @arg @ref LL_TAMP_SAMPLFREQDIV_1024
  *        @arg @ref LL_TAMP_SAMPLFREQDIV_512
  *        @arg @ref LL_TAMP_SAMPLFREQDIV_256
  */
#define LL_TAMP_GET_FILTER_SAMPLE_FREQUENCY(tamp_config_value) ((tamp_config_value) & TAMP_FLTCR_TAMPFREQ)

/**
  * @brief Helper macro to retrieve the trigger edge or level.
  * @param tamp_config_indiv_value Value returned by @ref LL_TAMP_GetConfigTampers
  * @retval Return value can be one of the following values:
  *         @arg @ref LL_TAMP_ACTIVELEVEL_DEACTIVATE_ALL
  *         @arg @ref LL_TAMP_ACTIVELEVEL_TAMP
  */
#define LL_TAMP_GET_TRIGGER(tamp_config_indiv_value) ((((tamp_config_indiv_value) & \
                                                        LL_TAMP_ACTIVELEVEL_TAMP_ALL) != 0U ) ?\
                                                      LL_TAMP_ACTIVELEVEL_TAMP : LL_TAMP_ACTIVELEVEL_DEACTIVATE_ALL)

/**
  * @brief Helper macro to retrieve the mode of the tamper.
  * @param tamp_config_indiv_value Value returned by @ref LL_TAMP_GetConfigTampers
  * @retval Return value can be one of the following values:
  *         @arg @ref LL_TAMP_ERASE_ACTIVATE_ALL
  *         @arg @ref LL_TAMP_NOERASE_TAMPER
  */
#define LL_TAMP_GET_NOERASE(tamp_config_indiv_value) ((((tamp_config_indiv_value) &\
                                                        LL_TAMP_NOERASE_TAMPER_ALL) != 0U ) ?\
                                                      LL_TAMP_NOERASE_TAMPER : LL_TAMP_ERASE_ACTIVATE_ALL)

/**
  * @brief Helper macro to retrieve the mask of the tamper.
  * @param tamp_config_indiv_value Value returned by @ref LL_TAMP_GetConfigTampers
  * @retval Return value can be one of the following values:
  *         @arg @ref LL_TAMP_MASK_NONE
  *         @arg @ref LL_TAMP_MASK_TAMPER
  */
#define LL_TAMP_GET_MASK(tamp_config_indiv_value) ((((tamp_config_indiv_value) &\
                                                     LL_TAMP_MASK_TAMPER_ALL) != 0U ) ?\
                                                   LL_TAMP_MASK_TAMPER : LL_TAMP_MASK_NONE)

/**
  * @brief Helper macro to retrieve the mode of the internal tamper.
  * @param itamp_config_indiv_value Value returned by @ref LL_TAMP_GetConfigInternalTampers
  * @retval Return value can be one of the following values:
  *         @arg @ref LL_TAMP_ITAMP_ERASE_ACTIVE_ALL
  *         @arg @ref LL_TAMP_ITAMP_NOERASE_TAMPER
  */
#define LL_TAMP_INTERNAL_GET_NOERASE(itamp_config_indiv_value) ((((itamp_config_indiv_value) &\
                                                                  LL_TAMP_ITAMP_NOERASE_TAMPER_ALL) != 0U ) \
                                                                ? LL_TAMP_ITAMP_NOERASE_TAMPER : \
                                                                LL_TAMP_ITAMP_ERASE_ACTIVE_ALL)


/**
  * @}
  */


/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @defgroup TAMP_LL_Exported_Functions TAMP Exported Functions
  * @{
  */

/** @defgroup TAMP_LL_EF_Tamper Tamper
  * @{
  */

/**
  * @brief  Enable TAMPx input detection
  * @rmtoll
  *  TAMP_CR1       TAMPxE        LL_TAMP_Enable
  * @param  Tampers
  *         This parameter can be a combination of the group values @ref TAMP_LL_EC_TAMPER
  */
__STATIC_INLINE void LL_TAMP_Enable(uint32_t Tampers)
{
  SET_BIT(TAMP->CR1, Tampers);
}

/**
  * @brief  Clear TAMPx input detection
  * @rmtoll
  *  TAMP_CR1       TAMPxE         LL_TAMP_Disable
  * @param  Tampers
  *         This parameter can be a combination of the group values @ref TAMP_LL_EC_TAMPER
  */
__STATIC_INLINE void LL_TAMP_Disable(uint32_t Tampers)
{
  CLEAR_BIT(TAMP->CR1, Tampers);
}

/**
  * @brief  Get TAMPx that are enabled
  * @rmtoll
  *  TAMP_CR1       TAMPxE         LL_TAMP_GetEnabled
  * @param  Tampers
  *         This parameter can be a combination of the group values @ref TAMP_LL_EC_TAMPER
  * @retval State of the tampers enable.
  */
__STATIC_INLINE uint32_t LL_TAMP_GetEnabled(uint32_t Tampers)
{
  return READ_BIT(TAMP->CR1, Tampers);
}

/**
  * @brief  Enable TAMPx interruption
  * @rmtoll
  *  TAMP_IER       TAMPxIE       LL_TAMP_EnableIT
  * @param  TampersIT
  *         This parameter can be a combination of the group values @ref TAMP_LL_EC_TAMPER_IT
  */
__STATIC_INLINE void LL_TAMP_EnableIT(uint32_t TampersIT)
{
  SET_BIT(TAMP->IER, TampersIT);
}

/**
  * @brief  Disable TAMPx interruption
  * @rmtoll
  *  TAMP_IER       TAMPxIE       LL_TAMP_DisableIT
  * @param  TampersIT
  *         This parameter can be a combination of the group values @ref TAMP_LL_EC_TAMPER_IT
  */
__STATIC_INLINE void LL_TAMP_DisableIT(uint32_t TampersIT)
{
  CLEAR_BIT(TAMP->IER, TampersIT);
}

/**
  * @brief  Get TAMPx interruption that are enabled.
  * @rmtoll
  *  TAMP_IER       TAMPxIE        LL_TAMP_IsEnabledIT
  * @param  TampersIT
  *         This parameter can be a combination of the group values @ref TAMP_LL_EC_TAMPER_IT
  * @retval State of the tampers interruption enable (1 enabled / 0 disabled).
  */
__STATIC_INLINE uint32_t LL_TAMP_IsEnabledIT(uint32_t TampersIT)
{
  return ((READ_BIT(TAMP->IER, TampersIT) == (TampersIT)) ? 1UL : 0UL);

}

/**
  * @brief  Enable Tamper mask flag
  * @note Associated Tamper IT must not enabled when tamper mask is set.
  * @rmtoll
  *  TAMP_CR2       TAMPxMSK       LL_TAMP_EnableMask
  * @param  Mask
  *         This parameter can be a combination of the group values @ref TAMP_LL_EC_TAMPER_MASK
  */
__STATIC_INLINE void LL_TAMP_EnableMask(uint32_t Mask)
{
  SET_BIT(TAMP->CR2, Mask);
}

/**
  * @brief  Disable Tamper mask flag
  * @rmtoll
  *  TAMP_CR2       TAMPxMSK       LL_TAMP_DisableMask
  * @param  Mask
  *         This parameter can be a combination of the group values @ref TAMP_LL_EC_TAMPER_MASK
  */
__STATIC_INLINE void LL_TAMP_DisableMask(uint32_t Mask)
{
  CLEAR_BIT(TAMP->CR2, Mask);
}

/**
  * @brief  Get TAMPx mask flag that are enabled
  * @rmtoll
  *  TAMP_CR2       TAMPxMSK       LL_TAMP_GetMasked
  * @param  Mask
  *         This parameter can be a combination of the group values @ref TAMP_LL_EC_TAMPER_MASK
  * @retval State of the tampers mask flag enable.
  */
__STATIC_INLINE uint32_t LL_TAMP_GetMasked(uint32_t Mask)
{
  return READ_BIT(TAMP->CR2, (Mask & LL_TAMP_MASK_TAMPER_ALL));
}

/**
  * @brief  Enable TAMPx potential mode
  * @rmtoll
  *  TAMP_CR2       TAMPxPOM     LL_TAMP_EnablePotentialMode
  * @param  Tamper
  *         This parameter can be a combination of the group values @ref TAMP_LL_EC_TAMPER_NOERASE
  * @note   In potential mode, the backup registers and devices secret can be blocked instead of erased.
  *         See TAMP interconnection table for more information.
  */
__STATIC_INLINE void LL_TAMP_EnablePotentialMode(uint32_t Tamper)
{
  SET_BIT(TAMP->CR2, Tamper);
}

/**
  * @brief  Disable TAMPx potential mode
  * @rmtoll
  *  TAMP_CR2       TAMPxPOM     LL_TAMP_DisablePotentialMode
  * @param  Tamper
  *         This parameter can be a combination of the group values @ref TAMP_LL_EC_TAMPER_NOERASE
  */
__STATIC_INLINE void LL_TAMP_DisablePotentialMode(uint32_t Tamper)
{
  CLEAR_BIT(TAMP->CR2, Tamper);
}

/**
  * @brief  Check if the TAMPx potential mode is enabled or disabled
  * @rmtoll
  *  TAMP_CR2       TAMPxPOM     LL_TAMP_IsEnabledPotentialMode
  * @param  Tamper
  *         This parameter can be a combination of the group values @ref TAMP_LL_EC_TAMPER_NOERASE
  * @retval State of TAMPx potential mode (1 enabled / 0 disabled).
  */
__STATIC_INLINE uint32_t LL_TAMP_IsEnabledPotentialMode(uint32_t Tamper)
{
  return ((READ_BIT(TAMP->CR2, Tamper) == (Tamper)) ? 1UL : 0UL);
}

/**
  * @brief Configure global tamper parameters
  * @rmtoll
  *  TAMP_FLTCR     TAMPPUDIS    LL_TAMP_SetConfig \n
  *  TAMP_FLTCR     TAMPPRCH     LL_TAMP_SetConfig \n
  *  TAMP_FLTCR     TAMPFREQ     LL_TAMP_SetConfig \n
  *  TAMP_FLTCR     TAMPFLT      LL_TAMP_SetConfig
  * @param Pullup pull-up (precharge of TAMP pins) can be one of the following values:
  *        @arg @ref LL_TAMP_PULL_UP_ENABLE
  *        @arg @ref LL_TAMP_PULL_UP_DISABLE
  * @param Precharge time duration of the precharge can be one of the following values:
  *        @arg @ref LL_TAMP_DURATION_1RTCCLK
  *        @arg @ref LL_TAMP_DURATION_2RTCCLK
  *        @arg @ref LL_TAMP_DURATION_4RTCCLK
  *        @arg @ref LL_TAMP_DURATION_8RTCCLK
  * @param FilterCounter filter counter, can be one of the following values:
  *        @arg @ref LL_TAMP_FILTER_DISABLE
  *        @arg @ref LL_TAMP_FILTER_2SAMPLES
  *        @arg @ref LL_TAMP_FILTER_4SAMPLES
  *        @arg @ref LL_TAMP_FILTER_8SAMPLES
  * @param SampleFrequency sample frequency, can be one of the following values:
  *        @arg @ref LL_TAMP_SAMPLFREQDIV_32768
  *        @arg @ref LL_TAMP_SAMPLFREQDIV_16384
  *        @arg @ref LL_TAMP_SAMPLFREQDIV_8192
  *        @arg @ref LL_TAMP_SAMPLFREQDIV_4096
  *        @arg @ref LL_TAMP_SAMPLFREQDIV_2048
  *        @arg @ref LL_TAMP_SAMPLFREQDIV_1024
  *        @arg @ref LL_TAMP_SAMPLFREQDIV_512
  *        @arg @ref LL_TAMP_SAMPLFREQDIV_256
  */
__STATIC_INLINE void LL_TAMP_SetConfig(uint32_t Pullup, uint32_t Precharge, uint32_t FilterCounter,
                                       uint32_t SampleFrequency)
{
  WRITE_REG(TAMP->FLTCR,  Pullup | Precharge | FilterCounter | SampleFrequency);
}

/**
  * @brief Retrieve the global tamper parameters configuration
  * @rmtoll
  *  TAMP_FLTCR     TAMPPUDIS    LL_TAMP_GetConfig \n
  *  TAMP_FLTCR     TAMPPRCH     LL_TAMP_GetConfig \n
  *  TAMP_FLTCR     TAMPFREQ     LL_TAMP_GetConfig \n
  *  TAMP_FLTCR     TAMPFLT      LL_TAMP_GetConfig
  * @retval Combined values of the pull-up precharge, precharge duration, sample frequency and filter
  */
__STATIC_INLINE uint32_t LL_TAMP_GetConfig(void)
{
  return READ_REG(TAMP->FLTCR);
}

/**
  * @brief Configure one or multiple tampers.
  * @rmtoll
  *  TAMP_CR2     TAMPxTRG    LL_TAMP_SetConfigTampers \n
  *  TAMP_CR2     TAMPxMSK    LL_TAMP_SetConfigTampers \n
  *  TAMP_CR2     TAMPxPOM    LL_TAMP_SetConfigTampers
  * @param Tampers
  *        tampers can be one of the group values @ref TAMP_LL_EC_TAMPER
  * @param Trigger trigger mode, can be one of the following values:
  *        @arg @ref LL_TAMP_ACTIVELEVEL_DEACTIVATE_ALL
  *        @arg @ref LL_TAMP_ACTIVELEVEL_TAMP
  * @param EraseSecrets tamper mode, can be one of the following values:
  *        @arg @ref LL_TAMP_ERASE_ACTIVATE_ALL
  *        @arg @ref LL_TAMP_NOERASE_TAMPER
  * @param Masked tamper masked, can be one of the following values:
  *        @arg @ref LL_TAMP_MASK_NONE
  *        @arg @ref LL_TAMP_MASK_TAMPER
  */
__STATIC_INLINE void LL_TAMP_SetConfigTampers(uint32_t Tampers, uint32_t Trigger, uint32_t EraseSecrets,
                                              uint32_t Masked)
{
  uint32_t temp1 = ((Tampers << TAMP_CR2_TAMP1TRG_Pos) | (Tampers << TAMP_CR2_TAMP1POM_Pos)
                    | ((Tampers << TAMP_CR2_TAMP1MSK_Pos) & LL_TAMP_MASK_TAMPER_ALL)) & (TAMP_CR2_CFG_MSK);
  uint32_t temp2 = (Tampers * (Trigger | Masked | EraseSecrets)) & (TAMP_CR2_CFG_MSK);
  MODIFY_REG(TAMP->CR2, temp1, temp2);
}

/**
  * @brief Retrieve one configuration tamper.
  * @rmtoll
  *  TAMP_CR2     TAMPxTRG    LL_TAMP_GetConfigTampers \n
  *  TAMP_CR2     TAMPxMSK    LL_TAMP_GetConfigTampers \n
  *  TAMP_CR2     TAMPxPOM    LL_TAMP_GetConfigTampers
  * @param Tampers
  *        tampers can be one of the group values @ref TAMP_LL_EC_TAMPER
  * @retval Combined values of the tamper masked, mode and trigger mode.
  */
__STATIC_INLINE uint32_t LL_TAMP_GetConfigTampers(uint32_t Tampers)
{
  return READ_BIT(TAMP->CR2, ((Tampers << TAMP_CR2_TAMP1TRG_Pos) | (Tampers << TAMP_CR2_TAMP1POM_Pos)
                              | (Tampers << TAMP_CR2_TAMP1MSK_Pos)) & TAMP_CR2_CFG_MSK);
}

/**
  * @brief  Enable TAMPx pull-up (Precharge TAMPx pins before sampling)
  * @rmtoll
  *  TAMP_FLTCR       TAMPPUDIS     LL_TAMP_EnablePullUp
  */
__STATIC_INLINE void LL_TAMP_EnablePullUp(void)
{
  CLEAR_BIT(TAMP->FLTCR, TAMP_FLTCR_TAMPPUDIS);
}

/**
  * @brief  Disable TAMPx pull-up (Disable precharge of TAMPx pins)
  * @rmtoll
  *  TAMP_FLTCR       TAMPPUDIS     LL_TAMP_DisablePullUp
  */
__STATIC_INLINE void LL_TAMP_DisablePullUp(void)
{
  SET_BIT(TAMP->FLTCR, TAMP_FLTCR_TAMPPUDIS);
}

/**
  * @brief  Check if the TAMPx pull-up is enabled or disabled
  * @rmtoll
  *  TAMP_FLTCR       TAMPPUDIS     LL_TAMP_IsEnabledPullUp
  * @retval State of TAMPx pull-up (1 enabled / 0 disabled).
  */
__STATIC_INLINE uint32_t LL_TAMP_IsEnabledPullUp(void)
{
  return ((READ_BIT(TAMP->FLTCR, TAMP_FLTCR_TAMPPUDIS) == (TAMP_FLTCR_TAMPPUDIS)) ? 0UL : 1UL);
}

/**
  * @brief  Set TAMPx precharge duration
  * @rmtoll
  *  TAMP_FLTCR       TAMPPRCH      LL_TAMP_SetPrecharge
  * @param  Duration This parameter can be one of the following values:
  *         @arg @ref LL_TAMP_DURATION_1RTCCLK
  *         @arg @ref LL_TAMP_DURATION_2RTCCLK
  *         @arg @ref LL_TAMP_DURATION_4RTCCLK
  *         @arg @ref LL_TAMP_DURATION_8RTCCLK
  */
__STATIC_INLINE void LL_TAMP_SetPrecharge(uint32_t Duration)
{
  MODIFY_REG(TAMP->FLTCR, TAMP_FLTCR_TAMPPRCH, Duration);
}

/**
  * @brief  Get TAMPx precharge duration
  * @rmtoll
  *  TAMP_FLTCR       TAMPPRCH      LL_TAMP_GetPrecharge
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_TAMP_DURATION_1RTCCLK
  *         @arg @ref LL_TAMP_DURATION_2RTCCLK
  *         @arg @ref LL_TAMP_DURATION_4RTCCLK
  *         @arg @ref LL_TAMP_DURATION_8RTCCLK
  */
__STATIC_INLINE uint32_t LL_TAMP_GetPrecharge(void)
{
  return (uint32_t)(READ_BIT(TAMP->FLTCR, TAMP_FLTCR_TAMPPRCH));
}

/**
  * @brief  Set TAMPx filter count
  * @rmtoll
  *  TAMP_FLTCR       TAMPFLT       LL_TAMP_SetFilterCount
  * @param  FilterCount This parameter can be one of the following values:
  *         @arg @ref LL_TAMP_FILTER_DISABLE
  *         @arg @ref LL_TAMP_FILTER_2SAMPLES
  *         @arg @ref LL_TAMP_FILTER_4SAMPLES
  *         @arg @ref LL_TAMP_FILTER_8SAMPLES
  */
__STATIC_INLINE void LL_TAMP_SetFilterCount(uint32_t FilterCount)
{
  MODIFY_REG(TAMP->FLTCR, TAMP_FLTCR_TAMPFLT, FilterCount);
}

/**
  * @brief  Get TAMPx filter count
  * @rmtoll
  *  TAMP_FLTCR       TAMPFLT       LL_TAMP_GetFilterCount
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_TAMP_FILTER_DISABLE
  *         @arg @ref LL_TAMP_FILTER_2SAMPLES
  *         @arg @ref LL_TAMP_FILTER_4SAMPLES
  *         @arg @ref LL_TAMP_FILTER_8SAMPLES
  */
__STATIC_INLINE uint32_t LL_TAMP_GetFilterCount(void)
{
  return (uint32_t)(READ_BIT(TAMP->FLTCR, TAMP_FLTCR_TAMPFLT));
}

/**
  * @brief  Set Tamper sampling frequency
  * @rmtoll
  *  TAMP_FLTCR       TAMPFREQ      LL_TAMP_SetSamplingFreq
  * @param  SamplingFreq This parameter can be one of the following values:
  *         @arg @ref LL_TAMP_SAMPLFREQDIV_32768
  *         @arg @ref LL_TAMP_SAMPLFREQDIV_16384
  *         @arg @ref LL_TAMP_SAMPLFREQDIV_8192
  *         @arg @ref LL_TAMP_SAMPLFREQDIV_4096
  *         @arg @ref LL_TAMP_SAMPLFREQDIV_2048
  *         @arg @ref LL_TAMP_SAMPLFREQDIV_1024
  *         @arg @ref LL_TAMP_SAMPLFREQDIV_512
  *         @arg @ref LL_TAMP_SAMPLFREQDIV_256
  */
__STATIC_INLINE void LL_TAMP_SetSamplingFreq(uint32_t SamplingFreq)
{
  MODIFY_REG(TAMP->FLTCR, TAMP_FLTCR_TAMPFREQ, SamplingFreq);
}

/**
  * @brief  Get Tamper sampling frequency
  * @rmtoll
  *  TAMP_FLTCR       TAMPFREQ      LL_TAMP_GetSamplingFreq
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_TAMP_SAMPLFREQDIV_32768
  *         @arg @ref LL_TAMP_SAMPLFREQDIV_16384
  *         @arg @ref LL_TAMP_SAMPLFREQDIV_8192
  *         @arg @ref LL_TAMP_SAMPLFREQDIV_4096
  *         @arg @ref LL_TAMP_SAMPLFREQDIV_2048
  *         @arg @ref LL_TAMP_SAMPLFREQDIV_1024
  *         @arg @ref LL_TAMP_SAMPLFREQDIV_512
  *         @arg @ref LL_TAMP_SAMPLFREQDIV_256
  */
__STATIC_INLINE uint32_t LL_TAMP_GetSamplingFreq(void)
{
  return (uint32_t)(READ_BIT(TAMP->FLTCR, TAMP_FLTCR_TAMPFREQ));
}

/**
  * @brief  Enable Active level for Tamper input
  * @rmtoll
  *  TAMP_CR2       TAMPxTRG       LL_TAMP_EnableActiveLevel
  * @param  Tamper
  *         This parameter can be a combination of the group values @ref TAMP_LL_EC_TAMPER_ACTIVELEVEL
  */
__STATIC_INLINE void LL_TAMP_EnableActiveLevel(uint32_t Tamper)
{
  SET_BIT(TAMP->CR2, Tamper);
}

/**
  * @brief  Disable Active level for Tamper input
  * @rmtoll
  *  TAMP_CR2       TAMPxTRG      LL_TAMP_DisableActiveLevel
  * @param  Tamper
  *         This parameter can be a combination of the group values @ref TAMP_LL_EC_TAMPER_ACTIVELEVEL
  */
__STATIC_INLINE void LL_TAMP_DisableActiveLevel(uint32_t Tamper)
{
  CLEAR_BIT(TAMP->CR2, Tamper);
}

/**
  * @brief  Check if the TAMPx Active level is enabled or disabled.
  * @rmtoll
  *  TAMP_CR2       TAMPxTRG     LL_TAMP_IsEnabledActiveLevel
  * @param  Tamper
  *         This parameter can be a one of the group values @ref TAMP_LL_EC_TAMPER_ACTIVELEVEL
  * @retval State of TAMPx Active level (1 enabled / 0 disabled).
  */
__STATIC_INLINE uint32_t LL_TAMP_IsEnabledActiveLevel(uint32_t Tamper)
{
  return ((READ_BIT(TAMP->CR2, Tamper) == (Tamper)) ? 1UL : 0UL);
}

/**
  * @}
  */

/** @defgroup TAMP_LL_EF_Internal_Tamper Internal Tamper
  * @{
  */

/**
  * @brief Configure one or multiple internal tampers.
  * @rmtoll
  *  TAMP_CR3     ITAMPxPOM        LL_TAMP_SetConfigInternalTampers
  * @param InternalTampers
  *        This parameter can be a combination of the group values @ref TAMP_LL_EC_INTERNAL
  * @param EraseSecrets tamper mode, can be one of the following values:
  *        @arg @ref LL_TAMP_ITAMP_ERASE_ACTIVE_ALL
  *        @arg @ref LL_TAMP_ITAMP_NOERASE_TAMPER
  */
__STATIC_INLINE void LL_TAMP_SetConfigInternalTampers(uint32_t InternalTampers, uint32_t EraseSecrets)
{
  uint32_t temp = InternalTampers >> LL_POSITION_FIRST_ITAMP;
  MODIFY_REG(TAMP->CR3, temp, temp * EraseSecrets);
}

/**
  * @brief Retrieve one configuration internal tamper.
  * @rmtoll
  *  TAMP_CR3     ITAMPxPOM        LL_TAMP_GetConfigInternalTampers
  * @param InternalTampers
  *        This parameter can be a combination of the group values @ref TAMP_LL_EC_INTERNAL
  * @retval Values of the select internal tampers no erase mode.
  */
__STATIC_INLINE uint32_t LL_TAMP_GetConfigInternalTampers(uint32_t InternalTampers)
{
  uint32_t temp = InternalTampers >> LL_POSITION_OFFSET_REG_ITAMP;
  return READ_BIT(TAMP->CR3, temp);
}

/**
  * @brief  Enable ITAMPx input detection
  * @rmtoll
  *  TAMP_CR1       ITAMPxE        LL_TAMP_ITAMP_Enable
  * @param  InternalTampers
  *         This parameter can be a combination of the group values @ref TAMP_LL_EC_INTERNAL
  */
__STATIC_INLINE void LL_TAMP_ITAMP_Enable(uint32_t InternalTampers)
{
  SET_BIT(TAMP->CR1, InternalTampers);
}

/**
  * @brief  Disable ITAMPx input detection
  * @rmtoll
  *  TAMP_CR1       ITAMPxE         LL_TAMP_ITAMP_Disable
  * @param  InternalTampers
  *          This parameter can be a combination of the group values @ref TAMP_LL_EC_INTERNAL
  */
__STATIC_INLINE void LL_TAMP_ITAMP_Disable(uint32_t InternalTampers)
{
  CLEAR_BIT(TAMP->CR1, InternalTampers);
}

/**
  * @brief  Get ITAMPx that are enabled
  * @rmtoll
  *  TAMP_CR1       ITAMPxE         LL_TAMP_ITAMP_GetEnabled
  * @param  InternalTampers
  *         This parameter can be a combination of the group values @ref TAMP_LL_EC_INTERNAL
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_TAMP_ITAMP_GetEnabled(uint32_t InternalTampers)
{
  return READ_BIT(TAMP->CR1, InternalTampers);
}

/**
  * @brief  Enable ITAMPx input detection interruption
  * @rmtoll
  *  TAMP_IER       ITAMPxE        LL_TAMP_ITAMP_EnableIT
  * @param  InternalTampersIT
  *         This parameter can be a combination of the group values @ref TAMP_LL_EC_INTERNAL_TAMPER_IT
  */
__STATIC_INLINE void LL_TAMP_ITAMP_EnableIT(uint32_t InternalTampersIT)
{
  SET_BIT(TAMP->IER, InternalTampersIT);
}

/**
  * @brief  Clear ITAMPx input detection interruption
  * @rmtoll
  *  TAMP_IER       ITAMPxE         LL_TAMP_ITAMP_DisableIT
  * @param  InternalTampersIT
  *         This parameter can be a combination of the group values @ref TAMP_LL_EC_INTERNAL_TAMPER_IT
  */
__STATIC_INLINE void LL_TAMP_ITAMP_DisableIT(uint32_t InternalTampersIT)
{
  CLEAR_BIT(TAMP->IER, InternalTampersIT);
}

/**
  * @brief  Get ITAMPx interruption that are enabled
  * @rmtoll
  *  TAMP_IER       ITAMPxE         LL_TAMP_ITAMP_IsEnabledIT
  * @param  InternalTampersIT
  *         This parameter can be a combination of the group values @ref TAMP_LL_EC_INTERNAL_TAMPER_IT
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_TAMP_ITAMP_IsEnabledIT(uint32_t InternalTampersIT)
{
  return ((READ_BIT(TAMP->IER, InternalTampersIT) == (InternalTampersIT)) ? 1UL : 0UL);
}

/**
  * @}
  */

/** @defgroup TAMP_LL_EF_Backup_Registers Backup_Registers
  * @{
  */

/**
  * @brief  Writes a data in a specified Backup data register.
  * @rmtoll
  *  TAMP_BKPxR        BKP           LL_TAMP_BKP_SetRegister
  * @param  BackupRegister This parameter can be one of the group values @ref TAMP_LL_EC_BKP
  * @param  Data Value between Min_Data=0x00 and Max_Data=0xFFFFFFFF
  */
__STATIC_INLINE void LL_TAMP_BKP_SetRegister(uint32_t BackupRegister, uint32_t Data)
{
  uint32_t tmp;

  tmp = (uint32_t)(&(TAMP->BKP0R));
  tmp += (BackupRegister * 4U);

  /* Write the specified register */
  *(__IO uint32_t *)tmp = (uint32_t)Data;
}

/**
  * @brief  Reads data from the specified TAMP Backup data Register.
  * @rmtoll
  *  TAMP_BKPxR        BKP           LL_TAMP_BKP_GetRegister
  * @param  BackupRegister This parameter can be one of the group values @ref TAMP_LL_EC_BKP
  * @retval Value between Min_Data=0x00 and Max_Data=0xFFFFFFFF
  */
__STATIC_INLINE uint32_t LL_TAMP_BKP_GetRegister(uint32_t BackupRegister)
{
  uint32_t tmp;

  tmp = (uint32_t)(&(TAMP->BKP0R));
  tmp += (BackupRegister * 4U);

  /* Read the specified register */
  return (*(__IO uint32_t *)tmp);
}

/**
  * @}
  */

/** @defgroup TAMP_LL_EF_FLAG_Management FLAG_Management
  * @{
  */

/**
  * @brief  Get tampers interrupt flags.
  * @rmtoll
  *  TAMP_SR          TAMPx       LL_TAMP_IsActiveFlag_TAMP
  * @param Tampers This parameter can be a combination of the following values:
  *        @arg @ref TAMP_LL_EC_TAMPER
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_TAMP_IsActiveFlag_TAMP(uint32_t Tampers)
{
  return ((READ_BIT(TAMP->SR, Tampers) != 0U) ? 1UL : 0UL);
}

/**
  * @brief  Get internal tampers interrupt flags.
  * @rmtoll
  *  TAMP_SR          ITAMPx       LL_TAMP_IsActiveFlag_ITAMP
  * @param InternalTampers This parameter can be a combination of the following values:
  *        @arg @ref TAMP_LL_EC_INTERNAL
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_TAMP_IsActiveFlag_ITAMP(uint32_t InternalTampers)
{
  return ((READ_BIT(TAMP->SR, InternalTampers) != 0U) ? 1UL : 0UL);
}

/**
  * @brief  Get tampers interrupt masked flags.
  * @rmtoll
  *  TAMP_MISR          TAMPxMF       LL_TAMP_IsActiveFlag_TAMPM
  * @param Tampers This parameter can be a combination of the following values:
  *        @arg @ref TAMP_LL_EC_TAMPER
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_TAMP_IsActiveFlag_TAMPM(uint32_t Tampers)
{
  return ((READ_BIT(TAMP->MISR, Tampers) != 0U) ? 1UL : 0UL);
}

/**
  * @brief  Get internal tampers interrupt masked flags.
  * @rmtoll
  *  TAMP_MISR          ITAMPxMF       LL_TAMP_IsActiveFlag_ITAMPM
  * @param InternalTampers This parameter can be a combination of the following values:
  *        @arg @ref TAMP_LL_EC_INTERNAL
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_TAMP_IsActiveFlag_ITAMPM(uint32_t InternalTampers)
{
  return ((READ_BIT(TAMP->MISR, InternalTampers) != 0U) ? 1UL : 0UL);
}

/**
  * @brief  Clear tampers interrupt masked flags.
  * @rmtoll
  *  TAMP_SCR          CTAMPxF       LL_TAMP_ClearFlag_TAMP
  * @param Tampers This parameter can be a combination of the following values:
  *        @arg @ref TAMP_LL_EC_TAMPER
  */
__STATIC_INLINE void LL_TAMP_ClearFlag_TAMP(uint32_t Tampers)
{
  WRITE_REG(TAMP->SCR, Tampers);
}

/**
  * @brief  Clear internal tampers interrupt masked flags.
  * @rmtoll
  *  TAMP_SCR          CITAMPxF       LL_TAMP_ClearFlag_ITAMP
  * @param InternalTampers This parameter can be a combination of the following values:
  *        @arg @ref TAMP_LL_EC_INTERNAL
  */
__STATIC_INLINE void LL_TAMP_ClearFlag_ITAMP(uint32_t InternalTampers)
{
  WRITE_REG(TAMP->SCR, InternalTampers);
}

/**
  * @}
  */


/** @defgroup TAMP_LL_EF_PRIVILEGE PRIVILEGE_Management
  * @{
  */

/**
  * @brief  Enable TAMPER privilege
  * @rmtoll
  *  TAMP_PRIVCFGR          TAMPPRIV           LL_TAMP_SetTampPrivilege
  */
__STATIC_INLINE void LL_TAMP_EnableTampPrivilege(void)
{
  SET_BIT(TAMP->PRIVCFGR, TAMP_PRIVCFGR_TAMPPRIV);
}

/**
  * @brief  Disable TAMPER privilege
  * @rmtoll
  *  TAMP_PRIVCFGR          TAMPPRIV           LL_TAMP_DisableTampPrivilege
  */
__STATIC_INLINE void LL_TAMP_DisableTampPrivilege(void)
{
  CLEAR_BIT(TAMP->PRIVCFGR, TAMP_PRIVCFGR_TAMPPRIV);
}

/**
  * @brief  Get TAMPER privilege level.
  * @rmtoll
  *  TAMP_PRIVCFGR          TAMPPRIV           LL_TAMP_IsEnabledTampPrivilege
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_TAMP_IsEnabledTampPrivilege(void)
{
  return ((READ_BIT(TAMP->PRIVCFGR, TAMP_PRIVCFGR_TAMPPRIV) == (TAMP_PRIVCFGR_TAMPPRIV)) ? 1UL : 0UL);
}

/**
  * @brief  Set Backup Registers privilege level.
  * @rmtoll
  *  TAMP_PRIVCFGR          BKPWPRIV           LL_TAMP_SetBackupRegisterPrivilege \n
  *  TAMP_PRIVCFGR          BKPRWPRIV          LL_TAMP_SetBackupRegisterPrivilege
  * @param  BackupRegisterPrivilege This parameter can be one of the following values:
  *         @arg @ref LL_TAMP_PRIVILEGE_BKUP_ZONE_NONE
  *         @arg @ref LL_TAMP_PRIVILEGE_BKUP_ZONE_1
  *         @arg @ref LL_TAMP_PRIVILEGE_BKUP_ZONE_2
  *         @arg @ref LL_TAMP_PRIVILEGE_BKUP_ZONE_ALL
  */
__STATIC_INLINE void LL_TAMP_SetBackupRegisterPrivilege(uint32_t BackupRegisterPrivilege)
{
  MODIFY_REG(TAMP->PRIVCFGR, (TAMP_PRIVCFGR_BKPWPRIV | TAMP_PRIVCFGR_BKPRWPRIV), BackupRegisterPrivilege);
}

/**
  * @brief  Get Backup Registers privilege level.
  * @rmtoll
  *  TAMP_PRIVCFGR          BKPWPRIV           LL_TAMP_GetBackupRegisterPrivilege \n
  *  TAMP_PRIVCFGR          BKPRWPRIV          LL_TAMP_GetBackupRegisterPrivilege
  * @retval This parameter can be one of the following values:
  *         @arg @ref LL_TAMP_PRIVILEGE_BKUP_ZONE_NONE
  *         @arg @ref LL_TAMP_PRIVILEGE_BKUP_ZONE_1
  *         @arg @ref LL_TAMP_PRIVILEGE_BKUP_ZONE_2
  *         @arg @ref LL_TAMP_PRIVILEGE_BKUP_ZONE_ALL
  */
__STATIC_INLINE uint32_t LL_TAMP_GetBackupRegisterPrivilege(void)
{
  return READ_BIT(TAMP->PRIVCFGR, (TAMP_PRIVCFGR_BKPWPRIV | TAMP_PRIVCFGR_BKPRWPRIV));
}

/**
  * @}
  */


/** @defgroup TAMP_LL_EF_Device_Secret_Management Device_Secret Management
  * @{
  */

/**
  * @brief Block access to the backup registers and device secrets.
  * @rmtoll
  *  TAMP_CR2      BKBLOCK    LL_TAMP_BlockDeviceSecretsAccess
  */
__STATIC_INLINE void LL_TAMP_BlockDeviceSecretsAccess(void)
{
  SET_BIT(TAMP->CR2, TAMP_CR2_BKBLOCK);
}

/**
  * @brief Unblock access to the backup registers and device secrets.
  * @rmtoll
  *  TAMP_CR2      BKBLOCK    LL_TAMP_UnblockDeviceSecretsAccess
  */
__STATIC_INLINE void LL_TAMP_UnblockDeviceSecretsAccess(void)
{
  CLEAR_BIT(TAMP->CR2, TAMP_CR2_BKBLOCK);
}

/**
  * @brief Check if the access to the backup registers and devices secrets is blocked.
  * @rmtoll
  *  TAMP_CR2      BKBLOCK    LL_TAMP_IsBlockedDeviceSecretsAccess
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_TAMP_IsBlockedDeviceSecretsAccess(void)
{
  return ((READ_BIT(TAMP->CR2, TAMP_CR2_BKBLOCK) == (TAMP_CR2_BKBLOCK)) ? 1UL : 0UL);
}

/**
  * @brief Erase the backup registers and device secrets.
  * @rmtoll
  *  TAMP_CR2      BKERASE    LL_TAMP_EraseDeviceSecrets
  */
__STATIC_INLINE void LL_TAMP_EraseDeviceSecrets(void)
{
  SET_BIT(TAMP->CR2, TAMP_CR2_BKERASE);
}


/**
  * @}
  */

/** @defgroup TAMP_LL_EF_Remap Tamp remap
  * @{
  */
/**
  * @brief  Enable remap of TAMP INx on different pin
  * @rmtoll
  *  TAMP_OR           IN2_RMP       LL_TAMP_EnableRemap \n
  *  TAMP_OR           IN3_RMP       LL_TAMP_EnableRemap
  * @param  tamp_remap This parameter can be a combination of the following values:
  *         @arg @ref LL_TAMP_RMP_TAMP_IN2_PA0_TO_PC1
  *         @arg @ref LL_TAMP_RMP_TAMP_IN3_PA1_TO_PA2
  */
__STATIC_INLINE void LL_TAMP_EnableRemap(uint32_t tamp_remap)
{
  SET_BIT(TAMP->OR, tamp_remap);
}

/**
  * @brief  Disable remap of TAMP INx on different pin
  * @rmtoll
  *  TAMP_OR           IN2_RMP       LL_TAMP_DisableRemap \n
  *  TAMP_OR           IN3_RMP       LL_TAMP_DisableRemap
  * @param  tamp_remap This parameter can be a combination of the following values:
  *         @arg @ref LL_TAMP_RMP_TAMP_IN2_PA0_TO_PC1
  *         @arg @ref LL_TAMP_RMP_TAMP_IN3_PA1_TO_PA2
  */
__STATIC_INLINE void LL_TAMP_DisableRemap(uint32_t tamp_remap)
{
  CLEAR_BIT(TAMP->OR, tamp_remap);
}

/**
  * @brief  Check if remap TAMP INx is enabled or disabled.
  * @rmtoll
  *  TAMP_OR           IN2_RMP       LL_TAMP_IsEnabledRemap \n
  *  TAMP_OR           IN3_RMP       LL_TAMP_IsEnabledRemap
  * @param  tamp_remap This parameter can be a combination of the following values:
  *         @arg @ref LL_TAMP_RMP_TAMP_IN2_PA0_TO_PC1
  *         @arg @ref LL_TAMP_RMP_TAMP_IN3_PA1_TO_PA2
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_TAMP_IsEnabledRemap(uint32_t tamp_remap)
{
  return ((READ_BIT(TAMP->OR, tamp_remap) == tamp_remap) ? 1UL : 0UL);
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

#endif /* defined(TAMP) */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* STM32C5XX_LL_TAMP_H */
