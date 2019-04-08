// test_motor_controls_switch.c

#include <stdbool.h>
#include <stdint.h>
#include "MockLED_wrapper.h"
#include "Mockcan.h"
#include "Mockpwm_wrapper.h"
#include "Mockswitches_wrapper.h"
#include "generated-can/generated_can.h"
#include "motor_controls_switch.h"
#include "unity.h"

MASTER_SPEED_t rx_masterspeed_msg;

void test_control_car_with_switches(void) {
  // uint8_t target_state = 2;
  // when we want to stop
  getSwitch_ExpectAndReturn(1, false);
  getSwitch_ExpectAndReturn(2, true);
  Set_PWM2_for_DC_ExpectAndReturn(15.0, true);
  control_car_with_switches();

  // when we want to go low speed forward
  getSwitch_ExpectAndReturn(1, false);
  getSwitch_ExpectAndReturn(2, false);
  getSwitch_ExpectAndReturn(3, true);
  Set_PWM2_for_DC_ExpectAndReturn(15.6, true);
  control_car_with_switches();

  // when we want to go medium speed forward
  getSwitch_ExpectAndReturn(1, false);
  getSwitch_ExpectAndReturn(2, false);
  getSwitch_ExpectAndReturn(3, false);
  getSwitch_ExpectAndReturn(4, true);
  Set_PWM2_for_DC_ExpectAndReturn(16.0, true);
  control_car_with_switches();

  // when we want to go low speed reverse
  getSwitch_ExpectAndReturn(1, true);
  Set_PWM2_for_DC_ExpectAndReturn(15.0, true);
  // Set_PWM2_for_DC_ExpectAndReturn(14.2, true);
  // Set_PWM2_for_DC_ExpectAndReturn(15.0, true);
  // Set_PWM2_for_DC_ExpectAndReturn(14.2, true);
  control_car_with_switches();
}
