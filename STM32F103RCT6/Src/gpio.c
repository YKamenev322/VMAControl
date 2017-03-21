
#include "gpio.h"
uint16_t count_c, count_h;
uint8_t count_3button;
bool needsavecount_cFlg, needsavecount_hFlg, need_clearLCD_flag, ind_flag;

void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct;

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();

	
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	
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
  //GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(PORT_DBG, &GPIO_InitStruct);
	
  /*Configure GPIO pins as input interrupt: PB4 */	
  GPIO_InitStruct.Pin = BRAKE;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(PORT_BRAKE, &GPIO_InitStruct);
  /*Configure GPIO pins as input interrupt: PB8 */
  GPIO_InitStruct.Pin = FAULT;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(PORT_FAULT, &GPIO_InitStruct);
	
  HAL_NVIC_SetPriority(EXTI4_IRQn, 1, 0);
  HAL_NVIC_EnableIRQ(EXTI4_IRQn);		
  HAL_NVIC_SetPriority(EXTI9_5_IRQn, 1, 0);
  HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);
	
	/* Configure GPIO pins as output: PB9 */
	GPIO_InitStruct.Pin = RESET_PIN;
  GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull  = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(PORT_RESET, &GPIO_InitStruct);
		
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
	
//	return (1 + (!HAL_GPIO_ReadPin(PORT_DIP4, DIP4) << 3) | (!HAL_GPIO_ReadPin(PORT_DIP3, DIP3) << 2) |
//				 (!HAL_GPIO_ReadPin(PORT_DIP2, DIP2) << 1) | (!HAL_GPIO_ReadPin(PORT_DIP1, DIP1)));
//		return (1 + ((!HAL_GPIO_ReadPin(PORT_DIP4, DIP4) << 2) | (!HAL_GPIO_ReadPin(PORT_DIP3, DIP3) << 1) | (!HAL_GPIO_ReadPin(PORT_DIP2, DIP2) << 0)));
		return (1 + ((!HAL_GPIO_ReadPin(PORT_DIP3, DIP3) << 2) | (!HAL_GPIO_ReadPin(PORT_DIP2, DIP2) << 1) | (!HAL_GPIO_ReadPin(PORT_DIP1, DIP1) << 0)));

}
/* USER CODE BEGIN 2 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  if (GPIO_Pin == BRAKE)
  {
		//пока не работает, пин подтянут к 3.3В на плате
		dbg_toggle();
  }
  if (GPIO_Pin == FAULT)
  {
		dbg_toggle();
  }	
}

