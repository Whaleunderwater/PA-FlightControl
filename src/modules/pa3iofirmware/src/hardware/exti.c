#include <exti.h>

void EXTIX_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD | GPIO_Mode_IPU;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD | GPIO_Mode_IPU;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource4);

	EXTI_InitStructure.EXTI_Line = EXTI_Line4;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);

	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource5);

	EXTI_InitStructure.EXTI_Line = EXTI_Line5;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);

	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource6);

	EXTI_InitStructure.EXTI_Line = EXTI_Line6;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);

	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource7);

	EXTI_InitStructure.EXTI_Line = EXTI_Line7;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);

	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource0);

	EXTI_InitStructure.EXTI_Line = EXTI_Line0;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);

	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource1);

	EXTI_InitStructure.EXTI_Line = EXTI_Line1;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);

	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

extern u32 timer_tick;

u32 start[6] = { 0, 0, 0, 0, 0, 0 };
u16 pwm[6] = { 0, 0, 0, 0, 0, 0 };
u32 ctl_error[6] = { 0, 0, 0, 0, 0, 0 };

void EXTI4_IRQHandler(void)
{
	if (EXTI_GetITStatus(EXTI_Line4) != RESET)
	{
		if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_4) == Bit_SET)
		{
			start[0] = timer_tick;
		}
		else if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_4) == Bit_RESET)
		{
			u32 _end = timer_tick;
			if (_end < start[0])
			{
				pwm[0] = 0xffffffff - start[0] + _end;
			}
			else
			{
				pwm[0] = _end - start[0];
			}
			ctl_error[0] = 0;
		}
	}
	EXTI_ClearITPendingBit(EXTI_Line4);
}

void EXTI9_5_IRQHandler(void)
{
	if (EXTI_GetITStatus(EXTI_Line5) != RESET)
	{
		if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_5) == Bit_SET)
		{
			start[1] = timer_tick;
		}
		else if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_5) == Bit_RESET)
		{
			u32 _end = timer_tick;
			if (_end < start[1])
			{
				pwm[1] = 0xffffffff - start[1] + _end;
			}
			else
			{
				pwm[1] = _end - start[1];
			}
			ctl_error[1] = 0;
		}
	}
	EXTI_ClearITPendingBit(EXTI_Line5);

	if (EXTI_GetITStatus(EXTI_Line6) != RESET)
	{
		if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_6) == Bit_SET)
		{
			start[2] = timer_tick;
		}
		else if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_6) == Bit_RESET)
		{
			u32 _end = timer_tick;
			if (_end < start[2])
			{
				pwm[2] = 0xffffffff - start[2] + _end;
			}
			else
			{
				pwm[2] = _end - start[2];
			}
			ctl_error[2] = 0;
		}
	}
	EXTI_ClearITPendingBit(EXTI_Line6);

	if (EXTI_GetITStatus(EXTI_Line7) != RESET)
	{
		if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_7) == Bit_SET)
		{
			start[3] = timer_tick;
		}
		else if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_7) == Bit_RESET)
		{
			u32 _end = timer_tick;
			if (_end < start[3])
			{
				pwm[3] = 0xffffffff - start[3] + _end;
			}
			else
			{
				pwm[3] = _end - start[3];
			}
			ctl_error[3] = 0;
		}

	}
	EXTI_ClearITPendingBit(EXTI_Line7);
}

void EXTI0_IRQHandler(void)
{
	if (EXTI_GetITStatus(EXTI_Line0) != RESET)
	{
		if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_0) == Bit_SET)
		{
			start[4] = timer_tick;
		}
		else if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_0) == Bit_RESET)
		{
			u32 _end = timer_tick;
			if (_end < start[4])
			{
				pwm[4] = 0xffffffff - start[4] + _end;
			}
			else
			{
				pwm[4] = _end - start[4];
			}
			ctl_error[4] = 0;
		}
	}
	EXTI_ClearITPendingBit(EXTI_Line0);
}

void EXTI1_IRQHandler(void)
{
	if (EXTI_GetITStatus(EXTI_Line1) != RESET)
	{
		if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1) == Bit_SET)
		{
			start[5] = timer_tick;
		}
		else if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1) == Bit_RESET)
		{
			u32 _end = timer_tick;
			if (_end < start[5])
			{
				pwm[5] = 0xffffffff - start[5] + _end;
			}
			else
			{
				pwm[5] = _end - start[5];
			}
			ctl_error[5] = 0;
		}
	}
	EXTI_ClearITPendingBit(EXTI_Line1);
}
