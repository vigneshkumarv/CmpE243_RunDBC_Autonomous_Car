/*
 * c_periodic_callbacks.c
 *
 *  Created on: Feb 16, 2019
 *      Author: reldn_000
 */

#include "c_periodic_callbacks.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>


bool c_period_init(void)
{
    init_can_bus();
    return true;
}

bool c_period_reg_tlm(void)
{
    return true;
}

void c_period_1Hz(uint32_t count)
{

    (void) count;
}
void c_period_10Hz(uint32_t count)
{
    (void) count;

    call_at_10Hz();

}

void c_period_100Hz(uint32_t count)
{

    (void) count;

}
void c_period_1000Hz(uint32_t count)
{
    /* NOTE: by default this function is not called.
     * You must enable it in main.cpp by setting
     * const bool run_1Khz = true;*/
    (void) count;
}

