#include "unity.h"

#include "Mockmaster_can.h"
#include "c_periodic_callbacks.h"

extern MASTER_DRIVE_CMD_t drive_data;

void setUp(void) {}

void tearDown(void) {}

void test_c_period_init(void) {
  init_can_ExpectAndReturn(true);
  TEST_ASSERT_TRUE(c_period_init());

  init_can_ExpectAndReturn(false);
  TEST_ASSERT_FALSE(c_period_init());
}

void test_c_period_reg_tlm(void) { TEST_ASSERT_TRUE(c_period_reg_tlm()); }

void test_c_period_1Hz(void) {
  check_and_restart_can_Expect();
  send_heartbeat_msg_Expect();
  c_period_1Hz(100);
}

void test_c_period_10Hz(void) {
  send_drive_cmd_Expect(&drive_data);
  read_can_ExpectAndReturn(true);
  c_period_10Hz(100);
}

void test_c_period_100Hz(void) { c_period_100Hz(100); }

void test_c_period_1000Hz(void) { c_period_1000Hz(100); }
