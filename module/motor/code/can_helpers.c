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
  // rpm_partial - 1
  MOTOR_DEBUG_RPM_PARTIAL_t rpm_part = {0};
  rpm_part.MOTOR_DEBUG_rpm_part = get_RPM_raw();
  dbc_encode_and_send_MOTOR_DEBUG_RPM_PARTIAL(&rpm_part);

  // rpm_act - 2
  MOTOR_DEBUG_RPM_ACTUAL_t rpm_act = {0};
  rpm_act.MOTOR_DEBUG_rpm_act = get_RPM_act();
  dbc_encode_and_send_MOTOR_DEBUG_RPM_ACTUAL(&rpm_act);

  // pi error - 3
  MOTOR_DEBUG_PI_ERROR_t pi_err = {0};
  pi_err.MOTOR_DEBUG_pi_err = get_pi_error();
  dbc_encode_and_send_MOTOR_DEBUG_PI_ERROR(&pi_err);

  // lg_err_cnt - 4
  MOTOR_DEBUG_LARGE_ERROR_CNT_t lg_err_cnt = {0};
  lg_err_cnt.MOTOR_DEBUG_lg_err_cnt = check_for_large_error();
  dbc_encode_and_send_MOTOR_DEBUG_LARGE_ERROR_CNT(&lg_err_cnt);

  // prop_cmd - 5
  MOTOR_DEBUG_PROPORTIONAL_CMD_t prop_cmd = {0};
  prop_cmd.MOTOR_DEBUG_prop_cmd = get_prop_cmd();
  dbc_encode_and_send_MOTOR_DEBUG_PROPORTIONAL_CMD(&prop_cmd);

  // int_cmd - 6
  MOTOR_DEBUG_INTEGRAL_CMD_t int_cmd = {0};
  int_cmd.MOTOR_DEBUG_int_cmd = get_int_cmd();
  dbc_encode_and_send_MOTOR_DEBUG_INTEGRAL_CMD(&int_cmd);

  // int_cmd_old - 7
  MOTOR_DEBUG_INTEGRAL_CMD_OLD_t int_cmd_old = {0};
  speed_control_t speed_state = get_speed_state();
  int_cmd_old.MOTOR_DEBUG_int_cmd_old = speed_state.int_cmd_old;
  dbc_encode_and_send_MOTOR_DEBUG_INTEGRAL_CMD_OLD(&int_cmd_old);

  // output - 8
  MOTOR_DEBUG_OUTPUT_t out = {0};
  out.MOTOR_DEBUG_out = get_output();
  dbc_encode_and_send_MOTOR_DEBUG_OUTPUT(&out);

  // pwm_act - 9
  MOTOR_DEBUG_PWM_ACTUAL_t pwm_act = {0};
  pwm_act.MOTOR_DEBUG_pwm_act = get_pwm_act();
  dbc_encode_and_send_MOTOR_DEBUG_PWM_ACTUAL(&pwm_act);
}

void send_Motor_Data(float speed_act, int steer_angle) {
  MOTOR_DATA_t motor_data = {0};

  if (speed_act < 0)
  {
      motor_data.MOTOR_DATA_direction = backward_act;
      speed_act *= -1;
  }
  else if (speed_act > 0)
  {
      motor_data.MOTOR_DATA_direction = forward_act;
  }
  else
  {
      motor_data.MOTOR_DATA_direction = stop_act;
  }
  motor_data.MOTOR_DATA_steer = steer_angle;
  motor_data.MOTOR_DATA_speed = speed_act;

  dbc_encode_and_send_MOTOR_DATA(&motor_data);
}

void read_All_CAN_Messages(MASTER_DRIVE_CMD_t* rx_master_drive_msg,
                           MASTER_HEARTBEAT_t* rx_master_heartbeat_msg)
{
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
    //LED_3_on();
    LED_1_on();
  } else {
    //LED_3_off();
    LED_1_off();
  }

  if (dbc_handle_mia_MASTER_HEARTBEAT(rx_master_heartbeat_msg, 100)) {
    //LED_2_on();
  } else {
    //LED_2_off();
  }
}

void check_and_handle_canbus_state(void) {
  if (CAN_is_bus_off(can1)) {
    //LED_1_on();
    CAN_reset_bus(can1);
  } else {
    //LED_1_off();
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

