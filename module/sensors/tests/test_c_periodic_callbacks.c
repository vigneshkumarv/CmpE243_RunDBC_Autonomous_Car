#include "unity.h"
#include "c_periodic_callbacks.h"
#include "Mockls_wrapper.h"
#include "Mockcan.h"
#include "Mocklight_sensor_read_and_send.h"

void setUp(void) {}

void tearDown(void) {}

void test_c_period_init(void) {
  // Test Case: CAN_init is true
  CAN_init_ExpectAndReturn(can1, 100, 64, 64, (void *)0, (void *)0, true);
  CAN_init_IgnoreArg_can();
  CAN_init_IgnoreArg_bus_off_cb();
  CAN_init_IgnoreArg_data_ovr_cb();
  
  CAN_bypass_filter_accept_all_msgs_Expect();
  CAN_reset_bus_Expect(can1);
  CAN_reset_bus_IgnoreArg_can();
  c_period_init();

}

void test_c_period_reg_tlm(void) { TEST_ASSERT_TRUE(c_period_reg_tlm()); }

void test_c_period_1Hz(void) { c_period_1Hz(0); }

void test_c_period_10Hz(void) {
  light_sensor_read_and_send_Expect();
  c_period_10Hz(0);
}

void test_c_period_100Hz(void) { c_period_100Hz(0); }

void test_c_period_1000Hz(void) { c_period_1000Hz(0); }
