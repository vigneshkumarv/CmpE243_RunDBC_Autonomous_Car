// motor_controls_master.h

#ifndef _MOTOR_CONTROLS_MASTER_H
#define _MOTOR_CONTROLS_MASTER_H

#include "generated_can.h"

void control_car_with_master(MASTER_DRIVE_CMD_t* rx_master_drive_msg);

#endif
