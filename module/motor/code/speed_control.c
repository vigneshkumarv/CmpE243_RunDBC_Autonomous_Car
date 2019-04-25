// speed_control.c

#include <stdbool.h>
#include <stdio.h>

#include "LCD_wrapper.h"
#include "LED_wrapper.h"
#include "encoder.h"
#include "speed_control.h"

const float TIRE_DIA_IN_METERS = 0.1061;
const float GEAR_RATIO = 16.0 / 90.0;  // 16-T?
const float pulses_per_rev = 64.0;
const int MAX_LARGE_ERROR_CNT = 5;
const float INT_SAT = 100;
const float OUTPUT_SAT = 30;

static float ret = 0.0;
static float output = 0.0;
static float int_cmd = 0.0;
static float prop_cmd = 0.0;
static float RPM_act = 0.0;
static float RPM_raw = 0.0;
static int large_error_cnt = 0;
static float pi_error = 0.0;
static float proportional_gain = 10.0;
static float integral_gain = 5.0;
static float speed_act = 0.0;

float get_pwm_act(void) { return ret; }

float get_output(void) { return output; }

float get_int_cmd(void) { return int_cmd; }

float get_prop_cmd(void) { return prop_cmd; }

float get_pi_error(void) { return pi_error; }

float get_RPM_act(void) { return RPM_act; }

float get_RPM_raw(void) { return RPM_raw; }

float getSpeedAct(void) { return speed_act; }

float final_pwm_safety_check(float pwm) {
  if (pwm >= 20.0) {
    LED_4_on();
    return 15.0;
  } else if (pwm <= 10.0) {
    LED_4_on();
    return 15.0;
  } else {
    LED_4_off();
    return pwm;
  }
}

int check_for_large_error(void) {
  if ((pi_error > 0.5) || (pi_error < -0.5))
    large_error_cnt++;
  else
    large_error_cnt = 0;

  return large_error_cnt;
}

float get_RPM_from_MPS(float meters_per_sec) {
  float meters_per_rev = 3.14 * TIRE_DIA_IN_METERS;
  float seconds_per_min = 60.0;
  float rev_per_meter = 1.0 / meters_per_rev;
  float meters_per_min = meters_per_sec * seconds_per_min;
  float rev_per_min = rev_per_meter * meters_per_min;
  return rev_per_min;
}

float get_actual_speed_from_rpm(float rev_per_min) {
  lcd_set_num((int)rev_per_min);

  float sec_per_min = 60.0;
  float meters_per_rev = 3.14 * TIRE_DIA_IN_METERS;
  float rev_per_sec = rev_per_min / sec_per_min;
  float meters_per_sec = rev_per_sec * meters_per_rev;
  return meters_per_sec;
}

float get_RPM_raw_10Hz(void)  // only be called from 1 place
{
  int encoder_count = get_encoder_count();
  float rpm = (((encoder_count) / (pulses_per_rev)) / 0.1) * 60;
  encoder_count = 0;
  return rpm;
}

float get_pwm_for_speed_control(speed_control_t *speed_state_ptr) {
  float speed_cmd = speed_state_ptr->meters_per_sec_cmd;
  RPM_raw = get_RPM_raw_10Hz();
  RPM_act = GEAR_RATIO * RPM_raw;  // multiply by gear ratio
  speed_act = get_actual_speed_from_rpm(RPM_act);
  pi_error = speed_cmd - speed_act;
  check_for_large_error();
  if (large_error_cnt > MAX_LARGE_ERROR_CNT) {
    // LED_4_on();
    return 15.0;
  } else {
    // LED_4_off();
  }
  prop_cmd = pi_error * proportional_gain;
  int_cmd = pi_error * integral_gain;
  int_cmd += speed_state_ptr->int_cmd_old;
  if (int_cmd > INT_SAT) {
    int_cmd = 100;
  }
  output = int_cmd + prop_cmd;
  if (output > OUTPUT_SAT) {
    output = 30;
    // LED_4_on();
  } else if (output < 0) {
    output = 0;
    // LED_4_on();
  } else {
    // LED_4_off();
  }

  speed_state_ptr->int_cmd_old = int_cmd;

  if (speed_state_ptr->isBackward == true) output *= -1;

  float pre_ret = 15.0 + (output / 20.0);
  ret = final_pwm_safety_check(pre_ret);
  return ret;
}
