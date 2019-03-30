// gpio_wrapper.cpp

#include "gpio_wrapper.h"
#include "gpio.hpp"

bool read_P2_0(void) // dont use an LED to read in parallel
{                    // but 330ohm pulldown is ok
    GPIO pin20(P2_0);
    pin20.setAsInput();
    return pin20.read();
}

void set_P2_0_High()
{
    GPIO pin20(P2_0);
    pin20.setAsOutput();
    pin20.setHigh();
}

void set_P2_0_Low()
{
    GPIO pin20(P2_0);
    pin20.setAsOutput();
    pin20.setLow();
}


