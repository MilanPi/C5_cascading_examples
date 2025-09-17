/**
  ******************************************************************************
  * @file    stm32c5xx_ll_comp.h
  * @author  GPM Application Team
  * @brief   Header file of COMP LL module.
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
#ifndef STM32C5XX_LL_COMP_H
#define STM32C5XX_LL_COMP_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "stm32c5xx.h"

/** @addtogroup STM32C5xx_LL_Driver
  * @{
  */

#if defined(COMP1)

/** @defgroup COMP_LL COMP
  * @{
  */

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/
/** @defgroup COMP_LL_Exported_Constants COMP Exported Constants
  * @{
  */
/** @defgroup COMP_LL_EC_POWERMODE Comparator modes - Power mode
  * @{
  */
#define LL_COMP_POWERMODE_HIGHSPEED     (0x00000000UL)         /*!< Comparator power mode to high speed */
#define LL_COMP_POWERMODE_MEDIUMSPEED   (COMP_CFGR1_PWRMODE_0) /*!< Comparator power mode to medium speed */
#define LL_COMP_POWERMODE_ULTRALOWPOWER (COMP_CFGR1_PWRMODE_1 \
                                         | COMP_CFGR1_PWRMODE_0) /*!< Comparator power mode to ultra-low power */
/**
  * @}
  */

/** @defgroup COMP_LL_EC_INPUT_PLUS Comparator inputs - Input plus (input non-inverting) selection
  * @{
  */
#define LL_COMP_INPUT_PLUS_IO1          (0x00000000UL)       /*!< Comparator input plus connected to IO1
                                        (for GPIO mapping, refer to datasheet parameters "COMPx_INP1") */
#define LL_COMP_INPUT_PLUS_IO2          (COMP_CFGR1_INPSEL_0) /*!< Comparator input plus connected to IO2
                                        (for GPIO mapping, refer to datasheet parameters "COMPx_INP2") */
#define LL_COMP_INPUT_PLUS_IO3          (COMP_CFGR1_INPSEL_1) /*!< Comparator input plus connected to IO3
                                        (for GPIO mapping, refer to datasheet parameters "COMPx_INP3") */
#define LL_COMP_INPUT_PLUS_DAC1_CH1     (COMP_CFGR1_INPSEL_1 | COMP_CFGR1_INPSEL_0) /*!< Comparator input plus
                                        connected to DAC1 channel 1 */
/**
  * @}
  */

/** @defgroup COMP_LL_EC_INPUT_MINUS Comparator inputs - Input minus (input inverting) selection
  * @{
  */
#define LL_COMP_INPUT_MINUS_VREFINT     (COMP_CFGR1_INMSEL_1 | COMP_CFGR1_INMSEL_0 \
                                         | COMP_CFGR1_SCALEN) /*!< Comparator  input minus connected to VrefInt
                                        (for VrefInt voltage value, refer to datasheet). */
#define LL_COMP_INPUT_MINUS_1_4VREFINT  (COMP_CFGR1_SCALEN | COMP_CFGR1_BRGEN) /*!< Comparator input minus connected
                                        to 1/4 VrefInt (for VrefInt voltage value, refer to datasheet). */
#define LL_COMP_INPUT_MINUS_1_2VREFINT  (COMP_CFGR1_INMSEL_0 | COMP_CFGR1_SCALEN | COMP_CFGR1_BRGEN) /*!< Comparator
                                        input minus connected to 1/2 VrefInt (for VrefInt voltage value, refer to
                                        datasheet). */
#define LL_COMP_INPUT_MINUS_3_4VREFINT  (COMP_CFGR1_INMSEL_1 | COMP_CFGR1_SCALEN | COMP_CFGR1_BRGEN) /*!< Comparator
                                        input minus connected to 3/4 VrefInt (for VrefInt voltage value, refer to
                                        datasheet). */
#define LL_COMP_INPUT_MINUS_IO1         (COMP_CFGR1_INMSEL_2 | COMP_CFGR1_INMSEL_0) /*!< Comparator
                                        input plus connected to IO1 (for GPIO mapping, refer to datasheet
                                        parameters "COMPx_INM1") */
#define LL_COMP_INPUT_MINUS_IO2         (COMP_CFGR1_INMSEL_2 | COMP_CFGR1_INMSEL_1) /*!< Comparator
                                        input plus connected to IO1 (for GPIO mapping, refer to datasheet
                                        parameters "COMPx_INM1") */
#define LL_COMP_INPUT_MINUS_IO3         (COMP_CFGR1_INMSEL_2 | COMP_CFGR1_INMSEL_1 \
                                         | COMP_CFGR1_INMSEL_0) /*!< Comparator input plus connected to IO3
                                        (for GPIO mapping, refer to datasheet parameters "COMPx_INM3") */
#define LL_COMP_INPUT_MINUS_DAC1_CH1    (COMP_CFGR1_INMSEL_2) /*!< Comparator input minus connected
                                        to DAC1 channel 1 (specific to COMP instances: COMP1) */
#define LL_COMP_INPUT_MINUS_TEMPSENSOR  (COMP_CFGR1_INMSEL_3) /*!< Comparator input minus connected
                                        to internal temperature sensor (also accessible through ADC peripheral) */
/**
  * @}
  */

/** @defgroup COMP_LL_EC_INPUT_HYSTERESIS Comparator input - Hysteresis
  * @{
  */
#define LL_COMP_HYSTERESIS_NONE         (0x00000000UL)                          /*!< No hysteresis */
#define LL_COMP_HYSTERESIS_LOW          (COMP_CFGR1_HYST_0)                     /*!< Hysteresis level low */
#define LL_COMP_HYSTERESIS_MEDIUM       (COMP_CFGR1_HYST_1)                     /*!< Hysteresis level medium */
#define LL_COMP_HYSTERESIS_HIGH         (COMP_CFGR1_HYST_1 | COMP_CFGR1_HYST_0) /*!< Hysteresis level high */
/**
  * @}
  */

/** @defgroup COMP_LL_EC_OUTPUT_POLARITY Comparator output - Output polarity
  * @{
  */
#define LL_COMP_OUTPUTPOL_NONINVERTED   (0x00000000UL) /*!< Comparator output polarity not inverted:
                                        comparator output at high level when input voltages: plus higher than minus */
#define LL_COMP_OUTPUTPOL_INVERTED      (COMP_CFGR1_POLARITY) /*!< Comparator output polarity not inverted:
                                        comparator output at low level when input voltages: plus higher than minus */
/**
  * @}
  */

/** @defgroup COMP_LL_EC_OUTPUT_BLANKING_SOURCE Comparator output - Blanking source
  * @{
  */
#define LL_COMP_BLANKINGSRC_NONE        (0x00000000UL)        /*!< Comparator output without blanking */
#define LL_COMP_BLANKINGSRC_TIM1_OC5    (COMP_CFGR1_BLANKING_0)   /*!< Comparator output blanking source TIM1 OC5 */
#define LL_COMP_BLANKINGSRC_TIM2_OC3    (COMP_CFGR1_BLANKING_1)   /*!< Comparator output blanking source TIM2 OC3 */
#define LL_COMP_BLANKINGSRC_TIM5_OC3    (COMP_CFGR1_BLANKING_0 \
                                         | COMP_CFGR1_BLANKING_1) /*!< Comparator output blanking source TIM5 OC3 */
#define LL_COMP_BLANKINGSRC_TIM5_OC4    (COMP_CFGR1_BLANKING_2)   /*!< Comparator output blanking source TIM5 OC4 */
#define LL_COMP_BLANKINGSRC_TIM8_OC5    (COMP_CFGR1_BLANKING_2 \
                                         | COMP_CFGR1_BLANKING_0) /*!< Comparator output blanking source TIM8 OC5 */
#define LL_COMP_BLANKINGSRC_TIM15_OC2   (COMP_CFGR1_BLANKING_2 \
                                         | COMP_CFGR1_BLANKING_1) /*!< Comparator output blanking source TIM15 OC2 */
/**
  * @}
  */

/** @defgroup COMP_LL_EC_OUTPUT_LEVEL Comparator output - Output level
  * @{
  */
#define LL_COMP_OUTPUT_LEVEL_LOW        (0x00000000UL) /*!< Comparator output level low (with polarity not inverted) */
#define LL_COMP_OUTPUT_LEVEL_HIGH       (0x00000001UL) /*!< Comparator output level high (with polarity not inverted) */
/**
  * @}
  */

/** @defgroup COMP_LL_EC_HW_DELAYS  Definitions of COMP hardware constraints delays
  * @note   Only COMP peripheral HW delays are defined in COMP LL driver driver, not timeout values.
  * @{
  */

/* Delay for comparator startup time.                                         */
/* Note: Delay required to reach propagation delay specification.             */
/* Literal set to maximum value (refer to device datasheet,                   */
/* parameter "tSTART").                                                       */
/* Unit: us                                                                   */
#define LL_COMP_DELAY_STARTUP_US        (80UL) /*!< Delay for comparator startup time.
                                        Delay set to maximum value (refer to device datasheet, parameter "tSTART").
                                        Unit: us.
                                        Note: At comparator enable, delay required to reach propagation delay
                                              specification. */

/* Delay for comparator voltage scaler stabilization time.                    */
/* Note: Voltage scaler is used when selecting comparator input               */
/*       based on VrefInt (VrefInt or subdivision of VrefInt).                */
/* Note: To get scaler bridge configuration,                                  */
/*       refer to @ref LL_COMP_IsInputScalerEnabled().                        */
/* Literal set to maximum value (refer to device datasheet,                   */
/* parameter "tSTART_SCALER").                                                */
/* Unit: us                                                                   */
#define LL_COMP_DELAY_VOLTAGE_SCALER_STAB_US (220UL) /*!< Delay for comparator voltage scaler stabilization time
                                        Delay set to maximum value (refer to device datasheet,
                                        parameter "tSTART_SCALER").
                                        Unit: us.
                                        Note: Voltage scaler is used when selecting comparator input
                                              based on VrefInt (VrefInt or subdivision of VrefInt).
                                        Note: To get scaler bridge configuration,
                                              refer to @ref LL_COMP_IsInputScalerEnabled().
                                        */

/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/** @defgroup COMP_LL_Exported_Macros COMP Exported Macros
  * @{
  */
/** @defgroup COMP_LL_EM_WRITE_READ Common write and read registers macro
  * @{
  */

/**
  * @brief  Write a value in COMP register
  * @param  __INSTANCE__ comparator instance
  * @param  __REG__ Register to be written
  * @param  __VALUE__ Value to be written in the register
  */
#define LL_COMP_WRITE_REG(__INSTANCE__, __REG__, __VALUE__) WRITE_REG((__INSTANCE__)->__REG__, (__VALUE__))

/**
  * @brief  Read a value in COMP register
  * @param  __INSTANCE__ comparator instance
  * @param  __REG__ Register to be read
  * @retval Register value
  */
#define LL_COMP_READ_REG(__INSTANCE__, __REG__) READ_REG((__INSTANCE__)->__REG__)
/**
  * @}
  */

/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @defgroup COMP_LL_Exported_Functions COMP Exported Functions
  * @{
  */

/** @defgroup COMP_LL_EF_Configuration_comparator_modes Configuration of comparator modes
  * @{
  */

/**
  * @brief  Set comparator instance operating mode to adjust power and speed.
  * @rmtoll
  *  CFGR1    PWRMODE        LL_COMP_SetPowerMode
  * @param  p_comp Comparator instance.
  * @param  power_mode This parameter can be one of the following values:
  *         @arg @ref LL_COMP_POWERMODE_HIGHSPEED
  *         @arg @ref LL_COMP_POWERMODE_MEDIUMSPEED
  *         @arg @ref LL_COMP_POWERMODE_ULTRALOWPOWER
  */
__STATIC_INLINE void LL_COMP_SetPowerMode(COMP_TypeDef *p_comp, uint32_t power_mode)
{
  MODIFY_REG(p_comp->CFGR1, COMP_CFGR1_PWRMODE, power_mode);
}

/**
  * @brief  Get comparator instance operating mode to adjust power and speed.
  * @rmtoll
  *  CFGR1    PWRMODE        LL_COMP_GetPowerMode
  * @param  p_comp Comparator instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_COMP_POWERMODE_HIGHSPEED
  *         @arg @ref LL_COMP_POWERMODE_MEDIUMSPEED
  *         @arg @ref LL_COMP_POWERMODE_ULTRALOWPOWER
  */
__STATIC_INLINE uint32_t LL_COMP_GetPowerMode(const COMP_TypeDef *p_comp)
{
  return (uint32_t)(READ_BIT(p_comp->CFGR1, COMP_CFGR1_PWRMODE));
}

/**
  * @}
  */

/** @defgroup COMP_LL_EF_Configuration_comparator_inputs Configuration of comparator inputs
  * @{
  */

/**
  * @brief  Set comparator inputs minus (inverting) and plus (non-inverting).
  * @note   In case of comparator input selected to be connected to IO:
  *         GPIO pins are specific to each comparator instance.
  *         Refer to description of parameters or to reference manual.
  * @note   Voltage scaler is used when selecting comparator input based on VrefInt (VrefInt or subdivision of VrefInt).
  *         In this case, specific delay must be fulfilled for voltage stabilization when enabling comparator,
  *         refer to LL_COMP_DELAY_VOLTAGE_SCALER_STAB_US.
  * @note   On this STM32 series, a voltage scaler is used
  *         when COMP input is based on VrefInt (VrefInt or subdivision
  *         of VrefInt):
  *         Voltage scaler requires a delay for voltage stabilization.
  *         Refer to device datasheet, parameter "tSTART_SCALER".
  * @rmtoll
  *  CFGR1    INPSEL         LL_COMP_ConfigInputs \n
  *  CFGR1    INMSEL         LL_COMP_ConfigInputs \n
  *  CFGR1    BRGEN          LL_COMP_ConfigInputs \n
  *  CFGR1    SCALEN         LL_COMP_ConfigInputs
  * @param  p_comp Comparator instance
  * @param  input_minus This parameter can be one of the following values:
  *         @arg @ref LL_COMP_INPUT_MINUS_1_4VREFINT
  *         @arg @ref LL_COMP_INPUT_MINUS_1_2VREFINT
  *         @arg @ref LL_COMP_INPUT_MINUS_3_4VREFINT
  *         @arg @ref LL_COMP_INPUT_MINUS_VREFINT
  *         @arg @ref LL_COMP_INPUT_MINUS_IO1
  *         @arg @ref LL_COMP_INPUT_MINUS_IO2
  *         @arg @ref LL_COMP_INPUT_MINUS_IO3
  *         @arg @ref LL_COMP_INPUT_MINUS_DAC1_CH1
  *         @arg @ref LL_COMP_INPUT_MINUS_TEMPSENSOR
  * @param  input_plus This parameter can be one of the following values:
  *         @arg @ref LL_COMP_INPUT_PLUS_IO1
  *         @arg @ref LL_COMP_INPUT_PLUS_IO2
  *         @arg @ref LL_COMP_INPUT_PLUS_IO3
  *         @arg @ref LL_COMP_INPUT_PLUS_DAC1_CH1
  */
__STATIC_INLINE void LL_COMP_ConfigInputs(COMP_TypeDef *p_comp, uint32_t input_minus, uint32_t input_plus)
{
  MODIFY_REG(p_comp->CFGR1,
             COMP_CFGR1_INMSEL | COMP_CFGR1_INPSEL | COMP_CFGR1_SCALEN | COMP_CFGR1_BRGEN,
             input_minus | input_plus);
}

/**
  * @brief  Set comparator input plus.
  * @note   In case of comparator input selected to be connected to IO:
  *         GPIO pins are specific to each comparator instance.
  *         Refer to description of parameters or to reference manual.
  * @rmtoll
  *  CFGR1    INPSEL         LL_COMP_SetInputPlus
  * @param  p_comp Comparator instance
  * @param  input_plus This parameter can be one of the following values:
  *         @arg @ref LL_COMP_INPUT_PLUS_IO1
  *         @arg @ref LL_COMP_INPUT_PLUS_IO2
  *         @arg @ref LL_COMP_INPUT_PLUS_IO3
  *         @arg @ref LL_COMP_INPUT_PLUS_DAC1_CH1
  */
__STATIC_INLINE void LL_COMP_SetInputPlus(COMP_TypeDef *p_comp, uint32_t input_plus)
{
  MODIFY_REG(p_comp->CFGR1, COMP_CFGR1_INPSEL, input_plus);
}

/**
  * @brief  Get comparator input plus.
  * @note   In case of comparator input selected to be connected to IO:
  *         GPIO pins are specific to each comparator instance.
  *         Refer to description of parameters or to reference manual.
  * @rmtoll
  *  CFGR1    INPSEL         LL_COMP_GetInputPlus
  * @param  p_comp Comparator instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_COMP_INPUT_PLUS_IO1
  *         @arg @ref LL_COMP_INPUT_PLUS_IO2
  *         @arg @ref LL_COMP_INPUT_PLUS_IO3
  *         @arg @ref LL_COMP_INPUT_PLUS_DAC1_CH1
  */
__STATIC_INLINE uint32_t LL_COMP_GetInputPlus(const COMP_TypeDef *p_comp)
{
  return (uint32_t)(READ_BIT(p_comp->CFGR1, COMP_CFGR1_INPSEL));
}

/**
  * @brief  Set comparator input minus.
  * @note   In case of comparator input selected to be connected to IO:
  *         GPIO pins are specific to each comparator instance.
  *         Refer to description of parameters or to reference manual.
  * @note   Voltage scaler is used when selecting comparator input based on VrefInt (VrefInt or subdivision of VrefInt).
  *         In this case, specific delay must be fulfilled for voltage stabilization when enabling comparator,
  *         refer to LL_COMP_DELAY_VOLTAGE_SCALER_STAB_US.
  * @rmtoll
  *  CFGR1    INMSEL         LL_COMP_SetInputMinus \n
  *  CFGR1    BRGEN          LL_COMP_SetInputMinus \n
  *  CFGR1    SCALEN         LL_COMP_SetInputMinus
  * @param  p_comp Comparator instance
  * @param  input_minus This parameter can be one of the following values:
  *         @arg @ref LL_COMP_INPUT_MINUS_1_4VREFINT
  *         @arg @ref LL_COMP_INPUT_MINUS_1_2VREFINT
  *         @arg @ref LL_COMP_INPUT_MINUS_3_4VREFINT
  *         @arg @ref LL_COMP_INPUT_MINUS_VREFINT
  *         @arg @ref LL_COMP_INPUT_MINUS_IO1
  *         @arg @ref LL_COMP_INPUT_MINUS_IO2
  *         @arg @ref LL_COMP_INPUT_MINUS_IO3
  *         @arg @ref LL_COMP_INPUT_MINUS_DAC1_CH1
  *         @arg @ref LL_COMP_INPUT_MINUS_TEMPSENSOR
  */
__STATIC_INLINE void LL_COMP_SetInputMinus(COMP_TypeDef *p_comp, uint32_t input_minus)
{
  MODIFY_REG(p_comp->CFGR1, COMP_CFGR1_INMSEL | COMP_CFGR1_SCALEN | COMP_CFGR1_BRGEN, input_minus);
}

/**
  * @brief  Get comparator input minus.
  * @note   In case of comparator input selected to be connected to IO:
  *         GPIO pins are specific to each comparator instance.
  *         Refer to description of parameters or to reference manual.
  * @rmtoll
  *  CFGR1    INMSEL         LL_COMP_GetInputMinus \n
  *  CFGR1    BRGEN          LL_COMP_GetInputMinus \n
  *  CFGR1    SCALEN         LL_COMP_GetInputMinus
  * @param  p_comp Comparator instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_COMP_INPUT_MINUS_1_4VREFINT
  *         @arg @ref LL_COMP_INPUT_MINUS_1_2VREFINT
  *         @arg @ref LL_COMP_INPUT_MINUS_3_4VREFINT
  *         @arg @ref LL_COMP_INPUT_MINUS_VREFINT
  *         @arg @ref LL_COMP_INPUT_MINUS_IO1
  *         @arg @ref LL_COMP_INPUT_MINUS_IO2
  *         @arg @ref LL_COMP_INPUT_MINUS_IO3
  *         @arg @ref LL_COMP_INPUT_MINUS_DAC1_CH1
  *         @arg @ref LL_COMP_INPUT_MINUS_TEMPSENSOR
  */
__STATIC_INLINE uint32_t LL_COMP_GetInputMinus(const COMP_TypeDef *p_comp)
{
  return (uint32_t)(READ_BIT(p_comp->CFGR1, COMP_CFGR1_INMSEL | COMP_CFGR1_SCALEN | COMP_CFGR1_BRGEN));
}

/**
  * @brief  Get comparator input voltage scaler bridge configuration.
  * @note   Voltage scaler is used when selecting comparator input based on VrefInt (VrefInt or subdivision of VrefInt).
  *         In this case, specific delay must be fulfilled for voltage stabilization when enabling comparator,
  *         refer to LL_COMP_DELAY_VOLTAGE_SCALER_STAB_US.
  * @rmtoll
  *  CFGR1    BRGEN          LL_COMP_IsInputScalerEnabled \n
  *  CFGR1    SCALEN         LL_COMP_IsInputScalerEnabled
  * @param  p_comp Comparator instance
  * @retval State of scaler bridge configuration (value "1" for enabled, value "0" for disabled).
  */
__STATIC_INLINE uint32_t LL_COMP_IsInputScalerEnabled(const COMP_TypeDef *p_comp)
{
  return ((READ_BIT(p_comp->CFGR1, (COMP_CFGR1_SCALEN | COMP_CFGR1_BRGEN)) != 0UL) ? 1UL : 0UL);
}

/**
  * @brief  Set comparator input hysteresis.
  * @note   Hysteresys applied on comparator input minus.
  * @rmtoll
  *  CFGR1    HYST           LL_COMP_SetInputHysteresis
  * @param  p_comp Comparator instance
  * @param  input_hysteresis This parameter can be one of the following values:
  *         @arg @ref LL_COMP_HYSTERESIS_NONE
  *         @arg @ref LL_COMP_HYSTERESIS_LOW
  *         @arg @ref LL_COMP_HYSTERESIS_MEDIUM
  *         @arg @ref LL_COMP_HYSTERESIS_HIGH
  */
__STATIC_INLINE void LL_COMP_SetInputHysteresis(COMP_TypeDef *p_comp, uint32_t input_hysteresis)
{
  MODIFY_REG(p_comp->CFGR1, COMP_CFGR1_HYST, input_hysteresis);
}

/**
  * @brief  Get comparator instance hysteresis mode of the minus (inverting) input.
  * @rmtoll
  *  CFGR1    HYST           LL_COMP_GetInputHysteresis
  * @param  p_comp Comparator instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_COMP_HYSTERESIS_NONE
  *         @arg @ref LL_COMP_HYSTERESIS_LOW
  *         @arg @ref LL_COMP_HYSTERESIS_MEDIUM
  *         @arg @ref LL_COMP_HYSTERESIS_HIGH
  */
__STATIC_INLINE uint32_t LL_COMP_GetInputHysteresis(const COMP_TypeDef *p_comp)
{
  return (uint32_t)(READ_BIT(p_comp->CFGR1, COMP_CFGR1_HYST));
}

/** @defgroup COMP_LL_EF_Configuration_comparator_output Configuration of comparator output
  * @{
  */

/**
  * @brief  Set comparator instance output polarity.
  * @rmtoll
  *  CFGR1    POLARITY       LL_COMP_SetOutputPolarity
  * @param  p_comp Comparator instance
  * @param  output_polarity This parameter can be one of the following values:
  *         @arg @ref LL_COMP_OUTPUTPOL_NONINVERTED
  *         @arg @ref LL_COMP_OUTPUTPOL_INVERTED
  */
__STATIC_INLINE void LL_COMP_SetOutputPolarity(COMP_TypeDef *p_comp, uint32_t output_polarity)
{
  MODIFY_REG(p_comp->CFGR1, COMP_CFGR1_POLARITY, output_polarity);
}

/**
  * @brief  Get comparator instance output polarity.
  * @rmtoll
  *  CFGR1    POLARITY       LL_COMP_GetOutputPolarity
  * @param  p_comp Comparator instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_COMP_OUTPUTPOL_NONINVERTED
  *         @arg @ref LL_COMP_OUTPUTPOL_INVERTED
  */
__STATIC_INLINE uint32_t LL_COMP_GetOutputPolarity(const COMP_TypeDef *p_comp)
{
  return (uint32_t)(READ_BIT(p_comp->CFGR1, COMP_CFGR1_POLARITY));
}

/**
  * @brief  Set comparator instance blanking source.
  * @note   Availability of parameters of blanking source from peripherals
  *         depends on their availability on the selected device.
  * @note   Blanking source can be specific to each comparator instance.
  *         Refer to description of parameters or to reference manual.
  * @rmtoll
  *  CFGR     BLANKING       LL_COMP_SetOutputBlankingSource
  * @param  p_comp Comparator instance
  * @param  blanking_source This parameter can be one of the following values:
  *         @arg @ref LL_COMP_BLANKINGSRC_NONE
  *         @arg @ref LL_COMP_BLANKINGSRC_TIM1_OC5
  *         @arg @ref LL_COMP_BLANKINGSRC_TIM2_OC3
  *         @arg @ref LL_COMP_BLANKINGSRC_TIM5_OC3
  *         @arg @ref LL_COMP_BLANKINGSRC_TIM5_OC4
  *         @arg @ref LL_COMP_BLANKINGSRC_TIM8_OC5
  *         @arg @ref LL_COMP_BLANKINGSRC_TIM15_OC2
  */
__STATIC_INLINE void LL_COMP_SetOutputBlankingSource(COMP_TypeDef *p_comp, uint32_t blanking_source)
{
  MODIFY_REG(p_comp->CFGR1, COMP_CFGR1_BLANKING, blanking_source);
}

/**
  * @brief  Get comparator instance blanking source.
  * @note   Availability of parameters of blanking source from peripherals
  *         depends on their availability on the selected device.
  * @note   Blanking source can be specific to each comparator instance.
  *         Refer to description of parameters or to reference manual.
  * @rmtoll
  *  CFGR     BLANKING       LL_COMP_GetOutputBlankingSource
  * @param  p_comp Comparator instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_COMP_BLANKINGSRC_NONE
  *         @arg @ref LL_COMP_BLANKINGSRC_TIM1_OC5
  *         @arg @ref LL_COMP_BLANKINGSRC_TIM2_OC3
  *         @arg @ref LL_COMP_BLANKINGSRC_TIM5_OC3
  *         @arg @ref LL_COMP_BLANKINGSRC_TIM5_OC4
  *         @arg @ref LL_COMP_BLANKINGSRC_TIM8_OC5
  *         @arg @ref LL_COMP_BLANKINGSRC_TIM15_OC2
  */
__STATIC_INLINE uint32_t LL_COMP_GetOutputBlankingSource(const COMP_TypeDef *p_comp)
{
  return (uint32_t)(READ_BIT(p_comp->CFGR1, COMP_CFGR1_BLANKING));
}

/**
  * @}
  */

/** @defgroup COMP_LL_EF_Operation Operation on comparator instance
  * @{
  */

/**
  * @brief  Enable comparator instance.
  * @note   After enable, comparator requires a delay to reach reach propagation delay specification,
  *         refer to LL_COMP_DELAY_STARTUP_US.
  * @note   Voltage scaler is used when selecting comparator input based on VrefInt (VrefInt or subdivision of VrefInt).
  *         In this case, specific delay must be fulfilled for voltage stabilization when enabling comparator,
  *         refer to LL_COMP_DELAY_VOLTAGE_SCALER_STAB_US.
  *         To get scaler bridge configuration, refer to @ref LL_COMP_IsInputScalerEnabled().
  * @rmtoll
  *  CFGR1    EN             LL_COMP_Enable
  * @param  p_comp Comparator instance
  */
__STATIC_INLINE void LL_COMP_Enable(COMP_TypeDef *p_comp)
{
  SET_BIT(p_comp->CFGR1, COMP_CFGR1_EN);
}

/**
  * @brief  Disable comparator instance.
  * @rmtoll
  *  CFGR1    EN             LL_COMP_Disable
  * @param  p_comp Comparator instance
  */
__STATIC_INLINE void LL_COMP_Disable(COMP_TypeDef *p_comp)
{
  CLEAR_BIT(p_comp->CFGR1, COMP_CFGR1_EN);
}

/**
  * @brief  Get comparator enable state.
  * @rmtoll
  *  CFGR1    EN             LL_COMP_IsEnabled
  * @param  p_comp Comparator instance
  * @retval Value "0" for comparator disabled, value "1" for comparator enabled.
  */
__STATIC_INLINE uint32_t LL_COMP_IsEnabled(const COMP_TypeDef *p_comp)
{
  return ((READ_BIT(p_comp->CFGR1, COMP_CFGR1_EN) == (COMP_CFGR1_EN)) ? 1UL : 0UL);
}

/**
  * @brief  Lock comparator instance.
  * @note   Once locked, comparator configuration can be accessed in read-only.
  * @note   The only way to unlock the comparator is a device system reset.
  * @rmtoll
  *  CFGR1    LOCK           LL_COMP_Lock
  * @param  p_comp Comparator instance
  */
__STATIC_INLINE void LL_COMP_Lock(COMP_TypeDef *p_comp)
{
  SET_BIT(p_comp->CFGR1, COMP_CFGR1_LOCK);
}

/**
  * @brief  Get comparator lock state.
  * @note   Once locked, comparator configuration can be accessed in read-only.
  * @note   The only way to unlock the comparator is a device system reset.
  * @rmtoll
  *  CFGR1    LOCK           LL_COMP_IsLocked
  * @param  p_comp Comparator instance
  * @retval Value "0" for comparator unlocked, value "1" for comparator locked.
  */
__STATIC_INLINE uint32_t LL_COMP_IsLocked(const COMP_TypeDef *p_comp)
{
  return ((READ_BIT(p_comp->CFGR1, COMP_CFGR1_LOCK) == (COMP_CFGR1_LOCK)) ? 1UL : 0UL);
}

/**
  * @brief  Read comparator instance output level.
  * @note   The comparator output level depends on the selected polarity
  *         (Refer to function @ref LL_COMP_SetOutputPolarity()).
  *         If the comparator polarity is not inverted:
  *          - Comparator output is low when the input plus
  *            is at a lower voltage than the input minus
  *          - Comparator output is high when the input plus
  *            is at a higher voltage than the input minus
  *         If the comparator polarity is inverted:
  *          - Comparator output is high when the input plus
  *            is at a lower voltage than the input minus
  *          - Comparator output is low when the input plus
  *            is at a higher voltage than the input minus
  * @rmtoll
  *  SR       C1VAL          LL_COMP_ReadOutputLevel
  * @param  p_comp Comparator instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_COMP_OUTPUT_LEVEL_LOW
  *         @arg @ref LL_COMP_OUTPUT_LEVEL_HIGH
  */
__STATIC_INLINE uint32_t LL_COMP_ReadOutputLevel(const COMP_TypeDef *p_comp)
{
  return (uint32_t)(READ_BIT(p_comp->SR, COMP_SR_C1VAL));
}

/**
  * @}
  */

/** @defgroup COMP_LL_EF_FLAG_Management Comparator flag Management
  * @{
  */

/**
  * @brief  Get comparator output trigger flag (latched)
  * @rmtoll
  *  SR       C1IF           LL_COMP_IsActiveFlag_OutputTrig
  * @param  p_comp Comparator instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_COMP_IsActiveFlag_OutputTrig(COMP_TypeDef *p_comp)
{
  return ((READ_BIT(p_comp->SR, COMP_SR_C1IF) == (COMP_SR_C1IF)) ? 1UL : 0UL);
}

/**
  * @brief  Clear comparator comparator output trigger flag (latched)
  * @rmtoll
  *  ICFR     CC1IF          LL_COMP_ClearFlag_OutputTrig
  * @param  p_comp Comparator instance
  */
__STATIC_INLINE void LL_COMP_ClearFlag_OutputTrig(COMP_TypeDef *p_comp)
{
  SET_BIT(p_comp->ICFR, COMP_ICFR_CC1IF);
}

/**
  * @}
  */

/** @defgroup COMP_LL_EF_IT_Management Comparartor IT management
  * @{
  */

/**
  * @brief  Enable comparator output trigger interrupt
  * @rmtoll
  *  ICFR     ITEN           LL_COMP_EnableIT_OutputTrig
  * @param  p_comp Comparator instance
  */
__STATIC_INLINE void LL_COMP_EnableIT_OutputTrig(COMP_TypeDef *p_comp)
{
  SET_BIT(p_comp->CFGR1, COMP_CFGR1_ITEN);
}

/**
  * @brief  Disable comparator output trigger interrupt
  * @rmtoll
  *  ICFR     ITEN           LL_COMP_DisableIT_OutputTrig
  * @param  p_comp Comparator instance
  */
__STATIC_INLINE void LL_COMP_DisableIT_OutputTrig(COMP_TypeDef *p_comp)
{
  CLEAR_BIT(p_comp->CFGR1, COMP_CFGR1_ITEN);
}

/**
  * @brief  Get comparator output trigger interrupt state
  * @rmtoll
  *  ICFR     ITEN           LL_COMP_IsEnabledIT_OutputTrig
  * @param  p_comp Comparator instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_COMP_IsEnabledIT_OutputTrig(COMP_TypeDef *p_comp)
{
  return ((READ_BIT(p_comp->CFGR1, COMP_CFGR1_ITEN) == (COMP_CFGR1_ITEN)) ? 1UL : 0UL);
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

#endif /* COMP1 */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* STM32C5XX_LL_COMP_H */
