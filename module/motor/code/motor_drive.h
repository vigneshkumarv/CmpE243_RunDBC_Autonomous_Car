/*
 * motor_drive.h
 *
 *  Created on: Apr 1, 2019
 *      Author: lenovo
 */

#ifndef MOTOR_DRIVE_H_
#define MOTOR_DRIVE_H_
#include "C:\Users\lenovo\Desktop\autonomous-car\shared_code\wrappers\pwm_wrapper.h"

typedef enum {
  steer_straight,
  steer_left,
  steer_right,
} steer_E;
void set_steer(steer_E steer);
bool Forward_LowSpeed();
bool Forward_MedSpeed();
bool Forward_HighSpeed();
bool Reverse_LowSpeed();
bool Stop();

#endif /* MOTOR_DRIVE_H_ */
