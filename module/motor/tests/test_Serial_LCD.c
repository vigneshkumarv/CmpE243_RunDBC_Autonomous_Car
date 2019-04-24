// test_Serial_LCD.c

#include "unity.h"

#include "Mockuart_wrapper.h"
#include "Mockutilities.h"
#include "Serial_LCD.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

void test_init_serial_lcd(void) {
  printf("hello world\n");
  init_serial_lcd();
}
