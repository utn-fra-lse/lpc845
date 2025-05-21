/*
 * Copyright  2019 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/*${header:start}*/
#include "pin_mux.h"
#include "board.h"
#include <stdbool.h>
/*${header:end}*/

/*${function:start}*/
void BOARD_InitHardware(void)
{
    BOARD_InitBootPins();
    BOARD_BootClockFRO30M();
    BOARD_InitDebugConsole();

    /* Select clock to USART0 (debug console) */
    CLOCK_Select(kUART0_Clk_From_MainClk);

    /* Select the main clock as source clock of USART1. */
    CLOCK_Select(kUART1_Clk_From_MainClk);

    /* Select the main clock as source clock of USART2. */
    CLOCK_Select(kUART2_Clk_From_MainClk);

    /* Turn on LED RED */
    LED_RED_INIT(LOGIC_LED_ON);
}
/*${function:end}*/
