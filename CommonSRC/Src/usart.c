
/* Includes ------------------------------------------------------------------*/
#include "usart.h"
#include "flash.h"
#ifndef BOOTLOADER
	#include "cmsis_os.h"
	extern SemaphoreHandle_t bUARTSemaphore;
	extern TimerHandle_t UARTTimer;
#endif
uint8_t TxOK[] = "OK";
uint8_t TxERROR[] = "ERROR";
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */
__IO ITStatus UartReady = RESET;
 uint8_t aRxBuffer[RXBUFFERSIZE] = {0};
 uint8_t RxBuffer[1] = {0};
 uint8_t aTxBuffer[TXBUFFERSIZE] = {0};
 #if defined(BOOTLOADER)
  uint8_t aTxFlashBuffer[TXBUFFERFLASHSIZE] = {0};
 #endif
 uint16_t numberRx = 0;
 uint16_t counterRx = 0;
 uint32_t timerCounter = 0;
 uint8_t RS485_ADDR = 0;
 
UART_HandleTypeDef huart;
DMA_HandleTypeDef hdma_rx;
DMA_HandleTypeDef hdma_tx;

void MX_USART_UART_Init(void)
{
  huart.Instance = USARTx;
  huart.Init.BaudRate = USARTx_BAUDRATE;
  huart.Init.WordLength = UART_WORDLENGTH_8B;
  huart.Init.StopBits = UART_STOPBITS_1;
  huart.Init.Parity = UART_PARITY_NONE;
  huart.Init.Mode = UART_MODE_TX_RX;
  huart.Init.HwFlowCtl = UART_HWCONTROL_NONE;//UART_HWCONTROL_RTS
  huart.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart) != HAL_OK)
  {
    Error_Handler();
  }
}

void HAL_UART_MspInit(UART_HandleTypeDef* uartHandle)
{

  GPIO_InitTypeDef  GPIO_InitStruct;

  /*##-1- Enable peripherals and GPIO Clocks #################################*/
  /* Enable GPIO clock */
  USARTx_TX_GPIO_CLK_ENABLE();
  USARTx_RX_GPIO_CLK_ENABLE();
	USARTx_RTS_GPIO_CLK_ENABLE();

  /* Enable USARTx clock */
  USARTx_CLK_ENABLE();

  /* Enable DMA clock */
  DMAx_CLK_ENABLE();

  /*##-2- Configure peripheral GPIO ##########################################*/
  /* UART TX GPIO pin configuration  */
  GPIO_InitStruct.Pin       = USARTx_TX_PIN;
  GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull      = GPIO_PULLUP;
  GPIO_InitStruct.Speed     = GPIO_SPEED_FREQ_HIGH;

  HAL_GPIO_Init(USARTx_TX_GPIO_PORT, &GPIO_InitStruct);

  /* UART RX GPIO pin configuration  */
  GPIO_InitStruct.Pin 			= USARTx_RX_PIN;
  GPIO_InitStruct.Mode      = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull      = GPIO_NOPULL;

  HAL_GPIO_Init(USARTx_RX_GPIO_PORT, &GPIO_InitStruct);
	
	/* UART RTS GPIO pin config */
	GPIO_InitStruct.Pin 	= USARTx_RTS_PIN;
  GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull  = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;

  HAL_GPIO_Init(USARTx_RTS_GPIO_PORT, &GPIO_InitStruct);	
	
  /*##-3- Configure the NVIC for UART ########################################*/
  /* NVIC for USART */
  HAL_NVIC_SetPriority(USARTx_IRQn, 0, 1);
  HAL_NVIC_EnableIRQ(USARTx_IRQn);
	
  /*##-3- Configure the DMA ##################################################*/
  /* Configure the DMA handler for Transmission process */
	
  hdma_tx.Instance                 = USARTx_TX_DMA_CHANNEL;
  hdma_tx.Init.Direction           = DMA_MEMORY_TO_PERIPH;
  hdma_tx.Init.PeriphInc           = DMA_PINC_DISABLE;
  hdma_tx.Init.MemInc              = DMA_MINC_ENABLE;
  hdma_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
  hdma_tx.Init.MemDataAlignment    = DMA_MDATAALIGN_BYTE;
  hdma_tx.Init.Mode                = DMA_NORMAL;
  hdma_tx.Init.Priority            = DMA_PRIORITY_LOW;

  HAL_DMA_Init(&hdma_tx);

  /* Associate the initialized DMA handle to the UART handle */
  __HAL_LINKDMA(uartHandle, hdmatx, hdma_tx);

  /* Configure the DMA handler for reception process */
	
  hdma_rx.Instance                 = USARTx_RX_DMA_CHANNEL;
  hdma_rx.Init.Direction           = DMA_PERIPH_TO_MEMORY;
  hdma_rx.Init.PeriphInc           = DMA_PINC_DISABLE;
  hdma_rx.Init.MemInc              = DMA_MINC_ENABLE;
  hdma_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
  hdma_rx.Init.MemDataAlignment    = DMA_MDATAALIGN_BYTE;
  hdma_rx.Init.Mode                = DMA_NORMAL;
  hdma_rx.Init.Priority            = DMA_PRIORITY_HIGH;

  HAL_DMA_Init(&hdma_rx);

  /* Associate the initialized DMA handle to the the UART handle */
  __HAL_LINKDMA(uartHandle, hdmarx, hdma_rx);

  /*##-4- Configure the NVIC for DMA #########################################*/
  /* NVIC configuration for DMA transfer complete interrupt (USARTx_TX) */
  HAL_NVIC_SetPriority(USARTx_DMA_TX_IRQn, 6, 1);
  HAL_NVIC_EnableIRQ(USARTx_DMA_TX_IRQn);

  /* NVIC configuration for DMA receive complete interrupt (USARTx_RX) */
  HAL_NVIC_SetPriority(USARTx_DMA_RX_IRQn, 6, 0);// выше, чем нижний предел прерываний РТОС
																									//для использования ..FromISR();
  HAL_NVIC_EnableIRQ(USARTx_DMA_RX_IRQn);

}

/* Дергаем ногой RTS
*		1 вход в функциях send..
*		2 вход в HAL_UART_TxCpltCallback()
*/
void rts_toggle()
{
	HAL_GPIO_TogglePin(USARTx_RTS_GPIO_PORT, USARTx_RTS_PIN);
}

uint8_t check_request()
{
	uint8_t ret = BTL_CMD_NO_CMD;
	//uint8_t crc = 0x00;
	uint8_t crc = START_BYTE;
	for (uint16_t i = 1; i < numberRx - 1; i++)//не проверяем 1 стартбайт
	{
		if (i < CMD_NUMB_START_BYTES)
		{ 
			if (aRxBuffer[i] != START_BYTE) return ret;
		}
		if (i == CMD_NUMB_START_BYTES) 
		{
			if (aRxBuffer[i] != RS485_ADDR) return ret;
		}
		//crc = crc + aRxBuffer[i];
		crc ^= aRxBuffer[i];
	}
	//crc = crc + START_BYTE; //добавляем 1 стартбайт
	if (crc != aRxBuffer[numberRx - 1]) return ret;
	
	return aRxBuffer[CMD_NUMB_START_BYTES + 1]; //FlagByte
}

/*	Получаем из посылки число байт флеша, ожидаемых в следующей посылке
*/
uint16_t GetData16()
{
	return (aRxBuffer[CMD_NUMB_START_BYTES + 2] << 8 | aRxBuffer[CMD_NUMB_START_BYTES + 3]);
}

void clean_TxBuffer()
{
	for (uint8_t i = 0; i < TXBUFFERSIZE; i++)
	{
		aTxBuffer[i] = 0x00;
	}
}

void clean_RxBuffer()
{
	for (uint16_t i = 0; i < numberRx; i++)
	{
		aRxBuffer[i] = 0x00;
	}
}
void clean_counterRx()
{
	counterRx = 0;
}
void done_request()
{
}
void make_response(uint16_t data1, uint16_t data2, uint8_t data3, uint8_t data4, uint8_t flag)
{	
	uint8_t crc = 0x00;
	
	aTxBuffer[0] = START_BYTE;
	aTxBuffer[1] = RS485_ADDR;
	aTxBuffer[2] = flag;
#ifdef BOOTLOADER	
	aTxBuffer[2] = aRxBuffer[CMD_NUMB_START_BYTES + 1]; //FlagByte
	aTxBuffer[3] = 0;
	aTxBuffer[4] = 0;
	aTxBuffer[5] = 0;
	aTxBuffer[6] = 0;
#endif
#ifndef BOOTLOADER
	aTxBuffer[3] = data1 >> 8;
	aTxBuffer[4] = data1;
	aTxBuffer[5] = data2 >> 8;
	aTxBuffer[6] = data2;
	aTxBuffer[7] = data3;
	aTxBuffer[8] = data4;
#endif
	
	for (uint16_t i = 0; i < TXBUFFERSIZE - 1; i++)
	{
		//crc = crc + aTxBuffer[i];
		crc ^= aTxBuffer[i]; 
	}
	
	aTxBuffer[TXBUFFERSIZE - 1] = crc;
}

#if defined(BOOTLOADER)
void send_flash_data(uint32_t* data, uint8_t words)
{

	for (uint16_t i = 0; i < (words * 4); i = i + 4)
	{
		aTxFlashBuffer[i] 	= 0;
		aTxFlashBuffer[i+1] = 0;
		aTxFlashBuffer[i+2] = 0;
		aTxFlashBuffer[i+3] = 0;
	}
	for (uint16_t i = 0; i < (words * 4); i = i + 4)
	{		
		aTxFlashBuffer[i] 	|= data[i/4];
		aTxFlashBuffer[i+1] |= data[i/4] >> 8;
		aTxFlashBuffer[i+2] |= data[i/4] >> 16;
		aTxFlashBuffer[i+3] |= data[i/4] >> 24;
	}
	rts_toggle();
	HAL_UART_Transmit_DMA(&huart, (uint8_t *)aTxFlashBuffer, words * 4);
	HAL_Delay(AFTERSEND_DELAY);
}
#endif

void send_response()
{
	rts_toggle();
	HAL_UART_Transmit_DMA(&huart, (uint8_t *)aTxBuffer, TXBUFFERSIZE);
	HAL_Delay(AFTERSEND_DELAY);
}

void reseive_dma_1()
{
	HAL_UART_Receive_DMA(&huart, (uint8_t *)RxBuffer, 1);
}

void receive(uint16_t count, uint8_t timeout_sec)
{
	clean_RxBuffer();
	numberRx = count;
	//HAL_UART_Receive_DMA(&huart, (uint8_t *)aRxBuffer, numberRx);
	/**/
	clean_counterRx();
	reseive_dma_1();
}

void update_timer()
{
	/*Ставим новое время таймера*/
	timerCounter = HAL_GetTick()/* + REQUEST_DELAY*/;
}

void check_timer()
{
	/*Если был принят хоть 1 байт*/
	if (counterRx > 0)
	{
		/*Если время REQUEST_DELAY прошло*/
/*		if (timerCounter < HAL_GetTick())
		{
			counterRx = 0;
			clean_RxBuffer();
		}
*/
		if (HAL_GetTick() - timerCounter < REQUEST_DELAY) {}
		else 
		{
			counterRx = 0;
			clean_RxBuffer();
		}
	}
}


void check_timer2()
{
		/*Если время REQUEST_DELAY прошло*/
	if (timerCounter < HAL_GetTick())
	{
		counterRx = 0;
		clean_RxBuffer();
	}	
}
	
void send_OK()
{
	rts_toggle();
	HAL_UART_Transmit_DMA(&huart, TxOK, COUNTOF(TxOK)-1);
	HAL_Delay(AFTERSEND_DELAY);
}

void send_ERROR()
{
	rts_toggle();
	HAL_UART_Transmit_DMA(&huart, TxERROR, COUNTOF(TxERROR)-1);
	HAL_Delay(AFTERSEND_DELAY);
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
	rts_toggle();
	//clean_TxBuffer();
	//UartReady = RESET;
}


void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
#ifndef BOOTLOADER
	static portBASE_TYPE xHigherPriorityTaskWoken;
	xHigherPriorityTaskWoken = pdFALSE;
#endif
	
	aRxBuffer[counterRx] = RxBuffer[0];
	if (counterRx == 0)
	{
		
#ifdef BOOTLOADER 
		update_timer();//For FreeRTOS comment this line
										// and launch Task
#else
		xTimerResetFromISR(UARTTimer, &xHigherPriorityTaskWoken);
#endif
		
	}
	
	counterRx++;
	if (counterRx == numberRx) 
	{
		UartReady = SET;
#ifndef BOOTLOADER
		clean_counterRx();
#endif
	}
	reseive_dma_1();
#ifndef BOOTLOADER

	if (xHigherPriorityTaskWoken == pdTRUE)
	{
		xHigherPriorityTaskWoken = pdFALSE;
		taskYIELD();
	}
#endif
}

void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart)
{
}

