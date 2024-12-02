#ifndef Q7SEG_H
#define Q7SEG_H

#include "gpio.h"

#define Q7SEG_GPIO_PORT gpioB 

#define Q7SEG_TOTAL_PIN_NUM 12
#define Q7SEG_PIN_NUM 8
#define Q7SEG_SEG_NUM 4

typedef enum {
    q7segFail,
    q7segSuccess
} q7seg_ret_t;

typedef enum {
    q7segPinA = 10,
    q7segPinB = 6,
    q7segPinC = 3,
    q7segPinD = 1,
    q7segPinE = 0,
    q7segPinF = 9,
    q7segPinG = 4,
    q7segPinDp = 2
} q7seg_pin_t;

typedef enum {
    q7seg1 = 11,
    q7seg2 = 8,
    q7seg3 = 7,
    q7seg4 = 5,
} q7seg_seg_t;

extern q7seg_pin_t q7segPins[Q7SEG_PIN_NUM];
extern q7seg_seg_t q7segSegs[Q7SEG_SEG_NUM];

/// @brief Initializes display by setting up GPIO
/// @return Status of operation
q7seg_ret_t initDisplay();

/// @brief Writes to the GPIO pins to set the number section of display
/// @param num Base-10 number to display
/// @return Status of operation
q7seg_ret_t writeNum(uint8_t num);

/// @brief Writes a single segment on Q7Seg display
/// @param segment Segment to write to
/// @param num Base-10 number to display
/// @param dp Whether or not we want the DP active 
/// @return Status of operation
q7seg_ret_t writeDisplaySingle(q7seg_seg_t segment, uint8_t num, uint8_t dp);

#endif /* Q7SEG_H */