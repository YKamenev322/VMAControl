
#ifndef __gpio_H
#define __gpio_H
#ifdef __cplusplus
 extern "C" {
#endif

#include "stm32f1xx_hal.h"
#include "main.h"

#include <stdbool.h>
/*DIP SWITCHES*/
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

#define BRAKE 			GPIO_PIN_4
#define PORT_BRAKE 	GPIOB
#define FAULT 			GPIO_PIN_8
#define PORT_FAULT 	GPIOB
#define RESET_PIN		GPIO_PIN_9
#define PORT_RESET 	GPIOB

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

