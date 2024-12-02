#ifndef TIM_GENERAL_H
#define TIM_GENERAL_H

#include <stdint.h>
#include "stm32f446xx.h"

extern TIM_TypeDef* timGeneral2to5PtrArray[4];

typedef uint16_t tim_general_prescaler_t;
typedef uint32_t tim_general_load_t;

typedef enum {
    timGeneralTimer2,   // 32 bit timer
    timGeneralTimer3,   // 16 bit timer
    timGeneralTimer4,   // 16 bit timer
    timGeneralTimer5    // 32 bit timer
} tim_general_timer_t;

typedef enum {
    timGeneralCountUp,
    timGeneralCountDown
} tim_general_count_paradigm_t;

// CK_INT clock runs at ?
typedef enum {
    timGenCkInt,
    timGenCkIntTimes2,
    timGenCkTntTimes4
} tim_general_clk_div_t;

typedef struct {
    tim_general_count_paradigm_t countStyle;
    tim_general_prescaler_t prescaleAmount;
    tim_general_clk_div_t clockDivision;
    tim_general_load_t preloadValue
} tim_general_config_t;

typedef enum {
    timFail,
    timSuccess
} tim_ret_t;

#endif /* TIM_GENERAL_H */