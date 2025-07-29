#pragma once

#include <stdint.h>

#define NUM_ADC_CH    6    // A0..A5
#define NUM_MUX_CH   16    // 0..15 each
#define DAQ_TOTAL_SENSORS  (NUM_ADC_CH * NUM_MUX_CH)

typedef struct {
    uint32_t raw[DAQ_TOTAL_SENSORS];   // raw ADC counts or mV
} daq_frame_t;

// initialize ADC / MUX hardware
void daq_init(float sample_rate_hz);

// fill one frame of raw data (blocking)
void daq_read(daq_frame_t* frame);
