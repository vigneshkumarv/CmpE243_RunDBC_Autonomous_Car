// gps.c
#include "path_finding.h"
#include "can.h"
#include "stdbool.h"
const int source_node_index = MAX_SIZE - 2;
const int destination_node_index =MAX_SIZE - 1;
float coordinate_distance[MAX_SIZE][MAX_SIZE] = {0};
static int path[MAX_SIZE];
static int path_count = 0;
static int path_current_index = 0;
//static bool checkpoint_arrived = 0;
static bool start_flag = 0;

void set_start_flag(bool value){
    start_flag = value;
}

void clear_path_count(void){
    path_count = 0;
}


int check_path_checkpoint(int index){
    return path[index];
}

bool check_destination_received(void){
    //printf("destination latitude: %f", destination.latitude);
    //printf("destination longitude: %f", destination.longitude);
    if ((destination.latitude > 0) && (destination.longitude < 0)){
        return true;
    }
    else {
        return false;
    }
}

void current_location_set(float _longitude, float _latitude) {
  current_location.longitude = _longitude;
  current_location.latitude = _latitude;
}

void destination_set(float _longitude, float _latitude) {
  destination.longitude = _longitude;
  destination.latitude = _latitude;
}

void coordinate_distance_clear(void) {
  for (int i = 0; i < MAX_SIZE; i++) {
    for (int j = 0; j < MAX_SIZE; j++) {
      coordinate_distance[i][j] = 0;
    }
  }
}

coordinate coordinate_array[MAX_SIZE] = {
    /*{37.336967, -121.879623},  // 0
    {37.337329, -121.882732},  // 1
    {37.336918, -121.882571},  // 2
    {37.336653, -121.882263},  // 3
    {37.336322, -121.882002},  // 4
    {37.336090, -121.881853},  // 5
    {37.335707, -121.881610},  // 6
    {37.335285, -121.881302},  // 7
    {37.334862, -121.880948},  // 8
    {37.334719, -121.880832},  // 9
    {37.334609, -121.880965},  // 10
    {37.334442, -121.880830},  // 11
    {37.334552, -121.880591},  // 12
    {37.334692, -121.880718},  // 13
    {37.334917, -121.879872},  // 14
    {37.335235, -121.879257},  // 15
    {37.335486, -121.878731},  // 16
    {37.336038, -121.879178},  // 17
    {37.336625, -121.879602},  // 18
    {37.336741, -121.879376},  // 19
    {37.336213, -121.880522},  // 20
    {37.337201, -121.879890},  // 21
    {37.337090, -121.880282},  // 22
    {37.336867, -121.880757},  // 23
    {37.336519, -121.881444},  // 24
    {37.337878, -121.880291},  // 25
    {37.338233, -121.880664},  // 26
    {37.337853, -121.881517},  // 27
    {37.336398, -121.880044},  // 28
    {37.336188, -121.879991},  // 29
    {37.335845, -121.881435},  // 30
    {37.335744, -121.881367},  // 31
    {37.335835, -121.881320},  // 32
    {37.336042, -121.880876},  // 33
    {37.337371, -121.879875},  // 34
    {37.337747, -121.879745},  // 35
    {37.337904, -121.879467},  // 36
    {37.337570, -121.879606},  // 37
    {37.337671, -121.879200},  // 38
    {37.336111, -121.878925},  // 39
    {37.335636, -121.878575},  // 40
    {37.335877, -121.882245},  // 41
    {37.334405, -121.881305},  // 42
    {37.335474, -121.878480},  // 43
    {37.336487, -121.878298},  // 44
    {37.336737, -121.882007},  // 45 (temp) right outside ieee
    {37.337172, -121.882282},  // 46 (temp) corner of eng
    {37.337405, -121.881912},  // 47 (temp) after L corner
    {0, 0},                    // 45 //48
    {0, 0},                    // 46  //49
*/
            {37.339608, -121.881315},  // 0
            {37.339762, -121.881038},  // 1
            {37.339888, -121.880800},  // 2
            {37.339676, -121.880650},  // 3
            {37.339284, -121.880351},  // 4
            {37.338996, -121.880102},  // 5
            {37.338844, -121.880422},  // 6
            {37.338735, -121.880648},  // 7
            {37.339239, -121.880851},  // 8
            {37.339531, -121.881149},  // 9
            {37.339432, -121.881028},  // 10
            {37.339101, -121.880781},  // 11
            {0, 0},  // 12 source
            {0, 0},  // 13 destination

};
void make_all_paths(void) {
  /*make_path(0, 21);
  make_path(0, 19);
  make_path(1, 2);
  make_path(2, 3);
  make_path(3, 4);
  make_path(4, 5);
  make_path(4, 24);
  make_path(5, 41);
  make_path(5, 6);
  make_path(6, 30);
  make_path(6, 31);
  make_path(6, 7);
  make_path(7, 8);
  make_path(8, 9);
  make_path(9, 10);
  make_path(9, 13);
  make_path(10, 42);
  make_path(10, 11);
  make_path(11, 12);
  make_path(12, 13);
  make_path(12, 14);
  make_path(13, 9);
  make_path(13, 12);
  make_path(14, 15);
  make_path(15, 16);
  make_path(16, 40);
  make_path(16, 17);
  make_path(17, 39);
  make_path(17, 18);
  make_path(17, 39);
  make_path(18, 19);
  make_path(18, 28);
  make_path(19, 39);
  make_path(20, 33);
  make_path(20, 28);
  make_path(21, 34);
  make_path(21, 22);
  make_path(22, 23);
  make_path(23, 24);
  make_path(25, 26);
  make_path(25, 34);
  make_path(26, 27);
  make_path(28, 29);
  make_path(30, 32);
  make_path(31, 32);
  make_path(32, 33);
  make_path(34, 37);
  make_path(34, 35);
  make_path(35, 36);
  make_path(35, 37);
  make_path(36, 38);
  make_path(37, 38);
  make_path(39, 44);
  make_path(40, 43);

  //---------------------
  make_path(45,46);
  make_path(46,47); */
    make_path(0, 1);
    make_path(1, 2);
    make_path(2, 3);
    make_path(3, 4);
    make_path(4, 5);
    make_path(5, 6);
    make_path(6, 7);
    make_path(7, 11);
    make_path(11, 8);
    make_path(8, 10);
    make_path(9, 10);
    make_path(9, 0);
}

void bridge_path_finding(void) {
   // printf("start_flag: %d \n", start_flag);
  if (start_flag == 0){
      calculate_distance();
      init_path_finding();
      dijkstra(coordinate_distance, MAX_SIZE, source_node_index, destination_node_index);
      /*
      for (int i = path_count-1; i >= 0; i-- ){
          printf("%d ", path[i]);
      }
      printf("\n");
      */
  }
  start_flag = 1;
}

void init_path_finding(void) {

    //printf("current_location latitude: %f long: %f \n", current_location.latitude, current_location.longitude);
  // place current location gotten from GPS into coordinate array
  coordinate_array[MAX_SIZE - 2].latitude = current_location.latitude;
  coordinate_array[MAX_SIZE - 2].longitude = current_location.longitude;
  // place destination location into coordinate array
  coordinate_array[MAX_SIZE - 1].latitude = destination.latitude;
  coordinate_array[MAX_SIZE - 1].longitude = destination.longitude;

  float min_distance_start = INF;
  int min_index_start = -1;

  float min_distance_dest = INF;
  int min_index_dest = -1;

  for (int i = 0; i < MAX_SIZE - 2; i++) {
    if (gps_get_distance(coordinate_array[MAX_SIZE - 2], coordinate_array[i]) < min_distance_start) {
      min_distance_start = gps_get_distance(coordinate_array[MAX_SIZE - 2], coordinate_array[i]);
      min_index_start = i;
    }
    if (gps_get_distance(coordinate_array[MAX_SIZE - 1], coordinate_array[i]) < min_distance_dest) {
      min_distance_dest = gps_get_distance(coordinate_array[MAX_SIZE - 1], coordinate_array[i]);
      min_index_dest = i;
    }
  }
  make_path(MAX_SIZE - 2, min_index_start);
  //printf(" min_index_start: %d", min_index_start);
  make_path(MAX_SIZE - 1, min_index_dest);
  //printf(" min_index_dest: %d\n", min_index_dest);
}

void path_finding_main(void) {
  if (start_flag == 1) {
      current_location.latitude = geo_source_data.GEO_DATA_Latitude;
      current_location.longitude = geo_source_data.GEO_DATA_Longitude;

      if (is_checkpoint_arrived()) {
        if (path_current_index  != 0)
            path_current_index--;
      }
      bridge_checkpoint.BRIDGE_DATA_Latitude = coordinate_array[path[path_current_index]].latitude;
      bridge_checkpoint.BRIDGE_DATA_Longitude = coordinate_array[path[path_current_index]].longitude;
     // printf("bridge_checkpoint latitude: %f\n", bridge_checkpoint.BRIDGE_DATA_Latitude);
     // printf("bridge_checkpoint longitude: %f\n", bridge_checkpoint.BRIDGE_DATA_Longitude);
     // printf("checkpoint index: %d\n", path[path_current_index]);
      // send can msg to geo for the checkpoint coordinate
      can_msg_t can_msg_checkpoint;
      dbc_msg_hdr_t checkpoint_hdr;
      checkpoint_hdr = dbc_encode_BRIDGE_CHECKPOINT(can_msg_checkpoint.data.bytes, &bridge_checkpoint);
      can_msg_checkpoint.msg_id = checkpoint_hdr.mid;
      can_msg_checkpoint.frame_fields.data_len = checkpoint_hdr.dlc;
      CAN_tx(can1, &can_msg_checkpoint, 0);
  }
}

bool is_checkpoint_arrived(void) {
  return (gps_get_distance(current_location, coordinate_array[path[path_current_index]]) < 10);
}

void calculate_distance(void) {
  // for each matrix entry, calculate distance relative to others and store into array
  for (int i = 0; i < MAX_SIZE; i++) {
    for (int j = 0; j < MAX_SIZE; j++) {
      if (i == j)  // same entry
      {
        coordinate_distance[i][j] = 0;
      } else {
        coordinate_distance[i][j] = INF;
      }
    }
  }

  make_all_paths();
}

void make_path(int i, int j) {
  coordinate_distance[i][j] = gps_get_distance(coordinate_array[i], coordinate_array[j]);
  coordinate_distance[j][i] = coordinate_distance[i][j];
}

void dijkstra(float cost[MAX_SIZE][MAX_SIZE], int n, int startnode, int endnode) {
  // float cost[MAX_SIZE][MAX_SIZE],
  float distance[MAX_SIZE];
  int pred[MAX_SIZE];
  int visited[MAX_SIZE];
  int count;
  int nextnode = -1;
  int i, j;
  float mindistance;

  // initialize pred[],distance[] and visited[]
  for (i = 0; i < n; i++) {
    distance[i] = cost[startnode][i];
    pred[i] = startnode;
    visited[i] = 0;
  }

  distance[startnode] = 0;
  visited[startnode] = 1;
  count = 1;
  while (count < n - 1) {
    mindistance = INF;
    // nextnode gives the node at minimum distance
    for (i = 0; i < n; i++) {
      if (distance[i] < mindistance && !visited[i]) {
        mindistance = distance[i];
        nextnode = i;
      }
    }

    // check if a better path exists through nextnode
    visited[nextnode] = 1;
    for (i = 0; i < n; i++)
      if (!visited[i])
        if (mindistance + cost[nextnode][i] < distance[i]) {
          distance[i] = mindistance + cost[nextnode][i];
          pred[i] = nextnode;
        }
    count++;
  }

  j = endnode;
  path[path_count] = endnode;
  path_count++;
  do {
    j = pred[j];
    path[path_count] = j;
    path_count++;
  } while (j != startnode);

  path_current_index = path_count - 1;
}

float gps_get_distance(coordinate gps_data, coordinate dest_data) {
  gps_data.latitude = (gps_data.latitude * PI) / 180;
  gps_data.longitude = (-gps_data.longitude * PI) / 180;
  dest_data.latitude = (dest_data.latitude * PI) / 180;
  dest_data.longitude = (-dest_data.longitude * PI) / 180;

  float a =
      pow(sin((dest_data.latitude - gps_data.latitude) / 2), 2) +
      cos(gps_data.latitude) * cos(dest_data.latitude) * pow(sin((dest_data.longitude - gps_data.longitude) / 2), 2);
  float c = 2 * atan2(sqrt(a), sqrt(1 - a));
  float distance = 6371 * 1000 * c;
  return distance;
}
