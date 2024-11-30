#include <stdint.h>
#include "stm32f446xx.h"
#include "gpio.h"
#include "rcc.h"

void main(void) {
    rcc_enable_peripheral_clk(rccClkGpioA);

    gpio_pin_set_dir(gpioA, 5, gpioOutput);
    gpio_pin_set_dir(gpioC, 13, gpioInput);

    gpio_level_t buttonPressed = gpioPinLow;

    while(1) {
        gpio_pin_read(gpioC, 13, &buttonPressed);

        if(buttonPressed) {
            gpio_pin_toggle(gpioA, 5);
        }
    }
}