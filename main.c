#include <stdint.h>
#include "stm32f446xx.h"

void main(void) {
    RCC->AHB1ENR |= (1 << 0);

    volatile uint32_t dummy;
    dummy = RCC->AHB1ENR;
    dummy = RCC->AHB1ENR;

    GPIOA->MODER |= (1 << 10);

    while(1) {
        GPIOA->ODR ^= (1 << 5);
        for (uint32_t i = 0; i < 500000; i++);
    }
}