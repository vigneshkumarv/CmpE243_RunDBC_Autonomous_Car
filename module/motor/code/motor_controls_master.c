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

void control_car_with_master(MASTER_DRIVE_CMD_t* rx_master_drive_msg) {
  // read drive command from master (get steer, speed, direction)
  // and do stuff
  // also determine target state (reverse or non-reverse)

  // from -45deg to +45deg
  steer_car(rx_master_drive_msg->MASTER_DRIVE_CMD_steer);

  // from 0-100 m/s
  move_car(rx_master_drive_msg->MASTER_DRIVE_CMD_direction, rx_master_drive_msg->MASTER_DRIVE_CMD_speed);
}
