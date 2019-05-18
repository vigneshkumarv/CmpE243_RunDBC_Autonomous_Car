// test_can_helpers.c

#include "unity.h"

#include "MockLED_wrapper.h"
//#include "Mockcan.h"
//#include "Mockpwm_wrapper.h"
#include "MockLCD_wrapper.h"
#include "Mockgpio_wrapper.h"
#include "Mockeint.h"
#include "encoder.h"
#include "speed_control.h"
//#include "can_helpers.h"
//#include "generated_can.h"
//#include "motor_controls_master.h"
//#include "motor_helpers.h"

void test_isEncoderConnected(void)
{
    // not trying to move, can't tell if encoder is connected
    LED_4_off_Expect();
    TEST_ASSERT_EQUAL(true, isEncoderConnected(15.0));

    // try to move (n1)
    LED_4_on_Expect();
    TEST_ASSERT_EQUAL(true, isEncoderConnected(17.0));

    // try to move (n2)
    LED_4_on_Expect();
    TEST_ASSERT_EQUAL(true, isEncoderConnected(17.0));

    // try to move (n3)
    LED_4_on_Expect();
    TEST_ASSERT_EQUAL(true, isEncoderConnected(17.0));

    // try to move (n4)
    LED_4_on_Expect();
    TEST_ASSERT_EQUAL(true, isEncoderConnected(17.0));

    // try to move (n5)
    LED_4_on_Expect();
    TEST_ASSERT_EQUAL(true, isEncoderConnected(17.0));

    // try to move (n6)
    LED_4_on_Expect();
    TEST_ASSERT_EQUAL(true, isEncoderConnected(17.0));

    // try to move (n7)
    LED_4_on_Expect();
    TEST_ASSERT_EQUAL(true, isEncoderConnected(17.0));


    // try to move (n8)
    LED_4_on_Expect();
    TEST_ASSERT_EQUAL(true, isEncoderConnected(17.0));

    // try to move (n9)
    LED_4_on_Expect();
    TEST_ASSERT_EQUAL(true, isEncoderConnected(17.0));

    // try to move (n10) but encoder is not connected anymore
    LED_4_on_Expect();
    LED_4_on_Expect();
    TEST_ASSERT_EQUAL(false, isEncoderConnected(17.0));

    // try to move (n11) but encoder is not connected anymore
    LED_4_on_Expect();
    LED_4_on_Expect();
    TEST_ASSERT_EQUAL(false, isEncoderConnected(17.0));

    // the only way to restore encoder now is to either:
    // - send a move command with 0 speed
    // - read non-zero encoder value


    // let's see if this works
    // so we send a move with 0 speed
    //LED_4_on_Expect();
    LED_4_off_Expect();
    TEST_ASSERT_EQUAL(true, isEncoderConnected(15.0));

    // and then we can move normally
    LED_4_on_Expect();
    TEST_ASSERT_EQUAL(true, isEncoderConnected(17.0));

}

void test_get_pwm_act(void)
{
    TEST_ASSERT_EQUAL(0, get_pwm_act());
}

void test_get_output(void)
{
    TEST_ASSERT_EQUAL(0, get_output());
}

void test_get_int_cmd(void)
{
    TEST_ASSERT_EQUAL(0, get_int_cmd());
}

void test_get_prop_cmd(void)
{
    TEST_ASSERT_EQUAL(0, get_prop_cmd());
}

void test_get_pi_error(void)
{
    TEST_ASSERT_EQUAL(0, get_pi_error());
}

void test_get_RPM_act(void)
{
    TEST_ASSERT_EQUAL(0, get_RPM_act());
}

void test_get_RPM_raw(void)
{
    TEST_ASSERT_EQUAL(0, get_RPM_raw());
}

void test_getSpeedAct(void)
{
    TEST_ASSERT_EQUAL(0, getSpeedAct());
}

void test_final_pwm_safety_check(void)
{
    //LED_4_on_Expect();
    TEST_ASSERT_EQUAL(15, final_pwm_safety_check(20));

   // LED_4_on_Expect();
    TEST_ASSERT_EQUAL(15, final_pwm_safety_check(10));

    //LED_4_off_Expect();
    TEST_ASSERT_EQUAL(17.0, final_pwm_safety_check(17.0));

    //LED_4_off_Expect();
    TEST_ASSERT_EQUAL(13.3, final_pwm_safety_check(13.3));

    //LED_4_on_Expect();
    TEST_ASSERT_EQUAL(15, final_pwm_safety_check(24.8));

    //LED_4_on_Expect();
    TEST_ASSERT_EQUAL(15, final_pwm_safety_check(8.9));

    //LED_4_off_Expect();
    TEST_ASSERT_EQUAL(15, final_pwm_safety_check(15.0));
}

void test_check_for_large_error(void)
{
    TEST_ASSERT_EQUAL(0, check_for_large_error());
}

void test_get_RPM_from_MPS(void)
{
    TEST_ASSERT_EQUAL(0, get_RPM_from_MPS(0.0));

    TEST_ASSERT_EQUAL(180, get_RPM_from_MPS(1.0));
}

void test_get_actual_speed_from_rpm(void)
{
    lcd_set_num_Expect(0);
    TEST_ASSERT_EQUAL(0, get_actual_speed_from_rpm(0));

    lcd_set_num_Expect(32);
    float r = get_actual_speed_from_rpm(32);
    printf("r=%f\n", r);
    TEST_ASSERT_EQUAL(0, r); // 0 isnt accurate enough
}

void test_get_RPM_raw_10Hz(void)
{
    TEST_ASSERT_EQUAL(0, get_RPM_raw_10Hz());
}

void test_get_pwm_for_speed_control(void)
{
    speed_control_t speed_state_ptr;
    speed_state_ptr.meters_per_sec_cmd = 0;
    speed_state_ptr.int_cmd_old = 0;
    speed_state_ptr.isBackward = false;

    LED_2_off_Expect();
    LED_3_off_Expect();
    //LED_4_off_Expect();
    get_pwm_for_speed_control(&speed_state_ptr);

    speed_state_ptr.meters_per_sec_cmd = 1.0;
    LED_2_off_Expect();
    LED_3_off_Expect();
    //LED_4_off_Expect();
    get_pwm_for_speed_control(&speed_state_ptr);
}

