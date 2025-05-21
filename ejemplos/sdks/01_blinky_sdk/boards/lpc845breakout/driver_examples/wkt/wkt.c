/*
 * Copyright 2018 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_debug_console.h"
#include "board.h"
#include "app.h"
#include "fsl_wkt.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/
static volatile bool wktIsrFlag = false;

/*******************************************************************************
 * Code
 ******************************************************************************/
void WKT_IRQHandler(void)
{
    /* Clear interrupt flag.*/
    WKT_ClearStatusFlags(WKT, kWKT_AlarmFlag);
    wktIsrFlag = true;
    SDK_ISR_EXIT_BARRIER;
}

/*!
 * @brief Main function
 */
int main(void)
{
    uint32_t wkt_clock;

    /* Structure of initialize WKT */
    wkt_config_t wktConfig;

    /* Board pin, clock, debug console init */
    BOARD_InitHardware();

    /* Initialize and enable LED */
    APP_LED_INIT;

    wkt_clock = WKT_CLK_FREQ;

    /* Print a note to terminal */
    PRINTF("\r\nWKT interrupt example\r\n");

    /* config->clockSource = kWKT_DividedFROClockSource */
    WKT_GetDefaultConfig(&wktConfig);

    /* Init wkt module */
    WKT_Init(WKT, &wktConfig);

    /* Clear Pending Interrupt */
    NVIC_ClearPendingIRQ(WKT_IRQn);
    /* Enable at the NVIC */
    EnableIRQ(WKT_IRQn);

    while (1)
    {
        /* Set counter value to start the timer counting. Timer counts down to 0, stops and
         * generates an interrupt. When a new count value is loaded, Timer starts again.
         */
        WKT_StartTimer(WKT, USEC_TO_COUNT(250000U, wkt_clock));
        while (wktIsrFlag != true)
        {
        }
        PRINTF("\r\n Self-wake-up timer interrupt is occurred !");
        APP_LED_TOGGLE;
        wktIsrFlag = false;
    }
}
