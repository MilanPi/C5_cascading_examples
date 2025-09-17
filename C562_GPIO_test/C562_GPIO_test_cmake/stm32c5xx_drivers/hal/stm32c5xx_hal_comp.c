/**
  ******************************************************************************
  * @file    stm32c5xx_hal_comp.c
  * @author  GPM Application Team
  * @brief   COMP HAL module driver.
  *          This file provides firmware functions to manage the following
  *          functionalities of the COMP (analog comparator) peripheral:
  *           + Initialization and de-initialization functions
  *           + IO operation functions
  *           + Peripheral state and errors functions
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

/* Includes ------------------------------------------------------------------*/
#include "stm32_hal.h"

/** @addtogroup STM32C5xx_HAL_Driver
  * @{
  */

/** @addtogroup COMP
  * @{
# How to use the COMP (analog comparator) HAL module driver

## HAL COMP driver usage

- COMP configuration
  - System configuration (out of HAL COMP driver)
    - RCC to provide COMP kernel clock
    - GPIO to connect comparator inputs and output to device pins
    - CPU Cortex NVIC to configure interrupts lines (if COMP usage with interrupt)
  - COMP peripheral configuration
    - COMP peripheral is structured in subblocks with each a specific scope.
      HAL COMP follows this structure with a configuration structure and associated function for each subblock.
        - COMP instance subblock
          - basic configuration (prefix HAL_COMP)
          - output blanking from signal of other peripheral (typically: timer) (optional)
        - COMP multi-instances subblocks
          - window mode (prefix HAL_COMP_WINDOW): combine multiple COMP instances for voltage comparison
            to 2 thresholds.
    - COMP instances can belong to a COMP common instance, in this case they can share features (window mode,
      other shared features, ...). HAL COMP driver provides a mechanism to link HAL COMP handles
      and manage shared features.
  - HAL COMP configuration steps:
    1. Configure system
    2. Initialize HAL COMP handle using HAL_COMP_Init()
    3. Case of multiple COMP instances used: Link HAL COMP handles using HAL_COMP_WINDOW_SetHandle()
       (for more details, refer to function description).
    4. Configure comparator using functions HAL_COMP_[WINDOW]_SetConfig{Features}()
       and optional features with unitary functions HAL_COMP_[WINDOW]_Set{Features}()

- COMP operation
  - Activation and deactivation
    - COMP peripheral requires a specific procedure for activation (internal analog circuitry control, delay for
      stabilization time).
      Note: From activation step, COMP internal analog hardware is enabled, inducing current consumption.
            Therefore, after COMP usage, COMP must be deactivated for power optimization.
  - COMP analog comparison management
    - Comparisons can be performed using two programming models:
      - Background operation (for system wake up, asynchronous read of comparator output, comparator output on GPIO:
        using HAL_COMP_[WINDOW]_Start()
      - Interrupt mode: using HAL_COMP_[WINDOW]_StartConv_IT(), HAL_COMP_IRQHandler() and callback functions
  - HAL COMP operation steps:
    1. Activate and start COMP comparison using functions HAL_COMP_[WINDOW]_Start...().
       Optionally, lock comparator using function HAL_COMP_[WINDOW]_Lock(): for safety purpose, comparator
       configuration frozen until system reset.
    2. Process comparison using HAL_COMP_[WINDOW]_GetOutputLevel(), IRQ handler and callback functions
    3. Deactivate and stop COMP comparison using functions HAL_COMP_[WINDOW]_Stop...() (if not locked).

## Callback registration
When the compilation flag USE_HAL_COMP_REGISTER_CALLBACKS is set to 1,
functions HAL_COMP_Register...Callback() allow to register following callbacks:
  - @ref HAL_COMP_OutputTriggerCallback() : COMP output trigger callback

When the compilation flag USE_HAL_COMP_REGISTER_CALLBACKS is set to 0 or not defined,
the callback registration feature is not available and all callbacks are set to the corresponding weak functions.

## Configuration inside the COMP driver

Config defines                  | Description           | Default value | Note
------------------------------- | --------------------- | ------------- | --------------------------------------------
USE_HAL_COMP_MODULE             | from hal_conf.h       | 1  | When set, HAL COMP module is enabled
USE_HAL_COMP_EXTI               | from hal_conf.h       | 1  | When set, HAL COMP can be used with EXTI
.                               |                       |    | (needed for event and IT operation)
USE_HAL_COMP_REGISTER_CALLBACKS | from hal_conf.h       | 0  | When defined, enable the register callbacks assert
USE_HAL_COMP_CLK_ENABLE_MODEL   | from hal_conf.h       | HAL_CLK_ENABLE_NO | Enable the gating of the peripheral clock
USE_HAL_CHECK_PARAM             | from hal_conf.h       | 0  | Parameters (pointers or sizes) are checked in runtime
USE_HAL_CHECK_PROCESS_STATE     | from hal_conf.h       | 0  | When set, enable atomic access to process state check
USE_ASSERT_DBG_PARAM            | from PreProcessor env | NA | When defined, enable the params assert
USE_ASSERT_DBG_STATE            | from PreProcessor env | NA | When defined, enable the state assert
COMP_WINDOW_MODE_SUPPORT        | from CMSIS | Defined  | When defined, COMP window mode features are available
  */

#if defined(USE_HAL_COMP_MODULE) && (USE_HAL_COMP_MODULE == 1)

/* Private constants ---------------------------------------------------------*/
/** @defgroup COMP_Private_Constants COMP Private Constants
  * @{
  */

#if defined(USE_HAL_COMP_EXTI) && (USE_HAL_COMP_EXTI == 1)
/*! Comparator EXTI Lines associated to comparator instances */
#define EXTI_COMP1                      (LL_EXTI_LINE_34)  /*!< EXTI line connected to comparator output: COMP1 */
#if defined(COMP2)
#define EXTI_COMP2                      (0)  /*!< EXTI line connected to comparator output: COMP2 */
#warning "C5 COMP: EXTI line for COMP2 to implement"
#endif /* COMP2 */
#endif /* USE_HAL_COMP_EXTI */

/**
  * @}
  */

/* Private macros -------------------------------------------------------------*/
/** @defgroup COMP_Private_Macros COMP Private Macros
  * @{
  */

/*! Get COMP instance from the selected HAL COMP handle */
#define COMP_GET_INSTANCE(hcomp) ((COMP_TypeDef *)((uint32_t)(hcomp)->instance))

#if defined(USE_HAL_COMP_EXTI) && (USE_HAL_COMP_EXTI == 1)
/*! Get the EXTI line associated to a comparator instance */
#if defined(COMP2)
#define COMP_GET_EXTI_LINE(instance)    (((instance) == HAL_COMP1) ? EXTI_COMP1 : EXTI_COMP2)
#else
#define COMP_GET_EXTI_LINE(instance)    EXTI_COMP1
#endif /* COMP2 */
#endif /* USE_HAL_COMP_EXTI */

/**
  * @brief Wait for approximate delay in us.
  * @param delay_us Delay to wait for (unit: us).
  * @note  Compute number of CPU cycles to wait for, using CMSIS global variable "SystemCoreClock".
  * @note  Delay is approximate (depends on compilation optimization).
  * @note  Computation: variable is divided by 2 to compensate partially CPU processing cycles of wait loop
  *        (total shift right of 21 bits, including conversion from frequency in MHz).
  *        If system core clock frequency is below 500kHz, delay is fulfilled by few CPU processing cycles.
  */
#define COMP_DELAY_US(delay_us)                                                        \
  do {                                                                                 \
    volatile uint32_t wait_loop_index = ((delay_us * (SystemCoreClock >> 19U)) >> 2U); \
    while (wait_loop_index != 0UL) {                                                   \
      wait_loop_index--;                                                               \
    }                                                                                  \
  } while(0)

/**
  * @brief IS_COMP macro assert definitions
  * @{
  */
/*! Assert definitions of comparator power mode */
#define IS_COMP_POWER_MODE(power_mode) (((power_mode) == HAL_COMP_POWER_MODE_HIGH_SPEED) \
                                        || ((power_mode) == HAL_COMP_POWER_MODE_MEDIUM_SPEED) \
                                        || ((power_mode) == HAL_COMP_POWER_MODE_ULTRA_LOW_POWER))

/*! Assert definitions of comparator input plus */
#define IS_COMP_INPUT_PLUS(input_plus) (((input_plus) == HAL_COMP_INPUT_PLUS_IO1) \
                                        || ((input_plus) == HAL_COMP_INPUT_PLUS_IO2) \
                                        || ((input_plus) == HAL_COMP_INPUT_PLUS_IO3) \
                                        || ((input_plus) == HAL_COMP_INPUT_PLUS_DAC1_CH1))

/*! Assert definitions of comparator input minus */
#define IS_COMP_INPUT_MINUS(input_minus) (((input_minus) == HAL_COMP_INPUT_MINUS_VREFINT) \
                                          || ((input_minus) == HAL_COMP_INPUT_MINUS_1_2VREFINT) \
                                          || ((input_minus) == HAL_COMP_INPUT_MINUS_1_4VREFINT) \
                                          || ((input_minus) == HAL_COMP_INPUT_MINUS_3_4VREFINT) \
                                          || ((input_minus) == HAL_COMP_INPUT_MINUS_IO1) \
                                          || ((input_minus) == HAL_COMP_INPUT_MINUS_IO2) \
                                          || ((input_minus) == HAL_COMP_INPUT_MINUS_IO3) \
                                          || ((input_minus) == HAL_COMP_INPUT_MINUS_DAC1_CH1) \
                                          || ((input_minus) == HAL_COMP_INPUT_MINUS_TEMPSENSOR))

/*! Assert definitions of comparator input hysteresis */
#define IS_COMP_INPUT_HYSTERESIS(input_hysteresis) (((input_hysteresis) == HAL_COMP_INPUT_HYSTERESIS_NONE) \
                                                    || ((input_hysteresis) == HAL_COMP_INPUT_HYSTERESIS_LOW) \
                                                    || ((input_hysteresis) == HAL_COMP_INPUT_HYSTERESIS_MEDIUM) \
                                                    || ((input_hysteresis) == HAL_COMP_INPUT_HYSTERESIS_HIGH))

/*! Assert definitions of comparator output polarity */
#define IS_COMP_OUTPUT_POLARITY(output_polarity) (((output_polarity) == HAL_COMP_OUTPUT_POLARITY_NONINVERTED) \
                                                  || ((output_polarity) == HAL_COMP_OUTPUT_POLARITY_INVERTED))

/*! Assert definitions of comparator output blanking */
#define IS_COMP_OUTPUT_BLANK(output_blank) (((output_blank) == HAL_COMP_OUTPUT_BLANK_NONE) \
                                            || ((output_blank) == HAL_COMP_OUTPUT_BLANK_TIM1_OC5) \
                                            || ((output_blank) == HAL_COMP_OUTPUT_BLANK_TIM2_OC3) \
                                            || ((output_blank) == HAL_COMP_OUTPUT_BLANK_TIM5_OC3) \
                                            || ((output_blank) == HAL_COMP_OUTPUT_BLANK_TIM5_OC4) \
                                            || ((output_blank) == HAL_COMP_OUTPUT_BLANK_TIM8_OC5) \
                                            || ((output_blank) == HAL_COMP_OUTPUT_BLANK_TIM15_OC2))

#if defined(USE_HAL_COMP_EXTI) && (USE_HAL_COMP_EXTI == 1)
/*! Assert definitions of comparator output trigger */
#define IS_COMP_OUTPUT_TRIG(output_trigger) (((output_trigger) == HAL_COMP_OUTPUT_TRIG_NONE) \
                                             || ((output_trigger) == HAL_COMP_OUTPUT_TRIG_RISING)  \
                                             || ((output_trigger) == HAL_COMP_OUTPUT_TRIG_FALLING) \
                                             || ((output_trigger) == HAL_COMP_OUTPUT_TRIG_RISING_FALLING))
#else
/*! Assert definitions of comparator output trigger */
#define IS_COMP_OUTPUT_TRIG(output_trigger) ((output_trigger) == HAL_COMP_OUTPUT_TRIG_NONE)
#endif /* USE_HAL_COMP_EXTI */

/*! Assert definitions of comparator event */
#define IS_COMP_EVENT(event) ((event) == HAL_COMP_EVENT_OUTPUT_TRIGGER)

/**
  * @}
  */

/**
  * @}
  */

/* Private functions ---------------------------------------------------------*/
/** @defgroup COMP_Private_Functions COMP Private Functions
  * @{
  */
static hal_status_t comp_activate(hal_comp_handle_t *hcomp);
/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @addtogroup COMP_Exported_Functions
  * @{
  */

/** @addtogroup COMP_Exported_Functions_Group1
  * @{
    Set of functions allowing to initialize and deinitialize the COMPx peripheral:
      + HAL_COMP_Init(): associate HAL COMP handle with selected COMP instance,
      + HAL_COMP_DeInit(): restore the default configuration of the HAL COMP handle,
      + HAL_COMP_WINDOW_SetHandle(): link HAL COMP handles sharing common features (window mode).
  */

/**
  * @brief  Initialize HAL COMP handle and associate it to the selected COMP instance.
  * @param  hcomp Pointer to a hal_comp_handle_t structure.
  * @param  instance COMP instance.
  * @retval HAL_INVALID_PARAM Invalid parameter
  * @retval HAL_ERROR         HAL COMP handle is already initialized and can not be modified.
  * @retval HAL_OK            HAL COMP handle has been correctly initialized.
  */
hal_status_t HAL_COMP_Init(hal_comp_handle_t *hcomp, hal_comp_t instance)
{
  ASSERT_DBG_PARAM(hcomp != NULL);
  ASSERT_DBG_PARAM(IS_COMP_ALL_INSTANCE((COMP_TypeDef *)((uint32_t)instance)));

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (hcomp == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hcomp->instance = instance;

#if defined(USE_HAL_COMP_USER_DATA) && (USE_HAL_COMP_USER_DATA == 1)
  hcomp->p_user_data = (void *) NULL;
#endif /* USE_HAL_COMP_USER_DATA */

#if defined(USE_HAL_COMP_REGISTER_CALLBACKS) && (USE_HAL_COMP_REGISTER_CALLBACKS == 1U)
  /* Init the COMP Callback settings */
  hcomp->p_output_trigger_cb = HAL_COMP_OutputTriggerCallback;
#endif /* USE_HAL_COMP_REGISTER_CALLBACKS */

#if defined(USE_HAL_COMP_EXTI) && (USE_HAL_COMP_EXTI == 1)
  hcomp->exti_line = COMP_GET_EXTI_LINE(instance);
  hcomp->output_trigger = HAL_COMP_OUTPUT_TRIG_NONE;
#endif /* USE_HAL_COMP_EXTI */

#if defined(USE_HAL_COMP_CLK_ENABLE_MODEL) && (USE_HAL_COMP_CLK_ENABLE_MODEL > HAL_CLK_ENABLE_NO)
  /* Enable peripheral clock */
  HAL_RCC_COMP1_EnableClock();
#endif /* USE_HAL_COMP_CLK_ENABLE_MODEL */

  /* Initialize HAL COMP state machine */
  hcomp->global_state = HAL_COMP_STATE_INIT;

  return HAL_OK;
}

/**
  * @brief  Deinitialize the COMP peripheral.
  * @param  hcomp Pointer to a hal_comp_handle_t structure.
  */
void HAL_COMP_DeInit(hal_comp_handle_t *hcomp)
{
  ASSERT_DBG_PARAM(hcomp != NULL);

  /* Stop the current operations */
  if (hcomp->global_state == HAL_COMP_STATE_ACTIVE)
  {
    LL_COMP_Disable(COMP_GET_INSTANCE(hcomp));
  }
  else
  {
    /* No action */
  }

#if defined(USE_HAL_COMP_EXTI) && (USE_HAL_COMP_EXTI == 1)
  LL_EXTI_DisableEvent_32_63(hcomp->exti_line);
  LL_EXTI_DisableIT_32_63(hcomp->exti_line);
  LL_EXTI_DisableRisingTrig_32_63(hcomp->exti_line);
  LL_EXTI_DisableFallingTrig_32_63(hcomp->exti_line);
#endif /* USE_HAL_COMP_EXTI */

#if defined(USE_HAL_COMP_USER_DATA) && (USE_HAL_COMP_USER_DATA == 1)
  hcomp->p_user_data = NULL;
#endif /* USE_HAL_COMP_USER_DATA */

  hcomp->global_state = HAL_COMP_STATE_RESET;
}

/**
  * @}
  */

/** @addtogroup COMP_Exported_Functions_Group2
  * @{
    Set of functions allowing to configure COMPx peripheral:
      + HAL_COMP_SetConfig(): Configure comparator.
      + HAL_COMP_GetConfig(): Get comparator configuration.
      + HAL_COMP_SetInputPlus(): Unitary configuration: Set comparator input plus configuration.
      + HAL_COMP_GetInputPlus(): Unitary configuration: Get comparator input plus configuration.
      + HAL_COMP_SetInputMinus(): Unitary configuration: Set comparator input minus configuration.
      + HAL_COMP_GetInputMinus(): Unitary configuration: Get comparator input minus configuration.
      + HAL_COMP_SetOutputBlanking(): Unitary configuration: Set comparator output blanking (optional).
      + HAL_COMP_GetOutputBlanking(): Unitary configuration: Get comparator output blanking (optional).
      + HAL_COMP_WINDOW_SetConfig(): Configure comparators in window mode.
      + HAL_COMP_WINDOW_GetConfig(): Get window comparators configuration.
      + HAL_COMP_WINDOW_SetInput(): Unitary configuration: Set window comparators input plus configuration
        (common to both comparator instances)
      + HAL_COMP_WINDOW_GetInput(): Unitary configuration: Get window comparators input plus configuration
        (common to both comparator instances)
      + HAL_COMP_WINDOW_SetUpperThreshold(): Unitary configuration: Set window comparators input minus configuration
        (for comparator instance assigned to upper threshold)
      + HAL_COMP_WINDOW_GetUpperThreshold(): Unitary configuration: Set window comparators input minus configuration
        (for comparator instance assigned to upper threshold)
      + HAL_COMP_WINDOW_SetLowerThreshold(): Unitary configuration: Set window comparators input minus configuration
        (for comparator instance assigned to lower threshold)
      + HAL_COMP_WINDOW_GetLowerThreshold(): Unitary configuration: Set window comparators input minus configuration
        (for comparator instance assigned to lower threshold)
      + HAL_COMP_WINDOW_SetOutputBlanking(): Unitary configuration: Set window comparators output blanking (optional).
      + HAL_COMP_WINDOW_GetOutputBlanking(): Unitary configuration: Get window comparators output blanking (optional).
  */

/**
  * @brief  Configure comparator.
  * @param  hcomp Pointer to a @ref hal_comp_handle_t structure.
  * @param  p_config Pointer to a @ref hal_comp_config_t structure containing COMP configuration.
  * @retval HAL_INVALID_PARAM Invalid parameter.
  * @retval HAL_ERROR         Operation completed with error.
  * @retval HAL_OK            Operation completed successfully.
  */
hal_status_t HAL_COMP_SetConfig(hal_comp_handle_t *hcomp, const hal_comp_config_t *p_config)
{
  hal_status_t status = HAL_ERROR;
  COMP_TypeDef *p_instance;
  uint32_t reg_config;

  ASSERT_DBG_PARAM(hcomp != NULL);
  ASSERT_DBG_PARAM((p_config != NULL));

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_config == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  ASSERT_DBG_PARAM(IS_COMP_POWER_MODE(p_config->power_mode));
  ASSERT_DBG_PARAM(IS_COMP_INPUT_PLUS(p_config->input_plus));
  ASSERT_DBG_PARAM(IS_COMP_INPUT_MINUS(p_config->input_minus));
  ASSERT_DBG_PARAM(IS_COMP_INPUT_HYSTERESIS(p_config->input_hysteresis));
  ASSERT_DBG_PARAM(IS_COMP_OUTPUT_POLARITY(p_config->output_polarity));
#if defined(USE_HAL_COMP_EXTI) && (USE_HAL_COMP_EXTI == 1)
  ASSERT_DBG_PARAM(IS_COMP_OUTPUT_TRIG(p_config->output_trigger));
#endif /* USE_HAL_COMP_EXTI */

  ASSERT_DBG_STATE(hcomp->global_state,
                   (uint32_t)HAL_COMP_STATE_INIT |
                   (uint32_t)HAL_COMP_STATE_IDLE |
                   (uint32_t)HAL_COMP_STATE_LINKED);

  p_instance = COMP_GET_INSTANCE(hcomp);

  if (LL_COMP_IsLocked(p_instance) == 0UL)
  {
    /* Set COMP configuration in a single register write access
       (equivalent to successive calls of configuration functions LL_COMP_Set...()) */
    reg_config = LL_COMP_READ_REG(p_instance, CFGR1);
    reg_config &= ~(COMP_CFGR1_PWRMODE
                    | COMP_CFGR1_INPSEL
                    | COMP_CFGR1_INMSEL
                    | COMP_CFGR1_SCALEN
                    | COMP_CFGR1_BRGEN
                    | COMP_CFGR1_HYST
                    | COMP_CFGR1_POLARITY);
    reg_config |= ((uint32_t)p_config->power_mode
                   | (uint32_t)p_config->input_plus
                   | (uint32_t)p_config->input_minus
                   | (uint32_t)p_config->input_hysteresis
                   | (uint32_t)p_config->output_polarity);
    LL_COMP_WRITE_REG(p_instance, CFGR1, reg_config);

#if defined(USE_HAL_COMP_EXTI) && (USE_HAL_COMP_EXTI == 1)
    /* Set HAL COMP handle with output trigger state for further usage in operation functions */
    hcomp->output_trigger = p_config->output_trigger;

    /* Set comparator output trigger through EXTI */
    if (((uint32_t)p_config->output_trigger & (uint32_t)HAL_COMP_OUTPUT_TRIG_RISING) != 0U)
    {
      LL_EXTI_EnableRisingTrig_32_63(hcomp->exti_line);
    }
    else
    {
      LL_EXTI_DisableRisingTrig_32_63(hcomp->exti_line);
    }

    if (((uint32_t)p_config->output_trigger & (uint32_t)HAL_COMP_OUTPUT_TRIG_FALLING) != 0U)
    {
      LL_EXTI_EnableFallingTrig_32_63(hcomp->exti_line);
    }
    else
    {
      LL_EXTI_DisableFallingTrig_32_63(hcomp->exti_line);
    }
#endif /* USE_HAL_COMP_EXTI */

    status = HAL_OK;

    hcomp->global_state = HAL_COMP_STATE_IDLE;
  }

  return status;
}

/**
  * @brief  Get comparator configuration.
  * @param  hcomp Pointer to a @ref hal_comp_handle_t structure.
  * @param  p_config Pointer to a @ref hal_comp_config_t structure containing the COMP configuration.
  */
void HAL_COMP_GetConfig(const hal_comp_handle_t *hcomp, hal_comp_config_t *p_config)
{
  COMP_TypeDef *p_instance;
  uint32_t reg_config;

  ASSERT_DBG_PARAM(hcomp != NULL);
  ASSERT_DBG_PARAM((p_config != NULL));

  ASSERT_DBG_STATE(hcomp->global_state,
                   (uint32_t)HAL_COMP_STATE_LINKED |
                   (uint32_t)HAL_COMP_STATE_IDLE |
                   (uint32_t)HAL_COMP_STATE_ACTIVE);

  p_instance = COMP_GET_INSTANCE(hcomp);

  /* For optimization purpose, get comparator configuration with one register access.
     (equivalent to calls of unitary LL functions LL_COMP_Getx()) */
  reg_config = LL_COMP_READ_REG(p_instance, CFGR1);
  p_config->power_mode = (hal_comp_power_mode_t)(reg_config & (uint32_t)COMP_CFGR1_PWRMODE);
  p_config->input_hysteresis = (hal_comp_input_hysteresis_t)((uint32_t)(reg_config & COMP_CFGR1_HYST));
  p_config->output_polarity = (hal_comp_output_polarity_t)((uint32_t)(reg_config & COMP_CFGR1_POLARITY));

  p_config->input_plus = (hal_comp_input_plus_t)LL_COMP_GetInputPlus(p_instance);
  p_config->input_minus = (hal_comp_input_minus_t)LL_COMP_GetInputMinus(p_instance);

#if defined(USE_HAL_COMP_EXTI) && (USE_HAL_COMP_EXTI == 1)
  p_config->output_trigger = hcomp->output_trigger;
#endif /* USE_HAL_COMP_EXTI */
}

/**
  * @brief  Set comparator input plus configuration.
  * @param  hcomp Pointer to a @ref hal_comp_handle_t structure.
  * @param  input_plus Value of @ref hal_comp_input_plus_t.
  * @retval HAL_ERROR         Operation completed with error.
  * @retval HAL_OK            Operation completed successfully.
  */
hal_status_t HAL_COMP_SetInputPlus(hal_comp_handle_t *hcomp, hal_comp_input_plus_t input_plus)
{
  hal_status_t status = HAL_OK;
  COMP_TypeDef *p_instance;

  ASSERT_DBG_PARAM(hcomp != NULL);
  ASSERT_DBG_PARAM(IS_COMP_INPUT_PLUS(input_plus));

  ASSERT_DBG_STATE(hcomp->global_state, HAL_COMP_STATE_IDLE);

  p_instance = COMP_GET_INSTANCE(hcomp);
  LL_COMP_SetInputPlus(p_instance, (uint32_t)input_plus);

  return status;
}

/**
  * @brief  Get comparator input plus configuration.
  * @param  hcomp Pointer to a @ref hal_comp_handle_t structure.
  * @retval hal_comp_input_plus_t Comparator input plus value.
  */
hal_comp_input_plus_t HAL_COMP_GetInputPlus(const hal_comp_handle_t *hcomp)
{
  COMP_TypeDef *p_instance;
  hal_comp_input_plus_t input_plus;

  ASSERT_DBG_PARAM(hcomp != NULL);

  ASSERT_DBG_STATE(hcomp->global_state,
                   (uint32_t)HAL_COMP_STATE_LINKED |
                   (uint32_t)HAL_COMP_STATE_IDLE |
                   (uint32_t)HAL_COMP_STATE_ACTIVE);

  p_instance = COMP_GET_INSTANCE(hcomp);
  input_plus = (hal_comp_input_plus_t)LL_COMP_GetInputPlus(p_instance);

  return input_plus;
}

/**
  * @brief  Set comparator input minus configuration.
  * @param  hcomp Pointer to a @ref hal_comp_handle_t structure.
  * @param  input_minus Value of @ref hal_comp_input_minus_t.
  * @retval HAL_ERROR         Operation completed with error.
  * @retval HAL_OK            Operation completed successfully.
  */
hal_status_t HAL_COMP_SetInputMinus(hal_comp_handle_t *hcomp, hal_comp_input_minus_t input_minus)
{
  hal_status_t status = HAL_OK;
  COMP_TypeDef *p_instance;

  ASSERT_DBG_PARAM(hcomp != NULL);
  ASSERT_DBG_PARAM(IS_COMP_INPUT_MINUS(input_minus));

  ASSERT_DBG_STATE(hcomp->global_state, HAL_COMP_STATE_IDLE);

  p_instance = COMP_GET_INSTANCE(hcomp);
  LL_COMP_SetInputMinus(p_instance, (uint32_t)input_minus);

  return status;
}

/**
  * @brief  Get comparator input minus configuration.
  * @param  hcomp Pointer to a @ref hal_comp_handle_t structure.
  * @retval hal_comp_input_minus_t Comparator input minus value.
  */
hal_comp_input_minus_t HAL_COMP_GetInputMinus(const hal_comp_handle_t *hcomp)
{
  COMP_TypeDef *p_instance;
  hal_comp_input_minus_t input_minus;

  ASSERT_DBG_PARAM(hcomp != NULL);

  ASSERT_DBG_STATE(hcomp->global_state,
                   (uint32_t)HAL_COMP_STATE_LINKED |
                   (uint32_t)HAL_COMP_STATE_IDLE |
                   (uint32_t)HAL_COMP_STATE_ACTIVE);

  p_instance = COMP_GET_INSTANCE(hcomp);
  input_minus = (hal_comp_input_minus_t)LL_COMP_GetInputMinus(p_instance);

  return input_minus;
}

/**
  * @brief  Set comparator output blanking.
  * @param  hcomp Pointer to a @ref hal_comp_handle_t structure.
  * @param  output_blank Value of @ref hal_comp_output_blank_t.
  * @retval HAL_ERROR         Operation completed with error.
  * @retval HAL_OK            Operation completed successfully.
  */
hal_status_t HAL_COMP_SetOutputBlanking(hal_comp_handle_t *hcomp, hal_comp_output_blank_t output_blank)
{
  hal_status_t status = HAL_OK;
  COMP_TypeDef *p_instance;

  ASSERT_DBG_PARAM(hcomp != NULL);
  ASSERT_DBG_PARAM(IS_COMP_OUTPUT_BLANK(output_blank));

  ASSERT_DBG_STATE(hcomp->global_state, HAL_COMP_STATE_IDLE);

  p_instance = COMP_GET_INSTANCE(hcomp);
  LL_COMP_SetOutputBlankingSource(p_instance, (uint32_t)output_blank);

  return status;
}

/**
  * @brief  Get comparator output blanking.
  * @param  hcomp Pointer to a @ref hal_comp_handle_t structure.
  * @retval hal_comp_output_blank_t Comparator output blanking value.
  */
hal_comp_output_blank_t HAL_COMP_GetOutputBlanking(hal_comp_handle_t *hcomp)
{
  COMP_TypeDef *p_instance;
  hal_comp_output_blank_t output_blank;

  ASSERT_DBG_PARAM(hcomp != NULL);

  ASSERT_DBG_STATE(hcomp->global_state,
                   (uint32_t)HAL_COMP_STATE_LINKED |
                   (uint32_t)HAL_COMP_STATE_IDLE |
                   (uint32_t)HAL_COMP_STATE_ACTIVE);

  p_instance = COMP_GET_INSTANCE(hcomp);
  output_blank = (hal_comp_output_blank_t) LL_COMP_GetOutputBlankingSource(p_instance);

  return output_blank;
}

/**
  * @}
  */

/** @addtogroup COMP_Exported_Functions_Group3
  * @{
    Set of function to handle the COMP interruptions :
      + HAL_COMP_IRQHandler(): Handle all COMP interrupt requests.
  */

/**
  * @brief  Handle the COMP interrupt request.
  * @param  hcomp Pointer to a hal_comp_handle_t structure.
  */
void HAL_COMP_IRQHandler(hal_comp_handle_t *hcomp)
{
#if defined(USE_HAL_COMP_EXTI) && (USE_HAL_COMP_EXTI == 1)
  /* Check COMP EXTI flag */
  if (LL_EXTI_IsActiveRisingFlag_32_63(hcomp->exti_line) != 0UL)
  {
    LL_EXTI_ClearRisingFlag_32_63(hcomp->exti_line);
    LL_COMP_ClearFlag_OutputTrig(COMP_GET_INSTANCE(hcomp));

#if defined(USE_HAL_COMP_REGISTER_CALLBACKS) && (USE_HAL_COMP_REGISTER_CALLBACKS == 1)
    hcomp->p_output_trigger_cb(hcomp);
#else
    HAL_COMP_OutputTriggerCallback(hcomp);
#endif /* USE_HAL_COMP_REGISTER_CALLBACKS */
  }
  if (LL_EXTI_IsActiveFallingFlag_32_63(hcomp->exti_line) != 0UL)
  {
    LL_EXTI_ClearFallingFlag_32_63(hcomp->exti_line);
    LL_COMP_ClearFlag_OutputTrig(COMP_GET_INSTANCE(hcomp));

#if defined(USE_HAL_COMP_REGISTER_CALLBACKS) && (USE_HAL_COMP_REGISTER_CALLBACKS == 1)
    hcomp->p_output_trigger_cb(hcomp);
#else
    HAL_COMP_OutputTriggerCallback(hcomp);
#endif /* USE_HAL_COMP_REGISTER_CALLBACKS */
  }
#else
  STM32_UNUSED(hcomp);
#endif /* USE_HAL_COMP_EXTI */
}

/**
  * @brief  Event callback.
  * @param  hcomp Pointer to a hal_comp_handle_t structure
  */
__WEAK void HAL_COMP_OutputTriggerCallback(hal_comp_handle_t *hcomp)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hcomp);

  /* Note : This function must not be modified. When the callback is needed, function
            HAL_COMP_EventICallback() can be implemented in the user file. */
}

#if defined(USE_HAL_COMP_REGISTER_CALLBACKS) && (USE_HAL_COMP_REGISTER_CALLBACKS == 1)
/**
  * @brief  Register the COMP output trigger callback to be used instead of
            the weak HAL_COMP_OutputTriggerCallback() predefined callback.
  * @param  hcomp Pointer to a hal_comp_handle_t structure.
  * @param  p_callback Pointer to the hal_comp_cb_t Comparator trigger callback function.
  * @retval HAL_INVALID_PARAM Invalid parameter
  * @retval HAL_ERROR         Operation completed with error.
  * @retval HAL_OK            Operation completed successfully.
  */
hal_status_t HAL_COMP_RegisterOutputTriggerCallback(hal_comp_handle_t *hcomp, hal_comp_cb_t p_callback)
{
  ASSERT_DBG_PARAM((hcomp != NULL));
  ASSERT_DBG_PARAM((p_callback != NULL));

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hcomp->p_output_trigger_cb = p_callback;

  return HAL_OK;
}
#endif /* USE_HAL_COMP_REGISTER_CALLBACKS */

/**
  * @}
  */

/** @addtogroup COMP_Exported_Functions_Group4
  * @{
    Set of function to handle the HAL COMP driver state and errors:
      + HAL_COMP_GetState(): Retrieve the HAL COMP global state,
      + HAL_COMP_GetEXTI_Handle(): Retrieve the HAL EXTI handle used by the selected HAL COMP handle.
  */

/**
  * @brief  Retrieve the HAL COMP global state.
  * @param  hcomp Pointer to a hal_comp_handle_t structure.
  * @retval hal_comp_state_t HAL COMP global state.
  */
hal_comp_state_t HAL_COMP_GetState(const hal_comp_handle_t *hcomp)
{
  ASSERT_DBG_PARAM((hcomp != NULL));

  return hcomp->global_state;
}

/**
  * @}
  */

/** @addtogroup COMP_Exported_Functions_Group5
  * @{
    Set of functions allowing to operate COMPx peripheral.
      + HAL_COMP_Start(): Start comparator
      + HAL_COMP_Stop(): Stop comparator
      + HAL_COMP_Start_IT(): Start comparator with interruption
      + HAL_COMP_Stop_IT(): Stop comparator with interruption
      + HAL_COMP_Lock(): Lock comparator
      + HAL_COMP_IsLocked(): Check whether comparator is locked
      + HAL_COMP_GetOutputLevel(): Get comparator output logical level
      + HAL_COMP_WINDOW_Start(): Start window comparators
      + HAL_COMP_WINDOW_Stop(): Stop window comparators
      + HAL_COMP_WINDOW_Start_IT(): Start window comparators with interruption
      + HAL_COMP_WINDOW_Stop_IT(): Stop window comparators with interruption
      + HAL_COMP_WINDOW_Lock(): Lock window comparators
      + HAL_COMP_WINDOW_IsLocked(): Check whether window comparators is locked
      + HAL_COMP_WINDOW_GetOutputLevel(): Get window comparators output logical level
  */

/**
  * @brief  Start comparator
  * @param  hcomp Pointer to a hal_comp_handle_t structure
  * @note   Depending on configuration of output trigger to system (hal_comp_output_trigger_t),
  *         comparator can generate events to system.
  *         Output trigger edge selection is optional (selected parameter can be no trigger).
  * @retval HAL_BUSY          HAL COMP state machine not in expected initial state
  * @retval HAL_ERROR         Operation completed with error.
  * @retval HAL_OK            Operation completed successfully.
  */
hal_status_t HAL_COMP_Start(hal_comp_handle_t *hcomp)
{
  hal_status_t status;

  ASSERT_DBG_PARAM(hcomp != NULL);

  ASSERT_DBG_STATE(hcomp->global_state, HAL_COMP_STATE_IDLE);

  HAL_CHECK_UPDATE_STATE(hcomp, global_state, HAL_COMP_STATE_IDLE, HAL_COMP_STATE_ACTIVE);

  /* Activate comparator */
  status = comp_activate(hcomp);

  if (status != HAL_OK)
  {
    hcomp->global_state = HAL_COMP_STATE_IDLE;
  }
#if defined(USE_HAL_COMP_EXTI) && (USE_HAL_COMP_EXTI == 1)
  else
  {
    if (hcomp->output_trigger != HAL_COMP_OUTPUT_TRIG_NONE)
    {
      LL_EXTI_ClearRisingFlag_32_63(hcomp->exti_line);
      LL_EXTI_ClearFallingFlag_32_63(hcomp->exti_line);
      LL_EXTI_EnableEvent_32_63(hcomp->exti_line);
    }
  }
#endif /* USE_HAL_COMP_EXTI */

  return status;
}

/**
  * @brief  Stop comparator.
  * @param  hcomp Pointer to a hal_comp_handle_t structure.
  * @retval HAL_ERROR         Operation completed with error.
  * @retval HAL_OK            Operation completed successfully.
  */
hal_status_t HAL_COMP_Stop(hal_comp_handle_t *hcomp)
{
  hal_status_t status = HAL_ERROR;

  ASSERT_DBG_PARAM(hcomp != NULL);

  ASSERT_DBG_STATE(hcomp->global_state,
                   (uint32_t)HAL_COMP_STATE_ACTIVE);

  /* Deactivate comparator */
  if (LL_COMP_IsLocked(COMP_GET_INSTANCE(hcomp)) == 0UL)
  {
    LL_COMP_Disable(COMP_GET_INSTANCE(hcomp));

#if defined(USE_HAL_COMP_EXTI) && (USE_HAL_COMP_EXTI == 1)
    if (hcomp->output_trigger != HAL_COMP_OUTPUT_TRIG_NONE)
    {
      LL_EXTI_DisableEvent_32_63(hcomp->exti_line);
    }
#endif /* USE_HAL_COMP_EXTI */

    status = HAL_OK;

    hcomp->global_state = HAL_COMP_STATE_IDLE;
  }

  return status;
}

#if defined(USE_HAL_COMP_EXTI) && (USE_HAL_COMP_EXTI == 1)
/**
  * @brief  Start comparator with interruption: default interruptions.
  * @param  hcomp Pointer to a hal_comp_handle_t structure.
  * @note   Depending on configuration of output trigger to system @ref hal_comp_output_trigger_t,
  *         comparator can generate events and interruption to system.
  *         Output trigger edge selection is mandatory (selected parameter must be different of no trigger).
  * @retval HAL_BUSY          HAL COMP state machine not in expected initial state
  * @retval HAL_ERROR         Operation completed with error.
  * @retval HAL_OK            Operation completed successfully.
  */
hal_status_t HAL_COMP_Start_IT(hal_comp_handle_t *hcomp)
{
  hal_status_t status;

  ASSERT_DBG_PARAM(hcomp != NULL);
#if defined(USE_ASSERT_DBG_PARAM)
  ASSERT_DBG_PARAM(hcomp->output_trigger != HAL_COMP_OUTPUT_TRIG_NONE);
#endif /* USE_ASSERT_DBG_PARAM */

  ASSERT_DBG_STATE(hcomp->global_state, HAL_COMP_STATE_IDLE);

  HAL_CHECK_UPDATE_STATE(hcomp, global_state, HAL_COMP_STATE_IDLE, HAL_COMP_STATE_ACTIVE);

  /* Activate comparator */
  status = comp_activate(hcomp);

  if (status == HAL_OK)
  {
    LL_EXTI_ClearRisingFlag_32_63(hcomp->exti_line);
    LL_EXTI_ClearFallingFlag_32_63(hcomp->exti_line);
    LL_EXTI_EnableIT_32_63(hcomp->exti_line);
    LL_COMP_EnableIT_OutputTrig(COMP_GET_INSTANCE(hcomp));
  }
  else
  {
    hcomp->global_state = HAL_COMP_STATE_IDLE;
  }

  return status;
}

/**
  * @brief  Stop comparator in interruption mode.
  * @param  hcomp Pointer to a hal_comp_handle_t structure.
  * @retval HAL_ERROR         Operation completed with error.
  * @retval HAL_OK            Operation completed successfully.
  */
hal_status_t HAL_COMP_Stop_IT(hal_comp_handle_t *hcomp)
{
  hal_status_t status = HAL_ERROR;

  ASSERT_DBG_PARAM(hcomp != NULL);

  ASSERT_DBG_STATE(hcomp->global_state,
                   (uint32_t)HAL_COMP_STATE_ACTIVE);

  /* Deactivate comparator */
  if (LL_COMP_IsLocked(COMP_GET_INSTANCE(hcomp)) == 0UL)
  {
    LL_COMP_Disable(COMP_GET_INSTANCE(hcomp));

    LL_COMP_DisableIT_OutputTrig(COMP_GET_INSTANCE(hcomp));
    LL_EXTI_DisableIT_32_63(hcomp->exti_line);

    status = HAL_OK;

    hcomp->global_state = HAL_COMP_STATE_IDLE;
  }

  return status;
}
#endif /* USE_HAL_COMP_EXTI */

/**
  * @brief  Lock comparator.
  * @param  hcomp Pointer to a hal_comp_handle_t structure.
  * @note   Once locked, comparator configuration cannot be changed (use case: safety purpose).
  * @note   Comparator can be unlocked with a system reset.
  * @retval HAL_ERROR         Operation completed with error.
  * @retval HAL_OK            Operation completed successfully.
  */
hal_status_t HAL_COMP_Lock(hal_comp_handle_t *hcomp)
{
  hal_status_t status = HAL_OK;
  COMP_TypeDef *p_instance;

  ASSERT_DBG_PARAM(hcomp != NULL);

  ASSERT_DBG_STATE(hcomp->global_state,
                   (uint32_t)HAL_COMP_STATE_IDLE |
                   (uint32_t)HAL_COMP_STATE_ACTIVE);

  p_instance = COMP_GET_INSTANCE(hcomp);
  LL_COMP_Lock(p_instance);

  return status;
}

/**
  * @brief  Check whether comparator is locked.
  * @param  hcomp Pointer to a hal_comp_handle_t structure.
  * @retval Value of hal_comp_lock_status_t.
  */
hal_comp_lock_status_t HAL_COMP_IsLocked(hal_comp_handle_t *hcomp)
{
  COMP_TypeDef *p_instance;
  hal_comp_lock_status_t lock_state;

  ASSERT_DBG_PARAM(hcomp != NULL);

  ASSERT_DBG_STATE(hcomp->global_state,
                   (uint32_t)HAL_COMP_STATE_IDLE |
                   (uint32_t)HAL_COMP_STATE_ACTIVE);

  p_instance = COMP_GET_INSTANCE(hcomp);
  lock_state = (hal_comp_lock_status_t)LL_COMP_IsLocked(p_instance);

  return lock_state;
}

/**
  * @brief  Get comparator output logical level.
  * @param  hcomp Pointer to a hal_comp_handle_t structure.
  * @retval Value of hal_comp_output_level_t.
  */
hal_comp_output_level_t HAL_COMP_GetOutputLevel(hal_comp_handle_t *hcomp)
{
  hal_comp_output_level_t output_level;
  COMP_TypeDef *p_instance;

  ASSERT_DBG_PARAM(hcomp != NULL);

  ASSERT_DBG_STATE(hcomp->global_state, HAL_COMP_STATE_ACTIVE);

  p_instance = COMP_GET_INSTANCE(hcomp);
  output_level = (hal_comp_output_level_t)LL_COMP_ReadOutputLevel(p_instance);

  return output_level;
}

/**
  * @}
  */

/** @addtogroup COMP_Exported_Functions_Group6  User data functions
  * @{
    This subsection provides functions allowing to:
      + HAL_COMP_SetUserData(): Set a user data pointer (ex: a user context) in a HAL COMP handle,
      + HAL_COMP_GetUserData(): Get a user data pointer (ex: a user context) from a HAL COMP handle.
    @note A typical usage is to set user data pointer before starting a process,
          then retrieve it within the user process completion callback.
  */
#if defined(USE_HAL_COMP_USER_DATA) && (USE_HAL_COMP_USER_DATA == 1)
/**
  * @brief  Store  user data pointer into the comp handle.
  * @param  hcomp Pointer to a hal_comp_handle_t.
  * @param  p_user_data Pointer to the user data.
  */
void HAL_COMP_SetUserData(hal_comp_handle_t *hcomp, const void *p_user_data)
{
  ASSERT_DBG_PARAM(hcomp != NULL);

  hcomp->p_user_data = p_user_data;
}

/**
  * @brief  Retrieve user data pointer from the comp handle.
  * @param  hcomp Pointer to a hal_comp_handle_t.
  * @retval (void*) the pointer to the user data, when previously set by HAL_COMP_SetUserData().
  * @retval NULL other way.
  */
const void *HAL_COMP_GetUserData(const hal_comp_handle_t *hcomp)
{
  ASSERT_DBG_PARAM(hcomp != NULL);

  return (hcomp->p_user_data);
}
#endif /* USE_HAL_COMP_USER_DATA */

/**
  * @}
  */

/**
  * @}
  */

/** @addtogroup COMP_Private_Functions
  * @{
  */

/**
  * @brief  Activate the selected comparator instance.
  * @param  hcomp Pointer to a hal_comp_handle_t structure.
  * @retval HAL_ERROR         Operation completed with error.
  * @retval HAL_OK            Operation completed successfully.
  */
static hal_status_t comp_activate(hal_comp_handle_t *hcomp)
{
  hal_status_t status = HAL_ERROR;
  COMP_TypeDef *p_instance;
  uint32_t delay_startup_us;

  p_instance = COMP_GET_INSTANCE(hcomp);

  if (LL_COMP_IsLocked(p_instance) == 0UL)
  {
    LL_COMP_Enable(p_instance);

    if (LL_COMP_IsInputScalerEnabled(p_instance) != 0UL)
    {
      /* Note: Stabilization delay of voltage scaler encompasses startup delay LL_COMP_DELAY_STARTUP_US */
      delay_startup_us = LL_COMP_DELAY_VOLTAGE_SCALER_STAB_US;
    }
    else
    {
      delay_startup_us = LL_COMP_DELAY_STARTUP_US;
    }

    /* Delay for COMP startup time. */
    COMP_DELAY_US(delay_startup_us);

    status = HAL_OK;
  }

  return status;
}

/**
  * @}
  */

#endif /* USE_HAL_COMP_MODULE */

/**
  * @}
  */

/**
  * @}
  */
