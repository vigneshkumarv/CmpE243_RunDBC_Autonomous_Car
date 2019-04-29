// gps.c
/*#include "path_finding.h"
#include "can.h"
#include "generated_can.h"

typedef struct {
    float longitude;
    float latitude;
} coordinate;

void test_float() {
printf("float = %u double = %u\n", sizeof(float), sizeof(double));
}

/// xxx you cannot have data defined at header files
coordinate coordinate_array[] = {
        { -121.8808995, 37.33485351 },
        { -121.8806246, 37.33459682 },
        { -121.8803357, 37.33473333 },
        { -121.8800418, 37.33487361 },
        { -121.8797657, 37.33500183 },
        { -121.8794967, 37.33512216 },
        { -121.8790651, 37.33532965 },
        { -121.8785729, 37.33561995 },
        { -121.8787561, 37.33587760 },
        { -121.8789526, 37.33613898 },
        { -121.8793226, 37.33595112 },
        { -121.8794851,  37.3358711 },
        { -121.8796876, 37.33587435 },
        { -121.8799636, 37.33573306 },
        { -121.8801131, 37.33562939 },
        { -121.8804553, 37.33543522 },
        { -121.8807983, 37.33525249 },
        { -121.8811156, 37.33503936 } };

// no one else should know about these variables
// so they should all be static
bool next_checkpoint_ready = 0;
bool checkpoint_arrived = 0;
coordinate destination = { 0 };
coordinate current_checkpoint = { 0 };
coordinate current_location = { 0 };
static const int total_num_of_pts = sizeof(coordinate_array) / sizeof(coordinate);
GEO_DATA_t geo_data = { 0 };
GEO_SOURCE_DATA_t gps_source_data = { 0 };
coordinate next_checkpoint = { 0 };

void init_path_finding(void)
{
    // place current location into coordinate array
    coordinate_array[total_num_of_pts - 2].latitude = current_location.latitude;
    coordinate_array[total_num_of_pts - 2].longitude = current_location.longitude;

    // place destination location into coordinate array
    coordinate_array[total_num_of_pts - 1].latitude = destination.latitude;
    coordinate_array[total_num_of_pts - 1].longitude = destination.longitude;

    next_checkpoint = path_calculation();
}

void path_calculation(void)
{
    // decode current distance from var send from GPS
    float current_distance = geo_data.GEO_DATA_Distance;
    if (current_distance < 1) {
        next_checkpoint = path_finding();
        // fill the dbc file to gps with next_checkpoint member vars
    }
}

coordinate path_finding(void)
{
    int valid_index = 0;
    float minimum_distance = 99999;
    int min_index = -1;

    for (int current_index = 0; current_index < total_num_of_pts; current_index++) {

        // xxx gps_get_distance() can receive 'coordinate' struct type
        // check 1: distance between destination and current  vs. distance between destination and next checkpoint
        float distance_btw_dest_checkpt = gps_get_distance(coordinate_array[current_index].latitude,
coordinate_array[current_index].longitude, destination.latitude, destination.longitude);

        float distance_btw_dest_current = gps_get_distance(coordinate_array[current_index].latitude,
coordinate_array[current_index].longitude, current_location.latitude, current_location.longitude);

        if (distance_btw_dest_checkpt < distance_btw_dest_current)  // check1
                {
            coordinate_array[valid_index] = coordinate_array[current_index];
            // check 2: distance between current and checkpoint -> the minimum is the next checkpoint
            float distance_btw_checkpt_current = gps_get_distance(current_checkpoint.latitude,
current_checkpoint.longitude, coordinate_array[current_index].latitude, coordinate_array[current_index].longitude); if
(minimum_distance > distance_btw_checkpt_current) { minimum_distance = distance_btw_checkpt_current; min_index =
valid_index;
            }
            valid_index++;
        }
    }

    total_num_of_pts = valid_index;
    if (min_index != -1) return coordinate_array[min_index];
    else
        return destination;
}

void can_receive_data(void)
{
    can_msg_t can_msg = { 0 };

    // Empty all of the queued, and received messages within the last 10ms (100Hz callback frequency)
    while (CAN_rx(bridge_module, &can_msg, 0)) {
        // Form the message header from the metadata of the arriving message
        dbc_msg_hdr_t can_msg_hdr;
        can_msg_hdr.dlc = can_msg.frame_fields.data_len;
        can_msg_hdr.mid = can_msg.msg_id;

        // Attempt to decode the message (brute force, but should use switch/case with MID)
        dbc_decode_GEO_DATA(&geo_data, can_msg.data.bytes, &can_msg_hdr);
        dbc_decode_GEO_SOURCE_DATA(&gps_source_data, can_msg.data.bytes, &can_msg_hdr);
    }
}*/
