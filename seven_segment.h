#ifndef SEVEN_SEGMENT_H
#define SEVEN_SEGMENT_H

#include "stm32f4xx.h"
#include <stdio.h>

void SS_spi_init();
void SS_SPI_Transmit(uint8_t instr, uint8_t val);
void SS_SPI_Disable(void);
void SS_SPI_Enable(void);
void SS_clear(void);

#endif
