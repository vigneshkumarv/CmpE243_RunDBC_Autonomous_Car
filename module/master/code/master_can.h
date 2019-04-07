// master_can.h

#ifndef MASTER_CAN_H_
#define MASTER_CAN_H_

#include <stdint.h>
#include "can.h"
#include "generated_can.h"

typedef struct {
  can_msg_t master_can_rx_msg;
} master_can_S;

bool init_can(void);
void check_and_restart_can(void);
bool read_can(void);
void send_drive_cmd(MASTER_DRIVE_CMD_t* drive_data);
void send_heartbeat_msg(void);

#endif /* MASTER_CAN_H_ */
