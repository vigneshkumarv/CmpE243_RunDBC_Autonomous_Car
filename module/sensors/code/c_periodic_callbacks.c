// sensor module main code

#include "c_periodic_callbacks.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include "car_sensors.h"
#include "read_and_send.h"

// static unsigned int timer_count = 0;

static int motor_speed_RPM = 0;
extern int encoder_count;

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


  motor_speed_RPM = (((encoder_count)/(64.0))/1)*60;
  printf("encoder_count: %d    motor_speed_RPM = %d \n", encoder_count, motor_speed_RPM);
  encoder_count = 0;
  send_heartbeat_msg(&sensor_module);

}

void c_period_10Hz(uint32_t count) {
  (void)count;

  //read_left_right_ultrasonic_sensors();
  //delay_ms(40);
  //read_middle_rear_sensors();
  read_left_right_bumper_sensors();
  send_can_msg(&sensor_module);
  delay_ms(40);
}

void c_period_100Hz(uint32_t count) {
  (void)count;
  /* timer_count++;
   if (timer_count == 1) {
       //read_left_right_ultrasonic_sensors();
   }
   else if (timer_count == 7) {
       read_middle_rear_sensors();
       read_left_right_bumper_sensors();
   }
   else if (timer_count == 12) {
       timer_count = 0;
       send_can_msg(&sensor_module);
   }*/



}

void c_period_1000Hz(uint32_t count) {
  /* NOTE: by default this function is not called.
   * You must enable it in main.cpp by setting
   * const bool run_1Khz = true;*/
  (void)count;
}
