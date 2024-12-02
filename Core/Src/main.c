#include <stdint.h>
#include "stm32f446xx.h"
#include "gpio.h"
#include "rcc.h"
#include "q7seg.h"

#include "FreeRTOS.h"
#include "task.h"

void displaySegmentTask(void *params) {
    static int calls = 0;

    while(1) {
        writeDisplaySingle(q7seg4, calls % 10, 1);
        calls++;

        vTaskDelay(pdMS_TO_TICKS(500));
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
