// geo_can.c
#include "geo_can.h"

void can_initialization(can_t* geo_module) {
  CAN_init(*geo_module, 100, 64, 64, ((void*)0), ((void*)0));
  CAN_bypass_filter_accept_all_msgs();
  CAN_reset_bus(*geo_module);
}

void send_heartbeat_msg(can_t* geo_module) {
  GEO_HEARTBEAT_t heartbeat = {0};
  heartbeat.GEO_HEARTBEAT_cmd = 0;  // heartbeat msg data field is 0
  can_msg_t can_msg = {0};

  // Encode the CAN message's data bytes, get its header and set the CAN message's DLC and length
  dbc_msg_hdr_t msg_hdr = dbc_encode_GEO_HEARTBEAT(can_msg.data.bytes, &heartbeat);
  can_msg.msg_id = msg_hdr.mid;
  can_msg.frame_fields.data_len = msg_hdr.dlc;

  // Queue the CAN message to be sent out
  CAN_tx(*geo_module, &can_msg, 0);
}

void send_can_msg(can_t* geo_module, GEO_DATA_t* geo_data) {
  can_msg_t can_msg = {0};

  // Encode the CAN message's data bytes, get its header and set the CAN message's DLC and length
  dbc_msg_hdr_t msg_hdr = dbc_encode_GEO_DATA(can_msg.data.bytes, geo_data);
  can_msg.msg_id = msg_hdr.mid;
  can_msg.frame_fields.data_len = msg_hdr.dlc;

  // Queue the CAN message to be sent out
  CAN_tx(*geo_module, &can_msg, 0);
}
