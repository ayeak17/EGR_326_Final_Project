#ifndef SONAR_H
#define SONAR_H

#include <stm32f446xx.h>
#include <stdio.h>

void sonar_setup(void);
int sonar_read_distance(void);


#endif
