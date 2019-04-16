/*
 * motor_drive.c
 *
 *  Created on: Apr 1, 2019
 *      Author: lenovo
 */

#include <stdio.h>
#include <stdbool.h>
#include "motor_drive.h"
#include "pwm_wrapper.h"

void set_steer(steer_E steer) {
  switch (steer) {
    case steer_straight:
      Set_PWM_for_Servo(15.0);
      printf("straight\n");
      break;

    case steer_left:
      Set_PWM_for_Servo(10.0);
      printf("left\n");
      break;

    case steer_right:
      Set_PWM_for_Servo(20.0);
      printf("right\n");
      break;
    default:
      Set_PWM_for_Servo(10.0);
  }
}
bool Forward_LowSpeed(void) {
  Set_PWM_for_DC(16.6);
  printf("Low Speed\n");
  return true;
}
bool Forward_MedSpeed(void) {
  Set_PWM_for_DC(18.2);
  return true;
}
bool Forward_HighSpeed(void) {
  Set_PWM_for_DC(19.8);
  return true;
}
bool Reverse_LowSpeed(void) {
  Set_PWM_for_DC(12.5);
  return true;
}
/*
bool Stop(void) {
  Set_PWM_for_DC(15.0);
  printf("Stop\n");
  return true;
}
*/
