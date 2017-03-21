
#ifndef __usart_H
#define __usart_H
#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"
#include "main.h"
/*
#define USARTx                           USART1
#define USARTx_CLK_ENABLE()              __HAL_RCC_USART1_CLK_ENABLE();
#define DMAx_CLK_ENABLE()                __HAL_RCC_DMA1_CLK_ENABLE()
#define USARTx_RX_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOA_CLK_ENABLE()
#define USARTx_TX_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOA_CLK_ENABLE()
#define USARTx_RTS_GPIO_CLK_ENABLE()     __HAL_RCC_GPIOA_CLK_ENABLE()

#define USARTx_FORCE_RESET()             __HAL_RCC_USART1_FORCE_RESET()
#define USARTx_RELEASE_RESET()           __HAL_RCC_USART1_RELEASE_RESET()

// Definition for USARTx Pins 
#define USARTx_TX_PIN                    GPIO_PIN_9
#define USARTx_TX_GPIO_PORT              GPIOA
#define USARTx_RX_PIN                    GPIO_PIN_10
#define USARTx_RX_GPIO_PORT              GPIOA
#define USARTx_RTS_PIN                   GPIO_PIN_12
#define USARTx_RTS_GPIO_PORT             GPIOA

// Definition for USARTx's DMA 

#define USARTx_TX_DMA_CHANNEL             DMA1_Channel4
#define USARTx_RX_DMA_CHANNEL             DMA1_Channel5


// Definition for USARTx's NVIC 
#define USARTx_DMA_TX_IRQn                DMA1_Channel4_IRQn
#define USARTx_DMA_RX_IRQn                DMA1_Channel5_IRQn
#define USARTx_DMA_TX_IRQHandler          DMAChannel4_IRQHandler
#define USARTx_DMA_RX_IRQHandler          DMAChannel5_IRQHandler

// Definition for USARTx's NVIC 
#define USARTx_IRQn                      USART1_IRQn
#define USARTx_IRQHandler                USART1_IRQHandler
*/

#define USARTx                           USART2
#define USARTx_CLK_ENABLE()              __HAL_RCC_USART2_CLK_ENABLE();
#define DMAx_CLK_ENABLE()                __HAL_RCC_DMA1_CLK_ENABLE()
#define USARTx_RX_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOA_CLK_ENABLE()
#define USARTx_TX_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOA_CLK_ENABLE()
#define USARTx_RTS_GPIO_CLK_ENABLE()     __HAL_RCC_GPIOA_CLK_ENABLE()

#define USARTx_FORCE_RESET()             __HAL_RCC_USART2_FORCE_RESET()
#define USARTx_RELEASE_RESET()           __HAL_RCC_USART2_RELEASE_RESET()

// Definition for USARTx Pins 
#define USARTx_TX_PIN                    GPIO_PIN_2
#define USARTx_TX_GPIO_PORT              GPIOA
#define USARTx_RX_PIN                    GPIO_PIN_3
#define USARTx_RX_GPIO_PORT              GPIOA
#define USARTx_RTS_PIN                   GPIO_PIN_1
#define USARTx_RTS_GPIO_PORT             GPIOA

// Definition for USARTx's DMA 

#define USARTx_TX_DMA_CHANNEL             DMA1_Channel7
#define USARTx_RX_DMA_CHANNEL             DMA1_Channel6


// Definition for USARTx's NVIC 
#define USARTx_DMA_TX_IRQn                DMA1_Channel7_IRQn
#define USARTx_DMA_RX_IRQn                DMA1_Channel6_IRQn
#define USARTx_DMA_TX_IRQHandler          DMAChannel7_IRQHandler
#define USARTx_DMA_RX_IRQHandler          DMAChannel6_IRQHandler

// Definition for USARTx's NVIC 
#define USARTx_IRQn                      USART2_IRQn
#define USARTx_IRQHandler                USART2_IRQHandler

#define USARTx_BAUDRATE                  57600//9600

//Протокольные настройки
#define CMD_NUMB_START_BYTES		2
#define CMD_NUMB_ADDR_BYTES			1
#define CMD_NUMB_FLAG_BYTES			1
#define CMD_NUMB_DATA_BYTES			2
#define CMD_NUMB_CS_BYTES				1
// 0xAA 0xAA Addr Cmd D1 D2 CS = 7
	
#define CMD_NUBM_BYTES					7//CMD_NUMB_START_BYTES+CMD_NUMB_ADDR_BYTES+CMD_NUMB_FLAG_BYTES+CMD_NUMB_DATA_BYTES+CMD_NUMB_CS_BYTES //7
#define CMD_NUBM_PROTOCOL_BYTES	5//CMD_NUBM_BYTES - CMD_NUMB_DATA_BYTES//5
#define START_BYTE 							0xAA
//#define RS485_ADDR 							0x01
/* Size of Reception buffer */
#define RXBUFFERSIZE                      1024 + CMD_NUBM_PROTOCOL_BYTES
#define TXBUFFERSIZE                      CMD_NUBM_BYTES + 1 //

/* Exported macro ------------------------------------------------------------*/
#define COUNTOF(__BUFFER__)   (sizeof(__BUFFER__) / sizeof(*(__BUFFER__)))

#define AFTERSEND_DELAY					0   //ms

#if   defined(BOOTLOADER)
	#define REQUEST_DELAY						500   //ms
#else
	#define REQUEST_DELAY						200   //ms
#endif 



extern UART_HandleTypeDef huart;
extern uint8_t RS485_ADDR;
extern void Error_Handler(void);
void MX_USART1_UART_Init(void);

void send_OK();
void send_ERROR();
void receive(uint16_t count, uint8_t timeout_sec);
uint8_t check_request();
uint16_t GetData16();
void clean_RxBuffer();
void check_timer();
void done_request();
void make_response();
void send_response();


#ifdef __cplusplus
}
#endif
#endif /*__ usart_H */

