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

  // XXX: This should be moved outside of this function because we want to modularize things
  // So in your period, call 'read_all_msgs()' and then 'run_control_loop()'
  read_All_CAN_Messages(&rx_master_drive_msg);
  // handles MIAs and...
  //  - updates rx_master_drive_msg

  // from -45deg to +45deg
  // XXX: Code clarity is always the right priority
  // so don't try to shorten variables because the code should be written
  // for the reader not the writer
  // So I would not even have these 'shadow copy' variables
  steer_angle = rx_master_drive_msg.MASTER_DRIVE_CMD_steer;

  // from 0-100 m/s
  // xxx better to call it out "requested_drive_speed_meters_per_sec"
  mps = rx_master_drive_msg.MASTER_DRIVE_CMD_speed;

  // stop (0), forward (1), backward (2)
  // XXX code should not be subtitles, and you should not need the comment above
  // if you use enums in dbc, then you won't need all this
  // Add an attribute to your dbc and it will generate enums for you
  direction_raw = rx_master_drive_msg.MASTER_DRIVE_CMD_direction;
  direction_E direction = get_direction(direction_raw);

  steer_car(steer_angle);
  move_car(direction, mps);

  float speed_act = getSpeedAct();

  // xxx Try to take this out of the function
  send_Motor_Data(speed_act, steer_angle, direction_raw);  // goes to Master and Bridge
  send_Motor_Debug();
}
