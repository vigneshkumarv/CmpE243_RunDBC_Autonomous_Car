// can_helpers.c

#include "can_helpers.h"
#include <can.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "LED_wrapper.h"
#include "generated_can.h"
#include "motor_helpers.h"
#include "pwm_wrapper.h"
#include "speed_control.h"

const uint32_t MASTER_HEARTBEAT__MIA_MS = 3000;
const MASTER_HEARTBEAT_t MASTER_HEARTBEAT__MIA_MSG = {.MASTER_HEARTBEAT_cmd = 1};

const uint32_t MASTER_DRIVE_CMD__MIA_MS = 3000;
const MASTER_DRIVE_CMD_t MASTER_DRIVE_CMD__MIA_MSG = {
    .MASTER_DRIVE_CMD_steer = 0, .MASTER_DRIVE_CMD_speed = 0.0, .MASTER_DRIVE_CMD_direction = stop_cmd};

void sendHeartbeat(void) {
  MOTOR_HEARTBEAT_t motor_heartbeat = {0};
  motor_heartbeat.MOTOR_HEARTBEAT_cmd = 0;
  dbc_encode_and_send_MOTOR_HEARTBEAT(&motor_heartbeat);
}

void send_Motor_Debug(void) {
  // m0
  MOTOR_DEBUG_m0_t m0 = {0};
  m0.MOTOR_DEBUG_rpm_partial = get_RPM_raw();
  m0.MOTOR_DEBUG_rpm_actual = get_RPM_act();
  dbc_encode_and_send_MOTOR_DEBUG_m0(&m0);

  // m1
  MOTOR_DEBUG_m1_t m1 = {0};
  m1.MOTOR_DEBUG_pi_error = get_RPM_raw();
  m1.MOTOR_DEBUG_large_error_cnt = check_for_large_error();
  dbc_encode_and_send_MOTOR_DEBUG_m1(&m1);

  // m2
  MOTOR_DEBUG_m2_t m2 = {0};
  m2.MOTOR_DEBUG_prop_cmd = get_prop_cmd();
  dbc_encode_and_send_MOTOR_DEBUG_m2(&m2);

  // m3
  MOTOR_DEBUG_m3_t m3 = {0};
  m3.MOTOR_DEBUG_int_cmd = get_int_cmd();
  dbc_encode_and_send_MOTOR_DEBUG_m3(&m3);

  // m4
  MOTOR_DEBUG_m4_t m4 = {0};
  speed_control_t speed_state = get_speed_state();
  m4.MOTOR_DEBUG_int_cmd_old = speed_state.int_cmd_old;
  dbc_encode_and_send_MOTOR_DEBUG_m4(&m4);

  // m5
  MOTOR_DEBUG_m5_t m5 = {0};
  m5.MOTOR_DEBUG_output = get_output();
  dbc_encode_and_send_MOTOR_DEBUG_m5(&m5);

  // m6
  MOTOR_DEBUG_m6_t m6 = {0};
  m6.MOTOR_DEBUG_pwm_act = get_pwm_act();
  dbc_encode_and_send_MOTOR_DEBUG_m6(&m6);
}

void send_Motor_Data(float speed_act, int steer_angle, MASTER_DRIVE_CMD_direction_E dir_cmd) {
  MOTOR_DATA_t motor_data = {0};
  motor_data.MOTOR_DATA_steer = steer_angle;
  motor_data.MOTOR_DATA_speed = speed_act;
  motor_data.MOTOR_DATA_direction = stop_act;
  switch (dir_cmd) {
    case (stop_cmd):
      motor_data.MOTOR_DATA_direction = stop_act;
      break;
    case (forward_cmd):
      motor_data.MOTOR_DATA_direction = forward_act;
      break;
    case (backward_cmd):
      motor_data.MOTOR_DATA_direction = backward_act;
      break;
  }
  dbc_encode_and_send_MOTOR_DATA(&motor_data);
}

void read_All_CAN_Messages(MASTER_DRIVE_CMD_t* rx_master_drive_msg, MASTER_HEARTBEAT_t* rx_master_heartbeat_msg) {
  can_msg_t can_msg;

  while (CAN_rx(can1, &can_msg, 0)) {
    dbc_msg_hdr_t can_msg_hdr;
    can_msg_hdr.mid = can_msg.msg_id;
    can_msg_hdr.dlc = can_msg.frame_fields.data_len;

    // Since you are providing the &can_msg_hdr, you don't have to use them
    // Only one will decode based on the message ID match
    dbc_decode_MASTER_DRIVE_CMD(rx_master_drive_msg, can_msg.data.bytes, &can_msg_hdr);
    dbc_decode_MASTER_HEARTBEAT(rx_master_heartbeat_msg, can_msg.data.bytes, &can_msg_hdr);
  }

  // handle MIAs
  // XXX: Increment MIA counters for all messages you handle above
  if (dbc_handle_mia_MASTER_DRIVE_CMD(rx_master_drive_msg, 100)) {
    LED_3_on();
  } else {
    LED_3_off();
  }

  if (dbc_handle_mia_MASTER_HEARTBEAT(rx_master_heartbeat_msg, 100)) {
    LED_2_on();
  } else {
    LED_2_off();
  }
}

void check_and_handle_canbus_state(void) {
  if (CAN_is_bus_off(can1)) {
    LED_1_on();
    CAN_reset_bus(can1);
  } else {
    LED_1_off();
  }
}

bool dbc_app_send_can_msg(uint32_t mid, uint8_t dlc, uint8_t bytes[8]) {
  can_msg_t can_msg = {0};
  can_msg.msg_id = mid;
  can_msg.frame_fields.data_len = dlc;
  memcpy(can_msg.data.bytes, bytes, dlc);
  return CAN_tx(can1, &can_msg, 0);
}

void init_can1_bus(void) {
  CAN_init(can1, 100, 32, 32, NULL, NULL);
  CAN_bypass_filter_accept_all_msgs();
  CAN_reset_bus(can1);
}
