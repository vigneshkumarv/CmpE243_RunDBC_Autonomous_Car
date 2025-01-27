// BIST.c

#include <stdbool.h>
#include <stdio.h>
#include "LCD_wrapper.h"
#include "LED_wrapper.h"  // uses all 4 LEDs
#include "motor_helpers.h"
#include "pwm_wrapper.h"
#include "switches_wrapper.h"  // just uses switch 1

static bool inProgress = false;
static int curr_time = 0;  // 0 - 8,000ms ish
static int percent_complete = 0;
static float slow_forward = 16.0;
static float slow_reverse = 14.0;  // 14.0 // 13.0 too fast but works

// total BIST time = 8 seconds = 8sec * 1000ms/sec = 8,000ms
// Stage 1
//  - go forward for 1.5 seconds // was 2.5
// Stage 2
//  - go backward for 1.5 seconds // was 2.5
// Stage 3
//  - turn right and hold for 2.5 seconds (don't move)
// Stage 4
//  - turn left and hold for 2.5 seconds (don't move)

bool isDoneWithInnerBIST(void)  // may be called every 100ms
{                               // returns true if the BIST is done
  LED_1_on();
  LED_2_on();
  LED_3_on();
  LED_4_on();
  percent_complete = 100 * curr_time / 8000;
  lcd_set_num(percent_complete);

  if (curr_time < 1500)  // 0-1400
  {                      // Stage 1 - Forward for 1.5 seconds
    Set_PWM_for_Servo(15.0);
    Set_PWM_for_DC(slow_forward);
  } else if (curr_time < 3000)   // 1500-2900
  {                              // Stage 2 - Reverse for 1.5 seconds
    if (reverse_statemachine())  // when SM is done
    {
      Set_PWM_for_DC(slow_reverse);
    }
    // otherwise follow the SM
  } else if (curr_time < 5500)  // 3000-5400
  {                             // Stage 3 - Hold right for 2.5 seconds
    Set_PWM_for_Servo(20.0);
    Set_PWM_for_DC(15.0);
  } else if (curr_time < 8000)  // 5500-7900
  {                             // Stage 4 - Hold left for 2.5 seconds
    Set_PWM_for_Servo(10.0);
    Set_PWM_for_DC(15.0);
  } else  // 8,000 is end of BIST
  {
    LED_1_off();
    LED_2_off();
    LED_3_off();
    LED_4_off();
    inProgress = false;
    curr_time = 0;
    lcd_set_num(0);
    Set_PWM_for_Servo(15.0);
    Set_PWM_for_DC(15.0);
    return true;
  }
  curr_time += 100;
  return false;
}

bool isBISTactive(void)  // every 100ms
{                        // returns true if the BIST is active
  if (inProgress) {      // ignore switch, and handle BIST
    if (isDoneWithInnerBIST()) {
      return false;  // stop doing the BIST
    } else {
      return true;  // keep going with the BIST
    }
  } else if (getSwitch(1))  // switch is pressed
  {
    inProgress = true;
    Set_PWM_for_DC(15.0);
    Set_PWM_for_Servo(15.0);
    return true;
  } else {
    return false;
  }
}
