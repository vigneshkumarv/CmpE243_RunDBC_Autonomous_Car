// Serial_LCD.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "uart_wrapper.h"
#include "utilities.h"

void init_serial_lcd(void) {
  // configure UART port
  uart2_init(38400, 32, 32);

  // wait 100ms
  delay_ms(100);

  // send 0xF0
  char init_char = 0xF0;
  uart2_putChar(init_char, 0);

  // wait 100ms
  delay_ms(100);

  char* brightness = "$BLIGHT:100";
  uart2_putLine(brightness, 0);
}

void clear_screen(void) {
  char* msg = "$CLR_SCR";
  uart2_putLine(msg, 0);
}

void clear_line(uint8_t line_num) {
  char* line_select;
  switch (line_num) {
    case (0):
      line_select = "$CLR_LINE:0";
      break;
    case (1):
      line_select = "$CLR_LINE:1";
      break;
    case (2):
      line_select = "$CLR_LINE:2";
      break;
    case (3):
      line_select = "$CLR_LINE:3";
      break;
    default:
      line_select = "$CLR_LINE:0";
  }
  uart2_putLine(line_select, 0);
}

void print_line(uint8_t line_num, char* char_msg) {
  char* line_select;
  switch (line_num) {
    case (0):
      clear_line(0);
      line_select = "$GOTO:0:0";
      break;
    case (1):
      clear_line(1);
      line_select = "$GOTO:0:1";
      break;
    case (2):
      clear_line(2);
      line_select = "$GOTO:0:2";
      break;
    case (3):
      clear_line(3);
      line_select = "$GOTO:0:3";
      break;
    default:
      clear_line(0);
      line_select = "$GOTO:0:0";
  }
  uart2_putLine(line_select, 0);
  uart2_putLine(char_msg, 0);
}

void print_seg(uint8_t line_num, uint8_t pos, char* char_msg, int len) {
  char buf[20] = "$GOTO:";

  char pos_char[3];
  sprintf(pos_char, "%d", pos);
  // itoa(pos, pos_char, 10);
  strcat(buf, pos_char);

  strcat(buf, ":");

  char line_char[3];
  sprintf(line_char, "%d", line_num);
  // itoa(line_num, line_char, 10);
  strcat(buf, line_char);

  uart2_putLine(buf, 0);

  int i;
  for (i = 0; i < (int16_t)strlen(char_msg); i++) {
    if (i >= len)  // in case length is shorter than string, truncate it
    {
      buf[i] = '\0';
      uart2_putLine(buf, 0);
      return;
    }
    buf[i] = char_msg[i];
  }

  for (i = strlen(char_msg); i < len; i++) {
    buf[i] = ' ';
  }
  buf[i] = '\0';

  uart2_putLine(buf, 0);
}
