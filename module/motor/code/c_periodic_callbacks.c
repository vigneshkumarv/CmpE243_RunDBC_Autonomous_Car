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
//#include "motor_drive.h"

#include "pwm_wrapper.h"
//#include "lpc_pwm.hpp"
#include "tune_motor_ls.h"

static float speed;

bool c_period_init(void) {
  // init_can_bus();
  pwm2_init();
  speed = 15.0;
  tune_motor_ls(speed);
  return true;
}

bool c_period_reg_tlm(void) { return true; }

void c_period_1Hz(uint32_t count) {
  (void)count;

  // tune_motor_ls();
}
void c_period_10Hz(uint32_t count) {
  (void)count;
  /*
    if (1 == count)
    {
        speed = 15.0;
    }
    else
    */
  speed = 14.2;
  tune_motor_ls(speed);
  // call_at_10Hz();
}

void c_period_100Hz(uint32_t count) {  // 1/100 = 0.01 sec = 10ms
  (void)count;
}
void c_period_1000Hz(uint32_t count) {
  /* NOTE: by default this function is not called.
   * You must enable it in main.cpp by setting
   * const bool run_1Khz = true;*/
  (void)count;
}
