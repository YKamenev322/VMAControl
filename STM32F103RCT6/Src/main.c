#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f1xx_hal.h"
#include "cmsis_os.h"
//#include "i2c.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "adc.h"
/*Для работы с bootloader'ом необходимо изменить значение VECT_TAB_OFFSET
соответствующее значению в бут прошивке, и изменить настройки Target
*/ 
extern uint16_t   PWMRegs[3];
extern uint8_t   	RS485_Address;

/* Variable containing ADC conversions results */
__IO uint16_t   aADCxConvertedValues[ADCCONVERTEDVALUES_BUFFER_SIZE];


/* Variables for ADC conversions results computation to physical values */
uint16_t   uhADCChannelToDAC_mVolt = 0;
uint16_t   uhVrefInt_mVolt = 0;
int32_t   wTemperature_DegreeCelsius = 0;
          
/* Variable to report ADC sequencer status */
uint8_t         ubSequenceCompleted = RESET;     /* Set when all ranks of the sequence have been converted */
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
extern void SystemClock_Config(void);
void Error_Handler(void);
void MX_FREERTOS_Init(void);

int main(void)
{

  HAL_Init();

  SystemClock_Config();
	
	/* Config RTOS (tasks, queues, semaphores,...) */
  MX_FREERTOS_Init();
	
  /* Initialize all configured peripherals */
	
  MX_GPIO_Init();
	RS485_ADDR = MX_GPIO_Init_Address();
	
//  MX_RTC_Init();
	
//  MX_I2C1_Init(); //Убрал из билда i2c_SDP600.c, eeprom.c, i2c.c, comment i2c.h
	
  //MX_TIM1_Init();
  bkp_enable();

	MX_USART1_UART_Init();
	HAL_UART_MspInit(&huart);
	//HAL_GPIO_WritePin(USARTx_RTS_GPIO_PORT, USARTx_RTS_PIN, GPIO_PIN_RESET);//RTS pin low(ReadyToSend)
	
  MX_ADC1_Init();
	HAL_ADC_MspInit(&hadc1);
	
	MX_TIM8_Init();
  /* USER CODE BEGIN 2 */
	
	HAL_TIM_PWM_Start_IT(&htim8, TIM_CHANNEL_2);
  HAL_TIMEx_PWMN_Start_IT(&htim8, TIM_CHANNEL_2);

	HAL_TIM_PWM_Start_IT(&htim8, TIM_CHANNEL_3);
  HAL_TIMEx_PWMN_Start_IT(&htim8, TIM_CHANNEL_3);
	
	/* Run the ADC calibration */
  
  if (HAL_ADCEx_Calibration_Start(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }
	
  if (HAL_ADC_Start_DMA(&hadc1,
                        (uint32_t *)aADCxConvertedValues,
                        ADCCONVERTEDVALUES_BUFFER_SIZE
                       ) != HAL_OK)
  {
    Error_Handler();
  }	
	
  osKernelStart();
  
  while (1)
  {
		//dbg_off();
		//__disable_irq();
		//dbg_toggle();
		//HAL_Delay(2000);
  }

}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  if (htim->Instance == TIM4) {
    HAL_IncTick();
  }
}


void Error_Handler(void)
{
  while(1) 
  {
  }
}
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *AdcHandle)
{
  /* Report to main program that ADC sequencer has reached its end */
	ubSequenceCompleted = SET;
}

/**
  * @brief  Conversion DMA half-transfer callback in non blocking mode 
  * @param  hadc: ADC handle
  * @retval None
  */
void HAL_ADC_ConvHalfCpltCallback(ADC_HandleTypeDef* hadc)
{

}

void HAL_ADC_ErrorCallback(ADC_HandleTypeDef *hadc)
{
  /* In case of ADC error, call main error handler */
  Error_Handler();
}


void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim)
{
    if (htim == &htim8)
    {
        switch (htim->Channel)
        {
        case HAL_TIM_ACTIVE_CHANNEL_1:    // Pin 
            TIM8->CCR1 = 0; 
            break;
        case HAL_TIM_ACTIVE_CHANNEL_2:    // Pin 
            TIM8->CCR2 = PWMRegs[1];
            break;
        case HAL_TIM_ACTIVE_CHANNEL_3:    // Pin  
            TIM8->CCR3 = PWMRegs[2];
            break;
        case HAL_TIM_ACTIVE_CHANNEL_4:    // Pin 
            TIM8->CCR4 = 0;
            break;
        case HAL_TIM_ACTIVE_CHANNEL_CLEARED:
            break;
        }
    }
}



#ifdef USE_FULL_ASSERT

void assert_failed(uint8_t* file, uint32_t line)
{
}

#endif

