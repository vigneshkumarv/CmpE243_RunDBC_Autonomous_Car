// LCD_wrapper.cpp

#include "LCD_wrapper.h"
#include "io.hpp"

void lcd_set_num(int num)
{
    LD.setNumber(num);
}
