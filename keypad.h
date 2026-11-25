#ifndef KEYPAD_H
#define KEYPAD_H

#include <stm32f446xx.h>

void keypad_setup(void);
int read_keypad(void);
void print_keys_serial(int key_val);
char print_keys_str(int key_val);

#endif
