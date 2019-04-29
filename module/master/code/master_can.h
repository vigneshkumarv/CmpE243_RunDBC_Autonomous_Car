// master_can.h

#ifndef MASTER_CAN_H_
#define MASTER_CAN_H_

#include <stdint.h>
#include "can.h"
#include "generated_can.h"
#include "navigation.h"

typedef struct {
  can_msg_t master_can_rx_msg;
} master_can_S;

bool init_can(void);
void check_and_restart_can(void);
bool read_can_50Hz(navigation_sensors_S* sensor_values, GEO_DATA_t* geo_data,
                   navigation_state_machine_S* state_variables);
void send_drive_cmd(navigation_motor_cmd_S drive_data);
void send_heartbeat_msg(void);

#endif /* MASTER_CAN_H_ */
