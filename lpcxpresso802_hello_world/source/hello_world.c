/*
 * Copyright (c) 2013 - 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017, 2024 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_device_registers.h"
#include "fsl_debug_console.h"
#include "board.h"
#include "app.h"
#include <stdio.h>
#include <stdlib.h>


/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/
/*!
 * @brief Main function
 */
int main(void)
{
    char ch;
    uint32_t delayCount;

    // BOARD_InitDebugConsole();

    /* Init board hardware. */
    PRINTF("Initializing board hardware...\r\n");
    DbgConsole_Printf("testing\n");
    BOARD_InitHardware();
    PRINTF("Board initialized.\r\n");
    BOARD_InitDebugConsole();



    while (1)
    {
        PRINTF("hello world.\r\n");
        for(delayCount = 0; delayCount < 1000000; delayCount++){

        }
//        ch = GETCHAR();
//        PUTCHAR(ch);
    	// Remove GETCHAR() for testing
    	//__NOP();  // Do nothing, just loop
    }
}
