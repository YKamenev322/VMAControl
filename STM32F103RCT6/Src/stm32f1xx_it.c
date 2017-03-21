/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"
#include "stm32f1xx.h"
#include "stm32f1xx_it.h"
#include "cmsis_os.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/

extern TIM_HandleTypeDef htim4;

extern DMA_HandleTypeDef hdma_adc1;
extern ADC_HandleTypeDef hadc1;
/******************************************************************************/
/*            Cortex-M3 Processor Interruption and Exception Handlers         */ 
/******************************************************************************/

void NMI_Handler(void)
{
}

void HardFault_Handler(void)
{
  while (1)
  {
		//rts_toggle();
		//HAL_Delay(100);
  }
}

void MemManage_Handler(void)
{
  while (1)
  {
		//rts_toggle();
		//HAL_Delay(100);
  }
}

void BusFault_Handler(void)
{
  while (1)
  {
		//rts_toggle();
		//HAL_Delay(100);
  }
}

void UsageFault_Handler(void)
{
  while (1)
  {
		//rts_toggle();
		//HAL_Delay(100);
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
  osSystickHandler();
}

void EXTI4_IRQHandler(void)
{
  HAL_GPIO_EXTI_IRQHandler(BRAKE);
}

void EXTI9_5_IRQHandler(void)
{
	HAL_GPIO_EXTI_IRQHandler(FAULT);
}

/**
* @brief This function handles TIM4 global interrupt.
*/
void TIM4_IRQHandler(void)
{
  HAL_TIM_IRQHandler(&htim4);
}

void TIM2_IRQHandler(void)
{
  HAL_TIM_IRQHandler(&htim2);
}

//void DMAChannel1_IRQHandler(void)
void DMA1_Channel1_IRQHandler(void)
{
  HAL_DMA_IRQHandler(hadc1.DMA_Handle);
}

//void ADC_IRQHandler(void)
void ADC1_2_IRQHandler(void)
{
  HAL_ADC_IRQHandler(&hadc1);
}

//void USART1_IRQHandler(void)
void USART2_IRQHandler(void)
{
  HAL_UART_IRQHandler(&huart);
}

/**
  *         used for USART data reception
  */

//void DMAChannel5_IRQHandler(void)
void DMA1_Channel6_IRQHandler(void)
{
  HAL_DMA_IRQHandler(huart.hdmarx);
}


/**
  *         used for USART data transmission
  */
	
//void DMAChannel4_IRQHandler(void)
void DMA1_Channel7_IRQHandler(void)
{
  HAL_DMA_IRQHandler(huart.hdmatx);
}

/**
* @brief This function handles TIM8 update interrupt.
*/
void TIM8_UP_IRQHandler(void)
{
  HAL_TIM_IRQHandler(&htim8);
}

/**
* @brief This function handles TIM8 capture compare interrupt.
*/
void TIM8_CC_IRQHandler(void)
{
  HAL_TIM_IRQHandler(&htim8);
}