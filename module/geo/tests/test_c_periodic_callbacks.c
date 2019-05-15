#include "unity.h"

#include "c_periodic_callbacks.h"
#include <stdbool.h>
#include <stdint.h>
//#include "Mockuartwrapper.h"
//#include <stdio.h>
#include "Mockcan.h"
#include "Mockgeo_can.h"

#include "Mockgps.h"
#include "queue.h"

//can_t geo_module = {0};
queue_S queue;
uint32_t count = 0;
//can_t geo_module = {0};

void test_c_period_init(void)
{
    can_t geo_module = {0};
    can_initialization_Expect(&geo_module);
    gps_module_init_Expect();

    bool return_var = c_period_init();
    TEST_ASSERT_TRUE(return_var);

}

void test_c_period_reg_tlm(void)
{
    bool return_var = c_period_reg_tlm();
    TEST_ASSERT_TRUE(return_var);

}

void test_c_period_1Hz(void)
{
    can_t geo_module = {0};
    send_heartbeat_msg_Expect(&geo_module);
    c_period_1Hz(count);
}

void test_c_period_10Hz(void)
{
    can_t geo_module = {0};
    GEO_COORDINATE_DATA_t geo_coordinate_data = {0};
    gps_obtain_and_process_data_Expect(count);
    send_can_msg_Expect(&geo_module, &geo_data);
    send_can_msg_to_bridge_Expect(&geo_module, &geo_coordinate_data);
    c_period_10Hz(count);
}
