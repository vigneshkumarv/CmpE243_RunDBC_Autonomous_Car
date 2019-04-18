/*
 * pwm_wrapper.cpp
 *
 *  Created on: Mar 31, 2019
 *      Author: lenovo
 */
#include "pwm_wrapper.h"
#include "lpc_pwm.hpp"

PWM * pwm3_ptr; // pwm3 = P2.2
PWM * pwm1_ptr; // pwm1 = P2.0

bool Set_PWM_for_Servo(float input){

    pwm1_ptr->set(input);
    return true;
}
bool Set_PWM_for_DC(float input){

    pwm3_ptr->set(input);
    return true;
}

void PWMs_init(void)
{
    pwm3_ptr = new PWM(PWM::pwm3, 100);
    pwm1_ptr = new PWM(PWM::pwm1, 100);
}
