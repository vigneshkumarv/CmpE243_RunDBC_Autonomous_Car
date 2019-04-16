// test_heartbeats.c

#include "unity.h"
#include <stdbool.h>
#include "Mockcan.h"

#include "heartbeats.h"
#include "generated-can/generated_can.h"
#include "can_helpers.h"
#include "MockLED_wrapper.h"
#include "motor_controls_master.h"
#include "motor_helpers.h"
#include "Mockpwm_wrapper.h"

extern MASTER_HEARTBEAT_t rx_master_heartbeat_msg;

void test_handle_heartbeats(void)
{
    can_msg_t can_msg;
    CAN_tx_ExpectAndReturn(can1, &can_msg, 0, true);
    CAN_tx_IgnoreArg_msg();

    CAN_rx_ExpectAndReturn(can1, &can_msg, 0, true);
    CAN_rx_IgnoreArg_msg();

    CAN_rx_ExpectAndReturn(can1, &can_msg, 0, false);
    CAN_rx_IgnoreArg_msg();

    if (dbc_handle_mia_MASTER_HEARTBEAT(&rx_master_heartbeat_msg, 100))
        LED_2_on_Expect();

    handle_heartbeats();

}
