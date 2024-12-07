#include "stm32f446xx.h"
#include "tim_pwm.h"
#include "rcc.h"

#define TIM_PWM_GET_UNIT_ADDR(timer) ((uintptr_t)TIM1 + (TIM_PWM_UNIT_REGISTER_OFFSET*timer))

tim_ret_t configurePwm(tim_pwm_timer_t pwmTimer, tim_pwm_config_t *pwmConfig) {
    TIM_TypeDef *pwmBase = TIM_PWM_GET_UNIT_ADDR(pwmTimer);
    uint8_t pwmCMMR1Shift = pwmConfig->pwmChannel * 8;
    uint8_t pwmCMMR2Shift = (pwmConfig->pwmChannel - 2) * 8;

    // supply clock to PWM module
    rcc_enable_peripheral_clk(rccClkTim1 + pwmTimer);

    if(pwmConfig->pwmIOMode == timPwmOutputMode) {
        // set IO, PWM mode and enable preload for now
        if(pwmConfig->pwmChannel < 2) {
            pwmBase->CCMR1 |= (pwmConfig->pwmIOMode << pwmCMMR1Shift);
            pwmBase->CCMR1 |= (pwmConfig->pwmFunctionalMode << pwmCMMR1Shift + 4);
            pwmBase->CCMR1 |= (1 << pwmCMMR1Shift + 3);
        } else {
            pwmBase->CCMR2 |= (pwmConfig->pwmIOMode << pwmCMMR2Shift);
            pwmBase->CCMR2 |= (pwmConfig->pwmFunctionalMode << pwmCMMR2Shift + 4);
            pwmBase->CCMR2 |= (1 << pwmCMMR2Shift + 3);
        }

        // set center mode alignment in CR1 (only center aligned PWM in this household)
        pwmBase->CR1 |= pwmConfig->pwmCenterAlignmentMode << TIM_CR1_CMS_Pos;

        // enable capture/compare output
        pwmBase->CCER |= (1 << pwmTimer * 4);
        pwmBase->CCER &= ~(1 << (pwmTimer * 4) + 1);
        pwmBase->CCER |= (1 << (pwmTimer * 4) + 2);
        pwmBase->CCER |= (1 << (pwmTimer * 4) + 3); // unsure about this NP polarity to low

        // configure corresponding GPIO (supply clock, set mode, set speed) 
    } else {
        // implement PWM input mode later

        return timFail;
    }

    pwmBase->CR1 |= TIM_CR1_ARPE_Msk;
    pwmBase->PSC = pwmConfig->prescaleAmount;
    pwmBase->ARR = pwmConfig->preloadValue;

    // set UG bit in TIMx_EGR to trigger update event and load shadow regs
    pwmBase->EGR |= TIM_EGR_UG_Msk;

    return timSuccess;
} 

tim_ret_t startPwm(tim_pwm_timer_t pwmTimer) {
    TIM_TypeDef *pwmBase = TIM_PWM_GET_UNIT_ADDR(pwmTimer);
    // set UG bit in EGR to load preload regs
    pwmBase->EGR |= TIM_EGR_UG_Msk;

    // set CEN in CR1 to start timer
    pwmBase->CR1 |= TIM_CR1_CEN_Msk;

    return timSuccess;
}

tim_ret_t setPwmDuty(tim_pwm_timer_t pwmTimer, uint8_t pwmDutyPercent) {

    return timSuccess;
}

tim_ret_t setPwmPeriod(tim_pwm_timer_t pwmTimer, uint32_t pwmPeriodUs) {
    
    return timSuccess;
}