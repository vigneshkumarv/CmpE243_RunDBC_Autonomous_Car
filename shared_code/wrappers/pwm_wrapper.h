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

bool Set_PWM1_for_Servo(float input);
bool Set_PWM2_for_DC(float input);
void pwm2_init(void);

#ifdef __cplusplus
}
#endif
#endif /* PWM_WRAPPER_H_ */
