// Functions for geographic sensors CAN communication

#ifndef GEO_CAN_H__
#define GEO_CAN_H__

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include "can.h"
#include "generated_can.h"

void can_initialization(can_t* geo_module);
void send_heartbeat_msg(can_t* geo_module);
void send_can_msg(can_t* geo_module, GEO_DATA_t* geo_data);

#endif  // GEO_CAN_H__
