// gps.c
#include "path_finding.h"
#include "can.h"
#include "stdbool.h"
//#include "Z:\CMPE243\SJSU_Dev\projects\bridge_project\generated_can\generated_can.h"
#include "generated_can.h"
const int source_node_index = 62;
const int destination_node_index = 63;
float coordinate_distance[MAX_SIZE][MAX_SIZE] = {0};
static int path[MAX_SIZE];
static int path_count = 0;
static int path_current_index = 0;
//static bool checkpoint_arrived = 0;
//coordinate destination = {37.1232, -121.893274};

//extern GEO_COORDINATE_DATA_t geo_source_data;

void current_location_set (float _longitude, float _latitude){
    current_location.longitude = _longitude;
    current_location.latitude = _latitude;
}

void destination_set (float _longitude, float _latitude){
    destination.longitude = _longitude;
    destination.latitude = _latitude;
}

void coordinate_distance_clear(void){
    for (int i = 0; i < MAX_SIZE; i++){
        for (int j = 0; j < MAX_SIZE; j++){
            coordinate_distance_clear[i][j] = 0;
        }
    }
}

coordinate coordinate_array[MAX_SIZE] = {
    {37.336714, -121.881036},   // 0
    {37.336512, -121.881447},   // 1
    {37.336274, -121.881936},   // 2
    {37.336160, -121.881827},   // 3
    {37.335716, -121.881604},   // 4
    {37.335312, -121.881314},   // 5
    {37.334865, -121.880945},   // 6
    {37.334688, -121.880741},   // 7
    {37.334577, -121.880629},   // 8
    {37.334385, -121.880791},   // 9
    {37.334561, -121.880932},   // 10
    {37.334871, -121.879913},   // 11
    {37.335276, -121.879198},   // 12
    {37.335492, -121.878728},   // 13
    {37.336024, -121.879180},   // 14
    {37.336620, -121.879590},   // 15
    {37.336727, -121.879392},   // 16
    {37.337282, -121.879837},   // 17
    {37.337068, -121.880311},   // 18
    {37.336207, -121.880494},   // 19
    {37.335878, -121.881217},   // 20
    {37.335981, -121.882168},   // 21
    {37.335803, -121.882439},   // 22
    {37.335675, -121.882883},   // 23
    {37.335592, -121.883052},   // 24
    {37.335503, -121.883368},   // 25
    {37.335576, -121.884412},   // 26
    {37.335333, -121.883640},   // 27
    {37.335133, -121.883496},   // 28
    {37.334935, -121.883925},   // 29
    {37.336168, -121.883190},   // 30
    {37.335941, -121.883649},   // 31
    {37.335235, -121.882787},   // 32
    {37.334963, -121.883364},   // 33
    {37.335031, -121.883169},   // 34
    {37.335133, -121.882706},   // 35
    {37.335342, -121.882255},   // 36
    {37.335024, -121.882032},   // 37
    {37.334549, -121.883099},   // 38
    {37.334658, -121.882885},   // 39
    {37.334363, -121.883510},   // 40
    {37.335048, -121.881835},   // 41
    {37.336719, -121.882324},   // 42
    {37.336803, -121.882455},   // 43
    {37.337199, -121.882743},   // 44
    {37.333976, -121.883175},   // 45
    {37.333822, -121.883054},   // 46
    {37.333666, -121.882851},   // 47
    {37.333396, -121.883390},   // 48
    {37.334067, -121.881966},   // 49
    {37.334396, -121.881311},   // 50
    {37.334193, -121.881160},   // 51
    {37.333994, -121.881587},   // 52
    {37.334883, -121.878115},   // 53
    {37.337891, -121.880282},   // 54
    {37.336718, -121.883519},   // 55
    {37.335841, -121.883899},   // 56
    {37.336351, -121.884271},   // 57
    {37.335852, -121.881449},  // 58
    {37.335725, -121.881353},  // 59
    {37.335372, -121.884266}, //60
    {37.335530, -121.883943}, //61
    {0, 0},                     // start (62) //(37.3374399, -121.8811722)
    {0, 0},     //DUMMY DESTINATION                // destination  (63) (37.3356233, -121.8829749)
};


void bridge_path_finding(void) {
  calculate_distance();
  init_path_finding();
  // coordinate array is already populated, now calculate distance matrix
  //printf("pt between dest and source: %f\n", coordinate_distance[60][61]);
  dijkstra(coordinate_distance, MAX_SIZE, source_node_index, destination_node_index);
  /*
  for (int i = path_count-1; i >= 0; i-- ){
      printf("%d ", path[i]);
  }
  printf("\n");
  */
}

void init_path_finding(void) {
  // place current location gotten from GPS into coordinate array
  coordinate_array[MAX_SIZE - 2].latitude = current_location.latitude;
  coordinate_array[MAX_SIZE - 2].longitude = current_location.longitude;
  // place destination location into coordinate array
  coordinate_array[MAX_SIZE - 1].latitude = destination.latitude;
  coordinate_array[MAX_SIZE - 1].longitude = destination.longitude;
/*
    coordinate_array[MAX_SIZE - 2].latitude = 37.337440;
    coordinate_array[MAX_SIZE - 2].longitude = -121.881172;
    coordinate_array[MAX_SIZE - 1].latitude = 37.335623;
    coordinate_array[MAX_SIZE - 1].longitude =  -121.882974;
*/
  float min_distance_start = INF;
  int min_index_start = -1;

  float min_distance_dest = INF;
  int min_index_dest = -1;

  for (int i = 0; i < MAX_SIZE - 2; i++) {
      //printf("gps_get_distance(coordinate_array[MAX_SIZE - 2], coordinate_array[i]): %f\n", gps_get_distance(coordinate_array[MAX_SIZE - 2], coordinate_array[i]));
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
  make_path(MAX_SIZE - 1, min_index_dest);
}

void path_finding_main(void) {
  current_location.latitude = geo_source_data.GEO_DATA_Latitude;
  current_location.longitude = geo_source_data.GEO_DATA_Longitude;
  if (is_checkpoint_arrived()) {
    path_current_index--;
    bridge_checkpoint.BRIDGE_DATA_Latitude = coordinate_array[path[path_current_index]].latitude;
    bridge_checkpoint.BRIDGE_DATA_Longitude = coordinate_array[path[path_current_index]].longitude;
  }
  // send can msg to geo for the checkpoint coordinate
}

bool is_checkpoint_arrived(void) {
  return (gps_get_distance(current_location, coordinate_array[path[path_current_index]]) < 2);
}

void calculate_distance(void) {

  // for each matrix entry, calculate distance relative to others and store into array
  for (int i = 0; i < MAX_SIZE; i++) {
    for (int j = 0; j < MAX_SIZE; j++) {
      if (i == j)  // same entry
      {
          coordinate_distance[i][j] = 0;
      }
      else {
          coordinate_distance[i][j] = INF;
      }
    }
  }

  make_all_paths();
}

void make_all_paths(void) {
  // get rid of invalid paths
  make_path(0, 1);
  make_path(0, 18 );  // pt0: only available to pt 1 and 18
  make_path(1, 2 );   // pt1: 0 and 2
  make_path(2, 42 );
  make_path(2, 3 );  // pt2: 1 and 3 and 42
  make_path(3, 21 );
  make_path(3, 4 );  // pt3: 2 and 4 and 21
  make_path(4, 5 );
  make_path(4, 59 );
  make_path(4, 58 );  // pt4: 3, 5, 59
  make_path(5, 6 );
  make_path(5, 41 );  // pt5: 4 and 6, 41
  make_path(6, 7 );
  make_path(6, 10 );  // pt6: 5 and 7 and 10
  make_path(7, 8 );
  make_path(7, 10 );  // pt7: 6 and 8 and 10
  make_path(8, 9 );
  make_path(8, 11 );  // pt8: 7 and 9 and 11
  make_path(9, 51 );
  make_path(9, 10 );   // pt9: 10 and 8 and 51
  make_path(10, 50 );  // pt10: 6 and 7 and 9 and 50
  make_path(11, 12 );  // pt11: 8 and 12
  make_path(12, 13 );  // pt12: 11 and 13
  make_path(13, 53 );
  make_path(13, 14 );  // pt13: 12 and 14 and 53
  make_path(14, 15 );  // pt14: 13 and 15
  make_path(15, 16 );
  make_path(15, 19 );  // pt15: 16 and 19
  make_path(16, 17 );  // pt16: 17 and 15
  make_path(17, 54 );
  make_path(17, 18 );  // pt17: 18 and 16 and 54
                                           // pt18: 0 and 17
  make_path(19, 20 );  // pt19: 15 and 20
  make_path(20, 59 );
  make_path(20, 58 );  // pt20: 4 and 19, 58, 59
  make_path(21, 22 );  // pt21: 3 and 22
  make_path(22, 23 );  // pt22: 23 and 21
  make_path(23, 24 );
  make_path(23, 30 );  // pt23: 24 and 30 and 22
  make_path(24, 25 );
  make_path(24, 32 );  // pt24: 23, 25, and 32
  make_path(25, 27 );
  make_path(25, 61 );
  make_path(25, 31 );  // pt25: 24, 27 and 31, 61
  make_path(26, 56 );
  make_path(26, 60 );
  make_path(26, 61 );  // pt26: 61, 60, and 56
  make_path(27, 28 );  // pt27: 25, 28
  make_path(28, 29 );
  make_path(28, 33 );  // pt28: 27 29 and 33
  make_path(29, 60 );
  make_path(29, 40 );  // pt29: 60, 28 and 40
  make_path(30, 42 );
  make_path(30, 55 );
  make_path(30, 31 );  // pt30: 31, 23 and 42 55
  make_path(31, 56 );  // pt31:  56 and 30
  make_path(32, 35 );
  make_path(32, 34 );  // pt32: 24, 34 and 35
  make_path(33, 34 );  // pt33: 28 and 34
  make_path(34, 39 );  // pt34: 39, 33 and 32
  make_path(35, 36 );  // pt35: 32 and 36
  make_path(36, 37 );  // pt36: 35 and 37
  make_path(37, 41 );
  make_path(37, 39 );  // pt37: 41 and 36 and 39
  make_path(38, 40 );
  make_path(38, 39 );  // pt38: 40 and 39
                                           // pt39: 34, 38 and 37
  make_path(40, 45 );  // pt40: 45, 38 and 29
                                           // pt41: 37, 5
  make_path(42, 43 );  // pt42: 2 30 and 43
  make_path(43, 44 );  // pt43: 44 and 42
                                           // pt44: 43
  make_path(45, 46 );  // pt45: 40 46
  make_path(46, 47 );  // pt46: 45 and 47
  make_path(47, 48 );
  make_path(47, 49 );  // pt47: 48 and 49
                                           // pt48: 47
  make_path(49, 50 );
  make_path(49, 52 );  // pt49: 52 and 47, and 50
  make_path(50, 51 );  // pt50: 51 and 49, 10
  make_path(51, 52 );  // pt51: 50 and 9, 52
                                           // pt52: 51 and 49
                                           // pt53: 13
                                           // pt54: 17
                                           // pt55: 30
  make_path(56, 57 );  // pt56: 26, 30, 57
                                           // pt57: 56
                                           // pt58: 4, 20
                                           // pt59: 4, 20
  make_path(60, 61 );  // pt60: 61, 29, 26
  // pt61: 60, 25, 26

  //make_path(62, 0, coordinate_distance);
  //make_path(63, 24, coordinate_distance);
}

void make_path(int i, int j) {
  coordinate_distance[i][j] = gps_get_distance(coordinate_array[i], coordinate_array[j]);
  coordinate_distance[j][i] = coordinate_distance[i][j];
}

void dijkstra(float cost[MAX_SIZE][MAX_SIZE], int n, int startnode, int endnode) {
  //float cost[MAX_SIZE][MAX_SIZE],
  float distance[MAX_SIZE];
  int pred[MAX_SIZE];
  int visited[MAX_SIZE];
  int count;
  int nextnode = -1;
  int i, j;
  float mindistance;

  // pred[] stores the predecessor of each node
  // count gives the number of nodes seen so far
  // create the cost matrix
  /*for (i = 0; i < n; i++)
    for (j = 0; j < n; j++)
      if (G[i][j] == 0)
      {
          cost[i][j] = INF;
         // printf("%f ", cost[i][j]);
      }

      else
      {
          cost[i][j] = G[i][j];

         // printf("%f ", cost[i][j]);
      }*/

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
    for (i = 0; i < n; i++){
        //printf("i: %d\n" , i);
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

  // print the path and distance for a specific destination node
  //printf("\nDistance of node%d = %f \n", endnode, distance[endnode]);

  j = endnode;
  path[path_count] = endnode;
  path_count++;
  do {
    j = pred[j];
    path[path_count] = j;
    path_count++;
  } while (j != startnode);

  path_current_index = path_count - 1;

  /*for (int i = path_current_index; i >= 0; i--) {
      printf(" %d ", path[i]);
  }
  printf("\n");*/
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
