#include "q7seg.h"
#include "gpio.h"
#include "rcc.h"

q7seg_pin_t q7segPins[Q7SEG_PIN_NUM] = {q7segPinA, q7segPinB, q7segPinC, q7segPinD, q7segPinE, q7segPinF, q7segPinG, q7segPinDp};
q7seg_seg_t q7segSegs[Q7SEG_SEG_NUM] = {q7seg1, q7seg2, q7seg3, q7seg4};

/// @brief Initializes display by setting up GPIO
/// @return Status of operation
q7seg_ret_t initDisplay() {
    rcc_enable_peripheral_clk(rccClkGpioB);
    gpio_port_set_dir(Q7SEG_GPIO_PORT, gpioOutput);

    return q7segSuccess;
}

/// @brief Writes to the GPIO pins to set the number section of display
/// @param num Base-10 number to display
/// @return Status of operation
q7seg_ret_t writeNum(uint8_t num) {
    uint16_t bitmask = 0;

    // Clear all pins to erase last config
    for(uint8_t i = 0; i < Q7SEG_PIN_NUM; i++) {
        gpio_pin_write(Q7SEG_GPIO_PORT, q7segPins[i], gpioPinHigh);
    }

    // Determine bitmask based on number
    switch(num) {
        case 0:
            bitmask |= (1 << q7segPinA) | (1 << q7segPinB) | (1 << q7segPinC) | (1 << q7segPinD) | (1 << q7segPinE) | (1 << q7segPinF); 
            break;
        case 1:
            bitmask |= (1 << q7segPinB) | (1 << q7segPinC); 
            break;
        case 2:
            bitmask |= (1 << q7segPinA) | (1 << q7segPinB) | (1 << q7segPinG) | (1 << q7segPinE) | (1 << q7segPinD); 
            break;
        case 3:
            bitmask |= (1 << q7segPinA) | (1 << q7segPinB) | (1 << q7segPinG) | (1 << q7segPinC) | (1 << q7segPinD);  
            break;
        case 4:
            bitmask |= (1 << q7segPinF) | (1 << q7segPinB) | (1 << q7segPinG) | (1 << q7segPinC); 
            break;
        case 5:
            bitmask |= (1 << q7segPinA) | (1 << q7segPinF) | (1 << q7segPinG) | (1 << q7segPinC) | (1 << q7segPinD); 
            break;
        case 6:
            bitmask |= (1 << q7segPinA) | (1 << q7segPinG) | (1 << q7segPinC) | (1 << q7segPinD) | (1 << q7segPinE) | (1 << q7segPinF); 
            break;
        case 7:
            bitmask |= (1 << q7segPinA) | (1 << q7segPinB) | (1 << q7segPinC); 
            break;
        case 8:
            bitmask |= (1 << q7segPinA) | (1 << q7segPinB) | (1 << q7segPinC) | (1 << q7segPinD) | (1 << q7segPinE) | (1 << q7segPinF) | (1 << q7segPinG); 
            break;
        case 9:
            bitmask |= (1 << q7segPinA) | (1 << q7segPinB) | (1 << q7segPinC) | (1 << q7segPinD) | (1 << q7segPinF) | (1 << q7segPinG); 
            break;
    }

    // Set all pins to new config
    for(uint8_t i = 0; i < Q7SEG_PIN_NUM; i++) {
        uint8_t shiftedBit = ~(bitmask >> q7segPins[i]) & 1U;
        gpio_pin_write(Q7SEG_GPIO_PORT, q7segPins[i], shiftedBit);
    }

    return q7segSuccess;
}

/// @brief Writes a single segment on Q7Seg display
/// @param segment Segment to write to
/// @param num Base-10 number to display
/// @param dp Whether or not we want the DP active 
/// @return Status of operation
q7seg_ret_t writeDisplaySingle(q7seg_seg_t segment, uint8_t num, uint8_t dp) {
    // Enable segment
    gpio_pin_write(Q7SEG_GPIO_PORT, segment, gpioPinHigh);

    // Set display point
    gpio_pin_write(Q7SEG_GPIO_PORT, q7segPinDp, dp);

    // Write number
    writeNum(num);

    return q7segSuccess;
}
