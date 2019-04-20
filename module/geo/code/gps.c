// gps.c
#include "gps.h"

static float gps_data_longitude = 0;
static float gps_data_latitude = 0;
static bool is_data_invalid = false;
static float destination_latitude = 37.33485;
static float destination_longitude = -121.880899;
static char delim[] = ",";

void gps_module_init(void) {
  uart2_init(9600, 512, 512);
  uart2_putLine(PMTK_SET_BAUDRATE_57600, 20);
  uart2_init(57600, 256, 256);
  uart2_putLine(PMTK_SET_NMEA_OUTPUT_RMCONLY, 20);
  uart2_putLine(PMTK_SET_NMEA_UPDATE_10HZ, 20);
  uart2_putLine(PMTK_API_SET_FIX_CTL_5HZ, 20);
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

float gps_get_bearing(float gps_latitude, float gps_longitude, float des_latitude, float des_longitude) {
  double bearing = 0, lon_difference = 0;
  gps_latitude = (gps_latitude * PI) / 180;
  gps_longitude = (-gps_longitude * PI) / 180;
  des_latitude = (des_latitude * PI) / 180;
  des_longitude = (des_longitude * PI) / 180;
  lon_difference = des_longitude - gps_longitude;

  bearing =
      atan2((sin(lon_difference) * cos(des_latitude)),
            ((cos(gps_latitude) * sin(des_latitude)) - (sin(gps_latitude) * cos(des_latitude) * cos(lon_difference))));
  bearing = (bearing * 180) / PI;

  if (bearing <= 0) bearing += 360;

  return bearing;
}

float gps_get_distance(float gps_latitude, float gps_longitude, float des_latitude, float des_longitude) {
  gps_latitude = (gps_latitude * PI) / 180;
  gps_longitude = (-gps_longitude * PI) / 180;
  des_latitude = (des_latitude * PI) / 180;
  des_longitude = (des_longitude * PI) / 180;
  float a = pow(sin((des_latitude - gps_latitude) / 2), 2) +
            cos(gps_latitude) * cos(des_latitude) * pow(sin((des_longitude - gps_longitude) / 2), 2);
  float c = 2 * atan2(sqrt(a), sqrt(1 - a));
  float distance = 6371 * 1000 * c;
  return distance;
}

float gps_get_deflection_angle(float gps_bearing, float compass_heading) {
  float deflection;
  deflection = gps_bearing - compass_heading;
  if (deflection > 180)
    deflection -= 360;
  else if (deflection < -180)
    deflection += 360;

  return deflection;
}

void gps_obtain_data(void) {
  char data_array[MAX_DATA_BUFF_LENGTH];
  int parse_counter = 0;
  // uart2_flush();
  gps_module_get_data(data_array);
  /*for (int i = 0; i < MAX_DATA_BUFF_LENGTH; i++) {
   printf("%c", data_array[i]);
   if (data_array[i] == '\0') break;
   }*/

  char* ptr = strtok(data_array, delim);
  if (*ptr == '$') {
    while (parse_counter < 6) {
      ptr = strtok(NULL, delim);
      if (parse_counter == 2) {
        gps_data_latitude = atof(ptr);
      } else if (parse_counter == 3) {
        if (*ptr != 'N') {
          is_data_invalid = true;
          break;
        }
      } else if (parse_counter == 4) {
        gps_data_longitude = atof(ptr);
      } else if (parse_counter == 5) {
        if (*ptr != 'W') {
          is_data_invalid = true;
          break;
        }
      }
      parse_counter++;
    }  // while

  }  //$
  else {
    is_data_invalid = true;
  }
}

void gps_process_data(void) {
  float gps_longitude_avg = 0;
  float gps_latitude_avg = 0;
  if (is_data_invalid == false) {
    if (gps_data_latitude > 0) {
      float latitude_data = ((int)(gps_data_latitude / 100)) +
                            (((int)gps_data_latitude % 100) + (gps_data_latitude - (int)(gps_data_latitude))) / 60;
      gps_latitude_avg = queue__update_and_get_average(&latitude_data_queue, latitude_data);
    }
    if (gps_data_longitude > 0) {
      float longitude_data = ((int)(gps_data_longitude / 100)) +
                             (((int)gps_data_longitude % 100) + (gps_data_longitude - (int)(gps_data_longitude))) / 60;
      gps_longitude_avg = queue__update_and_get_average(&longitude_data_queue, longitude_data);
      // printf(" longitude: %f \n", gps_longitude_avg);
    }

    float gps_bearing =
        gps_get_bearing(gps_latitude_avg, gps_longitude_avg, destination_latitude, destination_longitude);
    float compass_heading;
    read_compass_heading(&compass_heading);
    float gps_deflection = gps_get_deflection_angle(gps_bearing, compass_heading);
    float gps_distance =
        gps_get_distance(gps_latitude_avg, gps_longitude_avg, destination_latitude, destination_longitude);
    geo_data.GEO_DATA_Distance = gps_distance;
    geo_data.GEO_DATA_Angle = gps_deflection;
    printf("distance: %f, angle: %f \n", gps_distance, gps_deflection);
  } else {
    is_data_invalid = false;
  }
}
