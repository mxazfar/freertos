#include <stdint.h>
#include "stm32f446xx.h"
#include "gpio.h"

void main(void) {
    RCC->AHB1ENR |= (1 << 0);

    volatile uint32_t dummy;
    dummy = RCC->AHB1ENR;
    dummy = RCC->AHB1ENR;

    gpio_set_pin_dir(gpioA, 5, gpioOutput);

    while(1) {
        gpio_pin_toggle(gpioA, 5);
        for (uint32_t i = 0; i < 500000; i++);
    }
}