#!/bin/bash

# 
# This file executes from the build directory by the Eclipse "Pre Build" step
#

python ../../../../shared_code/_can_dbc/dbc_parse.py -i ../../../../shared_code/_can_dbc/243.dbc -s DRIVER > ../generated_can/generated_can.h