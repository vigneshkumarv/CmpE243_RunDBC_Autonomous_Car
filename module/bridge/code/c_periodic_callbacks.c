/*
 * c_periodic_callbacks.c
 *
 *  Created on: Feb 16, 2019
 *      Author: reldn_000
 */

#include "c_periodic_callbacks.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include "bridge_can.h"
#include "bridge_heartbeats.h"
#include "can.h"
#include "path_finding.h"

bool c_period_init(void)
{
    bridge_CAN_init();
    bridge_uart2_init();
    return true;
}

bool c_period_reg_tlm(void)
{
    return true;
}

void c_period_1Hz(uint32_t count)
{
    send_bridge_heartbeat_1hz();
    is_bridge_CAN_busoff_then_reset_1hz();

    if (check_destination_received()) {
        bridge_path_finding();
        path_finding_main();
    }
    (void) count;
}

void c_period_10Hz(uint32_t count)
{
    receive_CAN_data_10Hz();
    // empty out all the chars received
    for (int i = 0; i < 100; i++) {
        bridge_send_start_stop_CAN_10Hz();
    }
    if (0 == (count % 5)) {
        compile_and_send_data();
    }

}

void c_period_100Hz(uint32_t count)
{
    (void) count;
}

void c_period_1000Hz(uint32_t count)
{
    (void) count;
}
