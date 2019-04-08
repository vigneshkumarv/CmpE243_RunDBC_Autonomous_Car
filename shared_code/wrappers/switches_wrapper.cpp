// switches_wrapper.cpp

#include <stdbool.h>
#include "switches_wrapper.h"
#include "switches.hpp"
#include "io.hpp"

//uint8_t getSwitchValues(void) { }

bool init_switches(void)
{
    return SW.init();
}

bool getSwitch(int num)
{
    return SW.getSwitch(num);
}
