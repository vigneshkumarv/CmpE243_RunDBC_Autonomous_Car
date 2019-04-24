#include "unity.h"

#include <string.h>
#include "MockLED_wrapper.h"
#include "Mockcan.h"
#include "Mockobstacle_avoidance.h"
#include "generated_can.h"
#include "master_can.h"

void setUp(void) {}

void tearDown(void) {}

void test_init_can(void) {
  CAN_init_ExpectAndReturn(can1, 100, 64, 64, NULL, NULL, true);
  CAN_reset_bus_Expect(can1);
  CAN_bypass_filter_accept_all_msgs_Expect();
  init_can();
}

void test_check_and_restart_can(void) {
  CAN_is_bus_off_ExpectAndReturn(can1, true);
  CAN_reset_bus_Expect(can1);
  check_and_restart_can();
  CAN_is_bus_off_ExpectAndReturn(can1, false);
  check_and_restart_can();
}

void test_read_can(void) {
  can_msg_t test_rx_msg = {0};

  for (int index = 0; index < 30; index++) {
    CAN_rx_ExpectAndReturn(can1, NULL, 0, false);
    CAN_rx_IgnoreArg_msg();
    //    if (index < 29){
    LED_1_off_Expect();
    LED_2_off_Expect();
    LED_3_off_Expect();
    LED_4_off_Expect();
    //    }
    TEST_ASSERT_TRUE(read_can());
  }
  CAN_rx_ExpectAndReturn(can1, NULL, 0, false);
  CAN_rx_IgnoreArg_msg();
  LED_1_on_Expect();
  LED_2_on_Expect();
  LED_3_on_Expect();
  LED_4_on_Expect();
  TEST_ASSERT_FALSE(read_can());

  test_rx_msg.msg_id = BRIDGE_HEARTBEAT_HDR.mid;
  test_rx_msg.frame_fields.data_len = BRIDGE_HEARTBEAT_HDR.dlc;
  CAN_rx_ExpectAndReturn(can1, NULL, 0, true);
  CAN_rx_IgnoreArg_msg();
  CAN_rx_ReturnMemThruPtr_msg(&test_rx_msg, sizeof(can_msg_t));

  test_rx_msg.msg_id = GEO_HEARTBEAT_HDR.mid;
  test_rx_msg.frame_fields.data_len = GEO_HEARTBEAT_HDR.dlc;
  CAN_rx_ExpectAndReturn(can1, NULL, 0, true);
  CAN_rx_IgnoreArg_msg();
  CAN_rx_ReturnMemThruPtr_msg(&test_rx_msg, sizeof(can_msg_t));

  test_rx_msg.msg_id = MOTOR_HEARTBEAT_HDR.mid;
  test_rx_msg.frame_fields.data_len = MOTOR_HEARTBEAT_HDR.dlc;
  CAN_rx_ExpectAndReturn(can1, NULL, 0, true);
  CAN_rx_IgnoreArg_msg();
  CAN_rx_ReturnMemThruPtr_msg(&test_rx_msg, sizeof(can_msg_t));

  test_rx_msg.msg_id = SENSOR_HEARTBEAT_HDR.mid;
  test_rx_msg.frame_fields.data_len = SENSOR_HEARTBEAT_HDR.dlc;
  CAN_rx_ExpectAndReturn(can1, NULL, 0, true);
  CAN_rx_IgnoreArg_msg();
  CAN_rx_ReturnMemThruPtr_msg(&test_rx_msg, sizeof(can_msg_t));

  CAN_rx_ExpectAndReturn(can1, NULL, 0, false);
  CAN_rx_IgnoreArg_msg();

  LED_4_off_Expect();

  TEST_ASSERT_TRUE(read_can());
}
