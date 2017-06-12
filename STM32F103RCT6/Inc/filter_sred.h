/*
 * filter_sred.h
 */

#ifndef FILTER_SRED_H_
#define FILTER_SRED_H_

#define COUNT_FILTER	10

typedef union
{
    unsigned int Val;
    struct
    {
    	unsigned Flag:1;		//Флаг заполнения суммы
    	unsigned Index:8;		//Хранение индекса буфера
    	unsigned Filter_sum:23;	//Регистр суммы для усреднения
    } Reg;
		//unsigned short int buffer[COUNT_FILTER];
} FILTER_REG;

unsigned short int	filter_sred(unsigned short int ADC_val, unsigned short int* buf, FILTER_REG* filter_reg);

#endif /* SW_TIMER_H_ */
