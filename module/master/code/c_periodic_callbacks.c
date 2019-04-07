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
#include "master_can.h"

MASTER_DRIVE_CMD_t drive_data = {0};

bool c_period_init(void) {
  bool can_is_initialized = init_can();
  return can_is_initialized;
}

bool c_period_reg_tlm(void) { return true; }

void c_period_1Hz(uint32_t count) {
  check_and_restart_can();
  send_heartbeat_msg();
  (void)count;
}
void c_period_10Hz(uint32_t count) {
  send_drive_cmd(&drive_data);
  read_can();
  (void)count;
}

void c_period_100Hz(uint32_t count) { (void)count; }
void c_period_1000Hz(uint32_t count) {
  /* NOTE: by default this function is not called.
   * You must enable it in main.cpp by setting
   * const bool run_1Khz = true;*/
  (void)count;
}
