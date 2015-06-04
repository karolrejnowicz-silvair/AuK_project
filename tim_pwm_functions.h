#ifndef __TIM_PWM_FUNCTIONS_H
#define __TIM_PWM_FUNCTIONS_H

#include "stm32f4xx_hal.h"

void TIM_OC1_SetConfig(TIM_TypeDef *TIMx, TIM_OC_InitTypeDef *OC_Config);
void TIM_OC3_SetConfig(TIM_TypeDef *TIMx, TIM_OC_InitTypeDef *OC_Config);
void TIM_OC4_SetConfig(TIM_TypeDef *TIMx, TIM_OC_InitTypeDef *OC_Config);

#endif
