#include <stdint.h>
#include "stm32f446xx.h"
#include "gpio.h"

void main(void) {
    RCC->AHB1ENR |= ((1 << 0) | (1 << 2));

    volatile uint32_t dummy;
    dummy = RCC->AHB1ENR;
    dummy = RCC->AHB1ENR;

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