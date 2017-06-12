#ifndef MODBUS_H
#define MODBUS_H

#include "stm32f1xx_hal.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define HI(x) ((x)>>8)
#define LO(x) ((x)& 0xFF)

//размер буфера принимаемых по UART данных
#define MaxLenghtRecBuf 50
//размер буфера передаваемых по UART данных
#define MaxLenghtTrBuf 50
//размер буфера регистров хранения
#define MaxDataLen 10
//адрес устройства в сети RS485
#define RS485Addr 32

uint8_t ErrorMessage(uint8_t Error);
uint8_t ModBus(uint8_t NumByte);
uint16_t GetCRC16(unsigned char *buf, char bufsize);

#endif
