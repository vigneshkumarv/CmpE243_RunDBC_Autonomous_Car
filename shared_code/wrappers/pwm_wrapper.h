/*
 * pwm_wrapper.h
 *
 *  Created on: Mar 31, 2019
 *      Author: lenovo
 */

#ifndef PWM_WRAPPER_H_
#define PWM_WRAPPER_H_
#ifdef __cplusplus
extern "C" {
#endif

#include "stdint.h"
#include "stdbool.h"

bool Set_PWM1_for_Servo(float input);
bool Set_PWM2_for_DC(float input);

#ifdef __cplusplus
}
#endif
#endif /* PWM_WRAPPER_H_ */
