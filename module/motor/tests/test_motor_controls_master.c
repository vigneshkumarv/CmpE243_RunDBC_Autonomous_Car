// test_motor_controls_master.h

#include "unity.h"


#include "generated-can/generated_can.h"
#include "motor_helpers.h"
#include "can_helpers.h"
#include "Mockpwm_wrapper.h"
#include "Mockcan.h"
#include "MockLED_wrapper.h"

#include "motor_controls_master.h"

extern MASTER_DRIVE_CMD_t rx_master_drive_msg;

void test_control_car_with_master(void)
{
    can_msg_t can_msg;

    CAN_rx_ExpectAndReturn(can1, &can_msg, 0, true);
    CAN_rx_IgnoreArg_msg();
    CAN_rx_ExpectAndReturn(can1, &can_msg, 0, false);
    CAN_rx_IgnoreArg_msg();
    if (dbc_handle_mia_MASTER_DRIVE_CMD(&rx_master_drive_msg, 100))
    {
        LED_3_on_Expect();
    }


    Set_PWM_for_Servo_ExpectAndReturn(15.0, true);
    Set_PWM_for_DC_ExpectAndReturn(15.0, true);
    LED_4_off_Expect();

    control_car_with_master();
}
