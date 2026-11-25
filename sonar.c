#include "sonar.h"

volatile int edge = 0;
volatile int rise = 0;
volatile int fall = 0;

void sonar_setup()
{
	__disable_irq();
	RCC -> AHB1ENR |= 0x1; //GPIOA
	RCC -> APB1ENR |= 0xA; //TIM5,3
	RCC -> APB2ENR |= 0x4000;  //enable syscfg
				   
	GPIOA -> MODER &= ~0x3003; //clear bits to 0
	GPIOA -> MODER |= 0x2002;  // alternate function on PA0, PA6
	GPIOA -> AFR[0] &= ~0x0F00000F; //clear bits to 0
	GPIOA -> AFR[0] |= 0x2000002; // AF2 (TIM5) for PA0 and AF2 (TIM3) for PA6
	
	//Capture on PA0
	TIM5 -> DIER = 0x2;  //enable the CC1 interrupt
	TIM5 -> PSC = 16-1;  //divided by 16
	TIM5 -> ARR = 0xFFFFFFFF; //32-bit max count
	TIM5 -> CCMR1 = 0x01;  //CC1 set as input capture
	TIM5 -> CCER = 0xB; //CC1 both edges, capture enabled
	TIM5 -> EGR |= 0x1; //reinitialze the counter (force new prescaler value)
	TIM5 -> CR1 = 0x1;   //counter enable
	
	//PWM on PA6 (CH1)
	TIM3 -> PSC = 16-1;  //divided by 16
	TIM3 -> ARR = 65000-1;  //set period to 65ms
	TIM3 -> CNT = 0;  //clear counter
	
	TIM3 -> CCMR1 = 0x60;  //PWM Mode 1 on CH1 of timer 3
	TIM3 -> CCER |= 0x0001; //enable output on CH1 
	TIM3 -> CCR1 = 10; //set on time (10 us)
	TIM3 -> CR1 = 0x1; //enable timer
	
	NVIC_EnableIRQ(TIM5_IRQn);  //enable TIM5 interrupt
	
	__enable_irq();
}

void TIM5_IRQHandler(void)
{
	edge = 1; //edge flag
	if (GPIOA->IDR & 0x1)  //if PA0 is high, there is a rising edge
		rise = TIM5->CCR1;
	else  //otherwise it's a falling edge
		fall = TIM5->CCR1;
}

int sonar_read_distance(void)
{
	static float dist = 0;
	static int echo;
	if (edge) 
		{
			//calculating distance
			echo = fall - rise;	
			dist = echo / 148.0;
			//printf("%.2f \n", dist);
			edge = 0;
			rise = 0;
			fall = 0;
		}
	return dist;
}
