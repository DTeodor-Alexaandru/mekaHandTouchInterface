#pragma once

#include "sensor_array/sensor_array.h"
#include <stdint.h>

#define DAQ_TOTAL_SENSORS  (NUM_ADC_CH * NUM_MUX_CH)

void comms_send(const float filtered[]);
