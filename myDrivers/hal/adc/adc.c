#include "stm32f446xx.h"
#include "adc.h"
#include "rcc.h"

#define ADC_GET_UNIT_ADDR(adcUnit) ((uintptr_t)ADC1 + (ADC_UNIT_REGISTER_OFFSET*adcUnit))

adc_ret_t configureAdc(adc_unit_t unit, adc_config_t *adcConfig) {
    ADC_TypeDef *adcUnit = ADC_GET_UNIT_ADDR(unit);

    // supply clock
    rcc_enable_peripheral_clk(rccClkAdc1 + unit);

    // set scan mode
    adcUnit->CR2 |= (adcConfig->scanMode << ADC_CR2_CONT_Pos);
    // set interrupt enable EOCIE in ADC_CR1
    adcUnit->CR1 |= ADC_CR1_EOCIE;

    // write pin(s) to be converted and set sample times
    for(uint16_t i = 0; i < adcConfig->numChannels; i++) {
        // set sample times
        if(adcConfig->channels[i] < 10) {
            adcUnit->SMPR2 |= adcConfig->sampleTime[i] << adcConfig->channels[i] * 3;
        } else {
            adcUnit->SMPR1 |= adcConfig->sampleTime[i] << (adcConfig->channels[i] * 3 - 10);
        }

        // write pin sequence
        if(i < 6) {
            adcUnit->SQR3 |= adcConfig->channels[i] + 1 << i * 5;
        } else if (i < 13) {
            adcUnit->SQR2 |= adcConfig->channels[i] << (i * 5 - 30);
        } else {
            adcUnit->SQR1 |= adcConfig->channels[i] << (i * 5 - 60);
        }
    }

    // turn it on
    adcUnit->CR2 |= ADC_CR2_ADON;

    return adcSuccess;
}

adc_ret_t triggerSample(adc_unit_t unit) {
    ADC_TypeDef *adcUnit = ADC_GET_UNIT_ADDR(unit);

    adcUnit->CR2 |= ADC_CR2_SWSTART;

    return adcSuccess;
}

uint16_t readAdcResult(adc_unit_t unit) {
    ADC_TypeDef *adcUnit = ADC_GET_UNIT_ADDR(unit);

    return adcUnit->DR;
}