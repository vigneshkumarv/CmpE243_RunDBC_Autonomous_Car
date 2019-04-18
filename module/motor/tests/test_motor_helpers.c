// test_motor_helpers.c

#include "unity.h"
#include "Mockpwm_wrapper.h"
//#include <stdio.h>


#include "motor_helpers.h"

extern int reverse_cnt;
extern int state;

// should change once encoder works
void test_get_pwm_from_mph(void)
{

    TEST_ASSERT_EQUAL(get_pwm_from_mph(100), 20.0);
}

void test_steer_car(void)
{
    // straight
    Set_PWM_for_Servo_ExpectAndReturn(15.0, true);
    steer_car(0);

    // full right
    Set_PWM_for_Servo_ExpectAndReturn(20.0, true);
    steer_car(45);

    // slight right
    Set_PWM_for_Servo_ExpectAndReturn(16.1111, true);
    steer_car(10);

    // easy right
    Set_PWM_for_Servo_ExpectAndReturn(16.0, true);
    steer_car(9);

    // full left
    Set_PWM_for_Servo_ExpectAndReturn(10.0, true);
    steer_car(-45);

    // slight left
    Set_PWM_for_Servo_ExpectAndReturn(13.8889, true);
    steer_car(-10);

    // easy left
    Set_PWM_for_Servo_ExpectAndReturn(14.0, true);
    steer_car(-9);

    // beyond max right
    Set_PWM_for_Servo_ExpectAndReturn(20.0, true);
    steer_car(65);

    // beyond max left
    Set_PWM_for_Servo_ExpectAndReturn(10.0, true);
    steer_car(-180);
}

void test_move_car(void)
{
    Set_PWM_for_DC_ExpectAndReturn(20.0, true);
    move_car(forward, 100.0);

    reverse_cnt = 4;
    Set_PWM_for_DC_ExpectAndReturn(10.0, true);
    move_car(backward, -100.0);

    Set_PWM_for_DC_ExpectAndReturn(15.0, true);
    move_car(stop, 0);
}

void test_get_direction(void)
{
    TEST_ASSERT_EQUAL(get_direction(1), forward);
    TEST_ASSERT_EQUAL(get_direction(2), backward);
    TEST_ASSERT_EQUAL(get_direction(0), stop);
}

void test_reverse_statemachine(void)
{
    Set_PWM_for_DC_ExpectAndReturn(15.0, true);
    reverse_statemachine();
    Set_PWM_for_DC_ExpectAndReturn(14.1, true);
    reverse_statemachine();
    Set_PWM_for_DC_ExpectAndReturn(15.0, true);
    reverse_statemachine();
    Set_PWM_for_DC_ExpectAndReturn(14.1, true);
    reverse_statemachine();
    TEST_ASSERT_EQUAL(state, 0);

}
