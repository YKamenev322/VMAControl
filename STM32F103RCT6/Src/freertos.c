
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

/* USER CODE END Includes */

/* ThreadId Handles*/
osThreadId i2cTaskHandle;
osThreadId testTaskHandle;
osThreadId uartTaskHandle;

/* Uart Vars */
extern __IO ITStatus UartReady;

/* ADC Vars*/
extern ADC_HandleTypeDef hadc1;
extern __IO uint16_t   aADCxConvertedValues[ADCCONVERTEDVALUES_BUFFER_SIZE];
extern uint16_t   uhADCChannelToDAC_mVolt;
extern uint16_t   uhVrefInt_mVolt;
extern int32_t    wTemperature_DegreeCelsius;  
extern uint8_t    ubSequenceCompleted;     /* Set when all ranks of the sequence have been converted */

uint16_t   PWMRegs[3]={10000,10000, 10000};
#define	PWMPulse	19999 	
uint8_t   	RS485_Address = 0;
/* Function prototypes -------------------------------------------------------*/
//void i2cTask(void const * argument);
void testTask(void const * argument);
void uartTask(void const * argument);

SemaphoreHandle_t xSemaphore;
SemaphoreHandle_t bSemaphoreModbusTask;

void MX_FREERTOS_Init(void) {

	//xSemaphore = xSemaphoreCreateMutex();
	bSemaphoreModbusTask = xSemaphoreCreateBinary();

  /* USER CODE BEGIN RTOS_THREADS */
/*	
  osThreadDef(i2cTaskName, i2cTask, osPriorityNormal, 0, 128);
  i2cTaskHandle = osThreadCreate(osThread(i2cTaskName), NULL);
*/
/**/
  osThreadDef(testTaskName, testTask, osPriorityNormal, 0, 128);
  testTaskHandle = osThreadCreate(osThread(testTaskName), NULL);
/**/

	osThreadDef(uartTaskName, uartTask, osPriorityRealtime, 0, 128);
  uartTaskHandle = osThreadCreate(osThread(uartTaskName), NULL);
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

void testTask(void const * argument)
{
	uint32_t prv_time = osKernelSysTick();
	uint32_t i = 0;

	//bkp_enable();
	
	for(;;) {    
                                                       
    HAL_ADC_Start(&hadc1);
      
    /* Wait for conversion completion before conditional check hereafter */
    HAL_ADC_PollForConversion(&hadc1, 1);
    if (ubSequenceCompleted == SET)

    {
      
      /* Computation of ADC conversions raw data to physical values */
      /* Note: ADC results are transferred into array "aADCxConvertedValues"  */
      /*       in the order of their rank in ADC sequencer.                   */
      uhADCChannelToDAC_mVolt    = COMPUTATION_DIGITAL_12BITS_TO_VOLTAGE(aADCxConvertedValues[0]);
      uhVrefInt_mVolt            = COMPUTATION_DIGITAL_12BITS_TO_VOLTAGE(aADCxConvertedValues[2]);
      wTemperature_DegreeCelsius = COMPUTATION_TEMPERATURE_STD_PARAMS(aADCxConvertedValues[1]);

      /* Reset variable for next loop iteration */
      ubSequenceCompleted = RESET;
    }
		
		//rts_toggle();
		
		dbg_toggle();
		
		//TEEEEEEEST
						//make_response();
						//send_response();
		
		//test
/*		
		if (PWMRegs[1] == 0) PWMRegs[1] = 19500;
		PWMRegs[1] = PWMRegs[1] >> 3;
		if (PWMRegs[2] == 0) PWMRegs[2] = 19500;
		PWMRegs[2] = PWMRegs[2] >> 3;
*/		
		
		osDelayUntil(&prv_time, 1000);
	}
}

void uartTask(void const * argument)
{
	uint32_t prv_time = osKernelSysTick();
	receive(CMD_NUBM_BYTES, 0);
	
	for(;;) {
		check_timer();
		if (UartReady == SET)
			{
				//osDelay(10);
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
						PWMRegs[1] = (PWMPulse/100) * (GetData16() >> 8);
						PWMRegs[2] = (PWMPulse/100) * (0x00FF & GetData16());
						make_response();
						receive(CMD_NUBM_BYTES, 0);
						send_response();
						break;
				}
			}                                  
		osDelayUntil(&prv_time, 10);
	}
}

