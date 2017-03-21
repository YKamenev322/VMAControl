
/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"
#include "tim.h"

#include "gpio.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

TIM_HandleTypeDef htim1;
TIM_HandleTypeDef htim2;
TIM_HandleTypeDef htim8;

/* TIM1 init function */
void MX_TIM1_Init(void)
{
  TIM_SlaveConfigTypeDef sSlaveConfig;
  TIM_MasterConfigTypeDef sMasterConfig;
  TIM_IC_InitTypeDef sConfigIC;

  htim1.Instance = TIM1;
  htim1.Init.Prescaler = 0;
  htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim1.Init.Period = 0;
  htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim1.Init.RepetitionCounter = 0;
  if (HAL_TIM_Base_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }

  if (HAL_TIM_IC_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }

  sSlaveConfig.SlaveMode = TIM_SLAVEMODE_RESET;
  sSlaveConfig.InputTrigger = TIM_TS_TI1F_ED;
  sSlaveConfig.TriggerPolarity = TIM_INPUTCHANNELPOLARITY_RISING;
  sSlaveConfig.TriggerFilter = 15;
  if (HAL_TIM_SlaveConfigSynchronization(&htim1, &sSlaveConfig) != HAL_OK)
  {
    Error_Handler();
  }

  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }

  sConfigIC.ICPolarity = TIM_INPUTCHANNELPOLARITY_FALLING;
  sConfigIC.ICSelection = TIM_ICSELECTION_DIRECTTI;
  sConfigIC.ICPrescaler = TIM_ICPSC_DIV1;
  sConfigIC.ICFilter = 15;
  if (HAL_TIM_IC_ConfigChannel(&htim1, &sConfigIC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }

  if (HAL_TIM_IC_ConfigChannel(&htim1, &sConfigIC, TIM_CHANNEL_2) != HAL_OK)
  {
    Error_Handler();
  }

}


/* TIM2 init function */
void MX_TIM2_Init(void)
{
  TIM_ClockConfigTypeDef sClockSourceConfig;
  TIM_MasterConfigTypeDef sMasterConfig;
  TIM_OC_InitTypeDef sConfigOC;

  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 71;//1MHz
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 20000; //50 Hz
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	
  if (HAL_TIM_PWM_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }

  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 10000;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
	sConfigOC.OCNPolarity  = TIM_OCNPOLARITY_HIGH;
	sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;
  if (HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_3) != HAL_OK)
  {
    Error_Handler();
  }

}

/* TIM8 init function */
void MX_TIM8_Init(void)
{
	  TIM_ClockConfigTypeDef sClockSourceConfig;
  TIM_MasterConfigTypeDef sMasterConfig;
  TIM_OC_InitTypeDef sConfigOC;

  htim8.Instance = TIM8;
  htim8.Init.Prescaler = 71;//1MHz
  htim8.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim8.Init.Period = 20000 - 1; //50 Hz
  htim8.Init.RepetitionCounter = 0;
  htim8.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;

  //sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  //HAL_TIM_ConfigClockSource(&htim8, &sClockSourceConfig);
	
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

  sConfigOC.Pulse = 10000;
	
    /**TIM8 GPIO Configuration    
    PB0     ------> TIM8_CH2N
    PB1     ------> TIM8_CH3N
    PC7     ------> TIM8_CH2
    PC8     ------> TIM8_CH3 
    */		
  if (HAL_TIM_PWM_ConfigChannel(&htim8, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_ConfigChannel(&htim8, &sConfigOC, TIM_CHANNEL_3) != HAL_OK)
  {
    Error_Handler();
  }
	
/*  TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig;
	  
  sBreakDeadTimeConfig.BreakState       = TIM_BREAK_ENABLE;
  sBreakDeadTimeConfig.DeadTime         = 100;
  sBreakDeadTimeConfig.OffStateRunMode  = TIM_OSSR_ENABLE;
  sBreakDeadTimeConfig.OffStateIDLEMode = TIM_OSSI_ENABLE;
  sBreakDeadTimeConfig.LockLevel        = TIM_LOCKLEVEL_1;  
  sBreakDeadTimeConfig.BreakPolarity    = TIM_BREAKPOLARITY_HIGH;
  sBreakDeadTimeConfig.AutomaticOutput  = TIM_AUTOMATICOUTPUT_ENABLE;
*/
  TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig;

  sBreakDeadTimeConfig.BreakState = TIM_BREAK_DISABLE;	
  sBreakDeadTimeConfig.DeadTime = 255;
  sBreakDeadTimeConfig.OffStateRunMode = TIM_OSSR_ENABLE;
  sBreakDeadTimeConfig.OffStateIDLEMode = TIM_OSSI_ENABLE;
  sBreakDeadTimeConfig.LockLevel = TIM_LOCKLEVEL_OFF;
  sBreakDeadTimeConfig.BreakPolarity = TIM_BREAKPOLARITY_HIGH;
  sBreakDeadTimeConfig.AutomaticOutput = TIM_AUTOMATICOUTPUT_ENABLE;
	
	
  if(HAL_TIMEx_ConfigBreakDeadTime(&htim8, &sBreakDeadTimeConfig) != HAL_OK)
  {
    Error_Handler();
  }
	
/*

  sBreakDeadTimeConfig.OffStateRunMode = TIM_OSSR_DISABLE;
  sBreakDeadTimeConfig.OffStateIDLEMode = TIM_OSSI_DISABLE;
  sBreakDeadTimeConfig.LockLevel = TIM_LOCKLEVEL_OFF;
  sBreakDeadTimeConfig.DeadTime = 255;
  sBreakDeadTimeConfig.BreakState = TIM_BREAK_DISABLE;
  sBreakDeadTimeConfig.BreakPolarity = TIM_BREAKPOLARITY_HIGH;
  sBreakDeadTimeConfig.AutomaticOutput = TIM_AUTOMATICOUTPUT_ENABLE;
  if (HAL_TIMEx_ConfigBreakDeadTime(&htim8, &sBreakDeadTimeConfig) != HAL_OK)

*/
}

void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef *tim_baseHandle)
{
  GPIO_InitTypeDef GPIO_InitStruct;
  if(tim_baseHandle->Instance==TIM2)
  {
  /* USER CODE BEGIN TIM1_MspInit 0 */

  /* USER CODE END TIM1_MspInit 0 */
    /* Peripheral clock enable */
    __HAL_RCC_TIM2_CLK_ENABLE();

		/**TIM2 GPIO Configuration    
    PA2     ------> TIM2_CH3 
    */
    GPIO_InitStruct.Pin = GPIO_PIN_2;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    HAL_NVIC_SetPriority(TIM2_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(TIM2_IRQn);

  /* USER CODE BEGIN TIM1_MspInit 1 */

  /* USER CODE END TIM1_MspInit 1 */
  }
	  if(tim_baseHandle->Instance==TIM8)
  {
  /* USER CODE BEGIN TIM8_MspInit 0 */

  /* USER CODE END TIM8_MspInit 0 */
    /* Peripheral clock enable */
    __HAL_RCC_TIM8_CLK_ENABLE();
    /* Peripheral interrupt init */
    //HAL_NVIC_SetPriority(TIM8_UP_IRQn, 0, 0);
    //HAL_NVIC_EnableIRQ(TIM8_UP_IRQn);
    HAL_NVIC_SetPriority(TIM8_CC_IRQn, 0, 15);
    HAL_NVIC_EnableIRQ(TIM8_CC_IRQn);
  /* USER CODE BEGIN TIM8_MspInit 1 */
    /**TIM8 GPIO Configuration    
    PB0     ------> TIM8_CH2N
    PB1     ------> TIM8_CH3N
    PC7     ------> TIM8_CH2
    PC8     ------> TIM8_CH3 
    */
		
		__HAL_RCC_GPIOB_CLK_ENABLE();
		__HAL_RCC_GPIOC_CLK_ENABLE();
			
    GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_7|GPIO_PIN_8;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
  /* USER CODE END TIM8_MspInit 1 */
  }
}


