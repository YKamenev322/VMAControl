
/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"
#include "tim.h"
#include "main.h"

#include "gpio.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

TIM_HandleTypeDef htim1;
TIM_HandleTypeDef htim2;//for ADD on Semenuk and for VMA on my
TIM_HandleTypeDef htim8;//for ADD on my

/* TIM2 init function */
void MX_TIM2_Init(void)
{
  TIM_ClockConfigTypeDef sClockSourceConfig;
  TIM_MasterConfigTypeDef sMasterConfig;
  TIM_OC_InitTypeDef sConfigOC;

  htim2.Instance = TIM2;
  htim2.Init.Prescaler = TIMx_VMA_DRIVER_MC33035_HALLSENSOR_PSC;//1MHz
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = TIMx_VMA_DRIVER_MC33035_HALLSENSOR_PERIOD_MAX; //15 Hz
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	
  if (HAL_TIM_PWM_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
}
void MX_TIM8_Init()
{
	TIM_ClockConfigTypeDef sClockSourceConfig;
  TIM_MasterConfigTypeDef sMasterConfig;
  TIM_OC_InitTypeDef sConfigOC;
	
  htim8.Instance = TIMx_ADD_DRIVER;
	
  htim8.Init.Prescaler = TIMx_ADD_DRIVER_PSC;
  htim8.Init.Period = TIMx_ADD_DRIVER_PERIOD;

  htim8.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim8.Init.RepetitionCounter = 0;
  htim8.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;

  if (HAL_TIM_PWM_Init(&htim8) != HAL_OK)
  {
    Error_Handler();
  }

  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
	sConfigOC.OCNPolarity  = TIM_OCNPOLARITY_HIGH;
	sConfigOC.OCIdleState = TIM_OCIDLESTATE_SET;
	sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
	
  sConfigOC.Pulse = 0;
		
  if (HAL_TIM_PWM_ConfigChannel(&htim8, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_ConfigChannel(&htim8, &sConfigOC, TIM_CHANNEL_3) != HAL_OK)
  {
    Error_Handler();
	}
  TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig;

  sBreakDeadTimeConfig.BreakState = TIM_BREAK_DISABLE;	
  sBreakDeadTimeConfig.DeadTime = ADD_DEADTIME;
  sBreakDeadTimeConfig.OffStateRunMode = TIM_OSSR_ENABLE;
  sBreakDeadTimeConfig.OffStateIDLEMode = TIM_OSSI_ENABLE;
  sBreakDeadTimeConfig.LockLevel = TIM_LOCKLEVEL_OFF;
  sBreakDeadTimeConfig.BreakPolarity = TIM_BREAKPOLARITY_HIGH;
  sBreakDeadTimeConfig.AutomaticOutput = TIM_AUTOMATICOUTPUT_ENABLE;
	
	
  if(HAL_TIMEx_ConfigBreakDeadTime(&htim8, &sBreakDeadTimeConfig) != HAL_OK)
  {
    Error_Handler();
  }
}
/* TIM1 init function */
void MX_TIM1_Init(void)
{
	TIM_ClockConfigTypeDef sClockSourceConfig;
  TIM_MasterConfigTypeDef sMasterConfig;
  TIM_OC_InitTypeDef sConfigOC;
	//test ESC30A
#if !defined (SEMENUK_DRIVER)
	#if defined(VMADRIVER_ESC30)
	htim1.Instance = TIMx_VMA_DRIVER;
  htim1.Init.Prescaler = TIMx_VMA_DRIVER_ESC30_PSC;//1MHz
  htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim1.Init.Period = TIMx_VMA_DRIVER_ESC30_PERIOD; //50 Hz
  htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	
  if (HAL_TIM_PWM_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }

  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = ESC30_PWM_NULL;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
	sConfigOC.OCNPolarity  = TIM_OCNPOLARITY_HIGH;
	sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;
  if (HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
	#endif
	
	#if defined(VMADRIVER_MC33035)//TODO !!!!!!!!!!!!
//  htim8.Instance = TIMx_VMA_DRIVER;
//  htim8.Init.Prescaler = TIMx_VMA_DRIVER_MC33035_PSC;
//  htim8.Init.Period = TIMx_VMA_DRIVER_MC33035_PERIOD;
//	
//  htim8.Init.CounterMode = TIM_COUNTERMODE_UP;
//  htim8.Init.RepetitionCounter = 0;
//  htim8.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;

//  if (HAL_TIM_PWM_Init(&htim8) != HAL_OK)
//  {
//    Error_Handler();
//  }

//  sConfigOC.OCMode = TIM_OCMODE_PWM1;
//  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
//	sConfigOC.OCNPolarity  = TIM_OCNPOLARITY_HIGH;
//	sConfigOC.OCIdleState = TIM_OCIDLESTATE_SET;
//	sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;
//  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;

//  sConfigOC.Pulse = MC33035_PWM_MIN;
//		
//  if (HAL_TIM_PWM_ConfigChannel(&htim8, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
//  {
//    Error_Handler();
//  }
	#endif
#else
	
  htim1.Instance = TIMx_ADD_DRIVER;
	
  htim1.Init.Prescaler = TIMx_ADD_DRIVER_PSC;
  htim1.Init.Period = TIMx_ADD_DRIVER_PERIOD;

  htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim1.Init.RepetitionCounter = 0;
  htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;

  if (HAL_TIM_PWM_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }

  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
	sConfigOC.OCNPolarity  = TIM_OCNPOLARITY_HIGH;
	sConfigOC.OCIdleState = TIM_OCIDLESTATE_SET;
	sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
	
  sConfigOC.Pulse = 0;
		
  if (HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_3) != HAL_OK)
  {
    Error_Handler();
	}
  TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig;

  sBreakDeadTimeConfig.BreakState = TIM_BREAK_DISABLE;	
  sBreakDeadTimeConfig.DeadTime = ADD_DEADTIME;
  sBreakDeadTimeConfig.OffStateRunMode = TIM_OSSR_ENABLE;
  sBreakDeadTimeConfig.OffStateIDLEMode = TIM_OSSI_ENABLE;
  sBreakDeadTimeConfig.LockLevel = TIM_LOCKLEVEL_OFF;
  sBreakDeadTimeConfig.BreakPolarity = TIM_BREAKPOLARITY_HIGH;
  sBreakDeadTimeConfig.AutomaticOutput = TIM_AUTOMATICOUTPUT_ENABLE;
	
	
  if(HAL_TIMEx_ConfigBreakDeadTime(&htim1, &sBreakDeadTimeConfig) != HAL_OK)
  {
    Error_Handler();
  }
#endif
	
}


void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef *tim_baseHandle)
{
  GPIO_InitTypeDef GPIO_InitStruct;
	
  if(tim_baseHandle->Instance==TIM2)//for VMA HallSensor
  {
    __HAL_RCC_TIM2_CLK_ENABLE();

    HAL_NVIC_SetPriority(TIM2_IRQn, 10, 0);
    HAL_NVIC_EnableIRQ(TIM2_IRQn);
  }
#if !defined (SEMENUK_DRIVER)	
	if(tim_baseHandle->Instance==TIMx_VMA_DRIVER) //timer for VMA driver
  {
		__HAL_RCC_GPIOA_CLK_ENABLE();
		__HAL_RCC_GPIOB_CLK_ENABLE();
		__HAL_RCC_GPIOC_CLK_ENABLE();
		__HAL_RCC_GPIOD_CLK_ENABLE();
		
    TIMx_VMA_CLK_ENABLE;
		
    /* Peripheral interrupt init */
    HAL_NVIC_SetPriority(TIMx_VMA_CC_IRQn, 0, 15);
    HAL_NVIC_EnableIRQ(TIMx_VMA_CC_IRQn);

    GPIO_InitStruct.Pin = TIMx_VMA_DRIVER_CH1;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(TIMx_VMA_DRIVER_CH1_PORT, &GPIO_InitStruct);
  }
#endif	
	if(tim_baseHandle->Instance==TIMx_ADD_DRIVER)// timer for ADD driver 
  {
		__HAL_RCC_GPIOA_CLK_ENABLE();
		__HAL_RCC_GPIOB_CLK_ENABLE();
		__HAL_RCC_GPIOC_CLK_ENABLE();
		__HAL_RCC_GPIOD_CLK_ENABLE();
		
		TIMx_ADD_CLK_ENABLE;

    HAL_NVIC_SetPriority(TIMx_ADD_CC_IRQn, 1, 0);
    HAL_NVIC_EnableIRQ(TIMx_ADD_CC_IRQn);

    GPIO_InitStruct.Pin = TIMx_ADD_DRIVER_CH1;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(TIMx_ADD_DRIVER_CH1_PORT, &GPIO_InitStruct);
		
    GPIO_InitStruct.Pin = TIMx_ADD_DRIVER_CH2;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(TIMx_ADD_DRIVER_CH2_PORT, &GPIO_InitStruct);
		
    GPIO_InitStruct.Pin = TIMx_ADD_DRIVER_CH1N;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(TIMx_ADD_DRIVER_CH1N_PORT, &GPIO_InitStruct);
		
    GPIO_InitStruct.Pin = TIMx_ADD_DRIVER_CH2N;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(TIMx_ADD_DRIVER_CH2N_PORT, &GPIO_InitStruct);

//remapping of TIM1 alternate function channels 1 to 4, 1N to 3N, external trigger (ETR) and Break input (BKIN)
//Partial remap (ETR/PA12, CH1/PA8, CH2/PA9,  CH3/PA10, CH4/PA11, BKIN/PA6,  CH1N/PA7,  CH2N/PB0,  CH3N/PB1)
	#if defined (SEMENUK_DRIVER)
		TIMx_ADD_REMAP_PARTIAL;
	#endif
	}
/*		
#if defined (VMADRIVER_ESC30)
		//config PA8 - TMI1_CH1
		__HAL_RCC_GPIOA_CLK_ENABLE();
		
		GPIO_InitStruct.Pin = GPIO_PIN_8;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
#endif
#if defined (VMADRIVER_MC33035)
		//config PA8 - TMI1_CH1
		__HAL_RCC_GPIOA_CLK_ENABLE();
		 
		GPIO_InitStruct.Pin = GPIO_PIN_8;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
#endif			
		/*
    GPIO_InitStruct.Pin = GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
		
    GPIO_InitStruct.Pin = GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
		*/
//  }
}


