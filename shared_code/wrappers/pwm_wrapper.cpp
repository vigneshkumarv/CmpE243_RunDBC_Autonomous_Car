//pwm_wrapper.cpp

#include "pwm_wrapper.h"
#include "lpc_pwm.hpp"

//PWM * pwm3_ptr; // pwm3 = P2.2
PWM * pwm2_ptr; // pwm2 = P2.1
PWM * pwm1_ptr; // pwm1 = P2.0

bool Set_PWM_for_Servo(float input){

    pwm1_ptr->set(input);
    return true;
}
bool Set_PWM_for_DC(float input){

    pwm2_ptr->set(input);
    return true;
}

void PWMs_init(void)
{
    pwm2_ptr = new PWM(PWM::pwm2, 100);
    pwm1_ptr = new PWM(PWM::pwm1, 100);
}

