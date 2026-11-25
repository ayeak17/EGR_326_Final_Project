/*
 Title: main.c
 Author: Allie Perna & Alex Yeakle
 Course: EGR 326
 Assignment: Final Project
 Instructor: Dr. Krug
 Description: Main function for the project
*/

#include "final_project.h"

int main()
{
	main_setup();

	while (1)
	{

	}
}

void main_setup()
{
	Display_Init(); //set up LCD
	// Splash screen
	Draw_Bitmap((TFT_WIDTH - jeff->width) / 2, (TFT_HEIGHT - jeff->height) / 2,
                jeff);
	delayMS(4000);
	Fill_Screen(GRAY);

	SS_spi_init();	//set up seven segment

	LM_setup();

	keypad_setup();

	sonar_setup();
	
}
