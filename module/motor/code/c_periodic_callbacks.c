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
#include "BIST.h"
#include "LCD_wrapper.h"
#include "LED_wrapper.h"
#include "Serial_LCD.h"
#include "can_helpers.h"
#include "encoder.h"
#include "motor_controls_master.h"
#include "motor_helpers.h"
#include "pwm_wrapper.h"
#include "uart_wrapper.h"
#include "utilities.h"

#include "pwm_wrapper.h"
#include "LCD_wrapper.h"
#include "LED_wrapper.h"
#include "encoder.h"
#include "motor_controls_master.h"

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

MASTER_DRIVE_CMD_t rx_master_drive_msg;
MASTER_HEARTBEAT_t rx_master_heartbeat_msg;
=======
// LED4=on when either:
//  - encoder sees no movement
//    or
//  - [steering full left or full right]
// LCD displays either:
//  - actual RPM value
//    or
//  - [actual MPH]


// define interrupts for encoder
// keep global counter for encoder_count

bool c_period_init(void) {
  init_can1_bus();
  enable_encoder_interrupts();
  PWMs_init();
  Set_PWM_for_DC(15.0);
  Set_PWM_for_Servo(15.0);

  // XXX: Don't have magic code, why is this here?
  // Atleast comment it
  // delay_ms(500);
  init_speed_state();

  return true;
}

bool c_period_reg_tlm(void) { return true; }

void c_period_1Hz(uint32_t count) {
  (void)count;
  check_and_handle_canbus_state();
}
void c_period_10Hz(uint32_t count) {
  (void)count;

  // XXX: Since the sensor loop and other things will be 20Hz
  // we should move this to 20Hz which we can do by
  // calling it in 100Hz and then doing 'if (0 == (count % 5)) { ...'

  sendHeartbeat();

  // this also does MIAs
  read_All_CAN_Messages(&rx_master_drive_msg, &rx_master_heartbeat_msg);

  if (!isBISTactive()) {
    control_car_with_master(&rx_master_drive_msg);
  }

  send_Motor_Data(getSpeedAct(), rx_master_drive_msg.MASTER_DRIVE_CMD_steer,
                  rx_master_drive_msg.MASTER_DRIVE_CMD_direction);  // direction

  send_Motor_Debug();
  control_car_with_master();

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
