// ls_wrapper.cpp

#include "ls_wrapper.h"
#include "io.hpp"

int ls_get_per(void)
{
    return Light_Sensor::getInstance().getPercentValue();
}

