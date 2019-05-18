// test_can_helpers.c

#include "unity.h"

#include "MockLED_wrapper.h"
//#include "Mockcan.h"
//#include "Mockpwm_wrapper.h"
#include "MockLCD_wrapper.h"
#include "Mockeint.h"
#include "Mockgpio_wrapper.h"
#include "Mockpwm_wrapper.h"
#include "encoder.h"
#include "speed_control.h"

//#include "can_helpers.h"
#include "generated_can.h"
//#include "motor_controls_master.h"
#include "motor_helpers.h"

void test_steer_car(void) {
  // straight
  Set_PWM_for_Servo_ExpectAndReturn(15.0, true);
  steer_car(0);

  // full right
  Set_PWM_for_Servo_ExpectAndReturn(20.0, true);
  steer_car(45);

  // slight right
  Set_PWM_for_Servo_ExpectAndReturn(16.1111, true);
  steer_car(10);

  // easy right
  Set_PWM_for_Servo_ExpectAndReturn(16.0, true);
  steer_car(9);

  // full left
  Set_PWM_for_Servo_ExpectAndReturn(10.0, true);
  steer_car(-45);

  // slight left
  Set_PWM_for_Servo_ExpectAndReturn(13.8889, true);
  steer_car(-10);

  // easy left
  Set_PWM_for_Servo_ExpectAndReturn(14.0, true);
  steer_car(-9);

  // beyond max right
  Set_PWM_for_Servo_ExpectAndReturn(20.0, true);
  steer_car(65);

  // beyond max left
  Set_PWM_for_Servo_ExpectAndReturn(10.0, true);
  steer_car(-180);
}

void test_move_car(void) {
  // stop
  lcd_set_num_Expect(0);
  Set_PWM_for_DC_ExpectAndReturn(15.0, true);
  move_car(stop_cmd, 0.0);

  // forward n1
  lcd_set_num_Expect(0.0);
  LED_4_off_Expect();
  LED_3_off_Expect();
  LED_2_off_Expect();
  Set_PWM_for_DC_ExpectAndReturn(15.4, true);
  move_car(forward_cmd, 1.0);

  // forward n2
  lcd_set_num_Expect(0.0);
  LED_4_off_Expect();
  // LED_4_on_Expect();
  LED_3_off_Expect();
  LED_2_off_Expect();
  Set_PWM_for_DC_ExpectAndReturn(15.95, true);
  move_car(forward_cmd, 2.0);

  // backward n1
  lcd_set_num_Expect(0.0);
  Set_PWM_for_DC_ExpectAndReturn(15, true);
  move_car(backward_cmd, 1.0);

  // stop
  lcd_set_num_Expect(0.0);
  Set_PWM_for_DC_ExpectAndReturn(15.0, true);
  move_car(stop_cmd, 0.0);
}

void test_reverse_statemachine(void) {
  Set_PWM_for_DC_ExpectAndReturn(15.0, true);
  reverse_statemachine();

  Set_PWM_for_DC_ExpectAndReturn(14.0, true);
  reverse_statemachine();

  Set_PWM_for_DC_ExpectAndReturn(15.0, true);
  reverse_statemachine();

  Set_PWM_for_DC_ExpectAndReturn(14.0, true);
  reverse_statemachine();

  reverse_statemachine();
}

void test_init_speed_state(void) { init_speed_state(); }
