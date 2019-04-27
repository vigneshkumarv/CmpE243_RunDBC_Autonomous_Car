// can_helpers.h

#ifndef _CAN_HELPERS_H
#define _CAN_HELPERS_H

#include <stdbool.h>
#include <stdint.h>
#include "generated_can.h"

void sendHeartbeat(void);
void send_Motor_Debug(void);
bool dbc_app_send_can_msg(uint32_t mid, uint8_t dlc, uint8_t bytes[8]);
void init_can1_bus(void);
void check_and_handle_canbus_state(void);
float get_pwm_from_mph(float mph);
void read_All_CAN_Messages(MASTER_DRIVE_CMD_t* rx_master_drive_msg, MASTER_HEARTBEAT_t* rx_master_heartbeat_msg);
void send_Motor_Data(float speed_act, int steer_angle, uint8_t direction_raw);

#endif
