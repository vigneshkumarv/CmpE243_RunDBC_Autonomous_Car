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
#include "can.h"
#include "geo_can.h"
#include "gps.h"
#include "queue.h"

bool c_period_init(void) {
  can_initialization(&GEO_module);
  gps_module_init();

  queue__init(&longitude_data_queue);
  queue__init(&latitude_data_queue);

  return true;
}

bool c_period_reg_tlm(void) { return true; }

void c_period_1Hz(uint32_t count) {
  (void)count;
  send_heartbeat_msg(&GEO_module);

}

void c_period_10Hz(uint32_t count) {
  (void)count;
  gps_obtain_and_process_data(count);
  send_can_msg(&GEO_module, &geo_data);
  send_can_msg_to_bridge(&GEO_module, &geo_coordinate_data);
  /*float heading_result = 0;
  read_compass_heading( &heading_result);
  uint8_t result = 0;
  check_calibration_level(&result);
  printf("compass heading: %f, calibration: %d \n", heading_result, result);*/
}

void c_period_100Hz(uint32_t count) { (void)count; }
void c_period_1000Hz(uint32_t count) {
  /* NOTE: by default this function is not called.
   * You must enable it in main.cpp by setting
   * const bool run_1Khz = true;*/
  (void)count;
}
