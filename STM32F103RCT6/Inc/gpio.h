
#ifndef __gpio_H
#define __gpio_H
#ifdef __cplusplus
 extern "C" {
#endif

#include "stm32f1xx_hal.h"
#include "main.h"

#include <stdbool.h>
/*DIP SWITCHES*/
#if !defined(SEMENUK_DRIVER)
	#define DIP1 			GPIO_PIN_15
	#define PORT_DIP1 GPIOA
	#define DIP2 			GPIO_PIN_10
	#define PORT_DIP2 GPIOC
	#define DIP3 			GPIO_PIN_11
	#define PORT_DIP3 GPIOC
	#define DIP4 			GPIO_PIN_12
	#define PORT_DIP4 GPIOC
	#define DIP5 			GPIO_PIN_2
	#define PORT_DIP5 GPIOD
	#define DIP6 			GPIO_PIN_5
	#define PORT_DIP6 GPIOB

	#define DBG 			GPIO_PIN_6
	#define PORT_DBG 	GPIOA

	#define BRAKE 						GPIO_PIN_4//vma
	#define PORT_BRAKE 				GPIOB
	#define BRAKE_EXTI_IRQn		EXTI4_IRQn
	#define BRAKE_IRQHandler	EXTI4_IRQHandler
	#define RESET_PIN					GPIO_PIN_9
	#define PORT_RESET 				GPIOB
	
	#define FAULT 						GPIO_PIN_8//add-driver
	#define PORT_FAULT 				GPIOB
	#define FAULT_EXTI_IRQn 	EXTI9_5_IRQn	
	#define FAULT_IRQHandler	EXTI9_5_IRQHandler

	#define DAC_PIN			GPIO_PIN_4
	#define PORT_DAC	 	GPIOA
	#define OE					GPIO_PIN_5
	#define PORT_OE		 	GPIOC

	//Motor GPIO pins
	#define MOTOR_DIR				GPIO_PIN_7
	#define PORT_MOTOR_DIR	GPIOA
	#define MOTOR_EN				GPIO_PIN_5
	#define PORT_MOTOR_EN		GPIOC

	#define HALL_SENSOR_A					GPIO_PIN_13
	#define PORT_HALL_SENSOR_A		GPIOB
	#define HALL_SENSOR_B					GPIO_PIN_14
	#define PORT_HALL_SENSOR_B		GPIOB
	#define HALL_SENSOR_C					GPIO_PIN_15
	#define PORT_HALL_SENSOR_C		GPIOB
//////////////////////
#else

	#define DIP1 			GPIO_PIN_0
	#define PORT_DIP1 GPIOC
	#define DIP2 			GPIO_PIN_1
	#define PORT_DIP2 GPIOC
	#define DIP3 			GPIO_PIN_2
	#define PORT_DIP3 GPIOC
	#define DIP4 			GPIO_PIN_3
	#define PORT_DIP4 GPIOC

	#define DBG 			GPIO_PIN_1
	#define PORT_DBG 	GPIOA
	
	#define FAULT 						GPIO_PIN_4//add-driver
	#define PORT_FAULT 				GPIOA
	#define FAULT_EXTI_IRQn 	EXTI4_IRQn	
	#define FAULT_IRQHandler	EXTI4_IRQHandler
	
  //just for no Errors wnen compile
	#define RESET_PIN							GPIO_PIN_2
	#define PORT_RESET 						GPIOA
	#define MOTOR_DIR							GPIO_PIN_2
	#define PORT_MOTOR_DIR				GPIOA
	#define MOTOR_EN							GPIO_PIN_2
	#define PORT_MOTOR_EN					GPIOA
	#define HALL_SENSOR_A					GPIO_PIN_2
	#define PORT_HALL_SENSOR_A		GPIOA
	#define HALL_SENSOR_B					GPIO_PIN_2
	#define PORT_HALL_SENSOR_B		GPIOA
	#define HALL_SENSOR_C					GPIO_PIN_2
	#define PORT_HALL_SENSOR_C		GPIOA
#endif
void 		MX_GPIO_Init(void);
uint8_t MX_GPIO_Init_Address(void);

void dbg_toggle();
void dbg_on();
void dbg_off();
void rst_on();
void rst_off();

#ifdef __cplusplus
}
#endif
#endif /*__ pinoutConfig_H */

