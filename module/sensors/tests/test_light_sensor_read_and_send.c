#include "unity.h"
#include "light_sensor_read_and_send.h"
#include "Mockls_wrapper.h"
#include "Mockcan.h"
#include "generated_can.h"

can_t can_bus_test;
can_msg_t can_msg_test;
SENSOR_DATA_t sensor_cmd_test;
dbc_msg_hdr_t msg_hdr_test;

void setUp(void) {
}

void tearDown(void) {
}

void test_light_sensor_read_and_send(void) {
    ls_get_per_ExpectAndReturn(50);
    can_msg_t can_msg_test = {0};
    SENSOR_DATA_t sensor_cmd_test = {0};
    msg_hdr_test = dbc_encode_SENSOR_DATA(can_msg_test.data.bytes, &sensor_cmd_test);

    can_msg_test.msg_id = msg_hdr_test.mid;
    can_msg_test.frame_fields.data_len = msg_hdr_test.dlc;
    CAN_tx_ExpectAndReturn(can_bus_test, &can_msg_test, 0, true);
    CAN_tx_IgnoreArg_can();
    CAN_tx_IgnoreArg_msg();
    light_sensor_read_and_send();
}

