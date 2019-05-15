// motor_helpers.h
#ifndef _MOTOR_HELPERS_H
#define _MOTOR_HELPERS_H

#include <stdbool.h>
#include "generated_can.h"
#include "motor_controls_master.h"
#include "speed_control.h"

typedef enum {
  rev_state_1_of_4,
  rev_state_2_of_4,
  rev_state_3_of_4,
  rev_state_4_of_4,
  rev_state_normal,
} rev_state_E;

speed_control_t get_speed_state(void);
bool reverse_statemachine(void);
void steer_car(int steer_angle);
void move_car(MASTER_DRIVE_CMD_direction_E direction, float mps);
void init_speed_state(void);

#endif
