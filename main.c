
#include "stm32f4xx_hal.h"
#include "stm32f401_discovery.h"
#include "lsm303dlhc.h"
#include "stm32f401_discovery_accelerometer.h"
#include "math.h"
#include "mag_accel.h"
//#include "tim_pwm.h"


void LED_Init(void);
void delay(int milisec);

uint8_t button_flag = 0;
int tick = 0;

int main() {

	uint8_t data[2] = {0, 0};
	float Data[3] = {0, 0, 0};
	
	HAL_Init();
	LED_Init();
	BSP_PB_Init(BUTTON_KEY, BUTTON_MODE_EXTI);
	//timer_init();
	//pwm_init(1);
	//pwm_init(2);
	//pwm_init(3);
	//pwm_init(4);
	
	accel_gyro_Init(data);


	tick = 0; 
	GyroAngle(Data);

	//}
	while(1)
	{	
		
	/*	if(BSP_PB_GetState(BUTTON_KEY) == 1) {
			pwm_ch_dim(1000 , 1);	
			pwm_ch_dim(0, 2);
			pwm_ch_dim(0, 3);
			pwm_ch_dim(0, 4);
		}
		else {
			pwm_ch_dim(0, 1);
			pwm_ch_dim(1000, 2);
			pwm_ch_dim(1000, 3);
			pwm_ch_dim(1000, 4);
		}
		*/
	}
	
	return 0;
}


/**
 * This function configures the LED pins
 */
void LED_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct;
 
  // GPIO Ports Clock Enable
  __GPIOD_CLK_ENABLE();
 
  // Configure GPIO pin PD15
  GPIO_InitStruct.Pin   =  GPIO_PIN_15 | GPIO_PIN_13 | GPIO_PIN_14 |  GPIO_PIN_12 ;
  GPIO_InitStruct.Mode  = GPIO_MODE_AF_PP;        // push-pull output
  GPIO_InitStruct.Pull  = GPIO_NOPULL;              
  GPIO_InitStruct.Speed = GPIO_SPEED_FAST;             // analog pin bandwidth limited
  GPIO_InitStruct.Alternate = GPIO_AF2_TIM4;
	HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
        
	
} /* LED_Init */


/**
 * Introduces a noticable delay in program execution
 */
void delay(int milisec)
{
	int i=1;
  while(i){
    if(tick==milisec){
				tick=0;
				i=0;
		}
	}  
} /* delay */



/**
 * System Tick Interrupt Service Routine 
 */
void SysTick_Handler(void)
{
    tick++;     
} /* SysTick_Handler */


void EXTI0_IRQHandler(void)
{
  // Check if EXTI line interrupt was detected
  if(__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_0) != RESET)  {
    // Clear the interrupt (has to be done for EXTI)
    __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_0);
    // Toggle LED
    button_flag = 1;
  }
}
