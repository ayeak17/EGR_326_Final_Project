/*  Author: Jacob Clarey
 *  Date: 10/9/23
 *  Description: This is the header file for spi transmission functions.
 *  Notes:
 */

#include "spi.h"

/*******************************************************************************/
//                          USER FUNCTION DEFINITIONS
/*******************************************************************************/
void SPI_Init(void)
{
    SPI_GPIO();

   //    NEEDS CR1 and CR2 defined
   //    CR1->  Master mode, MSB transmit first, Bit8,9=1
   //    CR1-> Full Duplex, 8-bit data
   // CR2= 0 
   SPI1->CR1 |= 0x304;
	SPI1->CR1 |= 0x4000;
	SPI1->CR2 = 0;
		

    SPI_Enable();
}

void SPI_GPIO(void)
{
	//define PIN setup for SCK, MOSI, MISO, CS_GPIO
	
	// enable SPI1 Clock
	RCC->APB2ENR |= 0x1000;
	RCC->AHB1ENR |= 0x2;  //enable GPIOB
	
	
	// enable MODER for SCK, MOSI, MISO, CS_GPIO  (Note CS- is just an output)
	SCK_GPIO->MODER |= (0x2 << (SCK_PIN*2));
	MOSI_GPIO->MODER |= (0x2 << (MOSI_PIN*2));
	CS_GPIO->MODER |= 0x1 << (CS_PIN*2);
	
	// setup AF fo SCK, MOSI, MISO  (SPI1 remember!)
	SCK_GPIO->AFR[0] |= (0x5 << (SCK_PIN*4));
	MOSI_GPIO->AFR[0] |= (0x5 << (MOSI_PIN*4));
	
  CS_Low();
}

void SPI_Disable(void)
{
   // disable SPI in CR1 register
	SPI1->CR1 &= ~0x40;
}

void SPI_Enable(void)
{
   // enable SPI in CR1 register
	SPI1->CR1 |= 0x40;
}

void SPI_Transmit(uint8_t *data, uint8_t size)
{
    uint8_t i = 0;
    while (i < size)
    {
        while (!(SPI1->SR & 0x2))
        {
        }
        SPI1->DR = data[i];
        i++;
    }

    while (!(SPI1->SR & 0x2))
    {
    }
    while (SPI1->SR & 0x80)
    {
    }

    uint8_t temp = SPI1->DR;
    temp = SPI1->SR;
}

void CS_Low(void)
{
    CS_GPIO->ODR &= ~(1 << CS_PIN);
}

void CS_High(void)
{
    CS_GPIO->ODR |= 1 << CS_PIN;
}
/*******************************************************************************/
/*******************************************************************************/

/* EOF */
