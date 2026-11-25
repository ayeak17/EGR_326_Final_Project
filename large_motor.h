#ifndef LARGE_MOTOR_H
#define LARGE_MOTOR_H

#include <stm32f446xx.h>
#include <stdio.h>

void LM_setup();
void LM_wave(int step_time, int dir, int steps);
void LM_full_step(int step_time, int dir, int steps);

#endif
