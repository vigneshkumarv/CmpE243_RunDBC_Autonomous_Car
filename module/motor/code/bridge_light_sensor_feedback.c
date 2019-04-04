/*
 * bridge_light_sensor_feedback.c
 *
 *  Created on: Mar 24, 2019
 *      Author: lenovo
 */
#include "bridge_light_sensor_feedback.h"
#include "C:\Users\lenovo\Desktop\autonomous-car\shared_code\wrappers\ls_wrapper.h"
#include "can.h"
#include "stdbool.h"

BRIDGE_DATA_t light_sensor_percent_val;
can_msg_t can_msg = {0};

void Bridge_CAN_Init() { CAN_init(can1, 100, 64, 64, NULL, NULL); }
void Bridge_CAN_Transmit() {
  light_sensor_percent_val.BRIDGE_DATA_cmd = ls_get_per();
  dbc_msg_hdr_t msg_hdr = dbc_encode_BRIDGE_DATA(can_msg.data.bytes, &light_sensor_percent_val);
  can_msg.msg_id = msg_hdr.mid;
  can_msg.frame_fields.data_len = msg_hdr.dlc;
  CAN_tx(can1, &can_msg, 0);
}

void Bridge_CAN_Check() {
  if (CAN_is_bus_off(can1)) {
    // printf("Resetting...\n");
    CAN_reset_bus(can1);
  }
}
