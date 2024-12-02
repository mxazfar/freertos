#ifndef ADC_H
#define ADC_H

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

#endif /* ADC_H */