// speed_control.c

#include "LCD_wrapper.h"
#include "LED_wrapper.h"
#include "speed_control.h"
#include "encoder.h"
#include <stdio.h>

extern int encoder_count;
float tire_diameter_in_meters = 0.1061;
float gear_ratio = 16.0 / 90.0; // 16-T?
const float pulses_per_rev = 64.0;

static int large_error_cnt = 0;
static const int max_large_error_count = 5;
float error = 0.0;
float proportional_gain = 10.0; //
float integral_gain = 5.0; //
float speed_act = 0.0;

void check_for_large_error(void)
{
    if ((error > 0.5) || (error < -0.5))
        large_error_cnt++;
    else
        large_error_cnt = 0;
}

float get_RPM_from_MPS(float meters_per_sec)
{
    float meters_per_rev = 3.14 * tire_diameter_in_meters;
    float seconds_per_min = 60.0;
    float rev_per_meter = 1.0 / meters_per_rev;
    float meters_per_min = meters_per_sec * seconds_per_min;
    float rev_per_min = rev_per_meter * meters_per_min;
    return rev_per_min;
}

float get_actual_speed_from_rpm(float rev_per_min)
{
    lcd_set_num((int)rev_per_min);
    //printf("rev_per_min = %f\n", rev_per_min);

    float sec_per_min = 60.0;
    float meters_per_rev = 3.14 * tire_diameter_in_meters;
    float rev_per_sec = rev_per_min / sec_per_min;
    float meters_per_sec = rev_per_sec * meters_per_rev;
    return meters_per_sec;
}

float get_RPM_100Hz(void) // only be called from 1 place
{
    float rpm = (((encoder_count) / (pulses_per_rev)) / 0.1) * 60;

    encoder_count = 0;
    return rpm;
}

float get_pwm_for_speed_control(speed_control_t *speed_state_ptr)
{ // float mps, float *int_cmd_old
    float speed_cmd = speed_state_ptr->meters_per_sec;
    float RPM_act = get_RPM_100Hz();
    RPM_act = gear_ratio * RPM_act; // multiply by gear ratio
    speed_act = get_actual_speed_from_rpm(RPM_act);
    //printf("speed_cmd = %f\n", speed_cmd);
    //printf("speed_act = %f\n", speed_act);
    error = speed_cmd - speed_act;
    check_for_large_error();
    if (large_error_cnt > max_large_error_count)
    {
        LED_4_on();
        return 15.0;
    }
    float prop_cmd = error * proportional_gain;
    float int_cmd = error * integral_gain;
    int_cmd += speed_state_ptr->int_cmd_old;
    float output = int_cmd + prop_cmd;
    if (output > 100)
    {
        output = 100;
        //LED_4_on();
    }
    else if (output < 0)
    {
        output = 0;
        //LED_4_on();
    }
    else
        LED_4_off();

    speed_state_ptr->int_cmd_old = int_cmd;

    if(speed_state_ptr->isBackward == true)
        output *= -1;

    return 15.0 + (output / 20.0);
}
