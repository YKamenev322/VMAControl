
#include "stm32f1xx_hal.h"
#include "usart.h"

extern UART_HandleTypeDef huart;

extern void led_tog();
/**
* @brief This function handles Non maskable interrupt.
*/
void NMI_Handler(void)
{
}

/**
* @brief This function handles Hard fault interrupt.
*/
void HardFault_Handler(void)
{
  while (1)
  {

  }
}


void MemManage_Handler(void)
{
  while (1)
  {

  }
}


void BusFault_Handler(void)
{
  while (1)
  {

  }
}

void UsageFault_Handler(void)
{
  while (1)
  {

  }
}


void DebugMon_Handler(void)
{

}

/**
* @brief This function handles System tick timer.
*/
void SysTick_Handler(void)
{
	HAL_IncTick();
}

//void USART1_IRQHandler(void)
//void USART2_IRQHandler(void)
void USARTx_IRQHandler(void)
{
  HAL_UART_IRQHandler(&huart);
}

/**
  *         used for USART data reception
  */

//void DMAChannel5_IRQHandler(void)
//void DMAChannel6_IRQHandler(void)
void USARTx_DMA_RX_IRQHandler(void)
{
  HAL_DMA_IRQHandler(huart.hdmarx);
}


/**
  *         used for USART data transmission
  */
	
//void DMAChannel4_IRQHandler(void)
//void DMAChannel7_IRQHandler(void)
void USARTx_DMA_TX_IRQHandler(void)
{
  HAL_DMA_IRQHandler(huart.hdmatx);
}
