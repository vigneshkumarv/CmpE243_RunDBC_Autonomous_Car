/*
 * c_periodic_callbacks.c
 *
 *  Created on: Feb 16, 2019
 *      Author: reldn_000
 */

#include "light_sensor_read_and_send.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include "can.h"

void light_sensor_read_and_send() {
  int light_value = light_sensor_getRawValue();
  SENSOR_DATA_t SENSOR_cmd = {0};
  SENSOR_cmd.SENSOR_DATA_cmd = light_value;

  can_msg_t can_msg = {0};
  dbc_msg_hdr_t dbc_encode_SENSOR_DATA(can_msg.data.bytes, &SENSOR_cmd);
  can_msg.msg_id = msg_hdr.mid;
  can_msg.frame_fields.data_len = msg_hdr.dlc;

  CAN_tx(can1, &can_msg, 0);
}

/*	CAN_init(can1, 100, 64, 64, ((void*)0), ((void*)0));
        CAN_bypass_filter_accept_all_msgs();
        CAN_reset_bus(can1);
        */