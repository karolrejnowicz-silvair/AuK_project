#ifndef __TIM_PWM_H
#define __TIM_PWM_H

#include "stm32f4xx_hal.h"

void timer_init(void);
void pwm_ch1_init(void);
void pwm_ch1_dim( int val, int channel );
void pwm_ch2_init(void);
void pwm_ch3_init(void);
void pwm_ch4_init(void);
	


// Nie wiem dlaczego ale to nie jest zdefiniowane w pliku stm32f4xx_hal_tim_ex.h
// ale w pliku .c jest

//void TIM_OC1_SetConfig(TIM_TypeDef *TIMx, TIM_OC_InitTypeDef *OC_Config);

#endif
