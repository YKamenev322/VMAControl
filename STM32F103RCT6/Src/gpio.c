
#include "gpio.h"	
#include "cmsis_os.h"
#include "vma.h"
extern TimerHandle_t VMATimer;
extern TimerHandle_t VMAResetTimer;
extern DRIVER Vma;
extern DRIVER Add;

void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct;

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();

  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	
#if !defined(SEMENUK_DRIVER)
  /*Configure GPIO pins : PA15 */
  GPIO_InitStruct.Pin = DIP1;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(PORT_DIP1, &GPIO_InitStruct);
  /*Configure GPIO pins : PC10 */
  GPIO_InitStruct.Pin = DIP2;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(PORT_DIP2, &GPIO_InitStruct);
  /*Configure GPIO pins : PC11 */
  GPIO_InitStruct.Pin = DIP3;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(PORT_DIP3, &GPIO_InitStruct);
  /*Configure GPIO pins : PC12 */
  GPIO_InitStruct.Pin = DIP4;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(PORT_DIP4, &GPIO_InitStruct);
  /*Configure GPIO pins : PD2 */
  GPIO_InitStruct.Pin = DIP5;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(PORT_DIP5, &GPIO_InitStruct);
  /*Configure GPIO pins : PB5 */
  GPIO_InitStruct.Pin = DIP6;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(PORT_DIP6, &GPIO_InitStruct);
	/* Configure DEBUG pin : PA6 */
	GPIO_InitStruct.Pin = DBG;
  GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull  = GPIO_PULLUP;
  HAL_GPIO_Init(PORT_DBG, &GPIO_InitStruct);
	
  /*Configure GPIO pins as input interrupt: PB4 */	
  GPIO_InitStruct.Pin = BRAKE;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(PORT_BRAKE, &GPIO_InitStruct);
	
	/*Configure GPIO pins as input interrupt: PB8 */
  GPIO_InitStruct.Pin  = FAULT;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;//GPIO_MODE_IT_RISING
  GPIO_InitStruct.Pull = GPIO_PULLUP;//GPIO_PULLDOWN
  HAL_GPIO_Init(PORT_FAULT, &GPIO_InitStruct);
	
	////// MOTOR PINS //////////////////
	GPIO_InitStruct.Pin = MOTOR_DIR;
  GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull  = GPIO_PULLUP;
  HAL_GPIO_Init(PORT_MOTOR_DIR, &GPIO_InitStruct);
	
	GPIO_InitStruct.Pin = MOTOR_EN;
  GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull  = GPIO_PULLUP;
  HAL_GPIO_Init(PORT_MOTOR_EN, &GPIO_InitStruct);
	
	GPIO_InitStruct.Pin = HALL_SENSOR_A;
  GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull  = GPIO_PULLUP;
  HAL_GPIO_Init(PORT_HALL_SENSOR_A, &GPIO_InitStruct);
	
	GPIO_InitStruct.Pin = HALL_SENSOR_B;
  GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull  = GPIO_PULLUP;
  HAL_GPIO_Init(PORT_HALL_SENSOR_B, &GPIO_InitStruct);
	
	GPIO_InitStruct.Pin = HALL_SENSOR_C;
  GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull  = GPIO_PULLUP;
  HAL_GPIO_Init(PORT_HALL_SENSOR_C, &GPIO_InitStruct);
	///////////////////////////////////
#if defined(VMA_ENABLE_BRAKE)	
  HAL_NVIC_SetPriority(BRAKE_EXTI_IRQn, 6, 0);
  HAL_NVIC_EnableIRQ(BRAKE_EXTI_IRQn);	
#endif	
#if defined(ADD_ENABLE_FAULT)
  HAL_NVIC_SetPriority(FAULT_EXTI_IRQn, 6, 0);
  HAL_NVIC_EnableIRQ(FAULT_EXTI_IRQn);
#endif
	/* Configure GPIO pins as output: PB9 */
	
	GPIO_InitStruct.Pin = RESET_PIN;
  GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_OD;
  GPIO_InitStruct.Pull  = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(PORT_RESET, &GPIO_InitStruct);
	
	HAL_GPIO_WritePin(PORT_RESET, RESET_PIN, GPIO_PIN_SET);
	
#else

  GPIO_InitStruct.Pin = DIP1;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(PORT_DIP1, &GPIO_InitStruct);
	
  GPIO_InitStruct.Pin = DIP2;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(PORT_DIP2, &GPIO_InitStruct);
	
  GPIO_InitStruct.Pin = DIP3;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(PORT_DIP3, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = DIP4;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(PORT_DIP4, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = DBG;
  GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull  = GPIO_PULLUP;
  HAL_GPIO_Init(PORT_DBG, &GPIO_InitStruct);
	
  GPIO_InitStruct.Pin = FAULT;//add-dr
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;//GPIO_MODE_IT_RISING
  GPIO_InitStruct.Pull = GPIO_PULLUP;//GPIO_PULLDOWN
  HAL_GPIO_Init(PORT_FAULT, &GPIO_InitStruct);
#if defined(ADD_ENABLE_FAULT)
  HAL_NVIC_SetPriority(FAULT_EXTI_IRQn, 6, 0);
  HAL_NVIC_EnableIRQ(FAULT_EXTI_IRQn);
#endif
#endif
}
void dbg_toggle()
{
	HAL_GPIO_TogglePin(PORT_DBG, DBG);
}
void dbg_on()
{
	HAL_GPIO_WritePin(PORT_DBG, DBG, GPIO_PIN_SET);
}
void dbg_off()
{
	HAL_GPIO_WritePin(PORT_DBG, DBG, GPIO_PIN_RESET);
}
void rst_on()
{
	HAL_GPIO_WritePin(PORT_RESET, RESET_PIN, GPIO_PIN_SET);
}
void rst_off()
{
	HAL_GPIO_WritePin(PORT_RESET, RESET_PIN, GPIO_PIN_RESET);
}

uint8_t MX_GPIO_Init_Address(void)
{
	
#if !defined(SEMENUK_DRIVER)
	return (1 + ((!HAL_GPIO_ReadPin(PORT_DIP3, DIP3) << 2) | (!HAL_GPIO_ReadPin(PORT_DIP2, DIP2) << 1) | (!HAL_GPIO_ReadPin(PORT_DIP1, DIP1) << 0)));
#else
	return (1 + ((!HAL_GPIO_ReadPin(PORT_DIP2, DIP2) << 1) | (!HAL_GPIO_ReadPin(PORT_DIP1, DIP1) << 0)));
#endif
	
}
/* USER CODE BEGIN 2 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
#if !defined(SEMENUK_DRIVER)
	static portBASE_TYPE xHigherPriorityTaskWoken;
  if (GPIO_Pin == BRAKE)
  {
		xHigherPriorityTaskWoken = pdFALSE;
		DRIVER_PwmDisable(&Vma);
//		xTimerStartFromISR(VMATimer, &xHigherPriorityTaskWoken);
//		xTimerStartFromISR(VMAResetTimer, &xHigherPriorityTaskWoken);//таймер на сброс защиты по току
		xTimerResetFromISR(VMATimer, &xHigherPriorityTaskWoken);//disable pwm 
		xTimerResetFromISR(VMAResetTimer, &xHigherPriorityTaskWoken);//reset pin 
		/*
		if (xHigherPriorityTaskWoken == pdTRUE)
		{
			xHigherPriorityTaskWoken = pdFALSE;
			taskYIELD();
		}
		*/
  }
#endif

#if defined(SEMENUK_DRIVER)	
  if (GPIO_Pin == FAULT)//add-dr
  {
		DRIVER_PwmDisable(&Add);
  }	
#endif
}

