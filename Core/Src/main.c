#include <stdint.h>
#include "stm32f446xx.h"
#include "gpio.h"
#include "rcc.h"
#include "adc.h"
#include "q7seg.h"

#include "FreeRTOS.h"
#include "task.h"
#include "tim_general.h"

uint16_t displayNum = 0;
uint16_t displayPow10[5] = {1, 10, 100, 1000, 10000};

tim_general_config_t timer2Config = {
    .countStyle = timGeneralCountUp,
    .prescaleAmount = (1 << 3),
    .clockDivision = timGenCkInt,
    .preloadValue = 0xFFFF
};

void initInterrupts() {
    NVIC_SetPriority(TIM2_IRQn, configLIBRARY_LOWEST_INTERRUPT_PRIORITY);
    NVIC_EnableIRQ(TIM2_IRQn);
}

void init() {
    initDisplay();
    initInterrupts();

    configureTimer(timGeneralTimer2, &timer2Config);
    startTimer(timGeneralTimer2);
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

    xTaskCreate(displaySegmentTask, "Display", 500, NULL, 1, NULL);

    vTaskStartScheduler();

    while(1) {}
}

void TIM2_IRQHandler(void) {
    TIM2->SR &= ~TIM_SR_UIF;
    displayNum++;
}
