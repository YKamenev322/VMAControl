#ifndef I2C_H
#define I2C_H

#include "stm32f1xx_hal.h"

#define EEPROM_ADDRESS 0xAE //(0b1010 A2 A1 A0 R\W) A2=A1=A0=1 адрес 7битный, 0й бит чтение/запись формирует либа

#define COUNT_C_EE_ADDR 			0x00
#define COUNT_H_EE_ADDR 			0x02
#define EEBUFFER_SIZE 				2
#define EE_TIMEOUT						10

void I2C_EE_Write(uint16_t val, uint16_t WriteAddr);
uint16_t I2C_EE_Read( uint16_t ReadAddr);

#endif
