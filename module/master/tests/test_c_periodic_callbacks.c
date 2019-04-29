#include "unity.h"

#include "Mockmaster_can.h"
#include "Mocknavigation.h"
#include "c_periodic_callbacks.h"

extern navigation_state_machine_S state_variables;
extern navigation_sensors_S sensor_data;
extern navigation_motor_cmd_S motor_command;
extern GEO_DATA_t geo_data;

void setUp(void) {}

void tearDown(void) {}

void test_c_period_init(void) {
  init_navigation_ExpectAnyArgs();
  init_can_ExpectAndReturn(true);
  TEST_ASSERT_TRUE(c_period_init());

  init_navigation_ExpectAnyArgs();
  init_can_ExpectAndReturn(false);
  TEST_ASSERT_FALSE(c_period_init());
}

void test_c_period_reg_tlm(void) { TEST_ASSERT_TRUE(c_period_reg_tlm()); }

void test_c_period_1Hz(void) {
  check_and_restart_can_Expect();
  send_heartbeat_msg_Expect();
  c_period_1Hz(100);
}

void test_c_period_10Hz(void) { c_period_10Hz(100); }

void test_c_period_100Hz(void) {
  c_period_100Hz(3);

  read_can_50Hz_ExpectAndReturn(&sensor_data, &geo_data, &state_variables, true);
  navigation_state_machine_ExpectAnyArgs();
  send_drive_cmd_Expect(motor_command);
  c_period_100Hz(38);
}

void test_c_period_1000Hz(void) { c_period_1000Hz(100); }
