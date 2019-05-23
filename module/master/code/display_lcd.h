// display_lcd.h

#ifndef DISPLAY_LCD_H_
#define DISPLAY_LCD_H_

#include <stdbool.h>
#include <stdint.h>
#include "Serial_LCD.h"
#include "generated_can.h"
#include "navigation.h"

void initialize_display_lcd(void);
void display_screens(uint32_t count, navigation_state_machine_S state_variables, GEO_DATA_t geo_data,
                     GEO_COORDINATE_DATA_t geo_coordinates, GEO_DEBUG_DATA_t geo_debug,
                     navigation_motor_cmd_S motor_command, MOTOR_DATA_t motor_actual, navigation_sensors_S sensor_data);
void display_operation_data(uint32_t count, navigation_state_machine_S state_variables, GEO_DATA_t geo_data,
                            GEO_DEBUG_DATA_t geo_debug, navigation_motor_cmd_S motor_command,
                            MOTOR_DATA_t motor_actual);
void display_sensor_data(uint32_t count, navigation_sensors_S sensor_data);
void display_motor_debug(void);
void display_geo_debug(uint32_t count, GEO_DATA_t geo_data, GEO_COORDINATE_DATA_t geo_coordinates,
                       GEO_DEBUG_DATA_t geo_debug);

#endif /* DISPLAY_LCD_H_ */
