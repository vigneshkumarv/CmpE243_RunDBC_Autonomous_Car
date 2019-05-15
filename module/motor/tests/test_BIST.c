// test_BIST.c

#include "unity.h"

#include <stdbool.h>

#include "BIST.h"
#include "MockLCD_wrapper.h"
#include "MockLED_wrapper.h"
#include "Mockeint.h"          // and here
#include "Mockgpio_wrapper.h"  // and here
#include "Mockpwm_wrapper.h"
#include "Mockswitches_wrapper.h"
#include "encoder.h"  // same thing here
#include "motor_helpers.h"
#include "speed_control.h"  // not used, but needs to be included for UT

void test_isBISTactive(void) {
  // switch is not pressed, dont do BIST
  getSwitch_ExpectAndReturn(1, false);
  isBISTactive();

  // switch is pressed, start the BIST
  getSwitch_ExpectAndReturn(1, true);
  Set_PWM_for_DC_ExpectAndReturn(15.0, true);
  Set_PWM_for_Servo_ExpectAndReturn(15.0, true);
  isBISTactive();

  // first iteration of the BIST
  LED_1_on_Expect();
  LED_2_on_Expect();
  LED_3_on_Expect();
  LED_4_on_Expect();
  lcd_set_num_Expect(0);
  Set_PWM_for_DC_ExpectAndReturn(16.0, true);
  Set_PWM_for_Servo_ExpectAndReturn(15.0, true);
  isBISTactive();
}
