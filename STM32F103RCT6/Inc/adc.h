/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __adc_H
#define __adc_H
#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"
//#include "main.h"

/* USER CODE BEGIN Includes */
//#include <stdbool.h>
/* USER CODE END Includes */

/* USER CODE BEGIN Private defines */
#define VDD_APPLI                      ((uint32_t) 3300)   /* Value of analog voltage supply Vdda (unit: mV) */
#define RANGE_12BITS                   ((uint32_t) 4095)   /* Max value with a full range of 12 bits */
#define MAX_ADC4_VALUE							    /*RANGE_12BITS * 1*/3430		/*Для защиты драйвера ВМА по току*/	//10А - 1/3 диапазона:  
#define MAX_ADC3_VALUE							    RANGE_12BITS * 1//3300		/*Для защиты драйвера ADD по току*/	
																													//диапазон: 3100(нуль ACS712) + (0..1000)
#define ADD_MAX_CURRENT									4000//mA
#define VMA_MAX_CURRENT									24000//mA
#define ADD_MAX_CURRENT_VALUE						3000//mA для отсечки add
#define VMA_MAX_CURRENT_VALUE						10000//mA для отсечки vma

#define ADCCONVERTEDVALUES_BUFFER_SIZE ((uint32_t)    5)   /* Size of array containing ADC converted values: set to ADC sequencer number of ranks converted, to have a rank in each address */

/* Internal temperature sensor: constants data used for indicative values in  */
/* this example. Refer to device datasheet for min/typ/max values.            */
/* For more accurate values, device should be calibrated on offset and slope  */
/* for application temperature range.                                         */
#define INTERNAL_TEMPSENSOR_V25        ((int32_t)1430)         /* Internal temperature sensor, parameter V25 (unit: mV). Refer to device datasheet for min/typ/max values. */
#define INTERNAL_TEMPSENSOR_AVGSLOPE   ((int32_t)4300)         /* Internal temperature sensor, parameter Avg_Slope (unit: uV/DegCelsius). Refer to device datasheet for min/typ/max values. */                                                               /* This calibration parameter is intended to calculate the actual VDDA from Vrefint ADC measurement. */

	 /**
  * @brief  Computation of temperature (unit: degree Celsius) from the internal
  *         temperature sensor measurement by ADC.
  *         Computation is using temperature sensor standard parameters (refer
  *         to device datasheet).
  *         Computation formula:
  *         Temperature = (VTS - V25)/Avg_Slope + 25
  *         with VTS = temperature sensor voltage
  *              Avg_Slope = temperature sensor slope (unit: uV/DegCelsius)
  *              V25 = temperature sensor @25degC and Vdda 3.3V (unit: mV)
  *         Calculation validity conditioned to settings: 
  *          - ADC resolution 12 bits (need to scale value if using a different 
  *            resolution).
  *          - Power supply of analog voltage Vdda 3.3V (need to scale value 
  *            if using a different analog voltage supply value).
  * @param TS_ADC_DATA: Temperature sensor digital value measured by ADC
  * @retval None
  */
#define COMPUTATION_TEMPERATURE_STD_PARAMS(TS_ADC_DATA)                        \
  ((((int32_t)(INTERNAL_TEMPSENSOR_V25 - (((TS_ADC_DATA) * VDD_APPLI) / RANGE_12BITS)   \
     ) * 1000                                                                  \
    ) / INTERNAL_TEMPSENSOR_AVGSLOPE                                           \
   ) + 25                                                                      \
  )

/**
  * @brief  Computation of voltage (unit: mV) from ADC measurement digital
  *         value on range 12 bits.
  *         Calculation validity conditioned to settings: 
  *          - ADC resolution 12 bits (need to scale value if using a different 
  *            resolution).
  *          - Power supply of analog voltage Vdda 3.3V (need to scale value 
  *            if using a different analog voltage supply value).
  * @param ADC_DATA: Digital value measured by ADC
  * @retval None
  */
#define COMPUTATION_DIGITAL_12BITS_TO_VOLTAGE(ADC_DATA)                        \
  ( (ADC_DATA) * VDD_APPLI / RANGE_12BITS)

/* Definition of ADCx clock resources */
#define ADCx                            ADC1
#define ADCx_CLK_ENABLE()               __HAL_RCC_ADC1_CLK_ENABLE()

#define ADCx_FORCE_RESET()              __HAL_RCC_ADC1_FORCE_RESET()
#define ADCx_RELEASE_RESET()            __HAL_RCC_ADC1_RELEASE_RESET()

#if !defined(SEMENUK_DRIVER)
	/* Definition of ADCxA channel (ADC1 potenciometer)*/
	#define ADCx_CHANNELa                   ADC_CHANNEL_10
	#define ADCx_CHANNELa_GPIO_CLK_ENABLE() __HAL_RCC_GPIOC_CLK_ENABLE()
	#define ADCx_CHANNELa_GPIO_PORT         GPIOC
	#define ADCx_CHANNELa_PIN               GPIO_PIN_0
	#define ADC1_NumOfChannel								0

	/* Definition of ADCxB channel (ADC2 potenciometer) */
	#define ADCx_CHANNELb                   ADC_CHANNEL_11
	#define ADCx_CHANNELb_GPIO_CLK_ENABLE() __HAL_RCC_GPIOC_CLK_ENABLE()
	#define ADCx_CHANNELb_GPIO_PORT         GPIOC
	#define ADCx_CHANNELb_PIN               GPIO_PIN_1
	#define ADC2_NumOfChannel								1

	/* Definition of ADCxC channel (ADC3 add-driver current) */
	#define ADCx_CHANNELc                   ADC_CHANNEL_12
	#define ADCx_CHANNELc_GPIO_CLK_ENABLE() __HAL_RCC_GPIOC_CLK_ENABLE()
	#define ADCx_CHANNELc_GPIO_PORT         GPIOC
	#define ADCx_CHANNELc_PIN               GPIO_PIN_2
	#define ADC3_NumOfChannel								2

	/* Definition of ADCxD channel (ADC4 vma-driver current)*/
	#define ADCx_CHANNELd                   ADC_CHANNEL_13
	#define ADCx_CHANNELd_GPIO_CLK_ENABLE() __HAL_RCC_GPIOC_CLK_ENABLE()
	#define ADCx_CHANNELd_GPIO_PORT         GPIOC
	#define ADCx_CHANNELd_PIN               GPIO_PIN_3
	#define ADC4_NumOfChannel								3

#else
	//Все каналы посадил на PA0 - ADC12_IN0
	/* Definition of ADCxA channel (ADC1 potenciometer)*/
	#define ADCx_CHANNELa                   ADC_CHANNEL_0
	#define ADCx_CHANNELa_GPIO_CLK_ENABLE() __HAL_RCC_GPIOC_CLK_ENABLE()
	#define ADCx_CHANNELa_GPIO_PORT         GPIOA
	#define ADCx_CHANNELa_PIN               GPIO_PIN_0
	#define ADC1_NumOfChannel								0

	/* Definition of ADCxB channel (ADC2 potenciometer) */
	#define ADCx_CHANNELb                   ADC_CHANNEL_0
	#define ADCx_CHANNELb_GPIO_CLK_ENABLE() __HAL_RCC_GPIOC_CLK_ENABLE()
	#define ADCx_CHANNELb_GPIO_PORT         GPIOA
	#define ADCx_CHANNELb_PIN               GPIO_PIN_0
	#define ADC2_NumOfChannel								1

	/* Definition of ADCxC channel (ADC3 add-driver current) */
	#define ADCx_CHANNELc                   ADC_CHANNEL_0
	#define ADCx_CHANNELc_GPIO_CLK_ENABLE() __HAL_RCC_GPIOC_CLK_ENABLE()
	#define ADCx_CHANNELc_GPIO_PORT         GPIOA
	#define ADCx_CHANNELc_PIN               GPIO_PIN_0
	#define ADC3_NumOfChannel								2

	/* Definition of ADCxD channel (ADC4 vma-driver current)*/
	#define ADCx_CHANNELd                   ADC_CHANNEL_0
	#define ADCx_CHANNELd_GPIO_CLK_ENABLE() __HAL_RCC_GPIOC_CLK_ENABLE()
	#define ADCx_CHANNELd_GPIO_PORT         GPIOA
	#define ADCx_CHANNELd_PIN               GPIO_PIN_0
	#define ADC4_NumOfChannel								3
	
#endif

/* Definition of Temp channel */
#define ADCTemp_NumOfChannel						4

/* Definition of ADCx DMA resources */
#define ADCx_DMA_CLK_ENABLE()           __HAL_RCC_DMA1_CLK_ENABLE()
#define ADCx_DMA                        DMA1_Channel1

#define ADCx_DMA_IRQn                   DMA1_Channel1_IRQn
#define ADCx_DMA_IRQHandler             DMA1_Channel1_IRQHandler

/* Definition of ADCx NVIC resources */
#define ADCx_IRQn                       ADC1_2_IRQn
#define ADCx_IRQHandler                 ADC1_2_IRQHandler

/* ## Definition of DAC related resources ################################### */
/* Definition of DACx clock resources */
/*
#define DACx                            DAC
#define DACx_CLK_ENABLE()               __HAL_RCC_DAC_CLK_ENABLE()
#define DACx_CHANNEL_GPIO_CLK_ENABLE()  __HAL_RCC_GPIOA_CLK_ENABLE()

#define DACx_FORCE_RESET()              __HAL_RCC_DAC_FORCE_RESET()
#define DACx_RELEASE_RESET()            __HAL_RCC_DAC_RELEASE_RESET()

#define DACx_CHANNEL_TO_ADCx_CHANNELa            DAC_CHANNEL_1

#define DACx_CHANNEL_TO_ADCx_CHANNELa_PIN        GPIO_PIN_4
#define DACx_CHANNEL_TO_ADCx_CHANNELa_GPIO_PORT  GPIOA
*/
/* USER CODE END Private defines */

extern ADC_HandleTypeDef hadc1;

void MX_ADC1_Init(void);
void MX_DMA_Init(void);
void HAL_ADC_MspInit(ADC_HandleTypeDef* hadc);
	 
/* USER CODE BEGIN Prototypes */

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif
#endif /*__ pinoutConfig_H */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
