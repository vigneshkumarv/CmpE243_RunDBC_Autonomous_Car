// obstacle_avoidance.c

#include "obstacle_avoidance.h"

#include <stdbool.h>
#include <stdint.h>

static const uint8_t steer_threshold_cm = 65;
static const uint16_t front_stop_threshold_cm = 30;
static const uint16_t front_slow_threshold_cm = 55;

bool forward_avoidance(obstacle_avoidance_S* sense_and_command) {
  bool ok_to_go_forward = true;
  sense_and_command->motor_direction = 1;
  if (sense_and_command->left_ultrasonic_cm < steer_threshold_cm) {
    sense_and_command->motor_speed = 17;
    if (sense_and_command->right_ultrasonic_cm <= sense_and_command->left_ultrasonic_cm) {
      sense_and_command->steer_direction = -20;
    } else {
      sense_and_command->steer_direction = 20;
    }
  } else if (sense_and_command->right_ultrasonic_cm < steer_threshold_cm) {
    sense_and_command->motor_speed = 17;
    sense_and_command->steer_direction = -20;
  } else {
    sense_and_command->motor_speed = 17;
    sense_and_command->steer_direction = 0;
  }

  if (sense_and_command->middle_ultrasonic_cm < front_stop_threshold_cm) {
    sense_and_command->steer_direction = 0;
    sense_and_command->motor_direction = 0;
    sense_and_command->motor_speed = 0;
    ok_to_go_forward = false;
  } else if (sense_and_command->middle_ultrasonic_cm < front_slow_threshold_cm) {
    sense_and_command->steer_direction = 20;
    sense_and_command->motor_direction = 1;
    sense_and_command->motor_speed = 17;
  }

  return ok_to_go_forward;
}
