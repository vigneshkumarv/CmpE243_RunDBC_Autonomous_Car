#include "unity.h"
#include "Mockcan.h"
#include "Can_lab.h"
#include "C:\Users\9595v\Desktop\autonomous-car\shared_code\wrappers\ls_wrapper.h"
#include <stdbool.h>
#include <stdint.h>

void test_Geo_CAN_initialize(void)
{
CAN_init_ExpectAndReturn(can1, 100, 10, 10, NULL, NULL, true);
Geo_CAN_initialize(void);
}


void test_Geo_CAN_transmit(void)
{
	CAN_tx_ExpectAndReturn(can1, NULL, 0, true);
    CAN_tx_IgnoreArg_msg();
    Geo_CAN_transmit(void);
}


void test_Geo_CAN_reset(void)
{
	CAN_is_bus_off_ExpectAndReturn(can1, true);
	CAN_reset_bus_Expect(can1);
	Geo_CAN_reset(void);
}

void test_Geo_LS_percentage_data(void)
{
	ls_get_per_Expect();
	Geo_LS_percentage_data(void);
}
