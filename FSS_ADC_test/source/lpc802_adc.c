#include "fsl_adc.h"
#include "fsl_clock.h"

#include "fsl_device_registers.h"
#include "fsl_debug_console.h"
#include "board.h"
#include "app.h"
#include "fsl_power.h"

#include "lpc802_adc.h"

void ADC_Configuration(void)
{
    adc_config_t adcConfigStruct;
    adc_conv_seq_config_t adcConvSeqConfigStruct;

/* Configure the converter. */
#if defined(FSL_FEATURE_ADC_HAS_CTRL_ASYNMODE) & FSL_FEATURE_ADC_HAS_CTRL_ASYNMODE
    adcConfigStruct.clockMode = kADC_ClockSynchronousMode; /* Using sync clock source. */
#endif                                                     /* FSL_FEATURE_ADC_HAS_CTRL_ASYNMODE */
    adcConfigStruct.clockDividerNumber = DEMO_ADC_CLOCK_DIVIDER;
#if defined(FSL_FEATURE_ADC_HAS_CTRL_RESOL) & FSL_FEATURE_ADC_HAS_CTRL_RESOL
    adcConfigStruct.resolution = kADC_Resolution12bit;
#endif /* FSL_FEATURE_ADC_HAS_CTRL_RESOL */
#if defined(FSL_FEATURE_ADC_HAS_CTRL_BYPASSCAL) & FSL_FEATURE_ADC_HAS_CTRL_BYPASSCAL
    adcConfigStruct.enableBypassCalibration = false;
#endif /* FSL_FEATURE_ADC_HAS_CTRL_BYPASSCAL */
#if defined(FSL_FEATURE_ADC_HAS_CTRL_TSAMP) & FSL_FEATURE_ADC_HAS_CTRL_TSAMP
    adcConfigStruct.sampleTimeNumber = 0U;
#endif /* FSL_FEATURE_ADC_HAS_CTRL_TSAMP */
#if defined(FSL_FEATURE_ADC_HAS_CTRL_LPWRMODE) & FSL_FEATURE_ADC_HAS_CTRL_LPWRMODE
    adcConfigStruct.enableLowPowerMode = false;
#endif /* FSL_FEATURE_ADC_HAS_CTRL_LPWRMODE */
#if defined(FSL_FEATURE_ADC_HAS_TRIM_REG) & FSL_FEATURE_ADC_HAS_TRIM_REG
    adcConfigStruct.voltageRange = kADC_HighVoltageRange;
#endif /* FSL_FEATURE_ADC_HAS_TRIM_REG */
    ADC_Init(DEMO_ADC_BASE, &adcConfigStruct);

#if !(defined(FSL_FEATURE_ADC_HAS_NO_CALIB_FUNC) && FSL_FEATURE_ADC_HAS_NO_CALIB_FUNC)
    uint32_t frequency = 0U;
    /* Calibration after power up. */
#if defined(FSL_FEATURE_ADC_HAS_CALIB_REG) && FSL_FEATURE_ADC_HAS_CALIB_REG
    DEMO_ADC_BASE->CTRL |= ADC_CTRL_BYPASSCAL_MASK;
    frequency = CLOCK_GetFreq(kCLOCK_BusClk);
    if (true == ADC_DoOffsetCalibration(DEMO_ADC_BASE, frequency))
#else
#if defined(SYSCON_ADCCLKDIV_DIV_MASK)
    frequency = CLOCK_GetFreq(DEMO_ADC_CLOCK_SOURCE) / CLOCK_GetClkDivider(kCLOCK_DivAdcClk);
#else
    frequency = CLOCK_GetFreq(DEMO_ADC_CLOCK_SOURCE);
#endif /* SYSCON_ADCCLKDIV_DIV_MASK */
    if (true == ADC_DoSelfCalibration(DEMO_ADC_BASE, frequency))
#endif /* FSL_FEATURE_ADC_HAS_CALIB_REG */
    {
        PRINTF("ADC Calibration Done.\r\n");
    }
    else
    {
        PRINTF("ADC Calibration Failed.\r\n");
    }
#if defined(FSL_FEATURE_ADC_CALIBRATION_CLOCK_LOWER_THAN_30MHz) && FSL_FEATURE_ADC_CALIBRATION_CLOCK_LOWER_THAN_30MHz
    ReInitSystemclock();
#endif
#endif /* FSL_FEATURE_ADC_HAS_NO_CALIB_FUNC */

#if !(defined(FSL_FEATURE_ADC_HAS_NO_INSEL) && FSL_FEATURE_ADC_HAS_NO_INSEL)
    /* Use the temperature sensor input to channel 0. */
    ADC_EnableTemperatureSensor(DEMO_ADC_BASE, true);
#endif /* FSL_FEATURE_ADC_HAS_NO_INSEL. */

    /* Enable channel DEMO_ADC_SAMPLE_CHANNEL_NUMBER's conversion in Sequence A. */
#if defined(FSL_FEATURE_ADC_HAS_SEQ_CTRL_TSAMP) & FSL_FEATURE_ADC_HAS_SEQ_CTRL_TSAMP
    adcConvSeqConfigStruct.seqSampleTimeNumber = 0U;
#endif /* FSL_FEATURE_ADC_HAS_SEQ_CTRL_TSAMP */
    adcConvSeqConfigStruct.channelMask =
        (1U << DEMO_ADC_SAMPLE_CHANNEL_NUMBER); /* Includes channel DEMO_ADC_SAMPLE_CHANNEL_NUMBER. */
    adcConvSeqConfigStruct.triggerMask      = 0U;
    adcConvSeqConfigStruct.triggerPolarity  = kADC_TriggerPolarityPositiveEdge;
    adcConvSeqConfigStruct.enableSingleStep = false;
    adcConvSeqConfigStruct.enableSyncBypass = false;
    adcConvSeqConfigStruct.interruptMode    = kADC_InterruptForEachSequence;
    ADC_SetConvSeqAConfig(DEMO_ADC_BASE, &adcConvSeqConfigStruct);
    ADC_EnableConvSeqA(DEMO_ADC_BASE, true); /* Enable the conversion sequence A. */
    /* Clear the result register. */
    ADC_DoSoftwareTriggerConvSeqA(DEMO_ADC_BASE);
    while (!ADC_GetChannelConversionResult(DEMO_ADC_BASE, DEMO_ADC_SAMPLE_CHANNEL_NUMBER, &adcResultInfoStruct))
    {
    }
    ADC_GetConvSeqAGlobalConversionResult(DEMO_ADC_BASE, &adcResultInfoStruct);
}
