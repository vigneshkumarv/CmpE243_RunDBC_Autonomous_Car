// motor_helpers.c

#include "motor_helpers.h"
#include <stdint.h>
#include <stdio.h>
#include "LCD_wrapper.h"
#include "LED_wrapper.h"
#include "speed_control.h"
//#include "encoder.h"
#include "motor_controls_master.h"
#include "pwm_wrapper.h"

int reverse_cnt = 0;  //
int state = 0;
float stop_pwm = 15.0;
float reverse_pwm = 13.0;  // 13.5 // 13.0 works

speed_control_t speed_state;                      // pointer makes the board crash
speed_control_t *speed_state_ptr = &speed_state;  //

void init_speed_state(void) {
  speed_state_ptr->meters_per_sec = 0.0;
  speed_state_ptr->int_cmd_old = 0.0;
  speed_state_ptr->isBackward = false;
}

void reverse_statemachine(void)  // every 100ms this would be called
{
  switch (state) {
    case (0):
      Set_PWM_for_DC(stop_pwm);  // stop
      ++state;
      break;
    case (1):
      Set_PWM_for_DC(reverse_pwm);  // reverse
      ++state;
      break;
    case (2):
      Set_PWM_for_DC(stop_pwm);  // stop
      ++state;
      break;
    case (3):
      Set_PWM_for_DC(reverse_pwm);  // reverse
      state = 0;
      break;
    default:
      // printf("ERROR in reverse state machine!\n");
      state = 0;  // should never happen
  }
}

direction_E get_direction(uint8_t direction_raw) {
  direction_E ret;
  switch (direction_raw) {
    case (1):
      ret = forward;
      break;
    case (2):
      ret = backward;
      break;
    default:
      ret = stop;
  }
  return ret;
}

void move_car(direction_E direction, float mps) {
  float pwm_val = 15.0;
  // for speed control
  // direction = forward; // for no CAN bus only

  switch (direction) {
    case (forward):
      reverse_cnt = 0;
      state = 0;
      speed_state_ptr->isBackward = false;
      speed_state_ptr->meters_per_sec = mps;
      break;
    case (backward):
      if ((reverse_cnt < 4))  // need to do state machine
      {
        reverse_statemachine();
        reverse_cnt++;
      }
      speed_state_ptr->isBackward = true;
      break;
    default:  // stop
      pwm_val = 15.0;
  }
  pwm_val = get_pwm_for_speed_control(speed_state_ptr);

  // printf("pwm_val = %f\n\n", pwm_val);
  Set_PWM_for_DC(pwm_val);
}

void steer_car(int steer_angle) {
  // -45 implies full left
  // 0 implies straight
  // 45 implies full right

  float pwm_val;
  int max_angle = 45;

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
