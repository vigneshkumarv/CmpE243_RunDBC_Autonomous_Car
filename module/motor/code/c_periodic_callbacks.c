/*
 * c_periodic_callbacks.c
 *
 *  Created on: Feb 16, 2019
 *      Author: reldn_000
 */

#include "c_periodic_callbacks.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include "generated_can/generated_can.h"

<<<<<<< module/motor/code/c_periodic_callbacks.c
#include "pwm_wrapper.h"
//#include "lpc_pwm.hpp"
#include "motor_controls_switch.h"
//#include "motor_controls_master.h"
#include "heartbeats.h"
#include "tune_motor_ls.h"

static int motor_speed_RPM = 0;
extern int encoder_count;
static float speed;

bool c_period_init(void) {
  // init_can_bus();
  pwm2_init();
  speed = 15.0;
  tune_motor_ls(speed);
  init_can1_bus();
  return true;
}

bool c_period_reg_tlm(void) { return true; }

void c_period_1Hz(uint32_t count) {
  (void)count;
  check_and_handle_canbus_state();
  handle_heartbeats();

  // tune_motor_ls();
}
void c_period_10Hz(uint32_t count) {
  (void)count;

  // read encoder
  motor_speed_RPM = (((encoder_count) / (64.0)) / 0.1) * 60;
  printf("encoder_count: %d    motor_speed_RPM = %d \n", encoder_count, motor_speed_RPM);
  encoder_count = 0;

  control_car_with_switches();
  // control_car_with_master();
}
=======
bool c_period_init(void) { return true; }

bool c_period_reg_tlm(void) { return true; }

void c_period_1Hz(uint32_t count) { (void)count; }
void c_period_10Hz(uint32_t count) { (void)count; }
>>>>>>> module/motor/code/c_periodic_callbacks.c

void c_period_100Hz(uint32_t count) {  // 1/100 = 0.01 sec = 10ms
  (void)count;
}
void c_period_1000Hz(uint32_t count) {
  /* NOTE: by default this function is not called.
   * You must enable it in main.cpp by setting
   * const bool run_1Khz = true;*/
  (void)count;
}
