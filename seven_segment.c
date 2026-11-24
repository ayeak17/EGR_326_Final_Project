#include "seven_segment.h"

void SS_spi_init()
{
	RCC->AHB1ENR |= 0x2;  //enable GPIOB
	RCC->APB1ENR |= 0x4000; //enable SPI2
	GPIOB->MODER |= 0x98000000; //AF for PB15,13, output for 14
	GPIOB->AFR[1] |= 0x50500000; //AF5 for PB15,13

	SPI2->CR1 |= 0x431C; //master mode, transmit only, baud rate: f/16
	SPI2->CR2 = 0;
	GPIOB->BSRR |= 0x4000; //bring CS high
	
	//Setup
	SS_SPI_Enable();
	uint8_t reg = 0x09;  //decode mode register
	uint8_t data = 0xFF;  //decode on all
	SS_SPI_Transmit(reg, data);
	
	reg = 0x0A;  //intensity register
	data = 0x07;
	SS_SPI_Transmit(reg, data);
	
	reg = 0x0B; //scan limit register
	data = 0x07; //display all digits
	SS_SPI_Transmit(reg, data);
	
	reg = 0x0C; //shutdown register
	data = 0x01;  //normal mode
	SS_SPI_Transmit(reg, data);
}

void SS_SPI_Disable(void)
{
   // disable SPI in CR1 register
	SPI2->CR1 &= ~0x40;
}

void SS_SPI_Enable(void)
{
   // enable SPI in CR1 register
	SPI2->CR1 |= 0x40;
}

void SS_SPI_Transmit(uint8_t instr, uint8_t val)
{
	uint8_t temp;
	GPIOB->BSRR = 0x40000000;  //bring CS low
	
 	while (!(SPI2->SR & 0x2));  //wait for tx buffer to be empty
	SPI2->DR = (uint8_t)instr;
	while (!(SPI2->SR & 0x2));  //wait for tx buffer to be empty
	
	SPI2->DR = (uint8_t)val;
	while (!(SPI2->SR & 0x2));  //wait for tx buffer to be empty
	while (SPI2->SR & 0x80);  //wait for not busy
	
	while (SPI2->SR & 0x01)  //empty the buffer
		temp = SPI2->DR;
	
	GPIOB->BSRR = 0x4000;  //bring CS high
	
}

void SS_clear()
{
	//blank all digits
	SPI_Transmit(0x01, 0x0F);
	SPI_Transmit(0x02, 0x0F);
	SPI_Transmit(0x03, 0x0F);
	SPI_Transmit(0x04, 0x0F);
	SPI_Transmit(0x05, 0x0F);
	SPI_Transmit(0x06, 0x0F);
	SPI_Transmit(0x07, 0x0F);
	SPI_Transmit(0x08, 0x0F);
}
