/*
 * pwm_wrapper.cpp
 *
 *  Created on: Mar 31, 2019
 *      Author: lenovo
 */
#include "pwm_wrapper.h"
#include "lpc_pwm.hpp"

PWM pwm1(PWM::pwm1,8); // 8 works
PWM pwm2(PWM::pwm2,8); // 10 works

bool Set_PWM1_for_Servo(float input){

    pwm1.set(input);
    return true;
}
bool Set_PWM2_for_DC(float input){

    pwm2.set(input);
    return true;
}
