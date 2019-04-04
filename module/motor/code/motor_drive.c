/*
 * motor_drive.c
 *
 *  Created on: Apr 1, 2019
 *      Author: lenovo
 */
#include "motor_drive.h"
#include <stdio.h>

void set_steer(steer_E steer) {
  switch (steer) {
    case steer_straight:
      set_PWM1_for_servo(15.0);
      printf("straight\n");
      break;

    case steer_left:
      set_PWM1_for_servo(10.0);
      printf("left\n");
      break;

    case steer_right:
      set_PWM1_for_servo(20.0);
      printf("right\n");
      break;
    default:
      set_PWM1_for_servo(10.0);
  }
}
bool Forward_LowSpeed() {
  set_PWM2_for_DC(16.6);
  printf("Low Speed\n");
  return true;
}
bool Forward_MedSpeed() {
  set_PWM2_for_DC(18.2);
  return true;
}
bool Forward_HighSpeed() {
  set_PWM2_for_DC(19.8);
  return true;
}
bool Reverse_LowSpeed() {
  set_PWM2_for_DC(12.5);
  return true;
}
bool Stop() {
  set_PWM2_for_DC(15.0);
  printf("Stop\n");
  return true;
}
