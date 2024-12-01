#include <stdint.h>
#include "stm32f446xx.h"
#include "gpio.h"
#include "rcc.h"
#include "q7seg.h"

void main(void) {
    rcc_enable_peripheral_clk(rccClkGpioA);
    rcc_enable_peripheral_clk(rccClkGpioC);

    gpio_pin_set_dir(gpioA, 5, gpioOutput);
    gpio_pin_set_dir(gpioC, 13, gpioInput);

    gpio_level_t buttonPressed = gpioPinLow;

    initDisplay();

    while(1) {
        for(uint8_t i = 0; i < 10; i++) {
            writeDisplaySingle(q7seg4, i, 1);
            for(volatile uint32_t i = 0; i < 250000; i++) {}
        }
    }
}