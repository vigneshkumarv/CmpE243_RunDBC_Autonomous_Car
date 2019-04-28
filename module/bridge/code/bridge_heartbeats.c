/*
 * bridge_heartbeats.c

 *
 *  Created on: Apr 26, 2019
 *      Author: lenovo
 */
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include "can.h"
#include "generated_can/generated_can.h"

BRIDGE_HEARTBEAT_t bridge_heartbeat = {0};
can_msg_t bridge_heartbeat_can_msg = {0};
dbc_msg_hdr_t bridge_heartbeat_msg_hdr;

bool send_bridge_heartbeat_1hz() {
  bridge_heartbeat.BRIDGE_HEARTBEAT_cmd = 0;
  bridge_heartbeat_msg_hdr = dbc_encode_BRIDGE_HEARTBEAT(bridge_heartbeat_can_msg.data.bytes, &bridge_heartbeat);
  bridge_heartbeat_can_msg.msg_id = bridge_heartbeat_msg_hdr.mid;
  bridge_heartbeat_can_msg.frame_fields.data_len = bridge_heartbeat_msg_hdr.dlc;

  return CAN_tx(can1, &bridge_heartbeat_can_msg, 0);
}
