/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"
#include "stm32f1xx.h"
#include "stm32f1xx_it.h"
#include "cmsis_os.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "adc.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/

extern TIM_HandleTypeDef htim4;
//extern TIM_HandleTypeDef htim2;

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
#if !defined(SEMENUK_DRIVER)
/*
void EXTI4_IRQHandler(void)
{
  HAL_GPIO_EXTI_IRQHandler(BRAKE);
}
*/
void BRAKE_IRQHandler(void)//needTest
{
  HAL_GPIO_EXTI_IRQHandler(BRAKE);
}
#endif

/*
void EXTI9_5_IRQHandler(void)
{
	HAL_GPIO_EXTI_IRQHandler(FAULT);
}
*/
void FAULT_IRQHandler(void)//needTest
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


/******************* ADC *****************/
//void DMA1_Channel1_IRQHandler(void)
void ADCx_DMA_IRQHandler(void)//needTest
{
  HAL_DMA_IRQHandler(hadc1.DMA_Handle);
}

//void ADC1_2_IRQHandler(void)
void ADCx_IRQHandler(void)//needTest
{
  HAL_ADC_IRQHandler(&hadc1);
}
/****************END ADC *****************/

/******************* UART *****************/
//void USART2_IRQHandler(void)
void USARTx_IRQHandler(void)//needTest
{
  HAL_UART_IRQHandler(&huart);
}
//Uart Rx
//void DMA1_Channel6_IRQHandler(void)
void USARTx_DMA_RX_IRQHandler(void)//needTest
{
  HAL_DMA_IRQHandler(huart.hdmarx);
}
//Uart Tx
//void DMA1_Channel7_IRQHandler(void)
void USARTx_DMA_TX_IRQHandler(void)//needTest	
{
  HAL_DMA_IRQHandler(huart.hdmatx);
}
/****************END UART *****************/

void TIM2_IRQHandler(void)
{
  HAL_TIM_IRQHandler(&htim2);
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
/**
* @brief This function handles TIM1 update interrupt.
*/
void TIM1_UP_IRQHandler(void)
{
  HAL_TIM_IRQHandler(&htim1);
}

/**
* @brief This function handles TIM1 capture compare interrupt.
*/
void TIM1_CC_IRQHandler(void)
{
  HAL_TIM_IRQHandler(&htim1);
}