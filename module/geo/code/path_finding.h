// Functions for geographic sensors

#ifndef PATH_FINDING_H__
#define PATH_FINDING_H__

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include "compass.h"
#include "generated_can.h"
#include "math.h"
#include "queue.h"

void init_path_finding(void);
void path_calculation(void);
/**
 * find_path() only needs to run at a slow rate like 1hz
 */
coordinate path_finding(void);

void can_receive_data(void);
#endif  // PATH_FINDING_H__
