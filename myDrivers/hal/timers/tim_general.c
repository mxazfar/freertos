#include "tim_general.h"
#include "stm32f446xx.h"

TIM_TypeDef* timGeneral2to5PtrArray[4] = {TIM2, TIM3, TIM4, TIM5};

tim_ret_t configureTimer(tim_general_timer_t timer, tim_general_config_t *timerConfiguration) {
    TIM_TypeDef* timerBase = timGeneral2to5PtrArray[timer];

    timerBase->CR1 |= (timerConfiguration->clockDivision << TIM_CR1_CKD_Pos) | 
                      (timerConfiguration->countStyle << TIM_CR1_DIR_Pos) |
                      (1 << TIM_CR1_URS_Pos); // hardcoding this for now, only under/overflow generate UEV

    timerBase->PSC = timerConfiguration->prescaleAmount;
    timerBase->ARR = timerConfiguration->preloadValue;
    timerBase->DIER |= TIM_DIER_UIE;

    return timSuccess;
}

tim_ret_t startTimer(tim_general_timer_t timer) {
    TIM_TypeDef* timerBase = timGeneral2to5PtrArray[timer];

    timerBase->CR1 |= (1 << TIM_CR1_CEN_Pos);

    return timSuccess;
}

tim_ret_t stopTimer(tim_general_timer_t timer) {
    TIM_TypeDef* timerBase = timGeneral2to5PtrArray[timer];

    timerBase->CR1 &= ~(1 << TIM_CR1_CEN_Pos);

    return timSuccess;
}