// can_helpers.c

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <can.h>
#include "pwm_wrapper.h"
#include "LED_wrapper.h"
#include "generated-can/generated_can.h"

extern int motor_speed_RPM;
extern MASTER_DRIVE_CMD_t rx_master_drive_msg;

void read_Master_Drive_Cmd(void)
{
    can_msg_t can_msg;
    while (CAN_rx(can1, &can_msg, 0))
    {
        dbc_msg_hdr_t can_msg_hdr;
        can_msg_hdr.mid = can_msg.msg_id;
        can_msg_hdr.dlc = can_msg.frame_fields.data_len;
        dbc_decode_MASTER_DRIVE_CMD(&rx_master_drive_msg, can_msg.data.bytes, &can_msg_hdr);
        //steer = rx_master_drive_msg.MASTER_DRIVE_CMD_steer;
        //mph = rx_master_drive_msg.MASTER_DRIVE_CMD_speed;
        //direction = rx_master_drive_msg.MASTER_DRIVE_CMD_direction;
    }
    if (dbc_handle_mia_MASTER_DRIVE_CMD(&rx_master_drive_msg, 100))
    {
        LED_3_on();
        Set_PWM_for_DC(15.0); //
    }
}

void check_and_handle_canbus_state(void)
{
    if (CAN_is_bus_off(can1))
    {
        LED_1_on();
        CAN_reset_bus(can1);
        printf("CAN1 bus had to be restarted\n");
    }
    else
    {
        LED_1_off();
    }
}

bool dbc_app_send_can_msg(uint32_t mid, uint8_t dlc, uint8_t bytes[8])
{
    can_msg_t can_msg = {0};
    can_msg.msg_id = mid;
    can_msg.frame_fields.data_len = dlc;
    memcpy(can_msg.data.bytes, bytes, dlc);
    return CAN_tx(can1, &can_msg, 0);
}

void init_can1_bus(void)
{
    CAN_init(can1, 100, 32, 32, NULL, NULL);
    CAN_bypass_filter_accept_all_msgs();
    CAN_reset_bus(can1);
}
