
#ifndef __tim_H
#define __tim_H
#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"
#include "main.h"
#if !defined (SEMENUK_DRIVER)
	 
	#define	TIMx_ADD_DRIVER						TIM8
	 
	#define	TIMx_ADD_DRIVER_CH1				GPIO_PIN_7		//TIM8CH2
	#define	TIMx_ADD_DRIVER_CH1_PORT	GPIOC					
	#define	TIMx_ADD_DRIVER_CH2				GPIO_PIN_8		//TIM8CH3 
	#define	TIMx_ADD_DRIVER_CH2_PORT	GPIOC					
	#define	TIMx_ADD_DRIVER_CH1N			GPIO_PIN_0		//TIM8CH2N
	#define	TIMx_ADD_DRIVER_CH1N_PORT	GPIOB					
	#define	TIMx_ADD_DRIVER_CH2N			GPIO_PIN_1		//TIM8CH3N 
	#define	TIMx_ADD_DRIVER_CH2N_PORT	GPIOB	
	#define TIMx_ADD_CLK_ENABLE				__HAL_RCC_TIM8_CLK_ENABLE()
	#define TIMx_ADD_CC_IRQn					TIM8_CC_IRQn

	#define TIMx_VMA_DRIVER						TIM1
	#define TIMx_VMA_CLK_ENABLE				__HAL_RCC_TIM1_CLK_ENABLE()	
	#define TIMx_VMA_CC_IRQn					TIM1_CC_IRQn
	 
	#define	TIMx_VMA_DRIVER_CH1				GPIO_PIN_8		//TIM1CH1 
	#define	TIMx_VMA_DRIVER_CH1_PORT	GPIOA								  
	 
#else

	#define	TIMx_ADD_DRIVER						TIM1
	
	#define	TIMx_ADD_DRIVER_CH1				GPIO_PIN_9		//TIM1CH2 
	#define	TIMx_ADD_DRIVER_CH1_PORT	GPIOA					
	#define	TIMx_ADD_DRIVER_CH2				GPIO_PIN_10		//TIM1CH3  
	#define	TIMx_ADD_DRIVER_CH2_PORT	GPIOA					
	#define	TIMx_ADD_DRIVER_CH1N			GPIO_PIN_0		//TIM1CH2N 
	#define	TIMx_ADD_DRIVER_CH1N_PORT	GPIOB					
	#define	TIMx_ADD_DRIVER_CH2N			GPIO_PIN_1		//TIM1CH3N  
	#define	TIMx_ADD_DRIVER_CH2N_PORT	GPIOB	
	#define TIMx_ADD_CLK_ENABLE				__HAL_RCC_TIM1_CLK_ENABLE()
	#define TIMx_ADD_CC_IRQn					TIM1_CC_IRQn
	#define TIMx_ADD_REMAP_PARTIAL		__HAL_AFIO_REMAP_TIM1_PARTIAL()
	 
#endif

#define TIMx_ADD_DRIVER_PSC			72 - 1			// 1 MHz
#define TIMx_ADD_DRIVER_PERIOD  200 - 1			// 5000Hz
	 
#define ADD_PWM_MAX							190 - 1
#define ADD_PWM_MIN							0
	 

/* 
 * ESC30 Settings
 */
	 
#define TIMx_VMA_DRIVER_ESC30_PSC			72 - 1			// 1 MHz
#define TIMx_VMA_DRIVER_ESC30_PERIOD	20000 - 1   // 50Hz	
	 
#define ESC30_PWM_NULL				1500 //uS
#define ESC30_PWM_MAX					1900
#define ESC30_PWM_MIN					1100

/* 
 * MC33035 Settings
 */
#define TIMx_VMA_DRIVER_MC33035_PSC			72 - 1			// 1 MHz
#define TIMx_VMA_DRIVER_MC33035_PERIOD	667 - 1     // 1500Hz // 400 - 2500Hz	

#define MC33035_PWM_MAX	  		199
#define MC33035_PWM_MIN 			0

#define TIMx_VMA_DRIVER_MC33035_HALLSENSOR_PSC				72 - 1     // 1 MHz	
#define TIMx_VMA_DRIVER_MC33035_HALLSENSOR_PERIOD_MIN	2777       // 1000000 : 2777 = 360 Hz	
#define TIMx_VMA_DRIVER_MC33035_HALLSENSOR_PERIOD_MAX	65535       // 1000000 : 65535 = 15 Hz	
	 	
//#define PWMPulse			200 - 1 // 5 kHz
//#define PWMPulseBase 	100 
extern uint8_t	PWMPulse;
extern uint8_t	PWMPulseBase;

extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim8;


extern void Error_Handler(void);

void MX_TIM1_Init(void);
void MX_TIM2_Init(void);
void MX_TIM8_Init(void);
                    

#ifdef __cplusplus
}
#endif
#endif /*__ tim_H */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
