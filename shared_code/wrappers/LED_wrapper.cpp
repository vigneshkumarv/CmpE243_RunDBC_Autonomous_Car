// LED_wrapper.cpp

#include "io.hpp"
#include "LED_wrapper.h"

void LED_1_on(void)
{
    LE.on(1);
}

void LED_2_on(void)
{
    LE.on(2);
}

void LED_3_on(void)
{
    LE.on(3);
}

void LED_4_on(void)
{
    LE.on(4);
}

void LED_1_off(void)
{
    LE.off(1);
}

void LED_2_off(void)
{
    LE.off(2);
}

void LED_3_off(void)
{
    LE.off(3);
}

void LED_4_off(void)
{
    LE.off(4);
}
