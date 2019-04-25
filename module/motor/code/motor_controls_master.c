// motor_controls_master.c

#include "motor_controls_master.h"
#include <can.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include "LED_wrapper.h"
#include "can_helpers.h"
#include "generated_can.h"
#include "motor_helpers.h"
#include "pwm_wrapper.h"
#include "speed_control.h"

static int steer_angle = 0;  // 0 for straight, -128 for full left, 127 for full right
static float mps = 0.0;
static uint8_t direction_raw = 0;  // 0 for stop, 1 for forward, 2 for reverse

MASTER_DRIVE_CMD_t rx_master_drive_msg;

void control_car_with_master(void) {
  // read drive command from master (get steer, speed, direction)
  // and do stuff
  // also determine target state (reverse or non-reverse)

  read_All_CAN_Messages(&rx_master_drive_msg);
  // handles MIAs and...
  //  - updates rx_master_drive_msg

  // from -45deg to +45deg
  steer_angle = rx_master_drive_msg.MASTER_DRIVE_CMD_steer;

  // from 0-100 m/s
  mps = rx_master_drive_msg.MASTER_DRIVE_CMD_speed;

  // stop (0), forward (1), backward (2)
  direction_raw = rx_master_drive_msg.MASTER_DRIVE_CMD_direction;
  direction_E direction = get_direction(direction_raw);

  steer_car(steer_angle);
  move_car(direction, mps);

  float speed_act = getSpeedAct();
  send_Motor_Data(speed_act, steer_angle, direction_raw);  // goes to Master and Bridge
  send_Motor_Debug();
}
