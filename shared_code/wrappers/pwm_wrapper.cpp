/*
 * pwm_wrapper.cpp
 *
 *  Created on: Mar 31, 2019
 *      Author: lenovo
 */
#include "pwm_wrapper.h"
#include "lpc_pwm.hpp"


//PWM pwm1(PWM::pwm1,100); // 8 works
// pwm2(PWM::pwm2,8); // 10 works

PWM * pwm2_ptr;
//PWM pwm2(PWM::pwm2,100); // 10 works

bool Set_PWM1_for_Servo(float input){

    //pwm1.set(input);
    return true;
}
bool Set_PWM2_for_DC(float input){

    pwm2_ptr->set(input);
    return true;
}

void pwm2_init(void)
{
    pwm2_ptr = new PWM(PWM::pwm2, 100);
}
