#include "gpio.h"
#include "stm32f446xx.h"

#define GPIO_GET_PORT_ADDR(port) ((uintptr_t)GPIOA + (GPIO_PORT_REGISTER_OFFSET*port))

gpio_ret_t gpio_pin_set_dir(gpio_port_t port, gpio_pin_t pin, gpio_dir_t direction) {
    GPIO_TypeDef *portAddr = (GPIO_TypeDef*)GPIO_GET_PORT_ADDR(port);

    portAddr->MODER &= ~(0b11 << pin * 2);
    portAddr->MODER |= (direction << pin * 2);

    return gpioSuccess;
}

gpio_ret_t gpio_pin_write(gpio_port_t port, gpio_pin_t pin, gpio_level_t level) {
    GPIO_TypeDef *portAddr = (GPIO_TypeDef*)GPIO_GET_PORT_ADDR(port);

    // TODO: add validation logic to ensure port and pin are configured for output
    if(level == gpioPinHigh) {
        portAddr->ODR |= (1 << pin);
    } else {
        portAddr->ODR &= ~(1 << pin);
    }

    return gpioSuccess;
}

gpio_ret_t gpio_pin_read(gpio_port_t port, gpio_pin_t pin, gpio_level_t *reading) {
    GPIO_TypeDef *portAddr = (GPIO_TypeDef*)GPIO_GET_PORT_ADDR(port);

    // TODO: add validation logic to ensure port and pin are configured for input
    *reading = (portAddr->IDR >> pin) & 1;

    return gpioSuccess;
}

gpio_ret_t gpio_pin_toggle(gpio_port_t port, gpio_pin_t pin) {
    GPIO_TypeDef *portAddr = (GPIO_TypeDef*)GPIO_GET_PORT_ADDR(port);

    // TODO: add validation logic to ensure port and pin are configured for output
    gpio_level_t pinLevel = (portAddr->ODR >> pin) & 1;

    if(pinLevel == gpioPinHigh) {
        gpio_pin_write(port, pin, gpioPinLow);
    } else {
        gpio_pin_write(port, pin, gpioPinHigh);
    }

    return gpioSuccess;
}

gpio_ret_t gpio_pin_configure_pupd(gpio_port_t port, gpio_pin_t pin, gpio_pupd_t pupd) {
    GPIO_TypeDef *portAddr = (GPIO_TypeDef*)GPIO_GET_PORT_ADDR(port);

    // TODO: add validation logic to ensure port/pin are set for input
    portAddr->PUPDR &= ~(0b11 << pin * 2);
    portAddr->PUPDR |= (pupd << pin * 2);

    return gpioSuccess;
}

gpio_ret_t gpio_pin_configure_alt_func(gpio_port_t port, gpio_pin_t pin, gpio_alt_func_t func) {
    GPIO_TypeDef *portAddr = (GPIO_TypeDef*)GPIO_GET_PORT_ADDR(port);

    // TODO: add validation logic to ensure port/pin set for alt func
    if(pin < 8) {
        portAddr->AFR[0] &= ~(0b1111 << pin * 4);
        portAddr->AFR[0] |= (func << pin * 4);
    } else {
        portAddr->AFR[1] &= ~(0b1111 << (pin - 8) * 4);
        portAddr->AFR[1] |= (func << (pin - 8) * 4);
    }

    return gpioSuccess;
}