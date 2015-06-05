
#include "stm32f4xx_hal.h"
#include "stm32f401_discovery.h"
#include "math.h"
#include "app.h"


void LED_Init(void);
void delay(int milisec);

uint8_t button_flag = 0;
int tick = 0;

int main() {

	uint8_t data[2] = {0, 0};
	float Data[3] = {0, 0, 0};
	float GyroError[3] = {0.0f, 0.0f, 0.0f };
	
	HAL_Init();
	LED_Init();
	BSP_PB_Init(BUTTON_KEY, BUTTON_MODE_EXTI);
	
	accel_gyro_Init(data, GyroError);
	PWM_Init();

	tick = 0; 
	GetXYZangle(Data, GyroError);

	while(1)
	{	
		
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
