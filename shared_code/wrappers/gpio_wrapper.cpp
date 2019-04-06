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

bool read_P2_1(void) // dont use an LED to read in parallel
{                    // but 330ohm pulldown is ok
    GPIO pin21(P2_0);
    pin21.setAsInput();
    return pin21.read();
}

void set_P2_1_High()
{
    GPIO pin21(P2_0);
    pin21.setAsOutput();
    pin21.setHigh();
}

void set_P2_1_Low()
{
    GPIO pin21(P2_0);
    pin21.setAsOutput();
    pin21.setLow();
}

bool read_P2_2(void) // dont use an LED to read in parallel
{                    // but 330ohm pulldown is ok
    GPIO pin22(P2_0);
    pin22.setAsInput();
    return pin22.read();
}

void set_P2_2_High()
{
    GPIO pin22(P2_0);
    pin22.setAsOutput();
    pin22.setHigh();
}

void set_P2_2_Low()
{
    GPIO pin22(P2_0);
    pin22.setAsOutput();
    pin22.setLow();
}

bool read_P2_3(void) // dont use an LED to read in parallel
{                    // but 330ohm pulldown is ok
    GPIO pin23(P2_3);
    pin23.setAsInput();
    return pin23.read();
}

void set_P2_3_High()
{
    GPIO pin23(P2_3);
    pin23.setAsOutput();
    pin23.setHigh();
}

void set_P2_3_Low()
{
    GPIO pin23(P2_3);
    pin23.setAsOutput();
    pin23.setLow();
}


