#include <stdint.h>
#include "stm32f446xx.h"

#include "gpio.h"
#include "rcc.h"
#include "adc.h"
#include "tim_general.h"

#include "q7seg.h"

#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

#define ADC1_CHANNELS_CONFIGURED 1

uint16_t displayNum = 5555;
uint16_t displayPow10[5] = {1, 10, 100, 1000, 10000};

tim_general_config_t timer2Config = {
    .countStyle = timGeneralCountUp,
    .prescaleAmount = (1 << 3),
    .clockDivision = timGenCkInt,
    .preloadValue = 0xFFFF
};

adc_channel_t adc1SampleChannels[ADC1_CHANNELS_CONFIGURED] = {adcCH1};
adc_sample_time_t adc1SampleTimes[ADC1_CHANNELS_CONFIGURED] = {adc28Cycles};

adc_config_t adc1Config  = {
    .scanMode = adcSingleConverion,
    .channels = &adc1SampleChannels, // PA1
    .sampleTime = &adc1SampleTimes,
    .numChannels = 1
};

uint16_t adcResult = 9999;

SemaphoreHandle_t adcSampleTrigger;
SemaphoreHandle_t adcSampleResult;

void initInterrupts() {
    NVIC_SetPriority(TIM2_IRQn, configLIBRARY_LOWEST_INTERRUPT_PRIORITY);
    NVIC_EnableIRQ(TIM2_IRQn);

    NVIC_SetPriority(ADC_IRQn, configLIBRARY_LOWEST_INTERRUPT_PRIORITY - 1);
    NVIC_EnableIRQ(ADC_IRQn);
}

void init() {
    initDisplay();
    initInterrupts();

    rcc_enable_peripheral_clk(rccClkGpioA);
    gpio_pin_set_dir(gpioA, 1, gpioAnalog);

    configureAdc(adc1, &adc1Config);

    configureTimer(timGeneralTimer2, &timer2Config);
    startTimer(timGeneralTimer2);
}

void sampleAnalogSignalTask(void *params) {
    while(1) {
        xSemaphoreTake(adcSampleTrigger, portMAX_DELAY);
        triggerSample(adc1);

        xSemaphoreTake(adcSampleResult, portMAX_DELAY);
        displayNum = filterAdcResultHysteresis(adcResult);
    }
}

void displaySegmentTask(void *params) {
    while(1) {
        for(uint8_t i = 0; i < 4; i++) {
            uint8_t numToDisplay = (displayNum % displayPow10[i + 1]) / displayPow10[i];

            if(displayNum > displayPow10[i]) {
                writeDisplaySingle(q7segSegs[3-i], numToDisplay, 1);
            }

            vTaskDelay(pdMS_TO_TICKS(5));
        }
    }
}

void main(void) {
    init();

    adcSampleTrigger = xSemaphoreCreateBinary();
    adcSampleResult = xSemaphoreCreateBinary();

    xTaskCreate(displaySegmentTask, "Display", 500, NULL, 1, NULL);
    xTaskCreate(sampleAnalogSignalTask, "Sample", 500, NULL, 2, NULL);

    vTaskStartScheduler();

    while(1) {}
}

void TIM2_IRQHandler(void) {
    TIM2->SR &= ~TIM_SR_UIF;
    BaseType_t wakeUpTask = pdFALSE;

    xSemaphoreGiveFromISR(adcSampleTrigger, &wakeUpTask);

    portYIELD_FROM_ISR(wakeUpTask);
}

void ADC_IRQHandler(void) {
    adcResult = readAdcResult(adc1);

    BaseType_t wakeUpTask = pdFALSE;

    xSemaphoreGiveFromISR(adcSampleResult, &wakeUpTask);

    portYIELD_FROM_ISR(wakeUpTask);
}
