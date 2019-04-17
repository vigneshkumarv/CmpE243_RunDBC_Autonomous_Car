// motor_controls_master.c

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <can.h>
#include "motor_helpers.h"
#include "motor_controls_master.h"
#include "can_helpers.h"
#include "generated-can/generated_can.h"

#include "can_helpers.h"
#include "LED_wrapper.h"
#include "pwm_wrapper.h"

//static int state;
//static int reverse_cnt;
//static bool is_reverse = false; // start in stop state

//static float stop_speed = 15.0;
//static float reverse_low_speed = 14.1;

static int steer_angle = 0; // 0 for straight, -128 for full left, 127 for full right
static float mph = 0.0;
static uint8_t direction_raw = 0; // 0 for stop, 1 for forward, 2 for reverse

MASTER_DRIVE_CMD_t rx_master_drive_msg;
const uint32_t MASTER_DRIVE_CMD__MIA_MS = 3000;
const MASTER_DRIVE_CMD_t MASTER_DRIVE_CMD__MIA_MSG = {.MASTER_DRIVE_CMD_steer = 0, .MASTER_DRIVE_CMD_speed = 0.0, .MASTER_DRIVE_CMD_direction = 0};

void control_car_with_master(void)
{
    // read drive command from master (get steer, speed, direction)
    // and do stuff
    // also determine target state (reverse or non-reverse)

    read_Master_Drive_Cmd(); // results in rx_master_drive_msg
                             // also handles mia

    // from -45deg to +45deg
    steer_angle = rx_master_drive_msg.MASTER_DRIVE_CMD_steer;

    // from 0-100mph
    mph = rx_master_drive_msg.MASTER_DRIVE_CMD_speed;

    // stop, forward, backward
    direction_raw = rx_master_drive_msg.MASTER_DRIVE_CMD_direction;

    direction_E direction = get_direction(direction_raw);

    steer_car(steer_angle);
    move_car(direction, mph);

}