// motor_controls_switch.c

// switch 1: low speed reverse
// switch 2: stop
// switch 3: low speed forward
// switch 4: medium speed forward

#include <stdint.h>
#include <stdio.h>
#include "pwm_wrapper.h"
#include "switches_wrapper.h"

static int state;
static int reverse_cnt;
static uint8_t target_state = 2;

float reverse_low_speed = 14.2;
// 14.3 inconsistent,
// 14.1 works,
// 14.25 glitchy,
// 14.2 good

float stop_speed = 15.0;
float forward_low_speed = 15.6;
float forward_medium_speed = 16.0;

void reverse_state_machine(void)  // every 100ms gets called
{
  if (state == 0) {
    printf("first state (stop)\n");
    Set_PWM2_for_DC(stop_speed);  // stop
    state++;
  } else if (state == 1)  // 0
  {
    printf("second state (reverse)\n");
    Set_PWM2_for_DC(reverse_low_speed);  // reverse
    state++;
  } else if (state == 2)  // 1
  {
    printf("third state (stop)\n");
    Set_PWM2_for_DC(stop_speed);  // stop
    state++;
  } else if (state == 3)  // 2
  {
    printf("fourth state (reverse)\n");
    Set_PWM2_for_DC(reverse_low_speed);  // reverse
    state = 0;
  }
}

void control_car_with_switches(void) {
  // read switches
  // and determine target state
  if (getSwitch(1))
    target_state = 1;  // low speed reverse
  else if (getSwitch(2))
    target_state = 2;  // stop
  else if (getSwitch(3))
    target_state = 3;  // low speed forward
  else if (getSwitch(4))
    target_state = 4;  // medium speed forward

  if (target_state == 1)  // low speed reverse
  {
    printf("Trying to go low speed reverse...\n");

    if ((reverse_cnt < 4)) {
      reverse_state_machine();  // utilize the state machine
      reverse_cnt++;
    } else if (reverse_cnt >= 4) {
      Set_PWM2_for_DC(reverse_low_speed);
    }

  } else if (target_state == 2)  // stop
  {
    printf("Trying to stop...\n");
    if (Set_PWM2_for_DC(stop_speed)) printf("Setting PWM2 to %f%%\n", stop_speed);

    reverse_cnt = 0;
    state = 0;
  } else if (target_state == 3)  // low speed forward
  {
    printf("Trying to go low speed forward...\n");
    if (Set_PWM2_for_DC(forward_low_speed)) printf("Setting PWM2 to %f%%\n", forward_low_speed);

    reverse_cnt = 0;
    state = 0;

    printf("\n");
  } else if (target_state == 4)  // medium speed forward
  {
    printf("Trying to go medium speed forward...\n");
    if (Set_PWM2_for_DC(forward_medium_speed)) printf("Setting PWM2 to %f%%\n", forward_medium_speed);

    reverse_cnt = 0;
    state = 0;
  }
}
