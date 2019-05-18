// Serial_LCD.h

#ifndef _SERIAL_LCD_H
#define _SERIAL_LCD_H


#include <stdint.h>
#include <stdbool.h>

void init_serial_lcd(void);
void clear_screen(void);
void clear_line(uint8_t line_num);

void print_line(uint8_t line_num, char* char_msg);
// clears line before printing

void print_seg(uint8_t line_num, uint8_t pos, char* char_msg, int len);
// char_msg will be truncated based on len
// or
// char_msg will be extended (with spaces) based on len

#endif
