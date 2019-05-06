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
#include "bridge_can.h"
#include "bridge_heartbeats.h"
#include "can.h"
#include "path_finding.h"

bool c_period_init(void) {
  printf("checkpoint\n");
  bridge_CAN_init();
  bridge_uart2_init();
  printf("checkpoint1\n");
  bridge_path_finding();
  printf("checkpoint2\n");
  return true;
}

bool c_period_reg_tlm(void) { return true; }

void c_period_1Hz(uint32_t count) {
  send_bridge_heartbeat_1hz();
  path_finding_main();
  is_bridge_CAN_busoff_then_reset_1hz();
  (void)count;
}

void c_period_10Hz(uint32_t count) {
  receive_CAN_data_10Hz();
  (void)count;
}

void c_period_100Hz(uint32_t count) {
  //bridge_send_start_stop_CAN_100Hz();
  (void)count;
}

void c_period_1000Hz(uint32_t count) { (void)count; }
