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
#include "BIST.h"
#include "LCD_wrapper.h"
#include "LED_wrapper.h"
#include "Serial_LCD.h"
#include "encoder.h"
#include "heartbeats.h"
#include "motor_controls_master.h"
#include "motor_helpers.h"
#include "uart_wrapper.h"

// LED1=on when CAN1 is off the bus
// LED2=on when MIA from master heartbeat
// LED3=on when MIA from master drive command
// LED4=on when:
//  - output-->pwm is outside the boundary of 0-100
//    or
//  - steering full left or full right
//  - [encoder is disconnected, PWM too big]
// LCD displays:
//  - [encoder's raw RPM value: not including gear ratio]
//    or
//  - actual MPS

bool c_period_init(void) {
  init_can1_bus();
  enable_encoder_interrupts();
  PWMs_init();
  Set_PWM_for_DC(15.0);
  Set_PWM_for_Servo(15.0);
  delay_ms(500);
  init_speed_state();

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

  if (!isBISTactive()) control_car_with_master();
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
