// display_lcd.c

#include "display_lcd.h"
#include <stdio.h>
#include <string.h>
#include "switches_wrapper.h"

static uint8_t switch_count = 0;
static uint8_t switch_select = 4;

static const uint8_t SWITCH_DEBOUNCE = 2;

static char line_buff[40];
// static const char* line_ptr = &line_buff;

void initialize_display_lcd(void) {
  init_serial_lcd();
  init_switches();
}

void display_screens(uint32_t count, navigation_state_machine_S state_variables, GEO_DATA_t geo_data,
                     GEO_COORDINATE_DATA_t geo_coordinates, GEO_DEBUG_DATA_t geo_debug,
                     navigation_motor_cmd_S motor_command, MOTOR_DATA_t motor_actual,
                     navigation_sensors_S sensor_data) {
  bool switch_state = getSwitch(1);
  if (switch_state && (switch_count == SWITCH_DEBOUNCE)) {
    if (4 == switch_select) {
      switch_select = 1;
    } else {
      switch_select++;
    }
  }
  if (switch_state) {
    switch_count++;
  } else {
    switch_count = 0;
  }

  switch (switch_select) {
    case 1:
      display_operation_data(count, state_variables, geo_data, geo_coordinates, motor_command, motor_actual);
      break;
    case 2:
      display_sensor_data(count, sensor_data);
      break;
    case 3:
      display_motor_debug();
      break;
    case 4:
      display_geo_debug(count, geo_data, geo_coordinates, geo_debug);
      break;
    default:
      display_operation_data(count, state_variables, geo_data, geo_coordinates, motor_command, motor_actual);
      break;
  }
}

void display_operation_data(uint32_t count, navigation_state_machine_S state_variables, GEO_DATA_t geo_data,
                            GEO_COORDINATE_DATA_t geo_coordinates, navigation_motor_cmd_S motor_command,
                            MOTOR_DATA_t motor_actual) {
  if (0 == count % 5) {
    //      clear_screen();
    char dir_cmd = ' ';
    if (motor_command.motor_direction == 2) {
      dir_cmd = '-';
    } else {
      dir_cmd = '+';
    }

    sprintf(line_buff, "SPEED cmd:%c%f0.2 mps", dir_cmd, motor_command.motor_speed);
    //      sprintf(line_buff, "test line 0");
    print_seg(0, 0, line_buff, 20);
    //      print_line(0, line_buff);
    printf("%s\n", line_buff);
  }

  if (1 == count % 5) {
    char nav_go[5];
    if (state_variables.go) {
      strcpy(nav_go, " GO ");
    } else {
      strcpy(nav_go, "STOP");
    }

    char dir_act = ' ';
    if (motor_actual.MOTOR_DATA_direction == 2) {
      dir_act = '-';
    } else {
      dir_act = '+';
    }

    sprintf(line_buff, "%s  act:%c%f mps", nav_go, dir_act, motor_actual.MOTOR_DATA_speed);
    //  sprintf(line_buff, "test line 1");
    print_seg(1, 0, line_buff, 20);
    //  print_line(1, line_buff);
    printf("%s\n", line_buff);
  }

  if (2 == count % 5) {
    sprintf(line_buff, "STEER: %0i* D%fm", motor_actual.MOTOR_DATA_steer, geo_data.GEO_DATA_Distance);
    //      sprintf(line_buff, "test line 2");
    print_seg(2, 0, line_buff, 20);
    //      print_line(2, line_buff);
  }

  if (3 == count % 5) {
    // PLACEHOLDER: this needs actual data from geo debug message
    sprintf(line_buff, "XX  STATE:%i A%f*", state_variables.state, geo_data.GEO_DATA_Angle);
    //  sprintf(line_buff, "test line 3");
    print_seg(3, 0, line_buff, 20);
    //  print_line(3, line_buff);
    printf("%s\n\n", line_buff);
  }
}

void display_sensor_data(uint32_t count, navigation_sensors_S sensor_data) {
  if (0 == count % 5) {
    sprintf(line_buff, "Left:   %i cm", sensor_data.left_ultrasonic_cm);
    print_seg(0, 0, line_buff, 20);
  }
  if (1 == count % 5) {
    sprintf(line_buff, "Middle: %i cm", sensor_data.middle_ultrasonic_cm);
    print_seg(1, 0, line_buff, 20);
  }
  if (2 == count % 5) {
    sprintf(line_buff, "Right:  %i cm", sensor_data.right_ultrasonic_cm);
    print_seg(2, 0, line_buff, 20);
  }
  if (3 == count % 5) {
    sprintf(line_buff, "Rear:   %i cm", sensor_data.rear_ir_cm);
    print_seg(3, 0, line_buff, 20);
  }
}

void display_motor_debug(void) { clear_screen(); }

void display_geo_debug(uint32_t count, GEO_DATA_t geo_data, GEO_COORDINATE_DATA_t geo_coordinates,
                       GEO_DEBUG_DATA_t geo_debug) {
  if (0 == count % 5) {
    sprintf(line_buff, "Lat: %f", geo_coordinates.GEO_DATA_Latitude);
    print_seg(0, 0, line_buff, 20);
  }
  if (1 == count % 5) {
    sprintf(line_buff, "Lon: %f", geo_coordinates.GEO_DATA_Longitude);
    print_seg(1, 0, line_buff, 20);
  }
  if (2 == count % 5) {
    //        sprintf(line_buff, "head: %f", geo_debug.GEO_COMPASS_Heading);
    sprintf(line_buff, "d:%fH:%f", geo_data.GEO_DATA_Angle, geo_debug.GEO_COMPASS_Heading);
    print_seg(2, 0, line_buff, 20);
  }
  if (3 == count % 5) {
    sprintf(line_buff, "cal: 0x%X %f", geo_debug.GEO_COMPASS_Calibration, geo_data.GEO_DATA_Distance);
    print_seg(3, 0, line_buff, 20);
  }
}
