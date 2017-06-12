#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f1xx_hal.h"
#include "cmsis_os.h"
//#include "i2c.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "adc.h"
#include "filter_sred.h"
#include "vma.h"
#include "dac.h"

/*Для работы с bootloader'ом необходимо изменить значение VECT_TAB_OFFSET
соответствующее значению в бут прошивке, и изменить настройки Target
Для включения ассертов раскомментить USE_FULL_ASSERT и configASSERT для РТОС
*/ 
///////test/////
extern uint16_t testTIM2ARR;
////////////////
extern uint8_t   	RS485_Address;

/* Variable containing ADC conversions results */
__IO uint16_t   aADCxConvertedValues[ADCCONVERTEDVALUES_BUFFER_SIZE];
extern __IO ITStatus AcpReady;

/* Variables for ADC conversions results computation to physical values */
uint16_t   uhADCChannelToDAC_mVolt = 0;
uint16_t   uhVrefInt_mVolt = 0;
int32_t   wTemperature_DegreeCelsius = 0;
          
/* Variable to report ADC sequencer status */
uint8_t         ubSequenceCompleted = RESET;     /* Set when all ranks of the sequence have been converted */
uint16_t ADCFilteredValues[ADCCONVERTEDVALUES_BUFFER_SIZE];
uint16_t ADCNullValues[ADCCONVERTEDVALUES_BUFFER_SIZE] = {0};
uint32_t adc_add = 0;
uint32_t adc_vma = 0;
FILTER_REG F[ADCCONVERTEDVALUES_BUFFER_SIZE];
uint16_t buf1[COUNT_FILTER], buf2[COUNT_FILTER], buf3[COUNT_FILTER], buf4[COUNT_FILTER];
/* USER CODE END PV */
DRIVER Vma;
DRIVER Add;
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
		
	bkp_enable();

	MX_USART_UART_Init();
	HAL_UART_MspInit(&huart);
	receive(CMD_NUBM_BYTES, 0);
	//HAL_GPIO_WritePin(USARTx_RTS_GPIO_PORT, USARTx_RTS_PIN, GPIO_PIN_RESET);//RTS pin low(ReadyToSend)
	
	F[ADC1_NumOfChannel].Val = 0;
	F[ADC2_NumOfChannel].Val = 0;
	F[ADC3_NumOfChannel].Val = 0;
	F[ADC4_NumOfChannel].Val = 0;
	F[ADCTemp_NumOfChannel].Val = 0;
	
  MX_ADC1_Init();
	HAL_ADC_MspInit(&hadc1);
	/*TIM8*/

	//MX_TIM8_Init();//ADD_Driver_timer
/*	
	HAL_TIM_PWM_Start_IT(&htim8, TIM_CHANNEL_1);
  HAL_TIMEx_PWMN_Start_IT(&htim8, TIM_CHANNEL_1);
	
	HAL_TIM_PWM_Start_IT(&htim8, TIM_CHANNEL_2);
  HAL_TIMEx_PWMN_Start_IT(&htim8, TIM_CHANNEL_2);

	HAL_TIM_PWM_Start_IT(&htim8, TIM_CHANNEL_3);
  HAL_TIMEx_PWMN_Start_IT(&htim8, TIM_CHANNEL_3);
*/


	DRIVER_Init(&Vma, VMA);
	#if !defined (SEMENUK_DRIVER)
	DRIVER_Start(&Vma);
	#endif
	
	DRIVER_Init(&Add, ADD);
	DRIVER_Start(&Add);
	//	Запускаю во freertos.c testTask
//  if (HAL_ADCEx_Calibration_Start(&hadc1) != HAL_OK)
//  {
//    Error_Handler();
//  }
//	
//  if (HAL_ADC_Start_DMA(&hadc1,
//                        (uint32_t *)aADCxConvertedValues,
//                        ADCCONVERTEDVALUES_BUFFER_SIZE
//                       ) != HAL_OK)
//  {
//    Error_Handler();
//  }

//TEST	
#if !defined(SEMENUK_DRIVER)	
  DAC_Init();
  //##-3- Set DAC Channel1 DHR register ######################################
  if (HAL_DAC_SetValue(&DacHandle, DACx_CHANNEL, DAC_ALIGN_12B_R, 4095) != HAL_OK)
  {
    // Setting value Error 
    Error_Handler();
  }

  //##-4- Enable DAC Channel1 ################################################
  if (HAL_DAC_Start(&DacHandle, DACx_CHANNEL) != HAL_OK)
  {
    // Start Error 
    Error_Handler();
  }
#endif
//TEST
	
  osKernelStart();
  
  while (1)
  {

  }

}


void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  if (htim->Instance == TIM4) {
    HAL_IncTick();
  }
#if !defined(SEMENUK_DRIVER)  
	/* HALLSENSOR Shifting */
  if (htim->Instance == TIM2) {
    VMA_HallSensorShift(&Vma);
		TIM2->ARR = testTIM2ARR;
  }
#endif
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *AdcHandle)
{
	static uint8_t local = 0;
	static bool blocal = 0;
	
  /* Report to main program that ADC sequencer has reached its end */
	ubSequenceCompleted = SET;
	AcpReady = SET;
	//ADC3 add-driver current
	ADCFilteredValues[ADC3_NumOfChannel]=filter_sred(aADCxConvertedValues[ADC3_NumOfChannel],buf3,&F[ADC3_NumOfChannel]);
	//ADC4 vma-driver current
	ADCFilteredValues[ADC4_NumOfChannel]=filter_sred(aADCxConvertedValues[ADC4_NumOfChannel],buf4,&F[ADC4_NumOfChannel]);

	/*FOR ACP NULL Values*/
	if (local == COUNT_FILTER)//ищем нуль после COUNT_FILTER считываний
	{
		ADCNullValues[ADC3_NumOfChannel] = ADCFilteredValues[ADC3_NumOfChannel];
		ADCNullValues[ADC4_NumOfChannel] = ADCFilteredValues[ADC4_NumOfChannel];
		blocal = 1;
	}
	local++;
	if (blocal == 1)//если нашли нуль
	{
		local = 0;
		adc_vma = ((ADCFilteredValues[ADC4_NumOfChannel] - ADCNullValues[ADC4_NumOfChannel]) * VMA_MAX_CURRENT)/
											(RANGE_12BITS - ADCNullValues[ADC4_NumOfChannel]);
		adc_add = ((ADCFilteredValues[ADC3_NumOfChannel] - ADCNullValues[ADC3_NumOfChannel]) * ADD_MAX_CURRENT)/
												(RANGE_12BITS - ADCNullValues[ADC3_NumOfChannel]);
		if (adc_vma > ADD_MAX_CURRENT ) adc_vma = 0;
		if (adc_add > VMA_MAX_CURRENT ) adc_add = 0;
	}
	/*_____________*/
		
}
void tim_pwm_callback_add()
{
//if (ADCFilteredValues[ADC3_NumOfChannel] > MAX_ADC3_VALUE)
	if (adc_add > ADD_MAX_CURRENT_VALUE)
						{
							//needTest
							DRIVER_SetPwmLow(&Add);
						}
						else 
						{
							DRIVER_SetPwm(&Add);
						}	 
}
void tim_pwm_callback_vma()
{
	//if (ADCFilteredValues[ADC4_NumOfChannel] > MAX_ADC4_VALUE)
	if (adc_vma > VMA_MAX_CURRENT_VALUE)
	{
		DRIVER_SetPwmLow(&Vma);//needTest
	}
	else 
	{
		DRIVER_SetPwm(&Vma);
	}
}
void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim)
{
	
    if (htim->Instance == TIMx_ADD_DRIVER)//
    {
        switch (htim->Channel)
        {
        case HAL_TIM_ACTIVE_CHANNEL_1:
            break;
        case HAL_TIM_ACTIVE_CHANNEL_2:
						if (Add.flagDirection == FORWARD)
						{
							tim_pwm_callback_add();
							TIMx_ADD_DRIVER->CCR2 = Add.PWMCurrent;      
						}
						else
							TIMx_ADD_DRIVER->CCR2 = 0;      
            break;
        case HAL_TIM_ACTIVE_CHANNEL_3:
						if (Add.flagDirection == BACKWARD)
						{
							tim_pwm_callback_add();
							TIMx_ADD_DRIVER->CCR3 = Add.PWMCurrent; 
						}
						else
							TIMx_ADD_DRIVER->CCR3 = 0;
            break;
        case HAL_TIM_ACTIVE_CHANNEL_4:    // Pin 
            TIMx_ADD_DRIVER->CCR4 = 0;
            break;
        case HAL_TIM_ACTIVE_CHANNEL_CLEARED:
            break;
        }
    }
#if !defined (SEMENUK_DRIVER)		
    if (htim->Instance == TIMx_VMA_DRIVER)//tim1
    {
        switch (htim->Channel)
        {
        case HAL_TIM_ACTIVE_CHANNEL_1:
					
						tim_pwm_callback_vma();
						TIMx_VMA_DRIVER->CCR1 = Vma.PWMCurrent;
				
            break;
        case HAL_TIM_ACTIVE_CHANNEL_2:    
            break;
        case HAL_TIM_ACTIVE_CHANNEL_3:    
            break;
        case HAL_TIM_ACTIVE_CHANNEL_4:   
            break;
        case HAL_TIM_ACTIVE_CHANNEL_CLEARED:
            break;
        }
    }
#endif
}

void HAL_ADC_ConvHalfCpltCallback(ADC_HandleTypeDef* hadc)
{

}

void HAL_ADC_ErrorCallback(ADC_HandleTypeDef *hadc)
{
  Error_Handler();
}

void Error_Handler(void)
{
  while(1) 
  {
  }
}


#ifdef USE_FULL_ASSERT

void assert_failed(uint8_t* file, uint32_t line)
{
}

#endif

