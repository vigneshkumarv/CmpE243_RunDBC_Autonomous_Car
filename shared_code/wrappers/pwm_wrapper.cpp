/*
 * pwm_wrapper.cpp
 *
 *  Created on: Mar 31, 2019
 *      Author: lenovo
 */
#include "pwm_wrapper.h"
#include "lpc_pwm.hpp"

PWM pwm1(PWM::pwm1,100);
PWM pwm2(PWM::pwm2,100);
bool set_PWM1_for_servo(float input){
    pwm1.set(input);
    return true;
}

bool set_PWM2_for_DC(float input){
    pwm2.set(input);
    return true;
}
