#ifndef GPIO_H
#define GPIO_H

#include <stdint.h>
#include "common.h"

#define GPIO_PORT_REGISTER_OFFSET 0x400

typedef uint8_t gpio_pin_t;

typedef enum {
    gpioPinLow,
    gpioPinHigh
} gpio_level_t;

typedef enum {
    gpioA,
    gpioB,
    gpioC,
    gpioD,
    gpioE,
    gpioF,
    gpioG,
    gpioH
} gpio_port_t;

typedef enum {
    gpioSuccess,
    gpioFail
} gpio_ret_t;

typedef enum {
    gpioInput,
    gpioOutput,
    gpioAlternate,
    gpioAnalog
} gpio_dir_t;

gpio_ret_t gpio_set_pin_dir(gpio_port_t port, gpio_pin_t pin, gpio_dir_t direction);
gpio_ret_t gpio_pin_write(gpio_port_t port, gpio_pin_t pin, gpio_level_t level);
gpio_ret_t gpio_pin_toggle(gpio_port_t port, gpio_pin_t pin);

#endif /* GPIO_H */