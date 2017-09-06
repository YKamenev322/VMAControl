
/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"

/* USER CODE BEGIN Includes */     

#include <stdbool.h>
#include "gpio.h"
#include "eeprom.h"
#include "usart.h"
#include "adc.h"
#include "flash.h"
#include "tim.h"
#include "filter_sred.h"
#include "vma.h"


/* USER CODE END Includes */

/* ThreadId Handles*/
osThreadId testTaskHandle;
osThreadId uartTaskHandle;
osThreadId acpTaskHandle;
osThreadId ESCTaskHandle;

/* Uart Vars */
extern __IO ITStatus UartReady;

/* ADC Vars*/
extern ADC_HandleTypeDef hadc1;
extern __IO uint16_t   aADCxConvertedValues[ADCCONVERTEDVALUES_BUFFER_SIZE];
extern uint16_t   uhADCChannelToDAC_mVolt;
extern uint16_t   uhVrefInt_mVolt;
extern int32_t    wTemperature_DegreeCelsius;  
extern uint8_t    ubSequenceCompleted;     /* Set when all ranks of the sequence have been converted */

extern __IO ITStatus AcpReady;

extern uint16_t ADCFilteredValues[ADCCONVERTEDVALUES_BUFFER_SIZE];
extern uint16_t ADCNullValues[ADCCONVERTEDVALUES_BUFFER_SIZE];
extern uint32_t adc_add;
extern uint32_t adc_vma;
extern FILTER_REG F[ADCCONVERTEDVALUES_BUFFER_SIZE];
extern uint16_t buf1[COUNT_FILTER], buf2[COUNT_FILTER], buf3[COUNT_FILTER], buf4[COUNT_FILTER];

extern DRIVER Vma;
extern DRIVER Add;

/* Function prototypes -------------------------------------------------------*/
//void i2cTask(void const * argument);
void testTask(void const * argument);
void uartTask(void const * argument);
void uartTimerCallback(xTimerHandle xTimer);
void acpTask(void const * argument);
//void ESCTask(void const * argument);
void ESCTask(xTimerHandle xTimer);
void ESCReset(xTimerHandle xTimer);
void UARTTimeoutCallback(xTimerHandle xTimer);
///////////TEEEEEST///////////
uint8_t test = 0;
uint16_t testTIM2ARR = TIMx_VMA_DRIVER_MC33035_HALLSENSOR_PERIOD_MAX;
////////////////////////////////
SemaphoreHandle_t xSemaphore;
SemaphoreHandle_t bSemaphoreModbusTask;
SemaphoreHandle_t bUARTSemaphore;

TimerHandle_t UARTTimer;
TimerHandle_t VMATimer;
TimerHandle_t VMAResetTimer;
TimerHandle_t UartTimeoutTimer;

void MX_FREERTOS_Init(void) {

	//xSemaphore = xSemaphoreCreateMutex();
	bSemaphoreModbusTask = xSemaphoreCreateBinary();
	bUARTSemaphore = xSemaphoreCreateBinary();

  /* USER CODE BEGIN RTOS_THREADS */

/**/
  osThreadDef(testTaskName, testTask, osPriorityNormal, 0, 128);
  testTaskHandle = osThreadCreate(osThread(testTaskName), NULL);
/**/

  osThreadDef(acpTaskName, acpTask, osPriorityLow, 0, 128);
  acpTaskHandle = osThreadCreate(osThread(acpTaskName), NULL);

/*
	osThreadDef(uartTaskName, uartTask, osPriorityRealtime, 0, 128);
  uartTaskHandle = osThreadCreate(osThread(uartTaskName), NULL);
*/
	UARTTimer = xTimerCreate("timer", 3/portTICK_RATE_MS, pdFALSE, 0, uartTimerCallback);
	//xTimerReset(UARTTimer, 0);
	VMATimer = xTimerCreate("VMAtimer", 1000/portTICK_RATE_MS, pdFALSE, 0, ESCTask);
	xTimerStart(VMATimer, 0);
	VMAResetTimer = xTimerCreate("VMAResetTimer", 20/portTICK_RATE_MS, pdFALSE, 0, ESCReset);
	UartTimeoutTimer = xTimerCreate("UartTimeout", 2000/portTICK_RATE_MS, pdFALSE, 0, UARTTimeoutCallback);
/*	
	osThreadDef(ESCTaskName, ESCTask, osPriorityLow, 0, 128);
  ESCTaskHandle = osThreadCreate(osThread(ESCTaskName), NULL);
*/	
}

/*Задержка при включении ESC контроллера*/
void ESCTask(xTimerHandle xTimer)
{
	DRIVER_PwmEnable(&Vma);
}

void ESCReset(xTimerHandle xTimer)
{
	HAL_GPIO_WritePin(PORT_RESET, RESET_PIN, GPIO_PIN_RESET);
	osDelay(5);
	HAL_GPIO_WritePin(PORT_RESET, RESET_PIN, GPIO_PIN_SET);
}

void acpTask(void const * argument)
{
	uint32_t prv_time = osKernelSysTick();
	for(;;) 
	{
    //HAL_ADC_Start(&hadc1); 
    // Wait for conversion completion before conditional check hereafter 
    //HAL_ADC_PollForConversion(&hadc1, 1);
    //test
		if (ubSequenceCompleted == SET)
    {     
      uhADCChannelToDAC_mVolt    = COMPUTATION_DIGITAL_12BITS_TO_VOLTAGE(aADCxConvertedValues[ADC1_NumOfChannel]);
      uhVrefInt_mVolt            = COMPUTATION_DIGITAL_12BITS_TO_VOLTAGE(aADCxConvertedValues[ADC2_NumOfChannel]);
      wTemperature_DegreeCelsius = COMPUTATION_TEMPERATURE_STD_PARAMS(aADCxConvertedValues[ADCTemp_NumOfChannel]);

      ubSequenceCompleted = RESET;
    }
		if (AcpReady == SET) 
		{
			AcpReady = RESET;
			//ADC1 potenciometer R20
		  ADCFilteredValues[ADC1_NumOfChannel]=filter_sred(aADCxConvertedValues[ADC1_NumOfChannel],buf1,&F[ADC1_NumOfChannel]);
			//ADC2 potenciometer R18
		  ADCFilteredValues[ADC2_NumOfChannel]=filter_sred(aADCxConvertedValues[ADC2_NumOfChannel],buf2,&F[ADC2_NumOfChannel]);
			//ADC3 add-driver current
				//ADCFilteredValues[ADC3_NumOfChannel]=filter_sred(aADCxConvertedValues[ADC3_NumOfChannel],&F[ADC3_NumOfChannel]);
			//ADC4 vma-driver current
				//ADCFilteredValues[ADC4_NumOfChannel]=filter_sred(aADCxConvertedValues[ADC4_NumOfChannel],&F[ADC4_NumOfChannel]);
		}		
		osDelayUntil(&prv_time, 10);
	}
}

void testTask(void const * argument)
{
	uint32_t prv_time = osKernelSysTick();
	uint8_t testlocal = 0;
	for(;;) {    
		dbg_toggle();
		//test
		/*
		testTIM2ARR = TIMx_VMA_DRIVER_MC33035_HALLSENSOR_PERIOD_MAX - 
									(test * (TIMx_VMA_DRIVER_MC33035_HALLSENSOR_PERIOD_MAX - 
									TIMx_VMA_DRIVER_MC33035_HALLSENSOR_PERIOD_MIN)) / 255;
		*/
		//VMA_SetVelocity(&Vma, 127);
		//xTimerReset(UartTimeoutTimer,0);
		/*
		switch (testlocal){
			case 0:
				{
			Vma.flagBrake = RESET;
			Add.flagBrake = RESET;
					testlocal = 1;
					break;
			}
			case 1:{
			Vma.flagBrake = SET;
			Add.flagBrake = RESET;
					testlocal = 2;
					break;
			}
			case 2:{
			Vma.flagBrake = RESET;
			Add.flagBrake = SET;
					testlocal = 3;
					break;
			}
			case 3:{
			Vma.flagBrake = SET;
			Add.flagBrake = SET;
					testlocal = 0;
					break;
			}
				default:
					testlocal = 0;
					break;
		}
		*/
		//ждем 1 сек для установки напряжений микросхем и запуска АЦП
		testlocal++;
		switch (testlocal){
			case 1:
				break;
			case 2:
			{
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
				
				break;
			}
			default:
				testlocal = 3;
				break;
		}

		osDelayUntil(&prv_time, 1000);
	}
}

void uartTimerCallback(xTimerHandle xTimer)
{
	static portBASE_TYPE xHigherPriorityTaskWoken;
	xHigherPriorityTaskWoken = pdFALSE;
	
		if (UartReady == SET)
			{
				UartReady = RESET;
				
				switch (check_request()) {
				
				case BTL_CMD_RESTART:
						taskENTER_CRITICAL();
//				
//#if !defined(SEMENUK_DRIVER)
//						HAL_TIM_PWM_Stop_IT(&htim8, TIM_CHANNEL_2);
//						HAL_TIMEx_PWMN_Stop_IT(&htim8, TIM_CHANNEL_2);

//						HAL_TIM_PWM_Stop_IT(&htim8, TIM_CHANNEL_3);
//						HAL_TIMEx_PWMN_Stop_IT(&htim8, TIM_CHANNEL_3);
//	
//#else
//						HAL_TIM_PWM_Stop_IT(&htim1, TIM_CHANNEL_2);
//						HAL_TIMEx_PWMN_Stop_IT(&htim1, TIM_CHANNEL_2);

//						HAL_TIM_PWM_Stop_IT(&htim1, TIM_CHANNEL_3);
//						HAL_TIMEx_PWMN_Stop_IT(&htim1, TIM_CHANNEL_3);
//#endif
//						HAL_Delay(100);
				
						goToBootloader();
						break;
				case BTL_CMD_NO_CMD:
						receive(CMD_NUBM_BYTES, 0);
						break;
				default:
						//done_request();
						DRIVER_SetVelocity(&Vma, GetData16() >> 8);
//#if defined(SEMENUK_DRIVER)
						DRIVER_SetVelocity(&Add, GetData16());
//#endif
						//test
						test = GetData16();
						testTIM2ARR = TIMx_VMA_DRIVER_MC33035_HALLSENSOR_PERIOD_MAX - 
													(test * (TIMx_VMA_DRIVER_MC33035_HALLSENSOR_PERIOD_MAX - 
													TIMx_VMA_DRIVER_MC33035_HALLSENSOR_PERIOD_MIN)) / 255;
						//testTIM2ARR = ((test - 0) * TIMx_VMA_DRIVER_MC33035_HALLSENSOR_PERIOD) / (255 - 0);
						//PWMRegs[0] = (PWMPulse/PWMPulseBase) * (GetData16() >> 8);
						//PWMRegs[1] = (PWMPulse/PWMPulseBase) * (0x00FF & GetData16());
						uint8_t flag = (Add.flagBrake << 1) | Vma.flagBrake;

//						uint32_t adc_vma = ((ADCFilteredValues[ADC4_NumOfChannel] - ADCNullValues[ADC4_NumOfChannel]) * 
//																VDD_APPLI * VMA_MAX_CURRENT) / RANGE_12BITS;
//						uint32_t adc_add = ((ADCFilteredValues[ADC3_NumOfChannel] - ADCNullValues[ADC3_NumOfChannel]) * 
//																VDD_APPLI * ADD_MAX_CURRENT) / RANGE_12BITS;
//						if (adc_vma > ADD_MAX_CURRENT * 1000) adc_vma = 0;
//						if (adc_add > VMA_MAX_CURRENT * 1000) adc_add = 0;
						make_response((uint16_t)(adc_vma), 
													(uint16_t)(adc_add), 
													Vma.velocity,//GetData16() >> 8, 
													Add.velocity,//GetData16(), 
													flag);
						receive(CMD_NUBM_BYTES, 0);
						send_response();
						break;
				}
			}
			else
			{
				clean_counterRx();
				clean_RxBuffer();
			}
			
	xTimerReset(UartTimeoutTimer,0);
}

void UARTTimeoutCallback(xTimerHandle xTimer)
{
	DRIVER_Stop(&Vma);
//#if defined(SEMENUK_DRIVER)
	DRIVER_Stop(&Add);
//#endif
}

/* USER CODE BEGIN Application */
/*
void i2cTask (void const * argument)
{
	count_h = I2C_EE_Read(COUNT_H_EE_ADDR);
	osDelay(5);
	count_c = I2C_EE_Read(COUNT_C_EE_ADDR);
	osDelay(5);
	uint32_t prv_time = osKernelSysTick();
	for(;;) {

		if (needsavecount_hFlg == TRUE) {
			 //Start_DMA1_Channel7();
			 I2C_EE_Write(count_h, COUNT_H_EE_ADDR);
			 needsavecount_hFlg = FALSE;
			 osDelay(5);
		}
		if (needsavecount_cFlg == TRUE) {
			 //Start_DMA1_Channel7();
			 I2C_EE_Write(count_c, COUNT_C_EE_ADDR);
			 needsavecount_cFlg = FALSE;
			 osDelay(5);
		}
		
		int16_t temp_sdp600;
		etError differror = SDP600_ReadPreassure(&temp_sdp600);
		if ( differror == NO_ERROR) {
			//xSemaphoreTake(xSemaphore, portMAX_DELAY);
			difPressure = temp_sdp600;
			//xSemaphoreGive(xSemaphore);
		}		

		osDelayUntil(&prv_time, 100);
	}
}
*/

/*
void uartTask(void const * argument)
{
	uint32_t prv_time = osKernelSysTick();
	receive(CMD_NUBM_BYTES, 0);
	
	for(;;) {
		//check_timer();
		xSemaphoreTake(bUARTSemaphore, portMAX_DELAY);
		osDelay(2);
		prv_time = osKernelSysTick();
		//osDelay(1);
		if (UartReady == SET)
			{
				UartReady = RESET;
				
				switch (check_request()) {
				
				case BTL_CMD_RESTART:
						taskENTER_CRITICAL();
						goToBootloader();
						break;
				case BTL_CMD_NO_CMD:
						receive(CMD_NUBM_BYTES, 0);
						break;
				default:
						//done_request();
						PWMRegs[0] = (PWMPulse/PWMPulseBase) * (GetData16() >> 8);
						PWMRegs[1] = (PWMPulse/PWMPulseBase) * (0x00FF & GetData16());
						make_response();
						receive(CMD_NUBM_BYTES, 0);
						osDelayUntil(&prv_time,1);
						send_response();
						break;
				}
			}
			else
			{
				clean_counterRx();
				clean_RxBuffer();
			}
		//osDelayUntil(&prv_time, 2);
	}
}
*/
/*
void ESCTask(void const * argument)
{
	HAL_GPIO_WritePin(PORT_RESET, RESET_PIN, GPIO_PIN_RESET);
	osDelay(5);
	HAL_GPIO_WritePin(PORT_RESET, RESET_PIN, GPIO_PIN_SET);
	osDelay(2000);
	VMA_PwmEnable(&Vma);
	
	//Connections: RED - 5V с ESC(не подключать); BLACK - GND; WHITE - PWM
	//PWM: 50Hz, 1500 ms - STOP, 1200 ms - 1800 ms - CONTROL
	//TEST TASK: CONTROL ESC30 with R20-potenciometer
	//test ESC30A 1-04-2017	
	uint16_t setvalue;
	MX_TIM8_Init();//USE TIM8 for test ESC30
	HAL_TIM_PWM_Start_IT(&htim8, TIM_CHANNEL_3);
	osDelay(2000); //start Delay
	uint32_t prv_time = osKernelSysTick();
	for (;;)
	{			
		//test ESC30A
		
		setvalue = ((uint32_t)ADCFilteredValues[ADC1_NumOfChannel]*600)/RANGE_12BITS;//-300 .. + 300 uS
		if (setvalue>300)
		{
			PWMRegs[1] = 1500 + (setvalue - 300 + 1);
		}
		else
		{
			PWMRegs[1] = 1500 - (300 - setvalue);
		}
		
		
		setvalue = ((uint32_t)Vma.velocity*(ESC30_PWM_MAX - ESC30_PWM_MIN))/127;//-300 .. + 300 uS
		
		if (Vma.flagDirection == FORWARD)
		{
			Vma.PWM = 1500 + setvalue;
		}
		else
		{
			Vma.PWM = 1500 - setvalue;
		}		
		
		//VMA_SetPwm(&Vma);
		osDelayUntil(&prv_time, 10);
	}
}
*/