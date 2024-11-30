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

typedef enum {
    gpioNoPupd,
    gpioPullup,
    gpioPulldown,
    gpioPupdReserved
} gpio_pupd_t;

typedef enum {
    gpioAF0,
    gpioAF1,
    gpioAF2,
    gpioAF3,
    gpioAF4,
    gpioAF5,
    gpioAF6,
    gpioAF7,
    gpioAF8,
    gpioAF9,
    gpioAF10,
    gpioAF11,
    gpioAF12,
    gpioAF13,
    gpioAF14,
    gpioAF15
} gpio_alt_func_t;

gpio_ret_t gpio_pin_set_dir(gpio_port_t port, gpio_pin_t pin, gpio_dir_t direction);
gpio_ret_t gpio_pin_read(gpio_port_t port, gpio_pin_t pin, gpio_level_t *reading);
gpio_ret_t gpio_pin_write(gpio_port_t port, gpio_pin_t pin, gpio_level_t level);
gpio_ret_t gpio_pin_toggle(gpio_port_t port, gpio_pin_t pin);

gpio_ret_t gpio_pin_configure_pupd(gpio_port_t port, gpio_pin_t pin, gpio_pupd_t pupd);
gpio_ret_t gpio_pin_configure_alt_func(gpio_port_t port, gpio_pin_t pin, gpio_alt_func_t func);

#endif /* GPIO_H */