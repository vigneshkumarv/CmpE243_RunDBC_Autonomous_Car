// Functions for geographic sensors

#ifndef GPS_H__
#define GPS_H__

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include "string.h"
#include "compass.h"
#include "generated_can.h"
#include "geo_can.h"
#include "led_wrapper.h"
#include "math.h"
#include "queue.h"
#include "uart_wrapper.h"

#define PI 3.141592653

#define PMTK_SET_NMEA_OUTPUT_RMCONLY "$PMTK314,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0*29"
#define PMTK_SET_NMEA_UPDATE_10HZ "$PMTK220,100*2F"
#define PMTK_SET_NMEA_UPDATE_5HZ "$PMTK220,200*2C"
#define PMTK_SET_NMEA_UPDATE_1HZ "$PMTK220,1000*1F"
#define PMTK_SET_BAUDRATE_57600 "$PMTK251,57600*2C"
#define PMTK_SET_BAUDRATE_9600 "$PMTK251,9600*17"
#define PMTK_SET_BAUDRATE_38400 "$PMTK251,38400*27"
#define PMTK_API_SET_FIX_CTL_5HZ "$PMTK300,200,0,0,0,0*2F"  //< 5 Hz, max fix rate
#define PMTK_API_SET_SBAS_ENABLED "$PMTK313,1*2E"           // enable differential GPS
#define PMTK_API_SET_DGPS_MODE "$PMTK301,2*2E"              // set differential gps mode (WAAS for north america)
#define MAX_DATA_BUFF_LENGTH 100

queue_S longitude_data_queue;
queue_S latitude_data_queue;

void gps_module_init(void);
void gps_module_get_data(char* pBuff);

float gps_get_bearing(coordinate GPS_data, coordinate DEST_data);
float gps_get_distance(coordinate GPS_data, coordinate DEST_data);
float gps_get_deflection_angle(float gps_bearing, float compass_heading);
void gps_obtain_and_process_data(int count);
coordinate gps_obtain_data(void);
void gps_process_data(void);
void gps_get_checkpoint_coordinate(void);

#endif  // GPS_H__
