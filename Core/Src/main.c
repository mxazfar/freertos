#include <stdint.h>
#include "stm32f446xx.h"
#include "gpio.h"
#include "rcc.h"
#include "q7seg.h"

#include "FreeRTOS.h"
#include "task.h"

uint16_t displayNum = 5943;

uint16_t displayPow10[5] = {1, 10, 100, 1000, 10000};

void displaySegmentTask(void *params) {
    while(1) {
        for(uint8_t i = 0; i < 4; i++) {
            uint8_t numToDisplay = (displayNum % displayPow10[i + 1]) / displayPow10[i];
            writeDisplaySingle(q7segSegs[3-i], numToDisplay, 1);
            vTaskDelay(pdMS_TO_TICKS(5));
        }
    }
}

void main(void) {
    rcc_enable_peripheral_clk(rccClkGpioA);
    rcc_enable_peripheral_clk(rccClkGpioC);

    gpio_pin_set_dir(gpioA, 5, gpioOutput);
    gpio_pin_set_dir(gpioC, 13, gpioInput);

    gpio_level_t buttonPressed = gpioPinLow;

    initDisplay();

    xTaskCreate(displaySegmentTask, "Display", 500, NULL, 1, NULL);

    vTaskStartScheduler();

    while(1) {}
}
