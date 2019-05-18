// test_Serial_LCD.c

#include "unity.h"

#include <stdio.h>
#include <stdlib.h>
//#include "Mockstdint.h"
#include <string.h>
//#include <stdint.h>
//#include <utilities.h>
#include "Mockutilities.h"

#include "Mockuart_wrapper.h"
#include "Serial_LCD.h"

void test_print_seg(void) {
  uart2_putLine_CMockExpect(1, "$GOTO:0:0", 0);
  uart2_putLine_CMockExpect(1, "initial position", 0);
  print_seg(0, 0, "initial position", 16);

  uart2_putLine_CMockExpect(1, "$GOTO:5:1", 0);
  uart2_putLine_CMockExpect(1, "in the middle", 0);
  print_seg(1, 5, "in the middle", 13);

  uart2_putLine_CMockExpect(1, "$GOTO:16:2", 0);
  uart2_putLine_CMockExpect(1, "hi  ", 0);
  print_seg(2, 16, "hi  ", 4);

  uart2_putLine_CMockExpect(1, "$GOTO:18:3", 0);
  uart2_putLine_CMockExpect(1, "bye", 0);
  print_seg(3, 18, "bye", 3);
}

void test_print_line(void) {
  uart2_putLine_CMockExpect(1, "$CLR_LINE:0", 0);
  uart2_putLine_CMockExpect(1, "$GOTO:0:0", 0);
  uart2_putLine_CMockExpect(1, "hello world", 0);
  print_line(0, "hello world");

  uart2_putLine_CMockExpect(1, "$CLR_LINE:1", 0);
  uart2_putLine_CMockExpect(1, "$GOTO:0:1", 0);
  uart2_putLine_CMockExpect(1, "this is line 1", 0);
  print_line(1, "this is line 1");

  uart2_putLine_CMockExpect(1, "$CLR_LINE:2", 0);
  uart2_putLine_CMockExpect(1, "$GOTO:0:2", 0);
  uart2_putLine_CMockExpect(1, "this is line 2", 0);
  print_line(2, "this is line 2");

  uart2_putLine_CMockExpect(1, "$CLR_LINE:3", 0);
  uart2_putLine_CMockExpect(1, "$GOTO:0:3", 0);
  uart2_putLine_CMockExpect(1, "this is the bottom line", 0);
  print_line(3, "this is the bottom line");
}

void test_clear_line(void) {
  uart2_putLine_CMockExpect(1, "$CLR_LINE:0", 0);
  clear_line(0);

  uart2_putLine_CMockExpect(1, "$CLR_LINE:1", 0);
  clear_line(1);

  uart2_putLine_CMockExpect(1, "$CLR_LINE:2", 0);
  clear_line(2);

  uart2_putLine_CMockExpect(1, "$CLR_LINE:3", 0);
  clear_line(3);
}

void test_clear_screen(void) {
  uart2_putLine_CMockExpect(1, "$CLR_SCR", 0);
  clear_screen();
}

void test_init_serial_lcd(void) {
  uart2_init_ExpectAndReturn(38400, 32, 32, true);

  delay_ms_Expect(100);

  uart2_putChar_ExpectAndReturn(0xF0, 0, true);

  delay_ms_Expect(100);

  uart2_putLine_CMockExpect(1, "$BLIGHT:100", 0);

  init_serial_lcd();
}
