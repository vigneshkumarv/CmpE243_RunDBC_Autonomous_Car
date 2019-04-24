// test_can_helpers.c

#include "unity.h"

#include "MockLED_wrapper.h"
#include "Mockcan.h"
#include "Mockpwm_wrapper.h"
#include "can_helpers.h"
#include "generated_can.h"
#include "motor_controls_master.h"
#include "motor_helpers.h"

extern MASTER_DRIVE_CMD_t rx_master_drive_msg;

void test_read_Master_Drive_Cmd(void) {
  can_msg_t can_msg;

  CAN_rx_ExpectAndReturn(can1, &can_msg, 0, true);
  CAN_rx_IgnoreArg_msg();

  CAN_rx_ExpectAndReturn(can1, &can_msg, 0, false);
  CAN_rx_IgnoreArg_msg();

  if (dbc_handle_mia_MASTER_DRIVE_CMD(&rx_master_drive_msg, 100)) {
    LED_3_on_Expect();
    Set_PWM_for_DC_ExpectAndReturn(15.0, true);
  }

  read_Master_Drive_Cmd();
}

void test_check_and_handle_canbus_state(void) {
  // can bus is off
  CAN_is_bus_off_ExpectAndReturn(can1, true);
  LED_1_on_Expect();
  CAN_reset_bus_Expect(can1);
  check_and_handle_canbus_state();

  // can bus is on
  CAN_is_bus_off_ExpectAndReturn(can1, false);
  LED_1_off_Expect();
  check_and_handle_canbus_state();
}

void test_init_can1_bus(void) {
  CAN_init_ExpectAndReturn(can1, 100, 32, 32, NULL, NULL, true);
  CAN_bypass_filter_accept_all_msgs_Expect();
  CAN_reset_bus_Expect(can1);

  init_can1_bus();
}
