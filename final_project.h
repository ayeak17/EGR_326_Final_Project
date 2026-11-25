/*
 Title: final_project.h
 Author: Allie Perna & Alex Yeakle
 Course: EGR 326
 Assignment: Final Project
 Instructor: Dr. Krug
 Description: Main header file to include all components
*/
#ifndef _FINAL_PROJ_
#define _FINAL_PROJ_

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stm32f446xx.h>

//Functions
void main_setup(void);


//LCD
#include "ILI9341.h"
#include "RccConfig.h"
#include "font_ubuntu_mono_24.h"
#include "my_photos.h"
#include "spi.h"

//7-segment
#include "seven_segment.h"

//Big Motor
#include "large_motor.h"

//Keypad
#include "keypad.h"

//Sonar
#include "sonar.h"

//Neopixel

//Small motor

//Rotary Encoder

//EEPROM


#endif
