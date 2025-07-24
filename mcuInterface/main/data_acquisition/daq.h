#pragma once

#include <stdint.h>
#include "sensor_array/sensor_array.h"

#define DAQ_TOTAL_SENSORS  (NUM_ADC_CH * NUM_MUX_CH)

typedef struct {
    uint32_t raw[DAQ_TOTAL_SENSORS];   // raw ADC counts or mV
} daq_frame_t;

// initialize ADC / MUX hardware
void daq_init(float sample_rate_hz);

// fill one frame of raw data (blocking)
void daq_read(daq_frame_t* frame);
