#include "rcc.h"
#include "stm32f446xx.h"

rcc_ret_t rcc_enable_peripheral_clk(rcc_peripheral_clk_t peripheral) {
    uint32_t peripheralBitmask = (1 << peripheral % 32);
    volatile uint32_t dummy;

    switch(peripheral / 32) {
        case 0:
            RCC->AHB1ENR |= peripheralBitmask;
            dummy = RCC->AHB1ENR;
            dummy = RCC->AHB1ENR;
            break;
        case 1:
            RCC->AHB2ENR |= peripheralBitmask;
            dummy = RCC->AHB2ENR;
            dummy = RCC->AHB2ENR;
            break;
        case 2:
            RCC->AHB3ENR |= peripheralBitmask;
            dummy = RCC->AHB3ENR;
            dummy = RCC->AHB3ENR;
            break;
        case 3:
            RCC->APB1ENR |= peripheralBitmask;
            dummy = RCC->APB1ENR;
            dummy = RCC->APB1ENR;
            break;
        case 4:
            RCC->APB2ENR |= peripheralBitmask;
            dummy = RCC->APB2ENR;
            dummy = RCC->APB2ENR;
            break;
    }

    return rccSuccess;
}