#include "Mockcan.h"
#include "motor_speed_assignment.h"
#include "unity.h"

//#include "can.h"
#include <stdbool.h>
#include "MockLCD_wrapper.h"
#include "Mockls_wrapper.h"
#include "generated-can/generated_can.h"

MASTER_SPEED_t rx_masterspeed_msg;

void setUp(void) {}

void tearDown(void) {}

void test_init_can_bus(void) {
  CAN_init_ExpectAndReturn(can1, 100, 32, 32, NULL, NULL, true);
  CAN_bypass_filter_accept_all_msgs_Expect();
  CAN_reset_bus_Expect(can1);
  init_can_bus();
}

void test_call_at_10Hz(void) {
  // TEST_ASSERT_TRUE(c_period_init());
  CAN_is_bus_off_ExpectAndReturn(can1, false);
  // CAN_reset_bus_Expect(can1);

  ls_get_per_ExpectAndReturn(50);
  MOTOR_DATA_t motor_data = {0};
  motor_data.MOTOR_DATA_cmd = 50;
  can_msg_t can_msg = {0};
  CAN_tx_ExpectAndReturn(can1, &can_msg, 0, true);
  CAN_tx_IgnoreArg_msg();
  dbc_encode_and_send_MOTOR_DATA(&motor_data);

  CAN_tx_ExpectAndReturn(can1, &can_msg, 0, true);
  CAN_tx_IgnoreArg_msg();

  CAN_rx_ExpectAndReturn(can1, &can_msg, 0, true);
  CAN_rx_IgnoreArg_msg();
  dbc_msg_hdr_t can_msg_hdr;
  can_msg_hdr.mid = can_msg.msg_id;
  can_msg_hdr.dlc = can_msg.frame_fields.data_len;
  dbc_decode_MASTER_SPEED(&rx_masterspeed_msg, can_msg.data.bytes, &can_msg_hdr);
  lcd_set_num_Expect(50);
  lcd_set_num_IgnoreArg_num();

  CAN_rx_ExpectAndReturn(can1, &can_msg, 0, false);
  CAN_rx_IgnoreArg_msg();
  lcd_set_num_Expect(50);
  lcd_set_num_IgnoreArg_num();

  call_at_10Hz();
}
