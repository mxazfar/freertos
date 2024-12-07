#ifndef ADC_H
#define ADC_H

#include <stdint.h>

#define ADC_UNIT_REGISTER_OFFSET 0x100U
#define ADC_HYSTERESIS_AMOUNT 18
#define ADC_JUMP_AMOUNT 28

typedef enum {
    adcTim1Ch1,
    adcTim1Ch2,
    adcTim1Ch3,
    adcTim2Ch2,
    adcTim2Ch3,
    adcTim2Ch4,
    adcTim2TRGO,
    adcTim3Ch1,
    adcTim3TRGO,
    adcTim4Ch4,
    adcTim5Ch1,
    adcTim5Ch2,
    adcTim5Ch4,
    adcTim8Ch1,
    adcTim8TRGO,
    adcExtiLine11
} adc_trigger_type_reg_channel_t;

typedef enum {
    adcNoTriggerDetect,
    adcTriggerRising,
    adcTriggerFalling,
    adcTriggerRisingFalling
} adc_trigger_polarity_t;

typedef enum {
    adc1,
    adc2,
    adc3
} adc_unit_t;

typedef enum {
    adcFail,
    adcSuccess
} adc_ret_t;

typedef enum {
    adcSingleConverion,
    adcContinuous
} adc_scan_mode_t;

typedef enum {
    adcCH1,
    adcCH2,
    adcCH3,
    adcCH4,
    adcCH5,
    adcCH6,
    adcCH7,
    adcCH8,
    adcCH9,
    adcCH10,
    adcCH11,
    adcCH12,
    adcCH13,
    adcCH14,
    adcCH15,
    adcCH16,
    adcCH17,
    adcCH18
} adc_channel_t;
 
typedef enum {
    adc3Cycles,
    adc15Cycles,
    adc28Cycles,
    adc56Cycles,
    adc84Cycles,
    adc112Cycles,
    adc144Cycles,
    adc480Cycles
} adc_sample_time_t;

typedef struct {
    adc_scan_mode_t scanMode; // mode of scanning (single or continuous)
    adc_channel_t *channels; // pointer to array of channels to sample (must be in sequence order)
    adc_sample_time_t *sampleTime; // pointer to sample time of each channel (must be in sequence order)
    uint8_t numChannels; // number of channels
} adc_config_t;

adc_ret_t configureAdc(adc_unit_t unit, adc_config_t *adcConfig);
adc_ret_t triggerSample(adc_unit_t unit);

uint16_t readAdcResult(adc_unit_t unit);
uint16_t filterAdcResultHysteresis(uint16_t rawAdcReading);

#endif /* ADC_H */