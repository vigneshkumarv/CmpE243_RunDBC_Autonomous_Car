// motor_helpers.c

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "LCD_wrapper.h"
#include "LED_wrapper.h"
#include "motor_controls_master.h"
#include "motor_helpers.h"
#include "pwm_wrapper.h"
#include "speed_control.h"
#include "generated_can.h"

const float STOP_PWM = 15.0;
const float REVERSE_SM_PWM = 13.0;  // 13.5 // 13.0 works

// xxx
// Since 'speed_state_ptr' alawys points to 'speed_state'
// you do not need this pointer at all.
// just use 'speed_state.'(whatever) all the time
static speed_control_t speed_state;                      // pointer makes the board crash
static speed_control_t *speed_state_ptr = &speed_state;  //
static rev_state_E rev_state = rev_state_1_of_4;

speed_control_t get_speed_state(void) { return *speed_state_ptr; }

void init_speed_state(void) {
  speed_state_ptr->meters_per_sec_cmd = 0.0;
  speed_state_ptr->int_cmd_old = 0.0;
  speed_state_ptr->isBackward = false;
}

bool reverse_statemachine(void)  // every 100ms this would be called
{                                // returns true if state machine is finished
  bool ret = false;
  switch (rev_state) {
    case (rev_state_1_of_4):
      Set_PWM_for_DC(STOP_PWM);  // stop
      rev_state = rev_state_2_of_4;
      ret = false;
      break;
    case (rev_state_2_of_4):
      Set_PWM_for_DC(REVERSE_SM_PWM);  // reverse
      rev_state = rev_state_3_of_4;
      ret = false;
      break;
    case (rev_state_3_of_4):
      Set_PWM_for_DC(STOP_PWM);  // stop
      rev_state = rev_state_4_of_4;
      ret = false;
      break;
    case (rev_state_4_of_4):
      Set_PWM_for_DC(REVERSE_SM_PWM);  // reverse
      rev_state = rev_state_normal;
      ret = true;
      break;
    default:  // already in reverse, dont follow state machine
      rev_state = rev_state_normal;
      ret = true;
  }
  return ret;
}

void move_car(MASTER_DRIVE_CMD_direction_E direction_cmd, float mps)
{
  float pwm_val = 15.0;

  switch (direction_cmd) {
    case (forward_cmd):
      speed_state_ptr->isBackward = false;
      speed_state_ptr->meters_per_sec_cmd = mps;
      rev_state = rev_state_1_of_4;
      pwm_val = get_pwm_for_speed_control(speed_state_ptr);
      Set_PWM_for_DC(pwm_val);
      break;
    case (backward_cmd):
      if (reverse_statemachine())  // when SM is done
      {
        pwm_val = get_pwm_for_speed_control(speed_state_ptr);
        Set_PWM_for_DC(pwm_val);
      }
      speed_state_ptr->isBackward = true;
      break;
    default:  // stop
      rev_state = rev_state_1_of_4;
      Set_PWM_for_DC(STOP_PWM);
  }
}

void steer_car(int steer_angle)
{
  // -45 implies full left
  // 0 implies straight
  // 45 implies full right

  float pwm_val;
  const int max_angle = 45;

  // XXX This is great for now, but later if you realize you can benefit from
  // a 5-state steering, then prove to yourself that you need it, then
  // implement 'slight left' and 'left' and 'center' etc.
  if (steer_angle >= max_angle)  // steer full right
  {
    pwm_val = 20.0;
    // LED_4_on();
  } else if (steer_angle <= (-1 * max_angle))  // steer full left
  {
    pwm_val = 10.0;
    // LED_4_on();
  } else  // steer normally
  {
    pwm_val = 15.0 + (5.0 * steer_angle / max_angle);
    // LED_4_off();
  }
  Set_PWM_for_Servo(pwm_val);
}
