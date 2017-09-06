#include "vma.h"
#include "tim.h"
#include <math.h>
#include "stm32f1xx_hal.h"
#include "gpio.h"

GPIO_PinState hallSensorTable[6][3] = 
{
	{GPIO_PIN_SET, GPIO_PIN_RESET, GPIO_PIN_SET},			//101 
	{GPIO_PIN_SET, GPIO_PIN_RESET, GPIO_PIN_RESET},		//100
	{GPIO_PIN_SET, GPIO_PIN_SET, GPIO_PIN_RESET},			//110
	{GPIO_PIN_RESET, GPIO_PIN_SET, GPIO_PIN_RESET},		//010
	{GPIO_PIN_RESET, GPIO_PIN_SET, GPIO_PIN_SET},			//011
	{GPIO_PIN_RESET, GPIO_PIN_RESET, GPIO_PIN_SET}		//001
};

void VMA_GPIO_EN(GPIO_PinState en);
void VMA_GPIO_DIR(GPIO_PinState en);

void DRIVER_Init(DRIVER* driver_handle, uint8_t type)
{
	driver_handle->flagACPOver = RESET;
	driver_handle->flagDirection = FORWARD;
	//driver_handle->flagEnablePWM = RESET;
	driver_handle->current = 0;
	driver_handle->velocity = 0;
	driver_handle->ErrorCounter = 0;
	driver_handle->flagBrake = RESET;
	driver_handle->BackwardState = STATE_NULL1;
	driver_handle->BackwardCounter = 0;
	driver_handle->ForwardCounter = 0;
	
	driver_handle->TypeOfDriver = type;

	if (driver_handle->TypeOfDriver == VMA) // init for VMA
	{
		driver_handle->flagEnablePWM = RESET;
#if !defined(SEMENUK_DRIVER)	//my
	
	#if defined(VMADRIVER_ESC30)
		driver_handle->PWMDesire = ESC30_PWM_NULL;
		driver_handle->PWMCurrent = ESC30_PWM_NULL;
	#endif
	
	#if defined(VMADRIVER_MC33035)
		driver_handle->PWMDesire = MC33035_PWM_MIN;
		driver_handle->PWMCurrent = MC33035_PWM_MIN;
		
		MX_TIM2_Init(); // Timer for HALL_SENSOR oscillating
	#endif

		MX_TIM1_Init();// my VMA
#endif	
	}
	else if (driver_handle->TypeOfDriver == ADD)//init for ADD
	{
		driver_handle->flagEnablePWM = SET;
	#if !defined (SEMENUK_DRIVER)
		MX_TIM8_Init();//my
	#else
		MX_TIM1_Init();//semenuk
	#endif
	}
}

void DRIVER_Start(DRIVER* driver_handle)
{
	if (driver_handle->TypeOfDriver == VMA) // init for VMA
	{
#if !defined(SEMENUK_DRIVER)
	
	#if defined(VMADRIVER_ESC30)
		HAL_TIM_PWM_Start_IT(&htim1, TIM_CHANNEL_1);
	#endif
	
	#if defined(VMADRIVER_MC33035)
//		HAL_TIM_PWM_Start_IT(&htim8, TIM_CHANNEL_1);
//		HAL_TIM_Base_Start_IT(&htim2);
	#endif
	
#endif
	}
	else if (driver_handle->TypeOfDriver == ADD)//init for ADD
	{
	/*  HAL_TIMEx_PWMN_Start_IT(&htim1, TIM_CHANNEL_1);
	*/
#if !defined(SEMENUK_DRIVER)
	HAL_TIM_PWM_Start_IT(&htim8, TIM_CHANNEL_2);
  HAL_TIMEx_PWMN_Start_IT(&htim8, TIM_CHANNEL_2);

	HAL_TIM_PWM_Start_IT(&htim8, TIM_CHANNEL_3);
  HAL_TIMEx_PWMN_Start_IT(&htim8, TIM_CHANNEL_3);
	
#else
	HAL_TIM_PWM_Start_IT(&htim1, TIM_CHANNEL_2);
  //HAL_TIMEx_PWMN_Start_IT(&htim1, TIM_CHANNEL_2);

	HAL_TIM_PWM_Start_IT(&htim1, TIM_CHANNEL_3);
  //HAL_TIMEx_PWMN_Start_IT(&htim1, TIM_CHANNEL_3);
#endif
	}
}
void DRIVER_Stop(DRIVER* driver_handle)
{
	DRIVER_SetVelocity(driver_handle, 0);
}

void DRIVER_SetVelocity(DRIVER* driver_handle, uint8_t setvalue)
{
	if (setvalue>0x80)//должно быть > , хак для 6 драйвера
	{
		driver_handle->velocity = 0xff - setvalue + 1;
		driver_handle->flagDirection = BACKWARD;
	}
	else
	{
		driver_handle->velocity = setvalue;
		driver_handle->flagDirection = FORWARD;
	}
	if (setvalue == 0x00)//сброс Брейка
	{
		driver_handle->flagBrake = RESET;
		if (driver_handle->TypeOfDriver == ADD)
			driver_handle->flagEnablePWM = SET;
	}
}

void VMA_HallSensorShift()
{
	static uint8_t i = 0;
	
	HAL_GPIO_WritePin(PORT_HALL_SENSOR_A, HALL_SENSOR_A, hallSensorTable[i][0]);
	HAL_GPIO_WritePin(PORT_HALL_SENSOR_B, HALL_SENSOR_B, hallSensorTable[i][1]);
	HAL_GPIO_WritePin(PORT_HALL_SENSOR_C, HALL_SENSOR_C, hallSensorTable[i][2]);
	
	i++;
	if (i == 6) i = 0;
}
void DRIVER_SetPwm(DRIVER* driver_handle)
{
	uint16_t setvalue;
	if (driver_handle->TypeOfDriver == VMA)
	{
#if defined (VMADRIVER_ESC30)
	setvalue = ((uint32_t)driver_handle->velocity*(ESC30_PWM_MAX - ESC30_PWM_NULL))/DRIVER_VEL_MAX;//-300 .. + 300 uS
		if ((driver_handle->flagEnablePWM == SET) & (driver_handle->flagBrake == RESET))
		{
			uint8_t localdelta = 0;
			if ((driver_handle->PWMCurrent > 1600)|((driver_handle->PWMCurrent < 1400)))
				localdelta = VMA_PWM_DELTA;
			else 
				localdelta = VMA_PWM_DELTA;//VMA_PWM_NULL_DELTA;
			
			if (driver_handle->flagDirection == FORWARD)
				driver_handle->PWMDesire = ESC30_PWM_NULL + setvalue;
			else
				driver_handle->PWMDesire = ESC30_PWM_NULL - setvalue;
//			uint8_t localdelta = VMA_PWM_DELTA;
			
			if (abs(driver_handle->PWMDesire - driver_handle->PWMCurrent) > localdelta)//reg
			{
				if (driver_handle->PWMDesire > driver_handle->PWMCurrent) 
					driver_handle->PWMCurrent = driver_handle->PWMCurrent + localdelta;
				else
					driver_handle->PWMCurrent = driver_handle->PWMCurrent - localdelta;
			}
			else
				driver_handle->PWMCurrent = driver_handle->PWMDesire;
		}
		else
			DRIVER_SetPwmNull(driver_handle);
#endif
		
#if defined (VMADRIVER_MC33035)
	setvalue = ((uint32_t)driver_handle->velocity*(MC33035_PWM_MAX - MC33035_PWM_MIN))/DRIVER_VEL_MAX;//0.100% PWM
		
		if ((driver_handle->flagEnablePWM == SET) & (driver_handle->flagBrake == RESET))
		{
				driver_handle->PWMDesire = MC33035_PWM_MIN + setvalue;
			
				/*Start of regulation*/
				if (abs(driver_handle->PWMDesire - driver_handle->PWMCurrent) > VMA_PWM_DELTA)
				{
					if (driver_handle->PWMDesire > driver_handle->PWMCurrent) 
						driver_handle->PWMCurrent = driver_handle->PWMCurrent + VMA_PWM_DELTA;
					else
						driver_handle->PWMCurrent = driver_handle->PWMCurrent - VMA_PWM_DELTA;
				}
				else
					driver_handle->PWMCurrent = driver_handle->PWMDesire;
				/*End of regulation*/
				
			if (driver_handle->flagDirection == FORWARD)
			{
				VMA_GPIO_DIR(FORWARD);
			}
			else
			{
				VMA_GPIO_DIR(BACKWARD);
			}
			VMA_GPIO_EN(GPIO_PIN_SET);
		}
		else
		{
			DRIVER_SetPwmNull(driver_handle);
			VMA_GPIO_EN(GPIO_PIN_RESET);
		}
#endif
	}
	else if (driver_handle->TypeOfDriver == ADD)
	{
//#if defined(SEMENUK_DRIVER)
		setvalue = ((uint32_t)driver_handle->velocity*(ADD_PWM_MAX - ADD_PWM_MIN))/DRIVER_VEL_MAX;//0.100% PWM
		
		if ((driver_handle->flagEnablePWM == SET) & (driver_handle->flagBrake == RESET))
		{
				driver_handle->PWMDesire = ADD_PWM_MIN + setvalue;
			
//				/*Start of regulation*/
//				if (abs(driver_handle->PWMDesire - driver_handle->PWMCurrent) > VMA_PWM_DELTA)
//				{
//					if (driver_handle->PWMDesire > driver_handle->PWMCurrent) 
//						driver_handle->PWMCurrent = driver_handle->PWMCurrent + VMA_PWM_DELTA;
//					else
//						driver_handle->PWMCurrent = driver_handle->PWMCurrent - VMA_PWM_DELTA;
//				}
//				else
//					driver_handle->PWMCurrent = driver_handle->PWMDesire;
				static uint8_t localdelay = 0;
				if (abs(driver_handle->PWMDesire - driver_handle->PWMCurrent) > 5)
				{
					localdelay ++;
					if (localdelay > 200) localdelay = 0;
					if (localdelay % 200 == 0) 
					{
						if (driver_handle->PWMDesire > driver_handle->PWMCurrent) 
							driver_handle->PWMCurrent = driver_handle->PWMCurrent + 5;
						else
							driver_handle->PWMCurrent = driver_handle->PWMCurrent - 5;
					}
				}
				else
					driver_handle->PWMCurrent = driver_handle->PWMDesire;
				/*End of regulation*/
				
		}
		else
		{
			DRIVER_SetPwmNull(driver_handle);
//			DRIVER_Stop(driver_handle);
		}
		static bool pwmNchannelStarted = false;
		if ((driver_handle->PWMCurrent != ADD_PWM_MIN) & !pwmNchannelStarted)
		{
			HAL_TIMEx_PWMN_Start_IT(&htim1, TIM_CHANNEL_2);
			HAL_TIMEx_PWMN_Start_IT(&htim1, TIM_CHANNEL_3);
			pwmNchannelStarted = true;
		}
		/*
		if ((driver_handle->PWMCurrent == ADD_PWM_MIN) & pwmNchannelStarted)
		{
			HAL_TIMEx_PWMN_Stop_IT(&htim1, TIM_CHANNEL_2);
			HAL_TIMEx_PWMN_Stop_IT(&htim1, TIM_CHANNEL_3);
			pwmNchannelStarted = false;
		}
		*/
//#endif
	}
}

void VMA_GPIO_EN(GPIO_PinState en)
{
	HAL_GPIO_WritePin(PORT_MOTOR_EN, MOTOR_EN, en);
}
void VMA_GPIO_DIR(GPIO_PinState en)
{
	HAL_GPIO_WritePin(PORT_MOTOR_DIR, MOTOR_DIR, !en);//forward = 0 but Set = 1
}

void DRIVER_SetPwmNull(DRIVER* driver_handle)
{
	if (driver_handle->TypeOfDriver == VMA)
	{
#if defined (VMADRIVER_ESC30)
	driver_handle->PWMCurrent = ESC30_PWM_NULL;
#endif
#if defined (VMADRIVER_MC33035)
	driver_handle->PWMCurrent = MC33035_PWM_MIN;	
#endif
	}
	else if (driver_handle->TypeOfDriver == ADD)
	{
#if defined(SEMENUK_DRIVER)
	driver_handle->PWMCurrent = ADD_PWM_MIN;
#endif
	}
}
void DRIVER_SetPwmLow(DRIVER* driver_handle)
{
	if (driver_handle->TypeOfDriver == VMA)
	{
	//TODO need TEST
#if defined (VMADRIVER_ESC30)
	
	if ((driver_handle->PWMCurrent - ESC30_PWM_NULL) > VMA_PWM_DELTA)//на прямом ходу
	{
		driver_handle->PWMCurrent = driver_handle->PWMCurrent - VMA_PWM_DELTA;
	}
	else if ((ESC30_PWM_NULL - driver_handle->PWMCurrent ) > VMA_PWM_DELTA) //на обратном
	{
		driver_handle->PWMCurrent = driver_handle->PWMCurrent + VMA_PWM_DELTA;
	}
	else //около нуля
		driver_handle->PWMCurrent = ESC30_PWM_NULL;
	
#endif
#if defined (VMADRIVER_MC33035)
	driver_handle->PWMCurrent = driver_handle->PWMCurrent - VMA_PWM_DELTA;	
	if (driver_handle->PWMCurrent < MC33035_PWM_MIN)
		driver_handle->PWMCurrent = MC33035_PWM_MIN;
#endif
	}
	else
	{
#if defined(SEMENUK_DRIVER)
	driver_handle->flagBrake = SET;
	driver_handle->PWMCurrent = driver_handle->PWMCurrent - VMA_PWM_DELTA;	
	if (driver_handle->PWMCurrent < ADD_PWM_MIN)
		driver_handle->PWMCurrent = ADD_PWM_MIN;
#endif
	}
}

void DRIVER_PwmEnable(DRIVER* driver_handle)
{
	driver_handle->flagEnablePWM = SET;
}

void DRIVER_PwmDisable(DRIVER* driver_handle)
{
	driver_handle->flagEnablePWM = RESET;
	driver_handle->flagBrake = SET;
	
	driver_handle->ErrorCounter++;
	driver_handle->BackwardState = STATE_DOWN;
	driver_handle->BackwardCounter = 0;
#if defined (VMADRIVER_MC33035)
	VMA_GPIO_EN(GPIO_PIN_RESET);
#endif
}
