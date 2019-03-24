// ls_wrapper.cpp

#include "ls_wrapper.h"
#include "io.hpp"


uint8_t ls_get_per(void)
{
    return Light_Sensor::getInstance().getPercentValue();
}

uint16_t ls_get_raw(void)
{
    return Light_Sensor::getInstance().getRawValue();
}
