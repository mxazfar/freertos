#include "gpio.h"
#include "stm32f446xx.h"

#define GPIO_GET_PORT_ADDR(port) (GPIOA + (GPIO_PORT_REGISTER_OFFSET*port))

gpio_ret_t gpio_set_pin_dir(gpio_port_t port, gpio_pin_t pin, gpio_dir_t direction) {
    GPIO_TypeDef *portAddr = GPIO_GET_PORT_ADDR(port);

    portAddr->MODER &= ~(0b11 << pin * 2);
    portAddr->MODER |= (direction << pin * 2);

    return gpioSuccess;
}

gpio_ret_t gpio_pin_write(gpio_port_t port, gpio_pin_t pin, gpio_level_t level) {
    GPIO_TypeDef *portAddr = GPIO_GET_PORT_ADDR(port);

    // TODO: add validation logic to ensure port and pin are configured for output
    if(level == gpioPinHigh) {
        portAddr->ODR |= (1 << pin);
    } else {
        portAddr->ODR &= ~(1 << pin);
    }

    return gpioSuccess;
}

gpio_ret_t gpio_pin_toggle(gpio_port_t port, gpio_pin_t pin) {
    GPIO_TypeDef *portAddr = GPIO_GET_PORT_ADDR(port);

    // TODO: add validation logic to ensure port and pin are configured for output
    gpio_level_t pinLevel = (portAddr->ODR >> pin) & 1;

    if(pinLevel == gpioPinHigh) {
        gpio_pin_write(port, pin, gpioPinLow);
    } else {
        gpio_pin_write(port, pin, gpioPinHigh);
    }

    return gpioSuccess;
}