#ifndef _ADC_CONFIG_H_
#define _ADC_CONFIG_H_

#include "fsl_adc.h"
#include "fsl_clock.h"
#include "fsl_device_registers.h"
#include "fsl_debug_console.h"
#include "board.h"
#include "app.h"
#include "fsl_power.h"

extern adc_result_info_t adcResultInfoStruct;

/* Define the ADC base and sample channel */
#ifndef DEMO_ADC_BASE
#define DEMO_ADC_BASE ADC0  /* Change this based on your MCU */
#endif

#ifndef DEMO_ADC_SAMPLE_CHANNEL_NUMBER
#define DEMO_ADC_SAMPLE_CHANNEL_NUMBER 0U /* Default ADC channel */
#endif

#ifndef DEMO_ADC_CLOCK_DIVIDER
#define DEMO_ADC_CLOCK_DIVIDER 1U /* Default clock divider */
#endif

/* Function prototype for ADC configuration */
void ADC_Configuration(void);

#endif /* _ADC_CONFIG_H_ */
