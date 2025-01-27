// sensor module main code

#include "c_periodic_callbacks.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include "car_sensors.h"
#include "read_and_send.h"

// static unsigned int timer_count = 0;

bool c_period_init(void) {
  init_sensors();
  CAN_init(sensor_module, 100, 64, 64, ((void*)0), ((void*)0));
  CAN_bypass_filter_accept_all_msgs();
  CAN_reset_bus(sensor_module);
  return true;
}

bool c_period_reg_tlm(void) { return true; }

void c_period_1Hz(uint32_t count) {
  (void)count;
  send_heartbeat_msg(&sensor_module);
}

void c_period_10Hz(uint32_t count) {
  (void)count;

}

void c_period_100Hz(uint32_t count) {
  (void)count;

  if (count % 10 == 0){
      // Set the trigger pin high for 20 micro-seconds, and then set it low.
      // Read the sensor values after 50ms to ensure that the ADC value is ready and accurate.
      read_left_right_ultrasonic_sensors();
      gpio_middle_trigger_set(high);
      delay_us(20);
      gpio_middle_trigger_set(low);

      read_left_right_bumper_sensors();
      send_can_msg(&sensor_module);
  }
  else if (count % 10 == 5){
      read_middle_rear_sensors();
      gpio_left_right_trigger_set(high);
      delay_us(20);
      gpio_left_right_trigger_set(low);

      send_can_msg(&sensor_module);
  }

}

void c_period_1000Hz(uint32_t count) {
  /* NOTE: by default this function is not called.
   * You must enable it in main.cpp by setting
   * const bool run_1Khz = true;*/
  (void)count;
}
