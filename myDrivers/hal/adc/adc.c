#include "stm32f446xx.h"
#include "adc.h"
#include "rcc.h"

#define ADC_GET_UNIT_ADDR(adcUnit) ((uintptr_t)ADC1 + (ADC_UNIT_REGISTER_OFFSET*adcUnit))

/**
 * @brief Configure ADC unit
 * @param unit ADC unit to be configured
 * @param adcConfig Pointer to configuration
 * @return Fail/success
 */
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

/**
 * @brief Triggers sample of ADC. The unit must be configured before calling this function.
 * @param unit ADC unit to sample
 * @return Fail/success
 */
adc_ret_t triggerSample(adc_unit_t unit) {
    ADC_TypeDef *adcUnit = ADC_GET_UNIT_ADDR(unit);

    adcUnit->CR2 |= ADC_CR2_SWSTART;

    return adcSuccess;
}

/**
 * @brief Reads raw ADC result of unit
 * @param unit ADC unit to read
 * @return Contents of the ADC unit's data register
 */
uint16_t readAdcResult(adc_unit_t unit) {
    ADC_TypeDef *adcUnit = ADC_GET_UNIT_ADDR(unit);

    return adcUnit->DR;
}

/**
 * @brief Filters DC result by applying a hysteresis filter
 * @param rawAdcReading Raw ADC reading to be filtered
 * @return Filtered ADC reading
 */
uint16_t filterAdcResultHysteresis(uint16_t rawAdcReading) {
    static uint16_t prevFilteredReading = 0;
    static uint8_t firstCall = 1;

    if (firstCall) {
        firstCall = 0;
        prevFilteredReading = rawAdcReading;
    }

    if ((rawAdcReading > prevFilteredReading + ADC_HYSTERESIS_AMOUNT) && (rawAdcReading < prevFilteredReading + ADC_JUMP_AMOUNT)) {
        prevFilteredReading = rawAdcReading; 
    } else if ((rawAdcReading < prevFilteredReading - ADC_HYSTERESIS_AMOUNT) && (rawAdcReading > prevFilteredReading - ADC_JUMP_AMOUNT)) {
        prevFilteredReading = rawAdcReading; 
    } else if ((rawAdcReading >= prevFilteredReading + ADC_JUMP_AMOUNT) || (rawAdcReading <= prevFilteredReading - ADC_JUMP_AMOUNT)) {
        prevFilteredReading = (prevFilteredReading + rawAdcReading) / 2; // damping to approach large jump
    }

    return prevFilteredReading;
}