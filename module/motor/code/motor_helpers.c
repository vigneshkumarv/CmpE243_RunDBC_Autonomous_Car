// motor_helpers.c

#include <stdint.h>
#include <stdio.h>
#include "LED_wrapper.h"
#include "LCD_wrapper.h"
#include "motor_helpers.h"
#include "encoder.h"
#include "motor_controls_master.h"
#include "pwm_wrapper.h"

// keep these as static? but unit test wont like it..
int reverse_cnt = 0; //
int state = 0;
static float stop_pwm = 15.0;
static float reverse_pwm = 14.1;

/*
float calc_pwm_target(int RPM_target) // for DC motor
{   // will eventually need to incorporate encoder (RPM_actual)

    if (RPM_target )
}
*/

void reverse_statemachine(void)  // every 100ms gets called
{
  switch (state)
  {
      case (0) :
            Set_PWM_for_DC(stop_pwm);  // stop
            ++state;
            break;
      case (1) :
            Set_PWM_for_DC(reverse_pwm);  // reverse
            ++state;
            break;
      case (2) :
            Set_PWM_for_DC(stop_pwm);  // stop
            ++state;
            break;
      case (3) :
            Set_PWM_for_DC(reverse_pwm);  // reverse
            state = 0;
            break;
      default :
            printf("ERROR in reverse state machine!\n");
            state = 0; // should never happen
  }
}

direction_E get_direction(uint8_t direction_raw)
{
    direction_E ret;
    switch (direction_raw)
    {
        case (1) :
                ret = forward;
                break;
        case (2) :
                ret = backward;
                break;
        default :
                ret = stop;
    }
    return ret;
}

void move_car(direction_E direction, float mph)
{
    float pwm_val = 15.0;

    // for encoder
    /*
    //int RPM_actual = get_RPM_10Hz();
    int RPM_target = get_RPM_from_MPH(mph);
    printf("RPM actual = %d\n", RPM_actual);
    printf("RPM target = %d\n\n", RPM_target);
    */
    pwm_val = 15.0 + (mph / 20.0);
    switch (direction)
    {
        case (forward) :
              reverse_cnt = 0;
              state = 0;
              break;
        case (backward) :
              if ((reverse_cnt < 4)) // need to do state machine
              {
                  reverse_statemachine();
                  reverse_cnt++;
              }
              break;
        default : // stop
              pwm_val = 15.0;
    }
    lcd_set_num((int) mph); // not for UT, only debug
    printf("pwm_val = %f\n", pwm_val);
    Set_PWM_for_DC(pwm_val);

}

void steer_car(int steer_angle)
{
    // -45 implies full left
    // 0 implies straight
    // 45 implies full right

    float pwm_val;
    int max_angle = 45;
    //printf("steer_angle = %d\n", steer_angle);

    if (steer_angle >= max_angle) // steer full right
    {
        pwm_val = 20.0;
        LED_4_on();
    }
    else if (steer_angle <= (-1 * max_angle)) // steer full left
    {
        pwm_val = 10.0;
        LED_4_on();
    }
    else // steer normally
    {
        pwm_val = 15.0 + (5.0 * steer_angle / max_angle);
        LED_4_off();
    }
    Set_PWM_for_Servo(pwm_val);
}

float get_pwm_from_mph(float mph) // should also consider direction
{ // should consider encoder (motor_speed_RPM)
    float pwm_speed = (mph / 20.0) + 15.0; // only works in forward

    /* //
    error = speed_cmd - speed_act
    prop_cmd = error * proportional_gain
    int_cmd_new = error * integral_gain
    int_cmd += int_cmd_new;
    output = int_cmd + prop_cmd
    if (output > 100) {output = 100}
    else if (output < 0) {output = 0}
    */

    return pwm_speed;
}
