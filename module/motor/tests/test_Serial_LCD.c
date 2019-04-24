// test_Serial_LCD.c

#include "unity.h"

#include "Serial_LCD.h"
#include "Mockutilities.h"
#include "Mockuart_wrapper.h"
#include "string.h"
#include "stdlib.h"
#include "stdio.h"


void test_init_serial_lcd(void)
{

    printf("hello world\n");
    init_serial_lcd();
}
