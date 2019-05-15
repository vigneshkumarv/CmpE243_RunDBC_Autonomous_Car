// test_can_helpers.c

#include "unity.h"

#include "MockLCD_wrapper.h"
#include "MockLED_wrapper.h"
#include "Mockcan.h"
#include "Mockeint.h"
#include "Mockgpio_wrapper.h"
#include "Mockpwm_wrapper.h"
#include "can_helpers.h"
#include "encoder.h"
#include "generated_can.h"
#include "motor_controls_master.h"
#include "motor_helpers.h"
#include "speed_control.h"

void test_sendHeartbeat(void) {
  can_msg_t can_msg;

  CAN_tx_ExpectAndReturn(can1, &can_msg, 0, true);
  CAN_tx_IgnoreArg_msg();

  sendHeartbeat();
}

void test_send_Motor_Debug(void) {
  can_msg_t can_msg;

  // 1
  CAN_tx_ExpectAndReturn(can1, &can_msg, 0, true);
  CAN_tx_IgnoreArg_msg();

  // 2
  CAN_tx_ExpectAndReturn(can1, &can_msg, 0, true);
  CAN_tx_IgnoreArg_msg();

  // 3
  CAN_tx_ExpectAndReturn(can1, &can_msg, 0, true);
  CAN_tx_IgnoreArg_msg();

  // 4
  CAN_tx_ExpectAndReturn(can1, &can_msg, 0, true);
  CAN_tx_IgnoreArg_msg();

  // 5
  CAN_tx_ExpectAndReturn(can1, &can_msg, 0, true);
  CAN_tx_IgnoreArg_msg();

  // 6
  CAN_tx_ExpectAndReturn(can1, &can_msg, 0, true);
  CAN_tx_IgnoreArg_msg();

  // 7
  CAN_tx_ExpectAndReturn(can1, &can_msg, 0, true);
  CAN_tx_IgnoreArg_msg();

  // 8
  CAN_tx_ExpectAndReturn(can1, &can_msg, 0, true);
  CAN_tx_IgnoreArg_msg();

  // 9
  CAN_tx_ExpectAndReturn(can1, &can_msg, 0, true);
  CAN_tx_IgnoreArg_msg();

  send_Motor_Debug();
}

void test_send_Motor_Data(void) {
  can_msg_t can_msg;

  CAN_tx_ExpectAndReturn(can1, &can_msg, 0, true);
  CAN_tx_IgnoreArg_msg();

  send_Motor_Data(1.0, 45);
}

void test_read_All_CAN_Messages(void) {
  MASTER_DRIVE_CMD_t rx_master_drive_msg;
  MASTER_HEARTBEAT_t rx_master_heartbeat_msg;

  can_msg_t can_msg;

  CAN_rx_ExpectAndReturn(can1, &can_msg, 0, true);
  CAN_rx_IgnoreArg_msg();

  CAN_rx_ExpectAndReturn(can1, &can_msg, 0, false);
  CAN_rx_IgnoreArg_msg();

  LED_1_off_Expect();
  // LED_2_off_Expect();

  read_All_CAN_Messages(&rx_master_drive_msg, &rx_master_heartbeat_msg);
}

void test_check_and_handle_canbus_state(void) {
  // can bus is off
  CAN_is_bus_off_ExpectAndReturn(can1, true);
  // LED_1_on_Expect();
  CAN_reset_bus_Expect(can1);
  check_and_handle_canbus_state();

  // can bus is on
  CAN_is_bus_off_ExpectAndReturn(can1, false);
  // LED_1_off_Expect();
  check_and_handle_canbus_state();
}

void test_init_can1_bus(void) {
  CAN_init_ExpectAndReturn(can1, 100, 32, 32, NULL, NULL, true);
  CAN_bypass_filter_accept_all_msgs_Expect();
  CAN_reset_bus_Expect(can1);

  init_can1_bus();
}
