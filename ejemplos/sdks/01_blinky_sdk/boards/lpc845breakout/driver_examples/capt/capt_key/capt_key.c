/*
 * Copyright 2020 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>
#include <stdint.h>
#include "touch_hal.h"
#include "touch.h"
#include "glitch_filter.h"
#include "app_config.h"
#include "app.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/* touch state machine. */
typedef enum
{
    kAPP_TouchStateInit   = 0, /* Initialization. */
    kAPP_TouchStateCalib  = 1, /* Calibration, learn the baseline. */
    kAPP_TouchStateDetect = 2, /* Detection. */
} app_touch_state_t;

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/

int32_t appTouchStateInitCounter = 0;
bool appTouchWindowsIsStable     = true;
int32_t pressedKeyIndex;
int32_t oldPressedKeyIndex;
app_touch_state_t appTouchState = kAPP_TouchStateInit;
glitch_filter_handle_t appGlitchFilterHandle;

int16_t appTouchValRaw[TOUCH_X_CHANNEL_COUNT] = {0};
int32_t appTouchWindowsSum[TOUCH_X_CHANNEL_COUNT];
int32_t appTouchWindowsAverage[TOUCH_X_CHANNEL_COUNT];
int32_t appTouchWindowsVariance[TOUCH_X_CHANNEL_COUNT];

/*******************************************************************************
 * Code
 ******************************************************************************/
int main(void)
{
    BOARD_InitHardware();

    BOARD_InitLED();
    BOARD_TurnOffAllLed();

    /* touch. */
    TOUCH_WINDOWS_Init();
    TOUCH_HAL_Init();

    appTouchState = kAPP_TouchStateInit;

    while (1)
    {
        TOUCH_HAL_WaitDataReady(appTouchValRaw);

        /* Push the raw data into window array. */
        TOUCH_WINDOWS_Puth(appTouchValRaw);

        /* process the state machine. */
        switch (appTouchState)
        {
            /*
             * Init stage.
             * In this stage, touch scan is started, the captured raw data is pushed
             * into the window array, but not processed.
             * This drops the unstable data after reset.
             */
            case kAPP_TouchStateInit:

                if (appTouchStateInitCounter < 4u * TOUCH_WINDOW_LENGTH)
                {
                    appTouchStateInitCounter++;
                }
                else
                {
                    appTouchStateInitCounter = 0u;
                    appTouchState            = kAPP_TouchStateCalib;

                    BOARD_TurnOnAllLed();
                }
                break;

            /* Calibration stage. */
            case kAPP_TouchStateCalib:

                /* Check variance to make sure the touch sample data is stable. */
                TOUCH_WINDOWS_CalcAverage(appTouchWindowsAverage);
                TOUCH_WINDOWS_CalcVariance(appTouchWindowsAverage, appTouchWindowsVariance);

                appTouchWindowsIsStable = true;
                for (uint8_t i = 0u; i < TOUCH_X_CHANNEL_COUNT; i++)
                {
                    if (appTouchWindowsVariance[i] > APP_CHANNEL_STABLE_VARIANCE)
                    {
                        appTouchWindowsIsStable = false;
                        break;
                    }
                }

                /* When sample data stable, use the stable data in window to calculate the baseline. */
                if (appTouchWindowsIsStable)
                {
                    TOUCH_WINDOWS_CalcSum(appTouchWindowsSum);
                    TOUCH_WINDOWS_SetBaseline(appTouchWindowsSum);

                    /* calib done. */
                    BOARD_TurnOffAllLed();

                    FILTER_Init(&appGlitchFilterHandle, TOUCH_X_CHANNEL_COUNT, APP_GLITCH_FILTER_LEVEL);
                    appTouchState = kAPP_TouchStateDetect;
                }

                break;

            case kAPP_TouchStateDetect:

                TOUCH_WINDOWS_CalcSum(appTouchWindowsSum);

                pressedKeyIndex = TOUCH_GetPressedKeyIndex(appTouchWindowsSum);

                pressedKeyIndex = FILTER_Output(&appGlitchFilterHandle, pressedKeyIndex);

                if (TOUCH_X_CHANNEL_COUNT == pressedKeyIndex)
                {
                    BOARD_TurnOffAllLed();
                }
                else
                {
                    if (oldPressedKeyIndex != pressedKeyIndex)
                    {
                        BOARD_TurnOffLed(oldPressedKeyIndex);
                    }
                    BOARD_TurnOnLed(pressedKeyIndex);
                }

                oldPressedKeyIndex = pressedKeyIndex;

                break;

            default:
                appTouchState = kAPP_TouchStateInit;
                break;
        } /* end switch. */
    }     /* end while. */
} /* end main. */
