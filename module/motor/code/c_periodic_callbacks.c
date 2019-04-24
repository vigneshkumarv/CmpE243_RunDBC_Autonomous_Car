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
#include "utilities.h"

#include "pwm_wrapper.h"
//#include "motor_controls_switch.h"
#include "LCD_wrapper.h"
#include "LED_wrapper.h"
#include "encoder.h"
#include "heartbeats.h"
#include "motor_controls_master.h"
#include "motor_helpers.h"
#include "BIST.h"
#include "uart_wrapper.h"
#include "Serial_LCD.h"

// LED1=on when CAN1 is off the bus
// LED2=on when MIA from master heartbeat
// LED3=on when MIA from master drive command
// LED4=on when:
//  - output-->pwm is outside the boundary of 0-100
//    or
//  - steering full left or full right
//  - [encoder is disconnected]
// LCD displays:
//  - [encoder's RPM value: not including gear ratio]
//    or
//  - actual MPH

// for encoder
//int motor_speed_RPM = 0;
// extern int encoder_count;

static float speed;
extern bool isBISTactive;

// define interrupts for encoder
// keep global counter for encoder_count

bool c_period_init(void) {
  init_can1_bus();
  enable_encoder_interrupts();
  PWMs_init();
  speed = 15.0;
  Set_PWM_for_DC(15.0);
  Set_PWM_for_Servo(15.0);
  delay_ms(500);
  init_speed_state();

  init_serial_lcd();
  clear_screen();
  print_line(0, "Hello, i am Line 0");
  print_line(1, "Line 1:");
  print_line(2, "and this is Line 2");
  print_line(3, "and this is Line 3");
  //clear_line(1);
  print_line(2, "empty line");
  print_seg(2, 15, "NULL", 3);

  print_seg(1, 11, "[pos=11]", 9);
  print_seg(1, 9, "pos9", 11);

  print_seg(3, 19, "#", 1);
  print_seg(3, 9, "==", 2);
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
  // control_car_with_switches();
  check_and_handle_BIST();
  if (!isBISTactive)
      control_car_with_master();
}

void c_period_100Hz(uint32_t count) {  // 1/100 = 0.01 sec = 10ms
  (void)count;
  //control_car_with_master();

}
void c_period_1000Hz(uint32_t count) {
  /* NOTE: by default this function is not called.
   * You must enable it in main.cpp by setting
   * const bool run_1Khz = true;*/
  (void)count;
}
