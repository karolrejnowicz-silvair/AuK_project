#include "tim_pwm.h"
  
uint16_t PrescalerValue = 4000;

TIM_Base_InitTypeDef TIM_TimeBaseStructure;
TIM_OC_InitTypeDef  TIM_OCInitStructure;
TIM_HandleTypeDef TIM4_Handle;

void timer_init(void){

	/* TIM Configuration */
	
//===============	TIM_Config();  - will do in a little bit later
		
		/* -----------------------------------------------------------------------
		TIM3 Configuration: generate 4 PWM signals with 4 different duty cycles.
		
		In this example TIM3 input clock (TIM3CLK) is set to 2 * APB1 clock (PCLK1), 
		since APB1 prescaler is different from 1.   
		TIM3CLK = 2 * PCLK1  
		PCLK1 = HCLK / 4 
		=> TIM3CLK = HCLK / 2 = SystemCoreClock /2
		
		To get TIM3 counter clock at 14 MHz, the prescaler is computed as follows:
		Prescaler = (TIM3CLK / TIM3 counter clock) - 1
		Prescaler = ((SystemCoreClock /2) /14 MHz) - 1
		
		To get TIM3 output clock at 21 KHz, the period (ARR)) is computed as follows:
		ARR = (TIM3 counter clock / TIM3 output clock) - 1
		= 665
		
		TIM3 Channel1 duty cycle = (TIM3_CCR1/ TIM3_ARR)* 100 = 50%
		TIM3 Channel2 duty cycle = (TIM3_CCR2/ TIM3_ARR)* 100 = 37.5%
		TIM3 Channel3 duty cycle = (TIM3_CCR3/ TIM3_ARR)* 100 = 25%
		TIM3 Channel4 duty cycle = (TIM3_CCR4/ TIM3_ARR)* 100 = 12.5%
		
		Note: 
		SystemCoreClock variable holds HCLK frequency and is defined in system_stm32f4xx.c file.
		Each time the core clock (HCLK) changes, user had to call SystemCoreClockUpdate()
		function to update SystemCoreClock variable value. Otherwise, any configuration
		based on this variable will be incorrect.    
		----------------------------------------------------------------------- */  
		
		/* Compute the prescaler value */
		PrescalerValue = (uint16_t) (SystemCoreClock / 14000000) - 1;
		
		__TIM4_CLK_ENABLE();
		
		TIM4_Handle.Instance = TIM4;
		
		/* Time base configuration */
		TIM4_Handle.Init.Period = 1000; //8399;		
		TIM4_Handle.Init.Prescaler = 240;//PrescalerValue;
		TIM4_Handle.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1 ;
		TIM4_Handle.Init.CounterMode = TIM_COUNTERMODE_UP;
		
		HAL_TIM_Base_Init(&TIM4_Handle);
		HAL_TIM_Base_Start_IT(&TIM4_Handle); // start timer interrupts
		
		//HAL_NVIC_SetPriority(TIM4_IRQn, 0, 1);
    //HAL_NVIC_EnableIRQ(TIM4_IRQn);
		 
	}

void pwm_init(int channel){
	
	  TIM_OCInitStructure.OCMode = TIM_OCMODE_PWM1;
	 	TIM_OCInitStructure.Pulse = 0;//CCR1_Val;
		TIM_OCInitStructure.OCPolarity = TIM_OCPOLARITY_HIGH;
		TIM_OCInitStructure.OCFastMode = TIM_OCFAST_DISABLE;
	
	switch(channel){
		
		case 1:	
						HAL_TIM_PWM_ConfigChannel(&TIM4_Handle, &TIM_OCInitStructure, TIM_CHANNEL_1);
						TIM_CCxChannelCmd(TIM4, TIM_CHANNEL_1, TIM_CCx_ENABLE);
						break;
		case 2:
						HAL_TIM_PWM_ConfigChannel(&TIM4_Handle, &TIM_OCInitStructure, TIM_CHANNEL_2);
						TIM_CCxChannelCmd(TIM4, TIM_CHANNEL_2, TIM_CCx_ENABLE);
						break;
		case 3:
						HAL_TIM_PWM_ConfigChannel(&TIM4_Handle, &TIM_OCInitStructure, TIM_CHANNEL_3);
						TIM_CCxChannelCmd(TIM4, TIM_CHANNEL_3, TIM_CCx_ENABLE);
						break;
		case 4:	
						HAL_TIM_PWM_ConfigChannel(&TIM4_Handle, &TIM_OCInitStructure, TIM_CHANNEL_4);
						TIM_CCxChannelCmd(TIM4, TIM_CHANNEL_4, TIM_CCx_ENABLE);
						break;
		default:
						break;
	}
	
	
}
	


void pwm_ch_dim( int val, int channel ){
	
	switch(channel){
		
		case 1:
				TIM4->CCR1 = val; // = TIM_OCInitStructure.Pulse
				break;
		case 2:
				TIM4->CCR2= val;
				break;
		case 3:
				TIM4->CCR3 = val;	
				break;
		case 4:
				TIM4->CCR4= val;
				break;
		default:
			break;
	}
	
	return;
}


		




