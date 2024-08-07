/*
 * Copyright 2017-2021 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/***********************************************************************************************************************
 * This file was generated by the MCUXpresso Config Tools. Any manual edits made to this file
 * will be overwritten if the respective MCUXpresso Config Tools is used to update this file.
 **********************************************************************************************************************/

#ifndef _PIN_MUX_H_
#define _PIN_MUX_H_

/***********************************************************************************************************************
 * Definitions
 **********************************************************************************************************************/

/*! @brief Direction type  */
typedef enum _pin_mux_direction
{
    kPIN_MUX_DirectionInput = 0U,        /* Input direction */
    kPIN_MUX_DirectionOutput = 1U,       /* Output direction */
    kPIN_MUX_DirectionInputOrOutput = 2U /* Input or output direction */
} pin_mux_direction_t;

/*!
 * @addtogroup pin_mux
 * @{
 */

/***********************************************************************************************************************
 * API
 **********************************************************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @brief Calls initialization functions.
 *
 */
void BOARD_InitBootPins(void);

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitPins(void); /* Function assigned for the Cortex-M0P */

#define IOCON_PIO_CLKDIV0 0x00u      /*!<@brief IOCONCLKDIV0 */
#define IOCON_PIO_HYS_EN 0x20u       /*!<@brief Enable hysteresis */
#define IOCON_PIO_INV_DI 0x00u       /*!<@brief Input not invert */
#define IOCON_PIO_MODE_INACT 0x00u   /*!<@brief No addition pin function */
#define IOCON_PIO_OD_DI 0x00u        /*!<@brief Disables Open-drain function */
#define IOCON_PIO_SMODE_BYPASS 0x00u /*!<@brief Bypass input filter */

/*! @name PIO1_0 (number 11), LD1[3]/CN1[31]/PIO1_0/CAPT_X1
  @{ */
/* Routed pin properties */
/*!
 * @brief Peripheral name */
#define BOARD_INITLEDSPINS_LED_GREEN_PERIPHERAL GPIO
/*!
 * @brief Signal name */
#define BOARD_INITLEDSPINS_LED_GREEN_SIGNAL PIO1
/*!
 * @brief Signal channel */
#define BOARD_INITLEDSPINS_LED_GREEN_CHANNEL 0
/*!
 * @brief Routed pin name */
#define BOARD_INITLEDSPINS_LED_GREEN_PIN_NAME PIO1_0
/*!
 * @brief Label */
#define BOARD_INITLEDSPINS_LED_GREEN_LABEL "LD1[3]/CN1[31]/PIO1_0/CAPT_X1"
/*!
 * @brief Identifier */
#define BOARD_INITLEDSPINS_LED_GREEN_NAME "LED_GREEN"
/*!
 * @brief Direction */
#define BOARD_INITLEDSPINS_LED_GREEN_DIRECTION kPIN_MUX_DirectionOutput

/* Symbols to be used with GPIO driver */
/*!
 * @brief GPIO peripheral base pointer */
#define BOARD_INITLEDSPINS_LED_GREEN_GPIO GPIO
/*!
 * @brief GPIO pin number */
#define BOARD_INITLEDSPINS_LED_GREEN_GPIO_PIN 0U
/*!
 * @brief GPIO pin mask */
#define BOARD_INITLEDSPINS_LED_GREEN_GPIO_PIN_MASK (1U << 0U)
/*!
 * @brief PORT device index: 1 */
#define BOARD_INITLEDSPINS_LED_GREEN_PORT 1U
/*!
 * @brief PORT pin number */
#define BOARD_INITLEDSPINS_LED_GREEN_PIN 0U
/*!
 * @brief PORT pin mask */
#define BOARD_INITLEDSPINS_LED_GREEN_PIN_MASK (1U << 0U)
/* @} */

/*! @name PIO1_1 (number 14), LD1[4]/CN1[30]/PIO1_1/CAPT_X2
  @{ */
/* Routed pin properties */
/*!
 * @brief Peripheral name */
#define BOARD_INITLEDSPINS_LED_BLUE_PERIPHERAL GPIO
/*!
 * @brief Signal name */
#define BOARD_INITLEDSPINS_LED_BLUE_SIGNAL PIO1
/*!
 * @brief Signal channel */
#define BOARD_INITLEDSPINS_LED_BLUE_CHANNEL 1
/*!
 * @brief Routed pin name */
#define BOARD_INITLEDSPINS_LED_BLUE_PIN_NAME PIO1_1
/*!
 * @brief Label */
#define BOARD_INITLEDSPINS_LED_BLUE_LABEL "LD1[4]/CN1[30]/PIO1_1/CAPT_X2"
/*!
 * @brief Identifier */
#define BOARD_INITLEDSPINS_LED_BLUE_NAME "LED_BLUE"
/*!
 * @brief Direction */
#define BOARD_INITLEDSPINS_LED_BLUE_DIRECTION kPIN_MUX_DirectionOutput

/* Symbols to be used with GPIO driver */
/*!
 * @brief GPIO peripheral base pointer */
#define BOARD_INITLEDSPINS_LED_BLUE_GPIO GPIO
/*!
 * @brief GPIO pin number */
#define BOARD_INITLEDSPINS_LED_BLUE_GPIO_PIN 1U
/*!
 * @brief GPIO pin mask */
#define BOARD_INITLEDSPINS_LED_BLUE_GPIO_PIN_MASK (1U << 1U)
/*!
 * @brief PORT device index: 1 */
#define BOARD_INITLEDSPINS_LED_BLUE_PORT 1U
/*!
 * @brief PORT pin number */
#define BOARD_INITLEDSPINS_LED_BLUE_PIN 1U
/*!
 * @brief PORT pin mask */
#define BOARD_INITLEDSPINS_LED_BLUE_PIN_MASK (1U << 1U)
/* @} */

/*! @name PIO1_2 (number 16), LD1[2]/CN1[29]/PIO1_2/CAPT_X3
  @{ */
/* Routed pin properties */
/*!
 * @brief Peripheral name */
#define BOARD_INITLEDSPINS_LED_RED_PERIPHERAL GPIO
/*!
 * @brief Signal name */
#define BOARD_INITLEDSPINS_LED_RED_SIGNAL PIO1
/*!
 * @brief Signal channel */
#define BOARD_INITLEDSPINS_LED_RED_CHANNEL 2
/*!
 * @brief Routed pin name */
#define BOARD_INITLEDSPINS_LED_RED_PIN_NAME PIO1_2
/*!
 * @brief Label */
#define BOARD_INITLEDSPINS_LED_RED_LABEL "LD1[2]/CN1[29]/PIO1_2/CAPT_X3"
/*!
 * @brief Identifier */
#define BOARD_INITLEDSPINS_LED_RED_NAME "LED_RED"
/*!
 * @brief Direction */
#define BOARD_INITLEDSPINS_LED_RED_DIRECTION kPIN_MUX_DirectionOutput

/* Symbols to be used with GPIO driver */
/*!
 * @brief GPIO peripheral base pointer */
#define BOARD_INITLEDSPINS_LED_RED_GPIO GPIO
/*!
 * @brief GPIO pin number */
#define BOARD_INITLEDSPINS_LED_RED_GPIO_PIN 2U
/*!
 * @brief GPIO pin mask */
#define BOARD_INITLEDSPINS_LED_RED_GPIO_PIN_MASK (1U << 2U)
/*!
 * @brief PORT device index: 1 */
#define BOARD_INITLEDSPINS_LED_RED_PORT 1U
/*!
 * @brief PORT pin number */
#define BOARD_INITLEDSPINS_LED_RED_PIN 2U
/*!
 * @brief PORT pin mask */
#define BOARD_INITLEDSPINS_LED_RED_PIN_MASK (1U << 2U)
/* @} */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitLEDsPins(void); /* Function assigned for the Cortex-M0P */

#define IOCON_PIO_CLKDIV0 0x00u      /*!<@brief IOCONCLKDIV0 */
#define IOCON_PIO_HYS_EN 0x20u       /*!<@brief Enable hysteresis */
#define IOCON_PIO_INV_DI 0x00u       /*!<@brief Input not invert */
#define IOCON_PIO_MODE_PULLUP 0x10u  /*!<@brief Selects pull-up function */
#define IOCON_PIO_OD_DI 0x00u        /*!<@brief Disables Open-drain function */
#define IOCON_PIO_SMODE_BYPASS 0x00u /*!<@brief Bypass input filter */

/*! @name PIO0_25 (number 19), CN1[11]/PIO0_25
  @{ */
/* Routed pin properties */
/*!
 * @brief Peripheral name */
#define BOARD_INITDEBUG_UARTPINS_DEBUG_UART_TX_PERIPHERAL USART0
/*!
 * @brief Signal name */
#define BOARD_INITDEBUG_UARTPINS_DEBUG_UART_TX_SIGNAL TXD
/*!
 * @brief Routed pin name */
#define BOARD_INITDEBUG_UARTPINS_DEBUG_UART_TX_PIN_NAME PIO0_25
/*!
 * @brief Label */
#define BOARD_INITDEBUG_UARTPINS_DEBUG_UART_TX_LABEL "CN1[11]/PIO0_25"
/*!
 * @brief Identifier */
#define BOARD_INITDEBUG_UARTPINS_DEBUG_UART_TX_NAME "DEBUG_UART_TX"
/*!
 * @brief PORT device index: 0 */
#define BOARD_INITDEBUG_UARTPINS_DEBUG_UART_TX_PORT 0U
/*!
 * @brief PORT pin number */
#define BOARD_INITDEBUG_UARTPINS_DEBUG_UART_TX_PIN 25U
/*!
 * @brief PORT pin mask */
#define BOARD_INITDEBUG_UARTPINS_DEBUG_UART_TX_PIN_MASK (1U << 25U)
/* @} */

/*! @name PIO0_24 (number 20), CN1[10]/PIO0_24
  @{ */
/* Routed pin properties */
/*!
 * @brief Peripheral name */
#define BOARD_INITDEBUG_UARTPINS_DEBUG_UART_RX_PERIPHERAL USART0
/*!
 * @brief Signal name */
#define BOARD_INITDEBUG_UARTPINS_DEBUG_UART_RX_SIGNAL RXD
/*!
 * @brief Routed pin name */
#define BOARD_INITDEBUG_UARTPINS_DEBUG_UART_RX_PIN_NAME PIO0_24
/*!
 * @brief Label */
#define BOARD_INITDEBUG_UARTPINS_DEBUG_UART_RX_LABEL "CN1[10]/PIO0_24"
/*!
 * @brief Identifier */
#define BOARD_INITDEBUG_UARTPINS_DEBUG_UART_RX_NAME "DEBUG_UART_RX"
/*!
 * @brief PORT device index: 0 */
#define BOARD_INITDEBUG_UARTPINS_DEBUG_UART_RX_PORT 0U
/*!
 * @brief PORT pin number */
#define BOARD_INITDEBUG_UARTPINS_DEBUG_UART_RX_PIN 24U
/*!
 * @brief PORT pin mask */
#define BOARD_INITDEBUG_UARTPINS_DEBUG_UART_RX_PIN_MASK (1U << 24U)
/* @} */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitDEBUG_UARTPins(void); /* Function assigned for the Cortex-M0P */

#define IOCON_PIO_CLKDIV0 0x00u      /*!<@brief IOCONCLKDIV0 */
#define IOCON_PIO_HYS_EN 0x20u       /*!<@brief Enable hysteresis */
#define IOCON_PIO_INV_DI 0x00u       /*!<@brief Input not invert */
#define IOCON_PIO_MODE_PULLUP 0x10u  /*!<@brief Selects pull-up function */
#define IOCON_PIO_OD_DI 0x00u        /*!<@brief Disables Open-drain function */
#define IOCON_PIO_SMODE_BYPASS 0x00u /*!<@brief Bypass input filter */

/*! @name RESETN (number 5), K2/CN3[10]/CN1[9]/CN1[34]/RESET/PIO0_5
  @{ */
/* Routed pin properties */
/*!
 * @brief Peripheral name */
#define BOARD_INITSWD_DEBUGPINS_K2_PERIPHERAL SYSCON
/*!
 * @brief Signal name */
#define BOARD_INITSWD_DEBUGPINS_K2_SIGNAL RESETN
/*!
 * @brief Routed pin name */
#define BOARD_INITSWD_DEBUGPINS_K2_PIN_NAME RESETN
/*!
 * @brief Label */
#define BOARD_INITSWD_DEBUGPINS_K2_LABEL "K2/CN3[10]/CN1[9]/CN1[34]/RESET/PIO0_5"
/*!
 * @brief Identifier */
#define BOARD_INITSWD_DEBUGPINS_K2_NAME "K2"
/*!
 * @brief PORT device index: 0 */
#define BOARD_INITSWD_DEBUGPINS_K2_PORT 0U
/*!
 * @brief PORT pin number */
#define BOARD_INITSWD_DEBUGPINS_K2_PIN 5U
/*!
 * @brief PORT pin mask */
#define BOARD_INITSWD_DEBUGPINS_K2_PIN_MASK (1U << 5U)
/* @} */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitSWD_DEBUGPins(void); /* Function assigned for the Cortex-M0P */

#define IOCON_PIO_CLKDIV0 0x00u      /*!<@brief IOCONCLKDIV0 */
#define IOCON_PIO_HYS_EN 0x20u       /*!<@brief Enable hysteresis */
#define IOCON_PIO_INV_DI 0x00u       /*!<@brief Input not invert */
#define IOCON_PIO_MODE_PULLUP 0x10u  /*!<@brief Selects pull-up function */
#define IOCON_PIO_OD_DI 0x00u        /*!<@brief Disables Open-drain function */
#define IOCON_PIO_SMODE_BYPASS 0x00u /*!<@brief Bypass input filter */

/*! @name PIO0_4 (number 6), K3/CN1[35]/PIO0_4/ADC_11/TRSTN/WAKEUP
  @{ */
/* Routed pin properties */
/*!
 * @brief Peripheral name */
#define BOARD_INITBUTTONSPINS_K3_PERIPHERAL GPIO
/*!
 * @brief Signal name */
#define BOARD_INITBUTTONSPINS_K3_SIGNAL PIO0
/*!
 * @brief Signal channel */
#define BOARD_INITBUTTONSPINS_K3_CHANNEL 4
/*!
 * @brief Routed pin name */
#define BOARD_INITBUTTONSPINS_K3_PIN_NAME PIO0_4
/*!
 * @brief Label */
#define BOARD_INITBUTTONSPINS_K3_LABEL "K3/CN1[35]/PIO0_4/ADC_11/TRSTN/WAKEUP"
/*!
 * @brief Identifier */
#define BOARD_INITBUTTONSPINS_K3_NAME "K3"
/*!
 * @brief Direction */
#define BOARD_INITBUTTONSPINS_K3_DIRECTION kPIN_MUX_DirectionInput

/* Symbols to be used with GPIO driver */
/*!
 * @brief GPIO peripheral base pointer */
#define BOARD_INITBUTTONSPINS_K3_GPIO GPIO
/*!
 * @brief GPIO pin number */
#define BOARD_INITBUTTONSPINS_K3_GPIO_PIN 4U
/*!
 * @brief GPIO pin mask */
#define BOARD_INITBUTTONSPINS_K3_GPIO_PIN_MASK (1U << 4U)
/*!
 * @brief PORT device index: 0 */
#define BOARD_INITBUTTONSPINS_K3_PORT 0U
/*!
 * @brief PORT pin number */
#define BOARD_INITBUTTONSPINS_K3_PIN 4U
/*!
 * @brief PORT pin mask */
#define BOARD_INITBUTTONSPINS_K3_PIN_MASK (1U << 4U)
/* @} */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitBUTTONsPins(void); /* Function assigned for the Cortex-M0P */

#define IOCON_PIO_CLKDIV0 0x00u      /*!<@brief IOCONCLKDIV0 */
#define IOCON_PIO_HYS_EN 0x20u       /*!<@brief Enable hysteresis */
#define IOCON_PIO_INV_DI 0x00u       /*!<@brief Input not invert */
#define IOCON_PIO_MODE_INACT 0x00u   /*!<@brief No addition pin function */
#define IOCON_PIO_OD_DI 0x00u        /*!<@brief Disables Open-drain function */
#define IOCON_PIO_SMODE_BYPASS 0x00u /*!<@brief Bypass input filter */

/*! @name CAPT_YL (number 1), S1/PIO1_8/CAPT_YL
  @{ */
/* Routed pin properties */
#define BOARD_INITCAPTPINS_CAPY_LOW_PERIPHERAL CAPT           /*!<@brief Peripheral name */
#define BOARD_INITCAPTPINS_CAPY_LOW_SIGNAL CAPTYL             /*!<@brief Signal name */
#define BOARD_INITCAPTPINS_CAPY_LOW_PIN_NAME CAPT_YL          /*!<@brief Routed pin name */
#define BOARD_INITCAPTPINS_CAPY_LOW_LABEL "S1/PIO1_8/CAPT_YL" /*!<@brief Label */
#define BOARD_INITCAPTPINS_CAPY_LOW_NAME "CAPY_LOW"           /*!<@brief Identifier */
#define BOARD_INITCAPTPINS_CAPY_LOW_PORT 1U                   /*!<@brief PORT device index: 1 */
#define BOARD_INITCAPTPINS_CAPY_LOW_PIN 8U                    /*!<@brief PORT pin number */
#define BOARD_INITCAPTPINS_CAPY_LOW_PIN_MASK (1U << 8U)       /*!<@brief PORT pin mask */
                                                              /* @} */

/*! @name CAPT_YH (number 3), S1/PIO1_9/CAPT_YH
  @{ */
/* Routed pin properties */
#define BOARD_INITCAPTPINS_CAPY_HIGH_PERIPHERAL CAPT           /*!<@brief Peripheral name */
#define BOARD_INITCAPTPINS_CAPY_HIGH_SIGNAL CAPTYH             /*!<@brief Signal name */
#define BOARD_INITCAPTPINS_CAPY_HIGH_PIN_NAME CAPT_YH          /*!<@brief Routed pin name */
#define BOARD_INITCAPTPINS_CAPY_HIGH_LABEL "S1/PIO1_9/CAPT_YH" /*!<@brief Label */
#define BOARD_INITCAPTPINS_CAPY_HIGH_NAME "CAPY_HIGH"          /*!<@brief Identifier */
#define BOARD_INITCAPTPINS_CAPY_HIGH_PORT 1U                   /*!<@brief PORT device index: 1 */
#define BOARD_INITCAPTPINS_CAPY_HIGH_PIN 9U                    /*!<@brief PORT pin number */
#define BOARD_INITCAPTPINS_CAPY_HIGH_PIN_MASK (1U << 9U)       /*!<@brief PORT pin mask */
                                                               /* @} */

/*! @name CAPT_X0 (number 9), S1/PIO0_31/CAPT_X0
  @{ */
/* Routed pin properties */
#define BOARD_INITCAPTPINS_CAPX_PERIPHERAL CAPT            /*!<@brief Peripheral name */
#define BOARD_INITCAPTPINS_CAPX_SIGNAL CAPTX               /*!<@brief Signal name */
#define BOARD_INITCAPTPINS_CAPX_CHANNEL 0                  /*!<@brief Signal channel */
#define BOARD_INITCAPTPINS_CAPX_PIN_NAME CAPT_X0           /*!<@brief Routed pin name */
#define BOARD_INITCAPTPINS_CAPX_LABEL "S1/PIO0_31/CAPT_X0" /*!<@brief Label */
#define BOARD_INITCAPTPINS_CAPX_NAME "CAPX"                /*!<@brief Identifier */
#define BOARD_INITCAPTPINS_CAPX_PORT 0U                    /*!<@brief PORT device index: 0 */
#define BOARD_INITCAPTPINS_CAPX_PIN 31U                    /*!<@brief PORT pin number */
#define BOARD_INITCAPTPINS_CAPX_PIN_MASK (1U << 31U)       /*!<@brief PORT pin mask */
                                                           /* @} */

/*! @name ACMP_I5 (number 42), S1/PIO0_30/ACMP_I5
  @{ */
/* Routed pin properties */
#define BOARD_INITCAPTPINS_CAPY_R_PERIPHERAL ACMP            /*!<@brief Peripheral name */
#define BOARD_INITCAPTPINS_CAPY_R_SIGNAL ACMP_IN5            /*!<@brief Signal name */
#define BOARD_INITCAPTPINS_CAPY_R_PIN_NAME ACMP_I5           /*!<@brief Routed pin name */
#define BOARD_INITCAPTPINS_CAPY_R_LABEL "S1/PIO0_30/ACMP_I5" /*!<@brief Label */
#define BOARD_INITCAPTPINS_CAPY_R_NAME "CAPY_R"              /*!<@brief Identifier */
#define BOARD_INITCAPTPINS_CAPY_R_PORT 0U                    /*!<@brief PORT device index: 0 */
#define BOARD_INITCAPTPINS_CAPY_R_PIN 30U                    /*!<@brief PORT pin number */
#define BOARD_INITCAPTPINS_CAPY_R_PIN_MASK (1U << 30U)       /*!<@brief PORT pin mask */
                                                             /* @} */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitCAPTPins(void); /* Function assigned for the Cortex-M0P */

#if defined(__cplusplus)
}
#endif

/*!
 * @}
 */
#endif /* _PIN_MUX_H_ */

/***********************************************************************************************************************
 * EOF
 **********************************************************************************************************************/
