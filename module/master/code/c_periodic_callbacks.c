/*
 * c_periodic_callbacks.c
 *
 *  Created on: Feb 16, 2019
 *      Author: reldn_000
 */

#include "c_periodic_callbacks.h"
#include <can.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include "light_speed.h"
#include "unit_testing_header.h"

light_speed_S speed_data = {0};

bool c_period_init(void) {
  init_light_speed();
  return true;
}

bool c_period_reg_tlm(void) { return true; }

void c_period_1Hz(uint32_t count) {
  check_and_restart_can();
  (void)count;
}
void c_period_10Hz(uint32_t count) {
  send_speed(speed_data.average_speed_percent);
  (void)count;
}

void c_period_100Hz(uint32_t count) {
  update_speed(&speed_data);
  (void)count;
}
void c_period_1000Hz(uint32_t count) {
  /* NOTE: by default this function is not called.
   * You must enable it in main.cpp by setting
   * const bool run_1Khz = true;*/
  (void)count;
}
