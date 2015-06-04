#ifndef __TIM_PWM_H
#define __TIM_PWM_H

#include "stm32f4xx_hal.h"

void timer_init(void);
void pwm_ch_dim( int val, int channel );
void pwm_init(int channel);


#endif
