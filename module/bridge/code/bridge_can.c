/*
 * bridge_can.c
 *
 *  Created on: Apr 26, 2019
 *      Author: lenovo
 */

#include "bridge_can.h"
#include "Uart2.h"
#include "uart0_min.h"
#define SIZE 50
#define ON "CARON"
#define OFF "CAROFF"
const int GEO_DISTANCE_N_ANGLE_MID = 769;
const int GEO_SOURCE_DATA_MID = 771;
bool button_was_pressed = false;


can_msg_t geo_can_msg = {0}, on_off_can_msg = {0};
GEO_SOURCE_DATA_t geo_source_data ={0};
GEO_DATA_t geo_distanceNangle_data ={0};
BRIDGE_DATA_CMD_t on_off_cmd = {0};
dbc_msg_hdr_t geo_can_msg_hdr;
dbc_msg_hdr_t on_off_msg_hdr;






char RX_buffer[SIZE] = {0};
char TX_buffer[SIZE] = {0};
static int bufferindex = 0;






typedef struct{
    float geo_src_latitude;
    float geo_src_longitude;
    float deflection_angle;
    float distance_from_destination;
} Geo_Data;

Geo_Data to_android;






bool bridge_uart2_init(void)
{
    return uart_init(9600, 64, 64);
}





bool bridge_CAN_init(void)
{
   CAN_init(can1,100,32,32,NULL,NULL);
   CAN_reset_bus(can1);
   CAN_bypass_filter_accept_all_msgs();
   return true;
}






void bridge_if_CAN_is_off_then_reset_1hz(void)
{
    if(CAN_is_bus_off(can1))
    {
        CAN_reset_bus(can1);
    }
}






// decode different messages through a struct pointer and concecatenate as required.
void receive_geo_CAN_data_10Hz(void)
{
    while(CAN_rx(can1, &geo_can_msg, 0))
    {
        geo_can_msg_hdr.dlc = geo_can_msg.frame_fields.data_len;
        geo_can_msg_hdr.mid = geo_can_msg.msg_id;

        geo_latitude_and_longitude(&geo_can_msg_hdr);
        geo_distance_and_angle(&geo_can_msg_hdr);
    }
}





void geo_distance_and_angle(dbc_msg_hdr_t * geo_distance_and_angle)
{
    //mid of geo data (distance and angle) is 769
    if(dbc_decode_GEO_DATA(&geo_distanceNangle_data, geo_can_msg.data.bytes, &geo_can_msg_hdr))
    {
        to_android.deflection_angle = geo_distanceNangle_data.GEO_DATA_Angle;
        to_android.distance_from_destination = geo_distanceNangle_data.GEO_DATA_Distance;
        sprintf(RX_buffer,"A%dD%d",(int)to_android.deflection_angle,(int)to_android.distance_from_destination);

        uart2_putchar(*RX_buffer, 0);
    }
}






void geo_latitude_and_longitude(dbc_msg_hdr_t * geo_latitude_and_longitude)
{
    //mid of geo data (latitude and longitude) is 771
    if (dbc_decode_GEO_SOURCE_DATA(&geo_source_data,geo_can_msg.data.bytes,&geo_can_msg_hdr))
    {
        to_android.geo_src_latitude = geo_source_data.GEO_DATA_Latitude;
        to_android.geo_src_longitude = geo_source_data.GEO_DATA_Longitude;
        sprintf(RX_buffer,"L%fG%f",to_android.geo_src_latitude,to_android.geo_src_longitude);
        uart2_putchar(*RX_buffer, 0);
    }
}






void bridge_send_start_stop_CAN_10Hz(void)
{
    check_app_message_delimiter();
    turn_car_on_or_off();
}





void turn_car_on_or_off(void)
{
    if(!strcmp(ON, TX_buffer))
    {
        turn_on_car();
    }
    else if(!strcmp(OFF, TX_buffer))
    {
        turn_off_car();
    }
}





void check_app_message_delimiter(void)
{
    char char_in_message_from_app = 0;

    (uart2_getchar(&char_in_message_from_app, 0));

    if(('~' != char_in_message_from_app) && ('\0' != char_in_message_from_app))
    {
        //printf("%c\n", char_in_message_from_app);
        TX_buffer[bufferindex++] = char_in_message_from_app;
    }
    else
    {
        TX_buffer[bufferindex++] = '\0';
        bufferindex = 0;
        uart0_puts(TX_buffer);
    }
}







bool turn_on_car(void)
{
    puts("Turn on");
    on_off_cmd.BRIDGE_DATA_CMD_start_stop = 1;
    on_off_msg_hdr = dbc_encode_BRIDGE_DATA_CMD(on_off_can_msg.data.bytes, &on_off_cmd);
    on_off_can_msg.msg_id = on_off_msg_hdr.mid;
    on_off_can_msg.frame_fields.data_len = on_off_msg_hdr.dlc;

    return CAN_tx(can1, &on_off_can_msg, 0);
}







bool turn_off_car(void)
{
    puts("turn off\n");
    on_off_cmd.BRIDGE_DATA_CMD_start_stop = 0;
    on_off_msg_hdr = dbc_encode_BRIDGE_DATA_CMD(on_off_can_msg.data.bytes, &on_off_cmd);
    on_off_can_msg.msg_id = on_off_msg_hdr.mid;
    on_off_can_msg.frame_fields.data_len = on_off_msg_hdr.dlc;

    return CAN_tx(can1, &on_off_can_msg, 0);
}


