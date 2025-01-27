// Functions for geographic sensors

#ifndef PATH_FINDING_H__
#define PATH_FINDING_H__

#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include "bridge_can.h"
#include "generated_can.h"
//#include "queue.h"

#define PI 3.141592653
#define INF 9999
#define MAX_SIZE 14

typedef struct {
  float latitude;
  float longitude;
} coordinate;

BRIDGE_CHECKPOINT_t bridge_checkpoint;
coordinate current_location;
coordinate destination;

// This function adds 2 more points (destination and source) to the coordinate array
// and make path with the nearst checkpoint
void init_path_finding(void);
// void path_calculation(void);

// function taken from geo module
float gps_get_distance(coordinate gps_data, coordinate dest_data);

// function that fills up the nxn matrix filled with distance values. uses the possible_path[] array
void calculate_distance(void);

// path finding algorithm
void dijkstra(float cost[MAX_SIZE][MAX_SIZE], int n, int startnode, int endnode);

// the initialization main code for path finding, for bridge module
void bridge_path_finding(void);

// main function for path finding, called in periodic task
void path_finding_main(void);

bool check_destination_received(void);

// functions that mark path between two points as valid path
void make_all_paths(void);
void make_path(int i, int j);

void can_receive_data(void);

bool is_checkpoint_arrived(void);

void current_location_set(float _longitude, float _latitude);

void destination_set(float _longitude, float _latitude);

void coordinate_distance_clear(void);

int check_path_checkpoint(int index);

void set_start_flag(bool value);

void clear_path_count(void);
#endif  // PATH_FINDING_H__
