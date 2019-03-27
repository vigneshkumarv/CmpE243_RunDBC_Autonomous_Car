#include "light_speed.h"
#include "unity.h"
#include "Mockcan.h"
#include <string.h>
#include "generated_can/generated_can.h"

light_speed_S speed_data = {0};
extern can_msg_t rx_can_message;

void setUp(void) {
    memset(&speed_data, 0, sizeof(speed_data));
}

void tearDown(void) {}

void test_init_light_speed(void){
    CAN_init_ExpectAndReturn(can1, 100, 64, 64, NULL, NULL, true);
    CAN_reset_bus_Expect(can1);
    CAN_bypass_filter_accept_all_msgs_Expect();
    init_light_speed();
}

void test_check_and_restart_can(void){
    CAN_is_bus_off_ExpectAndReturn(can1, true);
    CAN_reset_bus_Expect(can1);
    check_and_restart_can();
    CAN_is_bus_off_ExpectAndReturn(can1, false);
    check_and_restart_can();
}

void test_update_speed(void){

    CAN_rx_ExpectAndReturn(can1, NULL, 0, true);
    CAN_rx_IgnoreArg_msg();
    CAN_rx_ExpectAndReturn(can1, NULL, 0, false);
    CAN_rx_IgnoreArg_msg();
    rx_can_message.frame_fields.data_len = GEO_DATA_HDR.dlc;
    rx_can_message.msg_id = GEO_DATA_HDR.mid;
    update_speed(&speed_data);

}

void test_send_speed(void){

    CAN_tx_ExpectAndReturn(can1, NULL, 0, true);
    CAN_tx_IgnoreArg_msg();
    send_speed(speed_data.average_speed_percent);
}

