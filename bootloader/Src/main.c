#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f1xx_hal.h"
#include "usart.h"
#include "flash.h"

#if !defined(SEMENUK_DRIVER)
	#define DIP1 			GPIO_PIN_15
	#define PORT_DIP1 GPIOA
	#define DIP2 			GPIO_PIN_10
	#define PORT_DIP2 GPIOC
	#define DIP3 			GPIO_PIN_11
	#define PORT_DIP3 GPIOC

	#define DBG 			GPIO_PIN_6
	#define PORT_DBG 	GPIOA
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
#endif

/* Для изменения буфера данных меняем RXBUFFERSIZE в usart.h и
 * FLASH32_BUFF_SIZE в flash.h 
 * Разница в 4 раза
 */
extern UART_HandleTypeDef huart;
extern __IO ITStatus UartReady;
extern uint32_t flashBuffer[FLASH32_BUFF_SIZE];

extern void SystemClock_Config(void);
extern void Error_Handler(void);

void 		MX_GPIO_Init(void);
uint8_t MX_GPIO_Init_Address(void);
void dbg_toggle();

uint8_t startflag = 0;

int main(void)
{
	bkp_enable();

#if defined(ENABLE_START_RESET)			
	if (BKUPRead(RTC_BKP_DR2) == 0) {
		startflag = 1;
	}
	else if (BKUPRead(RTC_BKP_DR1) == 0 && Flash_Check()) {
		jump_to_app();
	};
#else	
	if (BKUPRead(RTC_BKP_DR1) == 0 && Flash_Check()) {
		jump_to_app();
	};
#endif	
	
  HAL_Init();

  SystemClock_Config();
	
	/*GPIO for getting Address*/
  MX_GPIO_Init();
	RS485_ADDR = MX_GPIO_Init_Address();
	
	MX_USART_UART_Init();
	HAL_UART_MspInit(&huart);
	
	receive(CMD_NUBM_BYTES, 0);
	if (startflag == 0)
		send_OK();
	
  while (1)
  {
		check_timer();
		
#if defined(ENABLE_START_RESET)		
		if (startflag == 1) 
			if (check_start_timer() == 1) {
				__disable_irq();
				BKUPWrite(RTC_BKP_DR2, BKP_VALUE);
				//HAL_Delay(100);
				HAL_NVIC_SystemReset();
			}
#endif
			
		if (UartReady == SET)
		{
			UartReady = RESET;
			
			switch (check_request()) {
				
				case BTL_CMD_RESTART:
					
						__disable_irq();
						BKUPWrite(RTC_BKP_DR2, BKP_VALUE);
						HAL_NVIC_SystemReset();
						break;
				
				case BTL_CMD_ERASE: 
						Flash_Erase();
						receive(CMD_NUBM_BYTES, 0);
						send_OK();
						break;
				
				case BTL_CMD_SETDATA_FLASH:
						receive(GetData16() + CMD_NUBM_PROTOCOL_BYTES, 0);
						HAL_Delay(100);
						send_OK();
						break;
				
				case BTL_CMD_FLASH:
						if (Flash_Flash() == BTL_FLASH_RES_OK)
						{
							receive(CMD_NUBM_BYTES, 0);
							send_OK();
						}
						else 
						{
							receive(CMD_NUBM_BYTES, 0);
							send_ERROR();
						}
						break;
				case BTL_CMD_FLASHCRC:
						if (Flash_FlashCRC() == BTL_FLASH_RES_OK)
						{
							receive(CMD_NUBM_BYTES, 0);
							send_OK();
						}
						else 
						{
							receive(CMD_NUBM_BYTES, 0);
							send_ERROR();
						}
						break;
						
				case BTL_CMD_READDATA:
				{
						uint8_t Page = GetData16() >> 8;
						uint8_t Words = GetData16();
				
						receive(CMD_NUBM_BYTES, 0);
						Flash_Read(Page, Words);//page and words
						HAL_Delay(5);
						send_flash_data(flashBuffer, Words);
						HAL_Delay(5);
						Flash_clean_flashbuffer(Words);
						break;
				}
				case BTL_CMD_GOTOAPP:
					
						send_OK();
						HAL_Delay(5);
						goToResetAndApp();
						break;
				
				default:
						receive(CMD_NUBM_BYTES, 0);
						//send_ERROR();
						break;
				
			} //end of switch

		}
		//else HAL_Delay(1);
	}/*end of while*/
}/*end of main*/

	
void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct;

  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
	
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  /*Configure GPIO pins : PA15 */
  GPIO_InitStruct.Pin = DIP1;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(PORT_DIP1, &GPIO_InitStruct);
  /*Configure GPIO pins : PC10 */
  GPIO_InitStruct.Pin = DIP2;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(PORT_DIP2, &GPIO_InitStruct);
  /*Configure GPIO pins : PC11 */
  GPIO_InitStruct.Pin = DIP3;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(PORT_DIP3, &GPIO_InitStruct);
	//DBG_PIN
	GPIO_InitStruct.Pin = DBG;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(PORT_DBG, &GPIO_InitStruct);
}
void dbg_toggle()
{
	HAL_GPIO_TogglePin(PORT_DBG, DBG);
}

uint8_t MX_GPIO_Init_Address(void)
{
#if !defined(SEMENUK_DRIVER)
	return (1 + ((!HAL_GPIO_ReadPin(PORT_DIP3, DIP3) << 2) | (!HAL_GPIO_ReadPin(PORT_DIP2, DIP2) << 1) | (!HAL_GPIO_ReadPin(PORT_DIP1, DIP1) << 0)));
#else
	return (1 + ((!HAL_GPIO_ReadPin(PORT_DIP2, DIP2) << 1) | (!HAL_GPIO_ReadPin(PORT_DIP1, DIP1) << 0)));
#endif
}

#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t* file, uint32_t line)
{
}
#endif

