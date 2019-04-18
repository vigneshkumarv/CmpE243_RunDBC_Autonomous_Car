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

#include "pwm_wrapper.h"
//#include "motor_controls_switch.h"
#include "LCD_wrapper.h"
#include "LED_wrapper.h"
#include "encoder.h"
#include "heartbeats.h"
#include "motor_controls_master.h"

// LED1=on when CAN1 is off the bus
// LED2=on when MIA from master heartbeat
// LED3=on when MIA from master drive command
// LED4=on when either:
//  - encoder sees no movement
//    or
//  - [steering full left or full right]
// LCD displays either:
//  - actual RPM value
//    or
//  - [actual MPH]

// for encoder
int motor_speed_RPM = 0;
// extern int encoder_count;

static float speed;

// define interrupts for encoder
// keep global counter for encoder_count

bool c_period_init(void) {
  init_can1_bus();
  enable_encoder_interrupts();
  PWMs_init();
  speed = 15.0;

  return true;
}

bool c_period_reg_tlm(void) { return true; }

void c_period_1Hz(uint32_t count) {
  (void)count;
  check_and_handle_canbus_state();
  handle_heartbeats();
}
void c_period_10Hz(uint32_t count) {
  (void)count;

  control_car_with_master();
  // control_car_with_switches();
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
