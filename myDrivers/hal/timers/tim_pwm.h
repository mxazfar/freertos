#ifndef TIM_PWM_H
#define TIM_PWM_H

#include "gpio.h"
#include "tim_general.h"

#define TIM_PWM_UNIT_REGISTER_OFFSET 0x400

typedef enum {
    timCmsDownInt = 1,
    timCmsUpInt,
    timCmsUpDownInt
} tim_pwm_cms_t;

typedef enum {
    timPwmMode1 = 6,
    timPwmMode2 
} tim_pwm_mode_t;

typedef enum {
    timPwm1,
    timPwm2
} tim_pwm_timer_t;

typedef enum {
    timPwmOutputMode,
    timPwmInputTI1,
    timPwmInputTI2,
    timPwmInputTRC
} tim_pwm_in_out_t;

typedef enum {
    timPwmChannel1,
    timPwmChannel2,
    timPwmChannel3,
    timPwmChannel4
} tim_pwm_channel_t;

typedef struct {
    tim_pwm_channel_t pwmChannel;
    tim_pwm_in_out_t pwmIOMode;
    tim_pwm_mode_t pwmFunctionalMode;
    tim_pwm_cms_t pwmCenterAlignmentMode;
    tim_general_prescaler_t prescaleAmount;
    tim_general_clk_div_t clockDivision;
    tim_general_load_t preloadValue;
} tim_pwm_config_t;

#endif /* TIM_PWM_H */