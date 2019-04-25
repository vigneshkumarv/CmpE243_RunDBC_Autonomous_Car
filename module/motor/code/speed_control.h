// speed_control.h
#ifndef _SPEED_CONTROL_H
#define _SPEED_CONTROL_H

#include <stdbool.h>

typedef struct {
  float meters_per_sec_cmd;
  float int_cmd_old;
  bool isBackward;
} speed_control_t;

float get_pwm_act(void);
float get_output(void);
float get_int_cmd(void);
float get_prop_cmd(void);
float get_pi_error(void);
float get_RPM_act(void);
float get_RPM_raw(void);
float getSpeedAct(void);

float final_pwm_safety_check(float pwm);
float get_RPM_from_MPS(float mps);
float get_actual_speed_from_rpm(float rev_per_min);
float get_RPM_raw_10Hz(void);
float get_pwm_for_speed_control(speed_control_t *speed_state);
int check_for_large_error(void);

#endif  // _SPEED_CONTROL_H
