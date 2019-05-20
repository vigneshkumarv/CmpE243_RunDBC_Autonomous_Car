// gps.c
#include "gps.h"
#include "geo_can.h"

//#include "generated_can/generated_can.h"

// static float gps_data_longitude = 0;
// static float gps_data_latitude = 0;
coordinate gps_data = {0};
static bool is_data_invalid = false;
// 37.339311, -121.880707 - north garage
// 37.334840, -121.880952 - in front of event center
// static float checkpoint_latitude = 37.339311;
// static float checkpoint_longitude = -121.880707;
// large road end near eng: 37.336322, -121.882006
// in between the alleyway between SU and engineering: 37.336373, -121.881744
// behind clark hall: 37.336218, -121.883073
static char delim[] = ",";

void gps_module_init(void) {
  uart2_init(9600, 512, 512);
  uart2_putLine(PMTK_SET_BAUDRATE_57600, 20);
  uart2_init(57600, 256, 256);
  uart2_putLine(PMTK_SET_NMEA_OUTPUT_RMCONLY, 20);
  uart2_putLine(PMTK_SET_NMEA_UPDATE_10HZ, 20);
  uart2_putLine(PMTK_API_SET_FIX_CTL_5HZ, 20);
  // uart2_putLine(PMTK_API_SET_SBAS_ENABLED, 20); //enable differential GPS
  // uart2_putLine(PMTK_API_SET_DGPS_MODE, 20); //set differential gps mode (WAAS for north america)

  // FOR DEBUG PURPOSE ONLY
  // dest_data.latitude = 37.336218;
  // dest_data.longitude = -121.883073;
}

void gps_module_get_data(char* pBuff) {
  // char Char;
  // uart2_getChar(&Char, 0);
  // while (Char != '\n'){uart2_getChar(&Char, 0);}
  uart2_gets(pBuff, MAX_DATA_BUFF_LENGTH, 20);
}

void gps_obtain_and_process_data(int count) {
  if (count % 2 == 1) {
    gps_obtain_data();
  }  // count % 2
  else if (count % 2 == 0) {
    gps_process_data();
  }
}

float gps_get_bearing(coordinate GPS_data, coordinate DEST_data) {
  float bearing = 0, lon_difference = 0;
  GPS_data.latitude = (GPS_data.latitude * PI) / 180;
  GPS_data.longitude = (GPS_data.longitude * PI) / 180;
  DEST_data.latitude = (DEST_data.latitude * PI) / 180;
  DEST_data.longitude = (DEST_data.longitude * PI) / 180;
  lon_difference = DEST_data.longitude - GPS_data.longitude;

  bearing = atan2((sin(lon_difference) * cos(DEST_data.latitude)),
                  ((cos(GPS_data.latitude) * sin(DEST_data.latitude)) -
                   (sin(GPS_data.latitude) * cos(DEST_data.latitude) * cos(lon_difference))));

  bearing = (bearing * 180) / PI;

  if (bearing <= 0) bearing += 360;

  return bearing;
}

float gps_get_distance(coordinate GPS_data, coordinate DEST_data) {
  GPS_data.latitude = (GPS_data.latitude * PI) / 180;
  GPS_data.longitude = (GPS_data.longitude * PI) / 180;
  DEST_data.latitude = (DEST_data.latitude * PI) / 180;
  DEST_data.longitude = (DEST_data.longitude * PI) / 180;
  float a =
      pow(sin((DEST_data.latitude - GPS_data.latitude) / 2), 2) +
      cos(GPS_data.latitude) * cos(DEST_data.latitude) * pow(sin((DEST_data.longitude - GPS_data.longitude) / 2), 2);
  float c = 2 * atan2(sqrt(a), sqrt(1 - a));
  float distance = 6371 * 1000 * c;
  if (distance > 1000) distance = 1000;
  return distance;
}

/*float gps_get_distance(coordinate GPS_data, coordinate DEST_data) {
  float distance = 0;
  float longitude_difference = DEST_data.longitude - GPS_data.longitude;
  float latitude_differenece = DEST_data.latitude - GPS_data.latitude;
  float meter_per_degree_longitude = 88619.20;
  float meter_per_degree_latitude = 110983.91;
  distance = sqrt(pow(longitude_difference * meter_per_degree_longitude, 2) +
                  pow(latitude_differenece * meter_per_degree_latitude, 2));
  return distance;
}

float gps_get_bearing(coordinate GPS_data, coordinate DEST_data) {
  float bearing = 0;
  float longitude_difference = DEST_data.longitude - GPS_data.longitude;
  float latitude_difference = DEST_data.latitude - GPS_data.latitude;
  float meter_per_degree_longitude = 88619.20;
  float meter_per_degree_latitude = 110983.91;

  bearing = atan2(((longitude_difference * meter_per_degree_longitude) * PI / 180),
                  ((latitude_difference * meter_per_degree_latitude) * PI / 180));
  return (bearing * 180 / PI);
}*/

float gps_get_deflection_angle(float gps_bearing, float compass_heading) {
  float deflection;
  deflection = gps_bearing - compass_heading;
  if (deflection > 180)
    deflection -= 360;
  else if (deflection < -180)
    deflection += 360;

  return deflection;
}

coordinate gps_obtain_data(void) {
  coordinate coordinates = {0};
  char data_array[MAX_DATA_BUFF_LENGTH];
  int parse_counter = 0;
  // uart2_flush();
  gps_module_get_data(data_array);
  /*for (int i = 0; i < MAX_DATA_BUFF_LENGTH; i++) {
 printf("%c", data_array[i]);
 if (data_array[i] == '\0') break;
 }
printf("\n");*/
  char* ptr = strtok(data_array, delim);
  if (*ptr == '$') {
    while (parse_counter < 6) {
      ptr = strtok(NULL, delim);
      if (parse_counter == 2) {
        gps_data.latitude = atof(ptr);
      } else if (parse_counter == 3) {
        if (*ptr != 'N') {
          is_data_invalid = true;
          break;
        }
      } else if (parse_counter == 4) {
        gps_data.longitude = atof(ptr);
      } else if (parse_counter == 5) {
        if (*ptr != 'W') {
          is_data_invalid = true;
          return coordinates;
        } else {
          coordinates.latitude = gps_data.latitude;
          coordinates.longitude = gps_data.longitude;
          return coordinates;
        }
      }
      parse_counter++;
    }  // while

  }  //$
  else {
    is_data_invalid = true;
  }
  coordinate temp = {0, 0};
  return temp;
}

void gps_process_data(void) {
  float gps_longitude_avg = 0;
  float gps_latitude_avg = 0;
  if (is_data_invalid == false) {
    if (gps_data.latitude > 0) {
      float latitude_data = ((int)(gps_data.latitude / 100)) +
                            (((int)gps_data.latitude % 100) + (gps_data.latitude - (int)(gps_data.latitude))) / 60;
      // gps_latitude_avg = queue__update_and_get_average(&latitude_data_queue, latitude_data);
      gps_latitude_avg = latitude_data;
    }
    if (gps_data.longitude > 0) {
      float longitude_data = ((int)(gps_data.longitude / 100)) +
                             (((int)gps_data.longitude % 100) + (gps_data.longitude - (int)(gps_data.longitude))) / 60;
      // gps_longitude_avg = -1 * (queue__update_and_get_average(&longitude_data_queue, longitude_data));
      gps_longitude_avg = -1 * longitude_data;
      // printf("latitude: %f, longitude: %f \n", gps_latitude_avg, gps_longitude_avg);
    }
    // light up led if both lat and long decimal digits are correct
    if ((int)gps_latitude_avg == 37 && (int)gps_longitude_avg == -121)
      LED_1_on();
    else
      LED_1_off();

    coordinate gps_avg = {gps_longitude_avg, gps_latitude_avg};
    geo_coordinate_data.GEO_DATA_Latitude = gps_latitude_avg;
    geo_coordinate_data.GEO_DATA_Longitude = gps_longitude_avg;

    // if destination is received
    // printf("dest_data.latitude: %f ", dest_data.latitude);
    // printf("dest_data.longitude: %f ", dest_data.longitude);
    float gps_bearing = gps_get_bearing(gps_avg, dest_data);
    float compass_heading;
    read_compass_heading(&compass_heading);
    float gps_deflection = gps_get_deflection_angle(gps_bearing, compass_heading);
    float gps_distance = gps_get_distance(gps_avg, dest_data);
    geo_data.GEO_DATA_Distance = gps_distance;
    geo_data.GEO_DATA_Angle = gps_deflection;
    // printf("distance: %f, angle: %f \n", gps_distance, gps_deflection);
    // printf("distance: %f, angle: %f \n", gps_distance, compass_heading);
  } else {
    is_data_invalid = false;
  }
}

void gps_get_checkpoint_coordinate(void) {
  receive_checkpoint_from_bridge(&GEO_module, &BRIDGE_data);
  if (BRIDGE_data.BRIDGE_DATA_Latitude > 0 && BRIDGE_data.BRIDGE_DATA_Longitude < 0) {
    dest_data.latitude = BRIDGE_data.BRIDGE_DATA_Latitude;
    dest_data.longitude = BRIDGE_data.BRIDGE_DATA_Longitude;
    // printf("dest_data lat: %f dest_data lon: %f \n",dest_data.latitude,  dest_data.longitude );
  }
}
