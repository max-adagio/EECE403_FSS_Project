/*
 * Copyright 2018 NXP
 * Copyright 2017-2018 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef _APP_H_
#define _APP_H_
#include "fsl_gpio.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*${macro:start}*/
#define APP_LED_INIT         LED_RED_INIT(1)
#define APP_LED_ON           LED_RED_ON()
#define APP_LED_TOGGLE       LED_RED_TOGGLE()
#define APP_WDT_IRQn         WDT_IRQn
#define APP_WDT_IRQ_HANDLER  WDT_IRQHandler
#define WDT_CLK_FREQ         CLOCK_GetFreq(kCLOCK_LPOsc)
#define kPDRUNCFG_PD_WDT_OSC kPDRUNCFG_PD_LPOSC
/*${macro:end}*/

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
/*${prototype:start}*/
void BOARD_InitHardware(void);
/*${prototype:end}*/

#endif /* _APP_H_ */
