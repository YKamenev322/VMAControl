#include "flash.h"
#include "usart.h"

pFunction Jump_To_Application;
uint32_t Address = 0, PAGEError = 0, Error = 0;

uint32_t flashBuffer[FLASH32_BUFF_SIZE] = {0x00000000};

extern uint16_t numberRx;
extern uint8_t aRxBuffer[RXBUFFERSIZE];

void bkp_enable()
{
		HAL_PWR_EnableBkUpAccess();
  __HAL_RCC_BKP_CLK_ENABLE();
}
uint8_t Flash_Check()
{
	    /* Check the correctness of written data */
	
		uint32_t Addr = FLASH_USER_START_ADDR + FLASH_USER_START_ADDR_OFFSET;
		uint32_t Addr_end = Addr + 16;
		uint8_t result;
		//проверяем первые 16 байт
    while (Addr < Addr_end)
    {
      if((*(__IO uint32_t*) Addr) != 0xffffffff)
      {
        result++;
      }
      Addr += 4;
    }
	return result;
}

void goToBootloader()
{
		__disable_irq();
		BKUPWrite(RTC_BKP_DR1, BKP_VALUE);
		HAL_NVIC_SystemReset();
}
void goToResetAndApp()
{
		__disable_irq();
		BKUPWrite(RTC_BKP_DR1, 0x00000000);
		HAL_NVIC_SystemReset();
}

void jump_to_app(void)
	{
	uint32_t JumpAddress;

	uint32_t startAddress = FLASH_USER_START_ADDR + FLASH_USER_START_ADDR_OFFSET;
	SCB->VTOR = NVIC_VectTab_FLASH | ((startAddress) & (uint32_t)0x1FFFFF80);
	JumpAddress = *(__IO uint32_t*) (startAddress + 4);
	Jump_To_Application = (pFunction) JumpAddress;
	__set_MSP(*(__IO uint32_t*) (startAddress));		
	Jump_To_Application(); 
	}

	uint32_t Flash_Erase()
{
	static FLASH_EraseInitTypeDef EraseInitStruct;

		HAL_FLASH_Unlock();

		EraseInitStruct.TypeErase   = FLASH_TYPEERASE_PAGES;
		EraseInitStruct.PageAddress = FLASH_USER_START_ADDR;
		EraseInitStruct.NbPages     = (FLASH_USER_END_ADDR - FLASH_USER_START_ADDR) / FLASH_PAGE_SIZE;

		if (HAL_FLASHEx_Erase(&EraseInitStruct, &PAGEError) != HAL_OK)
		{
			Error = HAL_FLASH_GetError();
		}
		HAL_FLASH_Lock();
		
		Address = FLASH_USER_START_ADDR + FLASH_USER_START_ADDR_OFFSET;
		
		return Error;	
}

uint8_t Flash_Flash()
{					
	uint16_t numberBytes = numberRx - CMD_NUBM_PROTOCOL_BYTES;
	uint8_t offset = CMD_NUMB_START_BYTES + 2;//смещение первого байта данных в принятой посылке
	for (uint16_t i = 0; i < numberBytes; i = i+4)
	{
		flashBuffer[i/4] |= aRxBuffer[i+3+offset] << 24;
		flashBuffer[i/4] |= aRxBuffer[i+2+offset] << 16;
		flashBuffer[i/4] |= aRxBuffer[i+1+offset] << 8;
		flashBuffer[i/4] |= aRxBuffer[i+offset];
						
			//aRxBuffer[i] = 0x00;
			//aRxBuffer[i+1] = 0x00;
			//aRxBuffer[i+2] = 0x00;
			//aRxBuffer[i+3] = 0x00;
			
	}
	HAL_FLASH_Unlock();	
		
	uint16_t k = 0;
	uint32_t Address_end = Address + numberBytes;
	
	while (Address < Address_end )
	{
		uint32_t Data = flashBuffer[k];
		if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, Address, Data) == HAL_OK)
		{
			Address = Address + 4;
			flashBuffer[k] = 0x00000000;
			k++;
		}
		else break;
	}
	
	HAL_FLASH_Lock();
	
	if (Address >= Address_end )
		return BTL_FLASH_RES_OK;
	else 
		return BTL_FLASH_RES_ERROR;
}

uint32_t BKUPRead(uint32_t BackupRegister)
{
  uint32_t backupregister = 0;
  uint32_t pvalue = 0;

  /* Check the parameters */
  //assert_param(IS_RTC_BKP(BackupRegister));

  backupregister = (uint32_t)BKP_BASE; 
  backupregister += (BackupRegister * 4);
  
  pvalue = (*(__IO uint32_t *)(backupregister)) & BKP_DR1_D;

  /* Read the specified register */
  return pvalue;
}

void BKUPWrite(uint32_t BackupRegister, uint32_t Data)
{
  uint32_t tmp = 0;

  /* Check the parameters */
  //assert_param(IS_RTC_BKP(BackupRegister));
  
  tmp = (uint32_t)BKP_BASE; 
  tmp += (BackupRegister * 4);

  *(__IO uint32_t *) tmp = (Data & BKP_DR1_D);
}
