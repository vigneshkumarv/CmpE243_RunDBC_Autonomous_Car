// Functions for geographic sensors CAN communication

#ifndef GEO_CAN_H__
#define GEO_CAN_H__

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include "can.h"
#include "generated_can.h"

BRIDGE_CHECKPOINT_t BRIDGE_data;
can_t GEO_module;

void can_initialization(can_t* geo_module);
void send_heartbeat_msg(can_t* geo_module);
void send_can_msg(can_t* geo_module, GEO_DATA_t* geo_data);
void send_can_msg_to_bridge(can_t* geo_module, GEO_COORDINATE_DATA_t* geo_data);
void receive_can_msg(can_t* geo_module, BRIDGE_CHECKPOINT_t* bridge_data);

#endif  // GEO_CAN_H__
