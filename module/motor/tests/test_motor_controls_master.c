// test_can_helpers.c

#include "unity.h"

#include "MockLED_wrapper.h"
//#include "Mockcan.h"
//#include "Mockpwm_wrapper.h"
#include "MockLCD_wrapper.h"
#include "Mockgpio_wrapper.h"
#include "Mockeint.h"
#include "Mockpwm_wrapper.h"
#include "encoder.h"
#include "speed_control.h"

//#include "can_helpers.h"
#include "generated_can.h"
#include "motor_controls_master.h"
#include "motor_helpers.h"

void test_control_car_with_master(void)
{
    MASTER_DRIVE_CMD_t rx_master_drive_msg;
    rx_master_drive_msg.MASTER_DRIVE_CMD_steer = 45;
    rx_master_drive_msg.MASTER_DRIVE_CMD_direction = forward_cmd;
    rx_master_drive_msg.MASTER_DRIVE_CMD_speed = 1.0;
    lcd_set_num_Expect(0);
    LED_4_off_Expect();
    LED_3_off_Expect();
    LED_2_off_Expect();
    Set_PWM_for_DC_ExpectAndReturn(15.4, true);
    Set_PWM_for_Servo_ExpectAndReturn(20.0, true);
    control_car_with_master(&rx_master_drive_msg);

    rx_master_drive_msg.MASTER_DRIVE_CMD_steer = -10;
    rx_master_drive_msg.MASTER_DRIVE_CMD_direction = stop_cmd;
    rx_master_drive_msg.MASTER_DRIVE_CMD_speed = 0.0;
    lcd_set_num_Expect(0);
    Set_PWM_for_DC_ExpectAndReturn(15.0, true);
    Set_PWM_for_Servo_ExpectAndReturn(13.8889, true);
    control_car_with_master(&rx_master_drive_msg);

    // reverse stage 1
    rx_master_drive_msg.MASTER_DRIVE_CMD_steer = 0;
    rx_master_drive_msg.MASTER_DRIVE_CMD_direction = backward_cmd;
    rx_master_drive_msg.MASTER_DRIVE_CMD_speed = 1.0;
    lcd_set_num_Expect(0);
    Set_PWM_for_DC_ExpectAndReturn(15.0, true);
    Set_PWM_for_Servo_ExpectAndReturn(15.0, true);
    control_car_with_master(&rx_master_drive_msg);

    // reverse stage 2
    lcd_set_num_Expect(0);
    Set_PWM_for_DC_ExpectAndReturn(14.0, true);
    Set_PWM_for_Servo_ExpectAndReturn(15.0, true);
    control_car_with_master(&rx_master_drive_msg);

    // reverse stage 3
    lcd_set_num_Expect(0);
    Set_PWM_for_DC_ExpectAndReturn(15.0, true);
    Set_PWM_for_Servo_ExpectAndReturn(15.0, true);
    control_car_with_master(&rx_master_drive_msg);

    // reverse stage 4
    lcd_set_num_Expect(0);
    Set_PWM_for_DC_ExpectAndReturn(14.0, true);
    Set_PWM_for_Servo_ExpectAndReturn(15.0, true);
    control_car_with_master(&rx_master_drive_msg);

    // reverse normal stage (n1)
    lcd_set_num_Expect(0);
    LED_4_off_Expect();
    LED_3_off_Expect();
    LED_2_off_Expect();
    Set_PWM_for_DC_ExpectAndReturn(14.45, true);
    Set_PWM_for_Servo_ExpectAndReturn(15.0, true);
    control_car_with_master(&rx_master_drive_msg);

    // reverse normal stage (n2)
    lcd_set_num_Expect(0);
    LED_4_off_Expect();
    LED_3_off_Expect();
    LED_2_off_Expect();
    Set_PWM_for_DC_ExpectAndReturn(14.3, true); // 13.75
    Set_PWM_for_Servo_ExpectAndReturn(15.0, true);
    control_car_with_master(&rx_master_drive_msg);

    // reverse normal stage (n3)
    lcd_set_num_Expect(0);
    LED_4_off_Expect();
    LED_3_off_Expect();
    LED_2_off_Expect();
    Set_PWM_for_DC_ExpectAndReturn(14.15, true); //13.5
    Set_PWM_for_Servo_ExpectAndReturn(15.0, true);
    control_car_with_master(&rx_master_drive_msg);

    // reverse normal stage (n4)
    lcd_set_num_Expect(0);
    LED_4_off_Expect();
    LED_3_off_Expect();
    LED_2_off_Expect();
    Set_PWM_for_DC_ExpectAndReturn(14, true); //13.25
    Set_PWM_for_Servo_ExpectAndReturn(15.0, true);
    control_car_with_master(&rx_master_drive_msg);

    // reverse normal stage (n5) -
    //                           -
    //                           -
    lcd_set_num_Expect(0);
    LED_4_off_Expect();
    LED_3_off_Expect();
    LED_2_on_Expect();
    Set_PWM_for_DC_ExpectAndReturn(13.85, true);
    Set_PWM_for_Servo_ExpectAndReturn(15.0, true);
    control_car_with_master(&rx_master_drive_msg);
}

