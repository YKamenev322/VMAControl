#include "eeprom.h"
#include "stm32f1xx_hal_i2c.h"
//#include "i2c.h"
uint8_t eeBuffer[EEBUFFER_SIZE];

extern I2C_HandleTypeDef hi2c1;

void I2C_EE_Write(uint16_t val, uint16_t WriteAddr)
{
	eeBuffer[0] = val;
	eeBuffer[1] = val >> 8;
	
	HAL_I2C_Mem_Write(&hi2c1, (uint16_t) EEPROM_ADDRESS, WriteAddr, 
									  I2C_MEMADD_SIZE_16BIT, eeBuffer, EEBUFFER_SIZE, EE_TIMEOUT);
}

uint16_t I2C_EE_Read( uint16_t ReadAddr) 
{
	eeBuffer[0] = 0x00;
	eeBuffer[1] = 0x00;
	
	HAL_I2C_Mem_Read(&hi2c1, (uint16_t) EEPROM_ADDRESS, ReadAddr, 
									 I2C_MEMADD_SIZE_16BIT, eeBuffer, EEBUFFER_SIZE, EE_TIMEOUT);
	
	return (eeBuffer[1] << 8 | eeBuffer[0]);
}

