// c_period_callbacks.c

#include "c_periodic_callbacks.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include "display_lcd.h"
#include "gpio_wrapper.h"
#include "master_can.h"
#include "navigation.h"
#include "pwm_wrapper.h"

// xxx statics
navigation_state_machine_S state_variables;
navigation_sensors_S sensor_data;
navigation_motor_cmd_S motor_command;
GEO_DATA_t geo_data;
GEO_COORDINATE_DATA_t geo_coordinates;
GEO_DEBUG_DATA_t geo_debug;
MOTOR_DATA_t motor_actual;

bool c_period_init(void) {
  init_navigation(&state_variables, &sensor_data, &geo_data, &motor_command);
  initialize_display_lcd();

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
  send_debug_msg(state_variables);

  display_screens(count, state_variables, geo_data, geo_coordinates, geo_debug, motor_command, motor_actual,
                  sensor_data);

  (void)count;
}
void c_period_100Hz(uint32_t count) {
  if (0 == count % 2) {
    read_can_50Hz(&sensor_data, &geo_data, &geo_coordinates, &geo_debug, &state_variables, &motor_actual);
    navigation_state_machine(count, &state_variables, sensor_data, geo_data, &motor_command);
    send_drive_cmd(motor_command);
  }
}
void c_period_1000Hz(uint32_t count) {
  /* NOTE: by default this function is not called.
   * You must enable it in main.cpp by setting
   * const bool run_1Khz = true;*/
  (void)count;
}
