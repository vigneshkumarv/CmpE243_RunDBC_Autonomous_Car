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

#include "stdbool.h"
#include "stdint.h"

bool set_PWM1_for_servo(float input);
bool set_PWM2_for_DC(float input);

#ifdef __cplusplus
}
#endif
#endif /* PWM_WRAPPER_H_ */
