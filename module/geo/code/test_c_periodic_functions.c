#include "unity.h"
#include <stdbool.h>
#include <stdio.h>
#include "c_periodic_callbacks.h"
#include "can.h"
#include "Can_lab.h"
#include "C:\Users\9595v\Desktop\autonomous-car\shared_code\wrappers\ls_wrapper.h"
#include <stdint.h>

void setUp(void)
{
}

void tearDown(void)
{
}

void test_c_period_init(void)
{
    Geo_CAN_initialize_Expect();
	CAN_reset_bus(can1)_Expect();
    c_period_init();
}
/*
void test_c_period_reg_tlm(void)
{
    c_period_reg_tlm();
}
*/

void test_c_period_1Hz(void)
{
    Geo_CAN_reset()_Expect;
    c_period_1Hz(0);
}


void test_c_period_10Hz(void)
{
    
	Geo_CAN_transmit_Expect();
    c_period_10Hz(0);
}

/*
void test_c_period_100Hz(void)
{

}

void test_c_period_1000Hz(void)
{
}