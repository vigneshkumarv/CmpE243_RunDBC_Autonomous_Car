// motor_speed_assignment.c

#include "motor_speed_assignment.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "can.h"
#include "generated-can/generated_can.h"
//#include "LED_wrapper.h"
#include <stdio.h>
#include "LCD_wrapper.h"
#include <string.h> // n
#include "ls_wrapper.h" // n

// MOTOR_DATA_t motor_data = { 0 };
MASTER_SPEED_t rx_masterspeed_msg;

bool dbc_app_send_can_msg(uint32_t mid, uint8_t dlc, uint8_t bytes[8]) {
  can_msg_t can_msg = {0};
  can_msg.msg_id = mid;
  can_msg.frame_fields.data_len = dlc;
  memcpy(can_msg.data.bytes, bytes, dlc);
  return CAN_tx(can1, &can_msg, 0);
}

void init_can_bus(void) {
  CAN_init(can1, 100, 32, 32, NULL, NULL);
  CAN_bypass_filter_accept_all_msgs();
  CAN_reset_bus(can1);
}

void call_at_10Hz(void) {
  if (CAN_is_bus_off(can1)) {
    CAN_reset_bus(can1);
    printf("CAN1 bus had to be restarted\n");
  }

  // send LS data to master
  uint8_t light_per = ls_get_per();
  MOTOR_DATA_t motor_data = { 0 };
  motor_data.MOTOR_DATA_cmd = light_per;
  //dbc_encode_and_send_MOTOR_HEARTBEAT(&motor_data);
  dbc_encode_and_send_MOTOR_DATA(&motor_data); // n

  // receive speed data from master
  can_msg_t can_msg;
  int val = 99;
  while (CAN_rx(can1, &can_msg, 0)) {
    dbc_msg_hdr_t can_msg_hdr;
    can_msg_hdr.mid = can_msg.msg_id;
    can_msg_hdr.dlc = can_msg.frame_fields.data_len;
    dbc_decode_MASTER_SPEED(&rx_masterspeed_msg, can_msg.data.bytes, &can_msg_hdr);
    val = can_msg.data.qword;

    // LED_1_off();
    lcd_set_num(val);
  }
  lcd_set_num(val);
}
