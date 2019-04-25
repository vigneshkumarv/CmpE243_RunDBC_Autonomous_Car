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

can_t geo_module = {0};
queue_S queue;

void test_c_period_init(void)
{
    can_initialization_Expect(&geo_module);
    gps_module_init_Expect();

    TEST_ASSERT_TRUE(c_period_init());
    TEST_ASSERT_EQUAL_INT(0, queue.front);
    TEST_ASSERT_EQUAL_INT(-1, queue.rear);
    TEST_ASSERT_EQUAL_INT(0, queue.size);
}
