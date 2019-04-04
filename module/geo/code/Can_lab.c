/*
 * can_lab.c
 *
 *  Created on: Mar 3, 2019
 *      Author: 9595v
 */


#include "can_lab.h"
#include "can.h"
#include <stdio.h>
#include <stdint.h>

bool Geo_CAN_initialize(void)
{
    CAN_init(can1, 100, 10, 10, NULL, NULL);
    return true;
}

bool Geo_CAN_transmit(can_msg_t *p)
{

    CAN_tx(can1, p,0);
    return true;
}

bool Geo_CAN_reset(void)
{
  if(CAN_is_bus_off(can1))
     CAN_reset_bus(can1);
    return true;
}

uint8_t Geo_LS_percentage_data(void)
{

    return ls_get_per();
}



