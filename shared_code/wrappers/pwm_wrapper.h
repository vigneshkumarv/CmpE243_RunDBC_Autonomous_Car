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

bool Set_PWM_for_Servo(float input);
bool Set_PWM_for_DC(float input);
void PWMs_init(void);

#ifdef __cplusplus
}
#endif
#endif /* PWM_WRAPPER_H_ */
