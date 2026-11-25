#include "keypad.h"

void keypad_setup()
{
	RCC -> APHB1ENR |= 0x4; //GPIOC
	GPIOC -> MODER &= ~0xFFFFFFF; //keypad inputs
	GPIOC -> PUPDR |= 0x55; //pull up on rows
}

int read_keypad(void)
{
	int num = 0;
	uint32_t col, row;
	for (col=0; col < 3; col++)
	{
		GPIOC -> MODER &= ~0x00003FFF;
		GPIOC -> MODER |= (1 << (2*col+8));
		GPIOC -> ODR &= (1 << (col+4));
		systick_delay(20);
		row = GPIOC -> IDR & 0x0000000F;
	
		while (!(GPIOC->IDR & 0x01) | !(GPIOC->IDR & 0x02) | !(GPIOC->IDR & 0x04) | !(GPIOC->IDR & 0x08));
		if (row != 0x0F) break;
	}
	if (col == 3) return 0;

	if (row == 0x0E) num=col+0+1;
	else if (row == 0x0D) num=col+3+1;
	else if (row == 0x0B) num=col+6+1;
	else if (row == 0x07) num=col+9+1;
	return num;
}

void print_keys_serial(int key_val)
{
	char tstr;
	if (key_val == 10)
		sprintf(tstr, "*");
	else if (key_val == 11)
		sprintf(tstr, "0");
	else if (key_val == 12)
		sprintf(tstr, "#");
	else 
		sprintf(tstr, "%d", key_val);
	USART2_write(tstr);
	//USART2_write("\n\r");
}

char print_keys_str(int key_val)
{
	char tstr;
	if (key_val == 10)
		sprintf(tstr, "*");
	else if (key_val == 11)
		sprintf(tstr, "0");
	else if (key_val == 12)
		sprintf(tstr, "#");
	else 
		sprintf(tstr, "%d", key_val);
	return tstr;

}
