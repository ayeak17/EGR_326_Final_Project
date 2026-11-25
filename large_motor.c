#include "large_motor.h"

void LM_full_step(int step_time, int dir, int steps)
{
	//Phases:
	//PC7: 1
	//PC8: 2
	//PC9: 3
	//PC10: 4
	
	uint8_t bits = 0x3;  //start with 0b0011
	
	if (dir > 0) {
	for (int x = 0; x < steps; x++)
	{
		for (int n = 0; n < 4; n++)
		{
			GPIOC->BSRR = (0x780 << 16) | ((bits & 0x0F) << 7); //clear 7-10 and set active bits from variable
			delayMS(step_time);  //delay between steps
			bits = ((bits << 1) & 0x0F) | (bits >> 3);  //shift the pattern wrapping bit 3 to bit 0
		}
	}
	GPIOC->BSRR |= 0x7800000;
}
	else if (dir <= 0)
	{
		for (int x = 0; x < steps; x++)
	{
		for (int n = 0; n < 4; n++)
		{
			GPIOC->BSRR = (0x780 << 16) | ((bits & 0x0F) << 7); //clear 7-10 and set active bits from variable
			delayMS(step_time);  //delay between steps
			bits = (bits >> 1) | ((bits & 0x01) << 3); //shift the pattern wrapping bit 0 to bit 3
		}
	}
	GPIOC->BSRR |= 0x7800000;
	}
	
}

void LM_wave(int step_time, int dir, int steps)
{
	//Phases:
	//PC7: 1
	//PC8: 2
	//PC9: 3
	//PC10: 4
	if (dir > 0)
	{
	for (int x = 0; x < steps; x++)
	{
		for (int n = 0; n < 4; n++)  //Start with lowest on and shift up
		{
			GPIOC->ODR |= (0x80 << n);  
			delayMS(step_time);
			GPIOC->BSRR |= 0x7800000;
		}
	}
}
	else if (dir <= 0)  //other direction
	{
		for (int x = 0; x < steps; x++)
	{
		for (int n = 0; n < 4; n++)  //start with highest on and shift down
		{
			GPIOC->ODR |= (0x400 >> n);
			delayMS(step_time);
			GPIOC->BSRR |= 0x7800000;
		}
	}
	}
}

void LM_setup()
{
	RCC -> AHB1ENR |= 0x4;  //GPIOC
	GPIOC -> MODER |= 0x154000; //motor phase outputs
}
