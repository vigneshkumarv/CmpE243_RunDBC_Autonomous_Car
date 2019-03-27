
/**
 * @file
 *
 * The purpose of this "C" callbacks is to provide the code to be able
 * to call pure C functions and unit-test it in C test framework
 */
#include <stdint.h>
#include <stdbool.h>
#include<stdio.h>
#include "can.h"
#include "Can_lab.h"
#include "C:\Users\9595v\Desktop\autonomous-car\shared_code\wrappers\ls_wrapper.h"
#include "generated_can\generated_can.h"




void c_period_init(void) {
    Geo_CAN_initialize();
    CAN_reset_bus(can1);

 //   uint32_t var=1000;

   // return true;
}
bool c_period_reg_tlm(void) {
    return true;
}

void c_period_1Hz(uint32_t count) {
    (void) count;
    Geo_CAN_reset();
//
}

void c_period_10Hz(uint32_t count) {
    (void) count;

    can_msg_t *p;
    can_msg_t msg = { 0 };
    p=&msg;
    GEO_DATA_t geo_object = { 0 };
    geo_object.GEO_DATA_cmd = Geo_LS_percentage_data();
    dbc_msg_hdr_t can_header = dbc_encode_GEO_DATA(msg.data.bytes, &geo_object);
    msg.msg_id = can_header.mid;
    msg.frame_fields.data_len = can_header.dlc;

    Geo_CAN_transmit(p);
        can_header.dlc = msg.frame_fields.data_len;
        can_header.mid = msg.msg_id;
//
//        if(dbc_encode(&geo_object, msg.data.bytes, &can_header)){
//            geo_object.THERMAL_SENSOR_celsius_unsigned=msg.data.bytes[0];
//           // printf("entered");
//
//            int num = thermal_object.THERMAL_SENSOR_celsius_unsigned;
//           // printf("%d", num);
//            led_display_set_number(num);
//        }
//    }
////
//    if(dbc_handle_mia_THERMAL_SENSOR(&thermal_object, 50))
//    {
//        printf("MIA occured\n");
//        turn_ON_LED();
//    }




}
void c_period_100Hz(uint32_t count) {
    (void) count;



}

void c_period_1000Hz(uint32_t count) {
    (void) count;
}
