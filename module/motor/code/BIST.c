// BIST.c

#include <stdio.h>
#include <stdbool.h>
#include "motor_helpers.h"
#include "pwm_wrapper.h"
#include "LED_wrapper.h" // uses all 4 LEDs
#include "LCD_wrapper.h"
#include "switches_wrapper.h" // just uses switch 1

bool isBISTactive = false;
int curr_time = 0; // 0 - 10,000ms ish
int percent_complete = 0;
static float slow_forward = 16.0;
static float slow_reverse = 14.0; // 14.0 // 13.0 too fast but works
extern int reverse_cnt;

// total BIST time = 10 seconds = 10sec * 1000ms/sec = 10,000ms
// Stage 1
//  - go forward for 2.5 seconds
// Stage 2
//  - go backward for 2.5 seconds
// Stage 3
//  - turn right and hold for 2.5 seconds (don't move)
// Stage 4
//  - turn left and hold for 2.5 seconds (don't move)

void continue_BIST(void) // may be called every 100ms
{
    LED_1_on();
    LED_2_on();
    LED_3_on();
    LED_4_on();
    percent_complete = 100 * curr_time / 10000;
    lcd_set_num(percent_complete);

    if (curr_time < 2500) // 0-2400
    {   // Stage 1 - Forward for 2.5 seconds
        Set_PWM_for_Servo(15.0);
        Set_PWM_for_DC(slow_forward);
    }
    else if (curr_time < 5000) // 2500-4900
    {   // Stage 2 - Reverse for 2.5 seconds
        if (reverse_cnt < 4)
        {
            reverse_statemachine();
            reverse_cnt++;
        }
        else
            Set_PWM_for_DC(slow_reverse);
    }
    else if (curr_time < 7500) // 5000-7400
    {   // Stage 3 - Hold right for 2.5 seconds
        Set_PWM_for_Servo(20.0);
        Set_PWM_for_DC(15.0);
    }
    else if (curr_time < 10000) // 7500-9900
    {   // Stage 4 - Hold left for 2.5 seconds
        Set_PWM_for_Servo(10.0);
        Set_PWM_for_DC(15.0);
    }
    else // 10,000 is end of BIST
    {
        LED_1_off();
        LED_2_off();
        LED_3_off();
        LED_4_off();
        isBISTactive = false;
        curr_time = 0;
        reverse_cnt = 0;
        lcd_set_num(0);
        Set_PWM_for_Servo(15.0);
        Set_PWM_for_DC(15.0);
        return;
    }
    curr_time += 100;
}

/*
void continue_BIST(void)
{

    if (total_time == 0)
    {   // Stage 1 - Forward
        Set_PWM_for_Servo(15.0);
        Set_PWM_for_DC(16.0);
        lcd_set_num(percent_complete);
    }
    else if (total_time <= 3000)
    {   // Stage 1 - Forward (cont'd)
        Set_PWM_for_Servo(15.0);
        Set_PWM_for_DC(16.0);
        printf("total_time = %d ms; ", total_time);
        printf("%d%% completed (Stage 1)\n", percent_complete);
        lcd_set_num(percent_complete);
    }
    else if (total_time <= 6000)
    {
        // Stage 2 - Reverse
        if (reverse_cnt < 4)
        {
            reverse_statemachine();
            reverse_cnt++;
        }
        else
            Set_PWM_for_DC(14.0);
        printf("total_time = %d ms; ", total_time);
        printf("%d%% completed (Stage 2)\n", percent_complete);
        lcd_set_num(percent_complete);
    }
    else if (total_time <= 12500)
    {
        // Stage 3 - Right Forward Circle
        Set_PWM_for_Servo(20.0);
        Set_PWM_for_DC(16.0);
        printf("total_time = %d ms; ", total_time);
        printf("%d%% completed (Stage 3)\n", percent_complete);
        lcd_set_num(percent_complete);
    }
    else if (total_time < 18000)
    {
        // Stage 4 - Left Forward Circle
        Set_PWM_for_Servo(10.0);
        Set_PWM_for_DC(16.0);
        printf("total_time = %d ms; ", total_time);
        printf("%d%% completed (Stage 4)\n", percent_complete);
        lcd_set_num(percent_complete);
    }
    else if (total_time == 18000)
    {
        printf("total_time = %d ms; ", total_time);
        printf("%d%% completed\ndone with BIST!\n", percent_complete);
        lcd_set_num(0);
        // movement part of BIST is done
        Set_PWM_for_Servo(15.0);
        Set_PWM_for_DC(15.0);
        // flash 1 LED for 1 second
        LED_1_on();

    }
    else if (total_time == 19000)
    {
        // now BIST is really done
        LED_1_off();
        //lcd_set_num(0);
        Set_PWM_for_DC(15.0);
        Set_PWM_for_Servo(15.0);
        total_time = 0;
        percent_complete = 0;
        isBISTactive = false;
        return;
    }

    total_time += 100;
    percent_complete = total_time / 100;

}
*/

void check_and_handle_BIST(void) // every 100ms
{
    if (isBISTactive)
    {   // ignore switch, and execute BIST
        continue_BIST();
    }
    else if (getSwitch(1))
    {
        isBISTactive = true;
        Set_PWM_for_DC(15.0);
        Set_PWM_for_Servo(15.0);
    }
}

